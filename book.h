#ifndef _BOOK_H_
#define _BOOK_H_

#include "list_node.h"
#include <time.h>

typedef enum {
    BOOK = 0, 
    PERIODICALS = 1, 
    NEWSPAPER = 2, 
} BookType;

typedef enum {
    IDLE = 0, 
    LENT = 1, 
    RESERVED = 2, 
    OFF_SHELF = 3, 
} BookStatus;

typedef enum {
    TITLE = 0, 
    AUTHOR = 1, 
    PRESS = 2, 
    PUBLIC_TIME = 3, 
    PRICE = 4, 
    TYPE = 5, 
    STATUS = 6, 
} ModifyFlag;

// ÿһ��ͼ��Ŀ����Ϣ������š����������ߡ������硢�������ڡ�������������������ǰ��������ѽ�������ȡ�

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

#endif
