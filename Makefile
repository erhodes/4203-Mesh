
test: packet.h packet.cpp test.cpp data_packet.h data_packet.cpp routing_packet.h routing_packet.cpp
	g++ packet.cpp test.cpp data_packet.cpp routing_packet.cpp -o test
all:	wlan.h wlan.cpp nbr_entry.cpp
	g++ -o main main.cpp wlan.cpp nbr_table.cpp nbr_entry.cpp
clean:
	rm -rf test main
