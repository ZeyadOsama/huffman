//
// Created by Zeyad Osama on 12/10/19.
//

#ifndef HUFFMAN_WRITER_H
#define HUFFMAN_WRITER_H

#define FREQUENCY_MAP std::map<char, int>
#define CODE_MAP std::map<char, std::string>

class writer {
public:
/**
 * @param outPath to write at.
 * @param freqMap to be decoded.
 * @return 0 if succeeded;
 */
    static int writeHeader(char *outPath, FREQUENCY_MAP freqMap);

/**
 * @param inPath to read file which includes text to be decoded.
 * @param outPath to write at.
 * @param codeMap to decode text.
 * @return
 */
    static int writeText(char *inPath, char *outPath, CODE_MAP codeMap);
};


#endif //HUFFMAN_WRITER_H
