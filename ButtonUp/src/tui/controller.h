#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "view.h"
/**
 * @brief The Controller class, provides a controller to link the game and the
 * TUI.
 */
class Controller {
private:
  /**
   * @brief m_game, the game to control.
   */
  Game &m_game;
  /**
   * @brief m_view, the (TUI) view to represent to game.
   */
  View &m_view;

public:
  /**
   * @brief Controller, the controller constructor.
   * @param g, the game to control.
   * @param v, the view to represent the game.
   */
  Controller(Game &g, View &v);
  /**
   * @brief cleanupInput, cleans up the input gotten from the view. It trims the
   * input string and makes it lowercase, in place.
   * @param s, the string to cleanup.
   */
  void cleanupInput(std::string &s);
  /**
   * @brief parseStarter, parses the users' choice for who starts the game, the
   * only two valid answers are "black" or "red".
   */
  void parseStarter();
  /**
   * @brief parseCommand, parses the users command obtained from the view. Valid
   * commands can be used to interact with the game and the view. Invalid
   * commands are ignored and the user is prompted for new input.
   */
  void parseCommand();
  /**
   * @brief start, stars the game proper.
   */
  void start();
  /**
   * @brief results, computes and displays the results of a round.
   */
  void results();
  /**
   * @brief replay, manages the replay phase, after a round is finished.
   */
  void replay();
  /**
   * @brief exit, exits the game.
   */
  void exit();
};

#endif // CONTROLLER_H
