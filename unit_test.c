/*******************************************************
 File name: unit_test.c
 
 Date: 2015.12.5
 
 Description: 单元测试代码 
 
 target: list_node, book, book_lent, account

 History: 2015.12.7 增加 book_lent test
    2015.12.12 增加 account test
 
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
#include "account.h"

// list_node测试代码 
// -----------------------------------------------------
    // 定义测试用数据 
    typedef struct simple {
        int data;
    } tSimple;
    
    // list_node测试用例搜索条件 
    static int SearchSimpleCondition(tListNode *pNode, void *arg)
    {
        int * pData = (int*)arg;
        
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
        for (i = 0; i < 4; i++) {
//            printf("%d  ", ( (tSimple*)(node->data) )->data);
            assert(( (tSimple*)(node->data) )->data == testArray[i]);
            node = node->next;
        }
        
        // 测试 SearchListNode
        assert(SearchListNode(list, SearchSimpleCondition, (void *) &testArray[0]) == headNode);
        assert(SearchListNode(list, SearchSimpleCondition, (void *) &testArray[3]) == tailNode);
        
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
        // 声明测试数据
        int         id;
        char        isbn[3][ISBN_LEN] = {"9787111135104", "9787115357618", "9787115369093", };
        char        title[3][MAX_STR] = {"计算机程序的构造和解释", "编程珠玑", "重构 改善既有代码的设计", };
        char        author[3][MAX_STR] = {"艾伯森", "乔恩·本特利", "Martin Fowler"};
        char        press[3][MAX_STR] = {"机械工业出版社", "人民邮电出版社", "人民邮电出版社", };
        time_t      public_time = time(NULL);
        double      price[3] = {45.0, 39.0, 69.0};

        int         dType;
        BookType    type;

        int i;
        for (i = 0; i < 3; i++) {
            dType = i+1;
            type = (BookType)dType;

            // 测试 CreateBookPrototype
            book_info * pBook = CreateBookPrototype(isbn[i], title[i], author[i], press[i], public_time, price[i], type);

            // 测试 AddToBooksList
            id = AddToBooksList(pBook);

            // 测试属性Getter/Setter
            assert(strcmp( (char*)GetBookInfo(id, TITLE), title[i]) == 0);
//            printf("%s\n", ((char*)GetBookInfo(id, TITLE)) );
            ModifyBookInfo(id, "代码整洁之道", TITLE);
            assert(strcmp( (char*)GetBookInfo(id, TITLE), "代码整洁之道") == 0);
//            printf("%s\n", ((char*)GetBookInfo(id, TITLE)) );
        }
    }
// -----------------------------------------------------


// book_lent测试代码 
// -----------------------------------------------------
    void testBookLent()
    {
        // 声明测试数据
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


// account测试代码
// -----------------------------------------------------
    void testAccount()
    {
        // 声明测试数据
        int license[3] = {149074999, 149074998, 10028};
        char name[3][STR_LEN] = {"张三", "李四", "王五", };
        char classes[3][STR_LEN] = {"网149", "网148", "", };
        AccountRank rank[3] = {STUDENT, STUDENT, TEACHER, };

        tListStruct * pAccList = GetAccountList();

        int i;
        for (i = 0; i < 3; i++) {
            AddToAccountList(CreateAccountPrototype(license[i], name[i], classes[i], rank[i]));
        }

        // 测试 AddToAccountList
        tListNode * pHeadAcc = GetListHead(pAccList);
        account_info * headAcc = (account_info*)(pHeadAcc->data);
        assert(headAcc->license == license[2]);

        tListNode * pNextAcc = GetListNext(pHeadAcc);
        account_info * nextAcc = (account_info*)(pNextAcc->data);
        assert(nextAcc->license == license[1]);

        // 测试 Setter/Getter
        assert(strcmp((char*)GetAccountInfo(license[0], NAME), name[0]) == 0);
        char nameChange[STR_LEN] = "赵六";
        ModifyAccountInfo(license[0], (void*)nameChange, NAME);
        assert(strcmp((char*)GetAccountInfo(license[0], NAME), nameChange) == 0);
    }
// -----------------------------------------------------
