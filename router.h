#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include <iostream>

struct RoutingEntry {
public:
  Address destination;
  Link *nextLink;
};

class Router : public Node {
private:
  void forwardPacket(Packet* packet, Link* link);
  Link* findLink(Packet* packet);
  std::string name() override { return "Router"; }

public :
  void receive(Link* link, Packet* packet) override;
  virtual ~Router() {};

protected:
  std::vector<RoutingEntry> routingTable_;
};

#endif
