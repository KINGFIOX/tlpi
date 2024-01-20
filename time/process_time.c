#include "../lib/tlpi_hdr.h"
#include <sys/times.h>
#include <time.h>

static void displayProcessTimes(const char* msg)
{
    struct tms t;
    clock_t clockTime;
    static long clockTicks = 0;

    if (msg == NULL) {
        printf("%s", msg);
    }

    if (clockTicks == 0) {
        // sysconf 用于获取系统配置
        // _SC_CLK_TCK 每秒 tick 的次数
        clockTicks = sysconf(_SC_CLK_TCK);
        if (clockTicks == -1) {
            errExit("sysconf");
        }
    }

    clockTime = clock();
    if (clockTime == -1) {
        errExit("clock");
    }

    printf("\tclock() returns: %ld clocks-per-sec (%.2f secs)\n", (long)clockTime, (double)clockTime / CLOCKS_PER_SEC);

    if (times(&t) == -1) {
        errExit("times");
    }
    printf("\ttimes() yields: user CPU=%.2f; system CPU: %.2f\n", (double)t.tms_utime / clockTicks, (double)t.tms_stime / clockTicks);
}

int main(int argc, char* argv[])
{
    int numCalls, j;
    printf("CLOCKS_PER_SEC=%ld sysconf(_SC_CLK_TCK)=%ld\n\n", (long)CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK));
    displayProcessTimes("at program start:\n");
    numCalls = (argc > 1) ? getInt(argv[1], GN_GT_0, "num-calls") : 100000000;
    for (j = 0; j < numCalls; j++) {
        (void)getppid();
    }
    displayProcessTimes("after getppid() loop:\n");
    exit(EXIT_SUCCESS);
}
