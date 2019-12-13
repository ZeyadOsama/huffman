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
            string outDir = argv[e.INPUT_INDEX];
            outDir.replace(outDir.end() - 1, outDir.end(), EXT_COMP_DIR);
            if (mkdir(outDir.c_str(), S_IRWXU) == -1)
                cerr << "error::  " << strerror(errno) << endl;
            else
                cout << "directory created." << endl;

            struct dirent *entry = nullptr;
            DIR *dp = opendir(argv[e.INPUT_INDEX]);
            if (dp != nullptr)
                while ((entry = readdir(dp))) {
                    string inPath = argv[e.INPUT_INDEX];
                    string fileName = entry->d_name;
                    if (fileName.find(EXT_TXT) != std::string::npos) {
                        inPath.append(fileName);

                        map<char, int> m = getFrequencies(inPath);

                        Huffman h(m);
                        h.build();

                        string outPath = outDir;
                        fileName.replace(fileName.end() - 4, fileName.end(), EXT_COMP_TXT);
                        outPath.append(fileName);

                        // verbose mode.
                        if (e.isVerbose()) {
                            printFrequencies(m);
                            h.printCodes();
                            cout << endl << "file:: in:: " << inPath << endl;
                            cout << "file:: out:: " << outPath << endl;
                        }
                        writeCompression(inPath, outPath, h.getCodesMap(), m);
                    }
                }
            closedir(dp);
        } else {
            map<char, int> m = getFrequencies(argv[e.INPUT_INDEX]);

            Huffman h(m);
            h.build();

            // verbose mode.
            if (e.isVerbose()) {
                printFrequencies(m);
                h.printCodes();
            }
            writeCompression(argv[e.INPUT_INDEX], argv[e.OUTPUT_INDEX], h.getCodesMap(), m);
        }
    } else {
        if (e.isMultiple()) {
            string outDir = argv[e.INPUT_INDEX];
            outDir.replace(outDir.end() - strlen(EXT_COMP_DIR), outDir.end(), EXT_DCMP_DIR);
            if (mkdir(outDir.c_str(), S_IRWXU) == -1)
                cerr << "error::  " << strerror(errno) << endl;
            else
                cout << "directory created." << endl;

            struct dirent *entry = nullptr;
            DIR *dp = opendir(argv[e.INPUT_INDEX]);
            if (dp != nullptr)
                while ((entry = readdir(dp))) {
                    string inPath = argv[e.INPUT_INDEX];
                    string fileName = entry->d_name;
                    if (fileName.find(EXT_TXT) != std::string::npos) {
                        inPath.append(fileName);

                        Reader r(inPath);
                        r.readFile();
                        map<char, int> m = r.getHeader();

                        Huffman h(m);
                        h.build();

                        string outPath = outDir;
                        fileName.replace(fileName.end() - strlen(EXT_COMP_TXT), fileName.end(), EXT_DCMP_TXT);
                        outPath.append(fileName);

                        // verbose mode.
                        if (e.isVerbose()) {
                            printFrequencies(m);
                            h.printCodes();
                            cout << endl << "file:: in:: " << inPath << endl;
                            cout << "file:: out:: " << outPath << endl;
                        }
                        writeDecompression(outPath, h.decode(r.getText()));
                    }
                }
            closedir(dp);
        } else {
            Reader r(argv[e.INPUT_INDEX]);
            r.readFile();
            map<char, int> m = r.getHeader();
            Huffman h(m);
            h.build();

            // verbose mode.
            if (e.isVerbose()) {
                printFrequencies(m);
                h.printCodes();
            }
            writeDecompression(argv[e.OUTPUT_INDEX], h.decode(r.getText()));
        }
    }
    return 0;
}