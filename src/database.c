#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "err.h"

int create_database(char *name)
{
  int error, path_length;
  char *path;

  // TODO What's going on here?
  path_length = strlen("./data/") + strlen(name);
  path = malloc(path_length + 1);
  sprintf(path, "./data/%s", name);
    
  error = stat(path, NULL);
  if (error >= 0)
  {
    err("DB Init Failure: DB already exists.", 0);
    return -1; 
  }

  error = mkdir(path, 0700);
  if (error < 0)
  {
    err("DB Init Failure:", 1);
    return -1;
  }

  return 0;
}

int main(int argc, char **argv)
{
  create_database("testing_db");
  return 0;
}
