#include "list_node.h"
#include <stdlib.h>

/*
typedef struct ListNode {
    void 			*data;
    struct ListNode *next;
} tListNode;

typedef struct ListStruct {
    struct ListNode *head;
    struct ListNode *tail
    int 			length;
} tListStruct;
*/

tListStruct * CreateList()
{
	tListStruct *list = (tListStruct*)malloc(sizeof(tListStruct));

	if (NULL == list) {
		return NULL;
	}

	list->head = NULL;
	list->tail = NULL;
	list->length = 0;

	return list;
}

int DeleteList(tListStruct *pListStruct, 
    void DeepDelete(tListNode * pNode, void * args), void * args)
{
	if (NULL == pListStruct) {
		return FAILURE;
	}

	while (pListStruct->head != NULL) {
		tListNode *p = pListStruct->head;
		pListStruct->head = pListStruct->head->next;
		pListStruct->length -= 1;
		
		if (DeepDelete != NULL) {
		    DeepDelete(p, args);
        }
        
		free(p);
	}

	pListStruct->tail = NULL;
	pListStruct->length = 0;
	
	free(pListStruct);
	return SUCCESS;
}

int AddListNode(tListStruct *pListStruct, void *pdata, 
	int Conditon(tListNode * pNode, void * args), void * args)
{
	if (NULL == pListStruct) {
		return FAILURE;
	}
	
	tListNode *node = (tListNode*)malloc(sizeof(tListNode));
	node->data = pdata;
	node->next = NULL;
	
	if (NULL == Conditon) {
    	if (NULL == pListStruct->head) {
    		pListStruct->head = node;
    		pListStruct->length += 1;
    	}
    
    	if (NULL == pListStruct->tail) {
    		pListStruct->tail = node;
    	}
    	else {
    		pListStruct->tail->next = node;
    		pListStruct->tail = node;
    		pListStruct->length += 1;
    	}
    
    	return SUCCESS;
    }
    else {    
    	tListNode *tempNode = pListStruct->head;
    	while (tempNode != NULL) {
    		if (Conditon(tempNode, args) == SUCCESS) {
    			node->next = tempNode->next;
    			tempNode->next = node;
    			pListStruct->length += 1;
    			return SUCCESS;
    		}
    		tempNode = tempNode->next;
    	}
    	return FAILURE;	
    }
}

int DeleteListNode(tListStruct *pListStruct, tListNode *pNode)
{
	if (NULL == pListStruct || NULL == pNode) {
		return FAILURE;
	}

	if (pListStruct->head == pNode) {
		pListStruct->head = pListStruct->head->next;
		pListStruct->length -= 1;
		if (pListStruct->length == 0) {
			pListStruct->tail = NULL;
		}
		return SUCCESS;
	}

	tListNode *tempNode = pListStruct->head;
	while (tempNode != NULL) {
		if (tempNode->next == pNode) {
			tempNode->next = tempNode->next->next;
			pListStruct->length -= 1;
			return SUCCESS;
		}
		tempNode = tempNode->next;
	}

	return FAILURE;
}

tListNode * SearchListNode(tListStruct *pListStruct, 
	int Conditon(tListNode * pNode, void * args), void * args)
{
	if (NULL == pListStruct || NULL == Conditon) {
		return NULL;
	}
	tListNode *tempNode = pListStruct->head;
	while (tempNode != NULL) {
		if (Conditon(tempNode, args) == SUCCESS) {
			return tempNode;
		}
		tempNode = tempNode->next;
	}
	return NULL;
}

tListNode * GetListHead(tListStruct *pListStruct)
{
	if (NULL == pListStruct) {
		return NULL;
	}
	return pListStruct->head;
}

tListNode * GetNextListNode(tListStruct *pListStruct, tListNode *pNode)
{
	if (NULL == pListStruct || NULL == pNode) {
		return NULL;
	}

	tListNode *tempNode = pListStruct->head;
	while (tempNode != NULL) {
		if (tempNode == pNode) {
			return tempNode->next;
		}
		tempNode = tempNode->next;
	}
	return NULL;
}
