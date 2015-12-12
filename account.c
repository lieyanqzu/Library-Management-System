/*******************************************************
 File name: account.c 
 Date: 2015.12.10
 
 Description: 所有账户的信息，包括读者和管理员（每一个人
    的借书信息包括借书证号、姓名、班级、学号等。） 
    
 Dependency: list_node

 History: 
 
********************************************************/


#include <string.h>
#include <stdlib.h>

#include "account.h"

/*
// 账户信息
typedef struct {
    int             license;
    char            name[STR_LEN];
    char            classes[STR_LEN];
    AccountRank     rank;
} account_info;
*/

tListStruct * accountList = NULL;

// 获得账户链表 
tListStruct * GetAccountList()
{
    if (NULL == accountList) {
        accountList = CreateList();
    }
    
    return accountList;
}

// 建立账户信息原型
account_info * CreateAccountPrototype(int license_, char *name_, char *classes_, AccountRank rank_)
{
    account_info * pAcc = (account_info*)malloc(sizeof(account_info));

    pAcc->license = license_;
    strncpy(pAcc->name, name_, STR_LEN);
    strncpy(pAcc->classes, classes_, STR_LEN);
    pAcc->rank = rank_;

    return pAcc;
}

// 按账号搜索条件 
static int SearchAccountCondition(tListNode *pNode, void *arg)
{
    int * pLicense = (int*)arg;
    
    if (( (account_info*)(pNode->data) )->license == *pLicense) {
        return SUCCESS;
    }
    
    return FAILURE;	  
}
 
// 用于按账户号插入的条件
static int AddAccountCondition(tListNode * pNode, tListNode * pAddNode, void * arg)
{
    tListNode * pNodeNext = GetListNext(pNode);
    
    if (NULL == pNodeNext) {
        return SUCCESS;
    }
    
    account_info * accInfoPrev = (account_info*)(pNode->data);
    account_info * accInfoNext = (account_info*)(pNodeNext->data);
    account_info * accInfoCurr = (account_info*)(pAddNode->data);
    
    // 按账户号码排序加入链表 
    if (accInfoPrev->license <= accInfoCurr->license 
        && accInfoCurr->license < accInfoNext->license) {
            return SUCCESS;
        }
    return FAILURE;
}

// 按账号搜索账户节点 
static tListNode * SearchAccountByLicense(int license)
{
    tListStruct * pList = accountList;
    tListNode * pNode = SearchListNode(pList, SearchAccountCondition, &license);
    return pNode;
}

// 返回节点的账户号
static int GetLicenseByNode(tListNode * pNode)
{
    account_info * pAcc = (account_info*)(pNode->data);
    return pAcc->license;
}

// 将账户信息插入链表 
int AddToAccountList(account_info * pAcc)
{
    tListStruct * pAccList = GetAccountList();
    tListNode * pHeadNode = GetListHead(pAccList);
    if (NULL == pAccList) {
        return FAILURE;
    }

    if (NULL == GetListHead(pAccList) ||
            GetLicenseByNode(pHeadNode) > pAcc->license) {
        return AddListNodeToHead(pAccList, (void*)pAcc);
    }

    return AddListNode(pAccList, (void*)pAcc, AddAccountCondition, NULL);
}

// 注销一个账户 
int RemoveAccountByLicense(int license)
{
    tListNode * pNode = SearchAccountByLicense(license);

    if (DeleteListNode(accountList, pNode) == SUCCESS) {
        free(pNode->data);
        free(pNode);
        return SUCCESS;
    }
    else {
        return FAILURE;
    }
}

// 修改账户信息 
int ModifyAccountInfo(int license, void * arg, AccountFlag mFlag)
{
    tListNode * pNode = SearchAccountByLicense(license);
    account_info * pAccount = (account_info*)(pNode->data);
    
    char * pChar = NULL;
    AccountRank * pRank = NULL;
    
    switch (mFlag) {
    case NAME:
        pChar = (char*)arg;
        strncpy(pAccount->name, pChar, STR_LEN);
        break;
    case CLASSES:
        pChar = (char*)arg;
        strncpy(pAccount->classes, pChar, STR_LEN);
        break;
    case RANK:
        pRank = (AccountRank*)arg;
        pAccount->rank = *pRank;
    default:
        return FAILURE;
    }
    return SUCCESS;
}

// 获取账户信息 
void * GetAccountInfo(int license, AccountFlag gFlag)
{
    tListNode * pNode = SearchAccountByLicense(license);
    account_info * pAccount = (account_info*)(pNode->data);
    
    char * pChar = NULL;
    AccountRank * pRank = NULL;
    
    switch (gFlag) {
    case NAME:
        pChar = pAccount->name;
        return (void*)pChar;
    case CLASSES:
        pChar = pAccount->classes;
        return (void*)pChar;
    case RANK:
        pRank = &(pAccount->rank);
        return (void*)pRank;
    default:
        return NULL; 
    }
}
