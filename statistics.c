/*******************************************************
 File name: statistics.c
 
 Date: 2015.12.21 
 
 Description: 统计借阅次数 
    
 Dependency: 

 History: 
 
********************************************************/


#include <stdlib.h>
#include <string.h>

#include "book.h"
#include "statistics.h"

tListStruct * statisticsList = NULL;

// 返回统计链表 
tListStruct * GetStatisticsList()
{
    if (NULL == statisticsList) {
        statisticsList = CreateList();
    }
    
    return statisticsList;
}

// 加入数据到统计链表 
int AddToStatisticsList(char *isbn)
{
    statistics_info *pStat = (statistics_info*)malloc(sizeof(statistics_info));
    tListStruct * pStatList = GetStatisticsList();
    
    strncpy(pStat->isbn, isbn, ISBN_LEN-1);
    pStat->lent_times = 1;
    
    if (NULL == pStatList) {
        return FAILURE;
    }
    
    return AddListNode(pStatList, (void*)pStat, NULL, NULL);
}

static int SearchStatisticsCondition(tListNode *pNode, void *arg)
{
    char * pISBN = (char*)arg;
    
    if (strcmp( ((statistics_info*)(pNode->data))->isbn, pISBN ) == 0) {
        return SUCCESS;
    }
    
    return FAILURE;	 
}

// 通过ISBN搜索统计节点 
tListNode * SearchStatisticsByISBN(char *isbn)
{
    return SearchListNode(statisticsList, SearchStatisticsCondition, isbn);
}

// 增加一次统计次数 
void AddOnceToStatistics(char *isbn)
{
    tListNode *pNode = SearchStatisticsByISBN(isbn);
    ( (statistics_info*)(pNode->data) )->lent_times++;
}

// 删除统计节点 
int DeleteStatisticsNode(char *isbn)
{
    tListNode * pNode = SearchStatisticsByISBN(isbn);

    if (DeleteListNode(statisticsList, pNode) == SUCCESS) {
        free(pNode->data);
        free(pNode);
        return SUCCESS;
    }
    else {
        return FAILURE;
    }
}

// 通过ISBN获得标题 
char *GetTitleByISBN(char *isbn)
{
    tListNode *pNode = NULL;
    int id;
    pNode = SearchBookByISBN(GetListByType(BOOK), isbn);
    if (NULL == pNode) {
        pNode = SearchBookByISBN(GetListByType(PERIODICALS), isbn);
        if (NULL == pNode) {
            pNode = SearchBookByISBN(GetListByType(NEWSPAPER), isbn);
            if (NULL == pNode)
            return NULL;
        } 
    }
    
    id = GetBookID(pNode);
    return (char*)GetBookInfo(id, TITLE); 
}

// 添加统计节点 
static int AddStatisticsCondition(tListNode * pNode, tListNode * pAddNode, void * arg)
{
    tListNode * pNodeNext = GetListNext(pNode);
    statistics_info * statInfoPrev = NULL;
    statistics_info * statInfoNext = NULL;
    statistics_info * statInfoCurr = NULL;
    
    if (NULL == pNodeNext) {
        return SUCCESS;
    }
    
    statInfoPrev = (statistics_info*)(pNode->data);
    statInfoNext = (statistics_info*)(pNodeNext->data);
    statInfoCurr = (statistics_info*)(pAddNode->data);
    
    // 按借阅次数排序加入链表 
    if (statInfoPrev->lent_times <= statInfoCurr->lent_times 
        && statInfoCurr->lent_times < statInfoNext->lent_times) {
            return SUCCESS;
        }
    return FAILURE;
}

int AddStaitsticsNode(tListStruct *pList, tListNode *pNode)
{
    tListStruct * statisticsList = GetStatisticsList();
    tListNode *pHead = NULL;
    statistics_info * pHeadStat;
    statistics_info * pNodeStat; 
    
    if (pNode != NULL) {
        pHead = GetListHead(pList);
        if (pHead != NULL) {
            pHeadStat = (statistics_info*)(pHead->data);
            pNodeStat = (statistics_info*)(pNode->data);
            if (pHeadStat->lent_times < pNodeStat->lent_times) {
                AddListNodeToHead(pList, (void*)(pNode->data));
            }
            else {
                AddListNode(pList, (void*)(pNode->data), AddStatisticsCondition, NULL);
            }
        }
        else {
            AddListNodeToHead(pList, (void*)(pNode->data));
        }
        return SUCCESS;
    }
    else {
        return FAILURE;
    }
}

int DeleteStatisticsListCondition(tListNode *pNode, void *arg)
{
    statistics_info *pStat = (statistics_info*)(pNode->data);
    free(pStat);
    return SUCCESS;
}

// 深层删除链表 
void DeleteStatisticsList()
{
    DeleteList(statisticsList, DeleteStatisticsListCondition, NULL);
}
