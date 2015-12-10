/*******************************************************
 File name: account.h
 
 Date: 2015.12.10
 
 Description: 所有账户的信息，包括读者和管理员（每一个人
    的借书信息包括借书证号、姓名、班级、学号等。） 
    
 Dependency: list_node

 History: 
 
********************************************************/


#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "list_node.h"

#define STR_LEN 32

// 用于Setter/Getter选择属性 
typedef enum {
    NAME = 0, 
    CLASSES = 1, 
    RANK = 2,  
} AccountFlag;

// 用户的类别 
typedef enum {
    STUDENT = 0, 
    TEACHER = 1, 
    ADMIN = 2,  
    LOSS = 3, 
} AccountRank;

// 账户信息 
typedef struct {
    int             license;
    char            name[STR_LEN];
    char            classes[STR_LEN];
    AccountRank     rank;
} account_info;

// 获得账户链表 
tListStruct * GetAccountList(); 

// 按账号搜索条件 
static int SearchAccountConditon(tListNode * pListNode,void * arg);

// 用于按账户号插入的条件
static int AddAccountCondition(tListNode * pNode, tListNode * pAddNode, void * arg);

// 按账号搜索账户节点 
static tListNode * SearchAccountByLicense(int license);

// 将账户信息插入链表 
int AddToAccountList(account_info * pAcc);

// 注销一个账户 
int RemoveAccountByLicense(int license);

// 修改账户信息 
int ModifyAccountInfo(int license, void * arg, AccountFlag mFlag);

// 获取账户信息 
void * GetAccountInfo(int id, AccountFlag gFlag); 
 
#endif
