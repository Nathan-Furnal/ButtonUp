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
  std::string command = m_view.readLine();
  util::trim(command);
  if (command.empty() || command == "" || command == "\n" ||
      command == " ") { // typical bad input
    std::cout << "Invalid command." << std::endl;
    return;
  }
  auto words = util::split(command); // split on space
  std::string cmd = words[0];        // isolate the first command
  util::strtolower(cmd);             // sanitize
  if (cmd == "move") {
    if (words.size() > 1 &&
        util::isint(words[1])) { // check if the second arg is an integer
      int numVal = std::stoi(words[1]);
      if (numVal > 0 && numVal <= 9) {
        if (m_game[numVal - 1].hasWhite()) {
          m_game.moveStack(numVal - 1);
        } else {
          std::cout << "Only stacks with white buttons can be moved."
                    << std::endl;
        }
      } else {
        std::cout << "Numbers must be in the range 1 to 9." << std::endl;
      }
    } else {
      std::cout << "Not a valid number." << std::endl;
    }
  } else if (cmd == "show") {
    m_view.displayBoard();
  } else if (cmd == "help") {
    std::cout << "Help is on the way." << std::endl;
  } else {
    std::cout << "Not a known command." << std::endl;
  }
}

void Controller::start() {
  m_view.displayBanner();
  parseStarter();
  m_view.displayBoard();
  std::cin.ignore();
  while (m_game.getState() != Game::GAME_OVER) {
    parseCommand();
  }
}
