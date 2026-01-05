import numpy as np
import geosample3d as g3d

functions = [f for f in dir(g3d) if f[0].islower() and callable(getattr(g3d, f))]
print(functions)
points = np.random.rand(1000, 3).astype(np.float32)
num_samples = 100
sampled_indices = g3d.bucket_fps_kdtree(points, num_samples)
sampled_points = points[sampled_indices]
print("Sampled Points:\n", sampled_points)
print("Sampled Indices:\n", sampled_indices)