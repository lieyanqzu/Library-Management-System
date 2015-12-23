/*******************************************************
 File name: file.h 
 
 Date: 2015.12.21
 
 Description: 包含对文件的操作 
    
 Dependency: book book_lent account setting statistics

 History: 2015.12.22 增加 Setting、Statistics
 
********************************************************/


#ifndef _FILE_H_
#define _FILE_H_

// 写入文件 
void WriteBookFile();
void WriteBookLentFile();
void WriteAccountFile();
void WriteSetting();
void WriteStatistics();

// 读取文件初始化链表 
void InitializeBook();
void InitializeBookLent();
void InitializeAccount();
void InitializeSetting();
void InitializeStatistics();

#endif
