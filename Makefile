
spencer: packet.h packet.cpp packet_test.cpp data_packet.h data_packet.cpp routing_packet.h routing_packet.cpp
	g++ packet.h packet.cpp packet_test.cpp data_packet.h data_packet.cpp routing_packet.h routing_packet.cpp
all:	wlan.h wlan.cpp nbr_entry.cpp
	g++ -o main main.cpp wlan.cpp nbr_table.cpp nbr_entry.cpp


