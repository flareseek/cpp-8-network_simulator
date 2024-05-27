#include "host.h"
#include <iterator>
#include <iostream>

void Host::initialize() {

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

  // TODO: 서비스에 열린 포트로 정착 

  std::vector<Service*>::iterator it;
  for (it = this->services_.begin(); it != this->services_.end(); it++) {

    Service* service = *it;
    if (service->getPort() != packet->destPort()) continue;

    std::cout << "Host #" << this->id() << ": received packet, destination port: " << packet->destPort() << std::endl;
    service->takePacket(packet);
    return; 
  }
  std::string srcAddress = packet->srcAddress().toString();
  std::string destAddress = packet->destAddress().toString();
  unsigned long fileBytes = packet->data().size();

  std::cout << "Host #" << this->id() << ": no service for packet (from: "<< srcAddress << ", to: " << destAddress << ", "<< fileBytes << " bytes)" << std::endl;
}
