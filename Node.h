/* 
 * File:   Node.h
 * Author: kassarza
 *
 * Created on October 13, 2015, 3:01 PM
 */


/*
 * File: Node.h
 */

#ifndef NODE_H
#define NODE_H
#include <string>
#include <iostream>

#include "ResistorList.h"

using namespace std;

//comments in Node.cpp
class Node {
    friend class NodeList;
    
private:
    int nodeID;
    ResistorList resList;
    bool set;
    double voltage;
    Node* previous;
    Node* next;
    
public:
    Node(int num);
    ~Node();
    bool addResistor(Resistor* res);
    void print();
    void setVoltage(double newVoltage);
    void resetVoltage();
    void moveHead();
    void resetHead();
    int connectedResistors();
    void printSolve();
};

#endif /* NODE_H */

