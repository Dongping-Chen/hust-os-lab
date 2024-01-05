/*
 * define the syscall numbers of PKE OS kernel.
 */
#ifndef _SYSCALL_H_
#define _SYSCALL_H_

// syscalls of PKE OS kernel. append below if adding new syscalls.
#define SYS_user_base 64
#define SYS_user_print (SYS_user_base + 0)
#define SYS_user_exit (SYS_user_base + 1)

/**
 * @brief Executes a system call with the given arguments.
 *
 * @param a0 The first argument of the system call.
 * @param a1 The second argument of the system call.
 * @param a2 The third argument of the system call.
 * @param a3 The fourth argument of the system call.
 * @param a4 The fifth argument of the system call.
 * @param a5 The sixth argument of the system call.
 * @param a6 The seventh argument of the system call.
 * @param a7 The eighth argument of the system call.
 * @return The result of the system call.
 */
long do_syscall(long a0, long a1, long a2, long a3, long a4, long a5, long a6, long a7);

#endif
