#include "dvrp_network_layer.h"



// Constructs a new DVRP network layer
DVRPNetworkLayer::DVRPNetworkLayer(){
	setDelegate(NULL);
	// TODO: INITIALIZE JOHNS OBJECT

	routingTable = new RoutingTable();

	
}


// Sets the delegate for this object
void DVRPNetworkLayer::setDelegate(DVRPNetworkLayerDelegate * newDelegate){
	delegate = newDelegate;
}

// Sends data to a one hop neighbour only
void DVRPNetworkLayer::sendRawData(string destination, string data){
	// TODO: Pipe this data to John's object
}

// Sends data to any reachable destination on the network
void DVRPNetworkLayer::sendData(string destination, string data){
	// TODO: Use John's mac address function to find the address of this machine
	string myAddress;
	DataPacket dataPacket(0, 5, myAddress, destination, data);
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
	string myAddress; // = getMyMacAddress()
	// TODO: Implement code below when john finishes

	// For each neighbour in our routing table
		string currentDestinationAddress; // The current neighbour in the table
		RoutingPacket routingTablePacket(5, 0, myAddress, currentDestinationAddress, routingVector); // Construct the packet data
		string packetData = routingTablePacket.toString(); // Construct the packet data
		sendRawData(currentDestinationAddress, packetData); // Send the packet data
}

// Creates a serialized version of the most optimal routes in the routing table
string DVRPNetworkLayer::serializeShortestPaths(){
	string delimiter1 = " ";
	string delimiter2 = "\n";
	stringstream serialization;
	// TODO: Implement the code below when John finishes and Eric updates his routing table
	// int routingVectorSize = ;
	// serialization << routingVectorSize;
	serialization << delimiter2;
	// For each person in our neighbour table
		// string currentDestination;
		// string optimumLeavingNode = routingTable->getBestRoute(currentDestination);
		// int distance = routingTable->getDistance(currentDestination);
		// serialization << currentDestination;
		serialization << delimiter1;
		// serialization << distance;
		serialization << delimiter2;
	return serialization.str();
}


// This method gets called on us when a packet has been received
// 	sourceAddress - The neighbour who sent us the packet
//	destinationAddress - Should always be our mac address
void DVRPNetworkLayer::receive(string sourceAddress, string destinationAddress, string data){
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
				
				if(shortestPathSerializedInitial != shortestPathSerializedFinal){ // If the routing vector we received actually caused us to find a shorter path to a destination
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



