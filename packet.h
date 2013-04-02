
#include <time.h>

/*
	There are two types of packets
	Message - Contains the message payload sent from the next layer in the network stack
	RoutingVector - Contains information specific to maintaining the distance vector routing table

*/

typedef struct PacketType{
	Invalid,
	Message,
	RoutingVector
} PacketType;



class Packet{
	private:
		// The type of packet which this object represents	
		PacketType type;
		// The date and time on which this packet was sent
		struct tm timeSent;
		// The date and time on whcih this packet will expire
		struct tm timeOfExpiry
		// The number of the packet
		int packetNumber;
		// The address of the source of this packet
		string sourceAddress;
		// The address of the destination of this packet
		string destinationAddress;

		// Payload of the packet itself
		string payload;

	public:
		// Constructs a packet object from raw packet data
		Packet(string packetData);
		// Gets the type of this packet
		PacketType getType() const;
		// Gets whether or not this packet is expired according to the time of expiry
		bool isPacketExpired() const;
		// Gets the number of this packet
		int getPacketNumber() const;
		// Gets the source address of this packet	
		string getSourceAddress() const;
		// Gets the destination address of this packet
		string getDestinationAddress() const;
		// Gets the payload contained within this packet
		string getPayload() const;
}
