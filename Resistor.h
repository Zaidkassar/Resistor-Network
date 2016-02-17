/* 
 * File:   Resistor.h
 * Author: kassarza
 *
 * Created on October 13, 2015, 3:01 PM
 */

/*
 * File: Resistor.h
 */

#ifndef RESISTOR_H
#define RESISTOR_H
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;


//Comments in Resistor.cpp
class Resistor {
    friend class ResistorList;
    friend class Node;
    friend class NodeList;
    
private:
    double resistance;
    string name;
    int endpointNodeIDs[2];
    Resistor* previous;
    Resistor* next;
    Resistor* nextNode1;
    Resistor* nextNode2;
    Resistor* previousNode1;
    Resistor* previousNode2;
    
public:
    Resistor();
    Resistor(string name_, double resistance_, int endpoints_[2]);
    ~Resistor();
    string getName() const; // returns the name
    double getResistance() const; // returns the resistance
    void setResistance(double resistance_);
    void print();
    friend ostream& operator<<(ostream&, const Resistor&);
    int getNodeNumber(int nodeID);
    int getNode1();
    int getNode2();
};

ostream& operator<<(ostream&, const Resistor&);

#endif /* RESISTOR_H */
