/*******************************************************
 File name: book.c 
 
 Date: 2015.12.4
 
 Description: ͼ��Ŀ����Ϣ("ÿһ��ͼ��Ŀ����Ϣ������
    �š����������ߡ������硢�������ڡ�����������
    ��������ǰ��������ѽ�������ȡ�")
    
 Dependency: list_node

 History: 
 
********************************************************/


#include <stdlib.h>
#include <string.h>

#include "book.h"

#define FLAG_POSITION 100000000

/*
// ͼ������Ϣ 
typedef struct {
    int         total_number;
    int         current_number;
    int         lent_number;
} stock_info;

// ͼ����Ϣ 
typedef struct {
    int         id;
    char        isbn[MAX_STR]; 
    char        title[MAX_STR];
    char        author[MAX_STR];
    char        press[MAX_STR];
    time_t      public_time;
    double      price;
    BookType    type;
    BookStatus  status;
    stock_info* stock;
} book_info;
*/

// Ҫ����鼮���ڿ�������������������Ļ�������������ͷ��㣬������ʱ����������Ͻ�����ӡ�ɾ�����޸ġ���ѯ�Ȳ�����

tListStruct * bookList = NULL;
tListStruct * periodicalsList = NULL;
tListStruct * newspaperList = NULL;

// ����ͼ����Ϣ�ṹ 
book_info * CreateBookPrototype(char *isbn_, char *title_, char *author_, char *press_, 
    time_t time_, double price_, BookType type_)
{
    book_info * pBook = (book_info*)malloc(sizeof(book_info));
    
    if (NULL == pBook) {
        return NULL;
    }
    
    pBook->id = 0;
    strncpy(pBook->isbn, isbn_, MAX_STR-1);
    strncpy(pBook->title, title_, MAX_STR-1);
    strncpy(pBook->author, author_, MAX_STR-1);
    strncpy(pBook->press, press_, MAX_STR-1);
    pBook->public_time = time_;
    pBook->price = price_;
    pBook->type = type_;
    pBook->status = IDLE;
    pBook->stock = NULL;
    
    return pBook;
}

// ��ID���� 
static int SearchBookCondition(tListNode *pNode, void *arg)
{
    int * pId = (int*)arg;
    
    if (( (book_info*)(pNode->data) )->id == *pId) {
        return SUCCESS;
    }
    
    return FAILURE;	       
}

// ��ISBN���� 
static int SearchISBNCondition(tListNode *pNode, void *arg)
{
    char * pIsbn = (char*)arg;
    
    if (strcmp( ((book_info*)(pNode->data))->isbn, pIsbn ) == 0) {
        return SUCCESS;
    }
    
    return FAILURE;
}

// ��ȡ�����ʾ��ͼ������ 
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

// ���ڵ���Ϣ����������� 
static tListStruct * GetListByNode(tListNode * pNode)
{
    book_info * pBookInfo = (book_info*)(pNode->data);
    return GetListByType(pBookInfo->type);
}

// ��ID����ͼ��ڵ� 
static tListNode * SearchBookById(int id)
{
    tListStruct * pList = NULL;
    switch((BookType)(id / FLAG_POSITION)) { // ��ID����ͼ������ 
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
    tListNode * pNode = SearchListNode(pList, SearchBookCondition, &id);
    return pNode;
}

// ��������Ҫ������
tListStruct * GetListByType(BookType type)
{
    switch (type) {
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

// ��ͼ����Ϣ�ṹ�������� 
int AddToBooksList(book_info * pBookInfo)
{
    tListStruct *pList = GetListByType(pBookInfo->type);
    tListNode *pNode = NULL;
    tListNode *pTailNode = NULL;
    stock_info *pStock = NULL;

    if (NULL == pBookInfo) {
        return FAILURE;
    }
    
    if (NULL == pList) {
        switch (pBookInfo->type) {
        case BOOK:
            bookList = CreateList();
            break;
        case PERIODICALS:
            periodicalsList = CreateList();
            break;
        case NEWSPAPER:
            newspaperList = CreateList();
            break;
        default:
            break;
        }
    }
    pList = GetListByType(pBookInfo->type);
    
    // �������Ƿ����д��鼮 
    pNode = SearchListNode(pList, SearchISBNCondition, pBookInfo->isbn);
    pTailNode = GetListTail(pList);

    if (AddListNode(pList, pBookInfo, NULL, NULL) == SUCCESS) {
        if (NULL == pTailNode) {
            pBookInfo->id = 1 + FLAG_POSITION * (int)GetListFlag(pList); 
        }
        else {
            // ͼ��ID��λ����ʾͼ������ 
            pBookInfo->id = ( (book_info*)(pTailNode->data) )->id + 1;
        }
        
        // �޸�ͼ������Ϣ 
        if (pNode != NULL) {
            stock_info *pStock = ( (book_info*)(pNode->data) )->stock;
            pBookInfo->stock = pStock;
            pStock->total_number++;
            pStock->current_number++;
        }
        else {
            pStock = (stock_info*)malloc(sizeof(stock_info));
            pBookInfo->stock = pStock;
            pStock->total_number = 1;
            pStock->current_number = 1;
            pStock->lent_number = 0;
        }
        return pBookInfo->id;
    }
    return FAILURE;
}

// ɾ��ͼ�� 
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

// �޸�ͼ����Ϣ 
int ModifyBookInfo(int id, void * arg, InfoFlag mFlag)
{
    tListNode * pNode = SearchBookById(id);
    book_info * pBook = (book_info*)(pNode->data);
    
    char * pChar = NULL;
    time_t * pTime = NULL;
    double * pDouble = NULL;
    BookType * pType = NULL;
    BookStatus * pStatus = NULL;
    
    // ��InfoFlagȷ���޸��� 
    switch (mFlag) {
    case ISBN:
        pChar = (char*)arg;
        strncpy(pBook->isbn, pChar, MAX_STR-1);
        break;          
    case TITLE:
        pChar = (char*)arg; 
        strncpy(pBook->title, pChar, MAX_STR-1);
        break;
    case AUTHOR:
        pChar = (char*)arg;
        strncpy(pBook->author, pChar, MAX_STR-1);
        break;
    case PRESS:
        pChar = (char*)arg;
        strncpy(pBook->press, pChar, MAX_STR-1);
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

// ��ȡͼ����Ϣ 
void * GetBookInfo(int id, InfoFlag gFlag)
{
    tListNode * pNode = SearchBookById(id);
    book_info * pBook = (book_info*)(pNode->data);
    
    char * pChar = NULL;
    time_t * pTime = NULL;
    double * pDouble = NULL;
    BookStatus * pStatus = NULL;
    stock_info * pStock = NULL;
    
    // ��InfoFlagȷ����ȡ�� 
    switch (gFlag) {
    case ISBN:
        pChar = pBook->isbn;
        return (void*)pChar;
    case TITLE:
        pChar = pBook->title;
        return (void*)pChar;
    case AUTHOR:
        pChar = pBook->author;
        return (void*)pChar;
    case PRESS:
        pChar = pBook->press;
        return (void*)pChar;
    case PUBLIC_TIME:
        pTime = &(pBook->public_time);
        return (void*)pTime;
    case PRICE:
        pDouble = &(pBook->price);
        return (void*)pDouble;
    case STATUS:
        pStatus = &(pBook->status);
        return (void*)pStatus;
    case STOCK:
        pStock = pBook->stock;
        return (void*)pStock;
    default:
        return NULL;
    }
}

// ����ͼ��ڵ�ID 
int GetBookID(tListNode * pNode)
{
    book_info * pBook = (book_info*)(pNode->data);
    return pBook->id;
}

int DeleteBookListCondition(tListNode *pNode, void *arg)
{
    book_info* pBook = (book_info*)(pNode->data);
    stock_info* pStock = pBook->stock;

    free(pStock);
    free(pBook);
    return SUCCESS;
}
