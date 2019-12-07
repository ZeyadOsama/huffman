//
// Created by Zeyad Osama on 11/22/19.
//

#ifndef HUFFMAN_IO_H
#define HUFFMAN_IO_H

std::map<char, int> getFrequencies(const std::string &path);

int writeCompression(char *inPath, char *outPath, std::map<char, std::string> codeMap);

char *readFile(char *path);

#endif //HUFFMAN_IO_H
