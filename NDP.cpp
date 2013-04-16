// File: NDP.cpp

#include "NDP.h"

// Instance
NDP* NDP::instance = 0;

// WLAN
WLAN NDP::wlan("wlan0");

// Neighbor Table
vector<Neighbor> NDP::neighbors;

// Running
bool NDP::running = false;

// Update Thread
thread* NDP::uthread = 0;

// Listen Thread
thread* NDP::lthread = 0;

// Beacon Thread
thread* NDP::bthread = 0;

// Mutex
mutex NDP::barrier;

// Message Handler
MessageHandler* NDP::messageHandler = 0; 

// Constructor
NDP::NDP(){
  instance = this;
  srand(time(0));
}

// Destructor
NDP::~NDP(){
  stop();
}

// Get Instance
NDP* NDP::getInstance(){
  return instance;
}

// Start
void NDP::start(){
  if(!running){ 
    running = true;
    // register handler
    wlan.registerMessageHandler(instance);
    // update thread
    uthread = new thread(update);
    // listen thread
    lthread = new thread(listen);
    // beacon thread
    bthread = new thread(beacon);
  }
}

// Stop
void NDP::stop(){
  if(running){
    running = false;
    // Stop WLAN
    wlan.stop();
    // Free Memory
    bthread->join();
    delete bthread;
    /* Must stop recvfrom() in wlan */
    //lthread->join();
    //delete lthread;
    uthread->join();
    delete uthread;
  }  
}

// Register Message Handler
void NDP::registerMessageHandler(MessageHandler* messageHandler){
  this->messageHandler = messageHandler;
}

// Get Addresses 
vector<string> NDP::getAddresses(){
  vector<string> addresses;
  NDP::barrier.lock();
  for(Neighbor &n: NDP::neighbors){
    addresses.push_back(n.getAddress());
  }
  NDP::barrier.unlock();
  return addresses;
}

// Handle Message
void NDP::handleMessage(string src, string dst, string msg){
  // handle beacon
  if(msg == "<BEACON>"){
    // Lock
    barrier.lock();
    // Add to neighbor table
    addNeighbor(src);
    // Unlock
    barrier.unlock();
  }
  // handle other
  else{
    // delegate message
    if(messageHandler != 0){
      messageHandler->handleMessage(src, dst, msg);
    }
  }
}

// Update
void NDP::update(){
  // update loop
  while(running){
    // Removal list
    vector<string> removals;
    // Lock
    barrier.lock();
    // Update neighbor table
    for(auto &n: neighbors){
      // Arrived
      if(n.getArrived() == true){
        // New neighbor
        if(n.getAge() == -1){
          // Notify IARP
		barrier.unlock();
          instance->foundNeighbor(n.getAddress());
		barrier.lock();
        }
        n.setAge(0);
        n.setArrived(false);
      }
      // Not arrived
      else{
        // Neighbor lost
        if(n.getAge() >= maxAge){
          // Add to removal list          
          removals.push_back(n.getAddress());
        }
        // Neighbor not lost yet
        else{
          // Increment age
          n.setAge(n.getAge() + 1);
        }
      }    
    }
    // Remove entries
    for(auto &a: removals){
      // Remove neighbor
      removeNeighbor(a);
      // Notify IARP      
	barrier.unlock();
      instance->lostNeighbor(a);
	barrier.lock();
    }
    // Unlock
    barrier.unlock();
    // SLeep for random duration
    chrono::milliseconds dura(
    rand() % (updateMaxDelay - updateMinDelay) + updateMinDelay);
    this_thread::sleep_for(dura);
  }
}

// Beacon
void NDP::beacon(){
  // beacon loop
  while(running){
    // transmit beacon
    	time_t seconds;
    seconds = time(NULL);
    //cout << "SENDING OUT A BEACON "  << "\n";
    	wlan.send("ff:ff:ff:ff:ff:ff", "<BEACON>");
    	// Sleep
    	chrono::milliseconds dura(beaconDelay);
    	this_thread::sleep_for(dura);
  }
  return;
}

// Listen
void NDP::listen(){
  // start listening
  wlan.start();
}

// Add Neighbor
void NDP::addNeighbor(const string address){
  // Check if neighbor exists
  for(auto &n: neighbors){
    if(n.getAddress() == address){
      // Update neighbor
      n.setArrived(true);
      // Check if was new
      if(n.getAge() != -1){
        n.setAge(0);      
      }
      return;
    }
  }
  // Add new neighbor
  Neighbor n(address);
  neighbors.push_back(n);
}

// Remove Neighbor
void NDP::removeNeighbor(const string address){
  vector<Neighbor>::iterator it = neighbors.begin();
  // Find element  
  for (auto &n: neighbors){
    // Remove neighbor
    if(n.getAddress() == address){
      neighbors.erase(it);
      return;
    }    
    it++;
  }
}

// Found Neighbor
void NDP::foundNeighbor(const string address){
  if(messageHandler != 0){
    // delegate
    messageHandler->foundNeighbor(address);
  }
}

// Lost Neighbor
void NDP::lostNeighbor(const string address){
  if(messageHandler != 0){
    // delegate
    messageHandler->lostNeighbor(address);
  }
}
