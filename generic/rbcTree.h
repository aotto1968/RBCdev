
/*
 * rbcTree.h --
 *
 * Copyright 1998-1999 Lucent Technologies, Inc.
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and warranty
 * disclaimer appear in supporting documentation, and that the names
 * of Lucent Technologies or any of their entities not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.
 *
 * Lucent Technologies disclaims all warranties with regard to this
 * software, including all implied warranties of merchantability and
 * fitness.  In no event shall Lucent Technologies be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether in
 * an action of contract, negligence or other tortuous action, arising
 * out of or in connection with the use or performance of this
 * software.
 *
 *	The "tree" data object was created by George A. Howlett.
 */

#ifndef _RBC_TREE_H
#define _RBC_TREE_H

#include "rbcChain.h"
#include "rbcPool.h"

typedef struct Rbc_TreeNodeStruct *Rbc_TreeNode;
typedef struct Rbc_TreeObjectStruct *Rbc_TreeObject;
typedef struct Rbc_TreeClientStruct *Rbc_Tree;
typedef struct Rbc_TreeTraceStruct *Rbc_TreeTrace;
typedef struct Rbc_TreeValueStruct *Rbc_TreeValue;
typedef struct Rbc_TreeTagEntryStruct Rbc_TreeTagEntry;
typedef struct Rbc_TreeTagTableStruct Rbc_TreeTagTable;

typedef char *Rbc_TreeKey;

#define TREE_PREORDER		(1<<0)
#define TREE_POSTORDER		(1<<1)
#define TREE_INORDER		(1<<2)
#define TREE_BREADTHFIRST	(1<<3)

#define TREE_TRACE_UNSET	(1<<3)
#define TREE_TRACE_WRITE	(1<<4)
#define TREE_TRACE_READ		(1<<5)
#define TREE_TRACE_CREATE	(1<<6)
#define TREE_TRACE_ALL		\
    (TREE_TRACE_UNSET | TREE_TRACE_WRITE | TREE_TRACE_READ | TREE_TRACE_CREATE)
#define TREE_TRACE_MASK		(TREE_TRACE_ALL)

#define TREE_TRACE_FOREIGN_ONLY	(1<<8)
#define TREE_TRACE_ACTIVE	(1<<9)

#define TREE_NOTIFY_CREATE	(1<<0)
#define TREE_NOTIFY_DELETE	(1<<1)
#define TREE_NOTIFY_MOVE	(1<<2)
#define TREE_NOTIFY_SORT	(1<<3)
#define TREE_NOTIFY_RELABEL	(1<<4)
#define TREE_NOTIFY_ALL		\
    (TREE_NOTIFY_CREATE | TREE_NOTIFY_DELETE | TREE_NOTIFY_MOVE | \
	TREE_NOTIFY_SORT | TREE_NOTIFY_RELABEL)
#define TREE_NOTIFY_MASK	(TREE_NOTIFY_ALL)

#define TREE_NOTIFY_WHENIDLE	 (1<<8)
#define TREE_NOTIFY_FOREIGN_ONLY (1<<9)
#define TREE_NOTIFY_ACTIVE	 (1<<10)

typedef struct {
    int type;
    Rbc_Tree tree;
    int inode;			/* Node of event */
    Tcl_Interp *interp;
} Rbc_TreeNotifyEvent;

typedef struct {
    Rbc_TreeNode node;		/* Node being searched. */
    unsigned long nextIndex;	/* Index of next bucket to be
				 * enumerated after present one. */
    Rbc_TreeValue nextValue;	/* Next entry to be enumerated in the
				 * the current bucket. */
} Rbc_TreeKeySearch;

/*
 * Rbc_TreeObject --
 *
 *	Structure providing the internal representation of the tree
 *	object.	A tree is uniquely identified by a combination of 
 *	its name and originating namespace.  Two trees in the same 
 *	interpreter can have the same names but reside in different 
 *	namespaces.
 *
 *	The tree object represents a general-ordered tree of nodes.
 *	Each node may contain a heterogeneous collection of data
 *	values. Each value is identified by a field name and nodes 
 *	do not need to contain the same data fields. Data field
 *	names are saved as reference counted strings and can be 
 *	shared among nodes.
 *
 *	The tree is threaded.  A node contains both a pointer to 
 *	back its parents and another to its siblings.  Therefore
 *	the tree maybe traversed non-recursively.
 * 
 *	A tree object can be shared by several clients.  When a
 *	client wants to use a tree object, it is given a token
 *	that represents the tree.  The tree object uses the tokens
 *	to keep track of its clients.  When all clients have 
 *	released their tokens the tree is automatically destroyed.
 */
struct Rbc_TreeObjectStruct {
    Tcl_Interp *interp;		/* Interpreter associated with this tree. */

    char *name;

    Tcl_Namespace *nsPtr;

    Tcl_HashEntry *hashPtr;	/* Pointer to this tree object in tree
				 * object hash table. */
    Tcl_HashTable *tablePtr;

    Rbc_TreeNode root;		/* Root of the entire tree. */

    char *sortNodesCmd;		/* Tcl command to invoke to sort entries */

    Rbc_Chain *clients;		/* List of clients using this tree */

    Rbc_Pool nodePool;
    Rbc_Pool valuePool;

    Tcl_HashTable nodeTable;	/* Table of node identifiers. Used to
				 * search for a node pointer given an inode.*/
    unsigned int nextInode;

    unsigned int nNodes;	/* Always counts root node. */

    unsigned int depth;		/* Maximum depth of the tree. */

    unsigned int flags;		/* Internal flags. See definitions
				 * below. */
    unsigned int notifyFlags;	/* Notification flags. See definitions
				 * below. */

};

/*
 * Rbc_TreeNodeStruct --
 *
 *	Structure representing a node in a general ordered tree.
 *	Nodes are identified by their index, or inode.  Nodes also
 *	have names, but nodes names are not unique and can be 
 *	changed.  Inodes are valid even if the node is moved.
 *
 *	Each node can contain a list of data fields.  Fields are
 *	name-value pairs.  The values are represented by Tcl_Objs.
 *	
 */
struct Rbc_TreeNodeStruct {
    Rbc_TreeNode parent;	/* Parent node. If NULL, then this is
				   the root node. */
    Rbc_TreeNode next;		/* Next sibling node. */
    Rbc_TreeNode prev;		/* Previous sibling node. */
    Rbc_TreeNode first;		/* First child node. */
    Rbc_TreeNode last;		/* Last child node. */

    Rbc_TreeKey label;		/* Node label (doesn't have to be
				 * unique). */

    Rbc_TreeObject treeObject;

    Rbc_TreeValue values;	/* Depending upon the number of values
				 * stored, this is either a chain or
				 * hash table of Rbc_TreeValue
				 * structures.  (Note: if logSize is 
				 * 0, then this is a list).  Each
				 * value contains key/value data
				 * pair.  The data is a Tcl_Obj. */

    unsigned short nValues;	/* # of values for this node. */

    unsigned short logSize;	/* Size of hash table indicated as a
				 * power of 2 (e.g. if logSize=3, then
				 * table size is 8). If 0, this
				 * indicates that the node's values
				 * are stored as a list. */

    unsigned int nChildren;	/* # of children for this node. */
    unsigned int inode;		/* Serial number of the node. */

    unsigned short depth;	/* The depth of this node in the tree. */

    unsigned short flags;
};

struct Rbc_TreeTagEntryStruct {
    char *tagName;
    Tcl_HashEntry *hashPtr;
    Tcl_HashTable nodeTable;
};

struct Rbc_TreeTagTableStruct {
    Tcl_HashTable tagTable;
    int refCount;
};

/*
 * Rbc_TreeClientStruct --
 *
 *	A tree can be shared by several clients.  Each client allocates
 *	this structure which acts as a ticket for using the tree.  Clients
 *	can designate notifier routines that are automatically invoked
 *	by the tree object whenever the tree is changed is specific
 *	ways by other clients.
 */

struct Rbc_TreeClientStruct {
    unsigned int magic;		/* Magic value indicating whether a
				 * generic pointer is really a tree
				 * token or not. */
    Rbc_ChainLink *linkPtr;	/* Pointer into the server's chain of
				 * clients. */
    Rbc_TreeObject treeObject;	/* Pointer to the structure containing
				 * the master information about the
				 * tree used by the client.  If NULL,
				 * this indicates that the tree has
				 * been destroyed (but as of yet, this
				 * client hasn't recognized it). */

    Rbc_Chain *events;		/* Chain of node event handlers. */
    Rbc_Chain *traces;		/* Chain of data field callbacks. */
    Rbc_TreeNode root;		/* Designated root for this client */
    Rbc_TreeTagTable *tagTablePtr;
};


typedef int (Rbc_TreeNotifyEventProc) _ANSI_ARGS_((ClientData clientData, 
	Rbc_TreeNotifyEvent *eventPtr));

typedef int (Rbc_TreeTraceProc) _ANSI_ARGS_((ClientData clientData, 
	Tcl_Interp *interp, Rbc_TreeNode node, Rbc_TreeKey key, 
	unsigned int flags));

typedef int (Rbc_TreeEnumProc) _ANSI_ARGS_((Rbc_TreeNode node, Rbc_TreeKey key,
	Tcl_Obj *valuePtr));

typedef int (Rbc_TreeCompareNodesProc) _ANSI_ARGS_((Rbc_TreeNode *n1Ptr, 
	Rbc_TreeNode *n2Ptr));

typedef int (Rbc_TreeApplyProc) _ANSI_ARGS_((Rbc_TreeNode node, 
	ClientData clientData, int order));

struct Rbc_TreeTraceStruct {
    ClientData clientData;
    Rbc_TreeKey key;
    Rbc_TreeNode node;
    unsigned int mask;
    Rbc_TreeTraceProc *proc;
};

/*
 * Structure definition for information used to keep track of searches
 * through hash tables:p
 */
struct Rbc_TreeKeySearchStruct {
    Rbc_TreeNode node;		/* Table being searched. */
    unsigned long nextIndex;	/* Index of next bucket to be
				 * enumerated after present one. */
    Rbc_TreeValue nextValue;	/* Next entry to be enumerated in the
				 * the current bucket. */
};

EXTERN Rbc_TreeKey Rbc_TreeGetKey _ANSI_ARGS_((CONST char *string));

EXTERN Rbc_TreeNode Rbc_TreeCreateNode _ANSI_ARGS_((Rbc_Tree tree, 
	Rbc_TreeNode parent, CONST char *name, int position)); 
EXTERN Rbc_TreeNode Rbc_TreeCreateNodeWithId _ANSI_ARGS_((Rbc_Tree tree, 
	Rbc_TreeNode parent, CONST char *name, int position, int inode)); 

EXTERN int Rbc_TreeDeleteNode _ANSI_ARGS_((Rbc_Tree tree, Rbc_TreeNode node));

EXTERN int Rbc_TreeMoveNode _ANSI_ARGS_((Rbc_Tree tree, Rbc_TreeNode node, 
	Rbc_TreeNode parent, Rbc_TreeNode before));

EXTERN Rbc_TreeNode Rbc_TreeGetNode _ANSI_ARGS_((Rbc_Tree tree, 
	unsigned int inode));

EXTERN Rbc_TreeNode Rbc_TreeFindChild _ANSI_ARGS_((Rbc_TreeNode parent, 
	CONST char *name));

EXTERN Rbc_TreeNode Rbc_TreeFirstChild _ANSI_ARGS_((Rbc_TreeNode parent));

EXTERN Rbc_TreeNode Rbc_TreeNextSibling _ANSI_ARGS_((Rbc_TreeNode node));

EXTERN Rbc_TreeNode Rbc_TreeLastChild _ANSI_ARGS_((Rbc_TreeNode parent));

EXTERN Rbc_TreeNode Rbc_TreePrevSibling _ANSI_ARGS_((Rbc_TreeNode node));

EXTERN Rbc_TreeNode Rbc_TreeNextNode _ANSI_ARGS_((Rbc_TreeNode root, 
	Rbc_TreeNode node));

EXTERN Rbc_TreeNode Rbc_TreePrevNode _ANSI_ARGS_((Rbc_TreeNode root,
	Rbc_TreeNode node));

EXTERN Rbc_TreeNode Rbc_TreeChangeRoot _ANSI_ARGS_((Rbc_Tree tree,
	Rbc_TreeNode node));

EXTERN Rbc_TreeNode Rbc_TreeEndNode _ANSI_ARGS_((Rbc_TreeNode node,
	unsigned int nodeFlags));

EXTERN int Rbc_TreeIsBefore _ANSI_ARGS_((Rbc_TreeNode node1, 
	Rbc_TreeNode node2));

EXTERN int Rbc_TreeIsAncestor _ANSI_ARGS_((Rbc_TreeNode node1, 
	Rbc_TreeNode node2));

EXTERN int Rbc_TreePrivateValue _ANSI_ARGS_((Tcl_Interp *interp, Rbc_Tree tree,
	Rbc_TreeNode node, Rbc_TreeKey key));

EXTERN int Rbc_TreePublicValue _ANSI_ARGS_((Tcl_Interp *interp, Rbc_Tree tree,
	Rbc_TreeNode node, Rbc_TreeKey key));

EXTERN int Rbc_TreeGetValue _ANSI_ARGS_((Tcl_Interp *interp, Rbc_Tree tree, 
	Rbc_TreeNode node, CONST char *string, Tcl_Obj **valuePtr));

EXTERN int Rbc_TreeValueExists _ANSI_ARGS_((Rbc_Tree tree, Rbc_TreeNode node, 
	CONST char *string));

EXTERN int Rbc_TreeSetValue _ANSI_ARGS_((Tcl_Interp *interp, Rbc_Tree tree, 
	Rbc_TreeNode node, CONST char *string, Tcl_Obj *valuePtr));

EXTERN int Rbc_TreeUnsetValue _ANSI_ARGS_((Tcl_Interp *interp, Rbc_Tree tree, 
	Rbc_TreeNode node, CONST char *string));

EXTERN int Rbc_TreeGetArrayValue _ANSI_ARGS_((Tcl_Interp *interp, 
	Rbc_Tree tree, Rbc_TreeNode node, CONST char *arrayName, 
	CONST char *elemName, Tcl_Obj **valueObjPtrPtr));

EXTERN int Rbc_TreeSetArrayValue _ANSI_ARGS_((Tcl_Interp *interp, 
	Rbc_Tree tree, Rbc_TreeNode node, CONST char *arrayName, 
	CONST char *elemName, Tcl_Obj *valueObjPtr));

EXTERN int Rbc_TreeUnsetArrayValue _ANSI_ARGS_((Tcl_Interp *interp, 
	Rbc_Tree tree, Rbc_TreeNode node, CONST char *arrayName, 
	CONST char *elemName));

EXTERN int Rbc_TreeArrayValueExists _ANSI_ARGS_((Rbc_Tree tree, 
	Rbc_TreeNode node, CONST char *arrayName, CONST char *elemName));

EXTERN int Rbc_TreeArrayNames _ANSI_ARGS_((Tcl_Interp *interp, Rbc_Tree tree, 
	Rbc_TreeNode node, CONST char *arrayName, Tcl_Obj *listObjPtr));

EXTERN int Rbc_TreeGetValueByKey _ANSI_ARGS_((Tcl_Interp *interp, 
	Rbc_Tree tree, Rbc_TreeNode node, Rbc_TreeKey key, 
	Tcl_Obj **valuePtr));

EXTERN int Rbc_TreeSetValueByKey _ANSI_ARGS_((Tcl_Interp *interp, 
	Rbc_Tree tree, Rbc_TreeNode node, Rbc_TreeKey key, Tcl_Obj *valuePtr));

EXTERN int Rbc_TreeUnsetValueByKey _ANSI_ARGS_((Tcl_Interp *interp, 
	Rbc_Tree tree, Rbc_TreeNode node, Rbc_TreeKey key));

EXTERN int Rbc_TreeValueExistsByKey _ANSI_ARGS_((Rbc_Tree tree, 
	Rbc_TreeNode node, Rbc_TreeKey key));

EXTERN Rbc_TreeKey Rbc_TreeFirstKey _ANSI_ARGS_((Rbc_Tree tree, 
	Rbc_TreeNode node, Rbc_TreeKeySearch *cursorPtr));

EXTERN Rbc_TreeKey Rbc_TreeNextKey _ANSI_ARGS_((Rbc_Tree tree, 
	Rbc_TreeKeySearch *cursorPtr));

EXTERN int Rbc_TreeApply _ANSI_ARGS_((Rbc_TreeNode root, 
	Rbc_TreeApplyProc *proc, ClientData clientData));

EXTERN int Rbc_TreeApplyDFS _ANSI_ARGS_((Rbc_TreeNode root, 
	Rbc_TreeApplyProc *proc, ClientData clientData, int order));

EXTERN int Rbc_TreeApplyBFS _ANSI_ARGS_((Rbc_TreeNode root, 
	Rbc_TreeApplyProc *proc, ClientData clientData));

EXTERN int Rbc_TreeSortNode _ANSI_ARGS_((Rbc_Tree tree, Rbc_TreeNode node, 
	Rbc_TreeCompareNodesProc *proc));

EXTERN int Rbc_TreeCreate _ANSI_ARGS_((Tcl_Interp *interp, CONST char *name,
	Rbc_Tree *treePtr));

EXTERN int Rbc_TreeExists _ANSI_ARGS_((Tcl_Interp *interp, CONST char *name));

EXTERN int Rbc_TreeGetToken _ANSI_ARGS_((Tcl_Interp *interp, CONST char *name, 
	Rbc_Tree *treePtr));

EXTERN void Rbc_TreeReleaseToken _ANSI_ARGS_((Rbc_Tree tree));

EXTERN int Rbc_TreeSize _ANSI_ARGS_((Rbc_TreeNode node));

EXTERN Rbc_TreeTrace Rbc_TreeCreateTrace _ANSI_ARGS_((Rbc_Tree tree, 
	Rbc_TreeNode node, CONST char *keyPattern, CONST char *tagName,
	unsigned int mask, Rbc_TreeTraceProc *proc, ClientData clientData));

EXTERN void Rbc_TreeDeleteTrace _ANSI_ARGS_((Rbc_TreeTrace token));

EXTERN void Rbc_TreeCreateEventHandler _ANSI_ARGS_((Rbc_Tree tree, 
	unsigned int mask, Rbc_TreeNotifyEventProc *proc, 
	ClientData clientData));

EXTERN void Rbc_TreeDeleteEventHandler _ANSI_ARGS_((Rbc_Tree tree, 
	unsigned int mask, Rbc_TreeNotifyEventProc *proc, 
	ClientData clientData));

EXTERN void Rbc_TreeRelabelNode _ANSI_ARGS_((Rbc_Tree tree, Rbc_TreeNode node, 
	CONST char *string));
EXTERN void Rbc_TreeRelabelNode2 _ANSI_ARGS_((Rbc_TreeNode node, 
	CONST char *string));
EXTERN char *Rbc_TreeNodePath _ANSI_ARGS_((Rbc_TreeNode node, 
	Tcl_DString *resultPtr));	
EXTERN int Rbc_TreeNodePosition _ANSI_ARGS_((Rbc_TreeNode node));

EXTERN void Rbc_TreeClearTags _ANSI_ARGS_((Rbc_Tree tree, Rbc_TreeNode node));
EXTERN int Rbc_TreeHasTag _ANSI_ARGS_((Rbc_Tree tree, Rbc_TreeNode node, 
	CONST char *tagName));
EXTERN void Rbc_TreeAddTag _ANSI_ARGS_((Rbc_Tree tree, Rbc_TreeNode node, 
	CONST char *tagName));
EXTERN void Rbc_TreeForgetTag _ANSI_ARGS_((Rbc_Tree tree, CONST char *tagName));
EXTERN Tcl_HashTable *Rbc_TreeTagHashTable _ANSI_ARGS_((Rbc_Tree tree, 
	CONST char *tagName));
EXTERN int Rbc_TreeTagTableIsShared _ANSI_ARGS_((Rbc_Tree tree));
EXTERN int Rbc_TreeShareTagTable _ANSI_ARGS_((Rbc_Tree src, Rbc_Tree target));
EXTERN Tcl_HashEntry *Rbc_TreeFirstTag _ANSI_ARGS_((Rbc_Tree tree, 
	Tcl_HashSearch *searchPtr));

#define Rbc_TreeName(token)	((token)->treeObject->name)
#define Rbc_TreeRootNode(token)	((token)->root)
#define Rbc_TreeChangeRoot(token, node) ((token)->root = (node))

#define Rbc_TreeNodeDepth(token, node)	((node)->depth - (token)->root->depth)
#define Rbc_TreeNodeLabel(node)	 ((node)->label)
#define Rbc_TreeNodeId(node)	 ((node)->inode)
#define Rbc_TreeNodeParent(node) ((node)->parent)
#define Rbc_TreeNodeDegree(node) ((node)->nChildren)

#define Rbc_TreeIsLeaf(node)     ((node)->nChildren == 0)
#define Rbc_TreeNextNodeId(token)     ((token)->treeObject->nextInode)

#define Rbc_TreeFirstChild(node) ((node)->first)
#define Rbc_TreeLastChild(node) ((node)->last)
#define Rbc_TreeNextSibling(node) (((node) == NULL) ? NULL : (node)->next)
#define Rbc_TreePrevSibling(node) (((node) == NULL) ? NULL : (node)->prev)

#endif /* _RBC_TREE_H */

