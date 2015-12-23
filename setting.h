/*******************************************************
 File name: setting.h
 
 Date: 2015.12.21
 
 Description: 关于借阅的一些配置信息 
    
 Dependency: 

 History: 
 
********************************************************/


#ifndef _SETTING_H_
#define _SETTING_H_

typedef struct {
    int teacher_borrow_number; // 可借书籍数量 
    int student_borrow_number;
    int teacher_renew_times; // 可续借次数 
    int student_renew_times;
    double fine_per_day; // 超期每天罚金 
} Setting;

Setting * GetSetting();

#endif
