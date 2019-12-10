//
// Created by Zeyad Osama on 11/22/19.
//

#include <iostream>
#include <string>
#include <map>
#include "../io/bitstream.h"
#include "huffman.h"

using namespace std;

void Huffman::printCodes() {
    cout << "Codes:" << endl;
    for (auto const &p : m_codesMap)
        cout << "\t" << p.first << ":\t" << p.second << endl;
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
    for (auto const &p : m_map)
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
    return Huffman::decode(m_minHeap.top(), s);
}

string Huffman::decode(struct MinHeapNode *root, string s) {
    s = toBinaryString(s);
    cout << s << endl;
    string ds;
    struct MinHeapNode *cur = root;
    for (char c : s) {
        if (c == '0')
            cur = cur->left;
        else
            cur = cur->right;

        if (cur->left == nullptr && cur->right == nullptr) {
            ds += cur->data;
            cur = root;
        }
    }
    return ds + '\0';
}