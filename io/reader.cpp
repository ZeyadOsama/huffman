//
// Created by Zeyad Osama on 12/10/19.
//

#include <iostream>
#include <map>
#include "reader.h"
#include "io.h"

using namespace std;

Reader::Reader(const string &inPath) {
    m_path = const_cast<char *>(inPath.c_str());
}

string Reader::readFile() {
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
    if (!buffer) {
        cerr << ERROR << strerror(errno) << endl;
        exit(EXIT_FAILURE);
    }
    m_buffer = string(buffer);
    free(buffer);
    return m_buffer;
}

FREQUENCY_MAP Reader::getMap(const string &_buffer) {
    string buffer;
    if (_buffer.empty())
        buffer = parseMap();
    else
        buffer = _buffer;

    FREQUENCY_MAP freqMap;
    int i = 0;
    char key = buffer[i++];
    while (buffer[i] != '\0') {
        if (buffer[i] == SEP_CODE) {
            i++;
            string s;
            while (buffer[i] != SEP_CODE_ENTRY)
                s += buffer[i++];
            freqMap[key] = stoi(s);
        } else
            key = buffer[i];
        i++;
    }
    return freqMap;
}

string Reader::getText() {
    return extractSnippet(SEP_TXT, SEP_TXT_END);
}

string Reader::parseMap() {
    return extractSnippet(SEP_MAP, SEP_MAP_END);
}

string Reader::extractSnippet(const char *_START, const char *_END, const std::string &_buffer, size_t _offset) {
    string buffer;
    if (_buffer.empty())
        buffer = m_buffer;
    else buffer = _buffer;

    int offset = 0;
    if (_offset != 0)
        offset = _offset;

    cout << _START << endl << _END << endl << endl;
    size_t start = buffer.find(_START, offset);

    size_t end = buffer.find(_END, start + 1);

    cout << "es::  offset:: " << offset << endl;
    cout << "es::  start:: " << start << endl;
    cout << "es::  end:: " << end << endl;

    if (start != string::npos && end != string::npos) {
        start += strlen(_START);
        buffer.erase(0, start);
        buffer.erase(end - start);
        return buffer;
    }
    return nullptr;
}