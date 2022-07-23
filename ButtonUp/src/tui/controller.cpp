#include "controller.h"
#include "util.h"

Controller::Controller(Game &g, View &v) : m_game(g), m_view(v) {}

void Controller::cleanupInput(std::string &str) {
  util::trim(str);
  util::strtolower(str);
}

void Controller::parseStarter() {
  bool invalid = true;
  while (invalid) {
    std::string starter = m_view.pickStarter();
    cleanupInput(starter);
    if (starter == "red") {
      m_game.setState(Game::RED);
      invalid = false;
    }
    if (starter == "black") {
      m_game.setState(Game::BLACK);
      invalid = false;
    }
  }
}

void Controller::parseCommand() {
  bool invalid = true;
  while (invalid) {
    std::string command = m_view.readLine();
    auto words = util::split(command);
    std::string cmd = words[0];
    util::strtolower(cmd);
    if (cmd == "move") {
      if (util::isint(words[1])) {
        int numVal = std::stoi(words[1]);
        if (numVal > 0 && numVal <= 9) {
          m_game.moveStack(numVal - 1);
          invalid = false;
        }
      } else {
        std::cout << "Not a valid number." << std::endl;
      }
    } else if (cmd == "show") {
      m_view.displayBoard();
      invalid = false;
    } else if (cmd == "help") {
      std::cout << "Help is on the way" << std::endl;
      invalid = false;
    } else {
      std::cout << "Not a known command." << std::endl;
    }
  }
}

void Controller::start() {
  m_view.displayBanner();
  parseStarter();
  m_view.displayBoard();
  while (m_game.getState() != Game::GAME_OVER) {
    parseCommand();
  }
}
