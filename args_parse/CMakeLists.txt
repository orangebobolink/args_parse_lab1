# В современном CMake рекомендуется сразу задавать нужную версию CMake.
cmake_minimum_required(VERSION 3.28)

# Говорим CMake что за проект.
project(args_parse_library LANGUAGES CXX)

# Определяем библиотеку и указываем из чего она состоит.
add_library(args_parse STATIC parser.hpp "parser.cpp" arg.hpp "arg.cpp" "stringArg.cpp" "intArg.cpp" "boolArg.cpp" "vectorService.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET args_parse PROPERTY CXX_STANDARD 17)
endif()

target_include_directories(args_parse PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(args_parse PUBLIC cxx_std_17)
