/*******************************************************
 File name: book_lent.h
 
 Date: 2015.12.7
 
 Description: �ѽ��ͼ�����Ϣ("ÿһ�������ĵ��鶼������
    ����Ϣ����š�������������֤�š��������ڡ�������
    �ڡ�������ȡ�")
    
 Dependency: list_node

 History: 
 
********************************************************/


#ifndef _BOOK_LENT_H_
#define _BOOK_LENT_H_

#include <time.h>

#include "list_node.h"

// �޸�����ʱѡ�����Ϣ�� 
typedef enum {
    LICENSE = 0, 
    BORROW_TIME = 1, 
    EXPIRE_TIME = 2,  
    FINE = 3,  
} LentInfoFlag;

// �ѽ��ͼ����Ϣ 
typedef struct {
    int     id;
    int     license;
    time_t  borrow_time;
    time_t  expire_time;
    double  fine;
} book_lent_info;

// ��ID�����ѽ��ͼ��
static int SearchLentBookConditon(tListNode * pListNode,void * arg);

// ͨ��ID�õ�book_lent_info 
static book_lent_info * GetLentInfoById(int id); 

// ����book_lent_info�ṹ 
book_lent_info * CreateLentPrototype(int id_, int license_, time_t borrow_time_);

// �����ѽ��ͼ������ 
tListStruct * GetBookLentList() ;

// �����µ��ѽ������������ 
int AddToBookLentList(book_lent_info * pLentBook);

// ͨ��ID�����ѽ��ͼ��ڵ� 
tListNode * SearchLentBookById(int id);

// ɾ��һ���ѽ��ͼ����Ϣ 
int RemoveLentBook(int id);

// ���ؽڵ���ָ���ͼ��ID 
int GetLentId(tListNode * pNode);

// �޸�ͼ�����ʱ�� 
int SetLentExpireTime(int id, time_t expire_time_);

// �޸�ͼ�鷣�� 
int SetLentFine(int id, double fine_);

// �����ѽ����ͼ�����Ϣ�� 
void * GetLentBookInfo(int id, LentInfoFlag sFlag);

#endif
