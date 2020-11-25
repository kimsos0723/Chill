#ifndef __ROUTE_TREE__
#define __ROUTE_TREE__

typedef struct avl_tree avl_tree_t;
typedef struct avl_tree_node avl_node_t;
typedef int node_data_t;

void avl_create(avl_tree_t* ptree);
void avl_distroy(avl_tree_t* ptree);
avl_node_t* avl_insert(avl_node_t* pnode, node_data_t data);

int avl_remove(avl_tree_t* ptree, avl_node_t target);
int avl_search(const avl_tree_t* ptree);

uint32_t avl_get_height(avl_node_t* pnode);
avl_node_t* avl_balance(avl_node_t* pnode);

void avl_show_all(const avl_tree_t*ptree);
#endif  // __ROUTE_TREE__
