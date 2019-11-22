//
// Created by Zeyad Osama on 11/22/19.
//

#include <map>
#include <fstream>
#include "io.h"

using namespace std;

map<char, int> getFrequencies(const string &path) {
    map<char, int> map;
    char c;
    fstream fin(path, fstream::in);
    while (fin >> noskipws >> c) {
        if (map.find(c) != map.end())
            map[c] += 1;
        else map[c] = 1;
    }
    return map;
}
