/*******************************************************
 File name: book.h
 
 Date: 2015.12.4
 
 Description: 图书的库存信息("每一种图书的库存信息包括编
    号、书名、作者、出版社、出版日期、金额、类别、总入库
    数量、当前库存量、已借出本数等。")
    
 Dependency: list_node

 History: 
 
********************************************************/


#ifndef _BOOK_H_
#define _BOOK_H_

#include <time.h>

#include "list_node.h"

#define MAX_STR 64
#define ISBN_LEN 14

// 图书类型分类 
typedef enum {
    BOOK = 1, 
    PERIODICALS = 2, 
    NEWSPAPER = 3, 
} BookType;

// 图书状态 
typedef enum {
    IDLE = 0, 
    LENT = 1, 
    RESERVED = 2, 
    OFF_SHELF = 3, 
} BookStatus;

// 调用Setter/Getter方法时需要修改的内容项 
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

// 图书库存信息
typedef struct {
    int         total_number;
    int         current_number;
    int         lent_number;
} stock_info;

// 图书信息 
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

// 创建图书信息结构 
book_info * CreateBookPrototype(char *isbn, char *title_, char *author_, char *press_, 
    time_t time_, double price_, BookType type_);

// 按ID搜索 
static int SearchBookCondition(tListNode *pListNode, void *arg);

// 按ISBN搜索 
static int SearchISBNCondition(tListNode *pListNode, void *arg);

// 获取链表表示的图书类型 
static BookType GetListFlag(tListStruct * pList);

// 按节点信息获得所在链表 
static tListStruct * GetListByNode(tListNode * pNode);

// 按ID搜索图书节点 
static tListNode * SearchBookById(int id);

// 返回所需要的链表
tListStruct * GetListByType(BookType type); 

// 把图书信息结构加入链表 
int AddToBooksList(book_info * pBookInfo);

// 删除图书 
int RemoveBookById(int id);

// 修改图书信息 
int ModifyBookInfo(int id, void * arg, InfoFlag mFlag);

// 获取图书信息 
void * GetBookInfo(int id, InfoFlag gFlag);

// 返回图书节点ID 
int GetBookID(tListNode * pNode); 

#endif

