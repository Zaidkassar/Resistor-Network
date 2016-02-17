/* 
 * File:   NodeList.cpp
 * Author: kassarza
 * 
 * Created on November 5, 2015, 3:22 PM
 */

#include "NodeList.h"

NodeList::NodeList() {
    head = NULL;
}

NodeList::NodeList(const NodeList& orig) {
}

NodeList::~NodeList() {
    if (head != NULL)
        delete head;
    head = NULL;
}

Node* NodeList::findNode(int num) {
    if (head == NULL) {
        return insertNode(num);
    }
    Node* find = head;
    while (true) {
        if (find->nodeID == num) {
            return find;
        } else if (find->nodeID > num || find->next == NULL) {
            return insertNode(num);
        }
        find = find->next;
    }
}//returns a pointer to a node with specified nodeID
//if not found the node is created then returned

Node* NodeList::insertNode(int num) {
    if (head == NULL) {
        head = new Node(num);
        return head;
    } else if (head->nodeID > num) {
        Node* temp = new Node(num);
        temp->next = head;
        head->previous = temp;
        head = temp;
        return head;
    }
    Node* find = head;
    while (find->next != NULL && find->next->nodeID < num) {
        find = find->next;
    }
    Node* temp = find->next;
    find->next = new Node(num);
    find->next->next = temp;
    find->next->previous = find;
    return find->next;
}//creates node with specified nodeID then returns a pointer to it
//node is placed in numerical order

void NodeList::resetHeads() {
    Node* temp = head;
    while (temp != NULL) {
        temp->resetHead();
        temp = temp->next;
    }
}//resets the heads of all nodes' resLists to NULL

bool NodeList::checkSolve() {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->set == true && temp->resList.head != NULL) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}//checks to see if solve can be run

void NodeList::print() {
    Node* temp = head;
    while (temp != NULL) {
        temp->print();
        temp = temp->next;
    }
}//prints all nodes

void NodeList::solve() {
    bool stop = false;
    Node* temp = head;
    while (temp != NULL) {
        if (!temp->set) {
            temp->resetVoltage();
        }
        temp = temp->next;
    }
    while (!stop) {
        stop = true;
        temp = head;
        while (temp != NULL) {
            Resistor *res = temp->resList.head;
            double addedRes = 0;
            double addedVRes = 0;
            if (!temp->set && res != NULL) {
                while (res != NULL) {
                    int otherNode = res->getNodeNumber(temp->nodeID);
                    addedRes += (1 / res->resistance);
                    addedVRes += (findNode(otherNode)->voltage / res->resistance);
                    if (res->getNode1() == temp->nodeID)
                        res = res->nextNode1;
                    else
                        res = res->nextNode2;
                }
                double voltage = addedVRes / addedRes;
                if ((temp->voltage - voltage) > MIN_ITERATION_CHANGE)
                    stop = false;
                else if ((voltage - temp->voltage) > MIN_ITERATION_CHANGE)
                    stop = false;
                temp->voltage = voltage;
            }
            temp = temp->next;
        }
    }
    printSolve();
}//solves unset node voltages

void NodeList::printSolve() {
    cout << "Solve:" << endl;
    Node* temp = head;
    while (temp != NULL) {
        temp->printSolve();
        temp = temp->next;
    }
}//prints result of solve