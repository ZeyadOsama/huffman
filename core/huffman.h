//
// Created by Zeyad Osama on 11/22/19.
//

#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H

#include <queue>

/**
 * @brief Huffman tree node.
 */
struct MinHeapNode {
    char data;
    uint freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, uint freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

/**
 * @brief Huffman class.
 */
class Huffman {
private:
    /**
     * @brief comparison of two heap nodes.
     */
    struct compare {
        bool operator()(MinHeapNode *l, MinHeapNode *r) {
            return (l->freq > r->freq);
        }
    };

    std::map<char, int> m_map;
    std::map<char, std::string> m_codesMap;

    std::priority_queue<MinHeapNode *, std::vector<MinHeapNode *>, compare>
            m_minHeap;

    void buildCodeMap(struct MinHeapNode *node, const std::string &str);

public:
    explicit Huffman(std::map<char, int> t_map) {
        m_map = std::move(t_map);
    }

/**
 * @brief main function that builds a Huffman Tree.
 */
    void build();

/**
 * @brief prints huffman codes from  the root of Huffman Tree.
 */
    void printCodes();

    std::map<char, std::string> getCodesMap();
};

#endif