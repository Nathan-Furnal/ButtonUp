#include "view.h"
#include <limits>
View::View(Game &g) : m_game(g) { g.subscribe(*this); }

void View::displayBanner() {
  std::cout << "-----------------------" << std::endl;
  std::cout << "  Welcome to ButtonUp! " << std::endl;
  std::cout << "-----------------------" << std::endl;
  std::cout << "\n";
  std::cout << "In this game, you're expected to stack buttons until there is "
               "only one button stack left."
            << std::endl;
  std::cout << "At each turn, a player can pick a stack "
               "which will move from left to right."
            << std::endl;
  std::cout << "But you can only pick a stack containing a white button."
            << std::endl;
  std::cout << "The goal is to have your buttons at the highest of the "
               "remaining stack."
            << std::endl;
  std::cout << "\n";
  std::cout << "***------Let's start!------***" << std::endl;
}

std::string View::displayButton(Button b) {
  std::string black{"\u001b[90;1m\u25a0\u25a0\u25a0\u25a0\u25a0\u25a0\033[0m"};
  std::string white{"\u001b[97;1m\u25a1\u25a1\u25a1\u25a1\u25a1\u25a1\033[0m"};
  std::string red{"\033[31;1m\u25a0\u25a0\u25a0\u25a0\u25a0\u25a0\033[0m"};
  switch (b) {
  case Button::WHITE:
    return white;
    break;
  case Button::BLACK:
    return black;
    break;
  case Button::RED:
    return red;
    break;
  case Button::EMPTY:
    return "      ";
    break;
  default:
    return "";
    break;
  }
}

void View::displayInfo() {
  std::string state;
  switch (m_game.getState()) {
  case Game::BEGIN:
    state = "Player pick";
    break;
  case Game::RED:
    state = "Red player's turn";
    break;
  case Game::BLACK:
    state = "Black player's turn";
    break;
  case Game::GAME_OVER:
    state = "Game over";
    break;
  }
  std::cout << "Game state: " << state << "      "
            << "Current turn: " << m_game.turns() << "\n";
}

void View::displayBoard() {
  displayInfo();
  std::cout << std::endl;
  for (size_t i = 0; i < ButtonStack::N_BUTTONS; i++) {
    std::cout << ButtonStack::N_BUTTONS - i << "| ";
    for (size_t j = 0; j < Game::N_STACKS; j++) {
      std::cout << displayButton(m_game[j][ButtonStack::N_BUTTONS - 1 - i]);
    }
    std::cout << std::endl;
  }
  std::cout << "----------------------------------------------------------"
            << std::endl;
  for (size_t i = 0; i < Game::N_STACKS; i++) {
    std::cout << "     " << i + 1;
  }
  std::cout << std::endl;
}

std::string View::pickStarter() {
  std::cout << "In the first round, it's up to the players to decide who "
               "starts first."
            << std::endl;
  std::cout << "In the following rounds, the player who lost the previous "
               "round picks the starter."
            << std::endl;
  std::cout << "Pick a starter player: (red/black) " << std::endl;
  std::string input;
  std::cin >> input;
  return input;
}

std::string View::readLine() {
  std::string line;
  // Skips a line all the time, not useful for constant I/O with users
  // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::getline(std::cin, line);
  return line;
}
void View::update() { displayBoard(); }
