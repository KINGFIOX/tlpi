#include "error_functions.h"
#include "ename.c.inc"
#include "tlpi_hdr.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __GUNC__
__attribute__((__noreturn__))
#endif

static void
terminate(Boolean useExit3)
{
    char* s;

    s = getenv("EF_DUMPCORE");

    // 是否有 dump core 。

    if (s != NULL && *s != '\0') {
        abort(); // 调用 abort() 才会有 core dump 文件
    } else {
        if (useExit3) {
            exit(EXIT_FAILURE);
        } else {
            _exit(EXIT_FAILURE);
        }
    }
}

/**
 * @brief 
 * 
 * @param useErr 
 * @param err 
 * @param flushStdout 
 * @param format 
 * @param ap 
 */
static void outputError(Boolean useErr, int err, Boolean flushStdout, const char* format, va_list ap)
{
#define BUF_SIZE 500
    char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];
    vsnprintf(userMsg, BUF_SIZE, format, ap);

    if (useErr) {
        snprintf(errText, BUF_SIZE, " [%s %s]",
            (err > 0 && err <= MAX_ENAME) ? ename[err] : "?UNKNOWN?", strerror(err));
    } else {
        snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);
    }

    if (flushStdout) {
        fflush(stdout);
    }
    fputs(buf, stderr);
    fflush(stderr);
}

void errMsg(const char* format, ...)
{
    va_list argList;
    int savedErrno;

    savedErrno = errno;

    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);

    errno = savedErrno;
}

void errExit(const char* format, ...)
{
    va_list argList;
    va_start(argList, format);
    outputError(TRUE, errno, TRUE, format, argList);
    va_end(argList);
    terminate(TRUE);
}

void err_exit(const char* format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errno, FALSE, format, argList);
    va_end(argList);

    terminate(FALSE);
}

void errExitEN(int errnum, const char* format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(TRUE, errnum, TRUE, format, argList);
    va_end(argList);

    terminate(TRUE);
}

void fatal(const char* format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(FALSE, 0, TRUE, format, argList);
    va_end(argList);

    terminate(TRUE);
}

void usageErr(const char* format, ...)
{
    va_list argList;
    fflush(stdout);

    fprintf(stderr, "Usage: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr);
    exit(EXIT_FAILURE);
}

void cmdLineErr(const char* format, ...)
{
    va_list argList;

    fflush(stdout);

    fprintf(stderr, "Command-line usage error: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr);
    exit(EXIT_FAILURE);
}