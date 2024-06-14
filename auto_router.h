#ifndef AUTO_ROUTER_H
#define AUTO_ROUTER_H

#include "address.h"
#include "host.h"
#include "link.h"
#include "router.h"
#include "service.h"
#include <map>
#include <set>
#include <limits>

class NodeInfo {
  public:
    double distance;
    std::set<Link*> links;
    Link* hostLink;
    bool isVisited;
    NodeInfo(double distance = std::numeric_limits<double>::max(), Link* hostLink = nullptr, bool isVisited = false) : distance(distance), hostLink(hostLink), isVisited(isVisited){};
};

class AutoRouter : public Router {

private:
  std::string name() override { return "AutoRouter"; }

public:
  void calculate(const std::vector<Node *> &nodes,
                 const std::vector<Link *> &links) {
    // 전체 노드와 링크 정보를 통해
    // 모든 호스트로 전달될 수 있는 라우팅 테이블을 구성한다
    // TODO: 구현

    std::map<Node*, NodeInfo> store;
    for (Link* link : links) {
      store[link->nodeA()].links.insert(link);
      store[link->nodeB()].links.insert(link);
    }

    store[this].distance = 0.0;
    store[this].isVisited = true;
    for(Link* link: store[this].links) {
      store[link->other(this)].distance = link->delay();
      store[link->other(this)].hostLink = link;
    }

    Node* curNode = nullptr;
    for(Node* node: nodes) {
      if (store[node].isVisited) continue;
      if (curNode == nullptr || store[node].distance < store[curNode].distance) 
        curNode = node;
    }

    while(curNode != nullptr) {
      for(Link* link: store[curNode].links) {
        double dist = store[curNode].distance + link->delay();
        if (dist < store[link->other(curNode)].distance) {
          store[link->other(curNode)].distance = dist;
          store[link->other(curNode)].hostLink = store[curNode].hostLink;
        }
      }
      store[curNode].isVisited = true;

      curNode = nullptr;
      for(Node* node: nodes) {
        if (store[node].isVisited) continue;
        if (curNode == nullptr || store[node].distance < store[curNode].distance) 
          curNode = node;
      }
    }
    
    for (Node* node: nodes) {
      Host* host = dynamic_cast<Host*>(node);
      if (host == nullptr) continue;
      this->routingTable_.push_back({ host->address(), store[node].hostLink });
    }
  }
};

#endif
