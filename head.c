#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
const int LINE_MAX = 10; // first n lines

void head(int fd, char* name)
{
  int n;
  int line_num = 0;
  while ((n = read(fd, buf, sizeof(buf))) > 0)
  {
    for (int i=0;i<n;i++){
      if (buf[i] == '\n')
        line_num++;
      
      if (line_num >= LINE_MAX) // similar to cat but exit if line max is reached
        exit();

      printf(1, "%c", buf[i]);
    }
  }

  if (n < 0)
  {
    printf(1, "head: read error\n");
    exit();
  }
}

int main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    head(0, "");
    exit();
  }

  for (i = 1; i < argc; i++)
  {
    if ((fd = open(argv[i], 0)) < 0)
    {
      printf(1, "head: cannot open %s\n", argv[i]);
      exit();
    }
    head(fd, argv[i]);
    close(fd);
  }
  exit();
}
