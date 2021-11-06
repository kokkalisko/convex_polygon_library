# polygon_operations

![example workflow](https://github.com/kokkalisko/polygon_operations/actions/workflows/cmake.yml/badge.svg?event=pull_request)


This is a short library written to perform simple operations with polygons in 2D.

The external libraries required for building and linking the executables and the static libraries belong to 3 categories:
1. Standard C++ libraries e.g. `iostream`, `vector`, `algorithm`
2. Libraries required for testing e.g. `GTest`, `GMock`
3. Libraries based on Python required for visualization

No linear algebra libraries were required e.g. `Eigen`, as they would be unnecessary and complicate the simple implementations of the operations.

To perform unit tests for all the functions of the library the `GTest` framework was selected and installed (see Section below).

Although the library was initially developed and debugged without visualization, it was considered a nice idea to provide some tools in order to visualize the scattered points and the shapes. For this reason, a short C++ wrapper for Python's `Matplotlib` plotting library was used. 
The wrapper is included into this package (along with its license) since it is essentially a header. For more info on the wrapper see [here](https://matplotlib-cpp.readthedocs.io/en/latest/).

The package was built using `CMake`.

# Installation (only for Ubuntu)

After installing `CMake` and `GCC` the installation of following packages is required. If no testing is required for the project functions, then the corresponding packages (see right below) can be skipped.

### Necessary packages for testing (optional)
```
sudo apt-get install libgtest-dev libgmock-dev
```
### Necessary packages for visualization
```
sudo apt-get install python3-pip python3-numpy python3-dev python3-matplotlib
```

# Building (only for Ubuntu)
When the installation steps are completed, the commands described below are required
1. Change directory to the package directory
2. Create build folder
```
mkdir build
cd build
```
3. Build the binaries

To build the tests along the other binaries:
```
cmake -DENABLE_TEST=ON 
make
```

To build solely the binaries:
```
cmake .. 
make
```
4. Run an example executable 
```
./examples/example1 
```

The output of the example executable should be a series of graphs and output messages.

6. Perform the tests (optional)
```
cd ./test
ctest -VV
```
# Dockerfile

A dockerfile for Linux (named Dockerfile) was also provided in order to build an image corresponding to a container were the library was already built with `CMake`. In the container the dynamic library of the package (named `libpolygon_operations.so`) is place inside the `/usr/lib/polygon_operations/` directory. The resulting docker image can be found in the following public [repo](https://hub.docker.com/repository/docker/kokkalisko/polygon_operations/) in DockerHub.

# Notes on the structure of the package

The directory layout (after building the package):

    .
    ├── build                   # Folder of compiled files (not existing before building)
    ├── cmake                   # Documentation files
    ├── CMakeLists.txt          # Contains a set of directives and instructions describing the project's source files and targets
    ├── Dockerfile              # File to create a docker image with the built binaries
    ├── .gitignore              # File containing which folders and files should be neglected from git
    ├── .github                 # Folder containing the workflows for CI/CD
    ├── examples                # Example executable demonstrating the functionality
    ├── include		            # Folder containing the project headers
    ├── LICENSE				    # Apache 2.0 license
    ├── README.md
    ├── src                     # Project source files (.cpp file)
    └── test                    # Automated tests (using GTest)
