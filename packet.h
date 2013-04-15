
#include <string>
#include <time.h>
#include <iostream>
#include <sstream>
/*
	There are two types of packets:

	DataPacket - Contains the message payload sent from the next layer in the network stack
	RoutingPacket - Contains information specific to maintaining the distance vector routing table

	Each of those types of packets are represented using subclasses of this class because they are both packets

*/

#ifndef INCLUDE_PACKET

#define INCLUDE_PACKET

using namespace std;

class Packet{
	private:
		// The date and time on which this packet was sent
		time_t timeSent;
		// The lifetime of the packet in milliseconds
		int lifeTime;
		// The number of the packet
		int packetNumber;
		// The address of the source of this packet
		string sourceAddress;
		// The address of the destination of this packet
		string destinationAddress;
		// The number of hops that this packet has made
		int hopCount;
		// Payload of the packet itself
		string payload;
		// Sets the time at which this packet was sent
		void setTimeSent(time_t newTimeSent);
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
		// Gets the liftime of this packet in seconds
		int getLifeTime() const;
		// Sets the number of hops this packet has made
		void setHopCount(int newHopCount);	
	public:
		Packet(int lifeTimeParam, int packetNumberParam, string sourceAddressParam, string destinationAddressParam, string payloadParam);
		// Constructs a packet object from raw packet data
		Packet(string packetData);
		// Gets the type of this packet
		virtual string getType() const;
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
		// Gets the time at which this packet was sent
		time_t getTimeSent() const;
		// Constructs a string representation of this object
		string toString() const;
		// Get the number of hops that this packet has made
		int  getHopCount() const;
};

#endif
