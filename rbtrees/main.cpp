//
//  main.cpp
//  rbtree
//
//  Created by Sunil on 3/22/17.
//  Copyright © 2017 Sunil. All rights reserved.
//

#include <iostream>
#include <memory>

#define class struct
#define private public
#define protected public

#include "rbtree.hpp"

#undef class
#undef private
#undef protected

using namespace std;

int main(int argc, const char * argv[]) {
    
    // sample usage of rb trees
    // build a red black tree.
    auto root = new rbnode(45, rbcolor::black);
    
    auto r1 = new rbnode(25);
    r1->parent = root;
    
    auto r2 = new rbnode(60);
    r2->parent = root;
    
    root->left = r1;
    root->right = r2;
    
    rbtree rbt;
    rbt.root = root;
    
    auto root2 = new rbnode(10, rbcolor::black);
    auto n7 = new rbnode(7, rbcolor::black, root2);
    auto n19 = new rbnode(19, rbcolor::red, root2);
    auto n13 = new rbnode(13, rbcolor::black, n19);
    auto n23 = new rbnode(23, rbcolor::black, n19);
    
    root2->left = n7;
    root2->right = n19;
    n19->left = n13;
    n19->right = n23;

    rbtree rbt2;
    rbt2.root = root2;
    
    cout << std::boolalpha << rbt.has_equal_black_nodes_all_path(rbt.root) << endl;
    cout << std::boolalpha << rbt.is_valid_rbtree() << endl;
    cout << std::boolalpha << rbt2.is_valid_rbtree() << endl;
    
    cout << "=== DFS ===" << endl;
    rbt2.dfs();
    
    cout << "=== BFS ===" << endl;
    rbt2.bfs();
    
    rbtree rb;
    
    rb.insert(50);
    cout << "=== INORDER ===" << endl;
    rb.inorder();
    cout << std::boolalpha << rb.is_valid_rbtree() << endl;
    
    rb.insert(100);
    cout << "=== INORDER ===" << endl;
    rb.inorder();
    cout << std::boolalpha << rb.is_valid_rbtree() << endl;
    
    rb.insert(150);
    cout << "=== INORDER ===" << endl;
    rb.inorder();
    cout << std::boolalpha << rb.is_valid_rbtree() << endl;
    
    rbtree rb2;
    for (int i = 0; i < 10; i++) {
        rb2.insert(i);
        cout << "=== INORDER ===" << endl;
        rb2.inorder();
        cout << std::boolalpha << rb2.is_valid_rbtree() << endl;
    }

    return 0;
}
