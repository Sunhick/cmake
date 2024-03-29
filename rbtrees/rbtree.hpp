//
//  rbtree.hpp
//  rbtree
//
//  Created by Sunil on 3/22/17.
//  Copyright © 2017 Sunil. All rights reserved.
//

#ifndef rbtree_hpp
#define rbtree_hpp

#include <iostream>
#include "rbnode.hpp"

////////////////////////////
// Red black tree
////////////////////////////
class rbtree {
private:
    rbnode *root;
    
    bool has_only_red_black_nodes(rbnode* node);
    bool rednode_has_black_children(rbnode* node);
    bool has_equal_black_nodes_all_path(rbnode* parent);
    bool violates(bool);
    int depth(rbnode* node);
    
    rbnode* tree_maximum(rbnode* node);
    rbnode* tree_minimum(rbnode* node);
    void color_correction(rb_color_fix fix);
    
    void inorder_traversal(rbnode* node);
    void preorder_traversal(rbnode* node);
    void postorder_traversal(rbnode* node);
    
public:
    rbtree();
    ~rbtree();
    
    void insert(int key);
    rbnode* search(int key);
    bool is_valid_rbtree();
    void prune(int min, int max);
    
    void balance(rbnode* node);
    void left_rotate(rbnode* node);
    void right_rotate(rbnode* node);
    
    int depth();
    
    void remove(int key);
    void remove_all(rbnode* root);
    
    void bfs();
    void dfs();
    
    void inorder();
    void preorder();
    void postorder();
};

#endif /* rbtree_hpp */
