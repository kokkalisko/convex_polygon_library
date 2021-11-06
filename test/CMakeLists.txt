enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(utilities_test utilities_test.cpp)
target_link_libraries(utilities_test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} polygon_operations_lib pthread)
target_include_directories(utilities_test PUBLIC ${polygon_operations_SOURCE_DIR}/include)

add_test(NAME utilities_test COMMAND utilities_test)

add_executable(convex_hull_test convex_hull_test.cpp)
target_link_libraries(convex_hull_test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} polygon_operations_lib pthread)
target_include_directories(utilities_test PUBLIC ${polygon_operations_SOURCE_DIR}/include)

add_test(NAME convex_hull_test COMMAND convex_hull_test)

add_executable(convex_polygon_test convex_polygon_test.cpp)
target_link_libraries(convex_polygon_test ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} polygon_operations_lib pthread)

add_test(NAME convex_polygon_test COMMAND convex_polygon_test)