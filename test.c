/*******************************************************
 File name: test.c
 
 Date: 2015.12.3
 
 Description: 为编写模块进行单元测试 

 History: 1、2015.12.4 重写list_node模块测试 
    2、2015.12.5 测试代码分离至unit_test 
 
********************************************************/


#include "unit_test.h"

int main(int argc, char* argv[])
{
    testListNode();
    
    return 0;
}
