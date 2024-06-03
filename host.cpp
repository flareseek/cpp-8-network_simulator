#include "host.h"
#include "simulator.h"
#include <iterator>
#include <iostream>
#include <string>

void Host::initialize() {
  this->openPort();
}

void Host::openPort() {
  std::vector<Service*>::iterator it;
  for (it = this->services_.begin(); it != this->services_.end(); it++) {
    Service* service = *it;
    short port = service->getPort();
    if (port != -2) {
      if (port == -1) port = this->INIT_CLIENT_PORT;
      while(this->portToService_.find(port) != this->portToService_.end()) {
        // std::cout << "Host #" << this->id() << ": service port conflict (" << port << ")" << std::endl;
        port++;
      }

      service->setPort(port);
      this->portToService_[port] = service;
    }
    service->initialize();
  }
}

void Host::send(Packet* packet) {
  // 일단은 0번째 index로 보내기...
  if (this->links_.size() != 0) {
    Simulator::schedule(0.0, [this, packet]() { 
        Object::log("sending packet: " + packet->toString());
        this->links_.front()->sendPacket(this, packet); 
        });
  }
}

void Host::receive(Packet* packet) {
  if (this->portToService_.find(packet->destPort()) == this->portToService_.end()) {
    Object::log("no service for packet: " + packet->toString());
    delete packet;
    return;
  }
  Service* service = this->portToService_[packet->destPort()];
  Simulator::schedule(0.0, [this, packet, service]() {
      Object::log("received packet: " + packet->toString() + ", forwarding to " + service->toString());
      service->takePacket(packet);
      });
}

Host::~Host() {
  for (std::vector<Service*>::iterator it = this->services_.begin(); it != this->services_.end(); it++) {
    Service* service = *it; 
    /* std::cout << "delete service"  << std::endl; */
    delete service;
  }
}

