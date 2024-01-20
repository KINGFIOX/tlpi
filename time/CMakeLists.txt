cmake_minimum_required(VERSION 3.18)

project(time)

# 头文件路径
set(inc "../lib")
include_directories(${inc})

aux_source_directory("../lib" SRC)

file(GLOB H_FILE "${inc}/*.h*")

message("H_FILE = ${H_FILE}")

# 创建可执行文件
add_executable(calendar ${SRC} ${H_FILE} calendar_time.c)

add_executable(process_time ${SRC} ${H_FILE} process_time.c)

