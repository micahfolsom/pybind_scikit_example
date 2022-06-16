#!/usr/env/bin python
from .bingo_cpp import run_bingo, Choice


def run_python_code() -> None:
    print("pybind_scikit_example.example.run_python_code(): badabing!")


def run_bingo_code() -> None:
    run_bingo(Choice.Bing)
    run_bingo(Choice.Bang)
    run_bingo(Choice.Bong)
    return None


def run_pingo_code() -> None:
    print("pybind_scikit_example.example.run_pingo_code(): badabing!")
    # TODO
    return None
