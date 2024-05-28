#include "host.h"
#include <iterator>
#include <iostream>

void Host::initialize() {
  std::vector<Service*>::iterator it;
  for (it = this->services_.begin(); it != this->services_.end(); it++) {
    Service* service = *it;
    short port = service->getPort();
    if (port < 0) port = this->clientPort_;
    while (this->portToService_.find(port) != this->portToService_.end()) {
      std::cout << "Host #" << this->id() << ": service port conflict (" << port << ")" << std::endl;
      port = ++(this->clientPort_);
    }
    service->setPort(port);
    this->portToService_[port] = service;
    this->clientPort_ ++;
  }
}

void Host::send(Packet* packet) {
  // 일단은 0번째 index로 보내기...
  if (this->links_.size() != 0) {
    std::string srcAddress = packet->srcAddress().toString();
    std::string destAddress = packet->destAddress().toString();
    unsigned long fileBytes = packet->data().size();

    std::cout << "Host #" << this->id() << ": sending packet (from: " << srcAddress << ", to: "<< destAddress << ", " << fileBytes <<" bytes)" << std::endl;
    this->links_.front()->sendPacket(this, packet);
  }
}

void Host::receive(Packet* packet) {
  if (this->portToService_.find(packet->destPort()) == this->portToService_.end()) {
    std::string srcAddress = packet->srcAddress().toString();
    std::string destAddress = packet->destAddress().toString();
    unsigned long fileBytes = packet->data().size();

    std::cout << "Host #" << this->id() << ": no service for packet (from: " << srcAddress << ", to: " << destAddress << ", " << fileBytes << " bytes)" << std::endl;
    return;
  }
  Service* service = this->portToService_[packet->destPort()];
  std::cout << "Host #" << this->id() << ": received packet, destination port: " << packet->destPort() << std::endl;
  service->takePacket(packet);
}
