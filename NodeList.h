/* 
 * File:   NodeList.h
 * Author: kassarza
 *
 * Created on November 5, 2015, 3:22 PM
 */

#ifndef NODELIST_H
#define	NODELIST_H

#define MIN_ITERATION_CHANGE 0.0001

#include "Node.h"

using namespace std;

//comments in NodeList.cpp
class NodeList {
public:
    NodeList();
    NodeList(const NodeList& orig);
    virtual ~NodeList();
    Node* findNode(int nodeID);
    Node* insertNode(int nodeID);
    void resetHeads();
    bool checkSolve();
    void print();
    void solve();
    void printSolve();
    
private:
    Node* head;
};

#endif	/* NODELIST_H */

