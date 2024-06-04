#include "packet_sink_service.h"
#include <string>

void PacketSinkService::takePacket(Packet* packet) {
  this->receivePacketBytes += packet->data().size();
  Object::log("received total " + std::to_string(this->receivePacketBytes) +" bytes");
  delete packet;
}
