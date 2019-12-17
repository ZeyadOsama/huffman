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
    out << SEPARATOR_HEADER;
    for (const auto &item : freqMap)
        out << item.first << SEPARATOR_CODE << item.second << SEPARATOR_CODE_ENTRY;
    out << SEPARATOR_HEADER_END;
    return 0;
}

int writer::writeText(const string &inPath, const string &outPath, CODE_MAP codeMap) {
    fstream in(inPath, fstream::in);
    ofstream out(outPath, ios::binary | ios::out | ios::app);

    std::streampos i = 0, fsize = 0;
    fsize = in.tellg();
    in.seekg(0, std::ios::end);
    fsize = in.tellg() - fsize;
    in.seekg(0, std::ios::beg);

    char c = 0;
    unsigned int acc = 0, bitCnt = 0;

    out << SEPARATOR_TEXT;
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
//        i = in.tellg();
//        if (i % 20480)
//            cout << setw(3) << (int) (((double) i / (double) fsize) * 100)
//                 << "% decompressed.\r" << flush;
    }
    out << SEPARATOR_TEXT_END;
    cout << "100% decompressed" << endl;
    cout << "Writing to file succeeded." << endl;
    return 0;
}