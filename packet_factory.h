#include "packet.h"
#include "data_packet.h"
#include "routing_packet.h"
#include <iostream>

#ifndef INCLUDE_PACKET_FACTORY
#define INCLUDE_PACKET_FACTORY



class PacketFactory {
	public:
	PacketFactory & getFactory();
	
	Packet * createPacket(string serializedPacket);

};

#endif
