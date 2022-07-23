#ifndef VIEW_H
#define VIEW_H
#include "game.h"
#include <iostream>
#include <string>

class View : public Observer {
private:
  Game m_game;

public:
  View(Game &);
  std::string parseCommand(std::string);
  void displayBanner();
  std::string displayButton(Button b);
  void displayBoard();
  std::string pickStarter();
  std::string readLine();
  void update() override;
};

#endif // VIEW_H
