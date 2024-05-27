#include "echo_service.h"
#include <iostream>

void EchoService::takePacket(Packet* packet) {
  std::cout << "EchoService: received \"" << packet->dataString() << "\" from " << packet->srcAddress().toString() << ":" << packet->srcPort() << ", send reply with same data" << std::endl;
  this->send(packet);
}

void EchoService::send(Packet* oldPacket) {
  Address srcAddress = this->host_->address();
  short srcPort = this->getPort();

  Address destAddress = oldPacket->srcAddress();
  short destPort = oldPacket->srcPort();

  Packet* newPacket = new Packet(srcAddress, destAddress, srcPort, destPort, oldPacket->data());

  this->host_->send(newPacket);
}

