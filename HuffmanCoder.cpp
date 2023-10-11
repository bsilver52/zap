/*
 *  HuffmanCoder.cpp
 *  Benjamin Silver
 *  April 4, 2023
 *
 *  CS 15 Project 3 Zap
 *
 *  Purpose: Allows the client to compress and decompress text files through
 *  Huffman coding.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include "HuffmanCoder.h"

using namespace std;

// HuffmanCoder (constructor)
// Input: Nothing
// Description: Initializes the member variable of the Huffman Coder class
// Output: Nothing, but the compressor prepared for the client
HuffmanCoder::HuffmanCoder() {
    rootN = nullptr;
}

// encoder
// Input: Input and output file names 
// Description: Compresses a text file
// Output: Nothing, but an output file is produced for the client
void HuffmanCoder::encoder(const string &input_file,
                           const string &output_file) {
    //construct the huffman tree and zap file inputs
    ifstream input(input_file);
    countFreqs(input);
    buildTree();
    string serialString = serializeTree(rootN);
    string fileEncoding = makeBitstring(input);
    
    //write zap file and terminate program
    BinaryIO binaryZap;
    binaryZap.writeFile(output_file, serialString, fileEncoding);
    printBits(fileEncoding);
    deleteTree(rootN);
}

// countFreqs
// Input: A stream containing the input file text 
// Description: Counts the number of each ASCII character in the text
// Output: Nothing, but an array of character counts is updated
void HuffmanCoder::countFreqs(std::istream &text) {
    char fileChar;
    
    //count character frequencies
    while (text.get(fileChar)) {
        int letterVal = int(fileChar);
        charCounts[letterVal]++;
    }

    //reset file pointer
    text.clear();
    text.seekg(0);
}

// buildTree
// Input: Nothing 
// Description: Constructs a huffman tree from a character frequency array
// Output: Nothing, but the node pointers in the tree are assigned
void HuffmanCoder::buildTree() {
    pushNodes();
    joinNodes();
    makeCodes();
}

// pushNodes
// Input: Nothing
// Description: Creates nodes for each unique character in the input file
// and stores them in a priority queue
// Output: Nothing, but the prioriy is updated
void HuffmanCoder::pushNodes() {
    for (int i = 0; i < ASCII_CHARS; i++) {
        int frequency = charCounts[i];
        
        //only make nodes for ascii chars in the text
        if (frequency != 0) {
            char fileChar = char(i);
            HuffmanTreeNode *node = new HuffmanTreeNode(fileChar, frequency);
            huffTree.push(node);
        }
    }
}

// joinNodes
// Input: Nothing 
// Description: Joins the lowest frequency nodes in a priority queue
// until only one node remains
// Output: Nothing, but the huffman tree is constructed
void HuffmanCoder::joinNodes() {
    while(huffTree.size() != 1) {
        //get lowest frequencies
        HuffmanTreeNode *node1 = huffTree.top();
        huffTree.pop();
        HuffmanTreeNode *node2 = huffTree.top();
        huffTree.pop();

        //create new node and push onto priority queue
        int newFreq = node1->get_freq() + node2->get_freq();
        HuffmanTreeNode *parent = new HuffmanTreeNode('\0', newFreq, node1,
                                                      node2);
        huffTree.push(parent);
    }

    rootN = huffTree.top();
}

// makeCodes
// Input: Nothing 
// Description: Generates binary codes for each unique character in the input
// file
// Output: Nothing, but an array of binary codes is updated
void HuffmanCoder::makeCodes() {
    HuffmanTreeNode *first = rootN;
    string code;
    codeHelper(first, code);
}

// codeHelper
// Input: Nothing 
// Description: Helper function for makeCodes
// Output: Nothing
void HuffmanCoder::codeHelper(HuffmanTreeNode *first, string code) {
    //handle case where node has a letter 
    if (first->isLeaf()) {
        int letterVal = int(first->get_val());
        charCodes[letterVal] = code;
    //recursive calls on left and right nodes
    } else {
        codeHelper(first->get_left(), code + "0");
        codeHelper(first->get_right(), code + "1");
    }
}

// serializeTree
// Input: The huffman tree root node
// Description: Converts a huffman tree to a string of internal and leaf nodes
// through a preorder traversal
// Output: A string, representing the serialized tree
std::string HuffmanCoder::serializeTree(HuffmanTreeNode *root) {
    HuffmanTreeNode *dummy = root;
    string serialTree;
    string s = serializeHelper(dummy, serialTree);
    return s;
}

// serializeHelper
// Input: The huffman tree root node and the serialized string
// Description: Helper function for serializeTree
// Output: The updated serialized tree string
string HuffmanCoder::serializeHelper(HuffmanTreeNode *first,
                                     string serialTree) {
    //handle empty tree case
    if (first == nullptr) {
        return serialTree;
    }

    //handle internal nodes
    if (first->get_val() == '\0') {
        serialTree += "I";
    
    //handle leaf nodes
    } else {
        string s(1, first->get_val());
        serialTree += "L" + s;
    }

    //recursive calls on left an right subtrees
    serialTree = serializeHelper(first->get_left(), serialTree);
    serialTree = serializeHelper(first->get_right(), serialTree);

    return serialTree;
}

// deserializeTree
// Input: A serialized huffman tree string
// Description: Constructs a huffman tree from its preorder traversal
// Output: A node pointer to the huffman tree root
HuffmanTreeNode *HuffmanCoder::deserializeTree(std::string serialTree) {
    int index = 0;
    return deserializeHelper(serialTree, index);
}

// deserializeHelper
// Input: The serialized huffman tree string and a pointer to its position
// Description: Helper function for deserializeTree
// Output: A node pointer to the huffman tree root
HuffmanTreeNode *HuffmanCoder::deserializeHelper(std::string serialTree,
                                                int &index) {
    int stringSize = serialTree.size();

    //handle empty strings
    if (index >= stringSize) {
        return nullptr;
    }

    char serialChar = serialTree[index++];

    //check for internal nodes
    if (serialChar == 'I'){
        HuffmanTreeNode *node = new HuffmanTreeNode('\0', 0);
        node->set_left(deserializeHelper(serialTree, index));
        node->set_right(deserializeHelper(serialTree, index));
        return node;
    
    //create a leaf for chars in the tree 
    } else {
        char val = serialTree[index++];
        HuffmanTreeNode *node = new HuffmanTreeNode(val, 0);
        return node;
    }
    
    return nullptr;
}

// makeBitstring
// Input: An input file stream
// Description: Converts an input file to binary using its huffman tree 
// Output: A string, representing the encoded file text
string HuffmanCoder::makeBitstring(istream &input_file) {
    string bitString;
    char fileChar;
    
    //count the frequencies
    while (input_file.get(fileChar)) {
        int letterVal = int(fileChar);
        bitString += charCodes[letterVal];
    }

    return bitString;
}

// printBits
// Input: The encoded file text string
// Description: Counts the bits in an encoded file string
// Output: Nothing, but a message containing the bit size to the terminal
void HuffmanCoder::printBits(string bitString) {
    int size = bitString.length();
    cout << "Success! Encoded given text using " << size << " bits." << endl;
}

// decoder
// Input: Input and output file names 
// Description: Unompresses a text file
// Output: Nothing, but an output file is produced for the client
void HuffmanCoder::decoder(const string &input_file,
                           const string &output_file) {
    //read the zap fie
    BinaryIO binaryUnzap;
    pair<string, string> zapFile = binaryUnzap.readFile(input_file);
    HuffmanTreeNode *deserialRoot = deserializeTree(zapFile.first);
    rootN = deserialRoot;

    //decode binary string and write to text file
    string fileText = translateBits(zapFile.second, deserialRoot);
    writeUncompressed(output_file, fileText);
    deleteTree(rootN);
}

// translateBits
// Input: A binary encoding and the huffman tree root
// Description: Translate an encoding to ascii characters 
// Output: A string, representing the decoded text
string HuffmanCoder::translateBits(string &binary, HuffmanTreeNode *node) {
    string fileString;
    int binarySize = binary.size();

    for (int i = 0; i < binarySize; i++) {

        //print out ascii char at leafs and reset node pointer
        if (node->isLeaf()) {
            fileString += node->get_val();
            node = rootN;
        }

        //traverse appropriate subtree
        if (binary.at(i) == '0') {
            node = node->get_left();
        } else {
            node = node->get_right();
        }
    }

    return checkBadzap(fileString, node);
}

// checkBadzap
// Input: A
// Description: Throws an error for bad zap files
// Output: The function terminates if an error is thrown or returns the
// original text string if it is acceptable
string HuffmanCoder::checkBadzap(string fileString, HuffmanTreeNode *curr) {
    if (not curr->isLeaf()) {
        throw runtime_error("Encoding did not match Huffman tree.");
    } else {
        fileString += curr->get_val();
        return fileString;
    }
}

// writeUncompressed
// Input: An output file string and its contents
// Description: Writes the decoded string to an output file
// Output: Nothing, but an output file is produced
void HuffmanCoder::writeUncompressed(const string &output_file, string text) {
    ofstream outputFile(output_file);
    outputFile << text;
    outputFile.close();
}

void HuffmanCoder::deleteTree(HuffmanTreeNode *root) {
    //return when all nodes have been deleted
    if (root == nullptr) {
        return;
    }

    deleteTree(root->get_left());
    deleteTree(root->get_right());
    delete root;
}