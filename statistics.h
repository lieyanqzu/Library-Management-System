/*******************************************************
 File name: statistics.h
 
 Date: 2015.12.21
 
 Description: ͳ�ƽ��Ĵ��� 
    
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

// ����ͳ������ 
tListStruct * GetStatisticsList();

// �������ݵ�ͳ������ 
int AddToStatisticsList(char *isbn);

// ͨ��ISBN����ͳ�ƽڵ� 
static int SearchStatisticsCondition(tListNode *pNode, void *arg); 
tListNode * SearchStatisticsByISBN(char *isbn);

// ����һ��ͳ�ƴ��� 
void AddOnceToStatistics(char *isbn);

// ɾ��ͳ�ƽڵ� 
int DeleteStatisticsNode(char *isbn);

// ͨ��ISBN��ñ��� 
char *GetTitleByISBN(char *isbn);

// ���������ͳ�ƽڵ� 
static int AddStatisticsCondition(tListNode * pNode, tListNode * pAddNode, void * arg);
int AddStaitsticsNode(tListStruct *pList, tListNode *pNode);

// ���ɾ������ 
int DeleteStatisticsListCondition(tListNode *pNode, void *arg);
void DeleteStatisticsList();

#endif
