#include "types.h"

// From proc.h Proc structure
// Per-process state
enum uprocstate
{
    U_UNUSED,
    U_EMBRYO,
    U_SLEEPING,
    U_RUNNABLE,
    U_RUNNING,
    U_ZOMBIE
};
struct uproc
{
    int pid;
    int ppid;
    int state;
    uint sz;
    char name[16];
};

//Processes || Copy elements from the kernel ptable to user space
// struct proc *getptable_proc(void);
