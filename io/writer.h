//
// Created by Zeyad Osama on 12/10/19.
//

#ifndef HUFFMAN_WRITER_H
#define HUFFMAN_WRITER_H

#include "../utils/constants.h"

class writer {
public:
    /**
     * @param outPath to write at.
     * @param freqMap to be decoded.
     * @return 0 if succeeded;
     */
    static int writeHeader(const std::string &outPath, const FREQUENCY_MAP &freqMap);

    /**
     * @param inPath to read file which includes text to be decoded.
     * @param outPath to write at.
     * @param codeMap to decode text.
     * @return
     */
    static int writeText(const std::string &inPath, const std::string &outPath, CODE_MAP codeMap);
};


#endif //HUFFMAN_WRITER_H
