/*******************************************************
 File name: unit_test.c
 
 Date: 2015.12.5
 
 Description: 单元测试代码 
 
 target: list_node, book, book_lent 

 History: 2015.12.7 增加 book_lent
 
********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "unit_test.h"

#include "list_node.h" 
#include "book.h"
#include "book_lent.h"

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


// book测试代码 
// -----------------------------------------------------
    void testBook()
    {
        // 声明测试数据变量 
        int         id;
        char        isbn[MAX_STR]; 
        char        title[MAX_STR];
        char        author[MAX_STR];
        char        press[MAX_STR];
        time_t      public_time;
        double      price;
        
        int         dType;
        BookType    type;
        
        int i;
        for (i = 0; i < 3; i++) {
            scanf("%s", isbn);
            scanf("%s", title);
            scanf("%s", author);
            scanf("%s", press);
            public_time = time(NULL);
            scanf("%lf", &price);
            scanf("%d", &dType);
            type = (BookType)dType;
            
            // 测试 CreateBookPrototype 
            book_info * pBook = CreateBookPrototype(isbn, title, author, press, public_time, price, type);
            
            // 测试 AddToBooksList 
            id = AddToBooksList(pBook);
            
            // 测试属性Getter/Setter 
            assert(strcmp( (char*)GetBookInfo(id, TITLE), title) == 0);
            printf("%s\n", ((char*)GetBookInfo(id, TITLE)) );
            ModifyBookInfo(id, "6666", TITLE);
            assert(strcmp( (char*)GetBookInfo(id, TITLE), "6666") == 0);
            printf("%s\n", ((char*)GetBookInfo(id, TITLE)) );
        }
    }
// -----------------------------------------------------


// book_lent测试代码 
// -----------------------------------------------------
void testBookLent()
{
    // 声明测试数据变量     
    int id1 = 100000002;
    int id2 = 200000033;
    int license1 = 149074999;
    int license2 = 149074998;
    time_t borrow_time = time(NULL);

    tListStruct * pLentList = GetBookLentList();
    tListNode * pHeadLentNode = NULL;
    
    // 测试 AddToBookLentList 
    AddToBookLentList(CreateLentPrototype(id1, license1, borrow_time));
    SetLentExpireTime(id1, time(NULL)+2592000);
    AddToBookLentList(CreateLentPrototype(id2, license2, borrow_time));
    SetLentExpireTime(id2, time(NULL)+2592000);
    pHeadLentNode = GetListHead(pLentList);
    
    // 测试 GetLentId
    assert(GetLentId(pHeadLentNode) == id1);
    
    // 测试 GetLentBookInfo 
    assert(*((int*)GetLentBookInfo(id2, LICENSE)) == license2); 
} 
// -----------------------------------------------------
