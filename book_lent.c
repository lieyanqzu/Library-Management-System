/*******************************************************
 File name: book_lent.c
 
 Date: 2015.12.7
 
 Description: 已借出图书的信息("每一本被借阅的书都包括如
    下信息：编号、书名、金额、借书证号、借书日期、到期日
    期、罚款金额等。")
    
 Dependency: list_node

 History: 
 
********************************************************/


#include <stdlib.h>

#include "book.h"
#include "book_lent.h"

#define TIME_MONTH 2592000

/*
// 已借出图书信息 
typedef struct {
    int     id;
    int     license;
    time_t  borrow_time;
    time_t  expire_time;
    double  fine;
} book_lent_info;
*/

// 已借出图书链表 
tListStruct * bookLentList = NULL;

// 按ID搜索已借出图书
static int SearchLentBookCondition(tListNode *pNode, void *arg)
{
    int * pId = (int*)arg;
    
    if (( (book_lent_info*)(pNode->data) )->id == *pId) {
        return SUCCESS;
    }
    
    return FAILURE;	       
}

// 通过ID得到book_lent_info 
static book_lent_info * GetLentInfoById(int id)
{
    tListNode * pNode = SearchLentBookById(id);
    book_lent_info * pLent = (book_lent_info*)(pNode->data);
    
    return pLent;
}

// 返回book_lent_info结构 
book_lent_info * CreateLentPrototype(int id_, int license_, time_t borrow_time_)
{
    book_lent_info * pLentBook = (book_lent_info*)malloc(sizeof(book_lent_info));
    
    pLentBook->id = id_;
    pLentBook->license = license_;
    pLentBook->borrow_time = borrow_time_;
    pLentBook->expire_time = borrow_time_ + TIME_MONTH;
    
    return pLentBook;
}

// 返回已借出图书链表 
tListStruct * GetBookLentList() 
{
    if (NULL == bookLentList) {
        bookLentList = CreateList();
    }
    
    return bookLentList;
}

// 加入新的已借出数据至链表 
int AddToBookLentList(book_lent_info * pLentBook)
{
    tListStruct * pLentList = GetBookLentList();
    if (NULL == pLentList) {
        return FAILURE;
    }
    
    return AddListNode(pLentList, (void*)pLentBook, NULL, NULL);
}

// 通过ID搜索已借出图书节点 
tListNode * SearchLentBookById(int id)
{
    return SearchListNode(bookLentList, SearchLentBookCondition, &id);
}

// 删除一本已借出图书信息 
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

// 返回节点所指向的图书ID 
int GetLentId(tListNode * pNode)
{
    book_lent_info * pLent = (book_lent_info*)(pNode->data);
    return pLent->id;
}

// 修改图书过期时间 
int SetLentExpireTime(int id, time_t expire_time_)
{
    book_lent_info * pLent = GetLentInfoById(id);
    
    pLent->expire_time = expire_time_;
    return SUCCESS;
}

// 返回已借出的图书的信息项 
void * GetLentBookInfo(int id, LentInfoFlag sFlag)
{
    book_lent_info * pLent = GetLentInfoById(id);
    
    // 按InfoFlag返回需要的信息项 
    switch (sFlag) {
    case LICENSE:
        return (void*) (&(pLent->license));
    case BORROW_TIME:
        return (void*) (&(pLent->borrow_time));
    case EXPIRE_TIME:
        return (void*) (&(pLent->expire_time));
    default:
        return NULL;
    } 
}

int DeleteBookLentListCondition(tListNode *pNode, void *arg)
{
    book_lent_info *pLent = (book_lent_info*)(pNode->data);
    free(pLent);
    return SUCCESS;
}

// 深层删除节点 
void DeleteBookLentList()
{
    DeleteList(bookLentList, DeleteBookLentListCondition, NULL);
}

