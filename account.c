#include <string.h>
#include <stdlib.h>

#include "account.h"
#include "list_node.h"
/*
typedef enum {
    STUDENT = 0, 
    TEACHER = 1, 
    LOSS = 2, 
} AccountRank;

typedef struct {
    int             license;
    char            name[MAX_STR];
    char            classes[MAX_STR];
    AccountRank     rank;
} account_info;*/

tListStruct * accountList = NULL;

tListStruct * GetAccountList()
{
    if (NULL == accountList) {
        accountList = CreateList();
    }
    
    return accountList;
}

static AddAccountCondition(tListNode * pNode, tListNode * pAddNode, void * arg)
{
    tListNode * pNodeNext = GetListNext(pNode);
    
    if (NULL == pNodeNext) {
        return SUCCESS;
    }
    
    account_info * accInfoPrev = (account_info*)(pNode->data);
    account_info * accInfoNext = (account_info*)(pNodeNext->data);
    account_info * accInfoCurr = (account_info*)(pAddNode->data);
    
    if (accInfoPrev->license <= accInfoCurr->license 
        && accInfoCurr->license < accInfoNext->license) {
            return SUCCESS;
        }
    return FAILURE;
}

// Ê©¹¤ÖÐ... 

