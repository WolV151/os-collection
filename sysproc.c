#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "uproc.h"

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_trace(void) // trace implementation
{
  int n; // store arugemnt value

  argint(0, &n);       // pass the address
  myproc()->trace = n; // set trace to whatever the arg was

  return myproc()->num_syscalls; // return number of calls for the proc
}

struct proc *getptable_proc()
{
  struct proc *kernel_table = ret_ptable();
  return kernel_table;
}

int sys_getprocs(void)
{
  int PROCESS_NAME_SIZE = 16;
  int size;
  struct uproc *buf;
  struct proc *p = '\0';
  char *pbuf;
  int l = 0;

  if (argint(0, &size) < 0)
  {
    return -1;
  }
  if (argptr(1, &pbuf, size * sizeof(struct uproc)) < 0)
  {
    return -1;
  }

  buf = (struct uproc *)pbuf;
  // need to write the getptable_proc function

  p = getptable_proc();

  for (int i = 0; i < size; i++)
  {
    strncpy(buf[i].name, p[i].name, PROCESS_NAME_SIZE);
    buf[i].ppid = p[i].parent->pid;
    buf[i].pid = p[i].pid;
    buf[i].state = p[i].state;
    buf[i].sz = p[i].sz;

    if (p[i].pid != 0)
    {
      l++;
    }

  }

  // copy from the p table to buf
  return l;
}
