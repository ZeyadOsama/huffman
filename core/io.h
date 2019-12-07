//
// Created by Zeyad Osama on 11/22/19.
//

#ifndef HUFFMAN_IO_H
#define HUFFMAN_IO_H

std::map<char, int> getDecompressedFrequencies(const std::string &path);

std::map<char, int> getCompressedFrequencies(const std::string &path);

int writeCompression(char *inPath, char *outPath, std::map<char, std::string> codeMap, std::map<char, int> freqMap);

int writeDecompression(char *outPath, const std::string &s);

std::string readFile(char *path);

#endif //HUFFMAN_IO_H
