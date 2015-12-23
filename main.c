#define RELEASE_MODE
#ifdef RELEASE_MODE

#include <windows.h> 

#include "file.h"
#include "interact.h"
#include "operation.h"

#define TITLE_NAME "ͼ�����ϵͳ v1.0"

static void Prepare();
static void AllIsDone();

int main(int argc, char* argv[])
{
    Prepare();
    ShowLogin();
    return 0;
}

static void Prepare()
{
    // �����ļ� 
    InitializeBook();
    InitializeBookLent();
    InitializeAccount();
    InitializeSetting();
    InitializeStatistics();
    // �޸Ŀ���̨���� 
    SetConsoleTitle(TITLE_NAME);
}

static void AllIsDone()
{
    // ɾ�������ͷ��ڴ� 
    DeleteBookList();
    DeleteBookLentList();
    DeleteAccountList();
    DeleteStatisticsList();
}

#endif
