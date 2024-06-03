#ifndef AUTO_ROUTER_H
#define AUTO_ROUTER_H

#include "address.h"
#include "host.h"
#include "link.h"
#include "router.h"
#include "service.h"
#include <algorithm>
#include <functional>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>

struct NodeInfo {
  bool isVisited;
  double delay;
  Link* link;

  NodeInfo(bool isVisited, double delay, Link* link) 
    : isVisited(isVisited), delay(delay), link(link) {};
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
    //
    //
    // 필요한 아웃풋 [node, distance, link]
    // 초기 값 <node, vector<Link>>
    // heap dlay, node, link
    std::map<Node*, NodeInfo> nodeInfo;

    std::map<Node*, std::vector<Link*>> nodeMap;
    for (Node* node: nodes) {
      nodeInfo[node] = NodeInfo(false, std::numeric_limits<double>::max(), nullptr);
      for (Link* link: links) {
        if (link->nodeA() == node || link->nodeB() == node) {
          nodeMap[node].push_back(link);
        }
      }
    }

    nodeInfo[this].isVisited = true;
    nodeInfo[this].delay = 0.0;

    // delay, node*, link
    std::priority_queue<
      std::pair<double, Node*>,
      std::vector<std::pair<double, Node*>>,
      std::greater<std::pair<double, Node*>>
        > pq;
    for (Link* link : nodeMap[this]) {
      Node* oppositeNode = link->other(this);
      double delay = link->delay();

      nodeInfo[oppositeNode].delay = delay;
      nodeInfo[oppositeNode].link = link;
      pq.push(std::make_pair(delay, oppositeNode));
    }

    while (!pq.empty()) {
      auto top = pq.top();
      pq.pop();
      
      NodeInfo& currentNodeInfo = nodeInfo[top.second];
      if (currentNodeInfo.isVisited) continue;
      currentNodeInfo.isVisited = true;

      for (Link* link: nodeMap[top.second]) {
        Node* oppositeNode = link->other(top.second);
        double lDelay = link->delay();
        double delay = currentNodeInfo.delay + lDelay;
        if (delay < nodeInfo[oppositeNode].delay) {
          nodeInfo[oppositeNode].delay = delay;
          nodeInfo[oppositeNode].link = currentNodeInfo.link;

          pq.push(std::make_pair(delay, oppositeNode));
        }
      }
    }

    for (auto &infoPair: nodeInfo) {
      if (infoPair.first == this) continue;
      Host* host = dynamic_cast<Host*>(infoPair.first);
      if (host == nullptr) continue;
      Router::routingTable_.push_back({ host->address(), nodeInfo[host].link });
    }
  }
};

#endif
