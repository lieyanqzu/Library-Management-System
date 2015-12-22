/*******************************************************
 File name: list_node.h
 
 Date: 2015.12.3
 
 Description: 提供用于创建链表数据结构的相关函数，包括创
    建链表、添加节点、搜索节点、删除链表或节点、特殊节点
    的返回

 History: 1、2015.12.5 修改部分代码 
 
********************************************************/


#ifndef _LIST_NODE_H_
#define _LIST_NODE_H_

#define SUCCESS 0
#define FAILURE (-1)

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

// 创建链表 
tListStruct * CreateList();

// 删除链表[，可选深入释放内层申请内存 ]
int DeleteList(tListStruct *pListStruct, 
    void DeepDelete(tListNode * pNode, void * args), void * args);

// 增加链表节点至链表尾部[，可选按条件插入节点] 
int AddListNode(tListStruct *pListStruct, void *pData,
                int Condition(tListNode * pNode, tListNode * pAddNode, void * args), void * args);

// 增加链表节点使之成为链表头部 
int AddListNodeToHead(tListStruct *pListStruct, void *pData);

// 删除链表中某一节点 
int DeleteListNode(tListStruct *pListStruct, tListNode *pNode);

// 按条件搜索节点 
tListNode * SearchListNode(tListStruct *pListStruct,
    int Condition(tListNode * pNode, void * args), void * args);
    
// 返回链表的头节点 
tListNode * GetListHead(tListStruct *pListStruct);

// 返回链表的尾节点 
tListNode * GetListTail(tListStruct *pListStruct);

// 返回当前节点的下一节点 
tListNode * GetListNext(tListNode *pNode);

// 返回当前节点的上一节点 
tListNode * GetListPrev(tListStruct * pList, tListNode *pNode);

#endif

