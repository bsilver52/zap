/*
 *  main.cpp
 *  Benjamin Silver
 *  April 4, 2023
 *
 *  CS 15 Project 3 Zap
 *
 *  Purpose: Provide the client a driver file to run Zap
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "HuffmanCoder.h"

using namespace std;

template<typename streamtype>
void fileOpener(streamtype &stream, const string filename);

// main
// Input: The number of command arguments and their names
// Description: Runs the zap compressors and uncompressors
// Output: Returns 0
int main(int argc, char *argv[]) {
    if (argc != 4 or (strcmp(argv[1], "zap") and strcmp(argv[1], "unzap"))) {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile" << endl;
        return EXIT_FAILURE;
    }

    ifstream infile;
    fileOpener(infile, argv[2]);

    HuffmanCoder compression;

    if (strcmp(argv[1], "zap") == 0) {
        compression.encoder(argv[2], argv[3]);
    } else {
        compression.decoder(argv[2], argv[3]);
    }

    infile.close();
    return 0;
}

// fileOpener
// Input: A file stream and its corresponding name
// Description: Checks if a file can be opened
// Output: Nothing (void function)
template<typename streamtype>
void fileOpener(streamtype &stream, const string filename) {
    stream.open(filename);
        
    if (not stream.is_open()) {
        throw runtime_error("Unable to open file " + filename);
    }
}