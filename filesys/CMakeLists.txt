cmake_minimum_required(VERSION 3.18)

project(filesys)

# 头文件路径
set(inc "../lib")
include_directories(${inc})

aux_source_directory("../lib" SRC)

file(GLOB H_FILE "${inc}/*.h*")

message("H_FILE = ${H_FILE}")

# 创建可执行文件
add_executable(t_mount ${SRC} ${H_FILE} t_mount.c)
