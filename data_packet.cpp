#include "data_packet.h"


DataPacket::DataPacket(int packetNumberParam, int lifeTimeParam, string sourceAddressParam, string destinationAddressParam, string messageParam) : Packet(packetNumberParam, lifeTimeParam, sourceAddressParam, destinationAddressParam, messageParam){
	cout << "DATA PACKET CONSTRUCTED\n";

}



DataPacket::DataPacket(string dataPacket) : Packet(dataPacket){

}


string DataPacket::getType() const{
	return string("DataPacket");
}







