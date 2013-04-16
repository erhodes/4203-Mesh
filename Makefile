all: NDP.o Neighbor.o WLAN.o MessageHandler.o test chat

chat: packet.o data_packet.o routing_packet.o packet_factory.o dvrp_network_layer.o routingtable.o example_chat.o NDP.o Neighbor.o WLAN.o MessageHandler.o
	g++ -std=c++0x -pthread packet.o data_packet.o routing_packet.o packet_factory.o dvrp_network_layer.o routingtable.o example_chat.o NDP.o Neighbor.o WLAN.o MessageHandler.o -o chat

test: packet.h packet.cpp test.cpp data_packet.h data_packet.cpp routing_packet.h routing_packet.cpp packet_factory.h packet_factory.cpp
	g++ packet.cpp test.cpp data_packet.cpp routing_packet.cpp packet_factory.cpp -o test

file: packet.o data_packet.o routing_packet.o packet_factory.o dvrp_network_layer.o routingtable.o example_file_transfer.o NDP.o Neighbor.o WLAN.o MessageHandler.o
	g++ -std=c++0x -pthread packet.o data_packet.o routing_packet.o packet_factory.o dvrp_network_layer.o routingtable.o example_file_transfer.o NDP.o Neighbor.o WLAN.o MessageHandler.o -o file

packet.o: packet.h packet.cpp
	g++ -std=c++0x -c packet.cpp

data_packet.o: data_packet.h data_packet.cpp
	g++ -std=c++0x -c data_packet.cpp

routing_packet.o: routing_packet.h routing_packet.cpp
	g++ -std=c++0x -c routing_packet.cpp

packet_factory.o: packet_factory.h packet_factory.cpp
	g++ -std=c++0x -c packet_factory.cpp

dvrp_network_layer.o: dvrp_network_layer.h dvrp_network_layer.cpp dvrp_network_layer_delegate.h
	g++ -std=c++0x -c dvrp_network_layer.cpp

routingtable.o: routingtable.h routingtable.cpp
	g++ -std=c++0x -c routingtable.cpp

example_chat.o: example_chat.h example_chat.cpp
	g++ -std=c++0x -c example_chat.cpp

example_file_transfer.o: example_file_transfer.h example_file_transfer.cpp
	g++ -std=c++0x -c example_file_transfer.cpp

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
	rm -rf test chat file










