#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#define MAX_STR 128

//每一个人的借书信息包括借书证号、姓名、班级、学号等。

typedef enum {
    STUDENT = 0, 
    TEACHER = 1, 
    LOSS = 2, 
} AccountRank;

typedef struct {
    int             license;
    char            name[MAX_STR];
    char            classes[MAX_STR];
    AccountRank     rank;
} account_info;

// 施工中... 

#endif
