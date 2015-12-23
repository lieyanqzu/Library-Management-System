/*******************************************************
 File name: setting.h
 
 Date: 2015.12.21
 
 Description: ���ڽ��ĵ�һЩ������Ϣ 
    
 Dependency: 

 History: 
 
********************************************************/


#ifndef _SETTING_H_
#define _SETTING_H_

typedef struct {
    int teacher_borrow_number; // �ɽ��鼮���� 
    int student_borrow_number;
    int teacher_renew_times; // ��������� 
    int student_renew_times;
    double fine_per_day; // ����ÿ�췣�� 
} Setting;

Setting * GetSetting();

#endif
