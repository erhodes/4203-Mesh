#include "dvrp_network_layer.h"



// Constructs a new DVRP network layer
DVRPNetworkLayer::DVRPNetworkLayer(){
	setDelegate(NULL);

	neighbourDiscovery = new NDP();
	neighbourDiscovery->registerMessageHandler(this);
	neighbourDiscovery->start();

	routingTable = new RoutingTable();
	
}

vector<string> DVRPNetworkLayer::getAllNodeAddresses(){
	return routingTable->getAllDestinations();
}

string DVRPNetworkLayer::getMyNetworkAddress(){
	return WLAN::getInstance()->getAddress();
}


// Found Neighbor
void DVRPNetworkLayer::foundNeighbor(const string address){
	// Add the trivial route to the table
	routingTable->newRoute(address,address,1);
	advertiseRoutingTable();

}

// Lost Neighbor
void DVRPNetworkLayer::lostNeighbor(const string address){
	routingTable->deleteNode(address);
	advertiseRoutingTable();
}

// Sets the delegate for this object
void DVRPNetworkLayer::setDelegate(DVRPNetworkLayerDelegate * newDelegate){
	delegate = newDelegate;
}

// Sends data to a one hop neighbour only
void DVRPNetworkLayer::sendRawData(string destination, string data){
	WLAN::getInstance()->send(destination,data);
}

// Sends data to any reachable destination on the network
void DVRPNetworkLayer::sendData(string destination, string data){
	string myAddress = WLAN::getInstance()->getAddress();
	cout << "PARAMETER MY ADDRESS "<<  myAddress << "\n";
	cout << "PARAMETER DESTINATION " << destination << "\n";
	cout << "PARAMETER DATA " << data << "\n";
	cout << "About to construct the data packet\n";
	DataPacket dataPacket(0, 5, myAddress, destination, data);
	cout << "Successfully constructed the packet\n";
	string packetData = dataPacket.toString();
	string optimumRoute = routingTable->getBestRoute(destination);
	sendRawData(optimumRoute, packetData);
}
// Forwards a packet that was not meant for us
void DVRPNetworkLayer::forwardPacket(Packet * p){
	string destination = p->getDestinationAddress();
	string	bestRoute = routingTable->getBestRoute(destination);
	
	if(bestRoute != "INVALID"){ // If there is actually a path to the destination
		string data = p->toString();
		sendRawData(bestRoute, data);	
	}
}

// Updates our routing table using the information that source has cerain
// distances to other nodes as per the included routing table
void DVRPNetworkLayer::updateRoutingTable(string routingVector, string source){
	int numberOfEntries = -1; // Used to hold the number of entries in the routing vector
	stringstream routingVectorStream(routingVector); // Create a stringstream that will be used for parsing the routing vector
	routingVectorStream >> numberOfEntries; // Parse the number of entries in the routing table
	if(numberOfEntries != -1){ // If there was no weird parsing error

		for(int i = 0 ; i < numberOfEntries; i++){

			string destination;
			routingVectorStream >> destination;

			int distance;
			routingVectorStream >> distance;
			
			routingTable->newRoute(destination, source, distance + 1);
		}
	}
		
}


// Tells our closest neighbours about how fast we can get to other destinations
void DVRPNetworkLayer::advertiseRoutingTable(){

	string routingVector = serializeShortestPaths();
	string myAddress= WLAN::getInstance()->getAddress();

	vector <string> neighbours = neighbourDiscovery->getAddresses();
	for(string &currentDestinationAddress: neighbours){
		RoutingPacket routingTablePacket(5, 0, myAddress, currentDestinationAddress, routingVector); // Construct the packet data
		string packetData = routingTablePacket.toString(); // Construct the packet data
		sendRawData(currentDestinationAddress, packetData); // Send the packet data
	}
}

// Creates a serialized version of the most optimal routes in the routing table
string DVRPNetworkLayer::serializeShortestPaths(){
	string delimiter1 = " ";
	string delimiter2 = "\n";
	stringstream serialization;
	
	vector <string> neighbours = neighbourDiscovery->getAddresses();
          
	
	int routingVectorSize = neighbours.size();
	serialization << routingVectorSize;
	serialization << delimiter2;
	for(string &currentDestinationAddress: neighbours){	
		string optimumLeavingNode = routingTable->getBestRoute(currentDestinationAddress);
		int distance = routingTable->getBestDistance(currentDestinationAddress);
		
		routingTable->printTable();
		serialization << currentDestinationAddress;
		serialization << delimiter1;
		serialization << distance;
		serialization << delimiter2;
	}
	return serialization.str();
}


// This method gets called on us when a packet has been received
// 	sourceAddress - The neighbour who sent us the packet
//	destinationAddress - Should always be our mac address
void DVRPNetworkLayer::handleMessage(string sourceAddress, string destinationAddress, string data){
	cout << "PACKET RECEIVED\n";
	PacketFactory factory;
	Packet * packet = factory.createPacket(data);
	if(packet){
		if(!packet->isExpired()){ // If the received packet is not expired
			if(packet->getType() == "DataPacket"){ // If the packet received is a data packet
				if(packet->getDestinationAddress() == destinationAddress){ // If the destination of the received packet was us
					if(delegate){ // If there is a delegate we can tell about the data received for us
						delegate->dataReceived(sourceAddress, data); // Tell the delegate about the data we received
					}
				}else{
					forwardPacket(packet);
				}
			}else if(packet->getType() == "RoutingPacket"){

				string shortestPathSerializedInitial = serializeShortestPaths(); // Figure out the most optimal paths before we update the routing table

				string routingVector = packet->getPayload(); 	// Gets the routing vector from within the packet object

				updateRoutingTable(routingVector, sourceAddress); // Update our routing table with whatever we can learn from our near neighbours routing table

				string shortestPathSerializedFinal = serializeShortestPaths(); // Figure out our most optimal paths right now
				cout << "DIFF: {" << shortestPathSerializedInitial << "} WITH: {" << shortestPathSerializedFinal << "}\n";	
				if(shortestPathSerializedInitial != shortestPathSerializedFinal){ // If the routing vector we received actually caused us to find a shorter path to a destination
					cout << "FOUND THEM TO BE DIFFERENT SO WE ARE ADVERTISING AGAIN!\n";
					advertiseRoutingTable();
				}
			}
		}else{
			cout << "Warning: Received expired packet\n";
		}
	}else{
		cout << "ERROR: Received invalid packet data\n";
	}

}



