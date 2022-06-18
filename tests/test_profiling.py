#!/usr/bin/env python
"""Tests for profiling code."""
import pybind_scikit_example as pbske


def test_init() -> None:
    pbske.profile_init(50, 50)


def test_1d_numpy() -> None:
    pbske.profile_1d_numpy(50, 50)


def test_1d_vector() -> None:
    pbske.profile_1d_vector(50, 50)


def test_2d_numpy() -> None:
    pbske.profile_2d_numpy(50, 50)


def test_3d_numpy_copy() -> None:
    pbske.profile_3d_numpy_copy(50, 50)


def test_3d_numpy_colmaj() -> None:
    pbske.profile_3d_numpy_colmaj(50, 50)


def test_3d_numpy_memcpy() -> None:
    pbske.profile_3d_numpy_memcpy(50, 50)


def test_all() -> None:
    pbske.profile_all(50, 50)
