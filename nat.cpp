#include "nat.h"
#include "packet.h"

void Nat::addNatTable(Host* host, short port) {
  this->natTable_.push_back({host->address(), port, this->port_});
  this->port_ ++;
}

void Nat::receive(Link* link, Packet* packet) {
  if (link == this->wanLink_)
    this->sendPrivateIp(packet);
  else 
    this->sendPublicIp(packet);
  delete packet;
}

void Nat::sendPublicIp(Packet* packet) {
  Packet* newPacket = nullptr;
  for(NatEntry& natEntry: natTable_) {
    if (natEntry.internalAddress == packet->srcAddress() 
        && natEntry.internalPort == packet->srcPort()) {
      newPacket = new Packet(this->address_, packet->destAddress(), natEntry.externalPort, packet->destPort(), packet->data());
      break;
    }
  }
  this->wanLink_->inPacket(this, newPacket);
}

void Nat::sendPrivateIp(Packet* packet) {
  for(NatEntry& natEntry: natTable_) {
    if (natEntry.externalPort == packet->destPort()) {
      Packet* newPacket = new Packet(packet->srcAddress(), natEntry.internalAddress, packet->srcPort(), natEntry.internalPort, packet->data());
      for(Link* link: this->links_) {
        Host* host = dynamic_cast<Host*>(link->other(this));
        if (host == nullptr) continue;
        if (host->address() == newPacket->destAddress()) 
          link->inPacket(this, newPacket);
      }
    }
  }
}
