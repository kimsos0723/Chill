#include "route_tree.h"

#include <inttypes.h>
#include <memory.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _avl_node_data {
  struct avl_tree_node* left;
  struct avl_tree_node* right;
  node_data_t value;
};

struct avl_tree_node {
  struct _avl_node_data data;
  uint32_t height;
  uint8_t hash[SHA256_DIGEST_LENGTH];
};

struct avl_tree {
  struct avl_tree_node* root;
  u_int32_t balance_factor;
};

void _avl_clear_leaf(avl_node_t* root) {
  if (root == NULL) {
    return;
  }
  _avl_clear_leaf(root->data.left);
  _avl_clear_leaf(root->data.right);
  free(root);
}

avl_tree_t* _avl_new_node(node_data_t value) {
  avl_node_t* node = (struct avl_tree_node*)malloc(sizeof(avl_node_t));
  node->data.left = NULL;
  node->data.right = NULL;
  node->data.value = value;
  node->height = 1;
  memset(node->hash, 0, SHA256_DIGEST_LENGTH);
  unsigned char md[SHA256_DIGEST_LENGTH];
  SHA256((unsigned char*)node->data.value, sizeof(node_data_t), node->hash);
  return node;
}

void avl_create(avl_tree_t* ptree) {
  if ((ptree = malloc(sizeof(avl_tree_t))) == NULL) {
    return NULL;
  }
  ptree->root = NULL;
}

uint32_t avl_get_height(avl_node_t* pnode) {
  if (node == NULL) return 0;
  return pnode->height;
}

uint32_t avl_get_difference(avl_node_t* pnode) {
  if (pnode == NULL) return 0;
  Node* leftChild = pnode->leftChild;
  Node* rightChild = pnode->rightChild;
  return avl_get_height(leftChild) - avl_get_height(rightChild);
}

uint32_t avl_set_height(avl_node_t* pnode) {
  if (pnode == NULL) return 0;
  uint32_t height = 1;
  uint32_t left_height = pnode->data.left->height;
  uint32_t right_height = pnode->data.right->height;
  height += left_height > right_height ? left_height : right_height;
  return height;
}

avl_node_t* _avl_rotateLL(avl_node_t* pnode) {
  avl_node_t* left = pnode->data.left;
  pnode->data.left = left->data.right;
  left->data.right = pnode;
  avl_set_height(pnode);
  return left;
}

_avl_rotateRR(avl_node_t* pnode) {
  avl_node_t* right = pnode->data.right;
  pnode->data.right = left->data.right;
  right->data.left = pnode;
  avl_set_height(pnode);
  return right;
}

_avl_rotateLR(avl_node_t* pnode) {
  avl_node_t* left = pnode->data.left;
  pnode->data.left = _avl_rotateRR(left);
  return _avl_rotateLL(pnode);
}

_avl_rotateRL(avl_node_t* pnode) {
  avl_node_t* right = pnode->data.right;
  pnode->data.right = _avl_rotateLL(left);
  return _avl_rotateRR(pnode);
}

avl_node_t* avl_balance(avl_node_t* pnode) {
  uint32_t difference =  avl_get_difference(pnode);
  if(difference >= 2 ) {
    if()
  }
}

avl_node_t* avl_insert(avl_node_t* pnode, node_data_t data) {
  unsigned char data_hash[SHA256_DIGEST_LENGTH];
  SHA256((unsigned char*)data, sizeof(node_data_t), data_hash);
  if (pnode == NULL) {
    pnode = _avl_new_node(data);
  } else if (strcmp(data_hash, pnode->hash) > 0) {
    pnode->data.left = avl_insert(pnode->data.left, data);
    pnode = avl_balance(pnode);
  } else if (strcmp(data_hash, pnode->hash) < 0) {
    pnode->data.right = avl_insert(pnode->data.right, data);
    pnode = avl_balance(pnode);
  } else {
    perror("redundant data!");
  }
  return pnode;
}

void avl_distroy(avl_tree_t* ptree) {
  _avl_clear_leaf(ptree->root);
  free(ptree);
}
