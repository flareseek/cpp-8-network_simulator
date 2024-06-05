#include "message_service.h"
#include "packet.h"
#include "simulator.h"
#include <string>

void MessageService::send(std::string message) {
  Address srcAddress = Service::host_->address();
  short srcPort = Service::port_;
  
  Address destAddress = this->destAddress_;
  short destPort = this->destPort_;

  Packet* packet = new Packet(srcAddress, destAddress, srcPort, destPort, message);
  Service::sendPacket(packet);
}

void MessageService::takePacket(Packet* packet) {
  Object::log("received \"" + packet->dataString() + "\" from " + packet->srcAddress().toString() + ":" + std::to_string(packet->srcPort()));
  delete packet;
}
