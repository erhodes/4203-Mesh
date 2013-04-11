#include "packet.h"




// Constructs a new packet object from the parameters
// type - The type of packet
// lifeTime - The number of seconds before the packet will expire
// packetNumber - The number of this packet
// sourceAddress - The source address of the packet
// destinationAddress - The destination address of the packet
// payload - The payload of the packet

Packet::Packet( int lifeTimeParam, int hopCountParam, int packetNumberParam,  string sourceAddressParam, string destinationAddressParam, string payloadParam){

	time_t tempTime;
	time(&tempTime);

	setTimeSent(tempTime);

	setHopCount(hopCountParam);

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
string Packet::getType() const{
	return string("BASE");
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

// Returns the number of hops that this packet has made
int Packet::getHopCount() const{
	return hopCount;
}


string Packet::toString() const{
	// Serialize this object for the network

	string delimiter = "\n";
	stringstream serialization;
	
	serialization << getType();

	serialization << delimiter;

	struct tm *nowtm;
	char tmbuf[64], buf[64];
	
	nowtm = localtime(&timeSent);
	strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
	
	string timeString (buf);

	serialization << timeString;

	serialization << delimiter;

	serialization << getLifeTime(); 

	serialization << delimiter;

	serialization << getPacketNumber();

	serialization << delimiter;
	
	serialization << getSourceAddress();

	serialization << delimiter;

	serialization << getDestinationAddress();

	serialization << delimiter;

	serialization << getPayload();

	return serialization.str();
}



/*

	Private Methods
*/



// Sets the time at which this packet was sent
void Packet::setTimeSent(time_t  newTimeSent){
	timeSent = newTimeSent;
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

// Sets the hop count of this packet
void Packet::setHopCount(int newHopCount){
	hopCount = newHopCount;
}

int Packet::getLifeTime() const{
	return lifeTime;
}
