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
  tree->max_degree = degree;
  tree->min_degree = (degree / 2) + 1; 

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
    node->keys[node->num_keys] = key;
    node->vals[node->num_keys] = value;
  }
  else 
  {
    node->keys = realloc(node->keys, sizeof(int) * (node->num_keys + 1));
    node->vals = realloc(node->keys, sizeof(void *) * (node->num_keys + 1));
  
    for (int i = 0; i < node->num_keys; i++)
    {
      if (key < node->keys[i])
      {
        int temp;     

        for (int j = i; i < node->num_keys; j++)
        {
          temp = node->keys[j];
          node->keys[j] = key;
          key = temp;
        }

        // also have to do this for value

        break;
      }
      else if (key == node->keys[i])
      {
        node->vals[i] = value;
        break;
      }
    }
  }

  node->num_keys++;
}

int _btree_insert(int key, void *value, btree_node *node, btree *tree)
{
  if (node->num_children < tree->max_degree)
  {
      
  }

  return 1;
}

int btree_insert(int key, void *value, btree *tree)
{
  if (tree->root == NULL)
  {
    tree->root = btree_create_node();
    btree_add_value(key, value, tree->root);
    return 1;
  }
  
  return _btree_insert(key, value, tree->root, tree);
}


void *btree_search(int key, btree *tree)
{
  return tree->root->vals[0];
}

