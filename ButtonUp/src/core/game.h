#ifndef GAME_H
#define GAME_H
#include "buttonstack.h"
#include "observer.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
/**
 * @brief The Game class, the main class containing the game logic with 9 button
 * stacks. It is also observable, notifying any observer of state changes.
 */
class Game : public Observable {

public:
  /**
   * @brief N_STACKS, the number of button stacks in the game.
   */
  static const int N_STACKS = 9;
  /**
   * @brief The GameState enum, an enumeration of possible states. The "begin"
   * value is used when the first player is picked, the red/black values define
   * a player's turn and the game over value signals the end of the game.
   */
  enum GameState { BEGIN = 0, RED, BLACK, GAME_OVER };
  /**
   * @brief Game, the game constructor, it reserves the memory necessary for the
   * stacks and shuffles the buttons.
   */
  Game();
  /**
   * @brief getState, the state getter.
   * @return the current game state.
   */
  constexpr GameState getState() const { return m_state; }
  /**
   * @brief setState, the state setter.
   * @param gs, the new state.
   */
  constexpr void setState(GameState gs) { m_state = gs; }
  /**
   * @brief moveStack, the main game logic. It manages the two possibilites of
   * dividing the buttons among the stacks when there are fewer buttons than
   * non-empty stacks and when there are more buttons than stacks. Since any
   * move has to go clockwise, only the starting position is necessary.
   * @param srcPos, the position from which the move is made.
   */
  void moveStack(int srcPos, bool testMode = false);
  /**
   * @brief isGameOver, checks if the game is over. Since playing a move is
   * mandatory and the number of buttons is constant (9), the game is always
   * over after 8 turns.
   * @return true if the game is over and false otherwise.
   */
  constexpr bool isGameOver() { return m_turns == 8; };
  /**
   * @brief reset, resets the game attributes and states: the state returns to
   * "begin", the stacks are emptied, the round scores are set to zero. Note
   * that the victory points are not changed since they are used across rounds.
   */
  constexpr void reset(bool testMode = false) {
      if(m_state != GameState::GAME_OVER && !testMode){
          throw std::runtime_error("The game can only be reset once it's over.");
      }
    m_state = GameState::BEGIN;
    m_turns = 0;
    m_roundResultBlack = 0;
    m_roundResultRed = 0;
    m_roundResult = 0;
    for (size_t i = 0; i < N_STACKS; i++) {
      m_stacks[i].reset();
    }
  }
  /**
   * @brief shuffleStacks, shuffles the <buttons> attribute and divides the
   * buttons among the stacks during the placement phase.
   * @param testMode, in test mode, the stacks are not shuffled which makes it
   * easier during testing.
   */
  void shuffleStacks(bool testMode = false);
  /**
   * @brief nonEmptyStacks, collects the indices of the non-empty stacks. It
   * goes over each stack and checks if they're empty.
   * @param startIdx, the starting index to collect the empyt stacks' indices.
   * This parameter is important because it makes the indices already sorted for
   * when the buttons are divided later on.
   * @return a vector of non-empty stacks positions.
   */
  std::vector<int> nonEmptyStacks(int startIdx);
  /**
   * @brief operator [], a subscript operator overlaod to access a specific
   * stack directly.
   * @param idx, the index to get the data at.
   * @return the button stack at the given index.
   */
  ButtonStack &operator[](int idx);
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

  /**
   * @brief notifyAll, notifies all the observers in the observers' list.
   */
  void notifyAll() override;
  /**
   * @brief computeRoundPoints, computes each players' points at the end of the
   * round and updates the victory points.
   */
  constexpr void computeRoundPoints() {
    // avoid using nonEmpty method because vectors make constexpr stuff
    // difficult
    int idx = 0;
    for (size_t i = 0; i < N_STACKS; ++i) {
      if (!m_stacks[i].isEmpty()) {
        idx = i;
        break;
      }
    }
    for (size_t i = 0; i < ButtonStack::N_BUTTONS; ++i) {
      if (m_stacks[idx][i] == Button::RED) {
        m_roundResultRed += i + 1;
      }
      if (m_stacks[idx][i] == Button::BLACK) {
        m_roundResultBlack += i + 1;
      }
    }
    // if result is >= 0, red won else black won
    // will be useful to display points later on
    m_roundResult = m_roundResultRed - m_roundResultBlack;
    if (m_roundResult >= 0) {
      m_redVictoryPoints += m_roundResult;
    } else {
      m_blackVictoryPoints += -(m_roundResult);
    }
  };
  /**
   * @brief turns, the number of turns getter.
   * @return the current number of turns that already have been played.
   */
  constexpr int turns() const { return m_turns; };
  /**
   * @brief redRoundResult, the getter for the round result of the red player.
   * @return the current round score of the red player.
   */
  constexpr int redRoundResult() const { return m_roundResultRed; };
  /**
   * @brief blackRoundResult, the getter for the round result of the black
   * player.
   * @return the current round score of the black player.
   */
  constexpr int blackRoundResult() const { return m_roundResultBlack; };
  /**
   * @brief redVictoryPoints, the getter for the victory points of the red
   * player.
   * @return the current victory points of the red player.
   */
  constexpr int redVictoryPoints() const { return m_redVictoryPoints; };
  /**
   * @brief blackVictoryPoints, the getter for the victory points of the black
   * player.
   * @return the current victory points of the black player.
   */
  constexpr int blackVictoryPoints() const { return m_blackVictoryPoints; };

private:
  /**
   * @brief observers, the list of observers of this observable.
   */
  std::vector<std::reference_wrapper<Observer>> observers;
  /**
   * @brief m_stacks, the vector of button stacks.
   */
  std::vector<ButtonStack> m_stacks;
  /**
   * @brief m_state, the state of the game.
   */
  GameState m_state = GameState::BEGIN;
  /**
   * @brief m_redVictoryPoints, the red player's victory points.
   */
  int m_redVictoryPoints = 0;
  /**
   * @brief m_blackVictoryPoints, the black player's victory points.
   */
  int m_blackVictoryPoints = 0;
  /**
   * @brief m_turns, the turns counter.
   */
  int m_turns = 0;
  /**
   * @brief m_roundResultRed, the red player's round result storage.
   */
  int m_roundResultRed = 0;
  /**
   * @brief m_roundResultBlack, the black player's round result storage.
   */
  int m_roundResultBlack = 0;
  /**
   * @brief m_roundResult, the difference of the players' points, to be added to
   * the victory points.
   */
  int m_roundResult = 0;
  /**
   * @brief buttons, the buttons of the game which will be shuffled and pushed
   * into the stacks.
   */
  std::vector<Button> buttons{Button::WHITE, Button::WHITE, Button::WHITE,
                              Button::RED,   Button::RED,   Button::RED,
                              Button::BLACK, Button::BLACK, Button::BLACK};
};

#endif // GAME_H
