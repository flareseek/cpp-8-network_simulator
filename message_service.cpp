#include "message_service.h"
#include "packet.h"

void MessageService::send(std::string message) {
  Address srcAddress = Service::host_->address();
  short srcPort = Service::port_;
  
  Address destAddress = this->destAddress_;
  short destPort = this->destPort_;

  Packet* packet = new Packet(srcAddress, destAddress, 
                              srcPort, destPort, message);

  Service::host_->send(packet);
}

void MessageService::takePacket(Packet* packet) {
  std::cout << "MessageService: received \"" << packet->dataString() << "\" from " << packet->srcAddress().toString() << ":" << packet->srcPort() << std::endl;
  delete packet;
}
