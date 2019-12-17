//
// Created by Zeyad Osama on 11/22/19.
//

#ifndef HUFFMAN_IO_H
#define HUFFMAN_IO_H

#include "../utils/constants.h"

FREQUENCY_MAP getFrequencies(const std::string &path);

void printFrequencies(const FREQUENCY_MAP &m);

/**
 * @param inPath to read file which includes text to be decoded.
 * @param outPath to write at.
 * @param codeMap to decode text.
 * @param freqMap to decode it to be read later in decompression.
 * @return 1 if succeeded.
 */
int writeCompression(const std::string &inPath, const std::string &outPath,
                     const CODE_MAP &codeMap, const FREQUENCY_MAP &freqMap);

/**
 * @param outPath to write at.
 * @param s decompression string.
 * @return 1 if succeeded.
 */
int writeDecompression(const std::string &outPath, const std::string &s);


/**
 * @brief gets size of a given file.
 * @param path of file to know it's size.
 * @return size.
 */
std::ifstream::pos_type fileSize(const std::string &path);

void printResults(clock_t start_t, const std::string &inPath, const std::string &outPath);

#endif //HUFFMAN_IO_H
