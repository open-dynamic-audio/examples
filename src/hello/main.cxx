
#include <vorpal/vorpal.h>

#include <chrono>
#include <memory>
#include <thread>

#include <cstdio>

using std::shared_ptr;

using Clock = std::chrono::high_resolution_clock;
using Milliseconds = std::chrono::milliseconds;

const double DURATION = 1.0;

void sleep_for (double seconds) {
  auto milliseconds = Milliseconds(static_cast<long int>(1000.0*DURATION));
  auto sleep_time = Clock::duration(milliseconds);
  std::this_thread::sleep_for(sleep_time);
}

int main () {
  vorpal::Engine engine;
  vorpal::Status status = vorpal::Status::OK("");
  if (!(status = engine.start({"../patches", VORPAL_PATCHES_PATH})).ok()) {
    std::printf("Error: %s\n", status.description().c_str());
    return 1;
  }
  std::printf("Opened device %s\n", status.description().c_str());

  {
    shared_ptr<vorpal::SoundtrackEvent> ev;
    if (!(status = engine.eventInstance("hello", &ev)).ok()) {
      std::printf("Error: %s\n", status.description().c_str());
      engine.finish();
      return 1;
    }

    engine.tick(DURATION);
    sleep_for(DURATION);
  }

  engine.finish();
  return 0;
}
