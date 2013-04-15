// File: MessageHandler.h

#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>

using namespace std;

// MessageHandler Class Definition
class MessageHandler{

// Public Member Functions
public:

  // Handle Message
  virtual void handleMessage(string src, string dst, string msg);

  // Found Neighbor
  virtual void foundNeighbor(const string address);

  // Lost Neighbor
  virtual void lostNeighbor(const string address);

};

#endif

