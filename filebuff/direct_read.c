#define _GNU_SOURCE
#include "../lib/tlpi_hdr.h"
#include <fcntl.h>
#include <malloc.h>

int main(int argc, char* argv[])
{
    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s file length [offset [alignment]]\n", argv[0]);
    }

    ssize_t length = getLong(argv[2], GN_ANY_BASE, "length");
    off_t offset = (argc > 3) ? getLong(argv[3], GN_ANY_BASE, "offset") : 0;
    ssize_t alignment = (argc > 4) ? getLong(argv[4], GN_ANY_BASE, "alignment") : 4096;

    int fd = open(argv[1], O_RDONLY | O_DIRECT);
    if (fd == -1) {
        errExit("open");
    }

    // 起始地址是 alignment * 2 的整数倍，分配 length + alignment 字节
    void* buf = (char*)memalign(alignment * 2, length + alignment) + alignment;
    if (buf == NULL) {
        errExit("memalign");
    }

    if (lseek(fd, offset, SEEK_SET) == -1) {
        errExit("lseek");
    }

    ssize_t numRead = read(fd, buf, length);
    if (numRead == -1) {
        errExit("read");
    }
    printf("read %ld bytes\n", (long)numRead);
    exit(EXIT_SUCCESS);
}