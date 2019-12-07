//
// Created by Zeyad Osama on 11/22/19.
//

#include <iostream>
#include <map>
#include <fstream>

#include "huffman.h"
#include "io.h"

using namespace std;

int writeCompression(char *inPath, char *outPath, map<char, string> codeMap) {

    int cnt = 0;
    char c;
    unsigned int acc = 0;
    unsigned int bitCnt = 0;
    fstream fin(inPath, fstream::in);
    ofstream out(outPath, ios::binary | ios::out);
    while (fin >> noskipws >> c) {
        if (codeMap.find(c) != codeMap.end()) {
            for (char &ch : codeMap[c]) {

                if (ch == '0')
                    acc |= 0;
                else if (ch == '1')
                    acc |= 1;

                std::bitset<8> x1(acc);

                cout << x1 << " - " << ch << " - " << bitCnt << endl;
                if (++bitCnt >= 8) {

                    std::bitset<8> x(acc);
                    std::cout << x << '\n';
                    cout << endl;

                    out.put(acc);
                    acc = 0;
                    bitCnt = 0;
                    cnt++;
                }
                acc <<= 1;
            }
        } else {
            fprintf(stderr, "Error occurred while writing to file.");
            return -1;
        }
    }

    cout << cnt << endl;
    cout << "Writing to file succeeded." <<
         endl;
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

char *readFile(char *path) {
    static char *buffer = nullptr;
    long length;
    FILE *fptr = fopen(path, "rb");

    if (fptr) {
        fseek(fptr, 0, SEEK_END);
        length = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);
        buffer = (char *) malloc((size_t) length);
        if (buffer)
            fread(buffer, sizeof(char), (size_t) length, fptr);
        fclose(fptr);
#ifdef DEBUG
        cout << "\ninput-file:: reading from file success.\n" << buffer << endl;
#endif
    }

    if (!buffer) {
        exit(EXIT_FAILURE);
    }
#ifdef DEBUG
    cout << "\nbuffer:-\n" << buffer << endl;
#endif


    std::bitset<8> x1(buffer[0]);
    std::bitset<8> x2(buffer[1]);
    std::bitset<8> x3(buffer[length - 2]);
    std::bitset<8> x4(buffer[length - 1]);
    std::cout << x1 << '\n';
    std::cout << x2 << '\n';
    std::cout << x3 << '\n';
    std::cout << length << '\n';

    return buffer;
}
