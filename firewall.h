#include "address.h"
#include "node.h"
#include "object.h"
#include <string>
#include <vector>

class FirewallPolicy : public Object {
  private:
    std::string name() override { return "FirewallPolicy"; }

  public:
    virtual bool isAllowed(Packet* packet) { return false; }
    ~FirewallPolicy() override {}
};

class Firewall : public Node {
private:
  class AllowAnyPolicy : public FirewallPolicy {
  private:
    short destPort_;

    std::string name() override { return "AllowAnyPolicy"; }

  public:
    AllowAnyPolicy(short destPort) : destPort_(destPort) {}
    bool isAllowed(Packet* packet) override;
    ~AllowAnyPolicy() override {}
  };

  class AllowSpecificPolicy : public FirewallPolicy {
  private:
    Address srcAddress_;
    short destPort_;

    std::string name() override { return "AllowSpecificPolicy"; }

  public:
    AllowSpecificPolicy(Address srcAddress, short destPort)
        : srcAddress_(srcAddress), destPort_(destPort) {}
    bool isAllowed(Packet* packet) override;
    ~AllowSpecificPolicy() override {}
  };

  std::string name() override { return "Firewall"; }
  Link *receiveLink_ = nullptr;
  std::vector<FirewallPolicy* > policies;

  void receiveInPacket(Packet* packet);
  void receiveOutPacket(Packet* packet);

public:
  void setReceiveLink(Link *link) { receiveLink_ = link; }

  void addAllowAnyPolicy(short destPort);
  void addAllowSpecificPolicy(Address srcAddress, short destPort);
  void receive(Link* link, Packet* packet) override;

  ~Firewall();
};

