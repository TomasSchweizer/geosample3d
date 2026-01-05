#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <stdexcept>
#include "farthest_point_sampling.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_geosample3d, m) {
    m.doc() = "Python bindings for geosample3d algorithms";

    m.def("bucket_fps_kdtree", 
        [](py::array_t<float, py::array::c_style | py::array::forcecast> points, 
           size_t n_samples, 
           size_t start_idx) 
        {
            // Validate input dimensions
            if (points.ndim() != 2) {
                throw std::runtime_error("Input points must be a 2D array (N, D)");
            }

            size_t n_points = static_cast<size_t>(points.shape(0));
            size_t dim = static_cast<size_t>(points.shape(1));

            // Pre-allocate the output NumPy array (indices are size_t)
            py::array_t<size_t> result(n_samples);
            
            // Call the C++ implementation
            int status = bucket_fps_kdtree(
                points.data(),
                n_points,
                dim,
                n_samples,
                start_idx,
                result.mutable_data()
            );

            if (status != 0) {
                throw std::runtime_error("C++ bucket_fps_kdtree failed with error code: " + std::to_string(status));
            }

            return result;
        },
        py::arg("points"),
        py::arg("n_samples"),
        py::arg("start_idx") = 0,
        "Performs Farthest Point Sampling using a KD-Tree bucket approach.");
}