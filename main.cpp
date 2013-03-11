#include "wlan.h"
#include "nbr_table.h"

#include <iostream>
using namespace std;


int main(){
    init();
    nbr_table neighbours;
    cout << "Sockets Prepared" << endl;
    while (true){
        cout << "Enter an Option" << endl;
        int i;
        cin >> i;
        if (i == 0){
            shutdown();
            return 0;
        }
        else if (i == 1){
            cout << "Send Mode" << endl;
            MySend();
        }
        else if (i = 2){
            string message, sender;
            cout << "Recieve Mode" << endl;
            Receive(&sender, &message);
            cout << "Recieved" << message << " from " << sender << endl;
            neighbours.beaconRecieved(sender);
            neighbours.printTable();
        }
    }
}
