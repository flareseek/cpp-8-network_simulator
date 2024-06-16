#include "simulator.h"
#include "object.h"
#include <iostream>

std::priority_queue<Schedule> Simulator::eventQueue;
double Simulator::time_ = 0.0;

void Simulator::run() {
  Object::initializeAll();

  while (!Simulator::eventQueue.empty()) {
    Schedule schedule = Simulator::eventQueue.top();
    Simulator::time_ = schedule.time();
    schedule.call();
    Simulator::eventQueue.pop();
  }

  Object::cleanup();
}
