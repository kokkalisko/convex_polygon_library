FROM rikorose/gcc-cmake:latest

# Add all files inside the repo to HOME library
ADD . /home/polygon_operations

# Install packages required for visualization
RUN apt-get update && apt-get install -y python3-pip python3-numpy \
    python3-dev python3-matplotlib

# Install packages required for testing
RUN apt-get update && apt-get install -y libgtest-dev libgmock-dev

# Configure CMake
WORKDIR /home/polygon_operations
RUN cmake -B /home/polygon_operations/build -DCMAKE_BUILD_TYPE=Release -DENABLE_TEST=ON

# Build
RUN cmake --build /home/polygon_operations/build --config Release

# Install package
WORKDIR /home/polygon_operations/build
RUN cpack -G DEB
RUN dpkg -i *.deb

# Return to source directory
WORKDIR /home/polygon_operations
