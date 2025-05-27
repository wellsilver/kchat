#include <vector>
#include <string>
#include <cstring>
#include <thread>

#include <ncurses.h>
#include <unistd.h>
#include <signal.h>

#include "net.hpp"
#include "tui.hpp"

bool end = false; // if its time to exit
unsigned int tasks = 0; // running tasks

void intHandler(int dummy) {
  end = true;
}

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  bool trackeronly = false;

  for (unsigned int i = 0;i < argc;i++) {
    if (strcmp("--tracker-only", argv[i]) == 0) {
      trackeronly = true;
    }
    if (strcmp("--help", argv[i]) == 0) {
      printf("PRCHAT Client & Server\n--tracker-only only start the tracker\n");
      return 0;
    }
  }

  net comms;
  comms.starttracker();
  if (!trackeronly) {
    tui term;
    term.startterminal();
  }
  signal(SIGINT, intHandler);
  // wait indefinitely until ended
  while (tasks != 0 || end == false) usleep(1000);
  return 0;
}