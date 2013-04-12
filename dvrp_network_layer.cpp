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


// Sends data to a destination on the network
// Destination must be a one hop neighbour to us
void DVRPNetworkLayer::sendData(string destination, string data){
	

}
// Forwards a packet that was not meant for us
void DVRPNetworkLayer::forwardPacket(Packet * p){
	string destination = p->getDestinationAddress();
	string	bestRoute = routingTable->getBestRoute(destination);
	
	if(bestRoute != "INVALID"){ // If there is actually a path to the destination
		string data = p->toString();
		sendData(bestRoute, data);	
	}
}

// Updates our routing table using the information that source has cerain
// distances to other nodes as per the included routing table
void DVRPNetworkLayer::updateRoutingTable(string routingVector, string source){
	
}


// Tells our closest neighbours about how fast we can get to other destinations
void DVRPNetworkLayer::advertiseRoutingTable(){

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

				string shortestPathsSerializedInitial = serializeShortestPaths(); // Figure out the most optimal paths before we update the routing table

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



