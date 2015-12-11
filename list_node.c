/*******************************************************
 File name: list_node.c
 
 Date: 2015.12.3
 
 Description: 提供用于创建链表数据结构的相关函数，包括创
    建链表、添加节点、搜索节点、删除链表或节点、特殊节点
    的返回 

 History: 1、2015.12.5 修改部分代码 
 
********************************************************/


#include <stdlib.h>

#include "list_node.h"

/*
// 链表节点原型声明 
typedef struct ListNode {
    void 			*data; // 以不定数据类型定义data 
    struct ListNode *next;
} tListNode;

// 链表信息头原型声明 
typedef struct ListStruct {
    struct ListNode *head;
    struct ListNode *tail;
    int 			length;
} tListStruct;
*/

// 创建链表 
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

// 删除链表[，可选深入释放内层申请内存]
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
		
		// 可定制深入释放每一个节点内部 
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

// 增加链表节点至链表尾部[，可选按条件插入节点] 
int AddListNode(tListStruct *pListStruct, void *pdata, 
	int Conditon(tListNode * pNode, tListNode * pAddNode, void * args), void * args)
{
	if (NULL == pListStruct) {
		return FAILURE;
	}
	
	tListNode *node = (tListNode*)malloc(sizeof(tListNode));
	node->data = pdata;
	node->next = NULL;
	
	if (NULL == Conditon) {
	    // 未提供添加条件时插入链表尾部 
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
        // 提供添加条件时按条件搜索并插入 
    	tListNode *tempNode = pListStruct->head;
    	while (tempNode != NULL) {
    		if (Conditon(tempNode, node, args) == SUCCESS) {
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

// 增加链表节点使之成为链表头部 
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

// 删除链表中某一节点 
int DeleteListNode(tListStruct *pListStruct, tListNode *pNode)
{
	if (NULL == pListStruct || NULL == pNode) {
		return FAILURE;
	}
    
    // 链表中只有一个节点时 
	if (pListStruct->head == pNode) {
		pListStruct->head = pListStruct->head->next;
		pNode->next = NULL;
		pListStruct->length -= 1;
		if (pListStruct->length == 0) {
			pListStruct->tail = NULL;
		}
		return SUCCESS;
	}
    
    // 查找节点并删除 
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

// 按条件搜索节点 
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

// 返回链表的头节点 
tListNode * GetListHead(tListStruct *pListStruct)
{
	if (NULL == pListStruct) {
		return NULL;
	}
	
	return pListStruct->head;
}

// 返回链表的尾节点 
tListNode * GetListTail(tListStruct *pListStruct)
{
    if (NULL == pListStruct) {
		return NULL;
	}
	
	return pListStruct->tail;
}

// 返回当前节点的下一节点 
tListNode * GetListNext(tListNode *pNode)
{
	if (NULL == pNode) {
		return NULL;
	}
	
	return pNode->next;
}

// 返回当前节点的上一节点 
tListNode * GetListPrev(tListStruct * pList, tListNode *pNode)
{
    if (pList == NULL || pNode == NULL) {
        return NULL;
    }
    
    tListNode * pTempNode = pList->head;
    while (pTempNode->next != NULL) {
        if (pTempNode->next == pNode) {
            return pTempNode;
        }
        pTempNode = pTempNode->next;
    }
    return NULL;
}
