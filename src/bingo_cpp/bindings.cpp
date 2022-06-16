#include <pybind11/pybind11.h>

#include "bingo.hpp"
namespace py = pybind11;

PYBIND11_MODULE(bingo_cpp, m) {
  // The module's docstring
  m.doc() = "Bingo C++ code, with python bindings";

  // Namespace-scope enum; for classes, just add another level, e.g.
  // Bingo::MyClass::Choice
  py::enum_<bingo::Choice>(m, "Choice")
      .value("Bing", bingo::Choice::Bing)
      .value("Bang", bingo::Choice::Bang)
      .value("Bong", bingo::Choice::Bong)
      .export_values();

  // Namespace-scope function
  m.def("run_bingo", &bingo::run_bingo);
}
