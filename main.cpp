///
/// main.c
/// Huffman
///
/// @author Zeyad Osama.
/// @date 2019-11-22.
/// @copyright © 2019 Zeyad Osama. All rights reserved.
///

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "utils/help.h"
#include "core/huffman.h"

#include "core/io.h"

using namespace std;

int main(int argc, char *argv[]) {
    map<char, int> m = getFrequencies("/Users/zeyadosama/CLionProjects/Huffman/cmake-build-debug/a.txt");

    for (auto const &p : m) {
        std::cout << p.first << ' ' << p.second << '\n';
    }

    cout << endl;

    Huffman h(m);
    h.build();
    h.printCodes();
    return 0;
}