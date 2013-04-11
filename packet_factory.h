#include "packet.h"
#include "data_packet.h"
#include "routing_packet.h"
#include <iostream>

class PacketFactory {
	public:
	PacketFactory & getFactory();
	
	Packet * createPacket(string serializedPacket);

};


