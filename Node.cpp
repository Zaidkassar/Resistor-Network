/* 
 * File:   Node.cpp
 * Author: kassarza
 * 
 * Created on October 13, 2015, 3:01 PM
 */

#include "Node.h"
#define MAX_RESISTORS_PER_NODE 5

Node::Node(int num) {
    set = false;
    nodeID = num;
    voltage = 0;
    next = NULL;
    previous = NULL;
}

Node::~Node() {
    previous = NULL;
    if (next != NULL)
        delete next;
    next = NULL;
}

bool Node::addResistor(Resistor* res) {
    resList.addRes(res, nodeID);
}//adds resistor to resList

void Node::print() {
    int numRes = connectedResistors();
    if (numRes > 0) {
        cout << "Connections at node " << nodeID << ": " << numRes << " resistor(s)" << endl;
        Resistor* temp = resList.head;
        while (temp != NULL) {
            temp->print();
            if (temp->getNode1() == nodeID)
                temp = temp->nextNode1;
            else
                temp = temp->nextNode2;
        }
    } else if (set) {
        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout.precision(2);
        cout << "Connections at node " << nodeID << ": " << voltage << " V" << endl;
    }
}// prints the whole node

void Node::setVoltage(double newVoltage) {
    voltage = newVoltage;
    set = true;
}//sets node voltage

void Node::resetVoltage() {
    voltage = 0;
    set = false;
}//unsets node voltage

void Node::moveHead() {
    Resistor* temp = resList.head;
    if (temp->getNode1() == nodeID)
        resList.head = temp->nextNode1;
    else
        resList.head = temp->nextNode2;
}//moves head to the next value in the resList

void Node::resetHead() {
    resList.head = NULL;
}//resets head, used when all resistors deleted

int Node::connectedResistors() {
    int count = 0;
    Resistor* temp = resList.head;
    while (temp != NULL) {
        count++;
        if (temp->getNode1() == nodeID)
            temp = temp->nextNode1;
        else
            temp = temp->nextNode2;
    }
    return count;
}//returns number or resistors in resList

void Node::printSolve() {
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "Node " << nodeID << ": " << voltage << " V" << endl;
}//prints the result of solve