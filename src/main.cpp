#include <vector>
#include <string>
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

int main() {
  setlocale(LC_ALL, "");

  net comms;
  comms.starttracker();
  tui term;
  term.startterminal();

  signal(SIGINT, intHandler);
  // wait indefinitely until ended
  while (tasks != 0 || end == false) usleep(1000);
  return 0;
}