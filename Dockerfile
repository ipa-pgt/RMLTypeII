FROM andrewosh/binder-base
MAINTAINER Lars Tingelstad <lars.tingelstad@ntnu.no>

USER root

ENV CC clang-3.5
ENV CXX clang++-3.5

RUN apt-get update && apt-get install -y cmake libpython-dev clang-3.5

USER main

RUN pip install numpy matplotlib
RUN curl -SL https://github.com/pybind/pybind11/archive/v1.8.1.tar.gz | tar -xvzC $HOME/notebooks
RUN mkdir build && cd build && cmake .. && cmake --build .
