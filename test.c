/*******************************************************
 File name: test.c
 
 Date: 2015.12.3
 
 Description: Ϊ��дģ����е�Ԫ���� 

 History: 1��2015.12.4 ��дlist_nodeģ����� 
    2��2015.12.5 ���Դ��������unit_test 
 
********************************************************/

//#define DEBUG_MODE
#ifdef DEBUG_MODE

#include <stdio.h>

#include "unit_test.h"

int main(int argc, char* argv[])
{
    // list_node����
    testListNode();
    printf("list_node test passed!\n");

    // book����
    testBook();
    printf("book test passed!\n");


    // book_lent����
    testBookLent();
    printf("book_lent test passed!\n");

    // account����
    testAccount();
    printf("account test passed!\n");

    return 0;
}

#endif

