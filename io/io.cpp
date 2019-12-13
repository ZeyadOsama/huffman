//
// Created by Zeyad Osama on 11/22/19.
//

#include <iostream>
#include <map>
#include <fstream>
#include <utility>
#include "writer.h"
#include "io.h"

using namespace std;

int writeCompression(const string &inPath, const string &outPath,
                     const CODE_MAP &codeMap, const FREQUENCY_MAP &freqMap) {
    writer::writeHeader(outPath, freqMap);
    writer::writeText(inPath, outPath, codeMap);
    return 0;
}

int writeDecompression(const string &outPath, const string &s) {
    ofstream out(outPath, ios::out);
    out << s;
    cout << "Writing to file succeeded." << endl;
    return 0;
}

FREQUENCY_MAP getFrequencies(const string &path) {
    map<char, int> map;
    char c;
    fstream fin(path, fstream::in);
    while (fin >> noskipws >> c) {
        if (map.find(c) != map.end())
            map[c] += 1;
        else map[c] = 1;
    }
    return map;
}

void printFrequencies(const map<char, int> &m) {
    cout << "Frequencies:" << endl;
    for (auto const &p : m)
        std::cout << "\t" << p.first << ":\t" << p.second << '\n';
    cout << endl;
}
