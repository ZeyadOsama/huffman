//
// Created by Zeyad Osama on 11/22/19.
//

#ifndef HUFFMAN_HELP_H
#define HUFFMAN_HELP_H

#define COMPRESS  "-c"
#define DECOMPRESS "-d"

#include <string>

class environment {
public:
    int INPUT_INDEX;
    int OUTPUT_INDEX;

    void set_argc_positions(int argc);
};

void print_help();

void print_help(const std::string &);

#endif //HUFFMAN_HELP_H
