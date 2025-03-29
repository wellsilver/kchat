#ifndef tui_hpp
#define tui_hpp

#include <string>
#include <ncurses.h>

class tui {
private:
  void renderchat(std::string);
  void rendermenu();
  void terminal();
  WINDOW *win;
public:
  void startterminal();
};

#endif