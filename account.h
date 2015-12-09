#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#define MAX_STR 128

//ÿһ���˵Ľ�����Ϣ��������֤�š��������༶��ѧ�ŵȡ�

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

// ʩ����... 

#endif
