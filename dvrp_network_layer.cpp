#include "dvrp_network_layer.h"




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
void DVRPNetworkLayer::sendData(string destination, string data){
	

}


void DVRPNetworkLayer::messageReceived(string sourceAddress, string destinationAddress, string data){
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


					// TODO: FORWARD THE PACKET

				}
			}else if(packet->getType() == "RoutingPacket"){

				// TODO: Handle the routing packet				

				// update our routing table
				// tell the neighbours about our routing table by constructing
				// a vector of the shortest paths

			}
		}else{
			cout << "Warning: Received expired packet\n";
		}
	}else{
		cout << "ERROR: Received invalid packet data\n";
	}

}



