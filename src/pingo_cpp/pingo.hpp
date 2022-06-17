#ifndef PINGO_HPP
#define PINGO_HPP
#include <pybind11/numpy.h>

#include <string>
#include <vector>

namespace pingo {
// Simple C struct for use in the numpy structured array
struct Event {
  std::uint8_t channel;
  std::uint64_t timestamp;
  float value;
  bool error;
};

// A class that we can bind to. Generates Events and stores them in a 3D
// vector
class Pingo {
 public:
  // Class-scope enum
  enum Type { Small = 1, Medium = 2, Large = 3, Other = 4 };
  // Class-scope constant declarations. These are accessible without
  // an instance
  static size_t const SMALL_PINGOS;
  static size_t const MEDIUM_PINGOS;
  static size_t const LARGE_PINGOS;

  explicit Pingo(Type type);
  explicit Pingo(size_t size);
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
  std::vector<int> get_data_1d_vec() const;
  pybind11::array_t<int> get_data_1d() const;
  void set_data_1d(pybind11::array_t<int> arr);
  pybind11::array_t<float> get_data_2d() const;
  void set_data_2d(pybind11::array_t<float> arr);
  pybind11::array_t<Event> get_data_3d() const;
  void set_data_3d(pybind11::array_t<Event> arr);

  // More advanced - functions showing what happens if 1) we get the loop
  // order wrong and use column instead of row major and 2) avoiding the
  // copy by passing the array pointer
  pybind11::array_t<Event> get_data_3d_colmaj() const;
  // using memcpy() to copy the whole array at once, instead of looping
  // over the vector<vector<vector<Event>>>
  pybind11::array_t<Event> get_data_3d_memcpy() const;
  // pybind11::array_t<Event> get_data_3d_nocopy();

 private:
  Type m_type;
  size_t m_size;
  std::vector<int> m_data1D;
  std::vector<std::vector<float>> m_data2D;
  std::vector<std::vector<std::vector<Event>>> m_data3D;
  // We store 3D data as a 1D array for performance - we can either memcpy
  // the whole thing to a numpy array, or pass the pointer directly to
  // numpy
  std::vector<Event> m_data3DNoCopy;
};
}  // namespace pingo

#endif
