/*******************************************************
 File name: unit_test.c
 
 Date: 2015.12.5
 
 Description: 单元测试代码 

 History: 
 
********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list_node.h" 
#include "unit_test.h"

// list_node测试代码 
// -----------------------------------------------------
    // 定义测试用数据 
    typedef struct simple {
        int data;
    } tSimple;
    
    // list_node测试用例搜索条件 
    static int SearchSimpleConditon(tListNode * pListNode,void * arg)
    {
        int * pData = (int*)arg;
        tListNode *pNode = (tListNode *)pListNode;
        
        if (( (tSimple*)(pNode->data) )->data == *pData) {
            return SUCCESS;
        }
        
        return FAILURE;	       
    }
    
    void testListNode()
    {
        tListStruct * list = CreateList();
        int i;
        
        // 准备测试用例 
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
        
        // 测试 AddListNode 
        printf("list_node test: \n");
        for (i = 0; i < 4; i++) {
            printf("%d  ", ( (tSimple*)(node->data) )->data);
            assert(( (tSimple*)(node->data) )->data == testArray[i]);
            node = node->next;
        }
        
        // 测试 SearchListNode
        assert(SearchListNode(list, SearchSimpleConditon, (void*)&testArray[0]) == headNode); 
        assert(SearchListNode(list, SearchSimpleConditon, (void*)&testArray[3]) == tailNode);
        
        // 测试 DeleteListNode
        if (DeleteListNode(list, headNode) == SUCCESS) {
            tListNode * newHead = GetListHead(list);
            assert(( (tSimple*)(newHead->data) )->data == testArray[1]);
        }
        
        DeleteList(list, NULL, NULL);
    } 
// -----------------------------------------------------
