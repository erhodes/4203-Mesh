#include "packet.h"




// Constructs a new packet object from the parameters
// type - The type of packet
// lifeTime - The number of seconds before the packet will expire
// packetNumber - The number of this packet
// sourceAddress - The source address of the packet
// destinationAddress - The destination address of the packet
// payload - The payload of the packet

Packet::Packet(PacketType typeParam, int lifeTimeParam, int packetNumberParam,  string sourceAddressParam, string destinationAddressParam, string payloadParam){

	type = typeParam;

	time_t tempTime;
	time(&tempTime);
	timeSent = localtime(&tempTime);

	lifeTime = lifeTimeParam;
	
	packetNumber = packetNumberParam;	

	sourceAddress = sourceAddressParam;

	destinationAddress = destinationAddressParam;

	payload = payloadParam;

}

Packet::Packet(string packetData){
// Parse the packet into the object

}

// Returns the type of packet represented by this object
PacketType Packet::getType() const{
	return type;
}


// Returns whether or not this packet is expired by looking at the associated time of expiry
bool Packet::isExpired() const{
	// Complicated
}

// Returns the number of the packet represented by this object
int Packet::getPacketNumber() const{
	return packetNumber;
}

// Returns the source address of the packet represented by this object
string Packet::getSourceAddress() const{
	return sourceAddress;
}

// Returns the destination address of the packet represented by this object
string Packet::getDestinationAddress() const{
	return destinationAddress;
}

// Returns the payload contained within the packet represented by this object
string Packet::getPayload() const{
	return payload;
}

string Packet::toString() const{
	// Serialize this object for the network
}



/*

	Private Methods
*/


// Sets what type of packet is represented by this object
void Packet::setType(PacketType newType){
	type = newType;
}

// Sets the time at which this packet was sent
void Packet::setTimeSent(tm * newTimeSent){
	timeSent = newTimeSent;
}

// Sets the number of milliseconds a packet is good for before expiry
void Packet::setTimeOfExpiry(int newLifeTime){
	lifeTime = newLifeTime;
}

// Sets the number of this packet
void Packet::setPacketNumber(int newPacketNumber){
	packetNumber = newPacketNumber;
}

// Sets the source address of the packet represented by this object
void Packet::setSourceAddress(string newSourceAddress){
	sourceAddress = newSourceAddress;
}

// Sets the destination address of the packet represented by this object
void Packet::setDestinationAddress(string newDestinationAddress){
	destinationAddress = newDestinationAddress;
}

// Sets the payload of this packet
void Packet::setPayload(string newPayload){
	payload = newPayload;
}


