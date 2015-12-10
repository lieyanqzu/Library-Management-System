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

// ����Setter/Getterѡ������ 
typedef enum {
    NAME = 0, 
    CLASSES = 1, 
    RANK = 2,  
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
    char            name[STR_LEN];
    char            classes[STR_LEN];
    AccountRank     rank;
} account_info;

// ����˻����� 
tListStruct * GetAccountList(); 

// ���˺��������� 
static int SearchAccountConditon(tListNode * pListNode,void * arg);

// ���ڰ��˻��Ų��������
static int AddAccountCondition(tListNode * pNode, tListNode * pAddNode, void * arg);

// ���˺������˻��ڵ� 
static tListNode * SearchAccountByLicense(int license);

// ���˻���Ϣ�������� 
int AddToAccountList(account_info * pAcc);

// ע��һ���˻� 
int RemoveAccountByLicense(int license);

// �޸��˻���Ϣ 
int ModifyAccountInfo(int license, void * arg, AccountFlag mFlag);

// ��ȡ�˻���Ϣ 
void * GetAccountInfo(int id, AccountFlag gFlag); 
 
#endif
