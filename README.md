# os-collection
Group of college projects for creating systemcalls for the xv6 operating system

XV6 is not included. The files can be inserted into a folder containing the xv6 files and the following files need to be edited:
- user.h - add system call placeholder
- syscall.h - add new entries for the systemcalls
- syscall.c - add new systemcalls to the systemcall function pointer array
- usys.S - add new systemcall
- MAKEFILE - include any programs (e.g. ps.c)

**These files may only run into the x86 architecure of xv6 as new implementations are written for RISCV**
