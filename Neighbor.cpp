// File: Neighbor.cpp

#include "Neighbor.h"

// Stream Insertion Operator
ostream& operator<<(ostream& out, const Neighbor& neighbor){
  out << "<";
  out << neighbor.getAddress();
  out << ", ";
  out << neighbor.getArrived();
  out << ", ";
  out << neighbor.getAge();
  out << ">";
}

// Constructor
Neighbor::Neighbor(string address, bool arrived, int age):
  address(address), arrived(arrived), age(age){
}

// Get Address
string Neighbor::getAddress() const{
  return address;
}

// Get Arrived
bool Neighbor::getArrived() const{
  return arrived;
}

// Set Arrived
void Neighbor::setArrived(bool arrived){
  this->arrived = arrived;
}

// Get Age
int Neighbor::getAge() const{
  return age;
}

// Set Age
void Neighbor::setAge(int age){
  this->age = age;
}

