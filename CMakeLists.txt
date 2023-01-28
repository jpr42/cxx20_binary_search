cmake_minimum_required(VERSION 3.22)

project(CXX_20_BINARY_SEARCH LANGUAGES "CXX")

add_executable(foo)

target_compile_features(foo PRIVATE cxx_std_20)

target_compile_options(foo PRIVATE
    -Werror
    -pedantic
    -Wall
    -Wextra
)

target_sources(foo PRIVATE main.cpp)
