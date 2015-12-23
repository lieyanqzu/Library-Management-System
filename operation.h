/*******************************************************
 File name: operation.h  
 
 Date: 2015.12.21
 
 Description: 对整体图书管理系统信息的操作 
    
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

// 程序退出 
int ProgramExit();

// 将时间转为字符串 
char *TimeToString(time_t time);

// 将用户密码恢复为默认密码 
void ChangePasswordToDefault(int license);

// 注销一个账户 
void CancelAccount(int license);

// 挂失 
void LossRegistration(int license);

// 用于列表显示的预操作 
void ListNodeSplit(tListStruct *pList, tListNode **pNodeArray);
int AccountNodeStepping(tListNode *pNode, int step);
int BookNodeStepping(tListNode *pNode, int step);
int LicenseLentStepping(tListNode *pNode, int step);

// 通过关键字搜索书籍链表 
tListStruct * GetSearchBookByKey(char *key);

// 获得一个用户借阅书籍的列表 
tListStruct * GetLicenseLentList(int license);

// 删除一本书 
void DeleteOneBook(int id);

// 借出一本书 
int LentBookToLicense(int id, int get_license);

// 还书 
double ReturnBook(int id);

// 续借 
int RenewBook(int id);

// 修改用户密码 
void ChangePassword(int license, char *pw);

// 获得统计排行榜 
tListStruct * GetStatisticsSort();

#endif
