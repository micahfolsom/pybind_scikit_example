#!/usr/bin/env python
"""Tests for profiling code."""
import pybind_scikit_example as pbske


def test_init():
    pbske.profile_init(50, 50)


def test_1d_numpy():
    pbske.profile_1d_numpy(50, 50)


def test_1d_vector():
    pbske.profile_1d_vector(50, 50)


def test_2d_numpy():
    pbske.profile_2d_numpy(50, 50)


def test_3d_numpy_copy():
    pbske.profile_3d_numpy_copy(50, 50)


def test_3d_numpy_colmaj():
    pbske.profile_3d_numpy_colmaj(50, 50)


def test_3d_numpy_memcpy():
    pbske.profile_3d_numpy_memcpy(50, 50)


def test_all():
    pbske.profile_all(50, 50)
