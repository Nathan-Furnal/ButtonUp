#ifndef GAME_H
#define GAME_H
#include "buttonstack.h"
#include "observer.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

class Game : public Observable {

public:
  static const int N_STACKS = 9;
  enum GameState { BEGIN = 0, RED, BLACK, GAME_OVER };
  Game();
  GameState getState();
  void setState(GameState gs);
  void moveStack(int srcPos);
  bool isGameOver();
  void reset();
  void shuffleStacks();
  std::vector<int> nonEmptyStacks();
  std::vector<int> nonEmptyStacks(int startIdx);
  ButtonStack &operator[](int);
  int turns();
  /**
   * @brief Subscribes the observer to the observers list.
   * @param obs the observer to add to the list.
   */
  void subscribe(Observer &obs) override;

  /**
   * @brief Removes an observer from the observers list.
   * @param obs the observer to remove from the list.
   */
  void unsubscribe(Observer &obs) override;

  void notifyAll() override;

  void computeRoundPoints();
  int redRoundResult();
  int blackRoundResult();
  int redVictoryPoints();
  int blackVictoryPoints();

private:
  std::vector<std::reference_wrapper<Observer>> observers;
  std::vector<ButtonStack> m_stacks;
  GameState m_state = GameState::BEGIN;
  int m_redVictoryPoints = 0;
  int m_blackVictoryPoints = 0;
  int m_turns = 0;
  int m_roundResultRed = 0;
  int m_roundResultBlack = 0;
  int m_roundResult = 0;
  std::vector<Button> buttons{Button::WHITE, Button::WHITE, Button::WHITE,
                              Button::RED,   Button::RED,   Button::RED,
                              Button::BLACK, Button::BLACK, Button::BLACK};
};

#endif // GAME_H
