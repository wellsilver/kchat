#include <vector>
#include <string>

#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

/* net.cpp */
class net;

// The string that the user is typing
std::string composing;

bool end = false; // if its time to exit
unsigned int tasks = 0; // running tasks

WINDOW *win;

void renderchat() {
  clear();
  
  curs_set(2);

  unsigned int x,y;
  getmaxyx(win, y, x);

  attron(WA_BOLD);
  mvprintw(y-1,0, "Chat | Tab for menu"); // left side of bottom bar
  std::string str = std::to_string(0) + " (known) listeners | " + std::to_string(0) + " Peers";
  mvprintw(y-1, x-str.length(), str.c_str()); // debian preinstalled isocant get the width of a formatted string :sob:
  attroff(WA_BOLD);
  
  unsigned int dist = 2;
  // render chat
  mvprintw(y-dist, 0, "OKAY > %s", composing.c_str());
  
  refresh();
}

void rendermenu() {
  clear();

  curs_set(0);

  unsigned int x,y;
  getmaxyx(win, y, x);

  attron(WA_BOLD);
  mvprintw(y-1,0, "Menu | Q to exit");
  std::string str = std::to_string(0) + " Peers";
  mvprintw(y-1, x-str.length(), str.c_str()); // cant get the width of a formatted string :sob:
  attroff(WA_BOLD);
  
  refresh();
}

void *handlescr(void *) {
  tasks++;
  win = initscr();
  noecho();
  keypad(win, TRUE);
  nodelay(win, TRUE);
  cbreak();
  timeout(0);

  uint mode = 1;
  wint_t wc;

  while (end == false) {
    get_wch(&wc);

    // if tab pressed switch menus
    if (wc == '\t' && mode == 1) {mode = 2;continue;}
    if (wc == '\t' && mode == 2) {mode = 1;continue;}

    // record written words
    if (wc >= 'A' && wc <= 'z' && mode == 2) composing += wc;
    if (wc == ' ' && mode == 2) composing += wc;
    // backspace
    if (wc == KEY_BACKSPACE && mode == 2 && composing.length() > 0) composing.pop_back();

    // exit
    if (wc == 'q' && mode == 1) {end = true;continue;};
    
    if (mode == 1) rendermenu();
    if (mode == 2) renderchat();

    usleep(10000); // at the end so continue will refresh everything
  } 

  endwin();
  tasks--;
  return 0;
}

void intHandler(int dummy) {
  end = true;
}

int main() {
  setlocale(LC_ALL, "");
  pthread_t rd;
  pthread_create(&rd, 0, handlescr, 0);

  signal(SIGINT, intHandler);
  // wait indefinitely until ended
  while (tasks != 0 || end == false) usleep(1000);
  return 0;
}