
#include <oda/oda.h>

#include <cstdio>
#include <thread>
#include <chrono>

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
    oda::Status status = engine.eventInstance("../patches/example", &ev);
    if (!status.ok()) {
      std::printf("Error: %s\n", status.description().c_str());
      engine.finish();
      return 1;
    }
  }
  //engine.testAudio();
  
  for (int i = 0; i < 1000; ++i) {
    engine.tick(0.001);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  engine.finish();
  return 0;
}

