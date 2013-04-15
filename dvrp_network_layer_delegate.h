// Defines the protocol that needs to be implemented by delegates of the
// DVRPNetworkLayer object.




#ifndef INCLUDE_DVRP_NETWORK_LAYER_DELEGATE
#define INCLUDE_DVRP_NETWORK_LAYER_DELEGATE

class DVRPNetworkLayerDelegate{

	public:
		

		// Called on the delegate object when data is received
		virtual	void dataReceived(string source, string data) = 0;
		
		


};




#endif






