#include "dvrp_network_layer.h"




DVRPNetworkLayer::DVRPNetworkLayer(){

}


// Sets the delegate for this object
void DVRPNetworkLayer::setDelegate(DVRPNetworkLayerDelegate * newDelegate){
	delegate = newDelegate;
}


// Sends data to a destination on the network
void DVRPNetworkLayer::sendData(string destination, string data){
	
}


