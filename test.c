/*******************************************************
 File name: test.c
 
 Date: 2015.12.3
 
 Description: Ϊ��дģ����е�Ԫ���� 

 History: 1��2015.12.4 ��дlist_nodeģ����� 
 
********************************************************/


#include <assert.h>
#include <stdio.h>
#include "list_node.h"

// list_node���������������� 
static int SearchSimpleConditon(tListNode * pListNode,void * arg);
// list_nodeģ����Դ��� 
void test_list_node();

int main()
{
    test_list_node();
    
    return 0;
}

// ������������� 
typedef struct simple {
    int data;
} tSimple;

// list_node���������������� 
static int SearchSimpleConditon(tListNode * pListNode,void * arg)
{
    int * pData = (int*)arg;
    tListNode *pNode = (tListNode *)pListNode;
    
    if (( (tSimple*)(pNode->data) )->data == *pData) {
        return SUCCESS;
    }
    
    return FAILURE;	       
}

void test_list_node()
{
    tListStruct * list = CreateList();
    int i;
    
    // ׼���������� 
    int testArray[4] = {3, 4, 5, 6};
    tSimple testSimple[4];
    
    if (NULL == list) {
        printf("Create List Failed!\n");
        return;
    }
    
    for (i = 0; i < 4; i++) {
        testSimple[i].data = testArray[i];
    }
    
    for (i = 0; i < 4; i++) {
        AddListNode(list, (void*)&testSimple[i], NULL, NULL);
    }
    
    tListNode *node, *headNode, *tailNode;
    node = headNode = GetListHead(list);
    tailNode = GetListTail(list);
    
    // ����AddListNode������ 
    printf("list_node test: \n");
    for (i = 0; i < 4; i++) {
        printf("%d  ", ( (tSimple*)(node->data) )->data);
        assert(( (tSimple*)(node->data) )->data == testArray[i]);
        node = node->next;
    }
    
    // ����SearchListNode������ 
    assert(SearchListNode(list, SearchSimpleConditon, (void*)&testArray[0]) == headNode); 
    assert(SearchListNode(list, SearchSimpleConditon, (void*)&testArray[3]) == tailNode);
    
    DeleteList(list, NULL, NULL);
} 
