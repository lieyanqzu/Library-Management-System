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

book_info * CreateBookPrototype(char *title_, char *author_, char *press_, 
    time_t time_, double price_, BookType type_, BookStatus status_)
{
    book_info * pBook = (book_info*)malloc(sizeof(book_info));
    
    if (NULL == pBook) {
        return NULL;
    }
    
    pBook->id = 0;
    strcpy(pBook->title, title_);
    strcpy(pBook->author, author_);
    strcpy(pBook->press, press_);
    pBook->public_time = time_;
    pBook->price = price_;
    pBook->type = type_;
    pBook->status = status_;
    pBook->stock = NULL;
    
    return pBook;
}

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

static BookType GetListFlag(tListStruct * pList)
{
    if (pList == bookList) {
        return BOOK;
    }
    else if (pList == periodicalsList) {
        return PERIODICALS;
    }
    else if (pList == newspaperList) {
        return NEWSPAPER;
    } 
    else {
        return 0;
    }
}

tListNode * SearchBookById(int id)
{
    tListStruct * pList = NULL;
    switch((BookType)(id / FLAG_POSITION)) {
    case BOOK:
        pList = bookList;
        break;
    case PERIODICALS:
        pList = periodicalsList;
        break;
    case NEWSPAPER:
        pList = newspaperList;
        break;
    default:
        return NULL;            
    }
    tListNode * pNode = SearchListNode(pList, SearchBookConditon, &id);
    return pNode;
}

static tListStruct * GetListByBookInfo(book_info * pBookInfo)
{
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

static tListStruct * GetListByNode(tListNode * pNode)
{
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
        tListNode * pTailNode = GetListTail(pList);
        if (pTailNode != NULL) {
            pBookInfo->id = ( (book_info*)(pTailNode->data) )->id + 1;
        }
        else {
            pBookInfo->id = 1 + FLAG_POSITION * (int)GetListFlag(pList);
        }
        
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
    
    char * pChar = NULL;
    time_t * pTime = NULL;
    double * pDouble = NULL;
    BookType * pType = NULL;
    BookStatus * pStatus = NULL;
    
    switch (mFlag) {
    case TITLE:
        pChar = (char*)arg; 
        strcpy(pBook->title, pChar);
        break;
    case AUTHOR:
        pChar = (char*)arg;
        strcpy(pBook->author, pChar);
        break;
    case PRESS:
        pChar = (char*)arg;
        strcpy(pBook->press, pChar);
        break;
    case PUBLIC_TIME:
        pTime = (time_t*)arg;
        pBook->public_time = *pTime;
        break;
    case PRICE:
        pDouble = (double*)arg;
        pBook->price = *pDouble;
        break;
    case TYPE:
        pType = (BookType*)arg;
        pBook->type = *pType;
        break;
    case STATUS:
        pStatus = (BookStatus*)arg;
        pBook->status = *pStatus;
        break;
    default:
        return FAILURE;
    }
    
    return SUCCESS;
}
