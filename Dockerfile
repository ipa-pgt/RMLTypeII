FROM andrewosh/binder-base
MAINTAINER Lars Tingelstad <lars.tingelstad@ntnu.no>

USER main

RUN pip install numpy matplotlib

RUN mkdir build && cd build && cmake .. && cmake --build .
