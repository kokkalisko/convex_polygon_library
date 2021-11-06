list(APPEND CMAKE_MODULE_PATH "${polygon_operations_SOURCE_DIR}/cmake/modules")

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

add_library(visualization_utilities visualization_utilities.cpp)
target_link_libraries(visualization_utilities polygon_operations)
target_include_directories(visualization_utilities PUBLIC ${polygon_operations_SOURCE_DIR}/include ${polygon_operations_SOURCE_DIR}/examples)

add_executable(example1 example1.cpp)
target_link_libraries(example1 polygon_operations visualization_utilities ${Python3_LIBRARIES})
target_include_directories(visualization_utilities PUBLIC ${polygon_operations_SOURCE_DIR}/include ${polygon_operations_SOURCE_DIR}/examples)

install(TARGETS example1 DESTINATION bin)
