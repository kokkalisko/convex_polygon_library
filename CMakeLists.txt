cmake_minimum_required(VERSION 3.0.0)
set(PACKAGE_VERSION_MAJOR 0)
set(PACKAGE_VERSION_MINOR 0)
set(PACKAGE_VERSION_PATCH 1)
project(polygon_operations VERSION ${PACKAGE_VERSION_MAJOR}.${PACKAGE_VERSION_MINOR}.${PACKAGE_VERSION_PATCH})


# Options. Turn on with 'cmake -DENABLE_TEST=ON'.
option(ENABLE_TEST "Build all tests." OFF)

# Configuration variables
set(MAIN_LIB_DESTINATION "lib/${CMAKE_PROJECT_NAME}")
set(INCLUDE_DESTINATION "include/${CMAKE_PROJECT_NAME}")
set(CMAKE_DEBUG_POSTFIX _d)

add_subdirectory(src)
add_subdirectory(examples)

if (ENABLE_TEST)
  add_subdirectory(test)
endif()

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "kokkalisko@gmail.com (Kokkkalis Konstantinos)")
set(CPACK_PACKAGE_VERSION_MAJOR "${PACKAGE_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PACKAGE_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PACKAGE_VERSION_PATCH}")
include(CPack)
