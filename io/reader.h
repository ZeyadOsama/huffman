//
// Created by Zeyad Osama on 12/10/19.
//

#ifndef HUFFMAN_READER_H
#define HUFFMAN_READER_H

#include "../utils/constants.h"

class Reader {
private:
    /**
     * @brief file path.
     */
    char *m_path;

    /**
     * @brief buffered string to be parsed and decoded.
     */
    std::string m_buffer;

    /**
     * @brief extracts snippet out of string.
     * @param _START to cut before.
     * @param _END to cut after.
     * @return snippet.
     */
    std::string extractSnippet(const char *_START, const char *_END);

    std::string parseHeader();

public:
    explicit Reader(char *inPath);

    /**
     * @brief reads file and buffer it in m_buffer.
     * @return 0 if succeed.
     */
    int readFile();

    /**
     * @return FREQUENCY_MAP for decoding.
     */
    FREQUENCY_MAP getHeader();

    /**
     * @return string TEXT section from encoded file.
     */
    std::string getText();
};


#endif //HUFFMAN_READER_H
