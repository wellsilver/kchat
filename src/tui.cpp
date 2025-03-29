#include "tui.hpp"

#include <string>
#include <thread>

#include <unistd.h>
#include <ncurses.h>

extern bool end; // If the program is running or not, main.cpp
extern unsigned int tasks; // How many tasks are running

void tui::renderchat(std::string composing) {
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

void tui::rendermenu() {
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

void tui::terminal() {
  tasks++;
  win = initscr();
  noecho();
  keypad(win, TRUE);
  nodelay(win, TRUE);
  cbreak();
  timeout(0);

  uint mode = 1;
  wint_t wc;
  std::string composing = "";

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
    if (mode == 2) renderchat(composing);

    usleep(10000); // at the end so continue will refresh everything
  } 

  endwin();
  tasks--;
}

void tui::startterminal() {
  std::thread(&tui::terminal, this).detach();
}