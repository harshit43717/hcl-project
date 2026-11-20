#!/bin/bash
# kernel_user_demo.sh - read-only commands for the Kernel vs User mode practical
# Author: Harshit Singh (2026B01010102)
# Nothing here modifies the system.

echo "=== 1. Kernel and current user ==="
uname -a
whoami
id

echo; echo "=== 2. Kernel threads (children of PID 2, shown in [brackets]) ==="
ps --ppid 2 -o pid,comm | head -10

echo; echo "=== 3. Some user-mode processes ==="
ps -eo pid,user,comm --sort=pid | grep -v '\[' | head -10

echo; echo "=== 4. Loaded kernel modules ==="
lsmod | head -10

echo; echo "=== 5. Kernel symbol addresses as a normal user ==="
head -3 /proc/kallsyms

echo; echo "=== 6. CPU time split (user vs sys) ==="
time ls -R /usr > /dev/null 2>&1
