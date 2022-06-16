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

void Pingo::scale(int factor) {
  for (size_t i = 0; i < m_size; ++i) {
    m_data1D[i] *= factor;
    for (size_t j = 0; j < m_size; ++j) {
      m_data2D[i][j] *= (float)factor;
      for (size_t k = 0; k < m_size; ++k) {
        m_data3D[i][j][k].x *= (float)factor;
        m_data3D[i][j][k].y *= (float)factor;
        m_data3D[i][j][k].z *= (float)factor;
      }
    }
  }
  return;
}

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
pybind11::array_t<int> Pingo::get_data_1d() const {
  pybind11::array_t<int> output(m_size);
  auto ptr = static_cast<int*>(output.request().ptr);
  for (size_t i = 0; i < m_size; ++i) {
    ptr[i] = m_data1D[i];
  }
  return output;
}
void Pingo::set_data_1d(pybind11::array_t<int> arr) { return; }
pybind11::array_t<float> Pingo::get_data_2d() const {
  pybind11::array_t<float> output(m_size * m_size);
  auto ptr = static_cast<float*>(output.request().ptr);
  for (size_t i = 0; i < m_size; ++i) {
    // More efficient:
    // memcpy(ptr, m_data2D[i].data(), m_size * sizeof(float));
    for (size_t j = 0; j < m_size; ++j) {
      // Row-major - getting this right/wrong can make a big difference
      // in performance, so be careful!
      // idx = (i * <J_DIM_SIZE>) + j;
      size_t idx = (i * m_size) + j;
      ptr[idx] = m_data2D[i][j];
    }
  }
  output.resize({m_size, m_size});
  return output;
}
void Pingo::set_data_2d(pybind11::array_t<float> arr) { return; }
pybind11::array_t<Point> Pingo::get_data_3d() const {
  pybind11::array_t<Point> output(m_size * m_size * m_size);
  auto ptr = static_cast<Point*>(output.request().ptr);
  for (size_t i = 0; i < m_size; ++i) {
    for (size_t j = 0; j < m_size; ++j) {
      // More efficient:
      // memcpy(ptr, m_data3D[i][j].data(), m_size * sizeof(Point));
      for (size_t k = 0; k < m_size; ++k) {
        // Row-major - getting this right/wrong can make a big difference
        // in performance, so be careful!
        // idx = ((i * <J_DIM_SIZE> + j) * <K_DIM_SIZE>) + k;
        size_t idx = ((i * m_size + j) * m_size) + k;
        ptr[idx].x = m_data3D[i][j][k].x;
        ptr[idx].y = m_data3D[i][j][k].y;
        ptr[idx].z = m_data3D[i][j][k].z;
      }
    }
  }
  output.resize({m_size, m_size, m_size});
  return output;
}
void Pingo::set_data_3d(pybind11::array_t<Point> arr) { return; }
}  // namespace pingo
