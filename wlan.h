// 802.11 Programming example
// Author: Michel Barbeau, January 2004
//
// File: wlan.hpp
//

//INCLUDES
// for socket()
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>

// for htons()
#include <arpa/inet.h>

// for ifreq
#include <net/if.h>

#include <errno.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
using namespace std;

typedef int Outcome;
#define OK 0
#define NOK -1

#define MAX_NAME_LEN 128

// Declaration of struct WLANAddr.
#define WLAN_ADDR_LEN 6
struct WLANAddr
{
   // address
   unsigned char data[WLAN_ADDR_LEN];
   // return the address in a human readable form
   char * wlan2asc();
   // defined the address from a human readable form
   Outcome str2wlan(char s[]);
};

// format of an WLAN header
struct WLANHeader
{
   WLANAddr destAddr;
   WLANAddr srcAddr;
   unsigned short type;
   // make IP different from the real IP number (x0800)
   // types x3*** are not reserved
   #define IP_TYPE 0x3901
};
#define WLAN_HEADER_LEN 14 // bytes

// wireless interface configuration
struct Ifconfig
{
   int sockid; // socket descriptor
   int ifindex; // index of the interface
   WLANAddr hwaddr; // MAC address
   int mtu; // maximum transmission unit
};

static int hexdigit(char a);
static int sscanf6(char *str, int *a1, int *a2, int *a3, int *a4, int *a5, int *a6);
Outcome init();
void Receive(string *sender, string *message);
void shutdown();
Outcome MySend(string message);
