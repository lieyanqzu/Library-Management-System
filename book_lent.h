#ifndef _BOOK_LENT_H_
#define _BOOK_LENT_H_

#include <time.h>

#include "list_node.h"

// 每一本被借阅的书都包括如下信息：编号、书名、金额、借书证号、借书日期、到期日期、罚款金额等。
typedef struct {
    int     id;
    char*   license;
    time_t  borrow_time;
    time_t  expire_time;
    double  fine;
} book_lent_info;

// 施工中... 

#endif
