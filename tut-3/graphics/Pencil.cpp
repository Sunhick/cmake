#include "include/Pencil.h"

#include <iostream>

using namespace std;

Pencil::Pencil() : name("default") {
}

void Pencil::DrawCircle() {
  cout << "drawing circle" << endl;
}
