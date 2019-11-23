//
// Created by Zeyad Osama on 11/22/19.
//

#include <iostream>
#include <map>
#include <fstream>
#include "io.h"

using namespace std;

int writeCompression(char *inPath, char *outPath, map<char, string> codeMap) {
    char c;
    unsigned int acc = 0, bitCnt = 0;
    fstream fin(inPath, fstream::in);
    ofstream out(outPath, ios::binary | ios::out | ios_base::app);
    while (fin >> noskipws >> c) {
        if (codeMap.find(c) != codeMap.end()) {
            acc |= c << bitCnt;
            if (++bitCnt == 8) {
                out.put(acc);
                acc = 0;
                bitCnt = 0;
            }
        } else {
            fprintf(stderr, "Error occurred while writing to file.");
            return -1;
        }
    }
    cout << "Writing to out file succeeded." << endl;
    return 0;
}


map<char, int> getFrequencies(const string &path) {
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
