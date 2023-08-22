#include "proc.h"
#include "param.h"
#include "user.h"

struct proc *getptable_proc()
{
    struct proc* p = malloc(NPROC * sizeof(struct proc));
    struct proc* kernel_table = ret_ptable();
    int i;

    for (i = 0; i < NPROC; i++)
    {
        p[i] = kernel_table[i];
    }
    return p;
}
