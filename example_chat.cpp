#include "example_chat.h"


using namespace std;


void ExampleChat::displayWelcomeMessage(){
	cout << " _    _ _____    _  _  __ __ _____    _____ _    _       _______ \n";
    cout << "| |  | |  __ \\  | || |/_ /_ | ____|  / ____| |  | |   /\\|__   __|\n";
	cout << "| |__| | |__) | | || |_| || | |__   | |    | |__| |  /  \\  | |   \n";
	cout << "|  __  |  ___/  |__   _| || |___ \\  | |    |  __  | / /\\ \\ | |   \n";
	cout << "| |  | | |         | | | || |___) | | |____| |  | |/ ____ \\| |   \n";
	cout << "|_|  |_|_|         |_| |_||_|____/   \\_____|_|  |_/_/    \\_\\_|   \n";
	cout << "\n";
	cout << "A simple chat program for testing our mesh networking implementation\n";
	cout << "\n";
}


void ExampleChat::displayOptions(){
	cout << "1. List Other Chatters\n";
	cout << "2. Send Message to a chatter\n";
	cout << "3. Exit\n"; 
	cout << "\n";
	cout << "Please make a selection: ";
}

int ExampleChat::getUserSelection(){
	int selection = -1;
	cin >> selection;
	
	cin.clear();
	cin.ignore(1000, '\n');

	return selection;
}

void ExampleChat::handleListChatters(){
	cout << "\n";
	cout << "Here is a list of chatters available\n";
	int currentAddressNumber= 1;
	vector<string> allAddresses = networkLayer->getAllNodeAddresses();
	for(string &currentNetworkAddress : allAddresses){
		cout << currentAddressNumber << ". ";
		cout << currentNetworkAddress;
		cout << "\n";
		currentAddressNumber++;
	}
	cout << "\n";
}

string ExampleChat::getUserString(){
	string input;
	getline(cin, input);
	return input;
}

void ExampleChat::displayAddressRequestMessage(){
	cout << "\n";
	cout << "Please input the corresponding number of the chatter you wish to send a message to: ";
}

void ExampleChat::displayMessageRequestMessage(){
	cout << "\n";
	cout << "Please input the message that you wish to send to the other chatter: ";
}

int ExampleChat::validateAddress(int address){
	// Just check if the computer is reachable
	vector<string> allAddresses = networkLayer->getAllNodeAddresses();
	if(address >= 1 && address <= allAddresses.size()){
		return 0;
	}	
	return 1;
}


string ExampleChat::lookupAddress(int addressIndex){
	vector<string> allAddresses = networkLayer->getAllNodeAddresses();
	return allAddresses[addressIndex - 1];
}


void ExampleChat::handleSendMessage(){
	displayAddressRequestMessage();
	int address =getUserSelection();
	if(validateAddress(address) == 0){ // Success
		displayMessageRequestMessage();
		string message = getUserString();
		cout <<"ABOUT TO SEND THE MESSAGE\n";
		string actualAddress = lookupAddress(address);
		cout << "TRYING TO SEND TO " << actualAddress << "\n";
		
		networkLayer->sendData(actualAddress, message);
	}else{
		cout << "\nThe address you entered does not appear to be that of a chatter, please try again later\n";
	}
	cout << "\n";
}

void  ExampleChat::initNetworkLayer(){
	networkLayer = new DVRPNetworkLayer();
	networkLayer->setDelegate(this);
	
}

// Delegate method that gets called when data is received
void ExampleChat::dataReceived(string source, string data){

	cout << "Message Received From (" << source << "): " << data << "\n";

}

void ExampleChat::cleanupNetworkLayer(){
	delete networkLayer;
}

void ExampleChat::runChatSession(){
	initNetworkLayer();

	displayWelcomeMessage();

	int choice = 0;	

	while(choice != 3){
		displayOptions();
		choice = getUserSelection();	
		if(choice == 1){
			handleListChatters();
		}else if(choice == 2){
			handleSendMessage();
		}else if(choice == 4){
			networkLayer->advertiseRoutingTable();
		}
	}
	cleanupNetworkLayer();
}



int main(int argc, char ** argv){
	ExampleChat exampleChat;
	exampleChat.runChatSession();	

	return 0;
}

