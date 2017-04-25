/*
 * rbcPool.c --
 *
 * Copyright 2001 Silicon Metrics, Inc.
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and warranty
 * disclaimer appear in supporting documentation, and that the names
 * of Lucent Technologies any of their entities not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.
 *
 * Silicon Metrics disclaims all warranties with regard to this
 * software, including all implied warranties of merchantability and
 * fitness.  In no event shall Lucent Technologies be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether in
 * an action of contract, negligence or other tortuous action, arising
 * out of or in connection with the use or performance of this
 * software.
 */

#include "rbcInt.h"
#include "rbcPool.h"

/*
 * Rbc_Pool --
 *
 *	Implements a pool memory allocator. 
 *
 *	  + It's faster allocating memory since malloc/free are called
 *	    only a fraction of the normal times.  Fixed size items can 
 *	    be reused without deallocating/reallocating memory.
 *	  + You don't have the extra 8-16 byte overhead per malloc. 
 *	  - Memory is freed only when the entire pool is destroyed.
 *	  - Memory is allocated in chunks. More memory is allocated 
 *	    than used.  
 *	  0 Depending upon allocation/deallocation patterns, locality
 *	    may be improved or degraded.
 *
 *      The pool is a chain of malloc'ed blocks.
 *
 *             +---------+  +---------+  +---------+  
 *       NULL<-| nextPtr |<-| nextPtr |<-| nextPtr |<- headPtr
 *             |---------|  |---------|  |---------|  
 *             | chunk1  |  | chunk2  |  | chunk3  |  
 *             +---------+  |         |  |         |  
 *                          +---------+  |         |  
 *                                       |         |  
 *                                       |         |  
 *                                       +---------+  
 *
 *      Each chunk contains an integral number of fixed size items.
 *	The number of items doubles until a maximum size is reached
 *      (each subsequent new chunk will be the maximum).  Chunks
 *	are allocated only when needed (no more space is available
 *	in the last chunk).
 *
 *	The chain of blocks is only freed when the entire pool is
 *	destroyed.  
 *
 *      A freelist of unused items also maintained. Each freed item
 *	is prepended to a free list.  Before allocating new chunks
 *	the freelist is examined to see if an unused items exist.
 *
 *               chunk1       chunk2       chunk3
 *            +---------+  +---------+  +---------+  
 *      NULL<-| unused  |  |         |  |         |
 *            +----^----+  +---------+  +---------+  
 *            | unused  |<-| unused  |<-| unused  |       
 *            +---------+  +---------+  +----^----+  
 *            |         |  |         |  | unused  |
 *            +---------+  |         |  +----^----+
 *                         |         |  |    |    |
 *                         +---------+  +----|----+
 *                                      | usused  |<- freePtr
 *                                      +---------+  
 */

#define POOL_MAX_CHUNK_SIZE      ((1<<16) - sizeof(Rbc_PoolChain))

#ifndef ALIGN
#define ALIGN(a) \
	(((size_t)a + (sizeof(void *) - 1)) & (~(sizeof(void *) - 1)))
#endif /* ALIGN */

static Rbc_PoolAllocProc VariablePoolAllocItem;
static Rbc_PoolFreeProc  VariablePoolFreeItem;
static Rbc_PoolAllocProc FixedPoolAllocItem;
static Rbc_PoolFreeProc  FixedPoolFreeItem;
static Rbc_PoolAllocProc StringPoolAllocItem;
static Rbc_PoolFreeProc  StringPoolFreeItem;

/*
 *----------------------------------------------------------------------
 *
 * VariablePoolAllocItem --
 *
 *      Returns a new item.  First check if there is any more space 
 *	left in the current chunk.  If there isn't then next check
 *	the free list for unused items.  Finally allocate a new 
 *	chunk and return its first item.
 *
 * Results:
 *      Returns a new (possible reused) item.
 *
 * Side Effects:
 *	A new memory chunk may be allocated.
 *
 *----------------------------------------------------------------------
 */
static void *
VariablePoolAllocItem(poolPtr, size)
    struct Rbc_PoolStruct *poolPtr;
    size_t size;		/* Number of bytes to allocate. */
{
    Rbc_PoolChain *chainPtr;
    void *memPtr;

    size = ALIGN(size);
    if (size >= POOL_MAX_CHUNK_SIZE) {
	/* 
	 * Handle oversized requests by allocating a chunk to hold the
	 * single item and immediately placing it into the in-use list.
	 */
	chainPtr = ckalloc(sizeof(Rbc_PoolChain) + size);
        if (poolPtr->headPtr == NULL) {
	    poolPtr->headPtr = chainPtr;
	} else {
	    chainPtr->nextPtr = poolPtr->headPtr->nextPtr;
	    poolPtr->headPtr->nextPtr = chainPtr;
	}
	memPtr = (void *)chainPtr;
    } else {
	if (poolPtr->bytesLeft >= size) {
	    poolPtr->bytesLeft -= size;
	    memPtr = (char *)(poolPtr->headPtr + 1) + poolPtr->bytesLeft;
	} else {
	    poolPtr->waste += poolPtr->bytesLeft;
	    /* Create a new block of items and prepend it to the in-use list */
	    poolPtr->bytesLeft = POOL_MAX_CHUNK_SIZE;
	    /* Allocate the requested chunk size, plus the header */
	    chainPtr = ckalloc(sizeof(Rbc_PoolChain) + poolPtr->bytesLeft);
	    chainPtr->nextPtr = poolPtr->headPtr;
	    poolPtr->headPtr = chainPtr;
	    /* Peel off a new item. */
	    poolPtr->bytesLeft -= size;
	    memPtr = (char *)(chainPtr + 1) + poolPtr->bytesLeft;
	}
    }
    return memPtr;
}

/*
 *----------------------------------------------------------------------
 *
 * VariablePoolFreeItem --
 *
 *      Placeholder for freeProc routine.  The pool memory is 
 *	not reclaimed or freed until the entire pool is released.
 *
 * Results:
 *      None.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static void
VariablePoolFreeItem(poolPtr, item) 
    struct Rbc_PoolStruct *poolPtr;
    void *item;
{
    /* Does nothing */
}

/*
 *----------------------------------------------------------------------
 *
 * StringPoolAllocItem --
 *
 *      Returns a new item.  First check if there is any more space 
 *	left in the current chunk.  If there isn't then next check
 *	the free list for unused items.  Finally allocate a new 
 *	chunk and return its first item.
 *
 * Results:
 *      Returns a new (possible reused) item.
 *
 * Side Effects:
 *	A new memory chunk may be allocated.
 *
 *----------------------------------------------------------------------
 */
static void *
StringPoolAllocItem(poolPtr, size)
    struct Rbc_PoolStruct *poolPtr;
    size_t size;		/* Number of bytes to allocate. */
{
    Rbc_PoolChain *chainPtr;
    void *memPtr;

    if (size >= POOL_MAX_CHUNK_SIZE) {
	/* 
	 * Handle oversized requests by allocating a chunk to hold the
	 * single item and immediately placing it into the in-use list.
	 */
	chainPtr = ckalloc(sizeof(Rbc_PoolChain) + size);
        if (poolPtr->headPtr == NULL) {
	    poolPtr->headPtr = chainPtr;
	} else {
	    chainPtr->nextPtr = poolPtr->headPtr->nextPtr;
	    poolPtr->headPtr->nextPtr = chainPtr;
	}
	memPtr = (void *)chainPtr;
    } else {
	if (poolPtr->bytesLeft >= size) {
	    poolPtr->bytesLeft -= size;
	    memPtr = (char *)(poolPtr->headPtr + 1) + poolPtr->bytesLeft;
	} else {
	    poolPtr->waste += poolPtr->bytesLeft;
	    /* Create a new block of items and prepend it to the
	     * in-use list */
	    poolPtr->bytesLeft = POOL_MAX_CHUNK_SIZE;
	    /* Allocate the requested chunk size, plus the header */
	    chainPtr = ckalloc(sizeof(Rbc_PoolChain) + poolPtr->bytesLeft);
	    chainPtr->nextPtr = poolPtr->headPtr;
	    poolPtr->headPtr = chainPtr;
	    /* Peel off a new item. */
	    poolPtr->bytesLeft -= size;
	    memPtr = (char *)(chainPtr + 1) + poolPtr->bytesLeft;
	}
    }
    return memPtr;
}

/*
 *----------------------------------------------------------------------
 *
 * StringPoolFreeItem --
 *
 *      Placeholder for freeProc routine.  String pool memory is 
 *	not reclaimed or freed until the entire pool is released.
 *
 * Results:
 *      None.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static void
StringPoolFreeItem(poolPtr, item) 
    struct Rbc_PoolStruct *poolPtr;
    void *item;
{
    /* Does nothing */
}

/*
 *       The fixed size pool is a chain of malloc'ed blocks.
 *
 *             +---------+  +---------+  +---------+  
 *       NULL<-| nextPtr |<-| nextPtr |<-| nextPtr |<- headPtr
 *             |---------|  |---------|  |---------|  
 *             | chunk1  |  | chunk2  |  | chunk3  |  
 *             +---------+  |         |  |         |  
 *                          +---------+  |         |  
 *                                       |         |  
 *                                       |         |  
 *                                       +---------+  
 *
 *      Each chunk contains an integral number of fixed size items.
 *	The number of items doubles until a maximum size is reached
 *      (each subsequent new chunk will be the maximum).  Chunks
 *	are allocated only when needed (no more space is available
 *	in the last chunk).
 *
 *	The chain of blocks is only freed when the entire pool is
 *	destroyed.  
 *
 *      A freelist of unused items also maintained. Each freed item
 *	is prepended to a free list.  Before allocating new chunks
 *	the freelist is examined to see if an unused items exist.
 *
 *               chunk1       chunk2       chunk3
 *            +---------+  +---------+  +---------+  
 *      NULL<-| unused  |  |         |  |         |
 *            +----^----+  +---------+  +---------+  
 *            | unused  |<-| unused  |<-| unused  |       
 *            +---------+  +---------+  +----^----+  
 *            |         |  |         |  | unused  |
 *            +---------+  |         |  +----^----+
 *                         |         |  |    |    |
 *                         +---------+  +----|----+
 *                                      | usused  |<- freePtr
 *                                      +---------+  
 */

/*
 *----------------------------------------------------------------------
 *
 * FixedPoolFreeItem --
 *
 *      Returns a new item.  First check if there is any more space 
 *	left in the current chunk.  If there isn't then next check
 *	the free list for unused items.  Finally allocate a new 
 *	chunk and return its first item.
 *
 * Results:
 *      Returns a new (possible reused) item.
 *
 * Side Effects:
 *	A new memory chunk may be allocated.
 *
 *----------------------------------------------------------------------
 */
static void *
FixedPoolAllocItem(poolPtr, size)
    struct Rbc_PoolStruct *poolPtr;
    size_t size;
{
    Rbc_PoolChain *chainPtr;
    void *newPtr;

    size = ALIGN(size);
    if (poolPtr->itemSize == 0) {
	poolPtr->itemSize = size;
    }
    assert(size == poolPtr->itemSize);

    if (poolPtr->bytesLeft > 0) {
	poolPtr->bytesLeft -= poolPtr->itemSize;
	newPtr = (char *)(poolPtr->headPtr + 1) + poolPtr->bytesLeft;
    } else if (poolPtr->freePtr != NULL) { /* Reuse from the free list. */
	/* Reuse items on the free list */
	chainPtr = poolPtr->freePtr;
	poolPtr->freePtr = chainPtr->nextPtr;
	newPtr = (void *)chainPtr;
    } else {			/* Allocate another block. */
	
	/* Create a new block of items and prepend it to the in-use list */
	poolPtr->bytesLeft = poolPtr->itemSize * (1 << poolPtr->poolSize);
	if (poolPtr->bytesLeft < POOL_MAX_CHUNK_SIZE) {
	    poolPtr->poolSize++; /* Keep doubling the size of the new 
				  * chunk up to a maximum size. */
	}
	/* Allocate the requested chunk size, plus the header */
	chainPtr = ckalloc(sizeof(Rbc_PoolChain) + poolPtr->bytesLeft);
	chainPtr->nextPtr = poolPtr->headPtr;
	poolPtr->headPtr = chainPtr;

	/* Peel off a new item. */
	poolPtr->bytesLeft -= poolPtr->itemSize;
	newPtr = (char *)(poolPtr->headPtr + 1) + poolPtr->bytesLeft;
    }
    return newPtr;
}

/*
 *----------------------------------------------------------------------
 *
 * FixedPoolFreeItem --
 *
 *      Frees an item.  The actual memory is not freed.  The item
 *	instead is prepended to a freelist where it may be reclaimed
 *	and used again.
 *
 * Results:
 *      None.
 *
 * Side Effects:
 *	Item is placed on the pool's free list.
 *
 *----------------------------------------------------------------------
 */
static void
FixedPoolFreeItem(poolPtr, item) 
    struct Rbc_PoolStruct *poolPtr;
    void *item;
{
    Rbc_PoolChain *chainPtr = (Rbc_PoolChain *)item;
    
    /* Prepend the newly deallocated item to the free list. */
    chainPtr->nextPtr = poolPtr->freePtr;
    poolPtr->freePtr = chainPtr;
}

/*
 *----------------------------------------------------------------------
 *
 * Rbc_PoolCreate --
 *
 *      Creates a new memory pool for fixed-size/variable-size/string
 *      items.  
 *
 * Results:
 *      Returns a pointer to the newly allocated pool.
 *
 *---------------------------------------------------------------------- 
 */

Rbc_Pool
Rbc_PoolCreate(type)
    int type;
{
    struct Rbc_PoolStruct *poolPtr;

    poolPtr = ckalloc(sizeof(struct Rbc_PoolStruct));
    switch (type) {
    case RBC_VARIABLE_SIZE_ITEMS:
	poolPtr->allocProc = VariablePoolAllocItem;
	poolPtr->freeProc = VariablePoolFreeItem;
	break;
    case RBC_FIXED_SIZE_ITEMS:
	poolPtr->allocProc = FixedPoolAllocItem;
	poolPtr->freeProc = FixedPoolFreeItem;
	break;
    case RBC_STRING_ITEMS:
 	poolPtr->allocProc = StringPoolAllocItem;
	poolPtr->freeProc = StringPoolFreeItem;
	break;
    }
    poolPtr->headPtr = poolPtr->freePtr = NULL;
    poolPtr->waste = poolPtr->bytesLeft = 0;
    poolPtr->poolSize = poolPtr->itemSize = 0;
    return poolPtr;
}

/*
 *----------------------------------------------------------------------
 *
 * Rbc_PoolDestroy --
 *
 *      Destroys the given memory pool.  The chain of allocated blocks
 *	are freed.  The is the only time that memory is actually freed.
 *
 * Results:
 *      None.
 *
 * Side Effects:
 *	All memory used by the pool is freed.
 *
 *----------------------------------------------------------------------
 */
void  
Rbc_PoolDestroy(poolPtr)
    struct Rbc_PoolStruct *poolPtr;
{
    register Rbc_PoolChain *chainPtr, *nextPtr;
    
    for (chainPtr = poolPtr->headPtr; chainPtr != NULL; chainPtr = nextPtr) {
	nextPtr = chainPtr->nextPtr;
	ckfree(chainPtr);
    }
    ckfree(poolPtr);
}

/*
 *----------------------------------------------------------------------
 *
 * Rbc_InitHashTableWithPool --
 *
 *      Given storage for a hash table, set up the fields to prepare
 *      the hash table for use.  The only difference between this 
 *      routine and Tcl_InitHashTable is that is uses a pool allocator
 *      to allocate memory for hash table entries.  The type of pool
 *      is either fixed or variable size (string) keys.
 *
 * Results:
 *      None.
 *
 * Side effects:
 *      TablePtr is now ready to be passed to Tcl_FindHashEntry and
 *      Tcl_CreateHashEntry.
 *
 *----------------------------------------------------------------------
 */

/*
void
Rbc_InitHashTableWithPool(
    register Tcl_HashTable *tablePtr,   // Pointer to table record, which
                                        // is supplied by the caller.
    size_t keyType)                     // Type of keys to use in table.
{   
    Tcl_InitHashTable(tablePtr, keyType);
    if (keyType == TCL_STRING_KEYS) {
        tablePtr->hPool = Rbc_PoolCreate(RBC_VARIABLE_SIZE_ITEMS);
    } else {
        tablePtr->hPool = Rbc_PoolCreate(RBC_FIXED_SIZE_ITEMS);
    }
}
*/
