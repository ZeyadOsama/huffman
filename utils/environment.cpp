//
// Created by Zeyad Osama on 11/22/19.
//

#include <iostream>
#include "environment.h"

using namespace std;

Environment::Environment(int t_argc, char *t_argv[]) {
    m_argc = t_argc;
    m_argv = t_argv;
    m_isVerbose = false;
    m_isMultiple = false;
    m_isCompress = false;
    INPUT_INDEX = OUTPUT_INDEX = 0;
    set();
}

void Environment::set() {
    for (int i = 1; i < m_argc; ++i) {
        if (!strcmp("-i", m_argv[i]) || !strcmp("--input", m_argv[i]))
            INPUT_INDEX = ++i;
        else if (!strcmp("-o", m_argv[i]) || !strcmp("--output", m_argv[i]))
            OUTPUT_INDEX = ++i;
        else if (!strcmp("-v", m_argv[i]) || !strcmp("--verbose", m_argv[i]))
            m_isVerbose = true;
        else if (!strcmp("-m", m_argv[i]) || !strcmp("--multiple", m_argv[i]))
            m_isMultiple = true;
        else if (!strcmp("-c", m_argv[i]) || !strcmp("--compress", m_argv[i]))
            m_isCompress = true;
    }
}

bool Environment::isVerbose() {
    return m_isVerbose;
}

bool Environment::isMultiple() {
    return m_isMultiple;
}

bool Environment::isCompress() {
    return m_isCompress;
}

void print_help() {
    cout << "Usage:" << endl
         << "\t./Huffman <mode> -i <input-file> -o <output-file>" << endl
         << "\t./Huffman <mode> -m -i <input-folder>" << endl
         << "\t./Huffman <mode> <option> -i <input-file> -o <output-file>" << endl
         << endl

         << "Modes:" << endl
         << "\t-c\t\tCompresses input file." << endl
         << "\t-d\t\tDecompresses input file." << endl
         << endl

         << "Options:" << endl
         << "\t-v\t\tVerbose mode." << endl
         << "\t-m\t\tMultiple mode." << endl
         << endl

         << "Huffman encodes or decodes your file with huffman algorithm." << endl;
}

void print_help(const string &help) {
    cout << help << endl;
}