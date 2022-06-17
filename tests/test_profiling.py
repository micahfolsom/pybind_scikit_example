#!/usr/bin/env python
"""Tests for profiling code."""
import pybind_scikit_example as pbske


def test_init():
    pbske.profile_init()

def test_1d_numpy():
    pbske.profile_1d_numpy()

def test_1d_vector():
    pbske.profile_1d_vector()

def test_2d_numpy():
    pbske.profile_2d_numpy()

def test_3d_numpy_copy():
    pbske.profile_3d_numpy_copy()
