/*******************************************************
 File name: operation.h  
 
 Date: 2015.12.21
 
 Description: ������ͼ�����ϵͳ��Ϣ�Ĳ��� 
    
 Dependency: account book_lent file book setting 
    statistics

 History: 
 
********************************************************/


#ifndef _OPERATION_H_
#define _OPERATION_H_

#include <time.h>

#include "account.h"
#include "book_lent.h"
#include "file.h"
#include "book.h"
#include "setting.h"
#include "statistics.h"

// �����˳� 
int ProgramExit();

// ��ʱ��תΪ�ַ��� 
char *TimeToString(time_t time);

// ���û�����ָ�ΪĬ������ 
void ChangePasswordToDefault(int license);

// ע��һ���˻� 
void CancelAccount(int license);

// ��ʧ 
void LossRegistration(int license);

// �����б���ʾ��Ԥ���� 
void ListNodeSplit(tListStruct *pList, tListNode **pNodeArray);
int AccountNodeStepping(tListNode *pNode, int step);
int BookNodeStepping(tListNode *pNode, int step);
int LicenseLentStepping(tListNode *pNode, int step);

// ͨ���ؼ��������鼮���� 
tListStruct * GetSearchBookByKey(char *key);

// ���һ���û������鼮���б� 
tListStruct * GetLicenseLentList(int license);

// ɾ��һ���� 
void DeleteOneBook(int id);

// ���һ���� 
int LentBookToLicense(int id, int get_license);

// ���� 
double ReturnBook(int id);

// ���� 
int RenewBook(int id);

// �޸��û����� 
void ChangePassword(int license, char *pw);

// ���ͳ�����а� 
tListStruct * GetStatisticsSort();

#endif
