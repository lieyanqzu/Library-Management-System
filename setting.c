/*******************************************************
 File name: setting.c
 
 Date: 2015.12.21
 
 Description: 关于借阅的一些配置信息 
    
 Dependency: 

 History: 
 
********************************************************/


#include <stdlib.h>

#include "setting.h"

Setting * setting = NULL;

Setting * GetSetting()
{
    if (NULL == setting) {
        setting = (Setting*)malloc(sizeof(Setting));
    }
    return setting;
}
