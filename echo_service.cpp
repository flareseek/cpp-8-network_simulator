#include "echo_service.h"
#include "simulator.h"
#include <iostream>
#include <string>

void EchoService::takePacket(Packet* packet) {
  Object::log("received \"" + packet->dataString() + "\" from " + packet->srcAddress().toString() + ":" + std::to_string(packet->srcPort()) + ", send reply with same data");

  Packet* newPacket = generatePacket(packet);
  Service::sendPacket(newPacket);

  delete packet;
}

Packet* EchoService::generatePacket(Packet* oldPacket) {
  Address srcAddress = this->host_->address();
  short srcPort = this->getPort();

  Address destAddress = oldPacket->srcAddress();
  short destPort = oldPacket->srcPort();

  return new Packet(srcAddress, destAddress, srcPort, destPort, oldPacket->data());
}
