//
// Created by Zeyad Osama on 11/22/19.
//

#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
#include "../utils/formats.h"
#include "writer.h"

using namespace std;
using namespace format;

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
    char c = ' ';
    fstream fin(path, fstream::in);
    while (fin >> noskipws >> c) {
        if (map.find(c) != map.end())
            map[c] += 1;
        else map[c] = 1;
    }
    return map;
}

void printFrequencies(const FREQUENCY_MAP &m) {
    cout << "Frequencies:" << endl;
    for (auto const &p : m)
        std::cout << "\t" << p.first << ":\t" << p.second << '\n';
    cout << endl;
}

ifstream::pos_type fileSize(const string &filename) {
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

void printResults(clock_t start_t, const std::string &inPath, const std::string &outPath) {
    ifstream::pos_type inSize = fileSize(inPath);
    ifstream::pos_type outSize = fileSize(outPath);

    cout << endl << "execution time " << tab << tab << cln << tab
         << setprecision(3) << (1.0 * (double) (clock() - start_t) / CLOCKS_PER_SEC) << " sec." << endl;

    cout << "input size " << tab << tab << cln << tab
         << inSize << " bytes."
         << endl;

    string identifier;
    double ratio;
    if (inSize > outSize) {
        identifier = "compression";
        ratio = ceil(((double) outSize / inSize) * 100);
    } else {
        identifier = "decompression";
        ratio = ceil(((double) inSize / outSize) * 100);
    }

    cout << identifier << " size " << tab << cln << tab
         << outSize << " bytes."
         << endl;

    cout << identifier << " ratio " << tab << cln << tab
         << ratio << "%"
         << endl;
}