#ifndef _INTERACT_H_
#define _INTERACT_H_

static void CursorGotoxy(int x,int y);

void ShowHeadInfo(int license);

void ShowLogin();

void ShowMain(int license);

void ShowMainForUser(int license);

void ShowMainForAdmin(int license);

void ShowSetting(int license);

void ShowAccount(int license);

void ShowAllAccount(int license);

int ShowAccountPage(int license, tListNode *pNode);

void ShowAddAccount(int license);

void ShowAccountInfo(int need_license);

void ShowAccountSearch(int license, int need_license);

int ProgramExit();
#endif
