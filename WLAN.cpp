// File: WLAN.cpp

#include "WLAN.h"

// WLAN Header
const string WLAN::WLAN_HEADER = "<WMESH>";

// BROADCAST
const string WLAN::WLAN_BROADCAST = "ff:ff:ff:ff:ff:ff";

// Instance
WLAN* WLAN::instance = 0;

// return the address in a human readable form
char * WLAN::WLANAddr::wlan2asc(){
   static char str[32];
   sprintf(str, "%x:%x:%x:%x:%x:%x", 
      data[0],data[1],data[2],data[3],data[4],data[5]);
   return str;
}

// defined the address from a human readable form
int WLAN::WLANAddr::str2wlan(char s[]){
   int a[6], i;  
   // parse the address
   if (sscanf6(s, a, a+1, a+2, a+3, a+4, a+5) < 6){
      return -1;
   }
   // make sure the value of every component does not exceed on byte
   for (i=0; i < 6; i++){
      if (a[i] > 0xff) return -1;
   }
   // assign the result to the "data" data member
   for (i=0; i < 6; i++){
      data[i] = a[i];
   }
   return 0;
}

// Constructor
WLAN::WLAN(string interface){
  // Instance
  instance = this;
  // Set Device
  device = new char[interface.length()+1];
  device[interface.length()] = 0;
  memcpy(device, interface.c_str(), interface.length());
  running = false;
  messageHandler = 0;
  // init
  if (!init()){
  // error occurred    
    exit(-1);
  }
}

// Destructor
WLAN::~WLAN(){
  // Stop
  stop();
  // Free Memory
  delete device;
}

// Get Instance
WLAN* WLAN::getInstance(){
  return instance;
}

// Start
void WLAN::start(){
  if(!running){
    running = true;
    // listen
    receive();
  }
}

// Stop
void WLAN::stop(){
  if(running){
    running = false;
    // close socket
    if (ifconfig.sockid != -1){
      close(ifconfig.sockid);
    } 
    // free buffer
    delete buff;
  }
}

// Register Message Handler
void WLAN::registerMessageHandler(MessageHandler* messageHandler){
  this->messageHandler = messageHandler;
}

// Get Address
string WLAN::getAddress(){
  string addr(ifconfig.hwaddr.wlan2asc());
  return addr;
}

// convert a char to a hex digit 
int WLAN::hexdigit(char a){
  if (a >= '0' && a <= '9') return(a-'0');
  if (a >= 'a' && a <= 'f') return(a-'a'+10);
  if (a >= 'A' && a <= 'F') return(a-'A'+10);
  return -1;
}

// convert an address string to a series of hex digits
int WLAN::sscanf6(char str[], int *a1, int *a2, int *a3, int *a4, int *a5, int *a6){
  int n;
  *a1 = *a2 = *a3 = *a4 = *a5 = *a6 = 0;
  while ((n=hexdigit(*str))>=0)
    (*a1 = 16*(*a1) + n, str++);
  if (*str++ != ':') return 1;
  while ((n=hexdigit(*str))>=0)
    (*a2 = 16*(*a2) + n, str++);
  if (*str++ != ':') return 2;
  while ((n=hexdigit(*str))>=0)
    (*a3 = 16*(*a3) + n, str++);
  if (*str++ != ':') return 3;
  while ((n=hexdigit(*str))>=0)
    (*a4 = 16*(*a4) + n, str++);
  if (*str++ != ':') return 4;
  while ((n=hexdigit(*str))>=0)
    (*a5 = 16*(*a5) + n, str++);
  if (*str++ != ':') return 5;
  while ((n=hexdigit(*str))>=0)
    (*a6 = 16*(*a6) + n, str++);
  return 6;
}

// Init
bool WLAN::init(){
  // Create device level socket
  // - AF_PACKET : packet interface on device level
  // - SOCK_RAW : raw packets including link level header
  // - ETH_P_ALL : all frames will be received
  if ((ifconfig.sockid = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1){ 
    printf("cannot open socket: %s\n", strerror(errno));
    return false;
  }
  // fetch the interface index
  struct ifreq ifr;
  strcpy(ifr.ifr_name, device);
  if (ioctl(ifconfig.sockid, SIOGIFINDEX, &ifr) < 0){
    printf("failed to fetch ifindex: %s\n", strerror(errno));
    return false;
  }
  ifconfig.ifindex = ifr.ifr_ifindex;
  // fetch the hardware address
  if (ioctl(ifconfig.sockid, SIOCGIFHWADDR, &ifr) == -1){
    printf("failed to fetch hardware address: %s\n", strerror(errno));
    return false;
  }
  memcpy(&ifconfig.hwaddr.data, &ifr.ifr_hwaddr.sa_data, WLAN_ADDR_LEN);
  // fetch the MTU
  if (ioctl(ifconfig.sockid, SIOCGIFMTU, &ifr) == -1){
    printf("WLANProtocol, failed to the MTU: %s\n", strerror(errno));
    return false;
  }
  ifconfig.mtu = ifr.ifr_mtu;
  // add the promiscuous mode
  struct packet_mreq mr;
  memset(&mr,0,sizeof(mr));
  mr.mr_ifindex = ifconfig.ifindex;
  mr.mr_type =  PACKET_MR_PROMISC;
  if (setsockopt(ifconfig.sockid, SOL_PACKET, PACKET_ADD_MEMBERSHIP, 
      (char *)&mr, sizeof(mr)) < 0){
    printf("WLANProtocol, failed to add the promiscuous mode: %s\n", 
    strerror(errno)); 
    return false;
  }
  // bind the socket to the interface
  // only traffic from that interface will be recieved
  struct sockaddr_ll sll;
  memset(&sll, 0, sizeof(sll));
  sll.sll_family = AF_PACKET;
  sll.sll_ifindex = ifconfig.ifindex;
  sll.sll_protocol = htons(ETH_P_ALL);
  if (bind(ifconfig.sockid, (struct sockaddr*)&sll, sizeof(sll)) < 0){
    printf("WLANProtocol, failed to bind the socket: %s\n", strerror(errno)); 
    return false;
  }  
  return true;
}

// Send
bool WLAN::send(string address, string message){
  // send buffer
  unsigned char buff[1024];
  // destination addres
  char* rp = new char[address.length()+1];
  rp[address.length()] = 0;
  memcpy(rp, address.c_str(), address.length());
  // message
  char* dp = new char[WLAN_HEADER.length() + message.length() + 1];
  dp[WLAN_HEADER.length() + message.length()] = 0;
  memcpy(dp, WLAN_HEADER.c_str(), WLAN_HEADER.length());
  memcpy(dp + WLAN_HEADER.length(), message.c_str(), message.length());
  // destination address (binary)
  WLANAddr daddr;
  // convert destination address from ASCII to binary
  daddr.str2wlan(rp);
  // store the destination address
  memmove(&hdr.destAddr, daddr.data, WLAN_ADDR_LEN);
  // store the source address
  memmove(&hdr.srcAddr, ifconfig.hwaddr.data, WLAN_ADDR_LEN);
  // set the type field
  hdr.type = htons(IP_TYPE);
  // store the header into the message 
  memmove(buff, &hdr, WLAN_HEADER_LEN);
  // store the payload
  memmove(buff+WLAN_HEADER_LEN, dp, strlen(dp));
  // set the "to address"
  struct sockaddr_ll to = {0};
  int tolen = sizeof(to);
  to.sll_family = AF_PACKET;
  to.sll_ifindex = ifconfig.ifindex;
  memmove(&(to.sll_addr), daddr.data, WLAN_ADDR_LEN);
  to.sll_halen = 6;  
  // send a frame
  int sentlen = sendto(
    ifconfig.sockid, buff, WLAN_HEADER_LEN+strlen(dp), 0, 
    (sockaddr *) &to, tolen);
  // release memory
  delete rp;
  delete dp;
  // Check errors
  if (sentlen == -1 ){
    printf("sendto() failed %s\n", strerror(errno));
    return false;
  }
  return true;
}

// Receive
void WLAN::receive(){
  // buffer for received data
  buff = new unsigned char[ifconfig.mtu];
  // frame length
  unsigned int i; // frame length
  // src address of message  
  struct sockaddr_ll from; // source address of the  message
  socklen_t fromlen = sizeof(struct sockaddr_ll); 
  int error;
  // receive loop
  while(running){
    // loop until a non-empty frame has been received on "device"
    while (running){
      // clear buffer
      memset(buff, 0, ifconfig.mtu);
      // wait and receive a frame
      fromlen = sizeof(from);
      i = recvfrom(ifconfig.sockid, buff, ifconfig.mtu, 0, 
        (struct sockaddr *) &from, &fromlen);
      if (i == -1){
        printf("cannot receive data: %s\n", strerror(errno));
        // sleep for 10 milliseconds before re-trying
        usleep(10000);
      }
      else{
        break; // exit the loop
      }
    }
    // Check if still running
    if(!running){
      break;
    }
    char asciiSrcAddr[32], asciiDestAddr[32];
    // casting to the WLAN header format
    WLANHeader * wlanHdr = (WLANHeader *) buff;
    // Get Destination
    char * dest = wlanHdr->destAddr.wlan2asc();
    strcpy(asciiDestAddr, dest);
    string destination(asciiDestAddr);
    // Get Source
    char * src = wlanHdr->srcAddr.wlan2asc();
    strcpy(asciiSrcAddr, src);
    string source(asciiSrcAddr);
    // get message
    string message((char*)(buff + sizeof(WLANHeader)));
    // check destination
    if(destination != getAddress() && destination != WLAN_BROADCAST){
      continue;
    }
    // check header
    if(WLAN_HEADER == message.substr(0, WLAN_HEADER.length())){
      // strip header
      message.erase(0, WLAN_HEADER.length());
    }
    else{
      continue;
    }
    // handle message
    if(messageHandler != 0){
      messageHandler->handleMessage(source, destination, message);
    }  
  }
}
