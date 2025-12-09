#include <iostream>
#include <vector>

#include <farthest_point_sampling.hpp>

int main() {

  std::vector<float> points = {
        0.0f, 0.0f, 0.0f,  // Point 0
        1.0f, 0.0f, 0.0f,  // Point 1
        0.0f, 1.0f, 0.0f,  // Point 2
        1.0f, 1.0f, 0.0f,  // Point 3
        0.0f, 0.0f, 1.0f,  // Point 4
        1.0f, 0.0f, 1.0f,  // Point 5
        0.0f, 1.0f, 1.0f,  // Point 6
        1.0f, 1.0f, 1.0f   // Point 7
    };

    size_t n_points = 8;
    size_t dim = 3;
    size_t n_samples = 4;   // We want to select 4 points
    size_t start_idx = 0;   // Start sampling from the first point

    // B. Create Sensible Output Buffer
    // We must pre-allocate memory for the results (indices are size_t)
    std::vector<size_t> output_indices(n_samples);

    // C. Call the function
    int result = bucket_fps_kdtree(
        points.data(),          // raw_data (pointer to float array)
        n_points,               // n_points
        dim,                    // dim
        n_samples,              // n_samples
        start_idx,              // start_idx
        output_indices.data()   // out_ptr (pointer to the allocated size_t array)
    );

    // D. Verify Results
    if (result == 0) {
        std::cout << "Success! Sampled indices: ";
        for (size_t idx : output_indices) {
            std::cout << idx << " ";
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Function failed with error code: " << result << std::endl;
    }

    return 0;
}