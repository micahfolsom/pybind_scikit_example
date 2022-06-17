#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>  // PYBIND11_NUMPY_DTYPE
#include <pybind11/stl.h>       // not sure but also needed for the STL part!
#include <pybind11/stl_bind.h>  // PYBIND11_MAKE_OPAQUE

#include "pingo.hpp"
namespace py = pybind11;

// STL containers (part 1, see py::bind_vector below)
PYBIND11_MAKE_OPAQUE(std::vector<pingo::Event>);

PYBIND11_MODULE(pingo_cpp, m) {
  // The module's docstring
  m.doc() = "Pingo C++ code, with python bindings";

  // STL containers (part 2, last step is .def()ing the function as usual)
  // std::vectors come out as a pythonic-vector object on the other side
  // using this name
  py::bind_vector<std::vector<pingo::Event>>(m, "EventStdVector");

  // C-struct for numpy structured array
  PYBIND11_NUMPY_DTYPE(pingo::Event, channel, timestamp, value, error);
  // Make it available in python as a plain old object with attributes
  // Only difference is you can't arbitrarily add attributes
  // Pass "py::dynamic_attr()" as an arg after "Event" below to get this
  // capability
  py::class_<pingo::Event> event(m, "Event");
  event.def(py::init<>())
      .def_readwrite("channel", &pingo::Event::channel)
      .def_readwrite("timestamp", &pingo::Event::timestamp)
      .def_readwrite("value", &pingo::Event::value)
      .def_readwrite("error", &pingo::Event::error);

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
      .def(py::init<std::size_t>())
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
      .def_property("data_1d_vec", &pingo::Pingo::get_data_1d_vec,
                    nullptr)  // not settable
      .def_property("data_1d", &pingo::Pingo::get_data_1d,
                    &pingo::Pingo::set_data_1d)
      .def_property("data_2d", &pingo::Pingo::get_data_2d,
                    &pingo::Pingo::set_data_2d)
      .def_property("data_3d", &pingo::Pingo::get_data_3d,
                    &pingo::Pingo::set_data_3d)
      .def_property("data_3d_colmaj", &pingo::Pingo::get_data_3d_colmaj,
                    nullptr)
      .def_property("data_3d_memcpy", &pingo::Pingo::get_data_3d_memcpy,
                    nullptr);
}
