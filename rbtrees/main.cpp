//
//  main.cpp
//  rbtree
//
//  Created by Sunil on 3/22/17.
//  Copyright © 2017 Sunil. All rights reserved.
//

#include <iostream>
#include <memory>

#include "rbtree.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    // sample usage of rb trees
    // build a red black tree.
    rbtree rbt;
    
    for (int k = 0; k <= 9; k++) {
        rbt.insert(k);
    }
    
    rbt.remove(9);
    rbt.remove(8);
    rbt.remove(5);
//    rbt.remove(6);
//    cout << "=== DFS ===" << endl;
//    rbt.dfs();
//    
//    cout << "=== BFS ===" << endl;
//    rbt.bfs();
//    
    cout << "=== INORDER ===" << endl;
    rbt.inorder();

    cout << "=== Is rb tree ===" << endl;
    cout << "is rb tree = " << std::boolalpha << rbt.is_valid_rbtree() << endl;
//
//    cout << "=== Max depth ===" << endl;
//    cout << "Max depth = " << rbt.depth() << endl;
    
    return 0;
}
