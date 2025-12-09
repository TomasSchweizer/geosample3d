#include <cstddef> // for size_t
#include <iostream>

int bucket_fps_kdtree(
    const float* raw_data, 
    size_t n_points, 
    size_t dim, 
    size_t n_samples, 
    size_t start_idx, 
    size_t* out_ptr
) {
    // Sanity check (optional for dummy, but good practice)
    if (n_points == 0 || out_ptr == nullptr) {
        return 1; // Return non-zero to trigger the exception in your Python wrapper
    }

    std::cout << "[C++] specific_algo: Running dummy sampling..." << std::endl;
    
    for (size_t i = 0; i < n_samples; ++i) {
        out_ptr[i] = (start_idx + i) % n_points;
    }

    return 0; // Return 0 to signal success
}