#ifndef VIEW_H
#define VIEW_H
#include "game.h"
#include <iostream>
#include <string>
/**
 * @brief The View class, provides a terminal view for the ButtonUp game.
 */
class View : public Observer {
private:
  /**
   * @brief m_game, a game reference which the view will represents.
   */
  Game &m_game;

public:
  /**
   * @brief View, the view constructor.
   * @param g, the game that the view will represent.
   */
  View(Game &g);
  /**
   * @brief displayBanner, displays the game banner with a presentation and a
   * short explanation about the game.
   */
  void displayBanner();
  /**
   * @brief displayButton, displays the button passed as parameter. Each button
   * value gets a unicode representation.
   * @param b, the button to represents.
   * @return a string with the button representation.
   */
  std::string displayButton(Button b);
  /**
   * @brief displayBoard, displays the game board, which is a 9x9 grid of
   * buttons.
   */
  void displayBoard();
  /**
   * @brief pickStarter, asks the users to pick the player to go first
   * (red/black).
   * @return a string with the user's choice.
   */
  std::string pickStarter();
  /**
   * @brief readLine, reads a line from standard input.
   * @return the string read from stdin.
   */
  std::string readLine();
  /**
   * @brief update - see Observer (observer.h).
   */
  void update() override;
  /**
   * @brief displayInfo, displays information about the game, such as the
   * current state, turn counter, etc.
   */
  void displayInfo();
  /**
   * @brief displayResult, displays the result of the current round.
   */
  void displayResult();
  /**
   * @brief displayHelp, displays the help menu .
   */
  void displayHelp();
  /**
   * @brief displayPoints, display more details about the points and victory of
   * the game.
   */
  void displayPoints();
};

#endif // VIEW_H
