/*******************************************************
 File name: book.h
 
 Date: 2015.12.4
 
 Description: ͼ��Ŀ����Ϣ("ÿһ��ͼ��Ŀ����Ϣ������
    �š����������ߡ������硢�������ڡ�����������
    ��������ǰ��������ѽ�������ȡ�")
    
 Dependency: list_node

 History: 2015.12.22 �޸Ĳ��ִ��� 
 
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
} BookStatus;

// ����Setter/Getter����ʱ��Ҫ�޸ĵ������� 
typedef enum {
    ISBN = 0, 
    TITLE = 1, 
    AUTHOR = 2, 
    PRESS = 3, 
    PRICE = 4, 
    TYPE = 5, 
    STATUS = 6, 
    STOCK = 7, 
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
    double      price;
    BookType    type;
    BookStatus  status;
    stock_info* stock;
} book_info;

// ����ͼ����Ϣ�ṹ 
book_info * CreateBookPrototype(char *isbn_, char *title_, char *author_, 
    char *press_, double price_, BookType type_);

// ��ȡ�����ʾ��ͼ������ 
static BookType GetListFlag(tListStruct * pList);

// ���ڵ���Ϣ����������� 
static tListStruct * GetListByNode(tListNode * pNode);

// ��ID����ͼ��ڵ� 
static int SearchBookCondition(tListNode *pNode, void *arg);
tListNode * SearchBookById(int id);

// ��ISBN����ͼ��ڵ� 
static int SearchISBNCondition(tListNode *pNode, void *arg);
tListNode * SearchBookByISBN(tListStruct *pList, char *isbn);

// ��������Ҫ������
tListStruct * GetListByType(BookType type);

// ��ͼ����Ϣ�ṹ�������� 
int AddToBooksList(book_info * pBookInfo);

// ɾ��ͼ�� 
int RemoveBookById(int id);

// �޸�/��ȡͼ����Ϣ 
int ModifyBookInfo(int id, void * arg, InfoFlag mFlag);
void * GetBookInfo(int id, InfoFlag gFlag);

// ����ͼ��ڵ�ID 
int GetBookID(tListNode * pNode);

// ���ɾ���ڵ� 
int DeleteBookListCondition(tListNode *pNode, void *arg); 
void DeleteBookList();

#endif

