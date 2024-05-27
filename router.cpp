#include "router.h"

void Router::receive(Packet* packet) {
  this->fowardPacket(packet);
}

// NOTE: 일단은 같은 목적지가 여러개 있을 때 제일 먼저 저장된 링크를 이용
void Router::fowardPacket(Packet* packet) {
  std::vector<RoutingEntry>::iterator it;
  std::string srcAddress = packet->srcAddress().toString();
  std::string destAddress = packet->destAddress().toString();
  unsigned long fileBytes = packet->data().size();

  for (it = routingTable_.begin(); it != routingTable_.end(); it++) {
    RoutingEntry routingEntry = *it;
    if (routingEntry.destination == packet->destAddress()) {

      std::cout << "Router #" << this->id() << ": forwarding packet (from: " << srcAddress << ", to: " << destAddress << ", " << fileBytes << " bytes)" << std::endl;
      routingEntry.nextLink->sendPacket(this, packet);
      return;
    }
  }

  std::cout << "Router #" << this->id() << ": no route for packet (from: " << srcAddress << ", to: " << destAddress << ", " << fileBytes << " bytes)" << std::endl;
}


