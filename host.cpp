#include "host.h"
#include "simulator.h"
#include <iterator>
#include <iostream>
#include <string>
#include <vector>

void Host::initialize() {
  this->openPort();
  this->initializeService();
}

void Host::openPort() {
  std::vector<Service*>::iterator it;
  for (it = this->services_.begin(); it != this->services_.end(); it++) {
    Service* service = *it;
    short port = service->getPort();
    if (port < 0) port = this->INIT_CLIENT_PORT;
    while(this->portToService_.find(port) != this->portToService_.end()) {
      // std::cout << "Host #" << this->id() << ": service port conflict (" << port << ")" << std::endl;
      port++;
    }

    service->setPort(port);
    this->portToService_[port] = service;
  }
}

void Host::send(Packet* packet) {
  // 일단은 0번째 index로 보내기...
  if (this->links_.size() != 0) {
    Object::log("sending packet: " + packet->toString());
    this->links_.front()->inPacket(this, packet); 
  } else {
    Object::log("not found a link");
    delete packet;
  }
}

void Host::receive(Packet* packet) {
  if (this->portToService_.find(packet->destPort()) == this->portToService_.end()) {
    Object::log("no service for packet: " + packet->toString());
    delete packet;
    return;
  }
  Service* service = this->portToService_[packet->destPort()];
  Object::log("received packet: " + packet->toString() + ", forwarding to " + service->toString());

  service->takePacket(packet);
}

void Host::initializeService() {
  std::vector<Service*>::iterator it;
  for(it = services_.begin(); it != services_.end(); it++) {
    Service* service = *it;
    service->initialize();
  }
}

Host::~Host() {
  for (std::vector<Service*>::iterator it = this->services_.begin(); it != this->services_.end(); it++) {
    Service* service = *it; 
    /* std::cout << "delete service"  << std::endl; */
    delete service;
  }
}

