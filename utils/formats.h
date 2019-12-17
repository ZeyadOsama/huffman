//
// Created by Zeyad Osama on 12/17/19.
//

#ifndef HUFFMAN_FORMATS_H
#define HUFFMAN_FORMATS_H

#include <iostream>
#include <string>
#include <map>
#include <utility>

namespace format {
    template<typename _CharT, typename _Traits>
    inline std::basic_ostream<_CharT, _Traits> &
    tab(std::basic_ostream<_CharT, _Traits> &__os) {
        return __os.put(__os.widen('\t'));
    }

    template<typename _CharT, typename _Traits>
    inline std::basic_ostream<_CharT, _Traits> &
    cln(std::basic_ostream<_CharT, _Traits> &__os) {
        return __os.put(__os.widen(':'));
    }
}

#endif //HUFFMAN_FORMATS_H
