///
/// main.c
/// Huffman
///
/// @author Zeyad Osama.
/// @date 2019-11-22.
/// @copyright © 2019 Zeyad Osama. All rights reserved.
///

#include <iostream>
#include <map>
#include "utils/help.h"
#include "core/huffman.h"
#include "core/io.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        print_help();
        exit(-1);
    }
    Environment e(argc, argv);

    if (strcmp(argv[1], COMPRESS) == 0) {
        map<char, int> m = getFrequencies(argv[e.INPUT_INDEX]);
        if (e.isVerbose()) {
            cout << "Frequencies:" << endl;
            for (auto const &p : m)
                std::cout << "\t" << p.first << ":\t" << p.second << '\n';
            cout << endl;
        }
        Huffman h(m);
        h.build();
        if (e.isVerbose())
            h.printCodes();
        writeCompression(argv[e.INPUT_INDEX], argv[e.OUTPUT_INDEX], h.getCodesMap());
    } else if (strcmp(argv[1], DECOMPRESS) == 0) {

    }
    return 0;
}