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
	for(int i = 0 ; i < 10; i++){

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
	return 0;	
}

void ExampleChat::handleSendMessage(){
	displayAddressRequestMessage();
	int address =getUserSelection();
	if(validateAddress(address) == 0){ // Success
		displayMessageRequestMessage();
		string message = getUserString();
		// Send the message
	}else{
		cout << "The address you entered does not appear to be that of a chatter, please try again later\n";
	}
	cout << "\n";
}

void  ExampleChat::initNetworkLayer(){
	networkLayer = new DVRPNetworkLayer();
	networkLayer->setDelegate(this);
	
}

void ExampleChat::dataReceived(string source, string data){

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
		}
	}
	cleanupNetworkLayer();
}



int main(int argc, char ** argv){
	
	ExampleChat exampleChat;
	exampleChat.runChatSession();	

	return 0;
}

