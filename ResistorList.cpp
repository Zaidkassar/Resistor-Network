/* 
 * File:   ResistorList.cpp
 * Author: kassarza
 * 
 * Created on November 5, 2015, 3:23 PM
 */

#include "ResistorList.h"

ResistorList::ResistorList() {
    head = NULL;
}

ResistorList::ResistorList(const ResistorList& orig) {
}

ResistorList::~ResistorList() {
    head = NULL;
}

Resistor* ResistorList::findRes(string resName) {
    if (head == NULL) {
        return NULL;
    }
    Resistor* find = head;
    while (true) {
        if (find->name == resName) {
            return find;
        } else if (find->next == NULL) {
            return NULL;
        }
        find = find->next;
    }
}//finds and returns a pointer to a resistor

void ResistorList::deleteRes(string resName) {
    Resistor* temp = findRes(resName);
    int node1 = temp->getNode1();
    int node2 = temp->getNode2();
    if (temp->previous != NULL)
        temp->previous->next = temp->next;
    else
        head = temp->next;
    if (temp->previousNode1 != NULL) {
        if (node1 == temp->previousNode1->getNode1())
            temp->previousNode1->nextNode1 = temp->nextNode1;
        else
            temp->previousNode1->nextNode2 = temp->nextNode1;
    }
    if (temp->previousNode2 != NULL) {
        if (node2 == temp->previousNode2->getNode1())
            temp->previousNode2->nextNode1 = temp->nextNode2;
        else
            temp->previousNode2->nextNode2 = temp->nextNode2;
    }
    if (temp->next != NULL)
        temp->next->previous = temp->previous;
    if (temp->nextNode1 != NULL) {
        if (node1 == temp->nextNode1->getNode1())
            temp->nextNode1->previousNode1 = temp->previousNode1;
        else
            temp->nextNode1->previousNode2 = temp->previousNode1;
    }
    if (temp->nextNode2 != NULL) {
        if (node2 == temp->nextNode2->getNode1())
            temp->nextNode2->previousNode1 = temp->previousNode2;
        else
            temp->nextNode2->previousNode2 = temp->previousNode2;
    }
    delete temp;
}//deletes a resistor and adjoins previous and next resistors in the resistors
//list and the resList for nodes

void ResistorList::insertRes(string name_, double resistance_, int endpoints_[2]) {
    if (head == NULL) {
        head = new Resistor(name_, resistance_, endpoints_);
        return;
    }
    Resistor* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new Resistor(name_, resistance_, endpoints_);
    temp->next->previous = temp;
}//adds a resistor to the resistors list

void ResistorList::addRes(Resistor* res, int nodeID) {
    if (head == NULL) {
        head = res;
        return;
    }
    Resistor* temp = head;
    while ((temp->nextNode1 != NULL && temp->getNode1() == nodeID) ||
            (temp->nextNode2 != NULL && temp->getNode2() == nodeID)) {
        if (temp->getNode1() == nodeID)
            temp = temp->nextNode1;
        else
            temp = temp->nextNode2;
    }
    if (temp->getNode1() == nodeID) {
        temp->nextNode1 = res;
        if (res->getNode1() == nodeID)
            temp->nextNode1->previousNode1 = temp;
        else
            temp->nextNode1->previousNode2 = temp;
    } else {
        temp->nextNode2 = res;
        if (res->getNode1() == nodeID)
            temp->nextNode2->previousNode1 = temp;
        else
            temp->nextNode2->previousNode2 = temp;
    }
}//adds a resistor to resList for nodes

void ResistorList::deleteAll() {
    Resistor* temp = head;
    while (head != NULL) {
        head = head->next;
        delete temp;
        temp = head;
    }
}//deletes all resistors

int ResistorList::checkHeads(string resName) {
    int hold = 0;
    Resistor* temp = findRes(resName);
    if (temp->previousNode1 == NULL)
        hold = 1;
    if (temp->previousNode2 == NULL)
        hold += 2;
    return hold;
}//checks if the resistor is the head of a resList

void ResistorList::destructor() {
    Resistor* temp = head;
    while (head != NULL) {
        head = head->next;
        delete temp;
        temp = head;
    }
}//separate destructor to account for resList which points to resistors.
//This is because resList acts similar to a shallow copy, using a normal destructor
//would cause a double free. This is called in the end of the program to delete 
//the resistor list.
//This is identical to deleteAll but used for clarity.