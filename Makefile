
spencer: packet.h packet.cpp spencer.cpp networklayer.cpp
	g++ packet.h packet.cpp spencer.cpp networklayer.cpp
all:	wlan.h wlan.cpp nbr_entry.cpp
	g++ -o main main.cpp wlan.cpp nbr_table.cpp nbr_entry.cpp


