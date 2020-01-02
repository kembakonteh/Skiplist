//
// Created by Kemba Konteh on 11/10/19.
//

#ifndef ASSIGNMENT4_SKIPLIST_H
#define ASSIGNMENT4_SKIPLIST_H

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <string>
#include <ctime>
#include <ostream>
#include <climits>

using namespace std;

class SkipList {
private:
    class SNode{
    public:

        // SNode constructor stores int as data
        explicit SNode(int data);
        // data for SNode
        int data;
        // link to next SNode
        SNode* next;
        // link to prev SNode
        SNode* prev;
        // link to up one level
        SNode* upLevel;
        // link to down one level
        SNode* downLevel;


    };

    // depth of SkipList, levels are 0 to depth-1
    int depth;

    // array of depth SNode* objects as frontGuards linking levels
    // if depth = 2, we'd have frontGuards[0] and frontGuards[1]
    SNode **frontGuards;

    // array of depth SNode* objects as rearGuards linking levels
    SNode **rearGuards;

    // given a SNode, place it before the given NextNode
    void addBefore(SNode *newNode, SNode *nextNode);

    // return true 50% of time,
    // each node has a 50% chance of being at higher level
    bool alsoHigher() const;

public:

    // default SkipList has depth of 1, just one doubly-linked list
    explicit SkipList(int depth = 1);

    // destructor
    virtual ~SkipList();

    // return true if successfully added, no duplicates
    bool Add(int data);

    // return true if successfully removed
    bool Remove(int data);

    // return true if found in SkipList
    bool Contains(int data);

    // friend function to display all the elements of SkipList
    friend ostream &operator<<(ostream &os, const SkipList &list);

};


#endif //ASSIGNMENT4_SKIPLIST_H
