/* 
 * File:   ResistorList.h
 * Author: kassarza
 *
 * Created on November 5, 2015, 3:23 PM
 */

#ifndef RESISTORLIST_H
#define	RESISTORLIST_H

#include "Resistor.h"

using namespace std;

//comments in ResistorList.cpp
class ResistorList {
    friend class Node;
    friend class NodeList;
    
public:
    ResistorList();
    ResistorList(const ResistorList& orig);
    virtual ~ResistorList();
    Resistor* findRes(string resName);
    void deleteRes(string resName);
    void insertRes(string name_, double resistance_, int endpoints_[2]);
    void addRes(Resistor* res, int nodeID);
    void deleteAll();
    int checkHeads(string resName);
    void destructor();
private:
    Resistor* head;
};

#endif	/* RESISTORLIST_H */

