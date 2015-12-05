/*******************************************************
 File name: list_node.c
 
 Date: 2015.12.3
 
 Description: �ṩ���ڴ����������ݽṹ����غ�����������
    ��������ӽڵ㡢�����ڵ㡢ɾ�������ڵ㡢����ڵ�
    �ķ��� 

 History: 1��2015.12.5 �޸Ĳ��ִ��� 
 
********************************************************/


#include <stdlib.h>

#include "list_node.h"

/*
// ����ڵ�ԭ������ 
typedef struct ListNode {
    void 			*data; // �Բ����������Ͷ���data 
    struct ListNode *next;
} tListNode;

// ������Ϣͷԭ������ 
typedef struct ListStruct {
    struct ListNode *head;
    struct ListNode *tail;
    int 			length;
} tListStruct;
*/

// �������� 
tListStruct * CreateList()
{
	tListStruct *pList = (tListStruct*)malloc(sizeof(tListStruct));

	if (NULL == pList) {
		return NULL;
	}

	pList->head = NULL;
	pList->tail = NULL;
	pList->length = 0;

	return pList;
}

// ɾ������[����ѡ�����ͷ��ڲ������ڴ�]
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
		
		// �ɶ��������ͷ�ÿһ���ڵ��ڲ� 
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

// ��������ڵ�������β��[����ѡ����������ڵ�] 
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
	    // δ�ṩ�������ʱ��������β�� 
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
        // �ṩ�������ʱ���������������� 
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

// ��������ڵ�ʹ֮��Ϊ����ͷ�� 
int AddListNodeToHead(tListStruct *pListStruct, void *pdata)
{
    if (NULL == pListStruct) {
		return FAILURE;
	}
	
	tListNode *node = (tListNode*)malloc(sizeof(tListNode));
	node->data = pdata;
	node->next = NULL;
	
	if (NULL == pListStruct->head) {
		AddListNode(pListStruct, pdata, NULL, NULL);
    }
    else {
        tListNode * pHead = pListStruct->head;
        node->next = pHead;
        pListStruct->head = node;
        pListStruct->length += 1;
    }
} 

// ɾ��������ĳһ�ڵ� 
int DeleteListNode(tListStruct *pListStruct, tListNode *pNode)
{
	if (NULL == pListStruct || NULL == pNode) {
		return FAILURE;
	}
    
    // ������ֻ��һ���ڵ�ʱ 
	if (pListStruct->head == pNode) {
		pListStruct->head = pListStruct->head->next;
		pNode->next = NULL;
		pListStruct->length -= 1;
		if (pListStruct->length == 0) {
			pListStruct->tail = NULL;
		}
		return SUCCESS;
	}
    
    // ���ҽڵ㲢ɾ�� 
	tListNode *tempNode = pListStruct->head;
	while (tempNode != NULL) {
		if (tempNode->next == pNode) {
			tempNode->next = tempNode->next->next;
			pNode->next = NULL;
			pListStruct->length -= 1;
			return SUCCESS;
		}
		tempNode = tempNode->next;
	}

	return FAILURE;
}

// �����������ڵ� 
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

// ���������ͷ�ڵ� 
tListNode * GetListHead(tListStruct *pListStruct)
{
	if (NULL == pListStruct) {
		return NULL;
	}
	
	return pListStruct->head;
}

// ���������β�ڵ� 
tListNode * GetListTail(tListStruct *pListStruct)
{
    if (NULL == pListStruct) {
		return NULL;
	}
	
	return pListStruct->tail;
}

// ���ص�ǰ�ڵ����һ�ڵ� 
tListNode * GetListNext(tListNode *pNode)
{
	if (NULL == pNode) {
		return NULL;
	}
	
	return pNode->next;
}
