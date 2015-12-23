cmake_minimum_required(VERSION 3.3)
project(LMS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    account.c
    account.h
    book.c
    book.h
    book_lent.c
    book_lent.h
    list_node.c
    list_node.h
    test.c
    unit_test.c
    unit_test.h main.c interact.c interact.h file.c file.h operation.c operation.h)

add_executable(LMS ${SOURCE_FILES})