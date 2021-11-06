# set source files
set(src convex_hull.cpp
        convex_polygon
		utilities.cpp)

add_library(polygon_operations_lib SHARED ${src})
target_include_directories(polygon_operations_lib PUBLIC ${polygon_operations_SOURCE_DIR}/include)
