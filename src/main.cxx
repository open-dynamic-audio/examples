
#include <oda/oda.h>

#include <cstdio>


int main () {
  oda::dummy();
  oda::Engine engine;
  oda::Status status = engine.start();
  if (!status.ok()) {
    std::printf("Error: %s\b", status.description().c_str());
    return 1;
  }
  std::printf("Opened device %s\n", status.description().c_str());

  engine.testAudio();

  engine.finish();
  return 0;
}

