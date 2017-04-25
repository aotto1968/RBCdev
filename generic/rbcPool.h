#ifndef RBC_POOL_H
#define RBC_POOL_H

typedef struct Rbc_PoolChainStruct {
   struct Rbc_PoolChainStruct *nextPtr;
} Rbc_PoolChain;

#define RBC_STRING_ITEMS		0
#define RBC_FIXED_SIZE_ITEMS		1
#define RBC_VARIABLE_SIZE_ITEMS		2

typedef struct Rbc_PoolStruct *Rbc_Pool;

typedef void *(Rbc_PoolAllocProc) _ANSI_ARGS_((Rbc_Pool pool, size_t size));
typedef void (Rbc_PoolFreeProc) _ANSI_ARGS_((Rbc_Pool pool, void *item));

struct Rbc_PoolStruct {
    Rbc_PoolChain *headPtr;	/* Chain of malloc'ed chunks. */
    Rbc_PoolChain *freePtr; 	/* List of deleted items. This is only used
				 * for fixed size items. */
    size_t poolSize;		/* Log2 of # of items in the current block. */
    size_t itemSize;		/* Size of an item. */
    size_t bytesLeft;		/* # of bytes left in the current chunk. */
    size_t waste;
    
    Rbc_PoolAllocProc *allocProc;
    Rbc_PoolFreeProc *freeProc;
};

EXTERN Rbc_Pool Rbc_PoolCreate _ANSI_ARGS_((int type));
EXTERN void Rbc_PoolDestroy _ANSI_ARGS_((Rbc_Pool pool));

#define Rbc_PoolAllocItem(poolPtr, n) (*((poolPtr)->allocProc))(poolPtr, n)
#define Rbc_PoolFreeItem(poolPtr, item) (*((poolPtr)->freeProc))(poolPtr, item)

#endif /* RBC_POOL_H */
