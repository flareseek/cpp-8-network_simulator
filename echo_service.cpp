#include "echo_service.h"
#include "simulator.h"
#include <iostream>
#include <string>

void EchoService::takePacket(Packet* packet) {
  Object::log("received \"" + packet->dataString() + "\" from " + packet->srcAddress().toString() + ":" + std::to_string(packet->srcPort()) + ", send reply with same data");

  Simulator::schedule(0.0, [this, packet]() {
      this->send(packet);
      });
}

void EchoService::send(Packet* oldPacket) {
  Address srcAddress = this->host_->address();
  short srcPort = this->getPort();

  Address destAddress = oldPacket->srcAddress();
  short destPort = oldPacket->srcPort();

  Packet* newPacket = new Packet(srcAddress, destAddress, srcPort, destPort, oldPacket->data());
  Simulator::schedule(0.0, [this, newPacket]() {
      this->host_->send(newPacket);
      });

  delete oldPacket;
}
