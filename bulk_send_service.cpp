#include "bulk_send_service.h"
#include "simulator.h"
void BulkSendService::initialize() {
  double time = this->startTime_;
  while(time < this->stopTime_) {
    Simulator::schedule(time, [this]() {
        this->sendPacket(this->generatePacket());
        });
    time += this->delay_;
  }
}

void BulkSendService::sendPacket(Packet* packet) {
  Object::log("sending data");
  Service::sendPacket(packet);
}

Packet* BulkSendService::generatePacket() {
  Address srcAddress = Service::host_->address();
  short srcPort = Service::port_;

  Address destAddress = this->destAddress_;
  short destPort = this->destPort_;

  return new Packet(srcAddress, destAddress, 
      srcPort, destPort, std::string(PACKET_SIZE, 'A'));
}

