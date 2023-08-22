#include "types.h"
#include "stat.h"
#include "user.h"
#include "uproc.h"

#define MAX_PROC 10


int main(int argc, char *argv[])
{
    struct uproc ptable[MAX_PROC];
    // struct uproc *p;
    int err;
    int i;

    err = getprocs(10, ptable);
    if (err == -1)
        printf(1, "Error getting ptable\n");

    for (i = 0; i < 10; i++)
    {   
        if (ptable[i].pid == 0)
        {
            continue;
        }

        if (ptable[i].ppid < 0)
            ptable[i].ppid = 0;  // root process doesn't have a vaild parent id

        printf(1, "%d %d %d %d %s\n", ptable[i].pid, ptable[i].ppid, ptable[i].state, ptable[i].sz, ptable[i].name);
    }

    exit();
}