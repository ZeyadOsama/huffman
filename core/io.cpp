//
// Created by Zeyad Osama on 11/22/19.
//

#include <iostream>
#include <map>
#include <fstream>
#include <utility>
#include <sstream>

#include "huffman.h"
#include "io.h"

using namespace std;

int writeFile(char *inPath, char *outPath, map<char, string> codeMap) {
    fstream fin(inPath, fstream::in);
    ofstream out(outPath, ios::binary | ios::out);
    out << "T^" << endl;

    char c;
    unsigned int acc = 0, bitCnt = 0;

    while (fin >> noskipws >> c) {
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
    out << endl << "^END";
    cout << "Writing to file succeeded." << endl;
    return 0;
}

int writeHeader(char *outPath, const map<char, int> &freqMap) {
    ofstream out(outPath, ios::binary | ios::out);
    out << "H^" << endl;
    for (auto const &p : freqMap)
        out << p.first << "," << p.second << endl;
    out << "^END_H" << endl;
    return 0;

}

int writeCompression(char *inPath, char *outPath, map<char, string> codeMap, map<char, int> freqMap) {
    writeHeader(outPath, freqMap);
    writeFile(inPath, outPath, codeMap);
    return 0;
}

int writeDecompression(char *outPath, const string &s) {
    ofstream out(outPath, ios::out);
    out << s;
    cout << "Writing to file succeeded." << endl;
    return 0;
}

map<char, int> getDecompressedFrequencies(const string &path) {
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

map<char, int> getCompressedFrequencies(const string &path) {

    map<char, int> map;
    std::ifstream file(path);
    std::string str;
    while (std::getline(file, str)) {
        if (str == "H^")
            continue;
        if (str == "^END_H")
            break;

        vector<string> tokens;
        stringstream check1(str);
        string intermediate;
        while (getline(check1, intermediate, ','))
            tokens.push_back(intermediate);
        char cstr[tokens[0].size() + 1];
        strcpy(cstr, tokens[0].c_str());
        map[cstr[0]] = stoi(tokens[1]);

    }
    return map;
}

string readFile(char *path) {
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

    std::string s(buffer);

    string f = "T^\n";
    s = s.substr(s.find(f) + f.length());
    return s;
}


