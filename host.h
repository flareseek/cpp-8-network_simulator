#ifndef HOST_H
#define HOST_H

#include "address.h"
#include "link.h"
#include "packet.h"
#include "service.h"
#include <sys/wait.h>
#include <vector>
#include <map>

class Host : public Node {
  friend class ServiceInstaller;

private:
  // 호스트의 주소
  Address address_;

  // 설치된 서비스 목록
  std::vector<Service *> services_;

  std::map<short, Service *> portToService_;
  const short INIT_CLIENT_PORT = 1000;
  void openPort();
  std::string name() override { return "Host"; }

public:
  Address address() { return address_; }
  Host(Address address) : address_(address) {}
  ~Host();

  // 호스트와 설치된 서비스를 전부 초기화한다.
  void initialize();

  // 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
  void send(Packet *packet);



  // custom
  void receive(Packet* packet) override;
};

#endif
