#!/usr/bin/env
"""Some simple functions to show the time differences of the various
approaches to passing arrays."""
import timeit

IMPORT = "from pybind_scikit_example import Pingo"


def profile_init(obj_size=100, ntrials=1000) -> None:
    dur = timeit.timeit(f"p = Pingo({obj_size})", setup=IMPORT, number=ntrials)
    print(f"\nTook {dur/ntrials} sec to create Pingo with {obj_size=} and {ntrials=}")


def profile_1d_numpy(obj_size=100, ntrials=1000) -> None:
    init = f"p = Pingo({obj_size})"
    dur = timeit.timeit("d = p.data_1d", setup=";".join([IMPORT, init]), number=ntrials)
    print(
        f"\nTook {dur/ntrials} sec to copy Pingo 1D data with {obj_size=} and"
        f" {ntrials=}"
    )


def profile_1d_vector(obj_size=100, ntrials=1000) -> None:
    init = f"p = Pingo({obj_size})"
    dur = timeit.timeit(
        "d = p.data_1d_vec", setup=";".join([IMPORT, init]), number=ntrials
    )
    print(
        f"\nTook {dur/ntrials} sec to copy Pingo 1D vector data with {obj_size=} and"
        f" {ntrials=}"
    )


def profile_2d_numpy(obj_size=100, ntrials=1000) -> None:
    init = f"p = Pingo({obj_size})"
    dur = timeit.timeit("d = p.data_2d", setup=";".join([IMPORT, init]), number=ntrials)
    print(
        f"\nTook {dur/ntrials} sec to copy Pingo 2D data with {obj_size=} and"
        f" {ntrials=}"
    )


def profile_3d_numpy_copy(obj_size=150, ntrials=1000) -> None:
    init = f"p = Pingo({obj_size})"
    dur = timeit.timeit("d = p.data_3d", setup=";".join([IMPORT, init]), number=ntrials)
    print(
        f"\nTook {dur/ntrials} sec to copy Pingo 3D data (loop copy) with"
        f" {obj_size=} and {ntrials=}"
    )
    # uint8, uint64, float32, bool = 1 + 8 + 4 + 1 bytes
    print(f"Total array size: {obj_size**3 * (1 + 8 + 4 + 1) / 1e9} GB")


def profile_3d_numpy_colmaj(obj_size=50, ntrials=1000) -> None:
    init = f"p = Pingo({obj_size})"
    dur = timeit.timeit(
        "d = p.data_3d_colmaj", setup=";".join([IMPORT, init]), number=ntrials
    )
    print(
        f"\nTook {dur/ntrials} sec to copy Pingo 3D data (loop copy, column major) with"
        f" {obj_size=} and {ntrials=}"
    )
    # uint8, uint64, float32, bool = 1 + 8 + 4 + 1 bytes
    print(f"Total array size: {obj_size**3 * (1 + 8 + 4 + 1) / 1e9} GB")


def profile_3d_numpy_memcpy(obj_size=50, ntrials=1000) -> None:
    init = f"p = Pingo({obj_size})"
    dur = timeit.timeit(
        "d = p.data_3d_memcpy", setup=";".join([IMPORT, init]), number=ntrials
    )
    print(
        f"\nTook {dur/ntrials} sec to copy Pingo 3D data (memcpy) with"
        f" {obj_size=} and {ntrials=}"
    )
    # uint8, uint64, float32, bool = 1 + 8 + 4 + 1 bytes
    print(f"Total array size: {obj_size**3 * (1 + 8 + 4 + 1) / 1e9} GB")


def profile_all(obj_size=50, ntrials=100) -> None:
    profile_init(obj_size, ntrials)
    profile_1d_numpy(obj_size, ntrials)
    profile_1d_vector(obj_size, ntrials)
    profile_2d_numpy(obj_size, ntrials)
    profile_3d_numpy_copy(obj_size, ntrials)
    profile_3d_numpy_colmaj(obj_size, ntrials)
    profile_3d_numpy_memcpy(obj_size, ntrials)


"""
def profile_3d_numpy_memcopy(obj_size=100, ntrials=1000):
    init = f"p = Pingo({obj_size})"
    dur = timeit.timeit(
        "d = p.data_3d_memcpy", setup=[IMPORT, init].join(";"), number=ntrials
    )
    print(f"\nTook {dur} sec to copy Pingo 3D data with {obj_size=} and {ntrials=}")
"""
