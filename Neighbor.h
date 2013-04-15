// File: Neighbor.h

#ifndef NEIGHBOR_H
#define NEIGHBOR_H

#include <iostream>
#include <string>
using namespace std;

// Neighbor Class Definition
class Neighbor{

// Stream Insertion Operator
friend ostream& operator<<(ostream& out, const Neighbor& neighbor);

// Public Members
public:

  // Constructor
  Neighbor(string address, bool arrived = true, int age = -1);

  // Get Address
  string getAddress() const;

  // Get Arrived
  bool getArrived() const;

  // Set Arrived
  void setArrived(bool arrived);

  // Get Age
  int getAge() const;

  // Set Age
  void setAge(int age);

// Private Members
private:

  string address;
  bool arrived;
  int age;

};

#endif

