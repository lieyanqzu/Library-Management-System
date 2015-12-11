/*******************************************************
 File name: book_lent.h
 
 Date: 2015.12.7
 
 Description: 已借出图书的信息("每一本被借阅的书都包括如
    下信息：编号、书名、金额、借书证号、借书日期、到期日
    期、罚款金额等。")
    
 Dependency: list_node

 History: 
 
********************************************************/


#ifndef _BOOK_LENT_H_
#define _BOOK_LENT_H_

#include <time.h>

#include "list_node.h"

// 修改数据时选择的信息项 
typedef enum {
    LICENSE = 0, 
    BORROW_TIME = 1, 
    EXPIRE_TIME = 2,  
    FINE = 3,  
} LentInfoFlag;

// 已借出图书信息 
typedef struct {
    int     id;
    int     license;
    time_t  borrow_time;
    time_t  expire_time;
    double  fine;
} book_lent_info;

// 按ID搜索已借出图书
static int SearchLentBookConditon(tListNode * pListNode,void * arg);

// 通过ID得到book_lent_info 
static book_lent_info * GetLentInfoById(int id); 

// 返回book_lent_info结构 
book_lent_info * CreateLentPrototype(int id_, int license_, time_t borrow_time_);

// 返回已借出图书链表 
tListStruct * GetBookLentList() ;

// 加入新的已借出数据至链表 
int AddToBookLentList(book_lent_info * pLentBook);

// 通过ID搜索已借出图书节点 
tListNode * SearchLentBookById(int id);

// 删除一本已借出图书信息 
int RemoveLentBook(int id);

// 返回节点所指向的图书ID 
int GetLentId(tListNode * pNode);

// 修改图书过期时间 
int SetLentExpireTime(int id, time_t expire_time_);

// 修改图书罚金 
int SetLentFine(int id, double fine_);

// 返回已借出的图书的信息项 
void * GetLentBookInfo(int id, LentInfoFlag sFlag);

#endif
