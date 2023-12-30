# chap6 - 进程

## 环境变量

### setenv

`setenv` 函数用于设置环境变量的值。它允许你在程序运行时动态地修改当前进程的环境变量。`setenv` 的函数原型如下：

```c
#include <stdlib.h>

int setenv(const char *name, const char *value, int overwrite);
```

- `name` 是要设置的环境变量的名称。
- `value` 是要为环境变量设置的新值。
- `overwrite` 指定是否允许覆盖已存在的同名环境变量。如果 `overwrite` 的值为非零，允许覆盖；如果为零，不允许覆盖。

下面是一个简单的示例，演示如何使用 `setenv` 设置和修改环境变量：

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // 设置环境变量 MY_VARIABLE 的值为 "Hello, World!"
    if (setenv("MY_VARIABLE", "Hello, World!", 1) != 0) {
        perror("setenv failed");
        return 1;
    }

    // 获取并打印环境变量 MY_VARIABLE 的值
    const char *value = getenv("MY_VARIABLE");
    if (value != NULL) {
        printf("MY_VARIABLE: %s\n", value);
    } else {
        printf("MY_VARIABLE not found\n");
    }

    // 修改环境变量 MY_VARIABLE 的值
    if (setenv("MY_VARIABLE", "New Value", 1) != 0) {
        perror("setenv failed");
        return 1;
    }

    // 再次获取并打印环境变量 MY_VARIABLE 的值
    value = getenv("MY_VARIABLE");
    if (value != NULL) {
        printf("Modified MY_VARIABLE: %s\n", value);
    } else {
        printf("MY_VARIABLE not found\n");
    }

    return 0;
}
```

在这个示例中，程序首先使用 `setenv` 设置环境变量 `MY_VARIABLE` 的值为 "Hello, World!"，然后通过 `getenv` 获取并打印该环境变量的值。接着，使用 `setenv` 修改 `MY_VARIABLE` 的值为 "New Value"，并再次获取并打印修改后的值。

## longjmp

### 例子

```c
#include "../lib/tlpi_hdr.h"
#include <setjmp.h>

static jmp_buf env;

static void f2(void)
{
    longjmp(env, 2);
}

static void f1(int argc)
{
    if (argc == 1) {
        longjmp(env, 1);
    }
    f2();
}

int main(int argc, char* argv[])
{
    switch (setjmp(env)) {
    case 0:
        printf("calling f1(0 after initial setjmp()\n)");
        f1(argc);
        break;
    case 1:
        printf("we jumped back from f1()\n)");
        break;
    case 2:
        printf("we jumped back from f2()\n)");
        break;
    }
    exit(EXIT_SUCCESS);
}
```

如果没有参数，那么 argc = 1。
那么调用顺序就是：setjmp(env) --> 0，然后进入 case0 的 f1 中;
f1 的 longjmp，伪返回 1，然后进入到 case1 的 printf

如果 argc = 2，
那么调用顺序就是：setjmp(en) --> 0，然后进入 case0 的 f1 中;
f1 又进入到 f2 中;
f2 的 longjmp，伪返回 0，然后进入到 case2 的 printf

### register

在现代的 C 和 C++ 标准中，`register` 关键字已经失去了它最初的意义，它仅仅是一个对编译器的建议，不再具有强制性。
在 C89 标准中，`register` 关键字是用来建议编译器将变量存储在寄存器中，以提高访问速度。
然而，在后续的 C 标准和 C++ 中，这个建议已经不再具备强制性。

在现代编译器中，编译器通常能够根据代码的上下文和优化策略自动选择合适的寄存器分配方案，因此程序员通常无需显式地使用 `register` 关键字。
实际上，使用 `register` 关键字可能对性能产生负面影响，因为编译器可能会忽略这个建议，而且寄存器的数量和用途也可能受到限制。

以下是一个简单的示例，演示了 `register` 关键字的使用：

```c
#include <stdio.h>

int main() {
    register int x = 10;  // 尝试将变量 x 存储在寄存器中

    printf("Value of x: %d\n", x);

    return 0;
}
```

然而，对于现代编译器而言，上述代码中使用 `register` 关键字并不会强制将 `x` 存储在寄存器中，编译器可能会忽略这个建议。
因此，程序员应当依赖于编译器的优化能力，而不是试图手动管理寄存器分配。
