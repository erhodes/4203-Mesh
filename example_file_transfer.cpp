#include "example_file_transfer.h"


using namespace std;


ExampleFileTransfer::ExampleFileTransfer(){

	inputFile = NULL;
	outputFile = NULL;

	totalBytesWritten =0;
	totalFileSize = 0;
}


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

	string delimiter = "\n";

	struct stat st;
	stat(fileName.c_str(), &st);
	long fileLength = st.st_size;

	stringstream fileTransferInformation;

	fileTransferInformation << "BEGIN FILE TRANSFER";
	
	fileTransferInformation << delimiter;

	fileTransferInformation << fileName;

	fileTransferInformation << delimiter;

	fileTransferInformation << fileLength;

	string fileTransferHeader = fileTransferInformation.str();	
	
	networkLayer->sendData(destinationAddress, fileTransferHeader);

	inputFile = fopen(fileName.c_str(), "r");

	char buffer[MAX_BLOCK_SIZE + 1];
	buffer[MAX_BLOCK_SIZE] = '\0';
	long i; 
	for(i = 0; i < fileLength - MAX_BLOCK_SIZE; i++){
		
		fread(buffer, MAX_BLOCK_SIZE, 1, inputFile);
		string nextFileBlock(buffer);
		
		networkLayer->sendData(destinationAddress, nextFileBlock);
	}

	fread(buffer, fileLength - i, 1, inputFile);
	buffer[fileLength-i] = '\0';

	fclose(inputFile);
	

	gettimeofday(&final, NULL);

	long seconds = final.tv_sec - initial.tv_sec;
	long microSeconds = final.tv_usec - initial.tv_usec;

	double totalTime = seconds + (microSeconds + 1) / 1000000.0;
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


	if(outputFile == NULL){
		stringstream fileTransferInformation(data);
		string header;
		fileTransferInformation >> header;
		if(header == "BEGIN FILE TRANSFER"){
			
			
			string fileName;
			fileTransferInformation >> fileName;
		
			long fileSize;
			fileTransferInformation >> fileSize;
			totalFileSize = fileSize;
			totalBytesWritten = 0;

			fopen(fileName.c_str(), "rw");		
						
		}
	}else{
		if(totalBytesWritten < totalFileSize){
			fwrite(data.c_str(), data.length(), 1, outputFile);
			totalBytesWritten+=data.length();
		}else{
			fclose(outputFile);
		}
		

	}
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

