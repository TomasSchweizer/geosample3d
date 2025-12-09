#pragma once

#include <cstddef>

/**
 * @brief Dummy implementation of bucket-based Farthest Point Sampling using a KD-Tree.
 * @param raw_data   Pointer to the flattened input point cloud data (P * C).
 * @param n_points   Total number of points (P).
 * @param dim        Dimension of points (C).
 * @param n_samples  Number of samples to select.
 * @param start_idx  Index of the initial point to start sampling from.
 * @param out_ptr    Pointer to the output array where selected indices will be written.
 * @return int       Returns 0 on success, non-zero on failure.
 */
int bucket_fps_kdtree(
    const float* raw_data,
    size_t n_points,
    size_t dim,
    size_t n_samples,
    size_t start_idx,
    size_t* out_ptr
);

