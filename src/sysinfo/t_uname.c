#include <stdio.h>
#define _GUN_SOURCE
#include "../lib/tlpi_hdr.h"
#include <sys/utsname.h>

int main(int argc, char* argv[])
{
    struct utsname uts;

    if (uname(&uts) == -1) {
        errExit("uname");
    }

    printf("Node name:\t%s\n", uts.nodename);
    printf("system name:\t%s\n", uts.sysname);
    printf("release:\t%s\n", uts.release);
    printf("version:\t%s\n", uts.version);
    printf("machine:\t%s\n", uts.machine);

#ifdef _GUN_SOURCE
    printf("domain name: %s\n", uts.domainname);
#endif
    exit(EXIT_SUCCESS);
}