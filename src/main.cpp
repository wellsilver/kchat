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

void renderchat() {
  clear();
  refresh();
}

void rendermenu() {
  clear();
  refresh();
}

void *handlescr(void *) {
  tasks++;
  win = initscr();
  noecho();
  keypad(win, TRUE);
  nodelay(win, TRUE);

  rendermenu();
  uint mode = 1;
  wchar_t wc;

  while (end == false) {
    usleep(10000);
    wc = wgetch(win);
    if (wc == ERR) continue; // do nothing

    // if tab pressed switch menus
    if (wc == '\t' && mode == 1) mode = 2;
    else if (mode == 2) mode = 1;

    if (mode == 1) rendermenu();
    else if (mode == 2) renderchat();
  }

  endwin();
  tasks--;
  return 0;
}

void intHandler(int dummy) {
  end = true;
}

void resizeHandler(int dummy) {
  refresh();
}

int main() {
  pthread_t rd;
  pthread_create(&rd, 0, handlescr, 0);

  signal(SIGINT, intHandler);
  signal(SIGWINCH, resizeHandler);
  // wait indefinitely until ended
  while (tasks != 0 || end == false) usleep(1000);
  return 0;
}