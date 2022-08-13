#include "game.h"

Game::Game() {
  m_stacks.reserve(N_STACKS);
  shuffleStacks();
}

void Game::shuffleStacks(bool testMode) {
  if (!testMode) {
    auto rng = std::default_random_engine{};
    std::shuffle(buttons.begin(), buttons.end(), rng);
  }
  if (testMode) {
    buttons = {Button::WHITE, Button::WHITE, Button::WHITE,
               Button::RED,   Button::RED,   Button::RED,
               Button::BLACK, Button::BLACK, Button::BLACK};
  }
  for (size_t i = 0; i < N_STACKS; i++) {
    m_stacks.push_back(ButtonStack());
    m_stacks[i].push(buttons[i]);
  }
}

std::vector<int> Game::nonEmptyStacks(int startIdx) {
  std::vector<int> nonEmptyIndices;
  nonEmptyIndices.reserve(N_STACKS);
  for (size_t i = 0; i < N_STACKS; i++) {
    int idx = (startIdx + i) % N_STACKS;
    if (!m_stacks[idx].isEmpty()) {
      nonEmptyIndices.push_back(idx);
    }
  }
  return nonEmptyIndices;
}

void Game::subscribe(Observer &obs) { observers.push_back(obs); }

void Game::unsubscribe(Observer &obs) {
  for (auto it = observers.begin(); it != observers.end();) {
    if (&(*it).get() == &obs) {
      it = observers.erase(it);
    } else {
      ++it;
    }
  }
}

void Game::notifyAll() {
  for (auto const &o : observers) {
    o.get().update();
  }
}

void Game::moveStack(int srcPos, bool testMode) {
    if(!m_stacks[srcPos].hasWhite() && !testMode){
        throw std::invalid_argument("Button stack does not contain a white button.");
    }
  bool replay = false;
  auto nonEmptyIndices = nonEmptyStacks(srcPos);
  int nButtons = m_stacks[srcPos].nButtons();
  int nStacks = (int)nonEmptyIndices.size() - 1; // -1 because current stack shouldn't be counted
  if (nButtons <= nStacks) {
    for (int i = 0; i < nButtons; i++) {
      // avoid pushing to self, hence +1
      m_stacks[nonEmptyIndices[i + 1]].push(m_stacks[srcPos][i]);
    }
    if (m_stacks[nonEmptyIndices[nButtons]].has2SameButtons()) {
      replay = true;
    }
  } else { // number of buttons is strictly superior to available stacks
    int i = 0;
    while (i < nStacks) { // do the same as above until there's one stack left
      // avoid pushing to self, hence +1
      m_stacks[nonEmptyIndices[i + 1]].push(m_stacks[srcPos][i]);
      i++;
    }
    // dump what's left on the buttons in the last usable stack
    int lastIdx = i;
    while (i < nButtons) {
      m_stacks[nonEmptyIndices[lastIdx]].push(m_stacks[srcPos][i]);
      i++;
    }
  }
  // non-stack operations were used and the current stack was emptied, reset is
  // needed
  m_stacks[srcPos].reset();
  // depends on the state
  m_turns++; // increase turn counter after a successful move
  if (!replay) {
    m_state = (m_state == GameState::RED) ? GameState::BLACK : GameState::RED;
  }
  if (isGameOver()) {
    m_state = GameState::GAME_OVER;
  }
  notifyAll();
}

ButtonStack &Game::operator[](int idx) { return m_stacks.at(idx); }
