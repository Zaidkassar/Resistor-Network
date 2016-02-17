#include "Rparser.h"

//Counts the amount of arguments submitted

int arguments(string line) {
    int count = 0;

    stringstream stream(line);
    string temp;

    while (stream >> temp)
        count++;

    return count;
}

//Inserts resistor

void insertR(string name, double resistance, int nodeid1, int nodeid2, NodeList* nodes, ResistorList* resistors) {
    int node[2] = {nodeid1, nodeid2};

    resistors->insertRes(name, resistance, node);
    Resistor* temp = resistors->findRes(name);
    nodes->findNode(nodeid1)->addResistor(temp);
    nodes->findNode(nodeid2)->addResistor(temp);

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "Inserted: resistor " << name << " " << resistance << " Ohms "
            << nodeid1 << " -> " << nodeid2 << endl;
}


//Modify resistor

void modifyR(string name, double resistance, ResistorList* resistors) {
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    Resistor* temp = resistors->findRes(name);
    cout << "Modified: resistor " << name << " from " << temp->getResistance() << " Ohms to " << resistance << " Ohms"
            << endl;

    temp->setResistance(resistance);
}

//Prints resistor if input is not "all"

void printR(string name, ResistorList* resistors) {
    cout << "Print:" << endl;
    resistors->findRes(name)->print();
}

//Prints all resistors ADD

void printAll(ResistorList* resistors) {
    cout << "Print:" << endl;
    //add later
}

//Prints printNode result if input is not "all" ADD

void printNode(int nodeid, NodeList* nodes) {
    cout << "Print:" << endl;
    nodes->findNode(nodeid)->print();
}

//Prints printNode result if input is "all" ADD

void printNodeAll(NodeList* nodes) {
    cout << "Print:" << endl;
    nodes->print();
}

//Deletes a single resistor

void deleteR(string name, NodeList* nodes, ResistorList* resistors) {
    cout << "Deleted: resistor " << name << endl;

    int hold = resistors->checkHeads(name);
    Resistor* temp = resistors->findRes(name);
    if (hold == 1) {
        nodes->findNode(temp->getNode1())->moveHead();
    } else if (hold == 2) {
        nodes->findNode(temp->getNode2())->moveHead();
    } else if (hold == 3) {
        nodes->findNode(temp->getNode1())->moveHead();
        nodes->findNode(temp->getNode2())->moveHead();
    }
    resistors->deleteRes(name);
}

//Deletes all resistors

void deleteAll(NodeList* nodes, ResistorList* resistors) {
    cout << "Deleted: all resistors" << endl;
    nodes->resetHeads();
    resistors->deleteAll();
}

//Sets a node's voltage

void setV(int nodeID, double voltage, NodeList* nodes){
    nodes->findNode(nodeID)->setVoltage(voltage);
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "Set: node " << nodeID << " to " << voltage << " Volts" << endl;
}

//Unsets a node's voltage

void unsetV(int nodeID, NodeList* nodes){
    nodes->findNode(nodeID)->resetVoltage();
    cout << "Unset: the solver will determine the voltage of node " << nodeID << endl;
}

//Solves for all unknown voltages

void solve(NodeList* nodes){
    nodes->solve();
}

int parser() {

    NodeList nodes;
    ResistorList resistors;
    string line, command;
    string name;
    double resistance, voltage;
    int nodeid1, nodeid2, args;
    bool cont = true; //Checks whether or not to continue. False after an error is found

    cout << "> ";
    getline(cin, line); // Get a line from standard input
    while (!cin.eof()) {

        // Put the line in a stringstream for parsing
        // Making a new stringstream for each line so flags etc. are in a known state
        stringstream lineStream(line);
        lineStream >> command;

        //Count amount of arguments
        args = arguments(line);

        if (command == "insertR") {

            //Check errors
            if (args < 2) {
                cout << "Error: too few arguments" << endl;
                cont = false;
            }
            lineStream >> name;
            if (cont && name == "all") {
                cout << "Error: resistor name cannot be the keyword \"all\""
                        << endl;
                cont = false;
            }
            if (cont && args < 3) {
                cout << "Error: too few arguments" << endl;
                cont = false;
            }

            //Checks if next value starts with a number
            if (cont && (lineStream >> ws).peek() != '-' &&
                    ((lineStream >> ws).peek() < '0' || (lineStream >> ws).peek() > '9')) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            lineStream >> resistance;

            //Checks if there are remaining characters, if input is correct there
            //should be whitespace as the next character
            if (cont && (lineStream.peek() != ' ' && lineStream.peek() != '\n'
                    && lineStream.peek() != '\t' && lineStream.peek() != char_traits<wchar_t>::eof())) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            if (cont && resistance < 0) {
                cout << "Error: negative resistance" << endl;
                cont = false;
            }
            if (cont && args < 4) {
                cout << "Error: too few arguments" << endl;
                cont = false;
            }
            if (cont && (lineStream >> ws).peek() != '-' && ((lineStream >> ws).peek() < '0' || (lineStream >> ws).peek() > '9')) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            lineStream >> nodeid1;
            if (cont && (lineStream.peek() != ' ' && lineStream.peek() != '\n' && lineStream.peek() != '\t' && lineStream.peek() != char_traits<wchar_t>::eof())) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            if (cont && args < 5) {
                cout << "Error: too few arguments" << endl;
                cont = false;
            }
            if (cont && (lineStream >> ws).peek() != '-' && ((lineStream >> ws).peek() < '0' || (lineStream >> ws).peek() > '9')) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            lineStream >> nodeid2;
            if (cont && (lineStream.peek() != ' ' && lineStream.peek() != '\n' && lineStream.peek() != '\t' && lineStream.peek() != char_traits<wchar_t>::eof())) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            if (cont && nodeid1 == nodeid2) {
                cout << "Error: both terminals of resistor connect to node "
                        << nodeid1 << endl;
                cont = false;
            }
            if (cont && args > 5) {
                cout << "Error: too many arguments" << endl;
                cont = false;
            }
            if (cont && resistors.findRes(name) != NULL) {
                cout << "Error: resistor " << name << " already exists" << endl;
                cont = false;
            }
            if (cont) {
                insertR(name, resistance, nodeid1, nodeid2, &nodes, & resistors);
            }

        } else if (command == "modifyR") {
            if (args < 2) {
                cout << "Error: too few arguments" << endl;
                cont = false;
            }
            lineStream >> name;
            if (cont && name == "all") {
                cout << "Error: resistor name cannot be the keyword \"all\""
                        << endl;
                cont = false;
            }
            if (cont && (lineStream >> ws).peek() != '-' && ((lineStream >> ws).peek() < '0' || (lineStream >> ws).peek() > '9')) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            lineStream >> resistance;
            if (cont && (lineStream.peek() != ' ' && lineStream.peek() != '\n' && lineStream.peek() != '\t' && lineStream.peek() != char_traits<wchar_t>::eof())) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            if (cont && resistance < 0) {
                cout << "Error: negative resistance" << endl;
                cont = false;
            }
            if (cont && args > 3) {
                cout << "Error: too many arguments" << endl;
                cont = false;
            }
            if (cont && resistors.findRes(name) == NULL) {
                cout << "Error: resistor " << name << " not found" << endl;
                cont = false;
            }
            if (cont)
                modifyR(name, resistance, &resistors);
        } else if (command == "printR") {
            if (args < 2) {
                cout << "Error: too few arguments" << endl;
                cont = false;
            }
            lineStream >> name;
            if (cont && args > 2) {
                cout << "Error: too many arguments" << endl;
                cont = false;
            }
            if (cont && name != "all" && resistors.findRes(name) == NULL) {
                cout << "Error: resistor " << name << " not found" << endl;
                cont = false;
            }
            if (cont && name == "all")
                printAll(&resistors);
            else if (cont)
                printR(name, &resistors);

        } else if (command == "printNode") {
            if (args < 2) {
                cout << "Error: too few arguments" << endl;
                cont = false;
            }

            //Checks if input might be "all"
            if (cont && (lineStream >> ws).peek() == 'a') {
                lineStream >> name;
                if (cont && args > 2) {
                    cout << "Error: too many arguments" << endl;
                    cont = false;
                }
                if (cont && name == "all")
                    printNodeAll(&nodes);
                else if (cont) {
                    cout << "Error: invalid argument" << endl;
                    cont = false;
                }

                //If not "all" expects a number and will return errors for other values
            } else {
                if (cont && (lineStream >> ws).peek() != '-' && ((lineStream >> ws).peek() < '0' || (lineStream >> ws).peek() > '9')) {
                    cout << "Error: invalid argument" << endl;
                    cont = false;
                }
                lineStream >> nodeid1;
                if (cont && (lineStream.peek() != ' ' && lineStream.peek() != '\n' && lineStream.peek() != '\t' && lineStream.peek() != char_traits<wchar_t>::eof())) {
                    cout << "Error: invalid argument" << endl;
                    cont = false;
                }
                if (cont && args > 2) {
                    cout << "Error: too many arguments" << endl;
                    cont = false;
                }
                if (cont)
                    printNode(nodeid1, &nodes);
            }
        } else if (command == "deleteR") {
            if (args < 2) {
                cout << "Error: too few arguments" << endl;
                cont = false;
            }
            lineStream >> name;
            if (cont && args > 2) {
                cout << "Error: too many arguments" << endl;
                cont = false;
            }
            if (cont && name != "all" && resistors.findRes(name) == NULL) {
                cout << "Error: resistor " << name << " not found" << endl;
                cont = false;
            }
            if (cont && name == "all")
                deleteAll(&nodes, &resistors);
            else if (cont)
                deleteR(name, &nodes, &resistors);

        } else if(command == "setV"){
            if (args < 2) {
                cout << "Error: too few arguments" << endl;
                cont = false;
            }
            if (cont && (lineStream >> ws).peek() != '-' && ((lineStream >> ws).peek() < '0' || (lineStream >> ws).peek() > '9')) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            lineStream >> nodeid1;
            if (cont && (lineStream.peek() != ' ' && lineStream.peek() != '\n' && lineStream.peek() != '\t' && lineStream.peek() != char_traits<wchar_t>::eof())) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            if (cont && (lineStream >> ws).peek() != '-' && ((lineStream >> ws).peek() < '0' || (lineStream >> ws).peek() > '9')) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            lineStream >> voltage;
            if (cont && (lineStream.peek() != ' ' && lineStream.peek() != '\n' && lineStream.peek() != '\t' && lineStream.peek() != char_traits<wchar_t>::eof())) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            if (cont && args > 3) {
                cout << "Error: too many arguments" << endl;
                cont = false;
            }
            if (cont)
                setV(nodeid1, voltage, &nodes);
        } else if(command == "unsetV"){
            if (args < 1) {
                cout << "Error: too few arguments" << endl;
                cont = false;
            }
            if (cont && (lineStream >> ws).peek() != '-' && ((lineStream >> ws).peek() < '0' || (lineStream >> ws).peek() > '9')) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            lineStream >> nodeid1;
            if (cont && (lineStream.peek() != ' ' && lineStream.peek() != '\n' && lineStream.peek() != '\t' && lineStream.peek() != char_traits<wchar_t>::eof())) {
                cout << "Error: invalid argument" << endl;
                cont = false;
            }
            if (cont && args > 2) {
                cout << "Error: too many arguments" << endl;
                cont = false;
            }
            if (cont)
                unsetV(nodeid1, &nodes);
        } else if(command == "solve"){
            if (args > 1) {
                cout << "Error: too many arguments" << endl;
                cont = false;
            }
            if (nodes.checkSolve() == false){
                cout << "Error: no nodes have their voltage set" << endl;
                cont = false;
            }
            if (cont)
                solve(&nodes);
        } else {
            cout << "Error: invalid command" << endl;
        }

        //Returns cont to true for next loop
        cont = true;
        cout << "> ";
        getline(cin, line);

        //Reset command value
        command = " ";
    } // End input loop until EOF.
    resistors.destructor();
    return 0;
}
