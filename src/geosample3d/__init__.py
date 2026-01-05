try:
    from ._geosample3d import bucket_fps_kdtree
except ImportError:
    raise ImportError("The C++ extension _geosample3d was not found. ")

__all__ = ['bucket_fps_kdtree']