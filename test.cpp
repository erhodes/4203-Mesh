#include "packet.h"

#include "packet_factory.h"

#include <iostream>

#include <unistd.h>


int testPacket(void){

	int lifeTime = 5;

	int packetNumber = 10; 
	
	string sourceAddress = "08:00:27:c7:cf:e9";

	string destinationAddress = "08:00:27:c7:cf:ff";

	string payload = "message";

	int hopCount = 0;

	Packet p(lifeTime, packetNumber, sourceAddress, destinationAddress, payload);

	if(p.getPacketNumber() != packetNumber){
		cout << "Failure: packetNumber getter/setter\n";
		return -1;
	}

	if(p.getSourceAddress() != sourceAddress){
		cout << "Failure: sourceAddress getter/setter\n";
		return -1;
	}

	if(p.getDestinationAddress() != destinationAddress){
		cout << "Failure: destinationAddress getter/setter\n";
		return -1;
	}

	if(p.getPayload() != payload){
		cout << "Failure: payload getter/setter\n";
		return -1;
	}

	if(p.isExpired()){
		cout << "Failure: isExpired method should have not said the packet was expired yet\n";
		return -1;
	}

	// Sleep for long enough for the packet to be expired
	sleep(lifeTime + 1);
	
	if(!p.isExpired()){
		cout << "Failure: isExpired method should have said the packet was expired\n";
		return -1;
	}

	if(p.getHopCount() != hopCount){
		cout << "Failure: hopCount getter/setter\n";
		return -1;	
	}

	return 0;
}


int testPacketFactoryForDataPacket(void){

	int lifeTime = 5;

	int packetNumber = 10; 
	
	string sourceAddress = "08:00:27:c7:cf:e9";

	string destinationAddress = "08:00:27:c7:cf:ff";

	string payload = "message";

	int hopCount = 0;

	string packetType = "DataPacket";

	DataPacket p(packetNumber, destinationAddress, payload);

	if(p.getPacketNumber() != packetNumber){
		cout << "Failure: packetNumber getter/setter\n";
		return -1;
	}

	if(p.getSourceAddress() != sourceAddress){
		cout << "Failure: sourceAddress getter/setter\n";
		return -1;
	}

	if(p.getDestinationAddress() != destinationAddress){
		cout << "Failure: destinationAddress getter/setter\n";
		return -1;
	}

	if(p.getPayload() != payload){
		cout << "Failure: payload getter/setter\n";
		return -1;
	}

	if(p.isExpired()){
		cout << "Failure: isExpired method should have not said the packet was expired yet\n";
		return -1;
	}

	// Sleep for long enough for the packet to be expired
	sleep(lifeTime + 1);
	
	if(!p.isExpired()){
		cout << "Failure: isExpired method should have said the packet was expired\n";
		return -1;
	}

	if(p.getHopCount() != hopCount){
		cout << "Failure: hopCount getter/setter\n";
		return -1;	
	}

	return 0;


}

int testPacketFactoryForRoutingPacket(void){

	int lifeTime = 5;

	int packetNumber = 10; 
	
	string sourceAddress = "08:00:27:c7:cf:e9";

	string destinationAddress = "08:00:27:c7:cf:ff";

	string payload = "message";

	int hopCount = 0;

	Packet p(lifeTime, packetNumber, sourceAddress, destinationAddress, payload);

	if(p.getPacketNumber() != packetNumber){
		cout << "Failure: packetNumber getter/setter\n";
		return -1;
	}

	if(p.getSourceAddress() != sourceAddress){
		cout << "Failure: sourceAddress getter/setter\n";
		return -1;
	}

	if(p.getDestinationAddress() != destinationAddress){
		cout << "Failure: destinationAddress getter/setter\n";
		return -1;
	}

	if(p.getPayload() != payload){
		cout << "Failure: payload getter/setter\n";
		return -1;
	}

	if(p.isExpired()){
		cout << "Failure: isExpired method should have not said the packet was expired yet\n";
		return -1;
	}

	// Sleep for long enough for the packet to be expired
	sleep(lifeTime + 1);
	
	if(!p.isExpired()){
		cout << "Failure: isExpired method should have said the packet was expired\n";
		return -1;
	}

	if(p.getHopCount() != hopCount){
		cout << "Failure: hopCount getter/setter\n";
		return -1;	
	}

	return 0;



}

int testPacketFactoryForPacket(void){
	int lifeTime = 5;

	int packetNumber = 10;
	
	string sourceAddress = "08:00:27:c7:cf:e9";

	string destinationAddress = "08:00:27:c7:cf:ff";

	string payload = "message";

	int hopCount = 0;

	Packet p(lifeTime, packetNumber, sourceAddress, destinationAddress, payload);

	if(p.getPacketNumber() != packetNumber){
		cout << "Failure: packetNumber getter/setter\n";
		return -1;
	}

	if(p.getSourceAddress() != sourceAddress){
		cout << "Failure: sourceAddress getter/setter\n";
		return -1;
	}

	if(p.getDestinationAddress() != destinationAddress){
		cout << "Failure: destinationAddress getter/setter\n";
		return -1;
	}

	if(p.getPayload() != payload){
		cout << "Failure: payload getter/setter\n";
		return -1;
	}

	if(p.isExpired()){
		cout << "Failure: isExpired method should have not said the packet was expired yet\n";
		return -1;
	}

	if(p.getHopCount() != hopCount){
		cout << "Failure: hopCount getter/setter\n";
		return -1;	
	}

	string serialized = p.toString();

	PacketFactory factory;
	
	Packet * tempq = factory.createPacket(serialized);
	Packet &q = *tempq;

	string sentPacket;

	sentPacket = q.toString();

	if(q.isExpired()){
		cout << "Failure: serialization->isExpired method should not have said that the packet was expired yet\n";
		return -1;
	}

	sleep(lifeTime+1);

	if(!q.isExpired()){
		cout << "Failure: serialization->isExpired method should have said that the packet was expired already\n";
	}

	if(q.getPacketNumber() != packetNumber){
		cout << "Failure: serialization->packetNumber getter/setter\n";
		return -1;
	}

	if(q.getSourceAddress() != sourceAddress){
		cout << "Failure: serialization->sourceAddress getter/setter\n";
		return -1;
	}

	if(q.getDestinationAddress() != destinationAddress){
		cout << "Failure: serialization->destinationAddress getter/setter\n";
		return -1;
	}

	if(q.getPayload() != payload){
		cout << "Failure: serialization->payload getter/setter\n";
		return -1;
	}

	if(q.getHopCount() != hopCount){
		cout << "Failure: serialization->hopCount getter/setter\n";
		return -1;	
	}

	return 0;
}

int testDataPacket(void){
	

	return 0;
}


int testRoutingPacket(void){

	return 0;
}

int testPacketFactory(void){
	
	if(testPacketFactoryForPacket() == 0 ){ // Success
		
	}else{
		cout << "Failure: serialization->Packet Class";
		return -1;
	}


	if(testPacketFactoryForDataPacket() == 0){ // Success

	}else{
		cout << "Failure: serialization->DataPacket Class";
		return -1;
	}

	if(testPacketFactoryForRoutingPacket() == 0){ // Success
		
	}else{
		cout << "Failure: serialization->RoutingPacket Class";
		return -1;
	}

	return 0;
}


int main (int argc, char ** argv){


	if(testPacket() == 0){ // Success
		cout << "Success: Packet Tests\n";
	}else{
		cout << "Failure: Packet Tests\n";
	}


	if(testDataPacket() == 0){ // Success
		cout << "Success: DataPacket Tests\n";
	}else{
		cout << "Failure: DataPacket Tests\n";
	}

	if(testRoutingPacket() == 0){ // Success
		cout << "Success: RoutingPacket Tests\n";
	}else{
		cout << "Failure: RoutingPacket Tests\n";
	}

	if(testPacketFactory() == 0){ // Success
		cout << "Success: PacketFactory Tests\n";
	}else{
		cout << "Failure: PacketFactory Tests\n";
	}

}

