/*******************************************************
 File name: operation.c  
 
 Date: 2015.12.21
 
 Description: 对整体图书管理系统信息的操作 
    
 Dependency: account book_lent file book setting 
    statistics

 History: 
 
********************************************************/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "operation.h"

#define PER_PAGE 8 // 每页列表显示数量 
#define TIME_LEN 20 // 时间字符串长度 
#define TIME_DAY 86400 // 每天增加的时间量 
#define TIME_MONTH 2592000 // 每月增加的时间量 

// 程序退出 
int ProgramExit()
{
    exit(0);
}

// 将时间转为字符串 
char *TimeToString(time_t time)
{
    char *timebuf = (char*)malloc(sizeof(char)*TIME_LEN);
    struct tm *newtime; 
    time_t lt = time;
    newtime = localtime(&lt);
    // 以YYYY/MM/DD显示时间 
    strftime(timebuf, 20, "%Y/%m/%d", newtime);
    return timebuf;
}

// 将用户密码恢复为默认密码 
void ChangePasswordToDefault(int license)
{
    tListNode *pNode = SearchAccountByLicense(license);
    char buf[PW_LEN];
    sprintf(buf, "%d", license);
    // 密码改为默认的密码，即和账号一样 
    ModifyAccountInfo(license, (void*)buf, PASSWORD);
    WriteAccountFile();
}

// 注销一个账户 
void CancelAccount(int license)
{
    AccountRank rank;
    rank = *(AccountRank*)GetAccountInfo(license, RANK);
    if (rank == ADMIN) {
        return;
    }
    RemoveAccountByLicense(license);
    WriteAccountFile();
}

// 挂失 
void LossRegistration(int license)
{
    AccountRank rank;
    rank = *(AccountRank*)GetAccountInfo(license, RANK);
    if (rank == ADMIN) {
        return;
    }
    if (rank != LOSS) {
        rank = LOSS;
    }
    else {
        if (strcmp((char*)GetAccountInfo(license, CLASSES), "") != 0) {
            rank = STUDENT;
        } else {
            rank = TEACHER;
        }
    }
    ModifyAccountInfo(license, (void*)&rank, RANK);
    WriteAccountFile();
}

// 用于列表显示的预操作 
void ListNodeSplit(tListStruct *pList, tListNode **pNodeArray)
{
    // 按页可显示数量分隔一个链表 
    int cnt = 0;
    int i = 0;
    tListNode *pHead = GetListHead(pList);
    pNodeArray[cnt++] = pHead;
    while (1) {
        for (i = 0; i < PER_PAGE; i++) {
            pHead = GetListNext(pHead);
            if (NULL == pHead) {
                return;
            }
        }
        pNodeArray[cnt++] = pHead;
    }
}

int AccountNodeStepping(tListNode *pNode, int step)
{
    // 获得列表中某个位置账户的账号 
    int i;
    for (i = 0; i < step-1; i++) {
        pNode = GetListNext(pNode);
    }
    return GetLicenseByNode(pNode);
}

int BookNodeStepping(tListNode *pNode, int step)
{
    // 获得列表中某个位置书籍的编号 
    int i;
    for (i = 0; i < step-1; i++) {
        pNode = GetListNext(pNode);
    }
    return GetBookID(pNode);
}

int LicenseLentStepping(tListNode *pNode, int step)
{
    // 获得借阅列表中某个书籍的编号 
    int i;
    for (i = 0; i < step-1; i++) {
        pNode = GetListNext(pNode);
    }
    return GetLentId(pNode);
}

// 通过关键字搜索书籍链表 
tListStruct * GetSearchBookByKey(char *key)
{
    tListStruct * searchList = CreateList();
    tListStruct * bookList = GetListByType(BOOK);
    tListStruct * periodicalsList = GetListByType(PERIODICALS);
    tListStruct * newspaperList = GetListByType(NEWSPAPER);
    tListNode *pNode = NULL;
    int id;
    
    // 分别搜索三个链表 
    pNode = GetListHead(bookList);
    while (pNode != NULL) {
        id = GetBookID(pNode);
        if (strstr((char*)GetBookInfo(id, TITLE), key) != NULL) {
            AddListNode(searchList, (void*)(pNode->data), NULL, NULL);
        }
        pNode = GetListNext(pNode);
    }
    
    pNode = GetListHead(periodicalsList);
    while (pNode != NULL) {
        id = GetBookID(pNode);
        if (strstr((char*)GetBookInfo(id, TITLE), key) != NULL) {
            AddListNode(searchList, (void*)(pNode->data), NULL, NULL);
        }
        pNode = GetListNext(pNode);
    }
    
    pNode = GetListHead(newspaperList);
    while (pNode != NULL) {
        id = GetBookID(pNode);
        if (strstr((char*)GetBookInfo(id, TITLE), key) != NULL) {
            AddListNode(searchList, (void*)(pNode->data), NULL, NULL);
        }
        pNode = GetListNext(pNode);
    }
    
    return searchList;
}

// 获得一个用户借阅书籍的列表 
tListStruct * GetLicenseLentList(int license)
{
    int get_license;
    tListStruct * licenseLentList = CreateList();
    tListStruct * bookLentList = GetBookLentList();
    tListNode *pNode = GetListHead(bookLentList);
    
    while (pNode != NULL) {
        get_license = *(int*)GetLentBookInfo(GetLentId(pNode), LICENSE);
        if (get_license == license) {
            AddListNode(licenseLentList, (void*)pNode->data, NULL, NULL);
        }
        pNode = GetListNext(pNode);
    }
    return licenseLentList;
}

// 删除一本书 
void DeleteOneBook(int id)
{
    int num;
    char isbn[ISBN_LEN];
    stock_info *pStock = NULL;
    BookStatus status;
    
    status = *(BookStatus*)GetBookInfo(id, STATUS);
    pStock = (stock_info*)GetBookInfo(id, STOCK);
    num = pStock->total_number;
    strncpy((char*)GetBookInfo(id, ISBN), isbn, ISBN_LEN-1);
    
    RemoveBookById(id);
    WriteBookFile();
    
    // 如果删除的书在借出中，删除借阅链表中的 
    if (status == LENT) {
        RemoveLentBook(id);
        WriteBookLentFile();
    }
    
    // 如果仅有的一本被删除，同时删除统计列表中的 
    if ((num == 1) && (SearchStatisticsByISBN(isbn) != NULL)) {
        DeleteStatisticsNode(isbn);
        WriteStatistics();
    }
}

// 借出一本书 
int LentBookToLicense(int id, int get_license)
{
    Setting *setting = GetSetting();
    tListStruct *pList = NULL;
    AccountRank rank;
    char isbn[ISBN_LEN];
    BookStatus status;
    tListNode *pNode = NULL;
    stock_info *pStock = NULL;
    tListNode *pLentNode;
    tListStruct * statisticsList = GetStatisticsList();
    
    pList = GetLicenseLentList(get_license);
    rank = *(AccountRank*)GetAccountInfo(get_license, RANK);
    
    // 判断是否超出借阅数量限制 
    switch (rank) {
    case LOSS:
        return FAILURE;
    case STUDENT:
        if (setting->student_borrow_number <= pList->length) {
            return FAILURE;
        }
        break;
    case TEACHER:
        if (setting->teacher_borrow_number <= pList->length) {
            return FAILURE;
        }
        break;
    }
    
    pLentNode = SearchBookById(id);
    pStock = ( (book_info*)(pLentNode->data) )->stock;
    pStock->current_number--;
    pStock->lent_number++;
    
    AddToBookLentList(CreateLentPrototype(id, get_license, time(NULL)));
    status = LENT;
    ModifyBookInfo(id, (void*)&status, STATUS);
    
    // 修改统计数据 
    strncpy(isbn, (char*)GetBookInfo(id, ISBN), ISBN_LEN-1);
    pNode = SearchStatisticsByISBN(isbn);
    
    if (NULL == pNode) {
        AddToStatisticsList(isbn);
    }
    else {
        AddOnceToStatistics(isbn);
    }
    
    WriteBookFile();
    WriteBookLentFile();
    WriteStatistics();
    return SUCCESS;
}

// 还书 
double ReturnBook(int id)
{
    double fine = 0.0;
    BookStatus status;
    stock_info *pStock = NULL;
    tListNode *pLentNode;
    tListNode *pNode = NULL;
    Setting *setting = GetSetting();
    time_t ex_time;

    pNode = SearchLentBookById(id);
    if (NULL == pNode) {
        return -1.0;
    }
    
    // 如果超期则计算罚金 
    ex_time = *(time_t*)GetLentBookInfo(id, EXPIRE_TIME);
    if (time(NULL) - ex_time > 0) {
        fine = ((time(NULL) - ex_time) / 86400) * setting->fine_per_day;
    }

    pLentNode = SearchBookById(id);
    pStock = ( (book_info*)(pLentNode->data) )->stock;
    pStock->current_number++;
    pStock->lent_number--;
    
    RemoveLentBook(id);
    status = IDLE;
    ModifyBookInfo(id, (void*)&status, STATUS);
    
    WriteBookFile();
    WriteBookLentFile();
    WriteStatistics();
    return fine;
}

// 续借 
int RenewBook(int id)
{
    int license;
    AccountRank rank;
    time_t br_time, ex_time;
    int current_times;
    tListNode *pNode = NULL;
    Setting *setting = GetSetting();
    
    pNode = SearchLentBookById(id);
    if (NULL == pNode) {
        return FAILURE;
    }
    
    license = *(int*)GetLentBookInfo(id, LICENSE);
    br_time = *(time_t*)GetLentBookInfo(id, BORROW_TIME);
    ex_time = *(time_t*)GetLentBookInfo(id, EXPIRE_TIME);
    
    // 检测是否超出续借次数限制 
    rank = *(AccountRank*)GetAccountInfo(license, RANK);
    current_times = (ex_time - br_time) / TIME_MONTH;
    switch (rank) {
    case STUDENT:
        if (setting->student_renew_times <= current_times-1) {
            return FAILURE;
        }
        break;
    case TEACHER:
        if (setting->teacher_renew_times <= current_times-1) {
            return FAILURE;
        }
        break;
    }
    ex_time += TIME_MONTH;
    SetLentExpireTime(id, ex_time);
    WriteBookLentFile();
    return SUCCESS;
}

// 修改用户密码 
void ChangePassword(int license, char *pw)
{
    ModifyAccountInfo(license, (void*)pw, PASSWORD);
    WriteAccountFile();
}

// 获得统计排行榜 
tListStruct * GetStatisticsSort()
{
    tListStruct * sortList = CreateList();
    tListStruct * statisticsList = GetStatisticsList();
    tListNode *pNode = GetListHead(statisticsList);

    while (pNode != NULL) {
        AddStaitsticsNode(sortList, pNode);
        pNode = GetListNext(pNode);
    }
    
    return sortList;
}
