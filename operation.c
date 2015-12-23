/*******************************************************
 File name: operation.c  
 
 Date: 2015.12.21
 
 Description: ������ͼ�����ϵͳ��Ϣ�Ĳ��� 
    
 Dependency: account book_lent file book setting 
    statistics

 History: 
 
********************************************************/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "operation.h"

#define PER_PAGE 8 // ÿҳ�б���ʾ���� 
#define TIME_LEN 20 // ʱ���ַ������� 
#define TIME_DAY 86400 // ÿ�����ӵ�ʱ���� 
#define TIME_MONTH 2592000 // ÿ�����ӵ�ʱ���� 

// �����˳� 
int ProgramExit()
{
    exit(0);
}

// ��ʱ��תΪ�ַ��� 
char *TimeToString(time_t time)
{
    char *timebuf = (char*)malloc(sizeof(char)*TIME_LEN);
    struct tm *newtime; 
    time_t lt = time;
    newtime = localtime(&lt);
    // ��YYYY/MM/DD��ʾʱ�� 
    strftime(timebuf, 20, "%Y/%m/%d", newtime);
    return timebuf;
}

// ���û�����ָ�ΪĬ������ 
void ChangePasswordToDefault(int license)
{
    tListNode *pNode = SearchAccountByLicense(license);
    char buf[PW_LEN];
    sprintf(buf, "%d", license);
    // �����ΪĬ�ϵ����룬�����˺�һ�� 
    ModifyAccountInfo(license, (void*)buf, PASSWORD);
    WriteAccountFile();
}

// ע��һ���˻� 
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

// ��ʧ 
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

// �����б���ʾ��Ԥ���� 
void ListNodeSplit(tListStruct *pList, tListNode **pNodeArray)
{
    // ��ҳ����ʾ�����ָ�һ������ 
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
    // ����б���ĳ��λ���˻����˺� 
    int i;
    for (i = 0; i < step-1; i++) {
        pNode = GetListNext(pNode);
    }
    return GetLicenseByNode(pNode);
}

int BookNodeStepping(tListNode *pNode, int step)
{
    // ����б���ĳ��λ���鼮�ı�� 
    int i;
    for (i = 0; i < step-1; i++) {
        pNode = GetListNext(pNode);
    }
    return GetBookID(pNode);
}

int LicenseLentStepping(tListNode *pNode, int step)
{
    // ��ý����б���ĳ���鼮�ı�� 
    int i;
    for (i = 0; i < step-1; i++) {
        pNode = GetListNext(pNode);
    }
    return GetLentId(pNode);
}

// ͨ���ؼ��������鼮���� 
tListStruct * GetSearchBookByKey(char *key)
{
    tListStruct * searchList = CreateList();
    tListStruct * bookList = GetListByType(BOOK);
    tListStruct * periodicalsList = GetListByType(PERIODICALS);
    tListStruct * newspaperList = GetListByType(NEWSPAPER);
    tListNode *pNode = NULL;
    int id;
    
    // �ֱ������������� 
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

// ���һ���û������鼮���б� 
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

// ɾ��һ���� 
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
    
    // ���ɾ�������ڽ���У�ɾ�����������е� 
    if (status == LENT) {
        RemoveLentBook(id);
        WriteBookLentFile();
    }
    
    // ������е�һ����ɾ����ͬʱɾ��ͳ���б��е� 
    if ((num == 1) && (SearchStatisticsByISBN(isbn) != NULL)) {
        DeleteStatisticsNode(isbn);
        WriteStatistics();
    }
}

// ���һ���� 
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
    
    // �ж��Ƿ񳬳������������� 
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
    
    // �޸�ͳ������ 
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

// ���� 
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
    
    // �����������㷣�� 
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

// ���� 
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
    
    // ����Ƿ񳬳������������ 
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

// �޸��û����� 
void ChangePassword(int license, char *pw)
{
    ModifyAccountInfo(license, (void*)pw, PASSWORD);
    WriteAccountFile();
}

// ���ͳ�����а� 
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
