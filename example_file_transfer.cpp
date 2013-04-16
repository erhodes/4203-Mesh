#include "example_file_transfer.h"


using namespace std;


void ExampleFileTransfer::displayWelcomeMessage(){
	cout << "    __  ______     __ __ ____________   ____________    ______\n";
	cout << "   / / / / __ \\   / // /<  <  / ____/  / ____/  _/ /   / ____/\n";
	cout << "  / /_/ / /_/ /  / // /_/ // /___ \\   / /_   / // /   / __/   \n";
	cout << " / __  / ____/  /__  __/ // /___/ /  / __/ _/ // /___/ /___   \n";
	cout << "/_/ /_/_/         /_/ /_//_/_____/  /_/   /___/_____/_____/   \n";
	cout << "\n";                                                              
	cout << "  __________  ___    _   _______ ________________ \n";
	cout << " /_  __/ __ \\/   |  / | / / ___// ____/ ____/ __ \\ \n";
	cout << "  / / / /_/ / /| | /  |/ /\\__ \\/ /_  / __/ / /_/ / \n";
	cout << " / / / _, _/ ___ |/ /|  /___/ / __/ / /___/ _, _/  \n";
	cout << "/_/ /_/ |_/_/  |_/_/ |_//____/_/   /_____/_/ |_|   \n";
                                                  
	cout << "\n";
	cout << "A simple file transfer program for testing our mesh networking implementation\n";
	cout << "\n";
}


void ExampleFileTransfer::displayOptions(){
	cout << "1. List Other Users\n";
	cout << "2. Send file to a user\n";
	cout << "3. Exit\n"; 
	cout << "\n";
	cout << "Please make a selection: ";
}

int ExampleFileTransfer::getUserSelection(){
	int selection = -1;
	cin >> selection;
	
	cin.clear();
	cin.ignore(1000, '\n');

	return selection;
}
	
void ExampleFileTransfer::handleListUsers(){
	cout << "\n";
	cout << "Here is a list of users available\n";
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

string ExampleFileTransfer::getUserString(){
	string input;
	getline(cin, input);
	return input;
}

void ExampleFileTransfer::displayAddressRequestMessage(){
	cout << "\n";
	cout << "Please input the corresponding number of the user you wish to send a file to: ";
}

void ExampleFileTransfer::displayFileNameRequestMessage(){
	cout << "\n";
	cout << "Please input the name of the file you wish to send: ";
}



int ExampleFileTransfer::validateAddress(int address){
	// Just check if the computer is reachable
	vector<string> allAddresses = networkLayer->getAllNodeAddresses();
	if(address >= 1 && address <= allAddresses.size()){
		return 0;
	}	
	return 1;
}


string ExampleFileTransfer::lookupAddress(int addressIndex){
	vector<string> allAddresses = networkLayer->getAllNodeAddresses();
	return allAddresses[addressIndex - 1];
}


void ExampleFileTransfer::handleFileTransfer(string destinationAddress, string fileName){
	struct timeval initial, final;

	gettimeofday(&initial, NULL);
	
	long totalBytes = 0;

	gettimeofday(&final, NULL);

	long seconds = final.tv_sec - initial.tv_sec;
	long microSeconds = final.tv_usec - initial.tv_usec;

	double totalTime = seconds + microSeconds * 1000000;
	double dataRate = (totalBytes /1024.0) / totalTime;

	cout << "Completed transfer of " << totalBytes << " bytes in " << totalTime << "  seconds (" << dataRate << " kB/s)"; 
	
}

void ExampleFileTransfer::handleSendFile(){
	displayAddressRequestMessage();
	int address =getUserSelection();
	if(validateAddress(address) == 0){ // Success
		displayFileNameRequestMessage();
		string fileName = getUserString();
		string actualAddress = lookupAddress(address);
		handleFileTransfer(actualAddress, fileName);

	}else{
		cout << "The address you entered does not appear to be that of a chatter, please try again later\n";
	}
	cout << "\n";
}

void  ExampleFileTransfer::initNetworkLayer(){
	networkLayer = new DVRPNetworkLayer();
	networkLayer->setDelegate(this);
	
}

// Delegate method that gets called when data is received
void ExampleFileTransfer::dataReceived(string source, string data){

	cout << "Message Received From (" << source << "): " << data << "\n";

}

void ExampleFileTransfer::cleanupNetworkLayer(){
	delete networkLayer;
}

void ExampleFileTransfer::runFileTransferSession(){
	initNetworkLayer();

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
	cleanupNetworkLayer();
}



int main(int argc, char ** argv){
	
	ExampleFileTransfer exampleFileTransfer;
	exampleFileTransfer.runFileTransferSession();	

	return 0;
}

