#include "packet.h"


#ifndef INCLUDE_ROUTING_PACKET
#define INCLUDE_ROUTING_PACKET

class RoutingPacket : public Packet{
	public:
		RoutingPacket(string packetData);

		virtual string getType() const;


};

#endif
