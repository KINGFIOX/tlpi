#include <stdio.h>
#include <stdlib.h>
#define __GNU_SOURCE
#include "../lib/tlpi_hdr.h"
#include "../users_groups/ugid_functions.h"
#include <limits.h>
#include <sys/fsuid.h>
#include <unistd.h>

#define SG_SIZE (NGROUPS_MAX + 1)

int main(int argc, char* argv[])
{
    uid_t ruid, euid, suid, fsuid;
    gid_t rgid, egid, sgid, fsgid;
    gid_t suppGroups[SG_SIZE];
    int numGroups, j;
    char* p;

    if (getresuid(&ruid, &euid, &suid) == -1) {
        errExit("getresuid");
    }
    if (getresgid(&rgid, &egid, &sgid) == -1) {
        errExit("getresgid");
    }

    fsuid = setfsuid(0);
    fsgid = setfsgid(0);

    printf("UID: ");
    p = userNameFromId(ruid);
    printf("real=%s (%ld); ", (p == NULL) ? "???" : p, (long)ruid);
    p = userNameFromId(euid);
    printf("eff=%s (%ld); ", (p == NULL) ? "???" : p, (long)euid);
    p = userNameFromId(suid);
    printf("saved=%s (%ld); ", (p == NULL) ? "???" : p, (long)suid);
    p = userNameFromId(fsuid);
    printf("fs=%s (%ld); ", (p == NULL) ? "???" : p, (long)fsuid);

    printf("GID: ");
    p = userNameFromId(ruid);
    printf("real=%s (%ld); ", (p == NULL) ? "???" : p, (long)rgid);
    p = userNameFromId(euid);
    printf("eff=%s (%ld); ", (p == NULL) ? "???" : p, (long)egid);
    p = userNameFromId(suid);
    printf("saved=%s (%ld); ", (p == NULL) ? "???" : p, (long)sgid);
    p = userNameFromId(fsuid);
    printf("fs=%s (%ld); ", (p == NULL) ? "???" : p, (long)fsgid);

    numGroups = getgroups(SG_SIZE, suppGroups);
    if (numGroups == -1) {
        errExit("getgroups");
    }

    printf("supplementary groups (%d): ", numGroups);
    for (j = 0; j < numGroups; j++) {
        p = groupNameFromId(suppGroups[j]);
        printf("%s (%ld); ", (p == NULL) ? "???" : p, (long)suppGroups[j]);
    }
    printf("\n");

    exit(EXIT_SUCCESS);
}