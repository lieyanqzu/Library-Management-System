/*******************************************************
 File name: statistics.h
 
 Date: 2015.12.21
 
 Description: 统计借阅次数 
    
 Dependency: 

 History: 
 
********************************************************/


#ifndef _STATISTICS_H
#define _STATISTICS_H

#include "book.h"

typedef struct {
    char isbn[ISBN_LEN];
    int lent_times;
} statistics_info;

// 返回统计链表 
tListStruct * GetStatisticsList();

// 加入数据到统计链表 
int AddToStatisticsList(char *isbn);

// 通过ISBN搜索统计节点 
static int SearchStatisticsCondition(tListNode *pNode, void *arg); 
tListNode * SearchStatisticsByISBN(char *isbn);

// 增加一次统计次数 
void AddOnceToStatistics(char *isbn);

// 删除统计节点 
int DeleteStatisticsNode(char *isbn);

// 通过ISBN获得标题 
char *GetTitleByISBN(char *isbn);

// 按排序添加统计节点 
static int AddStatisticsCondition(tListNode * pNode, tListNode * pAddNode, void * arg);
int AddStaitsticsNode(tListStruct *pList, tListNode *pNode);

// 深层删除链表 
int DeleteStatisticsListCondition(tListNode *pNode, void *arg);
void DeleteStatisticsList();

#endif
