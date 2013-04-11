#include "packet.h"


#ifndef INCLUDE_DATA_PACKET

#define INCLUDE_DATA_PACKET

class DataPacket : public Packet{

	public:

	DataPacket(string datapacket);

	// Return the correct packet type identifier because it is different from the superclass
	virtual string getType() const;


};

#endif
