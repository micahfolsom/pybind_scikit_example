#!/usr/bin/env python
"""Tests for pingo_cpp bindings."""
import pybind_scikit_example as pbske
import pytest


def test_pingo():
    p_s = pbske.Pingo(pbske.Pingo.Type.Small)
    p_m = pbske.Pingo(pbske.Pingo.Type.Medium)
    assert len(p_m) > len(p_s)

    p_l = pbske.Pingo(pbske.Pingo.Type.Large)
    assert len(p_l) > len(p_m)

    # pybind11 still forces us to get the type correct (takes an int)
    with pytest.raises(TypeError):
        p_s.scale(10.0)
    p_s.scale(10)
