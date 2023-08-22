# os-collection
Group of college projects for creating systemcalls for the xv6 operating system

- find.c - Find command, takes path to look recursevly and the file that is being looked for.
- head.c - Like the Linux version - "cat" the first 10 lines of a file
- ps.c - Current processes running
- trace - Systemcall (sysproc.c) - Minimal version of Linux "strace" call

XV6 is not included. The files can be inserted into a folder containing the xv6 files and the following files need to be edited:
- user.h - add system call placeholder
- syscall.h - add new entries for the systemcalls
- syscall.c - add new systemcalls to the systemcall function pointer array
- usys.S - add new systemcall
- MAKEFILE - include any programs (e.g. ps.c)

**These files may only run into the x86 architecure of xv6 as new implementations are written for RISCV**
