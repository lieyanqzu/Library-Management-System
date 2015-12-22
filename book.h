/*******************************************************
 File name: book.h
 
 Date: 2015.12.4
 
 Description: ͼ��Ŀ����Ϣ("ÿһ��ͼ��Ŀ����Ϣ������
    �š����������ߡ������硢�������ڡ�����������
    ��������ǰ��������ѽ�������ȡ�")
    
 Dependency: list_node

 History: 
 
********************************************************/


#ifndef _BOOK_H_
#define _BOOK_H_

#include <time.h>

#include "list_node.h"

#define MAX_STR 64
#define ISBN_LEN 14

// ͼ�����ͷ��� 
typedef enum {
    BOOK = 1, 
    PERIODICALS = 2, 
    NEWSPAPER = 3, 
} BookType;

// ͼ��״̬ 
typedef enum {
    IDLE = 0, 
    LENT = 1, 
    RESERVED = 2, 
    OFF_SHELF = 3, 
} BookStatus;

// ����Setter/Getter����ʱ��Ҫ�޸ĵ������� 
typedef enum {
    ISBN = 0, 
    TITLE = 1, 
    AUTHOR = 2, 
    PRESS = 3, 
    PUBLIC_TIME = 4, 
    PRICE = 5, 
    TYPE = 6, 
    STATUS = 7, 
    STOCK = 8, 
} InfoFlag;

// ͼ������Ϣ
typedef struct {
    int         total_number;
    int         current_number;
    int         lent_number;
} stock_info;

// ͼ����Ϣ 
typedef struct {
    int         id;
    char        isbn[ISBN_LEN]; 
    char        title[MAX_STR];
    char        author[MAX_STR];
    char        press[MAX_STR];
    time_t      public_time;
    double      price;
    BookType    type;
    BookStatus  status;
    stock_info* stock;
} book_info;

// ����ͼ����Ϣ�ṹ 
book_info * CreateBookPrototype(char *isbn, char *title_, char *author_, char *press_, 
    time_t time_, double price_, BookType type_);

// ��ID���� 
static int SearchBookCondition(tListNode *pListNode, void *arg);

// ��ISBN���� 
static int SearchISBNCondition(tListNode *pListNode, void *arg);

// ��ȡ�����ʾ��ͼ������ 
static BookType GetListFlag(tListStruct * pList);

// ���ڵ���Ϣ����������� 
static tListStruct * GetListByNode(tListNode * pNode);

// ��ID����ͼ��ڵ� 
static tListNode * SearchBookById(int id);

// ��������Ҫ������
tListStruct * GetListByType(BookType type); 

// ��ͼ����Ϣ�ṹ�������� 
int AddToBooksList(book_info * pBookInfo);

// ɾ��ͼ�� 
int RemoveBookById(int id);

// �޸�ͼ����Ϣ 
int ModifyBookInfo(int id, void * arg, InfoFlag mFlag);

// ��ȡͼ����Ϣ 
void * GetBookInfo(int id, InfoFlag gFlag);

// ����ͼ��ڵ�ID 
int GetBookID(tListNode * pNode); 

#endif

