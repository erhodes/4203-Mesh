



test: packet.h packet.cpp test.cpp data_packet.h data_packet.cpp routing_packet.h routing_packet.cpp packet_factory.h packet_factory.cpp
	g++ packet.cpp test.cpp data_packet.cpp routing_packet.cpp packet_factory.cpp -o test

chat: example_chat.cpp
	g++ example_chat.cpp -o chat

legacy:	wlan.h wlan.cpp nbr_entry.cpp
	g++ -o main main.cpp wlan.cpp nbr_table.cpp nbr_entry.cpp
clean:
	rm -rf test main chat
