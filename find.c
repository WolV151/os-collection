#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

char *
fmtname(char *path) // ls function
{
  static char buf[DIRSIZ + 1];
  char *p;

  // Find first character after last slash.
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if (strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));
  return buf;
}

// "similar" to the real strstr, returns 1 if
// sub_str is inside str
int strstr(const char *str, const char *sub_str)
{
  int i;
  const int len = strlen(str);
  const int len_sub = strlen(sub_str);
  int char_count = 0;
  int j = 0;

  for (i = 0; i < len; i++) // loop over word
  {
    do
    {
      if (str[i] == sub_str[i]) // while chars get matched
      {
        if (++char_count == len_sub) // if full sub_str length is exhausted and the condition is true
          return 1;                  // then the sub_string must be inside str

        i++;
        j++;
      }
      else
      {
        i -= char_count;
        char_count = 0;
        j = 0;
      }
    } while (char_count);
  }
  return 0;  // else return 0
}

// provide a dir tree to search and name to match
void find(char *path, char *str_name)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, 0)) < 0)
  {
    printf(2, "find: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0)
  {
    printf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }
  // printf(1, "%d\n", strcmp(str_name, "*"));
  switch (st.type)
  { // if file, print file path
  case T_FILE:
    if ((strstr(fmtname(path), str_name) == 1))
      printf(1, "%s\n", path);
    break;

  case T_DIR: // else if dir, open dir and call find() again
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
    {
      printf(1, "find: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
      if (de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if (stat(buf, &st) < 0)
      {
        printf(1, "find: cannot stat %s\n", buf);
        continue;
      }

      // don't bother opening more "." or ".." recursivly
      if ((st.type == T_DIR) && ((strcmp(fmtname(buf), ".") != 32) && (strcmp(fmtname(buf), "..") != 32)))
      {
        find(buf, str_name);
      } // if the file is matched print it's path, if the name is "*" print all
      else if (((st.type == T_FILE) && (strstr(fmtname(buf), str_name) == 1)) || (strcmp(str_name, "*") == 0))
      {
        printf(1, "%s\n", buf);
      }
    }
    break;
  }
  close(fd);
}

int main(int argc, char *argv[])
{
  if (argc <= 2)
  {
    find(".", "*"); // print out everything
    exit();
  }
  else if (argc > 3) // could do a loop to go through args 1,2 - 3,4 - 4,5...
  {
    printf(1, "find: only 0 or 2 arguments.");
    exit();
  }

  find(argv[1], argv[2]); // execute as normal

  exit();
}
