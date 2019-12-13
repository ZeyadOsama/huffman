//
// Created by Zeyad Osama on 12/10/19.
//

#include <iostream>
#include <map>
#include "reader.h"

using namespace std;

Reader::Reader(const string &inPath) {
    m_path = const_cast<char *>(inPath.c_str());
}

int Reader::readFile() {
    char *buffer = nullptr;
    long length;
    FILE *fptr = fopen(m_path, "rb");
    if (fptr) {
        fseek(fptr, 0, SEEK_END);
        length = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);
        buffer = (char *) malloc((size_t) length);
        if (buffer)
            fread(buffer, sizeof(char), (size_t) length, fptr);
        fclose(fptr);
    }
    if (!buffer)
        exit(EXIT_FAILURE);
    m_buffer = string(buffer);
    return 0;
}

FREQUENCY_MAP Reader::getHeader() {
    string buffer = parseHeader();
    FREQUENCY_MAP freqMap;
    int i = 0;
    char key = buffer[i++];
    while (buffer[i] != '\0') {
        if (buffer[i] == SEPARATOR_CODE) {
            i++;
            string s;
            while (buffer[i] != SEPARATOR_CODE_ENTRY)
                s += buffer[i++];
            freqMap[key] = stoi(s);
        } else
            key = buffer[i];
        i++;
    }
    return freqMap;
}

string Reader::getText() {
    return extractSnippet(SEPARATOR_TEXT, SEPARATOR_TEXT_END);
}

string Reader::parseHeader() {
    return extractSnippet(SEPARATOR_HEADER, SEPARATOR_HEADER_END);
}

string Reader::extractSnippet(const char *_START, const char *_END) {
    string buffer = m_buffer;
    size_t start = buffer.find(_START);
    size_t end = buffer.find(_END, start + 1);
    if (start != string::npos && end != string::npos) {
        start += strlen(_START);
        buffer.erase(0, start);
        buffer.erase(end - start);
        return buffer;
    }
    return nullptr;
}
