#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// 返回 group 的用户
char* userNameFromId(uid_t uid)
{
    struct passwd* pwd;
    pwd = getpwuid(uid);
    return (pwd == NULL) ? NULL : pwd->pw_name;
}

//
uid_t userIdFromName(const char* name)
{
    struct passwd* pwd;
    uid_t u;
    char* endptr;

    // 无效输入
    if (name == NULL || *name == '\0') {
        return -1;
    }

    // str to l 将str转为long
    // endptr 剩余的字符串放到endptr中，将endptr指向"剩余部分"
    // 10 表示 十进值
    u = strtol(name, &endptr, 10);

    // 读取完了
    if (*endptr == '\0') {
        return u;
    }

    // get password name
    pwd = getpwnam(name);
    if (pwd == NULL) {
        return -1;
    }

    return pwd->pw_uid;
}

char* groupNameFromId(gid_t gid)
{
    struct group* grp;
    grp = getgrgid(gid);
    return (grp == NULL) ? NULL : grp->gr_name;
}

gid_t groupIdFromName(const char* name)
{
    struct group* grp;
    gid_t g;
    char* endptr;

    if (name == NULL || *name == '\0') {
        return -1;
    }

    g = strtol(name, &endptr, 10);

    if (*endptr == '\0') {
        return g;
    }

    grp = getgrnam(name);
    if (grp == NULL) {
        return -1;
    }

    return grp->gr_gid;
}