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
#include "utils/environment.h"
#include "core/huffman.h"
#include "io/io.h"
#include "io/reader.h"

using namespace std;

int main(int argc, char *argv[]) {
    // environment initialization.
    if (argc < 4) {
        print_help();
        exit(EXIT_FAILURE);
    }
    Environment e(argc, argv);

    if (strcmp(argv[1], COMPRESS) == 0) {
        map<char, int> m = getFrequencies(argv[e.INPUT_INDEX]);

        Huffman h(m);
        h.build();

        // verbose mode.
        if (e.isVerbose()) {
            printFrequencies(m);
            h.printCodes();
        }
        writeCompression(argv[e.INPUT_INDEX], argv[e.OUTPUT_INDEX], h.getCodesMap(), m);
    } else if (strcmp(argv[1], DECOMPRESS) == 0) {
        map<char, int> m = reader::readHeader(argv[e.INPUT_INDEX]);

        Huffman h(m);
        h.build();

        // verbose mode.
        if (e.isVerbose()) {
            printFrequencies(m);
            h.printCodes();
        }
        writeDecompression(argv[e.OUTPUT_INDEX], h.decode(reader::readText(argv[e.INPUT_INDEX])));
    }
    return 0;
}