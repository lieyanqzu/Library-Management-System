#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#include "account.h"
#include "file.h"
#include "setting.h"
#include "operation.h"

#include "interact.h"

#define LIMIT_X 79
#define LIMIT_Y 24
#define PER_PAGE 8

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
    char * str1 = "��ӭʹ��ͼ�����ϵͳ";
    char * str2 = "��ǰ�û���";
    char * str3 = "δ��¼";
    char buf[10];
    int len_license = 0;
    int len = (int)strlen(str2);
    int user_start_point;
    int tag_start_point;

    if (license == 0) {
        CursorGotoxy(25, 0);
        printf("%s", str1);
        CursorGotoxy(70, 0);
        printf("��%s", str3);
        printf("\n�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
    }
    else {
        sprintf(buf, "%d", license);
        len_license = (int)strlen(buf);
        user_start_point = LIMIT_X-len-len_license-2;
        tag_start_point = user_start_point/2-10;
        CursorGotoxy(tag_start_point, 0);
        printf("%s", str1);
        CursorGotoxy(user_start_point, 0);
        printf("��%s%d", str2, license);
        printf("\n�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T\n");
    }
}

void ShowLogin()
{
    int license;
    char temp[17];
    int cnt = 0;
    char ch;
    char * pw = NULL;
    tListNode *pNode = NULL;

    system("cls");
    while (1) {
        ShowHeadInfo(0);
        CursorGotoxy(12, 12);
        printf("�������˺�\n");
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
        printf(" �������˺Ų����ڣ���");
    }

    while (1) {
        CursorGotoxy(12, 14);
        printf("����������\n");
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
            printf(" �������볤�ȹ�������");
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
                printf(" ��������������󣡣�");
            }
        }
    }

    ShowMain(license);
}

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

void ShowMainForUser(int license)
{
    int index;
    START:
    system("cls");
    ShowHeadInfo(license);
    
    CursorGotoxy(20, 7);
    printf("->ͼ �� �� ѯ\n");
    CursorGotoxy(20, 9);
    printf("  �� �� �� Ϣ\n");
    CursorGotoxy(20, 11);
    printf("  ͳ �� �� ��\n");
    CursorGotoxy(20, 13);
    printf("  �� ��");
    index = 1;
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("�������/�£�ѡ����Ŀ      ENTER��ȷ��ѡ��      ESC���˳�����");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1){
        char c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            ProgramExit();
        case ENTER:
            switch(index) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
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

void ShowMainForAdmin(int license)
{
    int index;
    START:
    system("cls");
    ShowHeadInfo(license);
    
    CursorGotoxy(20, 7);
    printf("->ͼ �� �� ��\n");
    CursorGotoxy(20, 9);
    printf("  �� �� �� ��\n");
    CursorGotoxy(20, 11);
    printf("  ͳ �� �� ��\n");
    CursorGotoxy(20, 13);
    printf("  ϵ ͳ �� ��\n");
    CursorGotoxy(20, 15);
    printf("  �� ��");
    index = 1;
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("�������/�£�ѡ����Ŀ      ENTER��ȷ��ѡ��      ESC���˳�����");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1){
        char c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            ProgramExit();
        case ENTER:
            switch(index) {
            case 1:
                break;
            case 2:
                ShowAccount(license); 
                goto START;
            case 3:
                break;
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
    Setting * set = GetSetting();
    
    system("cls");
    ShowHeadInfo(license);
    
    CursorGotoxy(20, 7);
    printf("->��ʦ������������ǰ%d��\n", set->teacher_borrow_number);
    CursorGotoxy(20, 9);
    printf("  ѧ��������������ǰ%d��\n", set->student_borrow_number);
    CursorGotoxy(20, 11);
    printf("  ��ʦ��������������ǰ%d��\n", set->teacher_renew_times);
    CursorGotoxy(20, 13);
    printf("  ѧ����������������ǰ%d��\n", set->student_renew_times);
    CursorGotoxy(20, 15);
    printf("  ����δ��ÿ�췣��������ǰ%.2f��\n", set->fine_per_day);
    CursorGotoxy(20, 17);
    printf("  �����ϼ��˵�");
    index = 1;
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("�������/�£�ѡ����Ŀ      ENTER��ȷ��ѡ��      ESC�������ϼ��˵�");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1){
        char c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            switch(index) {
            case 1:
                CursorGotoxy(20, index*2+5);
                printf("->�޸�ֵ��                                        ");
                CursorGotoxy(30, index*2+5);
                scanf("%d", &num);
                if (num > 0) {
                    set->teacher_borrow_number = num;
                    WriteSetting();
                }
                CursorGotoxy(20, index*2+5);
                printf("->��ʦ������������ǰ%d��\n", set->teacher_borrow_number);
                CursorGotoxy(LIMIT_X, LIMIT_Y);
                break;
            case 2:
                CursorGotoxy(20, index*2+5);
                printf("->�޸�ֵ��                                        ");
                CursorGotoxy(30, index*2+5);
                scanf("%d", &num);
                if (num > 0) {
                    set->student_borrow_number = num;
                    WriteSetting();
                }
                CursorGotoxy(20, index*2+5);
                printf("->ѧ��������������ǰ%d��\n", set->student_borrow_number);
                CursorGotoxy(LIMIT_X, LIMIT_Y);
                break;
            case 3:
                CursorGotoxy(20, index*2+5);
                printf("->�޸�ֵ��                                        ");
                CursorGotoxy(30, index*2+5);
                scanf("%d", &num);
                if (num > 0) {
                    set->teacher_renew_times = num;
                    WriteSetting();
                }
                CursorGotoxy(20, index*2+5);
                printf("->��ʦ��������������ǰ%d��\n", set->teacher_renew_times);
                CursorGotoxy(LIMIT_X, LIMIT_Y);
                break;
            case 4:
                CursorGotoxy(20, index*2+5);
                printf("->�޸�ֵ��                                        ");
                CursorGotoxy(30, index*2+5);
                scanf("%d", &num);
                if (num > 0) {
                    set->student_renew_times = num;
                    WriteSetting();
                }
                CursorGotoxy(20, index*2+5);
                printf("->ѧ����������������ǰ%d��\n", set->student_renew_times);
                CursorGotoxy(LIMIT_X, LIMIT_Y);
                break;
            case 5:
                CursorGotoxy(20, index*2+5);
                printf("->�޸�ֵ��                                        ");
                CursorGotoxy(30, index*2+5);
                scanf("%lf", &fine);
                if (fine > 0.0) {
                    set->fine_per_day = fine;
                    WriteSetting();
                }
                CursorGotoxy(20, index*2+5);
                printf("->����δ��ÿ�췣��������ǰ%.2f��\n", set->fine_per_day);
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
    START:
    system("cls");
    ShowHeadInfo(license);
    
    CursorGotoxy(20, 7);
    printf("->������Ϣһ��\n");
    CursorGotoxy(20, 9);
    printf("  ����������Ϣ\n");
    CursorGotoxy(20, 11);
    printf("  ������Ϣ��ѯ���޸ģ�\n");
    CursorGotoxy(20, 13);
    printf("  �����ϼ��˵�");
    index = 1;
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("�������/�£�ѡ����Ŀ      ENTER��ȷ��ѡ��      ESC�������ϼ��˵�");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1){
        char c2 = getch();
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
                printf("->�����ѯ�˺ţ�     \b\b\b\b\b");
                fflush(stdin);
                scanf("%d", &need_license);
                pNode = SearchAccountByLicense(need_license);

                if (pNode !=  NULL) {
                    ShowAccountSearch(license, need_license);
                }
                else {
                    CursorGotoxy(0, 4);
                    printf(" �������˺Ų����ڣ���");
                    CursorGotoxy(20, index*2+5);
                    printf("->������Ϣ��ѯ���޸ģ�                          \n");
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
    int size;
    int index = 1;
    int page = 0;
    int num;
    
    if (pList->length % PER_PAGE == 0) {
        size = pList->length / PER_PAGE;
    }
    else {
        size = pList->length / PER_PAGE + 1;
    }
    
    pNodeArray = (tListNode**)malloc(sizeof(tListNode*)*size);
    ListNodeSplit(pList, pNodeArray, size);
    
    while(1) {
        num = ShowAccountPage(license, pNodeArray[page]);
        CursorGotoxy(4, index*2+4); 
        printf("->");
        char c2 = getch();
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            break;
        case UP:
            if (index == 1) {
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
            if (index == num) {
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
        case RIGHT:
            if (page == size-1) {
                break;
            }
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
    printf("  �˺�              ����              �༶              ���              ");
    for (i = 0; i < PER_PAGE && pNode != NULL; i++) {
        get_license = GetLicenseByNode(pNode);
        strncpy(name, (char*)GetAccountInfo(get_license, NAME), STR_LEN-1);
        strncpy(classes, (char*)GetAccountInfo(get_license, CLASSES), STR_LEN-1);
        rank = *(AccountRank*)GetAccountInfo(get_license, RANK);
        CursorGotoxy(4, i*2+6); 
        printf("  %-18d%-18s%-18s", get_license, name, classes);
        switch (rank) {
        case STUDENT:
            printf("ѧ��");
            break;
        case TEACHER:
            printf("��ʦ");
            break;
        case ADMIN:
            printf("����Ա");
            break;
        case LOSS:
            printf("��ʧ��");
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
        printf("1.ѧ��\t2.��ʦ");
        CursorGotoxy(20, 8);
        printf("���");
        fflush(stdin);
        scanf("%d", &temprank);
        
        if (temprank != 1 && temprank != 2) {
            CursorGotoxy(0, 4);
            printf(" ����������1��2����");
            CursorGotoxy(20, 8);
            printf("���:                    ");
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
        printf("�˺ţ�");
        fflush(stdin);
        scanf("%d", &new_license);

        pNode = SearchAccountByLicense(new_license);

        if (pNode !=  NULL) {
            CursorGotoxy(0, 4);
            printf(" �����˺��Ѿ����ڣ���");
            CursorGotoxy(20, 10);
            printf("�˺ţ�                        ");
            CursorGotoxy(26, 10);
        }
        else {
            break;
        }
    }
    
    CursorGotoxy(20, 12);
    printf("������");
    fflush(stdin);
    scanf("%s", &name);
    
    if (rank != TEACHER) {
        CursorGotoxy(20, 14);
        printf("�༶��");
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
    printf("�˺ţ�%d\n", need_license);
    CursorGotoxy(6, 9);
    strcpy(name, (char*)GetAccountInfo(need_license, NAME));
    printf("������%s\n", name);
    CursorGotoxy(6, 11);
    strcpy(classes, (char*)GetAccountInfo(need_license, CLASSES));
    printf("�༶��%s\n", classes);
    CursorGotoxy(6, 13);
    printf("���");
    rank = *(AccountRank*)GetAccountInfo(need_license, RANK);
    switch (rank) {
    case STUDENT:
        printf("ѧ��");
        break;
    case TEACHER:
        printf("��ʦ");
        break;
    case ADMIN:
        printf("����Ա");
        break;
    case LOSS:
        printf("��ʧ��");
        break;
    }
}

void ShowAccountSearch(int license, int need_license)
{
    int index;
    char tempch;
    char name[STR_LEN];
    char classes[STR_LEN];
    START:
    system("cls");
    ShowHeadInfo(license);
    ShowAccountInfo(need_license);
    
    CursorGotoxy(45, 7);
    printf("->�޸Ķ�������\n");
    CursorGotoxy(45, 9);
    printf("  �޸Ķ��߰༶\n");
    CursorGotoxy(45, 11);
    printf("  ��ʧ�˺Ż�ȡ��\n");
    CursorGotoxy(45, 13);
    printf("  �ָ���Ĭ������\n");
    CursorGotoxy(45, 15);
    printf("  ע�����˺�\n");
    CursorGotoxy(45, 17);
    printf("  �����ϼ��˵�");
    index = 1;
    
    CursorGotoxy(0, LIMIT_Y); 
    printf("�������/�£�ѡ����Ŀ      ENTER��ȷ��ѡ��      ESC�������ϼ��˵�");
    CursorGotoxy(LIMIT_X, LIMIT_Y);
    
    while(1){
        char c2 = getch();
        
        switch ((KeyNum)c2) {
        case ESC:
            return;
        case ENTER:
            switch(index) {
            case 1:
                CursorGotoxy(45, 7);
                printf("->�޸�ֵ��     \b\b\b\b\b");
                fflush(stdin);
                scanf("%s", name);
                ModifyAccountInfo(need_license, (void*)name, NAME);
                WriteAccountFile();
                goto START;
            case 2:
                CursorGotoxy(45, 9);
                printf("->�޸�ֵ��     \b\b\b\b\b");
                fflush(stdin);
                scanf("%s", classes);
                ModifyAccountInfo(need_license, (void*)classes, CLASSES);
                WriteAccountFile();
                goto START;
            case 3:
                CursorGotoxy(45, 11);
                printf("->ȷ�Ϲ�ʧ��ȡ���𣿣�Y/N��");
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
            case 4:
                CursorGotoxy(45, 13);
                printf("->ȷ�ϻָ���Ĭ�����룿��Y/N��");
                fflush(stdin);
                scanf("%c", &tempch);
                if (tempch == 'Y' || tempch == 'y') {
                    ChangePasswordToDefault(need_license);
                    return;
                }
                else {
                    goto START;
                }
            case 5:
                CursorGotoxy(45, 15);
                printf("->ȷ��ע�����˺ţ���Y/N��");
                fflush(stdin);
                scanf("%c", &tempch);
                if (tempch == 'Y' || tempch == 'y') {
                    CancelAccount(need_license);
                    return;
                } 
                else {
                    goto START;
                }
            case 6:
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
            if (index == 6) {
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

int ProgramExit()
{
    exit(0);
}
