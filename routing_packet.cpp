#include "routing_packet.h"

/*

	The RoutingPacket class is used to represent packets containing control information
	about the topology of the network such as distance vectors for DVRP.



*/


RoutingPacket::RoutingPacket(int packetNumberParam, int lifeTimeParam, string sourceAddressParam, string destinationAddressParam, string routingInformationParam) : Packet(packetNumberParam, lifeTimeParam, sourceAddressParam, destinationAddressParam, routingInformationParam){
	

}


RoutingPacket::RoutingPacket(string packetData) : Packet(packetData){

}


string RoutingPacket::getType() const{
	return string("RoutingPacket");
}



