/*******************************************************
 File name: test.c
 
 Date: 2015.12.3
 
 Description: 为编写模块进行单元测试 

 History: 1、2015.12.4 重写list_node模块测试 
    2、2015.12.5 测试代码分离至unit_test 
 
********************************************************/

//#define DEBUG_MODE
#ifdef DEBUG_MODE

#include <stdio.h>

#include "unit_test.h"

int main(int argc, char* argv[])
{
    // list_node测试
    testListNode();
    printf("list_node test passed!\n");

    // book测试
    testBook();
    printf("book test passed!\n");


    // book_lent测试
    testBookLent();
    printf("book_lent test passed!\n");

    // account测试
    testAccount();
    printf("account test passed!\n");

    return 0;
}

#endif

