# В современном CMake рекомендуется сразу задавать нужную версию CMake.
cmake_minimum_required(VERSION 3.28)

# Говорим CMake что за проект.
project(args_parse_multy_args LANGUAGES CXX)

# Определяем библиотеку и указываем из чего она состоит.
add_library(multy_args STATIC multyIntArg.hpp multyStringArg.hpp multyBoolArg.hpp multyEmptyArg.hpp
multyIntArg.cpp multyStringArg.cpp multyBoolArg.cpp multyEmptyArg.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET multy_args PROPERTY CXX_STANDARD 17)
endif()

target_include_directories(multy_args PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(multy_args PUBLIC cxx_std_17)
