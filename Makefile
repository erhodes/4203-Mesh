
all: NDP.o Neighbor.o WLAN.o MessageHandler.o test chat


test: packet.h packet.cpp test.cpp data_packet.h data_packet.cpp routing_packet.h routing_packet.cpp packet_factory.h packet_factory.cpp
	g++ packet.cpp test.cpp data_packet.cpp routing_packet.cpp packet_factory.cpp -o test

chat: example_chat.cpp packet.h packet.cpp data_packet.h data_packet.cpp routing_packet.h routing_packet.cpp packet_factory.h packet_factory.cpp dvrp_network_layer.h dvrp_network_layer.cpp dvrp_network_layer_delegate.h routingtable.h routingtable.cpp
	g++ -std=c++0x packet.cpp data_packet.cpp routing_packet.cpp packet_factory.cpp dvrp_network_layer.cpp routingtable.cpp example_chat.cpp -o chat

file: example_file_transfer.cpp packet.h packet.cpp data_packet.h data_packet.cpp routing_packet.h routing_packet.cpp packet_factory.h packet_factory.cpp dvrp_network_layer.h dvrp_network_layer.cpp dvrp_network_layer_delegate.h routingtable.h routingtable.cpp
	g++ -std=c++0x packet.cpp data_packet.cpp routing_packet.cpp packet_factory.cpp dvrp_network_layer.cpp routingtable.cpp example_file_transfer.cpp -o chat

NDP.o: NDP.h NDP.cpp
	g++ -std=c++0x -c NDP.cpp

Neighbor.o: Neighbor.h Neighbor.cpp
	g++ -std=c++0x -c Neighbor.cpp

WLAN.o: WLAN.h WLAN.cpp
	g++ -std=c++0x -c WLAN.cpp

MessageHandler.o: MessageHandler.h MessageHandler.cpp
	g++ -std=c++0x -c MessageHandler.cpp

clean:
	rm -f *.o
	rm -rf test chat










