#include "packet.h"
#include "data_packet.h"
#include "routing_packet.h"
#include "packet_factory.h"
#include "dvrp_network_layer_delegate.h"
#include "routingtable.h"
#include "NDP.h"



/*
	The purpose of this class is to manage the DVRP network layer

*/


#ifndef INCLUDE_DVRP_NETWORK_LAYER
#define INCLUDE_DVRP_NETWORK_LAYER


class DVRPNetworkLayer : public MessageHandler{
	
public:

	// Constructs a DVRP network layer
	DVRPNetworkLayer();	
	
	// Sends data to a destination on the network
	void sendData(string destination, string data);	

	void setDelegate(DVRPNetworkLayerDelegate *);


	virtual void handleMessage(string src, string dst, string msg);

	// Found Neighbor
	virtual void foundNeighbor(const string address);

 	// Lost Neighbor
 	virtual void lostNeighbor(const string address);

	vector<string> getAllNodeAddresses();


	string getMyNetworkAddress();

private:
	bool vectorIsMissingRoute(string vector);	

	void sendRawData(string destination, string data);

	void advertiseRoutingTable();

	string serializeShortestPaths();
	
	string serializeShortestPathsForDestination(string destination);

	void updateRoutingTable(string routingVector, string source);

	void forwardPacket(Packet * p);

	DVRPNetworkLayerDelegate * delegate;

	RoutingTable * routingTable;

	NDP * neighbourDiscovery;
};


#endif
