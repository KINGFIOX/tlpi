#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

static jmp_buf env;

static void doJmp(int nvar, int rvar, int vvar)
{
    printf("inside doJmp(): nvar=%d rvar=%d vvar=%d\n", nvar, rvar, vvar);
    longjmp(env, 1);
}

int main(int argc, char* argv[])
{
    int nvar;
    register int rvar;
    volatile int vvar;

    nvar = 111;
    rvar = 222;
    vvar = 333;

    if (setjmp(env) == 0) {
        nvar = 777;
        rvar = 888;
        vvar = 999;
        doJmp(nvar, rvar, vvar);
    } else {
        printf("after doJmp(): nvar=%d rvar=%d vvar=%d\n", nvar, rvar, vvar);
    }

    exit(EXIT_SUCCESS);
}