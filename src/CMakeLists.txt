# set headers
set(header_path ${polygon_operations_SOURCE_DIR}/include/polygon_operations)
set(header_files ${header_path}/convex_hull.h
                ${header_path}/convex_polygon.h
                ${header_path}/utilities.h)

# set source files
set(src convex_hull.cpp
        convex_polygon
		utilities.cpp)

add_library(polygon_operations SHARED ${src})
target_include_directories(polygon_operations PUBLIC ${polygon_operations_SOURCE_DIR}/include)

install(TARGETS polygon_operations DESTINATION ${MAIN_LIB_DESTINATION})
install(FILES ${header_files} DESTINATION ${INCLUDE_DESTINATION})
