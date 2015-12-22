/*******************************************************
 File name: unit_test.c
 
 Date: 2015.12.5
 
 Description: ��Ԫ���Դ��� 
 
 target: list_node, book, book_lent, account

 History: 2015.12.7 ���� book_lent test
    2015.12.12 ���� account test
 
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

// list_node���Դ��� 
// -----------------------------------------------------
    // ������������� 
    typedef struct simple {
        int data;
    } tSimple;
    
    // list_node���������������� 
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
        
        // ���� AddListNode
        for (i = 0; i < 4; i++) {
//            printf("%d  ", ( (tSimple*)(node->data) )->data);
            assert(( (tSimple*)(node->data) )->data == testArray[i]);
            node = node->next;
        }
        
        // ���� SearchListNode
        assert(SearchListNode(list, SearchSimpleCondition, (void *) &testArray[0]) == headNode);
        assert(SearchListNode(list, SearchSimpleCondition, (void *) &testArray[3]) == tailNode);
        
        // ���� DeleteListNode
        if (DeleteListNode(list, headNode) == SUCCESS) {
            tListNode * newHead = GetListHead(list);
            assert(( (tSimple*)(newHead->data) )->data == testArray[1]);
        }
        
        DeleteList(list, NULL, NULL);
    } 
// -----------------------------------------------------


// book���Դ��� 
// -----------------------------------------------------
    void testBook()
    {
        // ������������
        int         id;
        char        isbn[3][ISBN_LEN] = {"9787111135104", "9787115357618", "9787115369093", };
        char        title[3][MAX_STR] = {"���������Ĺ���ͽ���", "�������", "�ع� ���Ƽ��д�������", };
        char        author[3][MAX_STR] = {"����ɭ", "�Ƕ���������", "Martin Fowler"};
        char        press[3][MAX_STR] = {"��е��ҵ������", "�����ʵ������", "�����ʵ������", };
        time_t      public_time = time(NULL);
        double      price[3] = {45.0, 39.0, 69.0};

        int         dType;
        BookType    type;

        int i;
        for (i = 0; i < 3; i++) {
            dType = i+1;
            type = (BookType)dType;

            // ���� CreateBookPrototype
            book_info * pBook = CreateBookPrototype(isbn[i], title[i], author[i], press[i], public_time, price[i], type);

            // ���� AddToBooksList
            id = AddToBooksList(pBook);

            // ��������Getter/Setter
            assert(strcmp( (char*)GetBookInfo(id, TITLE), title[i]) == 0);
//            printf("%s\n", ((char*)GetBookInfo(id, TITLE)) );
            ModifyBookInfo(id, "��������֮��", TITLE);
            assert(strcmp( (char*)GetBookInfo(id, TITLE), "��������֮��") == 0);
//            printf("%s\n", ((char*)GetBookInfo(id, TITLE)) );
        }
    }
// -----------------------------------------------------


// book_lent���Դ��� 
// -----------------------------------------------------
    void testBookLent()
    {
        // ������������
        int id1 = 100000002;
        int id2 = 200000033;
        int license1 = 149074999;
        int license2 = 149074998;
        time_t borrow_time = time(NULL);

        tListStruct * pLentList = GetBookLentList();
        tListNode * pHeadLentNode = NULL;

        // ���� AddToBookLentList
        AddToBookLentList(CreateLentPrototype(id1, license1, borrow_time));
        SetLentExpireTime(id1, time(NULL)+2592000);
        AddToBookLentList(CreateLentPrototype(id2, license2, borrow_time));
        SetLentExpireTime(id2, time(NULL)+2592000);
        pHeadLentNode = GetListHead(pLentList);

        // ���� GetLentId
        assert(GetLentId(pHeadLentNode) == id1);

        // ���� GetLentBookInfo
        assert(*((int*)GetLentBookInfo(id2, LICENSE)) == license2);
    }
// -----------------------------------------------------


// account���Դ���
// -----------------------------------------------------
    void testAccount()
    {
        // ������������
        int license[3] = {149074999, 149074998, 10028};
        char name[3][STR_LEN] = {"����", "����", "����", };
        char classes[3][STR_LEN] = {"��149", "��148", "", };
        AccountRank rank[3] = {STUDENT, STUDENT, TEACHER, };

        tListStruct * pAccList = GetAccountList();

        int i;
        for (i = 0; i < 3; i++) {
            AddToAccountList(CreateAccountPrototype(license[i], name[i], classes[i], rank[i]));
        }

        // ���� AddToAccountList
        tListNode * pHeadAcc = GetListHead(pAccList);
        account_info * headAcc = (account_info*)(pHeadAcc->data);
        assert(headAcc->license == license[2]);

        tListNode * pNextAcc = GetListNext(pHeadAcc);
        account_info * nextAcc = (account_info*)(pNextAcc->data);
        assert(nextAcc->license == license[1]);

        // ���� Setter/Getter
        assert(strcmp((char*)GetAccountInfo(license[0], NAME), name[0]) == 0);
        char nameChange[STR_LEN] = "����";
        ModifyAccountInfo(license[0], (void*)nameChange, NAME);
        assert(strcmp((char*)GetAccountInfo(license[0], NAME), nameChange) == 0);
    }
// -----------------------------------------------------

