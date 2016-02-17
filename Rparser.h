/* 
 * File:   Rparser.h
 * Author: kassarza
 *
 * Created on October 15, 2015, 3:49 PM
 */

#ifndef PARSER_H
#define	PARSER_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>

#include "Node.h"
#include "Resistor.h"
#include "NodeList.h"
#include "ResistorList.h"

using namespace std;

int arguments(string line);

//Prints insertR result
void insertR(string name, double resistance, int nodeid1, int nodeid2, NodeList* nodes, ResistorList* resistors);


//Prints modifyR result
void modifyR(string name, double resistance, ResistorList* resistors);

//Prints printR result if input is not "all"
void printR(string name, ResistorList* resistors);

//Prints printR result if input is "all"
void printAll(ResistorList* resistors);

//Prints printNode result if input is not "all"
void printNode(int nodeid, NodeList* nodes);

//Prints printR result if input is "all"
void printNodeAll(NodeList* nodes);

//Prints deleteR result if input is not "all"
void deleteR(string name, NodeList* nodes, ResistorList* resistors);

//Prints deleteR result if input is "all"
void deleteAll(NodeList* nodes, ResistorList* resistors);

void setV(int nodeID, double voltage, NodeList* nodes);

void unsetV(int nodeID, NodeList* nodes);

void solve(NodeList* nodes);

int parser();

#endif	/* PARSER_H */

