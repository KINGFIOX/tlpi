#include "../lib/tlpi_hdr.h"
#include <locale.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define SECONDS_IN_TROPICAL_YEAR (365.24219 * 24 * 60 * 60)

int main(int argc, char* argv[])
{
    time_t t;
    struct tm *gmp, *locp;
    struct tm gm, loc;
    struct timeval tv;

    time(NULL);
    printf("seconds since the ecpoch(1 Jan 1970): %ld", (long)t);
    printf("(about %6.3f years)\n", t / SECONDS_IN_TROPICAL_YEAR);

    if (gettimeofday(&tv, NULL) == -1) {
        errExit("gettimeofday");
    }
    printf("  gettimeofday() returned %ld secs, %ld microsecs\n", (long)tv.tv_sec, (long)tv.tv_usec);

    gmp = gmtime(&t);
    if (gmp == NULL) {
        errExit("gmtime");
    }

    gm = *gmp; // 保存

    printf("broken down by gmtime(): \n");
    printf("  year=%d mon=%d mday=%d hour=%d min=%d sec=%d", gm.tm_year, gm.tm_mon, gm.tm_mday, gm.tm_hour, gm.tm_min, gm.tm_sec);
    printf("wday=%d yday=%d isdst=%d\n", gm.tm_wday, gm.tm_yday, gm.tm_isdst);

    loc = *locp;

    printf("broken down by localtime():\n");
}