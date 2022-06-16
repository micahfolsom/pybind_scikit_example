#include "pingo.hpp"

#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

namespace pingo {
// Static constant definitions (must be in a .cpp file)
size_t const Pingo::SMALL_PINGOS = 10;
size_t const Pingo::MEDIUM_PINGOS = 50;
size_t const Pingo::LARGE_PINGOS = 100;

Pingo::Pingo(Type type) : m_type(type) {
  cout << "Creating";
  switch (m_type) {
    case Small:
      m_size = SMALL_PINGOS;
      cout << " Small";
      break;
    case Medium:
      m_size = MEDIUM_PINGOS;
      cout << " Medium";
      break;
    case Large:
      m_size = LARGE_PINGOS;
      cout << " Large";
      break;
    default:
      throw invalid_argument("pingo_cpp.Pingo(): invalid Type passed!");
  }
  cout << " Pingo..." << endl;

  m_data1D = vector<int>(m_size, (int)type);
  m_data2D = vector<vector<float>>(m_size);
  m_data3D = vector<vector<vector<Point>>>(m_size);
  for (size_t i = 0; i < m_size; ++i) {
    m_data2D[i] = vector<float>(m_size, (float)type);
    m_data3D[i] = vector<vector<Point>>(m_size);
    for (size_t j = 0; j < m_size; ++j) {
      m_data3D[i][j] = vector<Point>(m_size, {10.f, 20.f, 30.f});
    }
  }
  cout << "...done" << endl;
}

Pingo::~Pingo() { cout << "Destroying Pingo" << endl; }

void Pingo::scale(int factor) { return; }
string Pingo::str() const {
  stringstream ss;
  ss << "\nPingo:\n";
  ss << "  type: ";
  switch (m_type) {
    case Small:
      ss << "Small";
      break;
    case Medium:
      ss << "Medium";
      break;
    case Large:
      ss << "Large";
      break;
    default:
      throw invalid_argument("pingo_cpp.Pingo(): invalid Type passed!");
  }
  ss << "\n  size: " << m_size << "\n";
  return ss.str();
}
}  // namespace pingo
