/*******************************************************
 File name: setting.c
 
 Date: 2015.12.21
 
 Description: ���ڽ��ĵ�һЩ������Ϣ 
    
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
