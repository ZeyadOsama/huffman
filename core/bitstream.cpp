//
// Created by Zeyad Osama on 12/7/19.
//

#include <string>
#include <iostream>
#include "bitstream.h"

using namespace std;

inline string toBinaryString(const string &s) {
    string bs;
    for (char _char : s)
        bs += bitset<8>(_char).to_string();
    return bs;
}