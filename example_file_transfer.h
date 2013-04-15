#include <iostream>
#include "dvrp_network_layer.h"

#ifndef INCLUDE_EXAMPLE_FILE_TRANSFER
#define INCLUDE_EXAMPLE_FILE_TRANSFER

class ExampleFileTransfer : DVRPNetworkLayerDelegate{

	private:

		DVRPNetworkLayer * networkLayer;

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
		void dataReceived(string source, string data);	
		void runFileTranferSession();	
		

};

#endif
