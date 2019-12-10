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


int writeCompression(char *inPath, char *outPath, CODE_MAP codeMap, FREQUENCY_MAP freqMap) {
    writer::writeHeader(outPath, std::move(freqMap));
    writer::writeText(inPath, outPath, std::move(codeMap));
    return 0;
}

int writeDecompression(char *outPath, const string &s) {
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

//int getHeaderLength(char *inPath) {
//    int cnt = 0;
//    char ch;
//    ifstream in(inPath);
//    in.get(ch);
//    while (ch != SEPARATOR_HEADER) {
//        in.get(ch);
//        ++cnt;
//    }
//    return ++cnt;
//}
//
//FREQUENCY_MAP getCompressedFrequencies(const string &path) {
//    map<char, int> map;
//    std::ifstream file(path);
//    std::string str;
//    while (std::getline(file, str)) {
//        if (str == "H^")
//            continue;
//        if (str == "^END_H")
//            break;
//
//        vector<string> tokens;
//        stringstream check1(str);
//        string intermediate;
//        while (getline(check1, intermediate, ','))
//            tokens.push_back(intermediate);
//        char cstr[tokens[0].size() + 1];
//        strcpy(cstr, tokens[0].c_str());
//        map[cstr[0]] = stoi(tokens[1]);
//
//    }
//    return map;
//}


