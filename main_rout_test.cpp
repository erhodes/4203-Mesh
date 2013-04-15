
#include "routingtable.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    RoutingTable table;
    int input = 0;
    string destination, direction;
    int distance = 0;
    while (true){
        cout << "Enter an option: ";
        cin >> input;
        if (input == 0){
            return 0;
        }
        else if (input ==1){
            cout << "Enter destination: ";
            cin >> destination;
            cout << "Enter Direction: ";
            cin >> direction;
            cout << "Enter Distance: ";
            cin >> distance;
            table.newRoute(destination,direction,distance);
            //table.newRoute("a","b",12);
        }
        else if (input == 2){
            table.printTable();
        }
        else if (input == 3){
            cout << "Enter Destination for best route" << endl;
            cin >> destination;
            cout << "send to " << table.getBestRoute(destination) << endl;
        }
        else if (input == 4){
            cout << "Enter destination to delete" << endl;
            cin >> destination;
            table.deleteDestination(destination);
        }
        else if (input == 5){
            cout << "Enter destination: ";
            cin >> destination;
            cout << "Enter direction to delete: ";
            cin >> direction;
            table.deleteRoute(destination,direction);
        }
        cout << endl;
    }
    return 0;
}
