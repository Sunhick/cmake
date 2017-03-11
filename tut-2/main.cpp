#include "math.h"
#include <iostream>

using namespace std;

// defined externally. available at linking time.
// I should ideally put this in a header file.
// But i'm too lazy!!! I guess i could have instead 
// of typing this big comment. Whatever!
extern int add(int, int);
extern int sub(int, int);

int main(int argc, char *argv[])
{
  cout << "Add(4,5) = " << add(4, 5) << endl;
  cout << "Sub(4,5) = " << sub(4, 5) << endl;
  return 0;
}
