FROM rikorose/gcc-cmake:latest

# Add all files inside the repo to HOME library
ADD . /home/convex_polygon_library

# Install packages required for visualization
RUN apt-get update && apt-get install -y python3-pip python3-numpy \
    python3-dev python3-matplotlib

# Install packages required for testing
RUN apt-get update && apt-get install -y libgtest-dev libgmock-dev

WORKDIR /home/convex_polygon_library

RUN mkdir build

WORKDIR /home/convex_polygon_library/build

RUN cmake -DENABLE_TEST=ON ..

RUN make
