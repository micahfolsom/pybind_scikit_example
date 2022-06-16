#!/usr/bin/env python
"""Tests for pingo_cpp bindings."""
import pybind_scikit_example as pbske
import pytest
import numpy as np


def test_pingo_sizes():
    p_s = pbske.Pingo(pbske.Pingo.Type.Small)
    p_m = pbske.Pingo(pbske.Pingo.Type.Medium)
    assert len(p_m) > len(p_s)

    p_l = pbske.Pingo(pbske.Pingo.Type.Large)
    assert len(p_l) > len(p_m)

    SMA = pbske.Pingo.SMALL_PINGOS
    MED = pbske.Pingo.MEDIUM_PINGOS
    LRG = pbske.Pingo.LARGE_PINGOS
    assert np.shape(p_s.data_1d) == (SMA,)
    assert np.shape(p_m.data_1d) == (MED,)
    assert np.shape(p_l.data_1d) == (LRG,)

    assert np.shape(p_s.data_2d) == (SMA, SMA)
    assert np.shape(p_m.data_2d) == (MED, MED)
    assert np.shape(p_l.data_2d) == (LRG, LRG)

    assert np.shape(p_s.data_3d) == (SMA, SMA, SMA)
    assert np.shape(p_m.data_3d) == (MED, MED, MED)
    assert np.shape(p_l.data_3d) == (LRG, LRG, LRG)


def test_pingo_data():
    p_m = pbske.Pingo(pbske.Pingo.Type.Medium)
    # pybind11 still forces us to get the type correct (takes an int)
    with pytest.raises(TypeError):
        p_m.scale(10.0)
    p_m.scale(10)

    # Type = 2, so that's the initial value for the 1D array
    assert np.all(p_m.data_1d == (np.ones(len(p_m), dtype=int) * 2 * 10))
    assert np.all(p_m.data_2d == (np.ones((len(p_m), len(p_m)), dtype=int) * 2 * 10))
    assert np.all(np.isclose(p_m.data_3d["x"], np.ones(len(p_m), dtype=float) * 100.0))
