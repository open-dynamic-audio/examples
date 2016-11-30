
#include <vorpal/vorpal.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::cout;
using std::endl;
using std::shared_ptr;
using std::string;
using std::this_thread::sleep_for;
using std::vector;

using Clock = high_resolution_clock;

const auto ONE_SECOND = Clock::duration(milliseconds(1000));

void gameTick (double delta, shared_ptr<vorpal::SoundtrackEvent> ev);

int main (int argc, char** argv) {
  string event_name = "basic";
  if (argc >= 2) {
    event_name = argv[1];
  }

  std::srand(std::time(0));

  vorpal::Engine engine;
  {
    vorpal::Status status = engine.start({"../patches", VORPAL_PATCHES_PATH});
    if (!status.ok()) {
      cout << "Error: " << status.description() << endl;
      return -1;
    }
    cout << "Opened device " << status.description() << endl;
  }

  {
    shared_ptr<vorpal::SoundtrackEvent> ev;
    {
      vorpal::Status status = engine.eventInstance(event_name, &ev);
      if (!status.ok()) {
        cout << "Error: " << status.description() << endl;
        engine.finish();
        return -1;
      }
    }

    double seconds = 0.0;
    auto last = Clock::now();
    while (seconds < 10.0) {
      double delta = 1.0*(Clock::now() - last).count()/ONE_SECOND.count();
      last = Clock::now();
      gameTick(delta, ev);
      engine.tick(delta);
      seconds += delta;
    }
  }

  engine.finish();
  return 0;
}

void gameTick (double delta, shared_ptr<vorpal::SoundtrackEvent> ev) {
  static double total = 0.0;
  auto sleep_time = Clock::duration(milliseconds(16 + rand()%16));
  total += delta;
  ev->pushCommand("step", static_cast<int>(total));
  sleep_for(sleep_time);
}
