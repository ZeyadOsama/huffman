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
#include <dirent.h>
#include <sys/stat.h>
#include "utils/environment.h"
#include "core/huffman.h"
#include "io/io.h"
#include "io/reader.h"
#include "utils/constants.h"

using namespace std;

int main(int argc, char *argv[]) {
    // environment initialization.
    if (argc < 4) {
        print_help();
        exit(EXIT_FAILURE);
    }
    Environment e(argc, argv);

    if (e.isCompress()) {
        if (e.isMultiple()) {
            toFile(compressFolder(argv[e.INPUT_INDEX], e.isVerbose()), e.isVerbose());
        } else {
            clock_t start_t = clock();

            map<char, int> m = getFrequencies(argv[e.INPUT_INDEX]);

            Huffman h(m);
            h.build();

            writeCompression(argv[e.INPUT_INDEX], argv[e.OUTPUT_INDEX], h.getCodesMap(), m);

            // verbose mode.
            if (e.isVerbose()) {
                printFrequencies(m);
                h.printCodes();
                printResults(start_t, argv[e.INPUT_INDEX], argv[e.OUTPUT_INDEX]);
            }
        }
    } else {
        if (e.isMultiple()) {
            extractFile(argv[e.INPUT_INDEX], e.isVerbose());
        } else {
            clock_t start_t = clock();

            Reader r(argv[e.INPUT_INDEX]);
            r.readFile();

            map<char, int> m = r.getMap();

            Huffman h(m);
            h.build();

            writeDecompression(argv[e.OUTPUT_INDEX], h.decode(r.getText()));
            cout << "TST1" << endl;

            // verbose mode.
            if (e.isVerbose()) {
                printFrequencies(m);
                h.printCodes();
                printResults(start_t, argv[e.INPUT_INDEX], argv[e.OUTPUT_INDEX]);
            }
        }
    }
    return 0;
}