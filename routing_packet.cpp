#include "routing_packet.h"


RoutingPacket::RoutingPacket(string packetData) : Packet(packetData){

}


string RoutingPacket::getType() const{
	return string("RoutingPacket");
}



