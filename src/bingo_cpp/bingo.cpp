#include "bingo.hpp"

#include <iostream>
#include <stdexcept>
using namespace std;

namespace bingo {
void run_bingo(Choice choice) {
  switch (choice) {
    case Bing:
      cout << "bingo_cpp.run_bingo(): Bing!" << endl;
      break;
    case Bang:
      cout << "bingo_cpp.run_bingo(): Bang!" << endl;
      break;
    case Bong:
      cout << "bingo_cpp.run_bingo(): Bong!" << endl;
      break;
    default:
      throw invalid_argument("bingo_cpp.run_bingo(): invalid Choice");
  }
  return;
}
}  // namespace bingo
