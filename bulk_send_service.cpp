#include "bulk_send_service.h"
#include "simulator.h"
void BulkSendService::initialize() {
  Simulator::schedule(this->startTime_ - Simulator::now(), [this]() {
        this->send();
        this->repeat();
      });
}

void BulkSendService::repeat() {
  if (!((this->startTime_ <= (Simulator::now() + this->delay_)) &&
      ((Simulator::now() + this->delay_) < this->stopTime_))) return;

  Simulator::schedule(this->delay_, [this]() {
      this->send();
      this->repeat();
      });
}

void BulkSendService::send() {
  Address srcAddress = Service::host_->address();
  short srcPort = Service::port_;

  Address destAddress = this->destAddress_;
  short destPort = this->destPort_;

  Packet* packet = new Packet(srcAddress, destAddress, 
      srcPort, destPort, std::string(512, 'A'));

  Simulator::schedule(0.0, [this, packet]() { 
      Object::log("sending data");
      Service::host_->send(packet); 
      });
}

