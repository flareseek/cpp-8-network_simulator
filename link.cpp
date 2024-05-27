#include "link.h"
#include "node.h"
#include <iostream>
#include <string>

void Link::sendPacket(Node* sender, Packet* packet) {
  Node* receiver = this->other(sender);
  int srcId = sender->id();
  int destId = receiver->id();
  
  std::cout << "Link: forwarding packet from node #" << srcId << ", to node #" << destId << std::endl;
  receiver->receive(packet);
}
