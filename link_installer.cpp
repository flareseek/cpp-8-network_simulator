#include "link_installer.h"
#include "link.h"

Link* LinkInstaller::install(Node* a, Node* b, double delay) {
  Link* link = new Link(a, b, delay);
  a->links_.push_back(link);
  b->links_.push_back(link);
  return link;
}

