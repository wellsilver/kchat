#include <vector>
#include <string>

#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

std::string composing;

bool end = false; // if its time to exit
unsigned int tasks = 0; // running tasks

WINDOW *win;

void *render(void *) {
  tasks++;
  win = initscr();
  noecho();

  clear();
  refresh();

  while (end == false) {
    wchar_t c = getwchar();
    if (c != BUTTON_SHIFT && c != 'q') {

    } else if (c == 'q') end = true;
    
    refresh();
  }

  endwin();
  tasks--;
  return 0;
}

void intHandler(int dummy) {
  end = true;
}

int main() {
  pthread_t rd;
  pthread_create(&rd, 0, render, 0);

  signal(SIGINT, intHandler);
  // wait indefinitely until ended
  while (tasks != 0 || end == false) sleep(0);
  return 0;
}