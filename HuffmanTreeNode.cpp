/*
 *  HuffmanTreeNode.cpp
 *  Benjamin Silver
 *  April 4, 2023
 *
 *  CS 15 Project 3 Zap
 *
 *  Purpose: Contains the data used to build the Huffman Tree
 */

#include <iostream>
#include <fstream>
#include <string>
#include "HuffmanTreeNode.h"

using namespace std;

// HuffmanTreeNode (constructor)
// Input: A character and its frequency
// Description: Initializes a node object with the provided inputs
// Output: Nothing, but the node is prepared for the huffman tree
HuffmanTreeNode::HuffmanTreeNode(char c, int f) {
    val = c;
    freq = f;
    left = nullptr;
    right = nullptr;
}

// HuffmanTreeNode (constructor)
// Input: A character, its frequency, and pointers to other nodes
// Description: Initializes a node object with the provided inputs
// Output: Nothing, but the node is prepared for the huffman tree
HuffmanTreeNode::HuffmanTreeNode(char c, int f, HuffmanTreeNode *l,
                                 HuffmanTreeNode *r) {
    val = c;
    freq = f;
    left = l;
    right = r;
}

// HuffmanTreeNode::~HuffmanTreeNode() {
// }

// isLeaf
// Input: Nothing
// Description: Determines if a node is a leaf
// Output: True if it is, false if it is not
bool HuffmanTreeNode::isLeaf() const {
    return (left == nullptr and right == nullptr);
}

// get_val
// Input: Nothing
// Description: Returns the ascii character in a node
// Output: The ascii character
char HuffmanTreeNode::get_val() const {
    return val;
}

// get_freq
// Input: Nothing
// Description: Returns the frequency stored in a node
// Output: The frequency of a corresponding ascii character
int HuffmanTreeNode::get_freq() const {
    return freq;
}

// get_left
// Input: Nothing
// Description: Returns a nodes left pointer
// Output: The node being pointed to
HuffmanTreeNode *HuffmanTreeNode::get_left() const {
    return left;
}

// get_left
// Input: Nothing
// Description: Returns a nodes right pointer
// Output: The node being pointed to
HuffmanTreeNode *HuffmanTreeNode::get_right() const {
    return right;
}

// set_left
// Input: A huffman tree node
// Description: Reassigns a node's left pointer
// Output: Nothing, the pointers are updated accordingly
void HuffmanTreeNode::set_left(HuffmanTreeNode* node) {
    left = node;
}

// set_right
// Input: A huffman tree node
// Description: Reassigns a node's right pointer
// Output: Nothing, the pointers are updated accordingly
void HuffmanTreeNode::set_right(HuffmanTreeNode* node) {
    right = node;
}

// Node Comparator operator
// Input: 2 huffman tree nodes 
// Description: Determines if the first node is larger than the second node
// Output: True if it is, false if it is not
bool NodeComparator::operator()(const HuffmanTreeNode *n1,
                                const HuffmanTreeNode *n2) {
    return n1->get_freq() > n2->get_freq();
}