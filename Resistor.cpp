/* 
 * File:   Resistor.cpp
 * Author: kassarza
 * 
 * Created on October 13, 2015, 3:01 PM
 */

#include "Resistor.h"

Resistor::Resistor(){
    
}

Resistor::Resistor(string name_, double resistance_, int endpoints_[2]){
    resistance = resistance_;
    name = name_;
    endpointNodeIDs[0] = endpoints_[0];
    endpointNodeIDs[1] = endpoints_[1];
    next = NULL;
    previous = NULL;
    nextNode1 = NULL;
    nextNode2 = NULL;
    previousNode1 = NULL;
    previousNode2 = NULL;
}// nextNode & previousNode are used to create additional linked lists for each node
// endpoints_ holds the node indices to which this resistor connects

Resistor::~Resistor(){
    next = NULL;
    previous = NULL;
    nextNode1 = NULL;
    nextNode2 = NULL;
    previousNode1 = NULL;
    previousNode2 = NULL;
}

string Resistor::getName() const{
    return name;
} // returns the name

double Resistor::getResistance() const{
    return resistance;
} // returns the resistance

void Resistor::setResistance(double resistance_){
    resistance = resistance_;
} //Sets resistance

void Resistor::print(){
    
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << left << setw(20) << name << " " << right << setw(8) <<resistance << " Ohms " << endpointNodeIDs[0] <<" -> "<< endpointNodeIDs[1] << endl;
} //Prints resistor

int Resistor::getNodeNumber(int nodeID){
    if (nodeID == endpointNodeIDs[0])
        return endpointNodeIDs[1];
    else 
        return endpointNodeIDs[0];
} //Gets other node the resistor is connected to

int Resistor::getNode1(){
    return endpointNodeIDs[0];
} //Gets the first node the resistor is connected to
int Resistor::getNode2(){
    return endpointNodeIDs[1];
} //Gets the second node the resistor is connected to