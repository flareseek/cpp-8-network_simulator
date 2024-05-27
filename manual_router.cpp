#include "manual_router.h"

void ManualRouter::addRoutingEntry(const Address &destination, Link* nextLink) {
  Router::routingTable_.push_back({ destination, nextLink });
}
