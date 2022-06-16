#include <iostream>

#include "pingo.hpp"
using namespace pingo;
using namespace std;

int main(int, char**) {
  Pingo p(Pingo::Large);
  cout << p.str() << endl;
  return 0;
}
