#ifndef BULK_SEND_SERVICE_H
#define BULK_SEND_SERVICE_H

#include "address.h"
#include "host.h"
#include "service.h"
#include "simulator.h"

#define PACKET_SIZE 512

class BulkSendService : Service {
  friend class BulkSendServiceInstaller;

public:
  void takePacket(Packet* packet) override;
  void repeat();
  void send(Packet* packet);
  void initialize() override;

private:
  Address destAddress;
  short destPort;
  double delay;
  double startTime;
  double stopTime;

  BulkSendService(Host *host, Address destAddress, short destPort,
                  double delay = 1, double startTime = 0,
                  double stopTime = 10.0) : Service(host, -2), destAddress(destAddress), destPort(destPort), delay(delay), startTime(startTime), stopTime(stopTime) {}

  std::string name() override { return "BulkSendService"; }
};

#endif
