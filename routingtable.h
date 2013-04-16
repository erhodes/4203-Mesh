#ifndef ROUTINGTABLE_H
#define ROUTINGTABLE_H

#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

class RoutingTable
{
public:
    RoutingTable();
    void newRoute(string destination, string direction, int distance);
    void printTable();
    string getBestRoute(string destination);
    int getBestDistance(string destination);
    vector<string> getAllDestinations();
    void deleteDestination(string destination);
    void deleteRoute(string destination, string direction);
    void deleteNode(string address);
protected:
    map<string, map<string, int>* > table;

    void printSubTable(map<string, int> *m);
    void clearOldDestinations();
};

#endif // ROUTINGTABLE_H
