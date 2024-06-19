#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <ios>
#define RANDOM_SEED 369369

#include <iostream>
#include <cstdlib>
#include <functional>
#include <queue>
#include <vector>

class Simulator;

class Schedule {
private:
  double time_;
  std::function<void()> function_;

public:
  double time() { return time_; }
  void call() { function_(); }

  Schedule(double time, std::function<void()> function)
      : time_(time), function_(function) {}

  bool operator < (const Schedule& other) const {
    return this->time_ > other.time_;
  }
};

class Simulator {
private:
  static double time_;
  static std::priority_queue<Schedule> eventQueue;

public:
  static double now() { return time_; }

  static void prepare() { srand(RANDOM_SEED); }

  static void schedule(double time, std::function<void()> function) {
    // 스케줄 큐에 스케줄을 추가한다.
    // TODO: 구현
    //
    Schedule schedule(time, function);
    Simulator::eventQueue.push(schedule);
  }

  static void run();
};

#endif
