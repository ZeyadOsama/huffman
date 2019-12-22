//
// Created by Zeyad Osama on 12/10/19.
//

#include <iostream>
#include <map>
#include <fstream>
#include "writer.h"

using namespace std;

int writer::writeHeader(const string &outPath, const FREQUENCY_MAP &freqMap) {
    ofstream out(outPath, ios::binary | ios::out);
    out << SEP_MAP;
    for (const auto &item : freqMap)
        out << item.first << SEP_CODE << item.second << SEP_CODE_ENTRY;
    out << SEP_MAP_END;
    return 0;
}

int writer::writeText(const string &inPath, const string &outPath, CODE_MAP codeMap) {
    fstream in(inPath, fstream::in);
    ofstream out(outPath, ios::binary | ios::out | ios::app);

    char c = 0;
    unsigned int acc = 0, bitCnt = 0;

    out << SEP_TXT;
    while (in >> noskipws >> c) {
        if (codeMap.find(c) != codeMap.end()) {
            for (char &ch : codeMap[c]) {
                if (ch == '0')
                    acc |= 0;
                else if (ch == '1')
                    acc |= 1;
                if (++bitCnt >= 8) {
                    out.put(acc);
                    acc = 0;
                    bitCnt = 0;
                }
                acc <<= 1;
            }
        } else {
            cout << c << endl;
            fprintf(stderr, "Error occurred while writing to file.");
            return -1;
        }
    }
    out << SEP_TXT_END;
    cout << "100% decompressed" << endl;
    cout << "Writing to file succeeded." << endl;
    return 0;
}