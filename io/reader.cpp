//
// Created by Zeyad Osama on 12/10/19.
//

#include <iostream>
#include <map>
#include <fstream>
#include "reader.h"

#define SEPARATOR_CHAR_CODE char(131)
#define SEPARATOR_HEADER_ENTRY char(130)
#define SEPARATOR_HEADER char(129)
#define SEPARATOR_TEXT char(128)

using namespace std;

FREQUENCY_MAP reader::readHeader(char *inPath) {
    ifstream in(inPath);
    FREQUENCY_MAP freqMap;
    char ch;
    in.get(ch);
    char key = ch;

    while (ch != SEPARATOR_HEADER) {
        if (ch == SEPARATOR_CHAR_CODE) {
            in.get(ch);
            string s;
            while (ch != SEPARATOR_HEADER_ENTRY) {
                s += ch;
                in.get(ch);
            }
            freqMap[key] = stoi(s);
        } else
            key = ch;
        in.get(ch);
    }
    return freqMap;
}

string reader::readText(char *inPath) {
    ifstream in(inPath);
    char ch = 0;
    bool start = false;
    string s;
    while (ch != SEPARATOR_TEXT) {
        in.get(ch);
        if (ch == SEPARATOR_HEADER) {
            start = true;
            in.get(ch);
        }
        if (start)
            s += ch;
    }
    return s;
//    int headerLength = getHeaderLength(inPath);
//
//    char *buffer = nullptr;
//    long length;
//    FILE *fptr = fopen(inPath, "rb");
//
//    if (fptr) {
//        fseek(fptr, headerLength, SEEK_END);
//        length = ftell(fptr);
//        fseek(fptr, headerLength, SEEK_SET);
//        buffer = (char *) malloc((size_t) length);
//        if (buffer)
//            fread(buffer, sizeof(char), (size_t) length, fptr);
//        fclose(fptr);
//    }
//    if (!buffer)
//        exit(EXIT_FAILURE);
//    return string(buffer);
}