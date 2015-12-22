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
	tListNode *p = NULL;

	if (NULL == pListStruct) {
		return FAILURE;
	}

	while (pListStruct->head != NULL) {
		p = pListStruct->head;
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
int AddListNode(tListStruct *pListStruct, void *pData,
	int Condition(tListNode * pNode, tListNode * pAddNode, void * args), void * args)
{
	tListNode *node = NULL;
	tListNode *tempNode = NULL;

	if (NULL == pListStruct) {
		return FAILURE;
	}
	
	node = (tListNode*)malloc(sizeof(tListNode));
	node->data = pData;
	node->next = NULL;
	
	if (NULL == Condition) {
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
    	tempNode = pListStruct->head;
    	while (tempNode != NULL) {
    		if (Condition(tempNode, node, args) == SUCCESS) {
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
int AddListNodeToHead(tListStruct *pListStruct, void *pData)
{
	tListNode *node = NULL;
	tListNode * pHead = NULL;

    if (NULL == pListStruct) {
		return FAILURE;
	}
	
	node = (tListNode*)malloc(sizeof(tListNode));
	node->data = pData;
	node->next = NULL;
	
	if (NULL == pListStruct->head) {
		AddListNode(pListStruct, pData, NULL, NULL);
    }
    else {
        pHead = pListStruct->head;
        node->next = pHead;
        pListStruct->head = node;
        pListStruct->length += 1;
    }
} 

// ɾ��������ĳһ�ڵ� 
int DeleteListNode(tListStruct *pListStruct, tListNode *pNode)
{
	tListNode *tempNode = NULL;

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
	tempNode = pListStruct->head;
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
	int Condition(tListNode * pNode, void * args), void * args)
{
	tListNode *tempNode = NULL;

	if (NULL == pListStruct || NULL == Condition) {
		return NULL;
	}
	tempNode = pListStruct->head;
	while (tempNode != NULL) {
		if (Condition(tempNode, args) == SUCCESS) {
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

// ���ص�ǰ�ڵ����һ�ڵ� 
tListNode * GetListPrev(tListStruct * pList, tListNode *pNode)
{
	tListNode * pTempNode = NULL;
    if (pList == NULL || pNode == NULL) {
        return NULL;
    }
    
    pTempNode = pList->head;
    while (pTempNode->next != NULL) {
        if (pTempNode->next == pNode) {
            return pTempNode;
        }
        pTempNode = pTempNode->next;
    }
    return NULL;
}

