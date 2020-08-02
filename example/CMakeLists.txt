cmake_minimum_required(VERSION 3.1)
cmake_policy(VERSION 3.1)
project(example)

find_package(
  Boost 
  1.65.1 
  REQUIRED
  COMPONENTS 
  filesystem
  log)

include_directories(${CMAKE_SOURCE_DIR}/..)
add_executable(test test.cpp)
target_link_libraries(test ${Boost_LIBRARIES} -lpthread)
