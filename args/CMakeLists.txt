# В современном CMake рекомендуется сразу задавать нужную версию CMake.
cmake_minimum_required(VERSION 3.28)

# Говорим CMake что за проект.
project(args_parse_args LANGUAGES CXX)

# Определяем библиотеку и указываем из чего она состоит.
add_library(args STATIC boolArg.hpp stringArg.hpp intArg.hpp arg.hpp "arg.cpp" "stringArg.cpp" "intArg.cpp" "boolArg.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET args PROPERTY CXX_STANDARD 17)
endif()

target_include_directories(args PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(args PUBLIC cxx_std_17)
