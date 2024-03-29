//
//  rbtree.cpp
//  rbtree
//
//  Created by Sunil on 3/22/17.
//  Copyright © 2017 Sunil. All rights reserved.
//

#include "rbtree.hpp"

#include <list>
#include <tuple>
#include <stack>
#include <queue>
#include <iostream>

using namespace std;

rbtree::rbtree() {
    root = nullptr;
}

rbtree::~rbtree() {
    remove_all(root);
}

void rbtree::remove_all(rbnode* node) {
    if (!node) {
        // no node to delete
        return;
    }
    
    if (node->left)
        remove_all(node->left);
    if (node->right)
        remove_all(node->right);
    
    delete node;
}

bool rbtree::violates(bool constraint) {
    // just negate the constraint and return
    return !constraint;
}

void rbtree::insert(int key) {
    auto node = new rbnode(key, rbcolor::red);
    if (!root) {
        // empty tree. first node to add.
        // create a black node and add it to the rbtree.
        node->color = rbcolor::black;
        root = node;
        return;
    }
    
    auto temp = root;
    rbnode* parent = nullptr;
    
    // add node as you would in a BST.
    while(temp) {
        parent = temp;
        if (key > temp->key)
            temp = temp->right;
        else
            temp = temp->left;
    }
    
    // parent shouldn't be nullptr at this point.
    node->parent = parent;
    if (key > parent->key)
        parent->right = node;
    else
        parent->left = node;
    
    // adding node would have disturbed the rb tree.
    // Retore the it's properties by rebalancing it.
    balance(node);
}

bool rbtree::has_only_red_black_nodes(rbnode* node) {
    if (!node) {
        // no nodes, no color.
        return false;
    }
    
    // use any tree traversal and check the color
    
    // everynode has to be red or black.
    if (!node->is_red_node() && !node->is_black_node()) {
        // this node is neither red nor black. It's a invalid rb tree.
        return false;
    }
    
    // node has red/black color but doesn't have left or right subtree.
    if (!node->left && !node->right) {
        return true;
    }
    
    // only right subtree is available.
    if (!node->left && node->right) {
        return has_only_red_black_nodes(node->right);
    }
    
    // only left subtree is available.
    if (!node->right && node->left) {
        return has_only_red_black_nodes(node->left);
    }
    
    // Both left "and" right subtree should have only red/black nodes.
    return (
        has_only_red_black_nodes(node->left) && has_only_red_black_nodes(node->right)
            );
}

bool rbtree::rednode_has_black_children(rbnode* parent) {
    if (!parent) {
        // no node, no children. Nothing to check
        return false;
    }
    
    // if node is red, then check it's children
    if (parent->is_red_node()) {
        
        // if left and right children are null treat them as black.
        if (!parent->left && !parent->right) {
            return true;
        }
        
        // both left and right are available.
        if ((parent->left && parent->left->is_red_node())
            || (parent->right && parent->right->is_red_node())) {
            return false;
        }
        
        // left child is not null. make sure its color is black
        if (parent->left && parent->left->is_red_node()) {
            // left child is not black.
            return false;
        }
        
        // right child is not null. make sure its color is black
        if (parent->right && parent->right->is_red_node()) {
            // right child is not black.
            return false;
        }
    }
    
    
    // only right subtree is available.
    if (!parent->left && parent->right) {
        return has_only_red_black_nodes(parent->right);
    }
    
    // only left subtree is available.
    if (!parent->right && parent->left) {
        return has_only_red_black_nodes(parent->left);
    }
    
    // Both left "and" right subtree
    return (
            has_only_red_black_nodes(parent->left) && has_only_red_black_nodes(parent->right)
            );
}

bool rbtree::has_equal_black_nodes_all_path(rbnode* parent) {
    // do a depth first search traversal and count the black nodes
    // along all path from root to leaf node.
    if (!parent) {
        // no nodes. return true or false ?
        return true;
    }
    // stack of tuple of (node, count of black nodes) pair.
    stack<tuple<rbnode*, int>> stk;
    list<int> paths;
    
    auto count_if_black = [](rbnode* node) {
        return (node->is_black_node() ? 1 : 0);
    };
    
    stk.push(make_tuple(parent, count_if_black(parent)));
    
    while (!stk.empty()) {
        auto pair = stk.top();
        stk.pop();
        
        auto node = std::get<0>(pair);
        auto count = std::get<1>(pair);
        
        if (node->right) {
            auto right = node->right;
            stk.push(make_tuple(right, count + count_if_black(right)));
        } else {
            // right child is null. count it as a black node.
            paths.push_front(count + 1);
        }
        
        if (node->left) {
            auto left = node->left;
            stk.push(make_tuple(left, count + count_if_black(left)));
        } else {
            // left child is null. count it as a black node.
            paths.push_front(count + 1);
        }
    }
    
    // now check if black node count on all paths are same.
    auto first = paths.front();
    
#if DEBUG
    for (auto count : paths) cout << count << "|";
    cout << endl;
#endif
    
    for (auto count : paths) {
        if (count != first)
            return false;
    }
    
    
    return true;
}

bool rbtree::is_valid_rbtree() {
    // rb tree properties:
    //  P.1: every node is red/black.
    //  P.2: root is always black.
    //  P.3: leaf nodes are black.
    //  P.4: red node should have only black children.
    //  P.5: for any node x, # of black nodes along all
    //       paths from x to leaf nodes should be the same.
    
    if (!root) {
        // no nodes in the tree, is a valid RB tree
        return true;
    }
    
    // P.1: check if all nodes are red/ black.
    if (violates(has_only_red_black_nodes(root))) {
        // some nodes are of different color. It's not a red black tree
        return false;
    }
    
    // P.2: If root is not black then it's invalid.
    if (violates(root->is_black_node()))
        return false;
    
    // P.3: I take all null nodes to be black.
    // I treat all null nodes as black. So I don't have to
    // check for black null nodes.
    
    // P.4: all red nodes should have black children.
    if (violates(rednode_has_black_children(root))) {
        // some/all of red nodes doesn't have a black children
        return false;
    }
    
    // P.5:  check #black nodes along all possible path from root
    //  to leaf nodes.
    if (violates(has_equal_black_nodes_all_path(root))) {
        // unequal number of black nodes.
        return false;
    }
    
    return true;
}

rbnode* rbtree::search(int key) {
    if (!root) {
        // no nodes.
        return nullptr;
    }
    auto node = root;
    while(node) {
        if (node->key == key)
            return node;
        else if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    
    return nullptr;
}

void rbtree::bfs() {
    // breadth first search traversal.
    if (!root) {
        cout << "rb tree is empty" << endl;
        return;
    }
    
    deque<rbnode*> queue;
    queue.push_back(root);
    
    while(!queue.empty()) {
        auto node = queue.front();
        queue.pop_front();
        
        string color = node->is_black_node() ? "(black)" : "(red)";
        cout << node->key << color << endl;
        
        if (node->left) {
            queue.push_back(node->left);
        }
        
        if (node->right) {
            queue.push_back(node->right);
        }
    }
    
}

void rbtree::dfs() {
    // depth first search traversal.
    if (!root) {
        cout << "rb tree is empty!" << endl;
        return;
    }
    
    stack<rbnode*> stk;
    stk.push(root);
    
    while (!stk.empty()) {
        auto node = stk.top();
        stk.pop();
        
        string color = node->is_black_node() ? "(black)" : "(red)";
        cout << node->key << color << endl;
        
        if (node->right) {
            auto right = node->right;
            stk.push(right);
        }
        
        if (node->left) {
            auto left = node->left;
            stk.push(left);
        }
    }
}

void rbtree::prune(int min, int max) {
    throw new runtime_error("not implemented");
}

void rbtree::balance(rbnode* x) {
    while (true) {
        // loop invarient: node is red.
        // we don't want two consecutive nodes (node and it's parent) to be red.
        
        /*
            notation used in rb tree representation in comments.
                g  = black grand parent
                p  = black parent
                u  = black uncle
         
                X  = newly inserted red node
                G  = red grand parent
                P  = red parent
                U  = red uncle
         
            notation used in code:
                g = grand parent
                p = parent
                u = uncle
                x = node newly inserted.
         */
        auto p = x->parent;

        // if node's parent is black or null node(black). then we're done.
        if (!p || p->is_black_node()) {
            break;
        }
        
        auto g = p->parent;
        auto is_p_left_of_g = (g->left == p);
        auto u = is_p_left_of_g ? g->right : g->left;
        
        // treat null node as a black node.
        auto u_is_black = u ? u->is_black_node() : true;
        
        /* case 1: uncle is red.
            fix: recolor parent, grand-parent and uncle.
         
                      ...                                        ...
                      /                                          /
                     g             recolor (g, p, u)            G
                   /   \          ------------------->        /   \
                  P     U                                    p     u
                 / \   / \                                  / \   / \
                X                                          X

                  ...                                        ...
                    \                                          \
                     g             recolor (g, p, u)            G
                   /   \          ------------------->        /   \
                  U     P                                    u     p
                 / \   / \                                  / \   / \
                          X                                          X
         */
        auto u_is_red = !u_is_black;
        
        if (u_is_red) {
            g->color = rbcolor::red;
            p->color = rbcolor::black;
            
            if (u) {
                u->color = rbcolor::black;
            }
            
            // continue recoloring up the tree until rbtree properties are fixed.
            x = g;
            continue;
        }
        
        /* case 2: uncle is black (node is internal. falls within uncle and parent subtree).
            fix: rotate around parent. This rotation leads to case 3.
         
                    ...                                             ...
                    /                                               /
                   g                                               g
                 /   \           left rotate around p            /   \
                P     u        ----------------------->         X     u
               / \   / \                                       / \   / \
                  X                                           P
         
                ...                                            ...
                  \                                              \
                  g                                               g
                /   \          right rotate around p            /   \
               u     P        ----------------------->         u     X
              / \   / \                                       / \   / \
                   X                                                   P
         */
        auto is_x_right_of_p = (p->right == x);
        auto x_is_internal = (is_p_left_of_g && is_x_right_of_p) || (!is_p_left_of_g && !is_x_right_of_p);
        
        if (u_is_black && x_is_internal) {
            
            if (is_p_left_of_g && is_x_right_of_p)
                left_rotate(p);
            else
                right_rotate(p);
            
            // after left / right rotate, P takes the place of X
            x = p;
            continue;
        }
        
        /* case 3: uncle is black (node is external. falls outside of uncle and parent's subtree)
            fix: rotate around grand-parent and swap colors of grand-parent & parent.
         
                    ...                                             ...
                    /                                               /
                   g                                               p
                 /   \          right rotate around g            /   \
                P     u       -------------------------->       X     G
               / \   / \        swap color of (p, g)                 / \
              X   a                                                 a   u
                                                                       / \
         
              ...                                            ...
                \                                              \
                 g                                              p
               /   \          left rotate around g            /   \
              u     P       -------------------------->      G     X
             / \   / \        swap color of (p, g)          / \
                  a   X                                    u   a
                                                          / \
         */
        // I'm hard coding to true, because if none of the above cases are satisfied, It
        // has to be a case-3 and has to be external node.
        auto is_x_left_of_p = (p->left == x);
        auto x_is_external = true;
        
        if (u_is_black && x_is_external) {
            if (is_p_left_of_g && is_x_left_of_p)
                right_rotate(g);
            else
                left_rotate(g);
            
            // swap the color of (parent, grand-parent) after rotation.
            g->color = rbcolor::red;
            p->color = rbcolor::black;
        }
    }
    
    // in case if root's color is changed by case-1.
    // reset it's color to black.
    root->color = rbcolor::black;
}

void rbtree::right_rotate(rbnode* y) {
    /*
             y                                        x
            / \        right rotate around y         / \
           x   c     ----------------------->       a   y
          / \                                          / \
         a   b                                        b   c
     
     */
    
    auto x = y->left;
    
    // get right subtree of x if available.
    // otherwise set it to nullptr.
    auto b = x ? x->right : nullptr;
    
    // turn x's right subtree into a y's left subtree.
    y->left = b;
    
    if (b) {
        b->parent = y;
    }
    
    // set parent of x to y's parent.
    x->parent = y->parent;
    
    // if y doesn't have a parent, make x as root.
    if (!y->parent) {
        root = x;
    }
    // parent is not null, see if y is to left/right of parent.
    else if (y->parent->left == y) {
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }
    
    x->right = y;
    y->parent = x;
}

void rbtree::left_rotate(rbnode* x) {
    /*
            x                                          y
           / \          left rotate around x          / \
          a   y       ------------------------>      x   c
             / \                                    / \
            b   c                                  a   b
     */
    
    auto y = x->right;
    
    // get left subtree of y if available.
    // otherwise set it to nullptr.
    auto b = y ? y->left : nullptr;
    
    // no need to get c, as it stays unaffected by left rotation.
    
    // turn y's left subtree into a x's right subtree.
    x->right = b;
    if (b) {
        b->parent = x;
    }
    
    // set parent of y to x's parent.
    y->parent = x->parent;
    
    // if x doesn't have a parent, make y as root.
    if (!x->parent) {
        root = y;
    }
    // parent is not null, see if x is to left/right of parent.
    else if (x->parent->left == x) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

int rbtree::depth(rbnode* node) {
    if (!node) {
        // no node. depth is zero.
        return 0;
    }
    
    auto left_depth = depth(node->left);
    auto right_depth = depth(node->right);
    
    return 1 + max(left_depth, right_depth);
}

void rbtree::inorder() {
    inorder_traversal(root);
}

void rbtree::preorder() {
    preorder_traversal(root);
}

void rbtree::postorder() {
    postorder_traversal(root);
}

void rbtree::preorder_traversal(rbnode *node) {
    if (!node) {
        return;
    }
    
    preorder_traversal(node->left);
    preorder_traversal(node->right);
    auto color = node->is_black_node() ? "(black)" : "(red)";
    cout << node->key << color << endl;
}

void rbtree::postorder_traversal(rbnode *node) {
    if (!node) {
        return;
    }
    
    auto color = node->is_black_node() ? "(black)" : "(red)";
    cout << node->key << color << endl;
    postorder_traversal(node->left);
    postorder_traversal(node->right);
}

void rbtree::inorder_traversal(rbnode* node) {
    if (!node) {
        return;
    }
    
    inorder_traversal(node->left);
    auto color = node->is_black_node() ? "(black)" : "(red)";
    cout << node->key << color << endl;
    inorder_traversal(node->right);
}

int rbtree::depth() {
    return depth(root);
}

void rbtree::remove(int key) {
    // TODO: after removing the node, rebalance the tree.
    // ref: http://www.stolerman.net/studies/cs521/red_black_trees.pdf
    
    auto node = search(key);
    
    if (!node) {
        // node with key not found.
        return;
    }
    
    /*
     notation: a is the node to be deleted.
     case 1: no children.
     
     */
    if (!node->left && !node->right) {
        auto parent = node->parent;
        if (parent->left == node)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        
        if (node->color == rbcolor::black) {
            rb_color_fix fix = {
                .parent = parent,
                .double_edge = nullptr,
                .is_double_edge_left = parent->left == node
            };
            color_correction(fix);
        }
        delete node;
        return;
    }
    
    /*
     case 2: (only one child) no left child
     
                 /                           /
                a       ---------->         b
                 \                         / \
                  b
                 / \
     */
    if (!node->left) {
        // disregard the color, let's delete the node and fix color later.
        auto parent = node->parent;
        auto right = node->right;
        
        parent->right = right;
        
        if (right) {
            right->parent = parent;
            right->color = rbcolor::black;
        }
        
        if (node->color == rbcolor::black) {
            rb_color_fix fix = {
                .parent = parent,
                .double_edge = nullptr,
                .is_double_edge_left = parent->left == node
            };
            color_correction(fix);
        }
        
        delete node;
        return;
    }
    
    /*
     case 2: (only one child) no right child
            
                \                              \
                 a          -------->           b
                /                              / \
               b
              / \
     */
    
    if (!node->right) {
        auto parent = node->parent;
        auto left = node->left;
        parent->left = left;
        
        if (left) {
            left->parent = parent;
            left->color = rbcolor::black;
        }
        
        if (node->color == rbcolor::black) {
            rb_color_fix fix = {
                .parent = parent,
                .double_edge = nullptr,
                .is_double_edge_left = parent->left == node
            };
            color_correction(fix);
        }
        
        delete node;
        return;
    }
    
    /*
     case 4: node has two children
     
                 /                                     /
                a                                     e
              /   \                                 /   \
             b     c      ------------>            b     c
            / \   / \                             / \   / \
                 e   d                                 e
                  \ / \                                 \
     */
    if (node->left && node->right) {
        // auto replace = tree_minimum(node->right);
        auto replace = tree_maximum(node->left);
        
        // it would be easier to copy the value from replace
        // and delete it instead. I'm too lazy to swap the nodes.
        node->key = replace->key;
        
        // I dont have to change the color.
        
//        if (replace->right)
//            replace->parent->left = replace->parent;
        if (replace->left)
            replace->parent->right = replace->parent;
        
        // Is the replace directly attached to right side of the node.
//        if (node->right == replace) {
//            node->right = replace->right;
//        } else {
//            // If not present directly on the right.
//            replace->parent->left = replace->right;
//        }
        if (node->left == replace) {
            node->left = replace->left;
        } else {
            // If not present directly on the right.
            replace->parent->right = replace->left;
        }
        
        if (replace->color == rbcolor::black) {
            rb_color_fix fix = {
                .parent = replace->parent,
                .double_edge = replace->left,
                .is_double_edge_left = replace->parent->left == replace
            };
            color_correction(fix);
        }
        
        
        delete replace;
    }
}

void rbtree::color_correction(rb_color_fix fix) {
    while (1) {
        // passed node is the reference to double black if non null.
        // otherwise reference to parent is passed.
        
        /*
         notation used for tree representation in comments:
         
            ((b))  =  double black node
                b  =  black node
                r  =  red node
             null  =  null node

         */
        auto dblack = fix.double_edge;
        /*
         case 1: if double black node becomes the root. 
         Fix: Turn it into single black node.
         
                ((b))                       b
                /   \       ------>        / \
               null  null               null  null
         */
        if (dblack == root) {
            root->color = rbcolor::black;
            return;
        }
        
        /*
         case 2:
         */
        
        /*
         case 3: if parent, node(double edge) and it's sibling are all black.
         
                  b                             ((b))
                /   \                           /   \
            ((b))    b      ------->           b     r
                    / \                             / \
                   b   b                           b   b
         */
        auto parent = fix.parent;
        auto right = parent->right;
        auto left = parent->left;
        auto is_left_double_edge = fix.is_double_edge_left;
        auto isblack = [](rbnode* x) {
            return x ? x->is_black_node() : true;
        };
        
        auto sibling_children_are_black = false;
        if (is_left_double_edge) {
            
        }
        auto sibling_are_black = isblack(left) && isblack(right);
        
        if (parent->is_black_node() && sibling_are_black) {
            if (is_left_double_edge) {
                if (right)
                    right->color = rbcolor::red;
            } else {
                if (left)
                    left->color = rbcolor::red;
            }
            
            // now parent itself becomes the double black edge.
            fix.parent = parent->parent;
            fix.double_edge = parent;
            continue;
        }
        
        /*
         case 4: if parent is red, sibling is black and it's children are also black.
         Fix: swap color between parent and sibling
                    
                        r                            b
                      /   \                        /   \
                    ((b))  b     -------->        b     r
                          / \                          / \
                         b   b                        b   b
         */
        if (parent->is_red_node() && sibling_are_black) {
            parent->color = rbcolor::black;
            
            if (is_left_double_edge) {
                if (right) right->color = rbcolor::red;
            } else {
                if (left) left->color = rbcolor::red;
            }
            
            return;
        }
    }
}

rbnode* rbtree::tree_maximum(rbnode* node) {
    if (!node) {
        return nullptr;
    }
    
    while (node->right) {
        node = node->right;
    }
    
    return node;
}

rbnode* rbtree::tree_minimum(rbnode* node) {
    if (!node) {
        return nullptr;
    }
    
    while (node->left) {
        node = node->left;
    }
    
    return node;
}
