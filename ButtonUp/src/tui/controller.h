#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "view.h"

class Controller {
private:
  Game &m_game;
  View &m_view;

public:
  Controller(Game &, View &);
  void cleanupInput(std::string &);
  void parseStarter();
  void parseCommand();
  void start();
  void results();
  void replay();
  void exit();
};

#endif // CONTROLLER_H
