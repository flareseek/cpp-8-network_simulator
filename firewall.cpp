#include "firewall.h"
#include "host.h"
#include <string>

void Firewall::addAllowAnyPolicy(short destPort) {
  this->policies.push_back(new AllowAnyPolicy(destPort));
}

void Firewall::addAllowSpecificPolicy(Address srcAddress, short destPort) {
  this->policies.push_back(new AllowSpecificPolicy(srcAddress, destPort));
}

bool Firewall::AllowAnyPolicy::isAllowed(Packet* packet) {
  return packet->destPort() == AllowAnyPolicy::destPort_;
}

bool Firewall::AllowSpecificPolicy::isAllowed(Packet* packet) {
  return (packet->srcAddress() == AllowSpecificPolicy::srcAddress_) 
    && (packet->destPort() == AllowSpecificPolicy::destPort_);
}

void Firewall::receive(Link* link, Packet* packet) {
  if (link == this->receiveLink_)
    this->receiveInPacket(packet);
  else
    this->receiveOutPacket(packet);
}

void Firewall::receiveInPacket(Packet* packet) {
  for(FirewallPolicy* firewallPolicy : this->policies) {
    if (!firewallPolicy->isAllowed(packet)) continue;
    for (Link* link: this->links_) {
      Host* host = dynamic_cast<Host*>(link->other(this));
      if (host == nullptr) continue;
      if (host->address() == packet->destAddress()) {
        link->inPacket(this, packet);
        return;
      }
    }
    
  }
  // Dropping 4866<Packet> with src address 10.0.0.1 and dest port 5000
  Object::log("Dropping " + packet->toString() + " with src address " 
      + packet->srcAddress().toString() + " and dest port " 
      + std::to_string(packet->destPort()));
  delete packet;
}

void Firewall::receiveOutPacket(Packet* packet) {
  receiveLink_->inPacket(this, packet);
}

Firewall::~Firewall() {
  /* Object 에서 cleanup 하므로 */ 
  /*for(FirewallPolicy* policy : this->policies)*/
  /*  delete policy;*/
}
