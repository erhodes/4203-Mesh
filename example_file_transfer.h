#include <iostream>
#include "dvrp_network_layer.h"
#include <time.h>

#include <sys/time.h>

#include <sys/stat.h>

#ifndef INCLUDE_EXAMPLE_FILE_TRANSFER
#define INCLUDE_EXAMPLE_FILE_TRANSFER

#define MAX_BLOCK_SIZE 100

class ExampleFileTransfer : DVRPNetworkLayerDelegate{

	private:

		DVRPNetworkLayer * networkLayer;

		FILE * inputFile;

		FILE * outputFile;
		long totalBytesWritten;
		long totalFileSize;


		

		void initNetworkLayer();
		void cleanupNetworkLayer();
	
		void displayWelcomeMessage();
		void displayOptions();
		int getUserSelection();
		void handleListUsers();
		string getUserString();
		void displayAddressRequestMessage();
		void displayFileNameRequestMessage();
		int validateAddress(int address);
		void handleSendFile();

		string lookupAddress(int addressIndex);	
		void handleFileTransfer(string destinationAddress, string fileName);
	public:
		ExampleFileTransfer();
		void dataReceived(string source, string data);	
		void runFileTransferSession();	
		

};

#endif
