#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

void errMsg(const char* format, ...);

#ifdef __GUNC__
#define NORETURN __attribute__((__noreturn__))
#else
#define NORETURN
#endif

void errExit(const char* format, ...) NORETURN;

void err_exit(const char* format, ...) NORETURN;

void errExitEN(int errnum, const char* format, ...) NORETURN;

/* errMsg errExit err_exit errExitEN 用来诊断 系统调用 和 库函数 发生的错误 */

void fatal(const char* format, ...) NORETURN;

void usageErr(const char* format, ...) NORETURN;

void cmdLineErr(const char* format, ...) NORETURN;

#endif