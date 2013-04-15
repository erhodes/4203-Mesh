#include "packet.h"


#ifndef INCLUDE_ROUTING_PACKET
#define INCLUDE_ROUTING_PACKET

class RoutingPacket : public Packet{
	public:
		
		
		RoutingPacket(int packetNumberParam, int lifeTimeParam, string sourceAddressParam, string destinationAddressParam, string messageParam);

		RoutingPacket(string packetData);

		virtual string getType() const;


};

#endif
