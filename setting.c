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
