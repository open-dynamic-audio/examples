
#include <oda/oda.h>

#include <cstdio>
#include <thread>
#include <chrono>

using std::chrono::steady_clock;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

int main () {
  oda::dummy();
  oda::Engine engine;
  oda::Status status = engine.start();
  if (!status.ok()) {
    std::printf("Error: %s\b", status.description().c_str());
    return 1;
  }
  std::printf("Opened device %s\n", status.description().c_str());

  {
    oda::Event ev;
    {
      oda::Status status = engine.eventInstance("../patches/example", &ev);
      if (!status.ok()) {
        std::printf("Error: %s\n", status.description().c_str());
        engine.finish();
        return 1;
      }
    }
    //engine.testAudio();
    
    for (int i = 0; i < 200; ++i) {
      auto t1 = steady_clock::now();
      engine.tick(0.01);
      auto t2 = steady_clock::now();
      auto one_milis = steady_clock::duration(milliseconds(10));
      auto sleep_time = one_milis - (t2 - t1);
      sleep_for(sleep_time);
    }
  }

  engine.finish();
  return 0;
}

