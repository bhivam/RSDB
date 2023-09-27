#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/_types/_null.h>

#include "btree.h"

btree *btree_new(int degree)
{
  if (degree < BTREE_MIN_M)
  {
    degree = BTREE_MIN_M;
  }

  btree *tree = malloc(sizeof(btree));
    
  tree->root = NULL;
  tree->m = degree;
  tree->t = (int) (degree / 2.0); 

  return tree;
}

btree_node *btree_create_node()
{
  btree_node* node = malloc(sizeof(btree_node));
  
  node->num_keys = 0;
  node->num_children = 0;

  node->keys = NULL;
  node->vals = NULL;
  node->children = NULL;

  return node;
}

void btree_add_value(int key, void *value, btree_node *node)
{
  if (node->num_keys == 0)
  {
    node->keys = malloc(sizeof(int));
    node->vals = malloc(sizeof(void *));
  }
  else 
  {
    node->keys = realloc(node->keys, sizeof(int) * (node->num_keys + 1));
    node->vals = realloc(node->keys, sizeof(void *) * (node->num_keys + 1));
  }

  node->keys[node->num_keys] = key;
  node->vals[node->num_keys] = value;

  node->num_keys++;
}

int btree_insert(int key, void *value, btree *tree)
{
  if (tree->root == NULL)
  {
    tree->root = btree_create_node();
    btree_add_value(key, value, tree->root);
    return 1;
  }

  return 1;  
}

void *btree_search(int key, btree *tree)
{
  return tree->root->vals[0];
}

