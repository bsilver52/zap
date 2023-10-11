/*
 *  HuffmanCoder.h
 *  Benjamin Silver
 *  April 4, 2023
 *
 *  CS 15 Project 3 Zap
 *
 *  Purpose: Compresses and uncompresses text files
 */

#ifndef __HUFFMANCODER_H__
#define __HUFFMANCODER_H__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include "HuffmanTreeNode.h"
#include "BinaryIO.h"

using namespace std;

class HuffmanCoder {
    public:
        HuffmanCoder();
        void encoder(const string &input_file, const string &output_file);
        void decoder(const string &input_file, const string &output_file);
    private:
        //methods
        void countFreqs(std::istream &text);
        void buildTree();
        void pushNodes();
        void joinNodes();
        void makeCodes();
        void codeHelper(HuffmanTreeNode *first, string code);
        std::string serializeTree(HuffmanTreeNode *root);
        string serializeHelper(HuffmanTreeNode *first, string serialTree);
        HuffmanTreeNode *deserializeTree(std::string serialTree);
        HuffmanTreeNode *deserializeHelper(std::string serialTree, int &index);
        string makeBitstring(istream &input_file);
        void printBits(string bitString);
        string translateBits(string &binary, HuffmanTreeNode *node);
        string checkBadzap(string fileString, HuffmanTreeNode *curr);
        void writeUncompressed(const string &output_file, string text);
        void deleteTree(HuffmanTreeNode *root);

        
        //member variables
        static const int ASCII_CHARS = 256;

        int charCounts[ASCII_CHARS] = {0};
        string charCodes[ASCII_CHARS] = {"\0"};
        priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>,
                       NodeComparator > huffTree;

        HuffmanTreeNode *rootN;
};

#endif