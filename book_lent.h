#ifndef _BOOK_LENT_H_
#define _BOOK_LENT_H_

#include <time.h>

#include "list_node.h"

// ÿһ�������ĵ��鶼����������Ϣ����š�������������֤�š��������ڡ��������ڡ�������ȡ�
typedef struct {
    int     id;
    char*   license;
    time_t  borrow_time;
    time_t  expire_time;
    double  fine;
} book_lent_info;

// ʩ����... 

#endif
