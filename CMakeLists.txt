cmake_minimum_required(VERSION 3.0.0)
project(polygon_operations VERSION 0.1.0)

# Options. Turn on with 'cmake -DENABLE_TEST=ON'.
option(ENABLE_TEST "Build all tests." OFF)

add_subdirectory(src)
add_subdirectory(examples)
if (ENABLE_TEST)
  add_subdirectory(test)
endif()