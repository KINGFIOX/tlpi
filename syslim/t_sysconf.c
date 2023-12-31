#include "../lib/tlpi_hdr.h"

static void sysconfPrint(const char* msg, int name)
{
    errno = 0;
    long lim = sysconf(name);
    if (lim != -1) {
        printf("%s %ld\n", msg, lim);
    } else {
        if (errno == 0) {
            printf("%s (indeterminate)\n", msg);
        } else {
            errExit("sysconf %s", msg);
        }
    }
}

int main(int argc, char* argv[])
{
    sysconfPrint("_SC_ARG_MAX:\t", _SC_ARG_MAX);
    sysconfPrint("_SC_LOGIN_NAME_MAX:\t", _SC_LOGIN_NAME_MAX);
    sysconfPrint("_SC_OPEN_MAX:\t", _SC_OPEN_MAX);
    sysconfPrint("_SC_NGROUPS_MAX:\t", _SC_NGROUPS_MAX);
    sysconfPrint("_SC_PAGESIZE:\t", _SC_PAGESIZE);
    sysconfPrint("_SC_RTSIG_MAX:\t", _SC_RTSIG_MAX);
    exit(EXIT_SUCCESS);
}