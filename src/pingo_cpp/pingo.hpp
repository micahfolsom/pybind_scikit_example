#ifndef PINGO_HPP
#define PINGO_HPP
#include <pybind11/numpy.h>

#include <string>
#include <vector>

namespace pingo {
// Simple C struct for use in the numpy structured array
struct Point {
  float x;
  float y;
  float z;
};

// A class that we can bind to
class Pingo {
 public:
  // Class-scope enum
  enum Type { Small = 1, Medium = 2, Large = 3 };
  // Class-scope constant declarations. These are accessible without
  // an instance
  static size_t const SMALL_PINGOS;
  static size_t const MEDIUM_PINGOS;
  static size_t const LARGE_PINGOS;

  explicit Pingo(Type type);
  ~Pingo();

  // Scale all of the data; only integers allowed
  void scale(int factor);
  // Strings are passed opqaquely - map this to __str__()
  std::string str() const;
  // Map to __len__(), will come through as int
  inline size_t size() const { return m_size; }

  // Getters and setters, which will be passed opaquely to python, e.g.
  // pingo = pingo_cpp.Pingo(pingo_cpp.Pingo.Type.Large)
  // pingo.data_1d = numpy.ones(shape=(pingo_cpp.Pingo.LARGE_PINGOS))
  pybind11::array_t<int> get_data_1d() const;
  void set_data_1d(pybind11::array_t<int> arr);
  pybind11::array_t<float> get_data_2d() const;
  void set_data_2d(pybind11::array_t<float> arr);
  pybind11::array_t<Point> get_data_3d() const;
  void set_data_3d(pybind11::array_t<Point> arr);

 private:
  Type m_type;
  size_t m_size;
  std::vector<int> m_data1D;
  std::vector<std::vector<float>> m_data2D;
  std::vector<std::vector<std::vector<Point>>> m_data3D;
};
}  // namespace pingo

#endif
