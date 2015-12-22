/*******************************************************
 File name: account.h
 
 Date: 2015.12.10
 
 Description: �����˻�����Ϣ���������ߺ͹���Ա��ÿһ����
    �Ľ�����Ϣ��������֤�š��������༶��ѧ�ŵȡ��� 
    
 Dependency: list_node

 History: 
 
********************************************************/


#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "list_node.h"

#define STR_LEN 32
#define PW_LEN 17

// ����Setter/Getterѡ������ 
typedef enum {
    PASSWORD = 0,
    NAME = 1,
    CLASSES = 2,
    RANK = 3,
} AccountFlag;

// �û������ 
typedef enum {
    STUDENT = 0, 
    TEACHER = 1, 
    ADMIN = 2,  
    LOSS = 3, 
} AccountRank;

// �˻���Ϣ 
typedef struct {
    int             license;
    char            password[PW_LEN];
    char            name[STR_LEN];
    char            classes[STR_LEN];
    AccountRank     rank;
} account_info;

// ����˻����� 
tListStruct * GetAccountList();

// �����˻���Ϣԭ��
account_info * CreateAccountPrototype(int license_, char *name_, char *classes_, AccountRank rank_);

// ���˺��������� 
static int SearchAccountCondition(tListNode *pListNode, void *arg);

// ���ڰ��˻��Ų��������
static int AddAccountCondition(tListNode * pNode, tListNode * pAddNode, void * arg);

// ���˺������˻��ڵ� 
tListNode * SearchAccountByLicense(int license);

// ���ؽڵ���˻���
int GetLicenseByNode(tListNode * pNode);

// ���˻���Ϣ�������� 
int AddToAccountList(account_info * pAcc);

// ע��һ���˻� 
int RemoveAccountByLicense(int license);

// �޸��˻���Ϣ 
int ModifyAccountInfo(int license, void * arg, AccountFlag mFlag);

// ��ȡ�˻���Ϣ 
void * GetAccountInfo(int license, AccountFlag gFlag);
 
#endif

