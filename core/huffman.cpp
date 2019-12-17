//
// Created by Zeyad Osama on 11/22/19.
//

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include "../io/bitstream.h"
#include "../utils/formats.h"
#include "huffman.h"

#define BYTE_LEN 8

using namespace std;
using namespace format;

Huffman::Huffman(std::map<char, int> mapFreq) {
    m_mapFreq = std::move(mapFreq);
}

void Huffman::printCodes() {
    cout << "Codes:" << endl;
    bitset<BYTE_LEN> bs;
    unsigned char ch;
    for (auto const &p : m_codesMap) {
        ch = p.first;
        if (ch == 0xD || ch == 0xA)
            ch = ' ';
        bs = p.first;
        cout << tab << ch << cln
             << tab << (int) p.first
             << tab << bs
             << tab << p.second << endl;
    }
}

void Huffman::buildCodeMap(struct MinHeapNode *node, const string &str) {
    if (!node)
        return;
    if (node->data != CHAR_MIN)
        m_codesMap[node->data] = str;
    buildCodeMap(node->left, str + '0');
    buildCodeMap(node->right, str + '1');
}

void Huffman::build() {
    struct MinHeapNode *left, *right, *top;
    for (auto const &p : m_mapFreq)
        m_minHeap.push(new MinHeapNode(p.first, p.second));
    while (m_minHeap.size() != 1) {
        // extract the two minimum freq items from min heap.
        left = m_minHeap.top();
        m_minHeap.pop();

        right = m_minHeap.top();
        m_minHeap.pop();

        // create a new internal node with frequency equal
        // to the sum of the two nodes frequencies.
        //
        // make the two extracted node as left and right children
        // of this new node. Add this node to the min heap '$' is a special value
        // for internal nodes, not used
        top = new MinHeapNode(CHAR_MIN, left->freq + right->freq);
        top->left = left;
        top->right = right;
        m_minHeap.push(top);
    }
    buildCodeMap(m_minHeap.top(), "");
}

map<char, string> Huffman::getCodesMap() {
    return m_codesMap;
}

string Huffman::decode(string s) {
    return Huffman::decode(m_minHeap.top(), std::move(s));
}

string Huffman::decode(struct MinHeapNode *root, string s) {
    s = toBinaryString(s);
    string decodedString;
    struct MinHeapNode *cur = root;
    for (char c : s) {
        if (c == '0')
            cur = cur->left;
        else
            cur = cur->right;

        if (cur->left == nullptr && cur->right == nullptr) {
            decodedString += cur->data;
            cur = root;
        }
    }
    return decodedString;
}