#ifndef NAT_H
#define NAT_H

#include "address.h"
#include "host.h"
#include "link.h"
#include <set>
#include <vector>

struct NatEntry {
  Address internalAddress;
  short internalPort;
  short externalPort;
};

class Nat : public Node {
private:
  Address address_;

  Link *wanLink_;
  std::vector<NatEntry> natTable_;
  short port_ = 1000;
  std::string name() override { return "Nat"; }
  void sendPrivateIp(Packet* packet);
  void sendPublicIp(Packet* packet);

public:
  Nat(Address address) : address_(address) {}
  ~Nat() {}
  void setWanLink(Link *link) { wanLink_ = link; }
  void addNatTable(Host* host, short port);
  void receive(Link* link, Packet* packet) override;
  Address address() { return address_; }
};
#endif
