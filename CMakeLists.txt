cmake_minimum_required(VERSION 3.21)
project(procedural-builder)

find_package(Geode REQUIRED)

include(${GEODE_CMAKE_PACKAGE})

add_geode_mod(procedural-builder)
