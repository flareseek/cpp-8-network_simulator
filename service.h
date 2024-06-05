#ifndef SERVICE_H
#define SERVICE_H

#include "node.h"
#include "object.h"
#include "packet.h"

class Host;

class Service : public Object {
  friend class ServiceInstaller;

protected:
  // 서비스가 설치된 호스트
  Host *host_;

  // 서비스가 사용하는 포트
  short port_;

  Service(Host *host, int port) : host_(host), port_(port) {}


public:
  short getPort();
  void setPort(short port);
  virtual void takePacket(Packet* packet);
  virtual void sendPacket(Packet* packet);
  virtual void initialize() {}

  virtual ~Service() {};
};

#endif
