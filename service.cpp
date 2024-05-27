#include "service.h"

short Service::getPort() {
  return this->port_;
}

void Service::setPort(short port) {
  this->port_ = port;
}