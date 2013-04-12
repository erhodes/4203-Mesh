#include "routingtable.h"


RoutingTable::RoutingTable(){

}

void RoutingTable::newRoute(string destination, string direction, int distance){
    std::map<string, map<string, int>* >::iterator tableIterator = table.find(destination);
    if (tableIterator == table.end()){
        //adds a new element if the destination didn't previously exist
        map <string, int>* temp = new map <string, int>;
        temp->insert(std::pair<string,int>(direction,distance));
        table[destination] = temp;
    }
    else{
        //the destination exists in the routing table, so see if it needs to be updated
        map<string,int>* temp = tableIterator->second;
        std::map<string, int>::iterator rowIterator = temp->find(direction);
        if (rowIterator == temp->end()){
            //then we dont have any previous routes to the destination in this direction
            //so add it in
            temp->insert(std::pair<string,int>(direction,distance));
        }
        else{
            //check to see if the new route has a shorter distance, if so update, otherwise do nothing
            if (distance < rowIterator->second){
                //new distance is shorter than existing one, so update the route
                rowIterator->second = distance;
            }
        }
    }
}
/*pass in a destination, and if that destination is in the routing table,
  the address of the quickest route there will be returned as a string
*/
string RoutingTable::getBestRoute(string destination){
    std::map<string, map<string, int>* >::iterator tableIterator = table.find(destination);
    if (tableIterator == table.end()){
        return "INVALID";
    }
    else{
        //if the program gets here, it means that the destination exists in the routing table
        int shortest = 1000;
        string result;
        map<string,int>* temp = tableIterator->second;
        std::map<string, int>::iterator rowIterator = temp->begin();
        while (rowIterator != temp->end()){
            if (rowIterator->second < shortest){
                shortest = rowIterator -> second;
                result = rowIterator ->first;
            }
            rowIterator++;
        }
        return result;
    }
}

void RoutingTable::deleteDestination(string destination){
    table.erase(destination);
}

void RoutingTable::deleteRoute(string destination, string direction){
    std::map<string, map<string, int>* >::iterator tableIterator = table.find(destination);
    if (tableIterator == table.end()){
        return;
    }
    else {
        map<string,int>* temp = tableIterator->second;
        temp->erase(direction);
        return;
    }
}

void RoutingTable::printTable(){
    std::map<string, map<string, int>* >::iterator it = table.begin();
    for(it = table.begin(); it!=table.end(); ++it){
        cout << "Destination: " << it->first << endl;
        printSubTable(it->second);
    }
}

void RoutingTable::printSubTable(map<string, int>* m){
    std::map<string,int>::iterator it = m->begin();
    for (it = m->begin(); it!=m->end();++it){
        cout << it->first << ": " << it->second << endl;
    }
}
