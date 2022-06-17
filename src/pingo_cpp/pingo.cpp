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
  // cout << "Creating";
  switch (m_type) {
    case Small:
      m_size = SMALL_PINGOS;
      // cout << " Small";
      break;
    case Medium:
      m_size = MEDIUM_PINGOS;
      // cout << " Medium";
      break;
    case Large:
      m_size = LARGE_PINGOS;
      // cout << " Large";
      break;
    case Other:
      cerr << "Type.Other is invalid - use the size_t ctor instead" << endl;
      [[fallthrough]];
    default:
      throw invalid_argument("pingo_cpp.Pingo(): invalid Type passed!");
  }
  // cout << " Pingo..." << endl;

  m_data1D = vector<int>(m_size, (int)type);
  m_data2D = vector<vector<float>>(m_size);
  m_data3D = vector<vector<vector<Event>>>(m_size);
  m_data3DNoCopy = vector<Event>(m_size * m_size * m_size);
  for (size_t i = 0; i < m_size; ++i) {
    m_data2D[i] = vector<float>(m_size, (float)type);
    m_data3D[i] = vector<vector<Event>>(m_size);
    for (size_t j = 0; j < m_size; ++j) {
      m_data3D[i][j] = vector<Event>(m_size, {(uint8_t)(j % 255), (uint64_t)j,
                                              (float)(m_size - j - 1), false});
      for (size_t k = 0; k < m_size; ++k) {
        size_t idx = ((i * m_size + j) * m_size) + k;
        m_data3DNoCopy[idx] = {(uint8_t)(j % 255), (uint64_t)j,
                               (float)(m_size - j - 1), false};
      }
    }
  }
  // cout << "...done" << endl;
}
Pingo::Pingo(size_t size) : m_size(size) {
  // cout << "Creating Pingo..." << endl;
  m_type = Type::Other;

  m_data1D = vector<int>(m_size, (int)m_type);
  m_data2D = vector<vector<float>>(m_size);
  m_data3D = vector<vector<vector<Event>>>(m_size);
  m_data3DNoCopy = vector<Event>(m_size * m_size * m_size);
  for (size_t i = 0; i < m_size; ++i) {
    m_data2D[i] = vector<float>(m_size, (float)m_type);
    m_data3D[i] = vector<vector<Event>>(m_size);
    for (size_t j = 0; j < m_size; ++j) {
      m_data3D[i][j] = vector<Event>(m_size, {(uint8_t)(j % 255), (uint64_t)j,
                                              (float)(m_size - j - 1), false});
      for (size_t k = 0; k < m_size; ++k) {
        size_t idx = ((i * m_size + j) * m_size) + k;
        m_data3DNoCopy[idx] = {(uint8_t)(j % 255), (uint64_t)j,
                               (float)(m_size - j - 1), false};
      }
    }
  }
  // cout << "...done" << endl;
}

Pingo::~Pingo() {  // cout << "Destroying Pingo" << endl; }
}

void Pingo::scale(int factor) {
  for (size_t i = 0; i < m_size; ++i) {
    m_data1D[i] *= factor;
    for (size_t j = 0; j < m_size; ++j) {
      m_data2D[i][j] *= (float)factor;
      for (size_t k = 0; k < m_size; ++k) {
        m_data3D[i][j][k].value *= (float)factor;
        size_t idx = ((i * m_size + j) * m_size) + k;
        m_data3DNoCopy[idx].value *= (float)factor;
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
    case Other:
      ss << "Other";
      break;
    default:
      throw invalid_argument("pingo_cpp.Pingo(): invalid Type passed!");
  }
  ss << "\n  size: " << m_size << "\n";
  return ss.str();
}
vector<int> Pingo::get_data_1d_vec() const { return m_data1D; }
pybind11::array_t<int> Pingo::get_data_1d() const {
  pybind11::array_t<int> output(m_size);
  auto ptr = static_cast<int*>(output.request().ptr);
  for (size_t i = 0; i < m_size; ++i) {
    ptr[i] = m_data1D[i];
  }
  return output;
}
void Pingo::set_data_1d(pybind11::array_t<int> arr) {
  pybind11::buffer_info buf = arr.request();
  if (buf.shape[0] != (int64_t)m_size) {
    stringstream msg;
    msg << "Pingo::set_data_1d(): invalid size for axis 0. Got ";
    msg << buf.shape[0] << ", but expected " << m_size << ".";
    throw std::invalid_argument(msg.str());
  }
  auto ptr = static_cast<int*>(buf.ptr);
  for (size_t i = 0; i < m_size; ++i) {
    m_data1D[i] = ptr[i];
  }
  return;
}
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
void Pingo::set_data_2d(pybind11::array_t<float> arr) {
  int dsize[2] = {(int)m_size, (int)m_size};
  pybind11::buffer_info buf = arr.request();
  for (int iax = 0; iax < 2; ++iax) {
    if (buf.shape[iax] != dsize[iax]) {
      stringstream msg;
      msg << "Pingo::set_data_2d(): invalid size for axis " << iax;
      msg << ". Got " << buf.shape[iax] << ", but expected ";
      msg << dsize[iax] << ".";
      throw std::invalid_argument(msg.str());
    }
  }
  auto ptr = static_cast<float*>(buf.ptr);
  for (size_t i = 0; i < m_size; ++i) {
    for (size_t j = 0; j < m_size; ++j) {
      // Row-major
      size_t idx = (i * m_size) + j;
      m_data2D[i][j] = ptr[idx];
    }
  }
  return;
}
pybind11::array_t<Event> Pingo::get_data_3d() const {
  pybind11::array_t<Event> output(m_size * m_size * m_size);
  auto ptr = static_cast<Event*>(output.request().ptr);
  for (size_t i = 0; i < m_size; ++i) {
    for (size_t j = 0; j < m_size; ++j) {
      // More efficient:
      // memcpy(ptr, m_data3D[i][j].data(), m_size * sizeof(Event));
      for (size_t k = 0; k < m_size; ++k) {
        // Row-major - getting this right/wrong can make a big difference
        // in performance, so be careful!
        // idx = ((i * <J_DIM_SIZE> + j) * <K_DIM_SIZE>) + k;
        size_t idx = ((i * m_size + j) * m_size) + k;
        ptr[idx].channel = m_data3D[i][j][k].channel;
        ptr[idx].timestamp = m_data3D[i][j][k].timestamp;
        ptr[idx].value = m_data3D[i][j][k].value;
        ptr[idx].error = m_data3D[i][j][k].error;
      }
    }
  }
  output.resize({m_size, m_size, m_size});
  return output;
}
void Pingo::set_data_3d(pybind11::array_t<Event> arr) {
  int dsize[3] = {(int)m_size, (int)m_size, (int)m_size};
  pybind11::buffer_info buf = arr.request();
  for (int iax = 0; iax < 3; ++iax) {
    if (buf.shape[iax] != dsize[iax]) {
      stringstream msg;
      msg << "Pingo::set_data_2d(): invalid size for axis " << iax;
      msg << ". Got " << buf.shape[iax] << ", but expected ";
      msg << dsize[iax] << ".";
      throw std::invalid_argument(msg.str());
    }
  }
  auto ptr = static_cast<Event*>(buf.ptr);
  for (size_t i = 0; i < m_size; ++i) {
    for (size_t j = 0; j < m_size; ++j) {
      for (size_t k = 0; k < m_size; ++k) {
        // Row-major
        size_t idx = ((i * m_size + j) * m_size) + k;
        m_data3D[i][j][k] = ptr[idx];
      }
    }
  }
  return;
}
pybind11::array_t<Event> Pingo::get_data_3d_colmaj() const {
  pybind11::array_t<Event> output(m_size * m_size * m_size);
  auto ptr = static_cast<Event*>(output.request().ptr);
  // Loop order is incorrect on purpose
  for (size_t k = 0; k < m_size; ++k) {
    for (size_t j = 0; j < m_size; ++j) {
      for (size_t i = 0; i < m_size; ++i) {
        // Same idx calc as row-major but loop order is swapped
        size_t idx = ((i * m_size + j) * m_size) + k;
        ptr[idx].channel = m_data3D[i][j][k].channel;
        ptr[idx].timestamp = m_data3D[i][j][k].timestamp;
        ptr[idx].value = m_data3D[i][j][k].value;
        ptr[idx].error = m_data3D[i][j][k].error;
      }
    }
  }
  output.resize({m_size, m_size, m_size});
  return output;
}
pybind11::array_t<Event> Pingo::get_data_3d_memcpy() const {
  pybind11::array_t<Event> output(m_size * m_size * m_size);
  auto ptr = static_cast<Event*>(output.request().ptr);
  memcpy(ptr, m_data3DNoCopy.data(), m_size * m_size * m_size * sizeof(Event));
  output.resize({m_size, m_size, m_size});
  return output;
}
}  // namespace pingo
