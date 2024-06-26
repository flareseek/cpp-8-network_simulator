#ifndef LINK_H
#define LINK_H

#include "object.h"
#include "packet.h"
#include <cstdlib>

class Node;

class Link : public Object {
  friend class LinkInstaller;

public:
  ~Link() {};
  /*void sendPacket(Node* sender, Packet* packet);*/
  void inPacket(Node* sender, Packet* packet);
  void outPacket(Node* receiver, Packet* packet);

  // 매개변수로 주어진 노드가 아닌 반대편 노드를 구한다.
  Node *other(const Node *node) const {
    return node == nodeA_ ? nodeB_ : nodeA_;
  }

  double delay() { return delay_; }
  Node* nodeA() { return nodeA_; }
  Node* nodeB() { return nodeB_; }

private:
  Link(Node *nodeA, Node *nodeB, double delay = 0.0) : nodeA_(nodeA), nodeB_(nodeB), delay_(delay) {}

  Node *nodeA_;
  Node *nodeB_;
  double delay_;

  std::string name() { return "Link"; }
  
};

#endif
