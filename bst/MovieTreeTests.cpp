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

#include "MovieTree.hpp"

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

// Movie tree test
class MovieTreeTest : public ::testing::Test {
public:
  MovieTree* catalog;
  int size = 1;
  vector<string> inorder = { "Movie: 12 Angry Men 56","Movie: American History X 1","Movie: Apocalypse Now 5","Movie: Back to the Future 5","Movie: Casablanca 5","Movie: City Lights 10","Movie: City of God 9","Movie: Dr. Strangelove or: How I Learned to Stop Worrying and Love the Bomb 5","Movie: Fight Club 6","Movie: Forrest Gump 1","Movie: Gladiator 5","Movie: Goodfellas 5","Movie: Inception 10","Movie: Interstellar 8","Movie: It's a Wonderful Life 21","Movie: Leon: The Professional 31","Movie: Life Is Beautiful 3","Movie: Memento 9","Movie: Modern Times 9","Movie: Once Upon a Time in the West 12","Movie: One Flew Over the Cuckoo's Nest 10","Movie: Psycho 6","Movie: Pulp Fiction 34","Movie: Raiders of the Lost Ark 6","Movie: Rear Window 7","Movie: Saving Private Ryan 3","Movie: Schindler's List 10","Movie: Se7en 11","Movie: Seven Samurai 7","Movie: Shawshank Redemption 45","Movie: Spirited Away 10","Movie: Star Wars: Episode IV - A New Hope 6","Movie: Star Wars: Episode V - The Empire Strikes Back 12","Movie: Sunset Blvd. 5","Movie: Terminator 2: Judgment Day 10","Movie: The Dark Knight 90","Movie: The Departed 7","Movie: The Godfather 34","Movie: The Godfather: Part II 12","Movie: The Good the Bad and the Ugly 2","Movie: The Green Mile 8","Movie: The Lord of the Rings: The Fellowship of the Ring 20","Movie: The Lord of the Rings: The Return of the King 4","Movie: The Lord of the Rings: The Two Towers 5","Movie: The Matrix 5","Movie: The Pianist 7","Movie: The Silence of the Lambs 19","Movie: The Untouchables 3","Movie: The Usual Suspects 2","Movie: Whiplash 8" };
    
  MovieTreeTest() {
    // You can do set-up work for each test here.
    catalog = new MovieTree;
  }

  virtual ~MovieTreeTest() {
    // You can do clean-up work that doesn't throw exceptions here.
    delete catalog;
  }

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).   
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  void PopulateMovies() {
    string filename = "/Users/Sunny/prv/tmp/Assignment-8/Assignment-8/install/bin/Assignment8Movies.txt";
    ifstream file(filename);
    
    // non-existant or corrupted file
    if(file.fail()) {
      die("Check if file exists!");
    }
    
    int ranking, releaseYear, quantity;
    string title ,word, line;

    while(std::getline(file, line)) {
      stringstream lineStream(line);
        
      // format of Assignment8Movie.txt:
      // ranking(integer), title(string), releaseYear(integer), quantity(integer)
      std::getline(lineStream, word, ',');
      ranking = atoi(word.c_str());
        
      std::getline(lineStream, word, ',');
      title = word;
        
      std::getline(lineStream, word, ',');
      releaseYear = atoi(word.c_str());
        
      std::getline(lineStream, word);
      quantity = atoi(word.c_str());
        
      // add to movie catalog.
      catalog->addMovieNode(ranking, title, releaseYear, quantity);
      size++;
    } 
  }

  void die(string message) {
    cout << message << endl;
    exit(0);
  }
};

TEST_F(MovieTreeTest, test_empty) {
  EXPECT_TRUE(catalog->root == nullptr) << "root should be null";
  EXPECT_EQ(0, catalog->countMovieNodes()) << "count should be 0!";
}

TEST_F(MovieTreeTest, test_addNode) {
  PopulateMovies();
  EXPECT_EQ(50, catalog->countMovieNodes()) << "Node count should be 50!";
}

TEST_F(MovieTreeTest, test_DeleteAll) {
  PopulateMovies();
  catalog->DeleteAll(catalog->root);
  // need to set root to null. can't do it in DeleteAll because it's recursive.
  catalog->root = nullptr;
  EXPECT_EQ(0, catalog->countMovieNodes()) << "count should be 0 after DeleteAll nodes";
}

TEST_F(MovieTreeTest, test_searchFound) {
  PopulateMovies();
  
  auto title = "Star Wars: Episode V - The Empire Strikes Back";
  auto found = catalog->search(title);

  ASSERT_TRUE(found != nullptr) << "MovieNode should be not null";
  EXPECT_EQ(title, found->title) << title << " should be in movie tree";
}

TEST_F(MovieTreeTest, test_searchNotFound) {
  PopulateMovies();
  
  auto title = "Star Wars: Episode";
  auto found = catalog->search(title);
  
  EXPECT_TRUE(found == nullptr) << title << " shouldn't be in movie tree";
  EXPECT_TRUE(catalog->search("") == nullptr) << "No movie with empty title";
}

TEST_F(MovieTreeTest, test_printMovieInventory) {
  PopulateMovies();

  stringstream buffer;
  // redirect cout to string buffer
  {
    cout_redirect activate(buffer.rdbuf());
    catalog->printMovieInventory();
  }

  auto expected = string("");
  std::for_each(begin(inorder), end(inorder), [&expected](string line) {
      expected  += line + "\n";
    });
  
  EXPECT_EQ(expected, buffer.str()) << "inorder traversal is wrong";
}

TEST_F(MovieTreeTest, test_DeleteAllNodes_oneByOne) {
  PopulateMovies();

  for(int i = 0; i < size+1; i++) {
    auto line = inorder[size-i];
    string stray = "Movie: ";
    auto index = line.find_last_of(" ");
    auto title = line.substr(0, index);

    std::string::size_type rem = title.find(stray);
    if (rem != string::npos)
      title.erase(rem, stray.length());
        
    inorder.erase(std::remove(inorder.begin(), inorder.end(), line), inorder.end());
    stringstream buffer;
    {
      stringstream ignore; {
	cout_redirect active(ignore.rdbuf());
	catalog->deleteMovieNode(title);
      }
      
      cout_redirect activate(buffer.rdbuf());
      catalog->printMovieInventory();
    }

    auto got = buffer.str();
    auto expected = string("");
    std::for_each(begin(inorder), end(inorder), [&expected](string line) {
	expected  += line + "\n";
      });

    EXPECT_EQ(expected, got) << "Incorrect inorder traversal after delete";
  }
    
  EXPECT_EQ(0, catalog->countMovieNodes());
}
