# В современном CMake рекомендуется сразу задавать нужную версию CMake.
cmake_minimum_required(VERSION 3.28)

# Говорим CMake что за проект.
project(args_parse_folderparser_app LANGUAGES CXX)

# Определяем исполнимый файл и из чего он состоит.
add_executable(args_parse_folderparser "main.cpp"  "catalogTree.hpp" "catalogTree.cpp"
"threadpool.hpp"
"threadpool.cpp")

# Библиотека args_parse должна быть прилинкована к этому исполнимому файлу.
target_link_libraries(args_parse_folderparser PRIVATE args_parse args types)

