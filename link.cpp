#include "link.h"
#include "node.h"
#include "simulator.h"
#include <iostream>
#include <string>

void Link::sendPacket(Node* sender, Packet* packet) {
  Object::log("packet in: " + packet->toString() + " from " + sender->toString());
  Node* receiver = this->other(sender);

  Simulator::schedule(this->delay(), [this, packet, receiver]() {
      Object::log("packet out: " + packet->toString() + " to " + receiver->toString());
      receiver->receive(packet);
      });
}
