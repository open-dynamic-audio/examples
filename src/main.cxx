
#include <oda/oda.h>

#include <cstdio>
#include <thread>
#include <chrono>

using std::chrono::steady_clock;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

int main (int argc, char** argv) {
  oda::dummy();
  oda::Engine engine;
  oda::Status status = engine.start();
  if (!status.ok()) {
    std::printf("Error: %s\b", status.description().c_str());
    return 1;
  }
  std::printf("Opened device %s\n", status.description().c_str());

  {
    //engine.testAudio();
    //sleep_for(steady_clock::duration(milliseconds(3000)));

    oda::Event ev;
    {
      std::string patch_input = argv[1];
      patch_input = "../patches/" + patch_input;
      oda::Status status = engine.eventInstance(patch_input, &ev);
      if (!status.ok()) {
        std::printf("Error: %s\n", status.description().c_str());
        engine.finish();
        return 1;
      }
    }
    
    for (int i = 0; i < 200; ++i) {
      auto t1 = steady_clock::now();
      engine.tick(0.02);
      auto t2 = steady_clock::now();
      auto one_milis = steady_clock::duration(milliseconds(20));
      auto sleep_time = one_milis - (t2 - t1);
      sleep_for(sleep_time);
    }
  }

  engine.finish();
  return 0;
}

