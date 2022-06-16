#include <pybind11/pybind11.h>

#include "pingo.hpp"
namespace py = pybind11;

PYBIND11_MODULE(pingo_cpp, m) {
  // The module's docstring
  m.doc() = "Pingo C++ code, with python bindings";

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
      //.def_readonly_static("SMALL_PINGOS", &pingo::Pingo::SMALL_PINGOS)
      //.def_readonly_static("MEDIUM_PINGOS", &pingo::Pingo::MEDIUM_PINGOS)
      //.def_readonly_static("LARGE_PINGOS", &pingo::Pingo::LARGE_PINGOS)
      // Can set default args from python
      .def("scale", &pingo::Pingo::scale);
}
