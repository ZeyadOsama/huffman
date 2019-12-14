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
    /**
     * @brief data value.
     */
    char data;

    /**
     * @brief freq of data value.
     */
    uint freq;

    /**
     * @brief children.
     */
    MinHeapNode *left, *right;

    /**
     * @brief constructor.
     * @param data.
     * @param freq.
     */
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

    std::map<char, int> m_mapFreq;
    std::map<char, std::string> m_codesMap;

    /**
     * @brief used for Huffman tree building.
     * @see @struct MinHeapNode.
     */
    std::priority_queue<MinHeapNode *, std::vector<MinHeapNode *>, compare> m_minHeap;

    /**
     * @brief internal recursive function called by @see std::string decode(std::string s).
     * @param root of Huffman tree.
     * @param s to be decoded
     * @return decoded string.
     */
    static std::string decode(struct MinHeapNode *root, std::string s);

    void buildCodeMap(struct MinHeapNode *node, const std::string &str);

public:
    /**
     * @brief constructor.
     * @param mapFreq to be used in Huffman algorithm.
     */
    explicit Huffman(std::map<char, int> mapFreq);

    /**
     * @brief main function that builds a Huffman Tree.
     */
    void build();

    /**
     * @brief prints huffman codes from  the root of Huffman Tree.
     */
    void printCodes();

    /**
     * @return m_codesMap
     */
    std::map<char, std::string> getCodesMap();

    /**
     * @param s to be decoded.
     * @return decoded string.
     */
    std::string decode(std::string s);
};

#endif