//
// Created by Zeyad Osama on 12/11/19.
//

#ifndef HUFFMAN_CONSTANTS_H
#define HUFFMAN_CONSTANTS_H

#define SEPARATOR_HEADER "H^"
#define SEPARATOR_HEADER_END "^H_END"
#define SEPARATOR_TEXT "T^"
#define SEPARATOR_TEXT_END "^T_END"

#define SEPARATOR_CODE_ENTRY char(129)
#define SEPARATOR_CODE char(128)

#define FREQUENCY_MAP std::map<char, int>
#define CODE_MAP std::map<char, std::string>

#define EXT_COMP_DIR "_compress/"
#define EXT_COMP_TXT "_c.txt"

#define EXT_TXT ".txt"

#endif //HUFFMAN_CONSTANTS_H
