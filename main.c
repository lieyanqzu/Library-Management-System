#include "file.h"
#include "interact.h"

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
    InitializeBook();
    InitializeBookLent();
    InitializeAccount();
    InitializeSetting();
}

