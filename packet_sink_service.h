#ifndef PACKET_SINK_SERVICE_H
#define PACKET_SINK_SERVICE_H

#include "service.h"
#include <string>

class PacketSinkService : public Service {
  friend class PacketSinkServiceInstaller;

public:
  void initialize() override {}
  void takePacket(Packet* packet) override;

private:
  PacketSinkService(Host *host, short port): Service(host, port) {}
  std::string name() override { return "PacketSinkService"; }

  int receivePacketBytes = 0;
};

#endif
