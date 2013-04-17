#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
using namespace std;

#define A "f0:7d:68:13:a4:af"
#define B "1c:bd:b9:88:31:c1"
#define C "1c:bd:b9:7e:b6:9c"
#define D "1c:bd:b9:7e:b6:a0"
#define E "f0:7d:68:13:a4:9e"
#define F "1c:bd:b9:7e:b6:5d"


std::string exec(const char* cmd) {
    FILE* pipe = popen(cmd, "r");
    char buffer[32];
    string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 32, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);
    return result;
}

void blacklist(stringstream *stream, const char * blocked){
	int i =0;
	while(blocked[i] != '\0'){
		if(blocked[i] == 'a'){
			(*stream) << A;
		}else if(blocked[i] == 'b'){
			(*stream) << B;
		}else if(blocked[i] == 'c'){
			(*stream) << C;
		}else if(blocked[i] == 'd'){
			(*stream) << D;
		}else if(blocked[i] == 'e'){
			(*stream) << E;
		}else if(blocked[i] == 'f'){
			(*stream) << F;
		}
		(*stream) << "\n";
		i++;
	}	

}

int main(int argc, char ** argv){
	
	int topology =-1;
	cout << "Please type the topology number of the topology you wish to generate: ";
	cin >> topology;

	stringstream topologyFile;
	
	const char * cmd = "ifconfig | grep \"^wlan0\" | sed -e 's/wlan0     Link encap:Ethernet  HWaddr //'";
	
	string mac = exec(cmd);
	mac = mac.substr(0, mac.length()-3);
	if(mac == A){
		if(topology == 1){
			blacklist(&topologyFile, "cef");
		}else if(topology == 2){
			blacklist(&topologyFile, "ecf");
		}else if(topology == 3){
			blacklist(&topologyFile, "d");
		}
	}else if(mac == B){
		if(topology == 1){
			blacklist(&topologyFile, "cde");
		}else if(topology == 2){
			blacklist(&topologyFile, "dcf");
		}else if(topology == 3){
			blacklist(&topologyFile, "d")
		}
	}else if(mac == C){
		if(topology == 1){
			blacklist(&topologyFile, "abde");
		}else if(topology == 2){
			blacklist(&topologyFile, "abd");
		}else if(topology == 3){
			blacklist(&topologyFile, "");
		}
	}else if(mac == D){
		if(topology == 1){
			blacklist(&topologyFile,"bcef");
		}else if(topology == 2){
			blacklist(&topologyFile,"bcf");
		}else if(topology == 3){
			blacklist(&topologyFile, "ab");
		}
	}else if(mac == E){
		if(topology == 1){
			blacklist(&topologyFile,"abcd");
		}else if(topology == 2){
			blacklist(&topologyFile, "a");
		}else if(topology == 3){
			blacklist(&topologyFile,"abcdefg");
		}
	}else if(mac == F){
		if(topology == 1){
			cout << "RIGHT BLACKLIST\n";
			blacklist(&topologyFile,"ad");
		}else if(topology == 2){
			blacklist(&topologyFile,"abd");
		}else if(topology == 3){
			blacklist(&topologyFile, "abcdefg");
		}
    	}
    ofstream myfile;
    myfile.open("blacklist.txt");
    string stringToBeWritten = topologyFile.str();
    myfile << stringToBeWritten;
    myfile.close();
    return 0;
}
