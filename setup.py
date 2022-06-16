#!/usr/bin/env python
# From https://github.com/pybind/pybind_scikit_example
import importlib.util
from skbuild import setup

spec = importlib.util.spec_from_file_location(
    "__metadata__", "src/pybind_scikit_example/__metadata__.py"
)
METADATA = importlib.util.module_from_spec(spec)
spec.loader.exec_module(METADATA)

with open("README.md", "r") as f:
    long_description = f.read()

with open("requirements.txt", "r") as f:
    requirements = f.read()
    requirements = [line for line in requirements.split("\n") if line]

setup(
    name=METADATA.__name__,
    version=METADATA.__version__,
    description=METADATA.__description__,
    long_description=long_description,
    long_description_content_type="text/markdown",
    url=METADATA.__url__,
    download_url=f"{METADATA.__url__}/-/tags",
    author=METADATA.__author__,
    author_email=METADATA.__email__,
    maintainer=METADATA.__author__,
    maintainer_email=METADATA.__email__,
    classifiers=METADATA.__classifiers__,
    packages=["pybind_scikit_example"],
    package_dir={"": "src"},
    cmake_install_dir="src/pybind_scikit_example",
    python_requires=">=3.6",
    install_requires=requirements,
    extras_require={"test": ["pytest"]},
    include_package_data=True,
    zip_safe=False,
)
