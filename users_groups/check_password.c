#include <stdlib.h>
#define __BSD_SOURCE
#define _XOPEN_SOURCE
#include "../lib/tlpi_hdr.h"
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char *username, *password, *encrypted, *p;
    struct passwd* pwd;
    struct spwd* spwd;
    Boolean authOk;
    size_t len;

    // sysconf 用于获取系统配置信息
    // _SC_LOGIN_NAME_MAX 标识符，表示登录名的最大长度
    // 这样可以 获得 全部的登录名的最大长度
    long lnmax = sysconf(_SC_LOGIN_NAME_MAX);

    if (lnmax == -1) {
        lnmax = 256;
    }
    username = malloc(lnmax);

    if (username == NULL) {
        errExit("malloc");
    }

    // 获取用户名
    printf("Username: ");
    fflush(stdout);
    if (fgets(username, lnmax, stdin) == NULL) {
        exit(EXIT_FAILURE);
    }

    len = strlen(username);
    if (username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    // get password name
    pwd = getpwnam(username);
    if (pwd == NULL) {
        fatal("could not get password record");
    }
    // getspnam
    spwd = getspnam(username);
    if (spwd == NULL && errno == EACCES) {
        fatal("no permission to read shadow password file");
    }

    if (spwd != NULL) {
        pwd->pw_passwd = spwd->sp_pwdp;
    }
    password = getpass("Password: ");

    // crypt 关闭回显功能，并加密
    encrypted = crypt(password, pwd->pw_passwd);
    for (p = password; *p != '\0';) {
        *p++ = '\0';
    }

    if (encrypted == NULL) {
        errExit("crypt");
    }

    authOk = strcmp(encrypted, pwd->pw_passwd);
    if (!authOk) {
        printf("incorrect password\n");
        exit(EXIT_FAILURE);
    }

    printf("successfully authenticated: UID=%ld\n", (long)pwd->pw_uid);
    exit(EXIT_SUCCESS);
}