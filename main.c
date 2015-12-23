#define RELEASE_MODE
#ifdef RELEASE_MODE

#include <windows.h> 

#include "file.h"
#include "interact.h"
#include "operation.h"

#define TITLE_NAME "图书管理系统 v1.0"

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
    // 读入文件 
    InitializeBook();
    InitializeBookLent();
    InitializeAccount();
    InitializeSetting();
    InitializeStatistics();
    // 修改控制台标题 
    SetConsoleTitle(TITLE_NAME);
}

static void AllIsDone()
{
    // 删除链表释放内存 
    DeleteBookList();
    DeleteBookLentList();
    DeleteAccountList();
    DeleteStatisticsList();
}

#endif
