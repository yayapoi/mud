cmake_minimum_required(VERSION 3.14)

project(dllToMapCreate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(dllToMapCreate SHARED
  dllToMapCreate_global.h
  dlltomapcreate.cpp
  dlltomapcreate.h
)

target_compile_definitions(dllToMapCreate PRIVATE DLLTOMAPCREATE_LIBRARY)
