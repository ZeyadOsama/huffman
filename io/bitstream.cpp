//
// Created by Zeyad Osama on 12/7/19.
//

#include <string>
#include <iostream>

using namespace std;

string toBinaryString(const string &s) {
    string bs;
    for (char c : s)
        bs += bitset<8>(c).to_string();
    return bs;
}