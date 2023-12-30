#include "../lib/tlpi_hdr.h"
#include <stdlib.h>

#define MAX_ALLOCS 1000000

int main(int argc, char* argv[])
{
    char* ptr[MAX_ALLOCS];
    int freeStep, freeMin, freeMax, blockSize, numAllocs, j;

    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s num-allocs block-size [step [min [max]]]\n", argv[0]);
    }

    // 内存块的数量
    numAllocs = getInt(argv[1], GN_GT_0, "num-allocs");

    if (numAllocs > MAX_ALLOCS) {
        cmdLineErr("num-allocs > %d\n", MAX_ALLOCS);
    }

    // 内存块的大小
    blockSize = getInt(argv[2], GN_GT_0 | GN_ANY_BASE, "block-size");

    // 后面这个是 默认值;
    freeStep = (argc > 3) ? getInt(argv[3], GN_GT_0, "step") : 1;
    freeMin = (argc > 4) ? getInt(argv[4], GN_GT_0, "min") : 1;
    freeMax = (argc > 5) ? getInt(argv[5], GN_GT_0, "max") : numAllocs;

    // 打印初始的sbrk
    printf("initial program break:\t %10p\n", sbrk(0));

    // 要分配的 总的 内存大小
    printf("allocating %d*%d=%d bytes\n", numAllocs, blockSize, numAllocs * blockSize);

    for (j = 0; j < numAllocs; j++) {
        ptr[j] = malloc(blockSize);
        if (ptr[j] == NULL) {
            errExit("malloc");
        }
    }

    // 打印初始的sbrk
    printf("program break is now:\t %10p\n", sbrk(0));

    printf("freeing blocks from %d to %d in steps of %d\n", freeMin, freeMax, freeStep);

    for (j = freeMin - 1; j < freeMax; j += freeStep) {
        free(ptr[j]);
    }

    printf("after free(), program break is:\t %10p\n", sbrk(0));
    exit(EXIT_SUCCESS);
}