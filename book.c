#include "book.h"
#include <stdlib.h>
#include <string.h>

#define FLAG_POSITION 100000000

/*
typedef struct {
    int         total_number;
    int         current_number;
    int         lent_number;
} stock_info;

typedef struct {
    int         id;
    char*       title;
    char*       author;
    char*       press;
    time_t      public_time;
    double      price;
    BookType    type;
    BookStatus  status;
    stock_info* stock;
} book_info;

*/

// 要求把书籍、期刊、报刊分类管理，这样的话操作会更加灵活和方便，可以随时对其相关资料进行添加、删除、修改、查询等操作。

tListStruct * bookList = NULL;
tListStruct * periodicalsList = NULL;
tListStruct * newspaperList = NULL;

static int SearchBookConditon(tListNode * pListNode,void * arg)
{
    int * pId = (int*)arg;
    tListNode *pNode = (tListNode *)pListNode;
    
    if (( (book_info*)(pNode->data) )->id == *pId) {
        return SUCCESS;
    }
    
    return FAILURE;	       
}

static int SearchTitleConditon(tListNode * pListNode,void * arg)
{
    char * pTitle = (char*)arg;
    tListNode *pNode = (tListNode*)pListNode;
    
    if (strcmp( ((book_info*)(pNode->data))->title, pTitle ) == 0) {
        return SUCCESS;
    }
    
    return FAILURE;
}

tListNode * SearchBookById(int id)
{
    tListStruct * pList = NULL;
    switch(id / FLAG_POSITION) {
    case 1:
        pList = bookList;
        break;
    case 2:
        pList = periodicalsList;
        break;
    case 3:
        pList = newspaperList;
        break;
    default:
        return NULL;            
    }
    tListNode * pNode = SearchListNode(pList, SearchBookConditon, &id);
    return pNode;
}

static tListStruct * GetListByBookInfo(book_info * pBookInfo) {
    switch (pBookInfo->type) {
    case BOOK:
        return bookList;
    case PERIODICALS:
        return periodicalsList;
    case NEWSPAPER:
        return newspaperList;
    default:
        return NULL;
    }
}

static tListStruct * GetListByNode(tListNode * pNode) {
    book_info * pBookInfo = (book_info*)(pNode->data);
    return GetListByBookInfo(pBookInfo);
}

int AddToBooksList(book_info * pBookInfo)
{
    tListStruct * pList = GetListByBookInfo(pBookInfo);
    if (NULL == pBookInfo) {
        return FAILURE;
    }
    
    if (NULL == pList) {
        pList = CreateList();
    }
    
    tListNode * pNode = SearchListNode(pList, SearchTitleConditon, pBookInfo->title);
    
    if (AddListNode(pList, pBookInfo, NULL, NULL) == SUCCESS) {
        if (pNode != NULL) {
            stock_info *pStock = ( (book_info*)(pNode->data) )->stock;
            pBookInfo->stock = pStock;
            pStock->total_number++;
            pStock->current_number++;
        }
        else {
            stock_info *pStock = (stock_info*)malloc(sizeof(stock_info));
            pBookInfo->stock = pStock;
            pStock->total_number = 1;
            pStock->current_number = 1;
            pStock->lent_number = 0;
        }
    }
    return FAILURE;
}

int RemoveBookById(int id)
{
    tListNode * pNode = SearchBookById(id);
    stock_info *pStock = ( (book_info*)(pNode->data) )->stock;

    if (DeleteListNode(GetListByNode(pNode), pNode) == SUCCESS) {
        if (pStock->total_number == 1) {
            free(pStock);
        }
        else {
            pStock->total_number--;
            pStock->current_number--;
        }
        free(pNode->data);
        free(pNode);
        return SUCCESS;
    }
    else {
        return FAILURE;
    }
}

int ModifyBookInfo(int id, void * arg, ModifyFlag mFlag)
{
    tListNode * pNode = SearchBookById(id);
    book_info * pBook = (book_info*)(pNode->data);
    
    char * pChar = (char*)arg;
    time_t * pTime = (time_t*)arg;
    double * pDouble = (double*)arg;
    BookType * pType = (BookType*)arg;
    BookStatus * pStatus = (BookStatus*)arg;
    
    switch (mFlag) {
    case TITLE:
        strcpy(pBook->title, pChar);
        break;
    case AUTHOR:
        strcpy(pBook->author, pChar);
        break;
    case PRESS:
        strcpy(pBook->press, pChar);
        break;
    case PUBLIC_TIME:
        pBook->public_time = *pTime;
        break;
    case PRICE:
        pBook->price = *pDouble;
        break;
    case TYPE:
        pBook->type = *pType;
        break;
    case STATUS:
        pBook->status = *pStatus;
        break;
    default:
        return FAILURE;
    }
    
    return SUCCESS;
}
