
#include <oda/oda.h>
#include <oda/status.h>

#include <cstdio>


int main () {
  oda::dummy();
  oda::System sys;
  oda::Status status = sys.start();
  if (!status.ok()) {
    std::printf("Error: %s\b", status.description().c_str());
    return 1;
  }
  std::printf("Opened device %s\n", status.description().c_str());

  // oda::playSineWave(4, 440);
  oda::playScale();

  sys.finish();
  return 0;
}

