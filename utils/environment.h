//
// Created by Zeyad Osama on 11/22/19.
//

#ifndef HUFFMAN_ENVIRONMENT_H
#define HUFFMAN_ENVIRONMENT_H

#include <string>

class Environment {
private:
    char **m_argv;
    int m_argc;
    bool m_isVerbose;
    bool m_isMultiple;
    bool m_isCompress;

    void set();

public:
    int INPUT_INDEX;
    int OUTPUT_INDEX;

    Environment(int t_argc, char *t_argv[]);

    bool isVerbose();

    bool isMultiple();

    bool isCompress();
};

void print_help();

void print_help(const std::string &);

#endif //HUFFMAN_ENVIRONMENT_H
