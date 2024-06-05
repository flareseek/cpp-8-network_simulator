#include "router.h"
#include "simulator.h"

void Router::receive(Packet* packet) {
  Link* link = this->findLink(packet);
  this->forwardPacket(packet, link);
}

// NOTE: 일단은 같은 목적지가 여러개 있을 때 제일 먼저 저장된 링크를 이용
Link* Router::findLink(Packet* packet) {
  std::vector<RoutingEntry>::iterator it;
  for (it = routingTable_.begin(); it != routingTable_.end(); it++) {
    RoutingEntry routingEntry = *it;
    if (routingEntry.destination == packet->destAddress()) {
      return routingEntry.nextLink;
    }
  }
  return nullptr;
}

void Router::forwardPacket(Packet* packet, Link* nextLink) {
  if (nextLink == nullptr) {
    Object::log("no route for packet: " + packet->toString());
    delete packet;
    return;
  }

  
  Object::log("forwarding packet: " + packet->toString() + " to " + nextLink->toString());
  nextLink->inPacket(this, packet);
}


