# В современном CMake рекомендуется сразу задавать нужную версию CMake.
cmake_minimum_required(VERSION 3.28)

# Говорим CMake что за проект.
project(args_parse_types LANGUAGES CXX)

# Определяем библиотеку и указываем из чего она состоит.
add_library(types STATIC result.hpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET types PROPERTY CXX_STANDARD 17)
endif()

target_include_directories(types PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

target_compile_features(types PUBLIC cxx_std_17)
