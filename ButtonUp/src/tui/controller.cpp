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
    m_view.displayHelp();
  } else if (cmd == "quit" || cmd == "exit") {
    exit();
  } else {
    std::cout << "Not a known command." << std::endl;
  }
}

void Controller::results() {
  m_game.computeRoundPoints();
  m_view.displayResult();
  if (m_game.redVictoryPoints() >= 15 &&
      m_game.redVictoryPoints() > m_game.blackVictoryPoints()) {
    std::cout << "The red player has reached at least 15 victory points and "
                 "won the game!\n";
  } else if (m_game.blackVictoryPoints() >= 15 &&
             m_game.blackVictoryPoints() > m_game.redVictoryPoints()) {
    std::cout << "The black player has reached at least 15 victory points and "
                 "won the game!\n";
  } else {
    std::cout << "Neither player has reached the victory points total or beat "
                 "the other player, fancy a "
                 "rematch?\n";
  }
  std::cout << std::endl;
}

void Controller::replay() {
  bool invalid = true;
  while (invalid) {
    std::cout << "Would you like to play again? yes or no (y/n)" << std::endl;
    std::string answer = m_view.readLine();
    cleanupInput(answer);
    if (answer == "yes" || answer == "y") {
      m_game.reset();
      m_game.shuffleStacks();
      invalid = false;

    } else if (answer == "no" || answer == "n") {
      invalid = false;
      exit();
    } else {
      std::cout << "Not a known command. Please answer yes or no (y/n).\n";
    }
  }
}

void Controller::exit() { std::exit(EXIT_SUCCESS); }

void Controller::start() {
  m_view.displayBanner();
  while (true) {
    parseStarter();
    m_view.displayBoard();
    std::cin.ignore();
    while (m_game.getState() != Game::GAME_OVER) {
      parseCommand();
    }
    results();
    replay();
  }
}
