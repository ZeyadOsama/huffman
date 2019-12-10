//
// Created by Zeyad Osama on 11/22/19.
//

#ifndef HUFFMAN_ENVIRONMENT_H
#define HUFFMAN_ENVIRONMENT_H

#define COMPRESS  "-c"
#define DECOMPRESS "-d"

#include <string>

class Environment {
private:
    char **m_argv;
    int m_argc;
    bool m_isVerbose;

    void set();

public:
    int INPUT_INDEX;
    int OUTPUT_INDEX;

    Environment(int t_argc, char *t_argv[]);

    bool isVerbose();
};

void print_help();

void print_help(const std::string &);

#endif //HUFFMAN_ENVIRONMENT_H
