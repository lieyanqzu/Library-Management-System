/*******************************************************
 File name: file.h 
 
 Date: 2015.12.21
 
 Description: �������ļ��Ĳ��� 
    
 Dependency: book book_lent account setting statistics

 History: 2015.12.22 ���� Setting��Statistics
 
********************************************************/


#ifndef _FILE_H_
#define _FILE_H_

// д���ļ� 
void WriteBookFile();
void WriteBookLentFile();
void WriteAccountFile();
void WriteSetting();
void WriteStatistics();

// ��ȡ�ļ���ʼ������ 
void InitializeBook();
void InitializeBookLent();
void InitializeAccount();
void InitializeSetting();
void InitializeStatistics();

#endif
