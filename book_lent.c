/*******************************************************
 File name: book_lent.c
 
 Date: 2015.12.7
 
 Description: �ѽ��ͼ�����Ϣ("ÿһ�������ĵ��鶼������
    ����Ϣ����š�������������֤�š��������ڡ�������
    �ڡ�������ȡ�")
    
 Dependency: list_node

 History: 
 
********************************************************/


#include <stdlib.h>

#include "book.h"
#include "book_lent.h"

/*
// �ѽ��ͼ����Ϣ 
typedef struct {
    int     id;
    int     license;
    time_t  borrow_time;
    time_t  expire_time;
    double  fine;
} book_lent_info;
*/

// �ѽ��ͼ������ 
tListStruct * bookLentList = NULL;

// ��ID�����ѽ��ͼ��
static int SearchLentBookConditon(tListNode * pListNode, void * arg)
{
    int * pId = (int*)arg;
    tListNode *pNode = (tListNode *)pListNode;
    
    if (( (book_lent_info*)(pNode->data) )->id == *pId) {
        return SUCCESS;
    }
    
    return FAILURE;	       
}

// ͨ��ID�õ�book_lent_info 
static book_lent_info * GetLentInfoById(int id)
{
    tListNode * pNode = SearchLentBookById(id);
    book_lent_info * pLent = (book_lent_info*)(pNode->data);
    
    return pLent;
}

// ����book_lent_info�ṹ 
book_lent_info * CreateLentPrototype(int id_, int license_, time_t borrow_time_)
{
    book_lent_info * pLentBook = (book_lent_info*)malloc(sizeof(book_lent_info));
    
    pLentBook->id = id_;
    pLentBook->license = license_;
    pLentBook->borrow_time = borrow_time_;
    pLentBook->expire_time = borrow_time_;
    pLentBook->fine = 0.0;
    
    return pLentBook;
}

// �����ѽ��ͼ������ 
tListStruct * GetBookLentList() 
{
    if (NULL == bookLentList) {
        bookLentList = CreateList();
    }
    
    return bookLentList;
}

// �����µ��ѽ������������ 
int AddToBookLentList(book_lent_info * pLentBook)
{
    tListStruct * pLentList = GetBookLentList();
    if (NULL == pLentList) {
        return FAILURE;
    }
    
    return AddListNode(pLentList, (void*)pLentBook, NULL, NULL);
}

// ͨ��ID�����ѽ��ͼ��ڵ� 
tListNode * SearchLentBookById(int id)
{
    return SearchListNode(bookLentList, SearchLentBookConditon, &id);
}

// ɾ��һ���ѽ��ͼ����Ϣ 
int RemoveLentBook(int id)
{
    tListNode * pLentNode = SearchLentBookById(id);
     
    if (DeleteListNode(bookLentList, pLentNode) == SUCCESS) {
        free(pLentNode->data);
        free(pLentNode);
        return SUCCESS;
    }
    
    return FAILURE;
}

// ���ؽڵ���ָ���ͼ��ID 
int GetLentId(tListNode * pNode)
{
    book_lent_info * pLent = (book_lent_info*)(pNode->data);
    return pLent->id;
}

// �޸�ͼ�����ʱ�� 
int SetLentExpireTime(int id, time_t expire_time_)
{
    book_lent_info * pLent = GetLentInfoById(id);
    
    pLent->expire_time = expire_time_;
    return SUCCESS;
}

// �޸�ͼ�鷣�� 
int SetLentFine(int id, double fine_)
{
    book_lent_info * pLent = GetLentInfoById(id);
    
    pLent->fine = fine_;
    return SUCCESS;
}

// �����ѽ����ͼ�����Ϣ�� 
void * GetLentBookInfo(int id, LentInfoFlag sFlag)
{
    book_lent_info * pLent = GetLentInfoById(id);
    
    // ��InfoFlag������Ҫ����Ϣ�� 
    switch (sFlag) {
    case LICENSE:
        return (void*) (&(pLent->license));
    case BORROW_TIME:
        return (void*) (&(pLent->borrow_time));
    case EXPIRE_TIME:
        return (void*) (&(pLent->expire_time));
    case FINE:
        return (void*) (&(pLent->fine));
    default:
        return NULL;
    } 
}

