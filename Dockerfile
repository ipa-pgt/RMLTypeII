FROM andrewosh/binder-base
MAINTAINER Lars Tingelstad <lars.tingelstad@ntnu.no>

USER root

RUN apt-get update && apt-get install -y cmake libpython-dev

USER main

RUN pip install numpy matplotlib
RUN curl -SL https://github.com/pybind/pybind11/archive/v1.8.1.tar.gz | tar -xvzC $HOME/notebooks
RUN mkdir build && cd build && cmake .. && cmake --build .
