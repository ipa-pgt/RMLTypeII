FROM andrewosh/binder-base
MAINTAINER Lars Tingelstad <lars.tingelstad@ntnu.no>

USER root

RUN apt-get update && apt-get install cmake g++ python-dev

USER main

RUN pip install numpy matplotlib

RUN mkdir build && cd build && cmake .. && cmake --build .
