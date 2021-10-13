cmake_minimum_required(VERSION 3.0.0)
project(convex_polygon_library VERSION 0.1.0)

# Options. Turn on with 'cmake -DENABLE_TEST=ON'.
option(ENABLE_TEST "Build all tests." OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

find_package(Eigen3)

if (${EIGEN3_FOUND})
  include_directories(${EIGEN3_INCLUDE_DIR})
else()
  message(STATUS "Eigen3 not found")
endif()

find_package(Python3 COMPONENTS Interpreter Development)
if (${Python3_FOUND})
  include_directories(${Python3_INCLUDE_DIRS})
else()
  message(FATAL_ERROR "Python3 not found, please install it.")
endif()

find_package(NumPy)
if (${PYTHON_NUMPY_FOUND})
  include_directories(${PYTHON_NUMPY_INCLUDE_DIR})
else()
  message(WARNING "Python3 NumPy not found, proceeding with -DWITHOUT_NUMPY."
  " Some functions might not work.")
  add_definitions(-DWITHOUT_NUMPY)
endif()

include_directories(include)
add_library(convex_lib src/convex_hull.cpp src/convex_polygon.cpp src/utilities.cpp)

add_library(visualization_utilities src/visualization_utilities.cpp)
target_link_libraries(visualization_utilities convex_lib)

add_executable(convex_main src/convex_main.cpp)
target_link_libraries(convex_main convex_lib visualization_utilities ${Python3_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if (ENABLE_TEST)

    enable_testing()

    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    add_executable(utilities_test test/utilities_test.cpp)
    target_link_libraries(utilities_test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} convex_lib pthread)

    add_test(NAME utilities_test COMMAND $<TARGET_FILE:utilities_test>)

    add_executable(convex_hull_test test/convex_hull_test.cpp)
    target_link_libraries(convex_hull_test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} convex_lib pthread)

    add_test(NAME convex_hull_test COMMAND convex_hull_test)

    add_executable(convex_polygon_test test/convex_polygon_test.cpp)
    target_link_libraries(convex_polygon_test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} convex_lib pthread)

    add_test(NAME convex_polygon_test COMMAND convex_polygon_test)

endif()