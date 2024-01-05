/*
 * contains the implementation of all syscalls.
 */

#include <stdint.h>
#include <errno.h>

#include "util/types.h"
#include "syscall.h"
#include "string.h"
#include "process.h"
#include "util/functions.h"

#include "spike_interface/spike_utils.h"

/**
 * @brief 打印用户提供的字符串
 * 
 * @param buf 字符串缓冲区的指针
 * @param n 字符串的长度
 * @return ssize_t 返回打印的字符数
 */
ssize_t sys_user_print(const char* buf, size_t n) {
  sprint(buf);
  return 0;
}


ssize_t sys_user_exit(uint64 code) {
  sprint("User exit with code:%d.\n", code);
/**
 * @brief System call to exit the user application.
 *
 * This function is called when the user application wants to exit.
 * It prints the exit code and shuts down the system.
 *
 * @param code The exit code of the user application.
 * @return The number of bytes written.
 */
  // in lab1, PKE considers only one app (one process). 
  // therefore, shutdown the system when the app calls exit()
  shutdown(code);
}

long do_syscall(long a0, long a1, long a2, long a3, long a4, long a5, long a6, long a7) {
  switch (a0) {
    case SYS_user_print:
      return sys_user_print((const char*)a1, a2);
/**
 * Executes the specified system call with the given arguments.
 *
 * @param a0 The system call number.
 * @param a1 The first argument.
 * @param a2 The second argument.
 * @param a3 The third argument.
 * @param a4 The fourth argument.
 * @param a5 The fifth argument.
 * @param a6 The sixth argument.
 * @param a7 The seventh argument.
 * @return The result of the system call.
 */
    case SYS_user_exit:
      return sys_user_exit(a1);
    default:
      panic("Unknown syscall %ld \n", a0);
  }
}
