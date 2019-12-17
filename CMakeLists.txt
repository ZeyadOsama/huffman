cmake_minimum_required(VERSION 3.15)
project(Huffman)

set(CMAKE_CXX_STANDARD 14)

add_executable(Huffman main.cpp core/huffman.cpp core/huffman.h utils/environment.cpp utils/environment.h io/io.cpp io/io.h io/bitstream.cpp io/bitstream.h io/reader.cpp io/reader.h io/writer.cpp io/writer.h utils/constants.h utils/formats.h)