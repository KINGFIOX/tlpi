# chap4 - 通用的 IO 模型

## 权限

### S_IRUSR

"S_IRUSR" 是一个宏，通常用于 C 语言中的文件权限设置，特别是在使用 `chmod` 函数时。这个宏表示文件所有者（owner）具有读取权限（Read）。在文件权限中，有三个主要的权限类别：文件所有者、文件所属组和其他用户。

具体而言，"S_IRUSR" 的含义如下：

- "S\_": 这是一个常见的前缀，表示这是一个权限相关的宏。
- "IR": 表示读权限（Read）。
- "USR": 表示用户（User），即文件的所有者。

因此，"S_IRUSR" 就表示文件所有者具有读取权限。在使用 `chmod` 函数时，你可以将这个宏与其他权限宏组合使用，以设置文件的不同权限。例如，"S_IRUSR | S_IWUSR" 表示文件所有者具有读写权限。

### S_IWUSR

"S_IWUSR" 是一个宏，通常用于 C 语言中的文件权限设置，特别是在使用 `chmod` 函数时。这个宏表示文件所有者（owner）具有写入权限（Write）。在文件权限中，有三个主要的权限类别：文件所有者、文件所属组和其他用户。

具体而言，"S_IWUSR" 的含义如下：

- "S\_": 这是一个常见的前缀，表示这是一个权限相关的宏。
- "IW": 表示写入权限（Write）。
- "USR": 表示用户（User），即文件的所有者。

因此，"S_IWUSR" 就表示文件所有者具有写入权限。在使用 `chmod` 函数时，你可以将这个宏与其他权限宏组合使用，以设置文件的不同权限。例如，"S_IRUSR | S_IWUSR" 表示文件所有者具有读写权限。

## 空洞文件

空洞文件是有作用的。

比方说，我们打开的文件，他的大小或许只有 4k（如果是 windows 的文件系统，或许有 4k 对齐）。
但是假如我们使用 lseek，offset=6000，他就会偏移超出文件，那么 4096 到 6000 这段，就是空洞。
比方说，我们进行多线程的下载，下载 4 个 G 的文件，每个线程 1G。如果是第 4 个线程最先完成了第 3~4G 的下载，
那么就会形成很多的空洞。

如果一个文件有空洞，我们通过`ls -l`查看大小，他会包含空洞的，
比方说实际有效的字节是 4，空洞大小是 4，`ls -l`得到的是逻辑大小，
因此，这个结果是 8。但是假如我们使用`du`命令查看文件大小，结果却是 4

## ioctl

`ioctl`（Input/Output Control）是一个用于进行设备控制的系统调用，通常用于在 Unix 和类 Unix 系统中与设备进行交互。它的使用相对复杂，因为其参数和操作的具体含义通常取决于设备和操作系统。

基本的 `ioctl` 函数声明如下：

```c
int ioctl(int fd, unsigned long request, ...);
```

- `fd`：文件描述符，通常是打开设备文件后返回的。
- `request`：表示特定设备和操作的请求码。这是一个无符号长整型数，通常使用宏定义来指定。

使用 `ioctl` 的一般步骤如下：

1. 打开设备文件，获取文件描述符。

   ```c
   int fd = open("/dev/mydevice", O_RDWR);
   ```

2. 使用 `ioctl` 函数执行特定的控制操作。

   ```c
   #include <linux/ioctl.h>  // 包含 ioctl 请求码的头文件

   // 示例：请求码为 MY_IOCTL_COMMAND，参数为一个整数
   int value = 42;
   int result = ioctl(fd, MY_IOCTL_COMMAND, &value);
   ```

   在这里，`MY_IOCTL_COMMAND` 是一个宏，表示特定的控制命令。具体的宏定义和参数结构通常由设备的文档或头文件提供。

3. 根据需要处理 `ioctl` 的返回值和可能的错误。

   ```c
   if (result == -1) {
       perror("ioctl failed");
       // 处理错误
   }
   ```

请注意，`ioctl` 的使用方式会因设备和操作而异，因此确保查阅相关的设备文档或头文件以了解正确的请求码和参数。

以下是一个简单的示例，假设有一个虚构的设备，其中包含一个 `ioctl` 命令，用于获取设备信息：

```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/ioctl.h>

#define MY_IOCTL_GET_INFO _IOR('X', 1, int)

int main() {
    int fd = open("/dev/mydevice", O_RDWR);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }

    int info;
    if (ioctl(fd, MY_IOCTL_GET_INFO, &info) == -1) {
        perror("ioctl failed");
        close(fd);
        return 1;
    }

    printf("Device information: %d\n", info);

    close(fd);
    return 0;
}
```

在这个例子中，`MY_IOCTL_GET_INFO` 是一个宏，通过 `_IOR` 宏定义为一个输入参数是 `int` 类型的 ioctl 命令。
