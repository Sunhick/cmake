#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

#include "gtest/gtest.h"

// Nasty hack to test MovieTree
#define class struct
#define private public
#define protected public

#include "../rbtree.hpp"
#include "../rbnode.hpp"

#undef class
#undef private
#undef protected

using namespace std;

// Redirect the cout to a string
struct cout_redirect {
  cout_redirect(std::streambuf* new_buffer) 
    : old( std::cout.rdbuf(new_buffer))
  {
  }

  ~cout_redirect() {
    std::cout.rdbuf(old);
  }

private:
  std::streambuf* old;
};

class rbtree_tests : public ::testing::Test {
public:
  
};

TEST_F(rbtree_tests, test_empty) {

}