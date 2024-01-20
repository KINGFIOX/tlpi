# chap9 - 进程凭证

## ruid euid suid fsuid

在 Linux 和 Unix 系统中，这些变量是用户标识（User ID）相关的四个不同标识：

1. `ruid`（Real User ID）：`ruid` 表示当前进程的真实用户标识，即调用进程的实际用户。它是进程最初启动时分配的用户标识。

2. `euid`（Effective User ID）：`euid` 表示当前进程的有效用户标识，即用于确定进程对资源的访问权限的用户标识。在执行时，`euid` 可能会与 `ruid` 相同，也可能会在程序执行过程中被改变（例如通过设置 SetUID 位）。

3. `suid`（Saved Set-user-ID）：`suid` 表示已保存的用户标识。在执行时，`suid` 通常与 `euid` 相同。但是，在执行特权操作时，`euid` 可能会暂时更改，而 `suid` 保留原始的 `euid`，以便在完成特权操作后可以还原。

4. `fsuid`（Filesystem User ID）：`fsuid` 表示文件系统用户标识，即在文件系统上执行操作时使用的用户标识。它用于控制文件系统的访问权限。
