#include <string.h>
#include <stdio.h>

#include "account.h"
#include "file.h"

#include "operation.h"

#define PER_PAGE 8

void ChangePasswordToDefault(int license)
{
    tListNode *pNode = SearchAccountByLicense(license);
    char buf[PW_LEN];
    sprintf(buf, "%d", license);
    ModifyAccountInfo(license, (void*)buf, PASSWORD);
}

void CancelAccount(int license)
{
    RemoveAccountByLicense(license);
    WriteAccountFile();
}

void LossRegistration(int license)
{
    AccountRank rank;
    rank = *(AccountRank*)GetAccountInfo(license, RANK);
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
}

void ListNodeSplit(tListStruct *pList, tListNode **pNodeArray)
{
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
