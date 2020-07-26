cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(VERSION 3.1)

find_package(Boost
  COMPONENTS filesystem
  log)

add_subdirectory(example)
