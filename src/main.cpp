#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>

int main() {
  WINDOW *win = initscr();
  noecho();

  refresh();

  getch();


  sleep(1);
  endwin();
}