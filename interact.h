/*******************************************************
 File name: interact.h
 
 Date: 2015.12.21
 
 Description: 用户界面的显示 
    
 Dependency: book account file setting operation 
    book_lent statistics

 History: 
 
********************************************************/


#ifndef _INTERACT_H_
#define _INTERACT_H_

#include "book.h"
#include "list_node.h"

static void CursorGotoxy(int x,int y);

void ShowHeadInfo(int license);

void ShowLogin();

void ShowMain(int license);

void ShowMainForAdmin(int license);

void ShowSetting(int license);

void ShowAccount(int license);

void ShowAllAccount(int license);

int ShowAccountPage(int license, tListNode *pNode);

void ShowAddAccount(int license);

void ShowAccountInfo(int need_license);

void ShowAccountSearch(int license, int need_license);

void ShowBookManage(int license);

void ShowAddBook(int license);

void ShowAllBook(int license, BookType type);

int ShowBookPage(int license, tListNode *pNode);

void ShowBookInfo(int id);

void ShowBookSearch(int license, int id);

void ShowBookSearchForAdmin(int license, int id);

void ShowBookSearchForUser(int license, int id);

InfoFlag ChooseOneBookInfo();

void ShowSearchBykey(int license, char *key);

void ShowLicenseLent(int license, int need_license);

int ShowLicenseLentPage(int license, tListNode *pNode);

void ShowMainForUser(int license);

void ShowMyAccountInfo(int license);

void ShowStatistics(int license);

#endif
