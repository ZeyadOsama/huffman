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

    std::string parseMap();

public:
    explicit Reader(const std::string &inPath);

    /**
     * @brief reads file and buffer it in m_buffer.
     * @return 0 if succeed.
     */
    std::string readFile();

    /**
     * @return FREQUENCY_MAP for decoding.
     */
    FREQUENCY_MAP getMap(const std::string &_buffer = "");

    /**
     * @return string TEXT section from encoded file.
     */
    std::string getText();

    /**
     * @brief extracts snippet out of string.
     * @param _START to cut before.
     * @param _END to cut after.
     * @return snippet.
     */
    std::string
    extractSnippet(const char *_START, const char *_END, const std::string &_buffer = "", size_t _offset = 0);
};


#endif //HUFFMAN_READER_H
