#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "packet.h"
#include "object.h"
#include <vector>

class Node : public Object {
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;

protected:
  std::vector<Link*> links_;

public:
  Node() : id_(nextId_++) {}
  int id() const { return id_; }
  virtual ~Node() {};

  virtual void receive(Packet* packet) = 0;
};

#endif
