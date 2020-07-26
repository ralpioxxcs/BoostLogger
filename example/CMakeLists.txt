include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(test test.cpp ${CMAKE_SOURCE_DIR}/src/logger.cpp)
target_link_libraries(test ${Boost_LIBRARIES} -lpthread)
