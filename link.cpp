#include "link.h"
#include "node.h"
#include "simulator.h"
#include <iostream>
#include <string>

void Link::inPacket(Node* sender, Packet* packet) {
  Node* receiver = this->other(sender);

  Object::log("packet in: " + packet->toString() + " from " + sender->toString());
  Simulator::schedule(Simulator::now() + this->delay_, [this, receiver, packet]() {
    this->outPacket(receiver, packet);
  });
}

void Link::outPacket(Node* receiver, Packet* packet) {
  Object::log("packet out: " + packet->toString() + " to " + receiver->toString());
  receiver->receive(packet);
}

