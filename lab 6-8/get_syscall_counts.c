#include "types.h"
#include "user.h"
#include "syscall.h"
#include "stat.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
    printf(1, "initial fork count: %d\n", getcount(SYS_fork));
    if (fork() == 0) {
        printf(1, "child fork count: %d\n", getcount(SYS_fork));
        printf(1, "child write count: %d\n", getcount(SYS_write));
    } else {
        wait();
        printf(1, "parent fork count: %d\n", getcount(SYS_fork));
        printf(1, "parent write count: %d\n", getcount(SYS_write));
        int p = getpid();
        printf(1, "PID: %d\n", p);
    }
    printf(1, "wait count: %d\n", getcount(SYS_wait));
    printf(1, "getpid count: %d\n", getcount(SYS_getpid));
    printf(1, "UPTIME_VALUE: %d\n" ,uptime());
    printf(1, "uptime count: %d\n", getcount(SYS_uptime));
    exit();
}