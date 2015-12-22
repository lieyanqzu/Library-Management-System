#ifndef _SETTING_H_
#define _SETTING_H_

typedef struct {
    int teacher_borrow_number;
    int student_borrow_number;
    int teacher_renew_times;
    int student_renew_times;
    double fine_per_day;
} Setting;

Setting * GetSetting();

#endif
