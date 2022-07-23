#include "game.h"

Game::Game() {
  m_stacks.reserve(N_STACKS);
  shuffleStacks();
}

Game::GameState Game::getState() { return m_state; }

void Game::setState(Game::GameState gs) { m_state = gs; }

bool Game::isGameOver() { return m_turns == 7; }

void Game::reset() {
  m_state = GameState::BEGIN;
  m_turns = 0;
  m_roundResult = 0;
  for (size_t i = 0; i < N_STACKS; i++) {
    m_stacks[i].reset();
  }
}

void Game::shuffleStacks() {
  auto rng = std::default_random_engine{};
  std::shuffle(buttons.begin(), buttons.end(), rng);
  for (size_t i = 0; i < N_STACKS; i++) {
    m_stacks.push_back(ButtonStack());
    m_stacks[i].push(buttons[i]);
  }
}

std::vector<int> Game::nonEmptyStacks() {
  std::vector<int> nonEmptyIndices;
  nonEmptyIndices.reserve(N_STACKS);
  for (size_t i = 0; i < N_STACKS; i++) {
    if (!m_stacks[i].isEmpty())
      nonEmptyIndices.push_back(i);
  }
  return nonEmptyIndices;
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

void Game::moveStack(int srcPos) {
  bool replay = false;
  auto nonEmptyIndices = nonEmptyStacks(srcPos);
  int nButtons = m_stacks[srcPos].nButtons();
  int nStacks = (int)nonEmptyIndices.size() - 1;
  if (nButtons <= nStacks) {
    for (int i = 0; i < nButtons; i++) {
      // avoid pushing to self, hence +1
      m_stacks[nonEmptyIndices[i + 1]].push(m_stacks[srcPos][i]);
    }
    if (m_stacks[nButtons - 1].has2SameButtons()) {
      replay = true;
    }
  } else { // number of buttons is strictly superior to available stacks
    int i = 0;
    while (i < nStacks) {
      // avoid pushing to self, hence +1
      m_stacks[nonEmptyIndices[i + 1]].push(m_stacks[srcPos][i]);
      i++;
    }
    // dump what's left on the buttons in the last usable stack
    int lastIdx = i;
    while (i < nButtons) {
      m_stacks[nonEmptyIndices[lastIdx + 1]].push(m_stacks[srcPos][i]);
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

void Game::computeRoundPoints() {
  int idx = nonEmptyStacks()[0];
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
}

ButtonStack &Game::operator[](int idx) { return m_stacks.at(idx); }
