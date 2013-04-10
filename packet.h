
#include <string>
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


using namespace std;


class Packet{
	private:
		// The type of packet which this object represents	
		PacketType type;
		// The date and time on which this packet was sent
		struct timeval timeSent;
		// The lifetime of the packet in milliseconds
		int lifeTime;
		// The number of the packet
		int packetNumber;
		// The address of the source of this packet
		string sourceAddress;
		// The address of the destination of this packet
		string destinationAddress;

		// Payload of the packet itself
		string payload;

		// Sets what type of packet is represented by this object
		void setType(PacketType newType);
		// Sets the time at which this packet was sent
		void setTimeSent(timeval newTimeSent);
		// Sets the number of milliseconds a packet is good for before expiry
		void setLifeTime(int newLifeTime);
		// Sets the number of this packet
		void setPacketNumber(int newPacketNumber);
		// Sets the source address of the packet represented by this object
		void setSourceAddress(string newSourceAddress);
		// Sets the destination address of the packet represented by this object
		void setDestinationAddress(string newDestinationAddress);
		// Sets the payload of this packet
		void setPayload(string newPayload);
	
		int getLifeTime() const;		
	public:
		Packet(PacketType typeParam, int lifeTimeParam, int packetNumberParam, string sourceAddressParam, string destinationAddressParam, string payloadParam);
		// Constructs a packet object from raw packet data
		Packet(string packetData);
		// Gets the type of this packet
		PacketType getType() const;
		// Gets whether or not this packet is expired according to the time of expiry
		bool isExpired() const;
		// Gets the number of this packet
		int getPacketNumber() const;
		// Gets the source address of this packet	
		string getSourceAddress() const;
		// Gets the destination address of this packet
		string getDestinationAddress() const;
		// Gets the payload contained within this packet
		string getPayload() const;
		// Constructs a string representation of this object
		string toString() const;
}
