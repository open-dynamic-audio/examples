
#include <oda/oda.h>

#include <chrono>
#include <memory>
#include <thread>

#include <cstdio>

using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::shared_ptr;
using std::this_thread::sleep_for;

using Clock = high_resolution_clock;

int main (int argc, char** argv) {

  if (argc < 2) {
    std::printf("%s: Please specify event. Available ones are:\n%s",
                argv[0], "\texample\n\tbizarre\n\togg\n");
    return 1;
  }

  oda::Engine engine;
  oda::Status status = engine.start({"../patches", ODA_PATCHES_PATH});
  if (!status.ok()) {
    std::printf("Error: %s\n", status.description().c_str());
    return 1;
  }
  std::printf("Opened device %s\n", status.description().c_str());

  {
    //engine.testAudio();
    //sleep_for(steady_clock::duration(milliseconds(3000)));

    shared_ptr<oda::SoundtrackEvent> ev;

    {
      std::string patch_input = argv[1];
      oda::Status status = engine.eventInstance(patch_input, &ev);
      if (!status.ok()) {
        std::printf("Error: %s\n", status.description().c_str());
        engine.finish();
        return 1;
      }
    }

    auto last = Clock::now();
    double delta_time = 0.02;
    auto sleep_time = Clock::duration(milliseconds(20));
    std::vector<decltype(sleep_time.count())> times;
    for (int i = 0; i < 500; ++i) {
      if (i == 10) ev->pushCommand("foo", 3.14, "1337", 42);
      engine.tick(delta_time);
      auto now = Clock::now();
      sleep_for(sleep_time - (now - last));
      last = Clock::now();
    }
  }

  engine.finish();
  return 0;
}
