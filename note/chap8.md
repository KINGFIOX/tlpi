# chap8 - 用户和组

## getpwnam 与 getspnam

`getpwnam` 和 `getspnam` 都是用于获取用户信息的函数，但它们在获取用户密码信息的方式上有所不同。

1. **`getpwnam` 函数：**

   - `getpwnam` 用于通过用户名获取密码文件（通常是 `/etc/passwd` 文件）中的用户信息。
   - 返回的结构体是 `struct passwd`，包含了有关用户的信息，如用户名、UID、GID、登录目录、登录 Shell 等。
   - 但是，`struct passwd` 结构体中并不包含密码字段。密码字段被置为占位符 "x" 或 "\*"，实际的密码信息存储在 `/etc/shadow` 文件中。

   ```c
   #include <sys/types.h>
   #include <pwd.h>

   struct passwd *getpwnam(const char *name);
   ```

2. **`getspnam` 函数：**

   - `getspnam` 用于通过用户名获取密码文件（通常是 `/etc/shadow` 文件）中的用户密码信息。
   - 返回的结构体是 `struct spwd`，包含了有关用户密码的信息，如加密后的密码、上次修改密码的日期、密码的有效期等。
   - `struct spwd` 结构体相比 `struct passwd` 结构体，多了与密码相关的信息。

   ```c
   #include <shadow.h>

   struct spwd *getspnam(const char *name);
   ```

总的来说，`getpwnam` 用于获取用户的基本信息，而 `getspnam` 用于获取用户的密码信息。
在安全性方面，密码信息一般存储在 `/etc/shadow` 文件中，该文件对一般用户是不可读取的，只有超级用户（root）有权限读取。
这种分离密码信息的方式有助于增强系统的安全性。

### pw_passwd

在 `struct passwd` 结构体中，`pw_passwd` 字段存储的是用户的加密后的密码。
这个字段通常包含的是密码的哈希值或者其他形式的加密形式，而不是原始的明文密码。

在传统的 Unix 系统中，用户密码通常被存储在 `/etc/passwd` 文件中，但实际的密码值是经过单向散列（hash）处理的。
原始密码不会以明文形式存储，而是经过加密算法处理，生成一个不可逆的散列值。
这样即使 `/etc/passwd` 文件被非授权的用户读取，也无法轻松获取到明文密码。

以下是一个 `struct passwd` 结构体的部分定义：

```c
struct passwd {
    char   *pw_name;       /* 用户名 */
    char   *pw_passwd;     /* 加密的用户密码 */
    uid_t   pw_uid;        /* 用户标识 */
    gid_t   pw_gid;        /* 组标识 */
    // ...
};
```

通常，为了更进一步增强安全性，密码信息会被存储在 `/etc/shadow` 文件中，
这个文件对一般用户是不可读取的，只有超级用户（root）有权限读取。
因此，`struct passwd` 结构体中的 `pw_passwd` 字段一般是指向 `/etc/passwd` 文件或 `/etc/shadow` 文件中的相应字段的引用。

在现代系统中，更加安全的做法是使用密码哈希算法，
例如 MD5、SHA-256、SHA-512 等，以及加盐（salt）等技术，来存储用户密码的加密形式。
这样即使密码哈希值被泄露，由于加盐和哈希的不可逆性，破解密码也会更加困难。
