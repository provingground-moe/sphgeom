/*
 * LSST Data Management System
 * See COPYRIGHT file at the top of the source tree.
 *
 * This product includes software developed by the
 * LSST Project (http://www.lsst.org/).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the LSST License Statement and
 * the GNU General Public License along with this program.  If not,
 * see <https://www.lsstcorp.org/LegalNotices/>.
 */
#include "pybind11/pybind11.h"

#include "lsst/sphgeom/HtmPixelization.h"

namespace py = pybind11;
using namespace pybind11::literals;

namespace lsst {
namespace sphgeom {
namespace {

PYBIND11_MODULE(htmPixelization, mod) {
    py::module::import("lsst.sphgeom.pixelization");
    py::module::import("lsst.sphgeom.region");

    py::class_<HtmPixelization, Pixelization> cls(mod, "HtmPixelization");

    cls.attr("MAX_LEVEL") = py::int_(HtmPixelization::MAX_LEVEL);

    cls.def_static("level", &HtmPixelization::level, "i"_a);
    cls.def_static("triangle", &HtmPixelization::triangle, "i"_a);
    cls.def_static("asString", &HtmPixelization::asString, "i"_a);

    cls.def(py::init<int>(), "level"_a);
    cls.def(py::init<HtmPixelization const &>(), "htmPixelization"_a);

    cls.def("getLevel", &HtmPixelization::getLevel);

    cls.def("__eq__",
            [](HtmPixelization const &self, HtmPixelization const &other) {
                return self.getLevel() == other.getLevel();
            });
    cls.def("__ne__",
            [](HtmPixelization const &self, HtmPixelization const &other) {
                return self.getLevel() != other.getLevel();
            });
    cls.def("__repr__", [](HtmPixelization const &self) {
        return py::str("HtmPixelization({!s})").format(self.getLevel());
    });
    cls.def("__reduce__", [cls](HtmPixelization const &self) {
        return py::make_tuple(cls, py::make_tuple(self.getLevel()));
    });
}

}  // <anonymous>
}  // sphgeom
}  // lsst
