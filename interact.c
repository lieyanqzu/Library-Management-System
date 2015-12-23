/*******************************************************
 File name: interact.c 
 
 Date: 2015.12.21
 
 Description: 用户界面的显示 
    
 Dependency: book account file setting operation 
    book_lent statistics

 History: 
 
********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#include "book.h"
#include "account.h"
#include "file.h"
#include "setting.h"
#include "operation.h"
#include "book_lent.h"
#include "statistics.h"

#include "interact.h"

#define LIMIT_X 79
#define LIMIT_Y 24 
#define PER_PAGE 8 // 列表每页显示数量 

typedef enum {
    BACKSPACE = 8,
    ESC = 27,
    ENTER = 13,
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
} KeyNum;

static void CursorGotoxy(int x,int y)
{
    COORD loc = {x, y};
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, loc);
}

void ShowHeadInfo(int license)
{
    char * str1 = "欢迎使用图书管理系统";
    char * str2 = "当前用户：";
    char * str3 = "未登录";
    char buf[10];
    int len_license = 0;
    int len = (int)strlen(str2);
    int user_start_point;
    int tag_start_point;

    if (license == 0) {
        CursorGotoxy(25, 0);
        printf("%s", str1);
        CursorGotoxy(70, 0);
        printf("┇%s", str3);
        printf("\n════════════════════════════════════════\n");
    }
    else {
        sprintf(buf, "%d", license);
        len_license = (int)strlen(buf);
        user_start_point = LIMIT_X-len-len_license-2;
        tag_start_point = user_start_point/2-10;
        CursorGotoxy(tag_start_point, 0);
        printf("%s", str1);
        CursorGotoxy(user_start_point, 0);
        printf("┇%s%d", str2, license);
        printf("\n════════════════════════════════════════\n");
    }
}

void ShowLogin()
{
    int license;
    char temp[PW_LEN];
    int cnt = 0;
    char ch;
    char * pw = NULL;
    tListNode *pNode = NULL;

    system("cls");
    while (1) {
        ShowHeadInfo(0);
        CursorGotoxy(12, 12);
        printf("请输入账号\n");
        CursorGotoxy(16, 13);
        printf(">                    ");
        CursorGotoxy(17, 13);
        scanf("%d", &license);

        pNode = SearchAccountByLicense(license);

        if (pNode !=  NULL) {
            CursorGotoxy(0, 4);
            printf("                    ");
            break;
        }
        CursorGotoxy(0, 4);
        printf(" ！！此账号不存在！！");
    }

    while (1) {
        CursorGotoxy(12, 14);
        printf("请输入密码\n");
        CursorGotoxy(16, 15);
        printf(">                    ");
        CursorGotoxy(17, 15);

        while(cnt < 17 && (ch = getch()) != ENTER)
        {
            if (ch != BACKSPACE) {
                temp[cnt++] = ch;
                printf("*");
            }
            else {
                if (cnt > 0) {
                    temp[--cnt] = 0;
                    printf("\b \b");
                }
            }
        }
        if (cnt == 17) {
            cnt = 0;
            CursorGotoxy(0, 4);
            printf(" ！！密码长度过长！！");
        }
        else {
            temp[cnt] = 0;
            pw = (char*)GetAccountInfo(license, PASSWORD);
            if (strcmp(temp, pw) == 0) {
                CursorGotoxy(0, 4);
                printf("                    ");
                break;
            }
            else {
                cnt = 0;
                CursorGotoxy(0, 4);
                printf(" ！！密码输入错误！！");
            }
        }
    }

    ShowMain(license);
}

// 为不同的登陆账户显示不同的界面 
void ShowMain(int license)
{
    AccountRank rank;
    rank = *(AccountRank*)GetAccountInfo(license, RANK);

    if (rank != ADMIN) {
        ShowMainForUser(license);
    }
    else {
        ShowMainForAdmin(license);
    }

}

void ShowMainForAdmin(int license)
{
    int index;
    char c2;
     
    START:
    system("cls");
    ShowHeadInfo(license);
    
    CursorGotoxy(20, 7);
    printf("->图 书 管 理\n");
    CursorGotoxy(20, 9);
    printf("  读 者 管 理\n");
    CursorGotoxy(20, 11);
    printf("  统 计 数 据\n");
    CursorGotoxy(20, 13);
    printf("  系 统 设 置\n");
    CursorGotoxy(20, 15);
    printf("  退 出");
    index = 1;
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("方向键上/下：选择项目      ENTER：确认选择      ESC：退出程序");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1){
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            ProgramExit();
        case ENTER:
            switch(index) {
            case 1:
                ShowBookManage(license); 
                goto START;
            case 2:
                ShowAccount(license); 
                goto START;
            case 3:
                ShowStatistics(license);
                goto START;
            case 4:
                ShowSetting(license);
                goto START;
            case 5:
                return;
            }
            break;
        case UP:
            if (index == 1) {
                break;
            }
            CursorGotoxy(20, index*2+3); 
            printf("->");
            CursorGotoxy(20, index*2+5);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == 5) {
                break;
            }
            CursorGotoxy(20, index*2+5); 
            printf("  ");
            CursorGotoxy(20, index*2+7);
            printf("->"); 
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }
}

void ShowSetting(int license)
{
    int num = 0;
    double fine = 0.0;
    int index;
    char c2;
    Setting * set = GetSetting();
    
    system("cls");
    ShowHeadInfo(license);
    
    CursorGotoxy(20, 7);
    printf("->教师最大借阅数（当前%d）\n", set->teacher_borrow_number);
    CursorGotoxy(20, 9);
    printf("  学生最大借阅数（当前%d）\n", set->student_borrow_number);
    CursorGotoxy(20, 11);
    printf("  教师最大续借次数（当前%d）\n", set->teacher_renew_times);
    CursorGotoxy(20, 13);
    printf("  学生最大续借次数（当前%d）\n", set->student_renew_times);
    CursorGotoxy(20, 15);
    printf("  到期未还每天罚金数（当前%.2f）\n", set->fine_per_day);
    CursorGotoxy(20, 17);
    printf("  返回上级菜单");
    index = 1;
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1){
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            switch(index) {
            case 1:
                CursorGotoxy(20, index*2+5);
                printf("->修改值：                                        ");
                CursorGotoxy(30, index*2+5);
                scanf("%d", &num);
                if (num > 0) {
                    set->teacher_borrow_number = num;
                    WriteSetting();
                }
                CursorGotoxy(20, index*2+5);
                printf("->教师最大借阅数（当前%d）\n", set->teacher_borrow_number);
                CursorGotoxy(LIMIT_X, LIMIT_Y);
                break;
            case 2:
                CursorGotoxy(20, index*2+5);
                printf("->修改值：                                        ");
                CursorGotoxy(30, index*2+5);
                scanf("%d", &num);
                if (num > 0) {
                    set->student_borrow_number = num;
                    WriteSetting();
                }
                CursorGotoxy(20, index*2+5);
                printf("->学生最大借阅数（当前%d）\n", set->student_borrow_number);
                CursorGotoxy(LIMIT_X, LIMIT_Y);
                break;
            case 3:
                CursorGotoxy(20, index*2+5);
                printf("->修改值：                                        ");
                CursorGotoxy(30, index*2+5);
                scanf("%d", &num);
                if (num > 0) {
                    set->teacher_renew_times = num;
                    WriteSetting();
                }
                CursorGotoxy(20, index*2+5);
                printf("->教师最大续借次数（当前%d）\n", set->teacher_renew_times);
                CursorGotoxy(LIMIT_X, LIMIT_Y);
                break;
            case 4:
                CursorGotoxy(20, index*2+5);
                printf("->修改值：                                        ");
                CursorGotoxy(30, index*2+5);
                scanf("%d", &num);
                if (num > 0) {
                    set->student_renew_times = num;
                    WriteSetting();
                }
                CursorGotoxy(20, index*2+5);
                printf("->学生最大续借次数（当前%d）\n", set->student_renew_times);
                CursorGotoxy(LIMIT_X, LIMIT_Y);
                break;
            case 5:
                CursorGotoxy(20, index*2+5);
                printf("->修改值：                                        ");
                CursorGotoxy(30, index*2+5);
                scanf("%lf", &fine);
                if (fine > 0.0) {
                    set->fine_per_day = fine;
                    WriteSetting();
                }
                CursorGotoxy(20, index*2+5);
                printf("->到期未还每天罚金数（当前%.2f）\n", set->fine_per_day);
                CursorGotoxy(LIMIT_X, LIMIT_Y);
                break;
            case 6:
                return;
            }
            break;
        case UP:
            if (index == 1) {
                break;
            }
            CursorGotoxy(20, index*2+3); 
            printf("->");
            CursorGotoxy(20, index*2+5);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == 6) {
                break;
            }
            CursorGotoxy(20, index*2+5); 
            printf("  ");
            CursorGotoxy(20, index*2+7);
            printf("->"); 
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }
}

void ShowAccount(int license)
{
    int index;
    int need_license;
    tListNode *pNode = NULL;
    char c2;
    
    START:
    system("cls");
    ShowHeadInfo(license);
    
    CursorGotoxy(20, 7);
    printf("->读者信息一览\n");
    CursorGotoxy(20, 9);
    printf("  新增读者信息\n");
    CursorGotoxy(20, 11);
    printf("  读者信息查询（修改）\n");
    CursorGotoxy(20, 13);
    printf("  返回上级菜单");
    index = 1;
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1){
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            switch(index) {
            case 1:
                ShowAllAccount(license);
                goto START;
            case 2:
                ShowAddAccount(license);
                goto START;
            case 3:
                CursorGotoxy(20, index*2+5);
                printf("->输入查询账号：     \b\b\b\b\b");
                fflush(stdin);
                scanf("%d", &need_license);
                pNode = SearchAccountByLicense(need_license);

                if (pNode !=  NULL) {
                    ShowAccountSearch(license, need_license);
                }
                else {
                    CursorGotoxy(0, 4);
                    printf(" ！！此账号不存在！！");
                    CursorGotoxy(20, index*2+5);
                    printf("->读者信息查询（修改）                          \n");
                    CursorGotoxy(LIMIT_X, LIMIT_Y);
                    break;
                }
                goto START;
            case 4:
                return;
            }
            break;
        case UP:
            if (index == 1) {
                break;
            }
            CursorGotoxy(20, index*2+3); 
            printf("->");
            CursorGotoxy(20, index*2+5);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == 4) {
                break;
            }
            CursorGotoxy(20, index*2+5); 
            printf("  ");
            CursorGotoxy(20, index*2+7);
            printf("->"); 
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }
}

void ShowAllAccount(int license)
{
    tListStruct *pList = GetAccountList();
    tListNode **pNodeArray;
    int need_license;
    int size;
    int index = 1;
    int page = 0;
    int num;
    char c2;
    
    if (pList->length % PER_PAGE == 0) {
        size = pList->length / PER_PAGE;
    }
    else {
        size = pList->length / PER_PAGE + 1;
    }
    
    pNodeArray = (tListNode**)malloc(sizeof(tListNode*)*size);
    ListNodeSplit(pList, pNodeArray);
    
    num = ShowAccountPage(license, pNodeArray[page]);
    CursorGotoxy(4, 6);
    printf("->");
    CursorGotoxy(0, LIMIT_Y-1); 
    printf("方向键左/右：前后翻页      当前第%d页----共%d页", page+1, size);
    CursorGotoxy(0, LIMIT_Y); 
    printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1) {
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            need_license = AccountNodeStepping(pNodeArray[page], index);
            ShowAccountSearch(license, need_license);
            return;
        case UP:
            if (index == 1 || num == 0) {
                break;
            }
            CursorGotoxy(4, index*2+2); 
            printf("->");
            CursorGotoxy(4, index*2+4);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == num || num == 0) {
                break;
            }
            CursorGotoxy(4, index*2+4); 
            printf("  ");
            CursorGotoxy(4, index*2+6);
            printf("->"); 
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case LEFT:
            if (page == 0) {
                break;
            }
            index = 1;
            num = ShowAccountPage(license, pNodeArray[--page]);
            CursorGotoxy(4, 6);
            printf("->");
            CursorGotoxy(0, LIMIT_Y-1); 
            printf("方向键左/右：前后翻页      当前第%d页----共%d页", page+1, size);
            CursorGotoxy(0, LIMIT_Y); 
            printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case RIGHT:
            if (page == size-1) {
                break;
            }
            index = 1;
            num = ShowAccountPage(license, pNodeArray[++page]);
            CursorGotoxy(4, 6);
            printf("->");
            CursorGotoxy(0, LIMIT_Y-1); 
            printf("方向键左/右：前后翻页      当前第%d页----共%d页", page+1, size);
            CursorGotoxy(0, LIMIT_Y); 
            printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }
}

int ShowAccountPage(int license, tListNode *pNode)
{
    int get_license;
    char name[STR_LEN];
    char classes[STR_LEN];
    AccountRank rank;
    int i;
    int num = 0;
    system("cls");
    ShowHeadInfo(license);
    
    CursorGotoxy(4, 4); 
    printf("  账号              姓名              班级              类别              ");
    for (i = 0; i < PER_PAGE && pNode != NULL; i++) {
        get_license = GetLicenseByNode(pNode);
        strncpy(name, (char*)GetAccountInfo(get_license, NAME), STR_LEN-1);
        strncpy(classes, (char*)GetAccountInfo(get_license, CLASSES), STR_LEN-1);
        rank = *(AccountRank*)GetAccountInfo(get_license, RANK);
        CursorGotoxy(4, i*2+6); 
        printf("  %-18d%-18s%-18s", get_license, name, classes);
        switch (rank) {
        case STUDENT:
            printf("学生");
            break;
        case TEACHER:
            printf("教师");
            break;
        case ADMIN:
            printf("管理员");
            break;
        case LOSS:
            printf("挂失中");
            break;
        }
        pNode = GetListNext(pNode);
        num++;
    }
    return num;
}

void ShowAddAccount(int license)
{
    int new_license;
    char name[STR_LEN];
    char classes[STR_LEN];
    int temprank;
    AccountRank rank; 
    tListNode *pNode = NULL;
    
    system("cls");
    ShowHeadInfo(license);
    
    while(1) {
        CursorGotoxy(20, 7);
        printf("1.学生\t2.教师");
        CursorGotoxy(20, 8);
        printf("类别：");
        fflush(stdin);
        scanf("%d", &temprank);
        
        if (temprank != 1 && temprank != 2) {
            CursorGotoxy(0, 4);
            printf(" ！！请输入1或2！！");
            CursorGotoxy(20, 8);
            printf("类别:                    ");
            CursorGotoxy(26, 8);
        }
        else {
            if (temprank == 1) {
                rank = STUDENT;
            }
            else if (temprank == 2) {
                rank = TEACHER;
            }
            break;
        }
    }
    
    while (1) {
        CursorGotoxy(20, 10);
        printf("账号：");
        fflush(stdin);
        scanf("%d", &new_license);

        pNode = SearchAccountByLicense(new_license);

        if (pNode !=  NULL) {
            CursorGotoxy(0, 4);
            printf(" ！！账号已经存在！！");
            CursorGotoxy(20, 10);
            printf("账号：                        ");
            CursorGotoxy(26, 10);
        }
        else {
            break;
        }
    }
    
    CursorGotoxy(20, 12);
    printf("姓名：");
    fflush(stdin);
    scanf("%s", &name);
    
    if (rank != TEACHER) {
        CursorGotoxy(20, 14);
        printf("班级：");
        fflush(stdin);
        scanf("%s", &classes);
    }
    else {
        strcpy(classes, "");
    }
    
    AddToAccountList(CreateAccountPrototype(new_license, name, classes, rank));
    WriteAccountFile();
}

void ShowAccountInfo(int need_license)
{
    tListNode *pNode = SearchAccountByLicense(need_license);
    char name[STR_LEN];
    char classes[STR_LEN];
    AccountRank rank;
     
    CursorGotoxy(6, 7);
    printf("账号：%d\n", need_license);
    CursorGotoxy(6, 9);
    strcpy(name, (char*)GetAccountInfo(need_license, NAME));
    printf("姓名：%s\n", name);
    CursorGotoxy(6, 11);
    strcpy(classes, (char*)GetAccountInfo(need_license, CLASSES));
    printf("班级：%s\n", classes);
    CursorGotoxy(6, 13);
    printf("类别：");
    rank = *(AccountRank*)GetAccountInfo(need_license, RANK);
    switch (rank) {
    case STUDENT:
        printf("学生");
        break;
    case TEACHER:
        printf("教师");
        break;
    case ADMIN:
        printf("管理员");
        break;
    case LOSS:
        printf("挂失中");
        break;
    }
}

void ShowAccountSearch(int license, int need_license)
{
    int index;
    char tempch;
    char name[STR_LEN];
    char classes[STR_LEN];
    char c2;
    
    START:
    system("cls");
    ShowHeadInfo(license);
    ShowAccountInfo(need_license);
    
    CursorGotoxy(45, 7);
    printf("->修改读者姓名\n");
    CursorGotoxy(45, 9);
    printf("  修改读者班级\n");
    CursorGotoxy(45, 11);
    printf("  显示此账号当前借阅\n");
    CursorGotoxy(45, 13);
    printf("  挂失账号或取消\n");
    CursorGotoxy(45, 15);
    printf("  恢复到默认密码\n");
    CursorGotoxy(45, 17);
    printf("  注销此账号\n");
    CursorGotoxy(45, 19);
    printf("  返回上级菜单");
    index = 1;
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1){
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            switch(index) {
            case 1:
                CursorGotoxy(45, 7);
                printf("->修改值：     \b\b\b\b\b");
                fflush(stdin);
                scanf("%s", name);
                ModifyAccountInfo(need_license, (void*)name, NAME);
                WriteAccountFile();
                goto START;
            case 2:
                CursorGotoxy(45, 9);
                printf("->修改值：     \b\b\b\b\b");
                fflush(stdin);
                scanf("%s", classes);
                ModifyAccountInfo(need_license, (void*)classes, CLASSES);
                WriteAccountFile();
                goto START;
            case 3:
                ShowLicenseLent(license, need_license);
                goto START;
            case 4:
                CursorGotoxy(45, 13);
                printf("->确认挂失或取消吗？（Y/N）");
                fflush(stdin);
                scanf("%c", &tempch);
                if (tempch == 'Y' || tempch == 'y') {
                    LossRegistration(need_license);
                    return;
                }
                else {
                    goto START;
                }
                break;
            case 5:
                CursorGotoxy(45, 15);
                printf("->确认恢复到默认密码？（Y/N）");
                fflush(stdin);
                scanf("%c", &tempch);
                if (tempch == 'Y' || tempch == 'y') {
                    ChangePasswordToDefault(need_license);
                    return;
                }
                else {
                    goto START;
                }
            case 6:
                CursorGotoxy(45, 17);
                printf("->确认注销此账号？（Y/N）");
                fflush(stdin);
                scanf("%c", &tempch);
                if (tempch == 'Y' || tempch == 'y') {
                    CancelAccount(need_license);
                    return;
                } 
                else {
                    goto START;
                }
            case 7:
                return;
            }
            break;
        case UP:
            if (index == 1) {
                break;
            }
            CursorGotoxy(45, index*2+3); 
            printf("->");
            CursorGotoxy(45, index*2+5);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == 7) {
                break;
            }
            CursorGotoxy(45, index*2+5); 
            printf("  ");
            CursorGotoxy(45, index*2+7);
            printf("->");
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }
}

void ShowBookManage(int license)
{
    int index;
    int need_id;
    int temptype;
    BookType type; 
    tListNode *pNode = NULL;
    char key[MAX_STR];
    char c2;
    
    START: 
	system("cls");
    ShowHeadInfo(license);
    
    CursorGotoxy(20, 7);
    printf("->搜索图书信息\n");
    CursorGotoxy(20, 9);
    printf("  图书信息一览\n");
    CursorGotoxy(20, 11);
    printf("  新增图书信息\n");
    CursorGotoxy(20, 13);
    printf("  图书信息查询（修改）\n");
    CursorGotoxy(20, 15);
    printf("  返回上级菜单");
    index = 1; 
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("方向键上/下：选择项目      ENTER：确认选择      ESC：退出程序");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1){
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            switch(index) {
            case 1:
                CursorGotoxy(20, 7);
                printf("->输入搜索关键字：");
                fflush(stdin);
                scanf("%s", key);
                ShowSearchBykey(license, key);
                goto START; 
            case 2:
                while (1) {
                    CursorGotoxy(0, 4);
                    printf(" ！！1.图书  2.期刊  3.报刊！！");
                    CursorGotoxy(20, index*2+5);
                    printf("->选择书籍种类：     \b\b\b\b\b");
                    fflush(stdin);
                    scanf("%d", &temptype);
                    if (temptype == 1 || temptype == 2 || temptype == 3) {
                        switch (temptype) {
                        case 1:
                            type = BOOK;
                            break;
                        case 2:
                            type = PERIODICALS;
                            break;
                        case 3:
                            type = NEWSPAPER;
                            break;
                        }
                        break;
                    }
                }
                ShowAllBook(license, type);
                goto START;
            case 3:
                ShowAddBook(license);
                goto START;
			case 4:
			    CursorGotoxy(20, index*2+5);
                printf("->输入查询书籍编号：     \b\b\b\b\b");
                fflush(stdin);
                scanf("%d", &need_id);
                pNode = SearchBookById(need_id);

                if (pNode !=  NULL) {
                    ShowBookSearch(license, need_id);
                }
                else {
                    CursorGotoxy(0, 4);
                    printf(" ！！此书籍不存在！！");
                    CursorGotoxy(20, index*2+5);
                    printf("->读者信息查询（修改）                          \n");
                    CursorGotoxy(LIMIT_X, LIMIT_Y);
                    break;
                }
                goto START;
			case 5:
				return;
            }
            break;
        case UP:
            if (index == 1) {
                break;
            }
            CursorGotoxy(20, index*2+3); 
            printf("->");
            CursorGotoxy(20, index*2+5);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == 5) {
                break;
            }
            CursorGotoxy(20, index*2+5); 
            printf("  ");
            CursorGotoxy(20, index*2+7);
            printf("->"); 
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }
}

void ShowAddBook(int license)
{
    char isbn[ISBN_LEN]; 
    char title[MAX_STR];
    char author[MAX_STR];
    char press[MAX_STR];
    double price;
    int temptype;
    BookType type;
    int index; 
    char c2;
    
    system("cls");
    ShowHeadInfo(license);
    
    while (1) {
        CursorGotoxy(20, 7);
        printf("1.图书    2.期刊    3.报刊");
        CursorGotoxy(20, 8);
        printf("类别：");
        fflush(stdin);
        scanf("%d", &temptype);
        
        if (temptype != 1 && temptype != 2 && temptype != 3) {
            CursorGotoxy(0, 4);
            printf(" ！！请输入1、2或3！！");
            CursorGotoxy(20, 8);
            printf("类别:                    ");
            CursorGotoxy(26, 8);
        }
        else {
            if (temptype == 1) {
                type = BOOK;
            }
            else if (temptype == 2) {
                type = PERIODICALS;
            }
            else if (temptype == 3) {
                type = NEWSPAPER;
            } 
            break;
        }
    }
    
    CursorGotoxy(20, 10);
    printf("ISBN号：");
    fflush(stdin);
    scanf("%s", isbn);
    
    CursorGotoxy(20, 12);
    printf("标题：");
    fflush(stdin);
    scanf("%s", title);
    
    CursorGotoxy(20, 14);
    printf("作者：");
    fflush(stdin);
    scanf("%s", author);

    CursorGotoxy(20, 16);
    printf("出版社：");
    fflush(stdin);
    scanf("%s", press);
    
    CursorGotoxy(20, 18);
    printf("价格：");
    fflush(stdin);
    scanf("%lf", &price);
    
    system("cls");
    ShowHeadInfo(license);
    
    CursorGotoxy(0, 4);
    printf(" ！！请确认您输入的信息！！");
    
    CursorGotoxy(20, 8);
    printf("ISBN号：%s", isbn);
    
    CursorGotoxy(20, 10);
    printf("标题：%s", title);
    
    CursorGotoxy(20, 12);
    printf("作者：%s", author);
    
    CursorGotoxy(20, 14);
    printf("出版社：%s", press);
    
    CursorGotoxy(20, 16);
    printf("价格：%.2f", price);
    
    CursorGotoxy(20, 18);
    printf("类别：");
    switch(type) {
    case BOOK:
        printf("图书");
        break;
    case PERIODICALS:
        printf("期刊");
        break;
    case NEWSPAPER:
        printf("报刊");
        break;
    }
    
    index = 1;
    CursorGotoxy(55, 15);
    printf("->确认");
    CursorGotoxy(55, 17);
    printf("  取消");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while (1) {
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            switch(index) {
            case 1:
                AddToBooksList(CreateBookPrototype(isbn, title, author, press, price, type));
                WriteBookFile();
                return;
            case 2:
                return; 
            } 
            break;
        case UP:
            if (index == 1) {
                break;
            }
            CursorGotoxy(55, 15); 
            printf("->");
            CursorGotoxy(55, 17);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == 2) {
                break;
            }
            CursorGotoxy(55, 15); 
            printf("  ");
            CursorGotoxy(55, 17);
            printf("->");
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }        
    }
}

void ShowAllBook(int license, BookType type)
{
    tListStruct *pList = GetListByType(type);
    tListNode **pNodeArray;
    int need_id;
    int size;
    int index = 1;
    int page = 0;
    int num;
    char c2;

    if (pList->length % PER_PAGE == 0) {
        size = pList->length / PER_PAGE;
    }
    else {
        size = pList->length / PER_PAGE + 1;
    }
    
    pNodeArray = (tListNode**)malloc(sizeof(tListNode*)*size);
    ListNodeSplit(pList, pNodeArray);
    
    num = ShowBookPage(license, pNodeArray[page]);
    CursorGotoxy(4, 6);
    printf("->");
    CursorGotoxy(0, LIMIT_Y-1); 
    printf("方向键左/右：前后翻页      当前第%d页----共%d页", page+1, size);
    CursorGotoxy(0, LIMIT_Y); 
    printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1) {
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            if (num == 0) {
                return;
            } 
            need_id = BookNodeStepping(pNodeArray[page], index);
            ShowBookSearch(license, need_id);
            return;
        case UP:
            if (index == 1 || num == 0) {
                break;
            }
            CursorGotoxy(4, index*2+2); 
            printf("->");
            CursorGotoxy(4, index*2+4);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == num || num == 0) {
                break;
            }
            CursorGotoxy(4, index*2+4); 
            printf("  ");
            CursorGotoxy(4, index*2+6);
            printf("->"); 
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case LEFT:
            if (page == 0) {
                break;
            }
            index = 1;
            num = ShowBookPage(license, pNodeArray[--page]);
            CursorGotoxy(4, 6);
            printf("->");
            CursorGotoxy(0, LIMIT_Y-1); 
            printf("方向键左/右：前后翻页      当前第%d页----共%d页", page+1, size);
            CursorGotoxy(0, LIMIT_Y); 
            printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case RIGHT:
            if (page == size-1) {
                break;
            }
            index = 1;
            num = ShowBookPage(license, pNodeArray[++page]);
            CursorGotoxy(4, 6);
            printf("->");
            CursorGotoxy(0, LIMIT_Y-1); 
            printf("方向键左/右：前后翻页      当前第%d页----共%d页", page+1, size);
            CursorGotoxy(0, LIMIT_Y); 
            printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }
}

int ShowBookPage(int license, tListNode *pNode)
{
    int get_id;
    char title[MAX_STR];
    char isbn[ISBN_LEN];
    AccountRank rank;
    int i;
    int num = 0;
    system("cls");
    ShowHeadInfo(license);
    
    CursorGotoxy(4, 4); 
    printf("  编号                    标题                    ISBN                    ");
    for (i = 0; i < PER_PAGE && pNode != NULL; i++) {
        get_id = GetBookID(pNode);
        strncpy(title, (char*)GetBookInfo(get_id, TITLE), MAX_STR-1);
        strncpy(isbn, (char*)GetBookInfo(get_id, ISBN), ISBN_LEN-1);
        CursorGotoxy(4, i*2+6); 
        printf("  %-24d%-24s%-24s", get_id, title, isbn);
        pNode = GetListNext(pNode);
        num++;
    }
    return num;
}

void ShowBookInfo(int id)
{
    tListNode *pNode = SearchBookById(id);
    char isbn[ISBN_LEN]; 
    char title[MAX_STR];
    char author[MAX_STR];
    char press[MAX_STR];
    double price;
    BookType type;
    BookStatus status;
    stock_info* stock;
     
    CursorGotoxy(6, 5);
    printf("编号：%d\n", id);
    
    CursorGotoxy(6, 7);
    strcpy(isbn, (char*)GetBookInfo(id, ISBN));
    printf("ISBN：%s\n", isbn);
    
    CursorGotoxy(6, 9);
    strcpy(title, (char*)GetBookInfo(id, TITLE));
    printf("标题：%s\n", title);
    
    CursorGotoxy(6, 11);
    strcpy(author, (char*)GetBookInfo(id, AUTHOR));
    printf("作者：%s\n", author);
    
    CursorGotoxy(6, 13);
    strcpy(press, (char*)GetBookInfo(id, PRESS));
    printf("出版社：%s\n", press);
    
    CursorGotoxy(6, 15);
    price = *(double*)GetBookInfo(id, PRICE); 
    printf("价格：%.2f\n", price);
    
    CursorGotoxy(6, 17);
    type = *(BookType*)GetBookInfo(id, TYPE);
    printf("类型：");
    switch (type) {
    case BOOK:
        printf("图书\n");
        break;
    case PERIODICALS:
        printf("期刊\n");
        break;
    case NEWSPAPER:
        printf("报刊\n");
        break;
    }
    
    CursorGotoxy(6, 19);
    status = *(BookStatus*)GetBookInfo(id, STATUS);
    printf("状态：");
    switch (status) {
    case IDLE:
        printf("可借\n");
        break;
    case LENT:
        printf("已借出给%d\n", *(int*)GetLentBookInfo(id, LICENSE));
        break;
    }
    
    CursorGotoxy(6, 21);
    stock = (stock_info*)GetBookInfo(id, STOCK);
    printf("可借复本：%d本    已借出：%d本", stock->current_number, stock->lent_number);
}

// 为不同的登陆账户显示不同的界面 
void ShowBookSearch(int license, int id)
{
    AccountRank rank; 
    rank = *(AccountRank*)GetAccountInfo(license, RANK);
    switch (rank) {
    case ADMIN:
        ShowBookSearchForAdmin(license, id);
        break;
    case STUDENT: case TEACHER:
        ShowBookSearchForUser(license, id);
        break;
    }
} 

void ShowBookSearchForAdmin(int license, int id)
{
    BookStatus status;
    int index;
    double fine;
    int position;
    int num;
    char new_info[MAX_STR];
    double new_price;
    int get_license; 
    InfoFlag flag;
    tListNode *pNode = NULL;
    char c2;
    
    START:
    system("cls");
    ShowHeadInfo(license);
    ShowBookInfo(id);
    
    CursorGotoxy(45, 7);
    printf("->修改书籍信息\n");
    CursorGotoxy(45, 9);
    status = *(BookStatus*)GetBookInfo(id, STATUS);
    switch (status)  {
    case IDLE:
        printf("  借出书籍");
        num = 4;
        position = 9;
        break; 
    case LENT:
        printf("  归还书籍");
        CursorGotoxy(45, 11);
        printf("  续借书籍\n");
        num = 5;
        position = 11;
        break; 
    }
    CursorGotoxy(45, position+2);
    printf("  删除此本书籍\n");
    CursorGotoxy(45, position+4);
    printf("  返回上级菜单");
    index = 1;
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1){
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            switch (index) {
                case 1:
                    CursorGotoxy(45, 7);
                    printf("->选择想要修改的信息\n");
                    flag = ChooseOneBookInfo();
                    switch (flag) {
                    case TITLE: case AUTHOR: case PRESS:
                        CursorGotoxy(45, 7);
                        printf("->修改值：                     ");
                        CursorGotoxy(55, 7);
                        fflush(stdin);
                        scanf("%s", new_info);
                        ModifyBookInfo(id, (void*)new_info, flag);
                        WriteBookFile();
                        break;
                    case PRICE:
                        CursorGotoxy(45, 7);
                        printf("->修改值：                     ");
                        CursorGotoxy(55, 7);
                        fflush(stdin);
                        scanf("%lf", &new_price);
                        ModifyBookInfo(id, (void*)&new_price, flag);
                        WriteBookFile();
                        break;
                    }
                    goto START;
                case 2:
                    if (num == 4) {
                        CursorGotoxy(45, 9);
                        printf("->借书证号：               ");
                        CursorGotoxy(57, 9);
                        fflush(stdin);
                        scanf("%d", &get_license);
                        pNode = pNode = SearchAccountByLicense(get_license);
                        if (pNode !=  NULL) {
                            if (LentBookToLicense(id, get_license) == FAILURE) {
                                CursorGotoxy(0, 3);
                                printf(" ！！借阅数量已满或挂失中！！");
                                CursorGotoxy(45, 9);
                                printf("->借出书籍                    ");
                                CursorGotoxy(LIMIT_X, LIMIT_Y);
                                break;
                            } else {
                                goto START;
                            } 
                        }
                        CursorGotoxy(0, 3);
                        printf(" ！！此账号不存在！！");
                        CursorGotoxy(45, 9);
                        printf("->借出书籍                    ");
                        CursorGotoxy(LIMIT_X, LIMIT_Y);
                        break;
                    }
                    if (num == 5) {
                        fine = ReturnBook(id);
                        CursorGotoxy(0, 3);
                        if (fine == -1.0) {
                            break;
                        } else {
                            printf(" ！！需要支付罚金%.2f！！", fine);
                            CursorGotoxy(45, 9);
                            num = 4;
                            position = 9;
                            index = num;
                            printf("  借出书籍          ");
                            CursorGotoxy(45, position+2);
                            printf("  删除此本书籍      ");
                            CursorGotoxy(45, position+4);
                            printf("->返回上级菜单      ");
                            CursorGotoxy(45, position+6);
                            printf("                    ");
                            CursorGotoxy(LIMIT_X, LIMIT_Y);
                        }
                        break;
                    }
                    break;
                case 3:
                    if (num == 4) {
                        DeleteOneBook(id);
                        return;
                    }
                    if (num == 5) {
                        if (RenewBook(id) == FAILURE) {
                            CursorGotoxy(0, 3);
                            printf(" ！！续借失败！！");
                            break;
                        }
                    }
                    break;
                case 4:
                    if (num == 4) {
                        return;
                    }
                    if (num == 5) {
                        DeleteOneBook(id);
                        return;
                    }
                case 5:
                    return;
            }
            break;
        case UP:
            if (index == 1) {
                break;
            }
            CursorGotoxy(45, index*2+3); 
            printf("->");
            CursorGotoxy(45, index*2+5);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == num) {
                break;
            }
            CursorGotoxy(45, index*2+5); 
            printf("  ");
            CursorGotoxy(45, index*2+7);
            printf("->");
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }
}

void ShowBookSearchForUser(int license, int id)
{
    int num, index;
    int get_license;
    START:
    system("cls");
    ShowHeadInfo(license);
    ShowBookInfo(id);
    char c2;
    
    get_license = *(int*)GetLentBookInfo(id, LICENSE);
    if (get_license == license) {
        CursorGotoxy(45, 7);
        printf("->续借书籍");
        CursorGotoxy(45, 9);
        printf("  返回上级菜单");
        CursorGotoxy(LIMIT_X, LIMIT_Y);
        num = 2; 
    }
    else {
        CursorGotoxy(45, 7);
        printf("->返回上级菜单");
        CursorGotoxy(LIMIT_X, LIMIT_Y);
        num = 1;
    }
    index = 1;
    
    while(1){
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            switch (index) {
            case 1:
                if (num == 1) {
                    return;
                }
                if (num == 2) {
                    if (RenewBook(id) == FAILURE) {
                        CursorGotoxy(0, 3);
                        printf(" ！！续借失败！！");
                        break;
                    }
                }
                break;
            case 2:
                return;
            }
            break;
        case UP:
            if (index == 1) {
                break;
            }
            CursorGotoxy(45, index*2+3); 
            printf("->");
            CursorGotoxy(45, index*2+5);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == num) {
                break;
            }
            CursorGotoxy(45, index*2+5); 
            printf("  ");
            CursorGotoxy(45, index*2+7);
            printf("->");
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }
}

InfoFlag ChooseOneBookInfo()
{
    int index;
    char c2;
    
    CursorGotoxy(4, 9);
    printf("->");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    index = 1;
    
    while(1){
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return -1;
        case ENTER:
            return (InfoFlag)(index);
            break;
        case UP:
            if (index == 1) {
                break;
            }
            CursorGotoxy(4, index*2+5); 
            printf("->");
            CursorGotoxy(4, index*2+7);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == 4) {
                break;
            }
            CursorGotoxy(4, index*2+7); 
            printf("  ");
            CursorGotoxy(4, index*2+9);
            printf("->");
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }

}

void ShowSearchBykey(int license, char *key)
{
    tListStruct *pList = GetSearchBookByKey(key);
    tListNode **pNodeArray;
    int need_id;
    int size;
    int index = 1;
    int page = 0;
    int num;
    char c2;

    if (pList->length % PER_PAGE == 0) {
        size = pList->length / PER_PAGE;
    }
    else {
        size = pList->length / PER_PAGE + 1;
    }
    
    pNodeArray = (tListNode**)malloc(sizeof(tListNode*)*size);
    ListNodeSplit(pList, pNodeArray);
    
    num = ShowBookPage(license, pNodeArray[page]);
    CursorGotoxy(4, 6);
    printf("->");
    CursorGotoxy(0, LIMIT_Y-1); 
    printf("方向键左/右：前后翻页      当前第%d页----共%d页", page+1, size);
    CursorGotoxy(0, LIMIT_Y); 
    printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1) {
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            DeleteList(pList, NULL, NULL);
            return;
        case ENTER:
            if (num == 0) {
                return;
            }
            need_id = AccountNodeStepping(pNodeArray[page], index);
            ShowBookSearch(license, need_id);
            DeleteList(pList, NULL, NULL);
            return;
        case UP:
            if (index == 1 || num == 0) {
                break;
            }
            CursorGotoxy(4, index*2+2); 
            printf("->");
            CursorGotoxy(4, index*2+4);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == num || num == 0) {
                break;
            }
            CursorGotoxy(4, index*2+4); 
            printf("  ");
            CursorGotoxy(4, index*2+6);
            printf("->"); 
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case LEFT:
            if (page == 0) {
                break;
            }
            index = 1;
            num = ShowBookPage(license, pNodeArray[--page]);
            CursorGotoxy(4, 6);
            printf("->");
            CursorGotoxy(0, LIMIT_Y-1); 
            printf("方向键左/右：前后翻页      当前第%d页----共%d页", page+1, size);
            CursorGotoxy(0, LIMIT_Y); 
            printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case RIGHT:
            if (page == size-1) {
                break;
            }
            index = 1;
            num = ShowBookPage(license, pNodeArray[++page]);
            CursorGotoxy(4, 6);
            printf("->");
            CursorGotoxy(0, LIMIT_Y-1); 
            printf("方向键左/右：前后翻页      当前第%d页----共%d页", page+1, size);
            CursorGotoxy(0, LIMIT_Y); 
            printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }
}

void ShowLicenseLent(int license, int need_license)
{
    tListStruct *pList = GetLicenseLentList(need_license);
    tListNode **pNodeArray;
    int need_id;
    int size;
    int index = 1;
    int page = 0;
    int num;
    char c2;

    if (pList->length % PER_PAGE == 0) {
        size = pList->length / PER_PAGE;
    }
    else {
        size = pList->length / PER_PAGE + 1;
    }
    
    pNodeArray = (tListNode**)malloc(sizeof(tListNode*)*size);
    ListNodeSplit(pList, pNodeArray);
    
    num = ShowLicenseLentPage(license, pNodeArray[page]);
    CursorGotoxy(4, 6);
    printf("->");
    CursorGotoxy(0, LIMIT_Y-1); 
    printf("方向键左/右：前后翻页      当前第%d页----共%d页", page+1, size);
    CursorGotoxy(0, LIMIT_Y); 
    printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1) {
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            if (num == 0) {
                return;
            }
            DeleteList(pList, NULL, NULL);
            need_id = LicenseLentStepping(pNodeArray[page], index);
            ShowBookSearch(license, need_id);
            return;
        case UP:
            if (index == 1 || num == 0) {
                break;
            }
            CursorGotoxy(4, index*2+2); 
            printf("->");
            CursorGotoxy(4, index*2+4);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == num || num == 0) {
                break;
            }
            CursorGotoxy(4, index*2+4); 
            printf("  ");
            CursorGotoxy(4, index*2+6);
            printf("->"); 
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case LEFT:
            if (page == 0) {
                break;
            }
            index = 1;
            num = ShowBookPage(license, pNodeArray[--page]);
            CursorGotoxy(4, 6);
            printf("->");
            CursorGotoxy(0, LIMIT_Y-1); 
            printf("方向键左/右：前后翻页      当前第%d页----共%d页", page+1, size);
            CursorGotoxy(0, LIMIT_Y); 
            printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case RIGHT:
            if (page == size-1) {
                break;
            }
            index = 1;
            num = ShowBookPage(license, pNodeArray[++page]);
            CursorGotoxy(4, 6);
            printf("->");
            CursorGotoxy(0, LIMIT_Y-1); 
            printf("方向键左/右：前后翻页      当前第%d页----共%d页", page+1, size);
            CursorGotoxy(0, LIMIT_Y); 
            printf("方向键上/下：选择项目      ENTER：确认选择      ESC：返回上级菜单");
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }
}

int ShowLicenseLentPage(int license, tListNode *pNode)
{
    int get_id;
    time_t br_time, ex_time;
    char *brTime, *exTime;
    int i;
    int num = 0;
    system("cls");
    ShowHeadInfo(license);
    
    CursorGotoxy(4, 4);
    printf("  编号                    借书时间                到期时间                 ");
    for (i = 0; i < PER_PAGE && pNode != NULL; i++) {
        get_id = GetLentId(pNode);
        br_time = *(time_t*)GetLentBookInfo(get_id, BORROW_TIME);
        ex_time = *(time_t*)GetLentBookInfo(get_id, EXPIRE_TIME);
        CursorGotoxy(4, i*2+6);
        brTime = TimeToString(br_time);
        exTime = TimeToString(ex_time);
        printf("  %-24d%-24s%-24s", get_id, brTime, exTime);
        free(brTime);
        free(exTime);
        pNode = GetListNext(pNode);
        num++;
    }
    return num;
}

void ShowMainForUser(int license)
{
    char key[MAX_STR];
    int index;
    char c2;
    
    START:
    system("cls");
    ShowHeadInfo(license);
    
    CursorGotoxy(20, 7);
    printf("->图 书 查 询\n");
    CursorGotoxy(20, 9);
    printf("  我 的 信 息\n");
    CursorGotoxy(20, 11);
    printf("  统 计 数 据\n");
    CursorGotoxy(20, 13);
    printf("  退 出");
    index = 1;
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("方向键上/下：选择项目      ENTER：确认选择      ESC：退出程序");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1){
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            ProgramExit();
        case ENTER:
            switch(index) {
            case 1:
                CursorGotoxy(20, 7);
                printf("->输入搜索关键字：");
                fflush(stdin);
                scanf("%s", key);
                ShowSearchBykey(license, key);
                goto START;
            case 2:
                ShowMyAccountInfo(license);
                goto START;
            case 3:
                ShowStatistics(license);
                goto START;
            case 4:
                return;
            }
            break;
        case UP:
            if (index == 1) {
                break;
            }
            CursorGotoxy(20, index*2+3); 
            printf("->");
            CursorGotoxy(20, index*2+5);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == 4) {
                break;
            }
            CursorGotoxy(20, index*2+5); 
            printf("  ");
            CursorGotoxy(20, index*2+7);
            printf("->"); 
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }
}

void ShowMyAccountInfo(int license)
{
    int cnt = 0;
    char temp[PW_LEN];
    int index;
    char ch;
    char c2;
    
    START:
    system("cls");
    ShowHeadInfo(license);
    
    ShowAccountInfo(license);
    CursorGotoxy(45, 7);
    printf("->显示此账号当前借阅\n");
    CursorGotoxy(45, 9);
    printf("  修改登录密码\n");
    CursorGotoxy(45, 11);
    printf("  返回上级菜单");
    index = 1;
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("方向键上/下：选择项目      ENTER：确认选择      ESC：退出程序");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1){
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            switch(index) {
            case 1:
                ShowLicenseLent(license, license);
                goto START;
            case 2:
                CursorGotoxy(45, 9);
                printf("->修改值：                   \n");
                CursorGotoxy(55, 9);
                while(cnt < 17 && (ch = getch()) != ENTER)
                {
                    if (ch != BACKSPACE) {
                        temp[cnt++] = ch;
                        printf("*");
                    }
                    else {
                        if (cnt > 0) {
                            temp[--cnt] = 0;
                            printf("\b \b");
                        }
                    }
                }
                if (cnt == 17) {
                    cnt = 0;
                    CursorGotoxy(0, 4);
                    printf(" ！！密码长度过长！！");
                    CursorGotoxy(45, 9);
                    printf("->修改登录密码                           ");
                }
                else {
                    ChangePassword(license, temp);
                    return;
                }
                break; 
            case 3:
                return;
            }
            break;
        case UP:
            if (index == 1) {
                break;
            }
            CursorGotoxy(45, index*2+3); 
            printf("->");
            CursorGotoxy(45, index*2+5);
            printf("  "); 
            index --;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        case DOWN:
            if (index == 3) {
                break;
            }
            CursorGotoxy(45, index*2+5); 
            printf("  ");
            CursorGotoxy(45, index*2+7);
            printf("->"); 
            index ++;
            CursorGotoxy(LIMIT_X, LIMIT_Y);
            break;
        }
    }
}

void ShowStatistics(int license)
{
    tListStruct * sortList = NULL;
    tListNode *pNode;
    statistics_info *pStat;
    int cnt = 0;
    int index = 1;
    char c2;
    
    system("cls");
    ShowHeadInfo(license);
    
    sortList = GetStatisticsSort();
    pNode = GetListHead(sortList);
    CursorGotoxy(6, 4);
    printf("----------------------借出排行榜----------------------"); 
    CursorGotoxy(6, 6);
    printf("ISBN                  书名                  次数           ");
    while (pNode != NULL && cnt < 7) {
        CursorGotoxy(6, index*2+6);
        pStat = (statistics_info*)(pNode->data);
        pNode = GetListNext(pNode);
        if (GetTitleByISBN(pStat->isbn) != NULL) {
            printf("%-22s%-22s%-22d", pStat->isbn, GetTitleByISBN(pStat->isbn), pStat->lent_times);
            cnt += 1;
            index++;
        }
    }
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("ENTER / ESC：返回上级菜单");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    DeleteList(sortList, NULL, NULL);
    while(1){
        c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            return;
        }
    }
}
