//
// Created by Zeyad Osama on 11/22/19.
//

#include <iostream>
#include "help.h"

using namespace std;

Environment::Environment(int t_argc, char *t_argv[]) {
    INPUT_INDEX = OUTPUT_INDEX = 0;
    m_argc = t_argc;
    m_argv = t_argv;
    set();
}

void Environment::set() {
    if (m_argc == 4) {
        INPUT_INDEX = 2;
        OUTPUT_INDEX = 3;
    } else if (m_argc == 5) {
        INPUT_INDEX = 3;
        OUTPUT_INDEX = 4;
        m_isVerbose = strcmp(m_argv[2], "--v") == 0;
    }
}

bool Environment::isVerbose() {
    return m_isVerbose;
}

void print_help() {
    cout << "Usage:" << endl
         << "\t./Huffman <-mode> <input-file> <output-file>" << endl
         << endl

         << "Modes:" << endl
         << "\t-c\t\tCompresses input file." << endl
         << "\t-d\t\tDecompresses input file." << endl
         << endl

         //         << "Options:" << endl
         //         << "-o output_file\tName of file to write to" << endl
         //         << "-d\t\tDecode a huffman encoded file" << endl
         //         << "-t\t\tOutput table while encoding" << endl
         //         << "-v\t\tDisplay progressbar" << endl
         //         << "-c\t\tOutput header to STDOUT or read header from STDIN" << endl
         //         << endl

         << "Huffman encodes or decodes your file with huffman algorithm." << endl
         << endl
         << "Written by Zeyad Osama." << endl;
}

void print_help(const string &help) {
    cout << help << endl;
}