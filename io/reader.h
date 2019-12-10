//
// Created by Zeyad Osama on 12/10/19.
//

#ifndef HUFFMAN_READER_H
#define HUFFMAN_READER_H

#define FREQUENCY_MAP std::map<char, int>
#define CODE_MAP std::map<char, std::string>

class reader {
public:
/**
 * @param inPath to read file.
 * @return FREQUENCY_MAP
 */

    static FREQUENCY_MAP readHeader(char *inPath);

/**
 * @param inPath to read file.
 * @return decoded string itself.
 */
    static std::string readText(char *inPath);
};


#endif //HUFFMAN_READER_H
