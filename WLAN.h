// File: WLAN.h

#ifndef WLAN_H
#define WLAN_H

// C Headers
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// C++ Headers
#include <iostream>
#include <string>
#include "MessageHandler.h"

using namespace std;

// WLAN Class Definition
class WLAN{

  // Constants
  static const int MAX_NAME_LEN = 128;
  static const int WLAN_ADDR_LEN = 6;
  static const int WLAN_HEADER_LEN = 14;
  static const unsigned short IP_TYPE = 0x3901;
  static const string WLAN_HEADER;
  static const string WLAN_BROADCAST;

  // WLANAddr Struct Definition
  struct WLANAddr{
     // address
     unsigned char data[WLAN_ADDR_LEN];
     // return the address in a human readable form
     char * wlan2asc();
     // defined the address from a human readable form
     int str2wlan(char s[]);
  };

  // WLANHeader Struct Definition
  struct WLANHeader{
    // source address
    WLANAddr srcAddr;
    // destination address
    WLANAddr destAddr;
    // type
    unsigned short type;
  };

  // Ifconfig Struct Definition
  struct Ifconfig{
    // socket descriptor
    int sockid;
    // interface index
    int ifindex;
    // mac address
    WLANAddr hwaddr;
    // maximum transmission unit
    int mtu;
  };

// Public Member Functions
public:

  // Constructor
  WLAN(string interface);

  // Destructor
  ~WLAN();

  // Get Instance
  static WLAN* getInstance();

  // Start
  void start();

  // Stop
  void stop();

  // Send
  bool send(string address, string message);

  // Register Message Handler
  void registerMessageHandler(MessageHandler* messageHandler);

  // Get Address
  string getAddress();

// Private Member Functions
private:

  // convert a char to a hex digit
  static int hexdigit(char a);

  // convert an address string to a series of hex digits  
  static int sscanf6(char str[], int *a1, int *a2, int *a3, int *a4, int *a5,
    int *a6);

  // initialize wlan
  bool init();

  // receive
  void receive(); 

// Private Data Members
private:

  static WLAN* instance;
  char* device;
  unsigned char * buff;
  Ifconfig ifconfig;
  WLANHeader hdr;
  bool running;
  MessageHandler* messageHandler;

};

#endif
