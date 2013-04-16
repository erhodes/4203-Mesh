// File: NDP.h

#ifndef NDP_H
#define NDP_H

#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

#include "MessageHandler.h"
#include "WLAN.h"
#include "Neighbor.h"

using namespace std;

// NDP Class Definition
class NDP: public MessageHandler{

  // Constants
  static const int updateMinDelay = 100;
  static const int updateMaxDelay = 300;
  static const int beaconDelay = 100;
  static const int maxAge = 10;

// Public Member Functions
public:

  // Constructor
  NDP();

  // Destructor
  ~NDP();

  // Get Instance
  static NDP* getInstance();

  // Handle Message
  virtual void handleMessage(string src, string dst, string msg);

  // Start
  void start();

  // Stop
  void stop();

  // Register Message Handler
  void registerMessageHandler(MessageHandler* messageHandler);

  // Get Addresses 
  vector<string> getAddresses();

// Private Member Function
private:

  // Update
  static void update();

  // Beacon
  static void beacon();

  // Listen
  static void listen();

  // Found Neighbor
  void foundNeighbor(const string address);

  // Lost Neighbor
  void lostNeighbor(const string address);

  // Add Neighbor
  static void addNeighbor(string address);

  // Remove Neighbor
  static void removeNeighbor(string address);

// Private Data Members
private:

  static NDP* instance;
  static WLAN wlan;
  static vector<Neighbor> neighbors;
  static bool running;
  static thread* uthread; // update thread
  static thread* lthread; // listen thread
  static thread* bthread; // beacon thread
  static mutex barrier;
  static MessageHandler* messageHandler;

};

#endif
