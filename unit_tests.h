/*
 *  unit_tests.h
 *  Benjamin Silver
 *  April 4, 2023
 *
 *  CS 15 Project 3 Zap
 *
 *  Purpose: Tests functions for the HuffmanTreeNode class of Zap
 */

#include <cassert>
#include <sstream>
#include "HuffmanTreeNode.h"

using namespace std;

void constructor1_test() {
    HuffmanTreeNode node('t',3);
    assert(node.get_val() == 't');
    assert(node.get_freq() == 3);
    assert(node.get_left() == nullptr);
    assert(node.get_right() == nullptr);
}

void constructor2_test() {
    HuffmanTreeNode *node1 = new HuffmanTreeNode('t', 3);
    HuffmanTreeNode *node2 = new HuffmanTreeNode('x', 2);
    HuffmanTreeNode *node3 = new HuffmanTreeNode('b', 7);
    HuffmanTreeNode *node4 = new HuffmanTreeNode('u', 9, node1, node3);

    assert(node4->get_val() == 'u');
    assert(node4->get_freq() == 9);
    assert(node4->get_left() == node1);
    assert(node4->get_right() == node3);

    delete node1;
    delete node2;
    delete node3;
    delete node4;
}

void isLeaf_0null() {
    HuffmanTreeNode *node1 = new HuffmanTreeNode('t', 3);
    HuffmanTreeNode *node2 = new HuffmanTreeNode('x', 2);
    HuffmanTreeNode *node3 = new HuffmanTreeNode('b', 7);
    HuffmanTreeNode *node4 = new HuffmanTreeNode('u', 9, node1, node3);
    assert(not node4->isLeaf());
    delete node1;
    delete node2;
    delete node3;
    delete node4;
}

void isLeaf_2null() {
    HuffmanTreeNode *node1 = new HuffmanTreeNode('t', 3);
    HuffmanTreeNode *node2 = new HuffmanTreeNode('x', 2);
    HuffmanTreeNode *node3 = new HuffmanTreeNode('b', 7);
    HuffmanTreeNode *node4 = new HuffmanTreeNode('u', 9, node1, node3);
    assert(node2->isLeaf());
    delete node1;
    delete node2;
    delete node3;
    delete node4;
}

void isLeaf_1null() {
    HuffmanTreeNode *node1 = new HuffmanTreeNode('t', 3);
    HuffmanTreeNode *node2 = new HuffmanTreeNode('x', 2);
    HuffmanTreeNode *node3 = new HuffmanTreeNode('b', 7);
    HuffmanTreeNode *node4 = new HuffmanTreeNode('u', 9);
    node4->set_right(node2);
    assert(not node4->isLeaf());

    delete node1;
    delete node2;
    delete node3;
    delete node4;
}

void setLeft_test() {
    HuffmanTreeNode *node1 = new HuffmanTreeNode('t', 3);
    HuffmanTreeNode *node2 = new HuffmanTreeNode('x', 2);
    HuffmanTreeNode *node3 = new HuffmanTreeNode('b', 7);
    node2->set_left(node1);
    assert(node2->get_left() == node1);
    
    delete node1;
    delete node2;
    delete node3;
}

void setRight_test() {
    HuffmanTreeNode *node1 = new HuffmanTreeNode('t', 3);
    HuffmanTreeNode *node2 = new HuffmanTreeNode('x', 2);
    HuffmanTreeNode *node3 = new HuffmanTreeNode('b', 7);
    node2->set_right(node3);
    assert(node2->get_right() == node3);
    
    delete node1;
    delete node2;
    delete node3;
}

void multipleSets() {
    HuffmanTreeNode *node1 = new HuffmanTreeNode('t', 3);
    HuffmanTreeNode *node2 = new HuffmanTreeNode('x', 2);
    HuffmanTreeNode *node3 = new HuffmanTreeNode('b', 7);
    HuffmanTreeNode *node4 = new HuffmanTreeNode('&', 12);
    HuffmanTreeNode *node5 = new HuffmanTreeNode('<', 2);
    HuffmanTreeNode *node6 = new HuffmanTreeNode('@', 14);
    node2->set_right(node3);
    node2->set_right(node6);
    node2->set_left(node1);
    node2->set_right(node4);
    node2->set_left(node6);
    assert(node2->get_right() == node4);
    assert(node2->get_left() == node6);

    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
    delete node6;
}