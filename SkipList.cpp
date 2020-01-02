//
// Created by Kemba Konteh on 11/10/19.
//

#include "SkipList.h"

/* The goal of this program is to demonstrates dynamic arrays, pointers, and doubly linked lists.
 * The program describes a Skip List data structure to store integers. The program starts by doing a
 * O(log n) search through the Skip List for a given item (number in our case), by starting at the top
 * left most corner of the front guard(Skip List has front and rear guards, in this case, INT_MIN and
 * INT_MAX as the first and last values at each levels of the Skip List) and move towards the rear guard.
 * Duplicates are not allowed. Meaning, the program will not add values that already exist at that level.
 * Based on a random coin toss,a decision is made (50% chance) as to whether or not we insert a value at
 * a higher level. Values are sorted. */


/* SNode constructor, initializes integer data and next, prev, upLevel, and
 * downLevel to null pointer */
SkipList::SNode::SNode(int data) {
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
    this->upLevel = nullptr;
    this->downLevel = nullptr;
}


/* SkipList constructor requiring a positive integer as depth. The default SkipList has depth of 1,
 * just one doubly-linked list. In here, front and rear guards are dynamically allocated
 * arrays, and also SNode pointer objects created as guards. */
SkipList::SkipList(int depth) 	// = 1)
{
    this->depth = depth;
    frontGuards = new SNode*[depth];
    rearGuards = new SNode*[depth];
    for (int i = 0; i < depth; i++)
    {
        frontGuards[i] = new SNode(INT_MIN);
        rearGuards[i] = new SNode(INT_MAX);
        // cout << frontGuards[i]->data << " , " << rearGuards[i]->data << endl;
        frontGuards[i]->next = rearGuards[i];
        rearGuards[i]->prev = frontGuards[i];
        // cout << frontGuards[i]->data << " , " << rearGuards[i]->data << endl;

    }
    for (int i = 1; i < depth; i++)
    {
        frontGuards[i]->downLevel = frontGuards[i-1];
        rearGuards[i]->downLevel = rearGuards[i-1];
    }
    for (int i = depth - 2; i >= 0; i--)
    {
        frontGuards[i]->upLevel = frontGuards[i+1];
        rearGuards[i]->upLevel = rearGuards[i+1];
    }
}

/* This is the SkipList destructor. This program has been tested as required, under valgrind
 * in the CSS Linux Lab to ensure there is no memory leak. As per instructions, each node
 * is deleted at each level plus the dynamically allocated arrays, front and rear guards */
SkipList::~SkipList()
{
   SNode* currentNode;
   SNode* nextNode;
    for (int i = 0; i < depth ;i++)
    {
        if (frontGuards[i]->next == rearGuards[i])
            continue;
        currentNode = frontGuards[i]->next;
        while( currentNode->next != nullptr)
        {
            nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;

        }
    }
    for(int i = 0; i < depth; i++)
    {
        delete frontGuards[i] ;
        delete rearGuards[i];
    }
    delete[] frontGuards;
    delete[] rearGuards;
}

/* This is the addBefore method that adds a given SNode, places it before the next given node NextNode */
void SkipList::addBefore(SNode* newNode, SNode* nextNode)
{
    // checking necessary conditions before trying to link the nodes together
    assert(newNode != nullptr && nextNode != nullptr && newNode->data < nextNode->data);

    // insert newNode before nextNode, and link all pointers together
    newNode->prev = nextNode->prev;
    newNode->next = nextNode;
    nextNode->prev->next = newNode;
    nextNode->prev = newNode;

    // checking expected conditions after nodes have been linked
    assert (newNode->next == nextNode && nextNode->prev == newNode);
    assert (newNode->prev != nullptr && newNode->prev->data < newNode->data);
}

/* This is the alsoHigher method. Or random coin toss method. Returns true 50% of time, so that each node has a 50%
 * chance of being at higher level, otherwise false. */
bool SkipList::alsoHigher() const
{
    int r = rand();
    if( r%2 == 0 )
        return true;
    else
        return false;
}


/* This is the add method that adds or inserts values into the skip list. Returns true if successfully added and false,
 * otherwise, no duplicates are allowed. The method makes use of while loops and checking
 * to ensure that the next node ahead is not null and moving onto the next one, and so on moving
 * towards the rear guard at every level up to the end */
bool SkipList::Add(int data)
{
    SNode* newNode;
    SNode* newUpper;
    SNode* nextNode;
    nextNode = frontGuards[0]->next;

    while (nextNode->next != nullptr && nextNode->data < data)
    {
        //nextNode = newNode->next;
        nextNode = nextNode->next;
    }
    //cout << "checking add method:"  << endl;
    if (nextNode->data == data)
    {
        cout << "Insertion of duplicates in SkipList is not allowed!" << endl;
        return false;
    }
    else
        {
            //cout << "checking add method:"  << endl;
        newNode = new SNode(data);
        addBefore(newNode, nextNode);
            //cout << "checking add method:"  << endl;

        int level = 1;
        while(alsoHigher() == true && level < depth)
        {
            //cout << "checking add method:"  << endl;
            newUpper = new SNode(data);
            newUpper->downLevel = newNode;
            newNode->upLevel = newUpper;
            nextNode = newNode->prev;
            while(nextNode->upLevel == nullptr)
                nextNode = nextNode->prev;
            nextNode = nextNode->upLevel;
            while(nextNode->next != nullptr && nextNode->data < data)
                nextNode = nextNode->next;
            addBefore(newUpper, nextNode);
            newNode = newUpper;
            level++;
        }
    }
    return true;
}

/* This is the remove method that removes a given value at any level. It returns true if
 * successfully removed, otherwise false. The method makes use of while loops and if statements
 * The method also prints an error message should the value that needs to be deleted not
 * present in the SkipList */
bool SkipList::Remove(int data)
{
    SNode* current;
    SNode*upNode;
    current = frontGuards[depth-1];
    while (current != nullptr)
    {
        while (current->next->data < data)
            current = current->next;
        if (current->next->data == data)
        {
            current = current->next;
            break;
        }
        else
            current = current->downLevel;
    }
    if(current == nullptr)
    {
        cout << "ERROR - " << data << " is not present in the SkipList!" << endl;

        return false;
    }
    while (current->downLevel != nullptr)
        current = current->downLevel;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    upNode = current->upLevel;
    while(upNode != nullptr)
    {
         current = upNode;
         current->prev->next = current->next;
         current->next->prev = current->prev;
         upNode = current->upLevel;
         delete current;
    }
    return true;

}
/* This is the contains method that searches if a given value exists in the SkipList or not.
 * It returns true if found in SkipList, false otherwise. Search begins at the top most left
 * left corner of the front guard to ensure a big O log n (O(log n)) instead of a linear search
 * O(n) and moves towards the rear guard, and so on. */
bool SkipList::Contains(int data)
{
    SNode* current;
    current = frontGuards[depth - 1];
    while(current != nullptr)
    {
        while (current->next->data < data)
            current = current->next;
        if(current->next->data == data)
            return true;
        else
            current = current->downLevel;
    }
    return false;
}
/* This is the friend function used to display all the elements of ​SkipList. Output is displayed as required
 * by the prompt */
ostream &operator<<(ostream &os, const SkipList &list)
{
    SkipList::SNode* current;
    // cout << list.depth << endl;
    for (int i = list.depth - 1; i >= 0; i--)
    {
        os << "Level: " << i << " --\t";
        current = list.frontGuards[i];
        while (current != nullptr)
        {
            os << current->data << ", ";
            current = current->next;

        }
        os << endl;
    }
    return os;

}



