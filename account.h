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
#define PW_LEN 17

// 用于Setter/Getter选择属性 
typedef enum {
    PASSWORD = 0,
    NAME = 1,
    CLASSES = 2,
    RANK = 3,
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
    char            password[PW_LEN];
    char            name[STR_LEN];
    char            classes[STR_LEN];
    AccountRank     rank;
} account_info;

// 获得账户链表 
tListStruct * GetAccountList();

// 建立账户信息原型
account_info * CreateAccountPrototype(int license_, char *name_, char *classes_, AccountRank rank_);

// 按账号搜索账户节点 
static int SearchAccountCondition(tListNode *pNode, void *arg);
tListNode * SearchAccountByLicense(int license);

// 用于按账号插入的条件
static int AddAccountCondition(tListNode * pNode, tListNode * pAddNode, void * arg);

// 返回节点的账户号
int GetLicenseByNode(tListNode * pNode);

// 将账户信息插入链表 
int AddToAccountList(account_info * pAcc);

// 注销一个账户 
int RemoveAccountByLicense(int license);

// 修改/获取账户信息 
int ModifyAccountInfo(int license, void * arg, AccountFlag mFlag);
void * GetAccountInfo(int license, AccountFlag gFlag);

// 深层删除节点 
int DeleteAccountListCondition(tListNode *pNode, void *arg); 
void DeleteAccountList();
 
#endif

