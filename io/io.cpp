//
// Created by Zeyad Osama on 11/22/19.
//

#include <iostream>
#include <map>
#include <fstream>
#include <cmath>
#include <dirent.h>
#include <sys/stat.h>
#include "../utils/formats.h"
#include "../core/huffman.h"
#include "writer.h"
#include "reader.h"
#include "io.h"

using namespace std;
using namespace format;

void appendFile(const string &outPath, const string &inPath);

string mkdir_dcmp(const std::string &_path);

void rmdir_cmp(const std::string &_path);

int writeCompression(const string &inPath, const string &outPath,
                     const CODE_MAP &codeMap, const FREQUENCY_MAP &freqMap) {
    writer::writeHeader(outPath, freqMap);
    writer::writeText(inPath, outPath, codeMap);
    return 0;
}

int writeDecompression(const string &outPath, const string &s) {
    ofstream out(outPath, ios::out);
    out << s;
    cout << "Writing to file succeeded." << endl;
    return 0;
}

std::string compressFolder(const std::string &_inPath, const bool &_isVerbose) {
    clock_t start_t = clock();

    string _outPath = _inPath;
    _outPath.replace(_outPath.end() - 1, _outPath.end(), EXT_COMP_DIR);
    if (mkdir(_outPath.c_str(), S_IRWXU) == -1)
        cerr << ERROR << strerror(errno) << endl;
    else
        cout << "directory created." << endl;

    struct dirent *entry = nullptr;
    DIR *dp = opendir(_inPath.c_str());
    if (dp != nullptr)
        while ((entry = readdir(dp))) {
            string inPath = _inPath;
            string fileName = entry->d_name;
            if (fileName.find(EXT_TXT) != std::string::npos) {
                inPath.append(fileName);

                map<char, int> m = getFrequencies(inPath);

                Huffman h(m);
                h.build();

                string outPath = _outPath;
                fileName.replace(fileName.end() - strlen(EXT_TXT), fileName.end(), EXT_COMP_TXT);
                outPath.append(fileName);

                // verbose mode.
                if (_isVerbose) {
                    printFrequencies(m);
                    h.printCodes();
                    cout << endl << "file:: in:: " << inPath << endl;
                    cout << "file:: out:: " << outPath << endl;
                }
                writeCompression(inPath, outPath, h.getCodesMap(), m);
            }
        }
    if (_isVerbose)
        printResults(start_t, _inPath, _outPath);

    closedir(dp);
    return _outPath;
}

string mkdir_dcmp(const std::string &_path) {
    string outDir = _path;
    outDir.replace(outDir.end() - strlen(EXT_COMP_TXT), outDir.end(), EXT_DCMP_DIR);
    if (mkdir(outDir.c_str(), S_IRWXU) == -1)
        cerr << "error::  " << strerror(errno) << endl;
    else
        cout << "directory created." << endl;
    return outDir;
}

void rmdir_cmp(const std::string &_path) {
    char *path = const_cast<char *>(_path.c_str());
    struct dirent *entry = nullptr;
    DIR *dir = nullptr;
    dir = opendir(path);
    entry = readdir(dir);
    while (entry) {
        DIR *sub_dir = nullptr;
        FILE *file = nullptr;
        char abs_path[100] = {0};
        if (*(entry->d_name) != '.') {
            sprintf(abs_path, "%s/%s", path, entry->d_name);
            sub_dir = opendir(abs_path);
            if (sub_dir) {
                closedir(sub_dir);
                rmdir_cmp(abs_path);
            } else {
                file = fopen(abs_path, "r");
                if (file) {
                    fclose(file);
                    remove(abs_path);
                }
            }
        }
        entry = readdir(dir);
    }
    remove(path);
}

void extractFile(const std::string &_inPath, const bool &_isVerbose) {
    string _outPath = mkdir_dcmp(_inPath);

    clock_t start_t = clock();

    Reader r(_inPath);
    string buffer = r.readFile();

    int cnt = stoi(r.extractSnippet(SEP_FILE_CNT, SEP_FILE_CNT_END, buffer));
    vector<string> buffers;
    size_t end_map = 0, end_txt = 0, end_path = 0;

    for (int i = 0; i < cnt; ++i) {

        cout << "cnt:: " << i << endl;

        map<char, int> m = r.getMap(r.extractSnippet(SEP_MAP, SEP_MAP_END, buffer, end_map));
        end_map = buffer.find(SEP_MAP_END, end_map);

//        if (_isVerbose)
//            printFrequencies(m);

        string txt = r.extractSnippet(SEP_TXT, SEP_TXT_END, buffer, end_txt);
        end_txt = buffer.find(SEP_TXT_END, end_txt);

        Huffman h(m);
        h.build();

//        if (_isVerbose)
//            h.printCodes();

        string fileName = r.extractSnippet(SEP_PATH, SEP_PATH_END, buffer, end_path);
        end_path = buffer.find(SEP_PATH_END, end_path);

        string outPath = _outPath;
        outPath.append(fileName);

        writeDecompression(outPath, h.decode(txt));
    }
    if (_isVerbose)
        printResults(start_t, _inPath, _outPath);
}

int toFile(const std::string &_path, bool isVerbose) {
    vector<string> paths;
    vector<string> fileNames;

    struct dirent *entry = nullptr;
    DIR *dp = opendir(_path.c_str());
    if (dp != nullptr)
        while ((entry = readdir(dp))) {
            string fileName = entry->d_name;
            if (fileName.find(EXT_TXT) != std::string::npos) {
                string filePath = _path;
                filePath.append(EXT_DIR);
                filePath.append(fileName);
                paths.push_back(filePath);
                fileNames.push_back(fileName);
            }
        }
    // create out path
    string outPath = _path;
    outPath.replace(outPath.end() - strlen(EXT_COMP_DIR), outPath.end(), EXT_TXT);
    ofstream out(outPath, ios::binary | ios::out);
    out << SEP_FILE_CNT << paths.size() << SEP_FILE_CNT_END;

    // write file names.
    for (string p : fileNames)
        out << SEP_PATH << p.replace(p.end() - strlen(EXT_COMP_TXT), p.end(), EXT_TXT) << SEP_PATH_END;
    out.close();

    // write file content.
    for (const string &i : paths)
        appendFile(outPath, i);

    rmdir_cmp(_path);
    return 0;
}

void appendFile(const string &outPath, const string &inPath) {
    ofstream out(outPath, ios::binary | ios::out | ios::app);
    Reader r(inPath);
    out << r.readFile();
    out.close();
}

long long int folderSize(const string &path) {
    // command to be executed
    std::string cmd("du -sb ");
    cmd.append(path);
    cmd.append(" | cut -f1 2>&1");

    // execute above command and get the output
    FILE *stream = popen(cmd.c_str(), "r");
    if (stream) {
        const int max_size = 256;
        char readbuf[max_size];
        if (fgets(readbuf, max_size, stream) != nullptr) {
            return atoll(readbuf);
        }
        pclose(stream);
    }
    // return error val
    return -1;
}

ifstream::pos_type fileSize(const string &filename) {
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

FREQUENCY_MAP getFrequencies(const string &path) {
    map<char, int> map;
    char c = ' ';
    fstream fin(path, fstream::in);
    while (fin >> noskipws >> c) {
        if (map.find(c) != map.end())
            map[c] += 1;
        else map[c] = 1;
    }
    return map;
}

void printFrequencies(const FREQUENCY_MAP &m) {
    cout << "Frequencies:" << endl;
    for (auto const &p : m)
        std::cout << "\t" << p.first << ":\t" << p.second << '\n';
    cout << endl;
}

void printResults(clock_t start_t, const std::string &inPath, const std::string &outPath) {
    ifstream::pos_type inSize = fileSize(inPath);
    ifstream::pos_type outSize = fileSize(outPath);

    cout << endl << "execution time " << tab << tab << cln << tab
         << setprecision(3) << (1.0 * (double) (clock() - start_t) / CLOCKS_PER_SEC) << " sec." << endl;

    cout << "input size " << tab << tab << cln << tab
         << inSize << " bytes."
         << endl;

    string identifier;
    double ratio;
    if (inSize > outSize) {
        identifier = "compression";
        ratio = ceil(((double) outSize / inSize) * 100);
    } else {
        identifier = "decompression";
        ratio = ceil(((double) inSize / outSize) * 100);
    }

    cout << identifier << " size " << tab << cln << tab
         << outSize << " bytes."
         << endl;

    cout << identifier << " ratio " << tab << cln << tab
         << ratio << "%"
         << endl;
}