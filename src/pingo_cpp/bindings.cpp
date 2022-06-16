#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include "pingo.hpp"
namespace py = pybind11;

PYBIND11_MODULE(pingo_cpp, m) {
  // The module's docstring
  m.doc() = "Pingo C++ code, with python bindings";

  // C-struct for numpy structured array
  PYBIND11_NUMPY_DTYPE(pingo::Point, x, y, z);

  // Class-scope enum. Note that we're passing in the class to the enum
  // def instead of the module like in bingo_cpp
  py::class_<pingo::Pingo> pingo(m, "Pingo");
  py::enum_<pingo::Pingo::Type>(pingo, "Type")
      .value("Small", pingo::Pingo::Type::Small)
      .value("Medium", pingo::Pingo::Type::Medium)
      .value("Large", pingo::Pingo::Type::Large)
      .export_values();
  // Class defintions
  pingo
      // Template args are constructor arg types
      .def(py::init<pingo::Pingo::Type>())
      // Functions
      .def("__str__", &pingo::Pingo::str)
      .def("__len__", &pingo::Pingo::size)
      // Static constants
      .def_readonly_static("SMALL_PINGOS", &pingo::Pingo::SMALL_PINGOS)
      .def_readonly_static("MEDIUM_PINGOS", &pingo::Pingo::MEDIUM_PINGOS)
      .def_readonly_static("LARGE_PINGOS", &pingo::Pingo::LARGE_PINGOS)
      // Can set default args
      .def("scale", &pingo::Pingo::scale, py::arg("factor") = 1)
      // Properties allow opaque passthrough using = instead of calling
      // get_() and set_()
      .def_property("data_1d", &pingo::Pingo::get_data_1d,
                    &pingo::Pingo::set_data_1d)
      .def_property("data_2d", &pingo::Pingo::get_data_2d,
                    &pingo::Pingo::set_data_2d)
      .def_property("data_3d", &pingo::Pingo::get_data_3d,
                    &pingo::Pingo::set_data_3d);
}
