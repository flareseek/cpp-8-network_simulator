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
  void fowardPacket(Packet* packet);

public :
  void receive(Packet* packet) override;
  virtual ~Router() {};

protected:
  std::vector<RoutingEntry> routingTable_;
};

#endif
