/*******************************************************
 File name: list_node.h
 
 Date: 2015.12.3
 
 Description: �ṩ���ڴ����������ݽṹ����غ�����������
    ��������ӽڵ㡢�����ڵ㡢ɾ�������ڵ㡢����ڵ�
    �ķ���

 History: 1��2015.12.5 �޸Ĳ��ִ��� 
 
********************************************************/


#ifndef _LIST_NODE_H_
#define _LIST_NODE_H_

#define SUCCESS 0
#define FAILURE (-1)

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

// �������� 
tListStruct * CreateList();

// ɾ������[����ѡ�����ͷ��ڲ������ڴ� ]
int DeleteList(tListStruct *pListStruct, 
    void DeepDelete(tListNode * pNode, void * args), void * args);

// ��������ڵ�������β��[����ѡ����������ڵ�] 
int AddListNode(tListStruct *pListStruct, void *pData,
                int Condition(tListNode * pNode, tListNode * pAddNode, void * args), void * args);

// ��������ڵ�ʹ֮��Ϊ����ͷ�� 
int AddListNodeToHead(tListStruct *pListStruct, void *pData);

// ɾ��������ĳһ�ڵ� 
int DeleteListNode(tListStruct *pListStruct, tListNode *pNode);

// �����������ڵ� 
tListNode * SearchListNode(tListStruct *pListStruct,
    int Condition(tListNode * pNode, void * args), void * args);
    
// ���������ͷ�ڵ� 
tListNode * GetListHead(tListStruct *pListStruct);

// ���������β�ڵ� 
tListNode * GetListTail(tListStruct *pListStruct);

// ���ص�ǰ�ڵ����һ�ڵ� 
tListNode * GetListNext(tListNode *pNode);

// ���ص�ǰ�ڵ����һ�ڵ� 
tListNode * GetListPrev(tListStruct * pList, tListNode *pNode);

#endif

