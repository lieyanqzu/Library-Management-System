/*******************************************************
 File name: account.c 
 
 Date: 2015.12.10
 
 Description: �����˻�����Ϣ���������ߺ͹���Ա��ÿһ����
    �Ľ�����Ϣ��������֤�š��������༶��ѧ�ŵȡ��� 
    
 Dependency: list_node

 History: 
 
********************************************************/


#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "account.h"

/*
// �˻���Ϣ
typedef struct {
    int             license;
    char            name[STR_LEN];
    char            classes[STR_LEN];
    AccountRank     rank;
} account_info;
*/

tListStruct * accountList = NULL;

// ����˻����� 
tListStruct * GetAccountList()
{
    if (NULL == accountList) {
        accountList = CreateList();
    }
    
    return accountList;
}

// �����˻���Ϣԭ��
account_info * CreateAccountPrototype(int license_, char *name_, char *classes_, AccountRank rank_)
{
    account_info * pAcc = (account_info*)malloc(sizeof(account_info));
    char buf[PW_LEN];
    sprintf(buf, "%d", license_);

    pAcc->license = license_;
    strncpy(pAcc->password, buf, PW_LEN-1);
    strncpy(pAcc->name, name_, STR_LEN-1);
    strncpy(pAcc->classes, classes_, STR_LEN-1);
    pAcc->rank = rank_;

    return pAcc;
}

// ���˺��������� 
static int SearchAccountCondition(tListNode *pNode, void *arg)
{
    int * pLicense = (int*)arg;
    
    if (( (account_info*)(pNode->data) )->license == *pLicense) {
        return SUCCESS;
    }
    
    return FAILURE;	  
}
 
// ���ڰ��˻��Ų��������
static int AddAccountCondition(tListNode * pNode, tListNode * pAddNode, void * arg)
{
    tListNode * pNodeNext = GetListNext(pNode);
    account_info * accInfoPrev = NULL;
    account_info * accInfoNext = NULL;
    account_info * accInfoCurr = NULL;
    
    if (NULL == pNodeNext) {
        return SUCCESS;
    }
    
    accInfoPrev = (account_info*)(pNode->data);
    accInfoNext = (account_info*)(pNodeNext->data);
    accInfoCurr = (account_info*)(pAddNode->data);
    
    // ���˻���������������� 
    if (accInfoPrev->license <= accInfoCurr->license 
        && accInfoCurr->license < accInfoNext->license) {
            return SUCCESS;
        }
    return FAILURE;
}

// ���˺������˻��ڵ� 
tListNode * SearchAccountByLicense(int license)
{
    tListStruct * pList = accountList;
    tListNode * pNode = SearchListNode(pList, SearchAccountCondition, &license);
    return pNode;
}

// ���ؽڵ���˻���
int GetLicenseByNode(tListNode * pNode)
{
    account_info * pAcc = (account_info*)(pNode->data);
    return pAcc->license;
}

// ���˻���Ϣ�������� 
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

// ע��һ���˻� 
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

// �޸��˻���Ϣ 
int ModifyAccountInfo(int license, void * arg, AccountFlag mFlag)
{
    tListNode * pNode = SearchAccountByLicense(license);
    account_info * pAccount = (account_info*)(pNode->data);

    char * pChar = NULL;
    AccountRank * pRank = NULL;
    
    switch (mFlag) {
    case PASSWORD:
        pChar = (char*)arg;
        strncpy(pAccount->password, pChar, PW_LEN-1);
        break;
    case NAME:
        pChar = (char*)arg;
        strncpy(pAccount->name, pChar, STR_LEN-1);
        break;
    case CLASSES:
        pChar = (char*)arg;
        strncpy(pAccount->classes, pChar, STR_LEN-1);
        break;
    case RANK:
        pRank = (AccountRank*)arg;
        pAccount->rank = *pRank;
    default:
        return FAILURE;
    }
    return SUCCESS;
}

// ��ȡ�˻���Ϣ 
void * GetAccountInfo(int license, AccountFlag gFlag)
{
    tListNode * pNode = SearchAccountByLicense(license);
    account_info * pAccount = (account_info*)(pNode->data);

    char * pChar = NULL;
    AccountRank * pRank = NULL;
    
    switch (gFlag) {
    case PASSWORD:
        pChar = pAccount->password;
        return (void*)pChar;
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

int DeleteAccountListCondition(tListNode *pNode, void *arg)
{
    account_info* pAcc = (account_info*)(pNode->data);
    free(pAcc);
    return SUCCESS;
}

// ���ɾ���ڵ�
void DeleteAccountList()
{
    DeleteList(accountList, DeleteAccountListCondition, NULL);
}
