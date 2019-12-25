//
// Created by Zeyad Osama on 12/11/19.
//

#ifndef HUFFMAN_CONSTANTS_H
#define HUFFMAN_CONSTANTS_H

#define SEP_PATH "P_START^"
#define SEP_PATH_END "^P_END"
#define SEP_FILE_CNT "H_START^"
#define SEP_FILE_CNT_END "^H_END"
#define SEP_MAP "M_START^"
#define SEP_MAP_END "^M_END"
#define SEP_TXT "T_START^"
#define SEP_TXT_END "^T_END"

#define SEP_CODE_ENTRY char(129)
#define SEP_CODE char(128)

#define FREQUENCY_MAP std::map<char, int>
#define CODE_MAP std::map<char, std::string>

#define EXT_COMP_DIR "_compress/"
#define EXT_COMP_TXT "_c.txt"
#define EXT_DCMP_DIR "_decompress/"
#define EXT_DCMP_TXT "_d.txt"

#define EXT_TXT ".txt"

#define EXT_DIR "/"

#define ERROR "error::  "

#endif //HUFFMAN_CONSTANTS_H
