#include <iostream>


using namespace std;


void displayWelcomeMessage(){
	
	cout << "    __  ______     __ __ ____________   ____________    ______\n";
	cout << "   / / / / __ \   / // /<  <  / ____/  / ____/  _/ /   / ____/\n";
	cout << "  / /_/ / /_/ /  / // /_/ // /___ \   / /_   / // /   / __/   \n";
	cout << " / __  / ____/  /__  __/ // /___/ /  / __/ _/ // /___/ /___   \n";
	cout << "/_/ /_/_/         /_/ /_//_/_____/  /_/   /___/_____/_____/   \n";
	cout << "\n";                                                              
	cout << "  __________  ___    _   _______ ________________ \n";
	cout << " /_  __/ __ \/   |  / | / / ___// ____/ ____/ __ \ \n";
	cout << "  / / / /_/ / /| | /  |/ /\__ \/ /_  / __/ / /_/ / \n";
	cout << " / / / _, _/ ___ |/ /|  /___/ / __/ / /___/ _, _/  \n";
	cout << "/_/ /_/ |_/_/  |_/_/ |_//____/_/   /_____/_/ |_|   \n";
                                                  
	cout << "\n";
	cout << "A simple file transfer program for testing our mesh networking implementation\n";
	cout << "\n";
}


void displayOptions(){
	cout << "1. List Other Users\n";
	cout << "2. Send file to a user\n";
	cout << "3. Exit\n"; 
	cout << "\n";
	cout << "Please make a selection: ";
}

int getUserSelection(){
	int selection = -1;
	cin >> selection;
	
	cin.clear();
	cin.ignore(1000, '\n');

	return selection;
}

void handleListUsers(){
	cout << "\n";
	cout << "Here is a list of users available\n";
	for(int i = 0 ; i < 10; i++){

	}	
	cout << "\n";
}

string getUserString(){
	string input;
	getline(cin, input);
	return input;
}

void displayAddressRequestMessage(){
	cout << "\n";
	cout << "Please input the corresponding number of the user you wish to send a file to: ";
}

void displayMessageRequestMessage(){
	cout << "\n";
	cout << "Please input the name of the file you wish to send to this user: ";
}

int validateAddress(int address){
	// Just check if the computer is reachable
	return 0;	
}

void handleSendMessage(){
	displayAddressRequestMessage();
	int address =getUserSelection();
	if(validateAddress(address) == 0){ // Success
		displayMessageRequestMessage();
		string fileName = getUserString();
		// Send the file 
	}else{
		cout << "The address you entered does not appear to be that of a user, please try again later\n";
	}
	cout << "\n";
}

int main(int argc, char ** argv){

	displayWelcomeMessage();

	int choice = 0;	

	while(choice != 3){
		displayOptions();
		choice = getUserSelection();	
		if(choice == 1){
			handleListUsers();
		}else if(choice == 2){
			handleSendFile();
		}
	}

	return 0;
}
