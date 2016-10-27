
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

const auto ONE_SECOND = Clock::duration(milliseconds(1000));

void gameTick (shared_ptr<oda::SoundtrackEvent> ev, double *seconds) {
  auto sleep_time = Clock::duration(milliseconds(10 + rand()%16));
  ev->pushCommand("step", static_cast<int>(*seconds));
  sleep_for(sleep_time);
  *seconds += 1.0*sleep_time.count()/ONE_SECOND.count();
}

int main (int argc, char** argv) {

  if (argc < 2) {
    std::printf("%s: Please specify event. Available ones are:\n%s",
                argv[0], "\texample\n\tbizarre\n\togg\n");
    return 1;
  }

  std::srand(std::time(0));

  oda::Engine engine;
  oda::Status status = engine.start({"../patches", ODA_PATCHES_PATH});
  if (!status.ok()) {
    std::printf("Error: %s\n", status.description().c_str());
    return 1;
  }
  std::printf("Opened device %s\n", status.description().c_str());

  {
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

    double seconds = 0.0;
    while (seconds < 10.0) {
      gameTick(ev, &seconds);
      engine.tick(seconds);
    }
  }

  engine.finish();
  return 0;
}
