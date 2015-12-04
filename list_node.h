#ifndef _LIST_NODE_H_
#define _LIST_NODE_H_

#define SUCCESS 0
#define FAILURE (-1)

typedef struct ListNode {
    void 			*data;
    struct ListNode *next;
} tListNode;

typedef struct ListStruct {
    struct ListNode *head;
    struct ListNode *tail;
    int 			length;
} tListStruct;

tListStruct * CreateList();

int DeleteList(tListStruct *pListStruct, 
    void DeepDelete(tListNode * pNode, void * args), void * args);

int AddListNode(tListStruct *pListStruct, void *pdata, 
	int Conditon(tListNode * pNode, void * args), void * args);

int DeleteListNode(tListStruct *pListStruct, tListNode *pNode);

tListNode * SearchListNode(tListStruct *pListStruct, 
    int Conditon(tListNode * pNode, void * args), void * args);

tListNode * GetListHead(tListStruct *pListStruct);

tListNode * GetNextListNode(tListStruct *pListStruct, tListNode *pNode);

#endif
