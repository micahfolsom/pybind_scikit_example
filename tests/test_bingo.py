#!/usr/bin/env python
"""Tests for bingo_cpp bindings."""
import pybind_scikit_example as pbske
import pytest


def test_run_bingo():
    # Using the wrapper
    pbske.run_bingo_code()

    # Called directly
    pbske.run_bingo(pbske.Choice.Bing)
    pbske.run_bingo(pbske.Choice.Bang)
    pbske.run_bingo(pbske.Choice.Bong)

    # Must use the enum if that's the type of the function argument (no
    # implicit conversion from "int")
    with pytest.raises(TypeError):
        pbske.run_bingo(0)
    # Cast if you need to (in python, I know, I know)
    pbske.run_bingo(pbske.Choice(2))

    # The enums compare to ints just fine, though
    assert pbske.Choice.Bing == 0
    assert pbske.Choice.Bang == 1
    assert pbske.Choice.Bong == 2
