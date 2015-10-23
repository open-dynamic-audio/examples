
#include <oda/oda.h>

#include <cstdio>
#include <thread>
#include <chrono>

using std::chrono::steady_clock;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

int main (int argc, char** argv) {

  if (argc < 2) {
    std::printf("%s: Please specify event. Available ones are:\n%s",
                argv[0], "\texample\n\tbizarre\n\togg\n");
    return 1;
  }

  oda::Engine engine;
  oda::Status status = engine.start();
  if (!status.ok()) {
    std::printf("Error: %s\n", status.description().c_str());
    return 1;
  }
  std::printf("Opened device %s\n", status.description().c_str());
  engine.registerPath("../patches");
  engine.registerPath(ODA_PATCHES_PATH);

  {
    //engine.testAudio();
    //sleep_for(steady_clock::duration(milliseconds(3000)));

    oda::Event ev;

    {
      std::string patch_input = argv[1];
      oda::Status status = engine.eventInstance(patch_input, &ev);
      if (!status.ok()) {
        std::printf("Error: %s\n", status.description().c_str());
        engine.finish();
        return 1;
      }
    }
    
    for (int i = 0; i < 500; ++i) {
      auto t1 = steady_clock::now();
      if (i == 10) ev.pushCommand("start");
      //if (i == 80) ev.pushCommand("test");
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

