#include <stdlib.h>
#include <stdio.h>

#include "btree.h"

int main(int argc, char **argv)
{
  btree *tree = btree_new(3);

  char *phrase = "Grabbed from the btree!";
  
  btree_insert(1, (void *) phrase, tree);
  printf("%s\n", (char *) btree_search(1, tree));

}
