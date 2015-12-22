#include <stdio.h>
#include <stdlib.h>

#include "book.h"
#include "book_lent.h"
#include "account.h"
#include "setting.h"

#include "file.h"

void WriteBookFile()
{
    tListStruct *pList = NULL;
    tListNode *pNode = NULL;
    book_info *pBook = NULL;

    FILE *fp = fopen("book.dat", "w");
    pList = GetListByType(BOOK);
    fprintf(fp, "%d ", pList->length);
    pNode = GetListHead(pList);
    while(pNode != NULL) {
        pBook = (book_info*)(pNode->data);
        fwrite(pBook, sizeof(book_info), 1, fp);
        fwrite(pBook->stock, sizeof(stock_info), 1, fp);
        pNode = GetListNext(pNode);
    }

    pList = GetListByType(PERIODICALS);
    fprintf(fp, "%d ", pList->length);
    pNode = GetListHead(pList);
    while(pNode != NULL) {
        pBook = (book_info*)(pNode->data);
        fwrite(pBook, sizeof(book_info), 1, fp);
        fwrite(pBook->stock, sizeof(stock_info), 1, fp);
        pNode = GetListNext(pNode);
    }

    pList = GetListByType(NEWSPAPER);
    fprintf(fp, "%d ", pList->length);
    pNode = GetListHead(pList);
    while(pNode != NULL) {
        pBook = (book_info*)(pNode->data);
        fwrite(pBook, sizeof(book_info), 1, fp);
        fwrite(pBook->stock, sizeof(stock_info), 1, fp);
        pNode = GetListNext(pNode);
    }
    fclose(fp);
}


void InitializeBook()
{
    tListStruct *pList = NULL;
    book_info *pBook = NULL;
    stock_info *pStock = NULL;
    int length = 0;
    int i;

    FILE *fp = fopen("book.dat", "r");
    if (NULL == fp) {
        return;
    }
    else {
        pList = GetListByType(BOOK);
        fscanf(fp, "%d ", &length);
        for (i = 0; i < length; i++) {
            pBook = (book_info*)malloc(sizeof(book_info));
            fread(pBook, sizeof(book_info), 1, fp);
            pStock = (stock_info*)malloc(sizeof(stock_info));
            fread(pStock, sizeof(stock_info), 1, fp);
            pBook->stock = pStock;
            AddListNode(pList, (void*)pBook, NULL, NULL);
        }

        pList = GetListByType(PERIODICALS);
        fscanf(fp, "%d ", &length);
        for (i = 0; i < length; i++) {
            pBook = (book_info*)malloc(sizeof(book_info));
            fread(pBook, sizeof(book_info), 1, fp);
            pStock = (stock_info*)malloc(sizeof(stock_info));
            fread(pStock, sizeof(stock_info), 1, fp);
            pBook->stock = pStock;
            AddListNode(pList, (void*)pBook, NULL, NULL);
        }

        pList = GetListByType(NEWSPAPER);
        fscanf(fp, "%d ", &length);
        for (i = 0; i < length; i++) {
            pBook = (book_info*)malloc(sizeof(book_info));
            fread(pBook, sizeof(book_info), 1, fp);
            pStock = (stock_info*)malloc(sizeof(stock_info));
            fread(pStock, sizeof(stock_info), 1, fp);
            pBook->stock = pStock;
            AddListNode(pList, (void*)pBook, NULL, NULL);
        }
    }
    fclose(fp);
}

void WriteBookLentFile()
{
    tListStruct *pList = GetBookLentList();
    tListNode *pNode;
    book_lent_info *pLentBook;

    FILE *fp = fopen("booklent.dat", "w");
    fprintf(fp, "%d ", pList->length);
    pNode = GetListHead(pList);
    while(pNode != NULL) {
        pLentBook = (book_lent_info*)(pNode->data);
        fwrite(pLentBook, sizeof(book_lent_info), 1, fp);
        pNode = GetListNext(pNode);
    }
    fclose(fp);
}

void InitializeBookLent()
{
    tListStruct *pList = GetBookLentList();
    book_lent_info *pLentBook;
    int length = 0;
    int i;

    FILE *fp = fopen("booklent.dat", "r");
    if (NULL == fp) {
        return;
    }
    else {
        fscanf(fp, "%d ", &length);
        for (i = 0; i < length; i++) {
            pLentBook = (book_lent_info*)malloc(sizeof(book_info));
            fread(pLentBook, sizeof(book_lent_info), 1, fp);
            AddListNode(pList, (void*)pLentBook, NULL, NULL);
        }
    }
    fclose(fp);
}

void WriteAccountFile()
{
    tListStruct *pList = GetAccountList();
    tListNode *pNode;
    account_info *pAcc;

    FILE *fp = fopen("account.dat", "w");
    fprintf(fp, "%d ", pList->length);
    pNode = GetListHead(pList);
    while(pNode != NULL) {
        pAcc = (account_info*)(pNode->data);
        fwrite(pAcc, sizeof(account_info), 1, fp);
        pNode = GetListNext(pNode);
    }
    fclose(fp);
}

void InitializeAccount()
{
    tListStruct *pList = GetAccountList();
    account_info *pAcc;
    int length = 0;
    int i;

    FILE *fp = fopen("account.dat", "r");
    if (NULL == fp) {
        AddToAccountList(CreateAccountPrototype(10000, "Admin", "Admin", ADMIN));
        WriteAccountFile();
    }
    else {
        fscanf(fp, "%d ", &length);
        for (i = 0; i < length; i++) {
            pAcc = (account_info*)malloc(sizeof(account_info));
            fread(pAcc, sizeof(account_info), 1, fp);
            AddListNode(pList, (void*)pAcc, NULL, NULL);
        }
    }
    fclose(fp);
}

void WriteSetting()
{
    Setting * set = GetSetting();
    FILE *fp = fopen("setting.dat", "w");
    fwrite(set, sizeof(Setting), 1, fp);
    fclose(fp);
}

void InitializeSetting()
{
    Setting * set = GetSetting();
    FILE *fp = fopen("setting.dat", "r");
    if (NULL == fp) {
        set->teacher_borrow_number = 10;
        set->student_borrow_number = 7;
        set->teacher_renew_times = 2;
        set->student_renew_times = 1;
        set->fine_per_day = 0.1;
        WriteSetting();
    }
    else {
        fread(set, sizeof(Setting), 1, fp);
    }
    fclose(fp);
}
