#include "packet.h"
#include "data_packet.h"
#include "routing_packet.h"
#include "packet_factory.h"
#include "dvrp_network_layer_delegate.h"
#include "routingtable.h"

/*
	The purpose of this class is to manage the DVRP network layer

*/


#ifndef INCLUDE_DVRP_NETWORK_LAYER
#define INCLUDE_DVRP_NETWORK_LAYER


class DVRPNetworkLayer{
	
public:

	// Constructs a DVRP network layer
	DVRPNetworkLayer();	
	
	// Sends data to a destination on the network
	void sendData(string destination, string data);	

	void setDelegate(DVRPNetworkLayerDelegate *);

	void receive(string sourceAddress, string destinationAddress, string data);

private:

	void sendRawData(string destination, string data);

	void advertiseRoutingTable();

	string serializeShortestPaths();

	void updateRoutingTable(string routingVector, string source);

	void forwardPacket(Packet * p);

	DVRPNetworkLayerDelegate * delegate;

	RoutingTable * routingTable;
};


#endif
