/*
 * syscall_demo.c
 * Kernel Mode vs User Mode demonstration
 * Author : Harshit Singh (2026B01010102)
 *
 * The program itself always runs in USER MODE. Whenever it needs the
 * kernel to do something (get PID, write to screen, open a file) it makes
 * a system call, and the CPU briefly switches to KERNEL MODE.
 *
 * Compile : gcc syscall_demo.c -o syscall_demo
 * Run     : ./syscall_demo            (run as a normal user)
 * Trace   : strace -e trace=getpid,write,openat ./syscall_demo
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/syscall.h>

int main(void)
{
    const char *msg = "Hello from user mode - printed using the write() system call\n";

    /* 1. A direct system call: ask the kernel for our process ID */
    long pid = syscall(SYS_getpid);
    printf("[1] getpid() syscall returned PID = %ld\n", pid);

    /* 2. Another direct system call: write text to the terminal (fd 1) */
    printf("[2] Calling write() directly:\n");
    fflush(stdout);
    syscall(SYS_write, 1, msg, strlen(msg));

    /* 3. Try to open raw physical memory. Only the kernel (or root) may do
          this, so a normal user should get "Permission denied". */
    printf("[3] Trying to open /dev/mem (needs kernel-level privilege)...\n");
    int fd = open("/dev/mem", O_RDONLY);
    if (fd < 0)
        printf("    Failed as expected: %s\n", strerror(errno));
    else {
        printf("    Opened (are you running as root?). Closing it again.\n");
        close(fd);
    }
    return 0;
}
