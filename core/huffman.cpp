//
// Created by Zeyad Osama on 11/22/19.
//

#include <iostream>
#include <string>
#include <map>
#include "huffman.h"

using namespace std;

void Huffman::printCodes() {
    cout << "Codes:" << endl;
    printCodes(m_minHeap.top(), "");
}

void Huffman::printCodes(struct MinHeapNode *root, const string &str) {
    if (!root)
        return;
    if (root->data != '$')
        cout << "\t" << root->data << ": " << str << endl;
    printCodes(root->left, str + '0');
    printCodes(root->right, str + '1');
}

void Huffman::build() {

    struct MinHeapNode *left, *right, *top;

    for (auto const &p : m_map)
        m_minHeap.push(new MinHeapNode(p.first, p.second));

    // Iterate while size of heap doesn't become 1
    while (m_minHeap.size() != 1) {

        // Extract the two minimum
        // freq items from min heap
        left = m_minHeap.top();
        m_minHeap.pop();

        right = m_minHeap.top();
        m_minHeap.pop();

        // Create a new internal node with
        // frequency equal to the sum of the
        // two nodes frequencies. Make the
        // two extracted node as left and right children
        // of this new node. Add this node
        // to the min heap '$' is a special value
        // for internal nodes, not used
        top = new MinHeapNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        m_minHeap.push(top);
    }
}
