#include "packet_factory.h"



PacketFactory & PacketFactory::getFactory(){
	static PacketFactory sharedFactory;
	return sharedFactory;
}


Packet * PacketFactory::createPacket(string packetData){
	stringstream deserializer(packetData);
	
	string type;

	deserializer >> type;

	if(type == "Packet"){
		Packet * p = new Packet(packetData);
		return p;
	}else if(type == "DataPacket"){
		DataPacket * p = new DataPacket(packetData);
		return p;
	}else if(type == "RoutingPacket"){
		RoutingPacket * p = new RoutingPacket(packetData);
		return p;
	}

	return NULL;
}

