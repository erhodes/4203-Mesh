#include <iostream>
#include "dvrp_network_layer.h"

#ifndef INCLUDE_EXAMPLE_CHAT
#define INCLUDE_EXAMPLE_CHAT

class ExampleChat : DVRPNetworkLayerDelegate{

	private:

		DVRPNetworkLayer * networkLayer;

		void initNetworkLayer();
		void cleanupNetworkLayer();
	
		void displayWelcomeMessage();
		void displayOptions();
		int getUserSelection();
		void handleListChatters();
		string getUserString();
		void displayAddressRequestMessage();
		void displayMessageRequestMessage();
		int validateAddress(int address);
		void handleSendMessage();

	public:
		void runChatSession();	
		

};

#endif
