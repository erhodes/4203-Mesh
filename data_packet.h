#include "packet.h"


/*

	The DataPacket class was created so that data could be sent through the mesh
	network regardless of the topology. There needed to be a way to seperate
	network control packets from the actual data packets themselves. Therefore
	RoutingPackets and DataPackets were formed.

*/

#ifndef INCLUDE_DATA_PACKET

#define INCLUDE_DATA_PACKET

class DataPacket : public Packet{

	public:
	
	DataPacket(int packetNumberParam, int lifeTimeParam, string sourceAddressParam, string destinationAddressParam, string messageParam);

	DataPacket(string datapacket);

	// Return the correct packet type identifier because it is different from the superclass
	virtual string getType() const;


};

#endif
