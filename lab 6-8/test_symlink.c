#include "types.h"
#include "user.h"
#include "syscall.h"
#include "fcntl.h"

int main()
{
    int fd;

    fd = open("file_A", O_CREATE|O_RDWR);
    write(fd, "aaaaaaaaaa", 10);

    symlink("file_A","file_B");
    exit();

}