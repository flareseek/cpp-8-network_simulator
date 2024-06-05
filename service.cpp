#include "service.h"
#include "packet.h"
#include "host.h"
#include "simulator.h"

short Service::getPort() {
  return this->port_;
}

void Service::setPort(short port) {
  this->port_ = port;
}

void Service::takePacket(Packet* packet) {
  delete packet;
}

void Service::sendPacket(Packet* packet) {
  this->host_->send(packet);
}

