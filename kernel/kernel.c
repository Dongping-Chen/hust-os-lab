/*
 * Supervisor-mode startup codes
 */

#include "riscv.h"
#include "string.h"
#include "elf.h"
#include "process.h"

#include "spike_interface/spike_utils.h"

// process is a structure defined in kernel/process.h
process user_app;

/**
 * @brief Loads the user program into the process.
 * 
 * This function sets up the trapframe, kstack, and stack pointer for the process.
 * It then calls the load_bincode_from_host_elf() function to load the binary code
 * from the host ELF file into the process.
 * 
 * @param proc The process structure representing the user program.
 */
void load_user_program(process *proc) {
  // USER_TRAP_FRAME is a physical address defined in kernel/config.h
  proc->trapframe = (trapframe *)USER_TRAP_FRAME;
  memset(proc->trapframe, 0, sizeof(trapframe));
  // USER_KSTACK is also a physical address defined in kernel/config.h
  proc->kstack = USER_KSTACK;
  proc->trapframe->regs.sp = USER_STACK;

  // load_bincode_from_host_elf() is defined in kernel/elf.c
  load_bincode_from_host_elf(proc);
}

/**
 * @brief Function to start the supervisor mode.
 * 
 * This function enters the supervisor mode and performs the necessary setup for memory mapping.
 * It sets the satp register to 0, indicating that the virtual address is equal to the physical address.
 * The user application is then loaded into memory and executed.
 * Finally, the function switches to user mode using the switch_to() function.
 * 
 * @return 0
 */
int s_start(void) {
  sprint("Enter supervisor mode...\n");
  // Note: we use direct (i.e., Bare mode) for memory mapping in lab1.
  // which means: Virtual Address = Physical Address
  // therefore, we need to set satp to be 0 for now. we will enable paging in lab2_x.
  // 
  // write_csr is a macro defined in kernel/riscv.h
  write_csr(satp, 0);

  // the application code (elf) is first loaded into memory, and then put into execution
  load_user_program(&user_app);

  sprint("Switch to user mode...\n");
  // switch_to() is defined in kernel/process.c
  switch_to(&user_app);

  // we should never reach here.
  return 0;
}
