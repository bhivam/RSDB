#ifndef _BTREE_H
#define _BTREE_H

#define BTREE_MIN_M 3

typedef struct btree_node
{
  int num_keys; // number of keys in node
  int num_children;
  int *keys; // array of keys
  void **vals; // parallel array of values
  struct btree_node **children; // array with chilren
} btree_node; 

typedef struct btree
{
  // min_degree = cieling(max_degree / 2) 

  int max_degree; 
  int min_degree; 
  btree_node *root;
} btree;

btree *btree_new(int degree);
void btree_free(btree *tree);

int btree_insert(int key, void *value, btree *tree);
void *btree_search(int key, btree *tree);

#endif
