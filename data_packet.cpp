#include "data_packet.h"




DataPacket::DataPacket(string dataPacket) : Packet(dataPacket){

}


string DataPacket::getType() const{
	return string("DataPacket");
}







