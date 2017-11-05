cmake_minimum_required(VERSION 2.6)

project (ScienceDeLaVie)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
set (CMAKE_CXX_FLAGS "-O2")

include_directories(
    ../
)

#add_executable(compress 
#    ../compress_main.cpp
#)

add_executable(parse_file
    ../parser_main.cpp
)


add_executable(compressor
    ../compressor_main.cpp
    ../Basic_Compressor.cpp
    ../LZ77_Compressor.cpp
    ../Huffman_Compressor.cpp
    ../acgt_biblio.cpp
)
