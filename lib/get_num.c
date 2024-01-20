#include "get_num.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 打印错误信息
 * 
 * @param fname 接受文件名 "getLong"
 * @param msg 错误消息
 * @param arg 
 * @param name 
 */
static void gnFail(const char* fname, const char* msg, const char* arg, const char* name)
{
    fprintf(stderr, "%s error", fname);
    if (name != NULL) {
        fprintf(stderr, " (in %s)", name);
    }
    fprintf(stderr, ": %s\n", msg);
    if (arg != NULL && *arg != '\0') {
        fprintf(stderr, "\toffending text: %s\n", arg);
    }
    exit(EXIT_FAILURE);
}

/**
 * @brief 获得数字，也有进制
 * 
 * @param fname 
 * @param arg 
 * @param flags 
 * @param name 
 * @return long 
 */
static long getNum(const char* fname, const char* arg, int flags, const char* name)
{
    long res;
    char* endptr;
    int base;

    if (arg == NULL || *arg == '\0') {
        gnFail(fname, "null or empty string", arg, name);
    }

    // 进制
    base = (flags & GN_ANY_BASE) ? 0 : (flags & GN_BASE_8) ? 8
        : (flags & GN_BASE_16)                             ? 16
                                                           : 10;

    errno = 0;

    // base是进制
    res = strtol(arg, &endptr, base); // str to long
    if (errno != 0) {
        gnFail(fname, "strtol() failed", arg, name);
    }

    if (*endptr != '\0') {
        gnFail(fname, "nonnumeric characters", arg, name);
    }

    if ((flags & GN_NONNEG) && res < 0) {
        gnFail(fname, "negative value not allowed", arg, name);
    }

    if ((flags & GN_GT_0) && res <= 0) {
        gnFail(fname, "value must be > 0", arg, name);
    }

    return res;
}

long getLong(const char* arg, int flags, const char* name)
{
    return getNum("getLong", arg, flags, name);
}

int getInt(const char* arg, int flags, const char* name)
{
    long res;

    res = getNum("getInt", arg, flags, name);
    // 防止越界
    if (res > INT_MAX || res < INT_MIN) {
        gnFail("getInt", "integer out of range", arg, name);
    }

    return (int)res;
}