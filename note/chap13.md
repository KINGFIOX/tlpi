# chap13 - 文件 IO 缓冲

## memalign

```c
void* buf = (char*)memalign(alignment * 2, length + alignment) + alignment;
```

这行代码涉及到内存对齐的操作。让我解释一下这段代码的作用：

1. `memalign` 函数：`memalign` 是一个用于分配内存并确保所分配的内存地址满足特定对齐要求的函数。在这里，`memalign` 函数被用来分配一块内存，该内存的起始地址是 `alignment * 2` 的倍数，并且总长度是 `length + alignment`。

2. `(char*)memalign(alignment * 2, length + alignment)`：这部分代码分配了一块内存，并将其起始地址转换为 `char*` 类型，以便以字节为单位进行地址偏移。

3. `+ alignment`：在分配的内存块的起始地址上加上 `alignment`，这样就将起始地址向后偏移了 `alignment` 个字节。这个偏移的目的是为了确保返回的地址满足额外的对齐要求。

最终，`buf` 是一个 `void*` 指针，指向分配的内存块的起始地址，这个地址满足特定的对齐要求。这种对齐通常在涉及 SIMD（单指令多数据）指令集、硬件对齐要求或其他特定的内存对齐场景中很有用。
