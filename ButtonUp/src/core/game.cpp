#include "game.h"
#include <algorithm>
#include <random>
#include <stdexcept>

// TODO : add Observer/Observable
Game::Game(){
    shuffleStacks();
}

constexpr Game::GameState Game::getState(){
    return m_state;
}

constexpr void Game::setState(Game::GameState gs){
    m_state = gs;
}

constexpr bool Game::isGameOver(){
    return m_turns == 8;
}

constexpr void Game::reset(){
    m_state = GameState::BEGIN;
    m_turns = 0;
    for(size_t i = 0; i < N_STACKS; i++){
        m_stacks[i].reset();
    }
}

void Game::shuffleStacks(){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(buttons.begin(), buttons.end(), g);
    for(size_t i = 0; i < N_STACKS; i++){
        m_stacks[i].push(buttons[i]);
    }
}

std::vector<int> Game::nonEmptyStacks(){
    std::vector<int> nonEmptyIndices;
    nonEmptyIndices.reserve(N_STACKS);
    for(size_t i = 0; i < N_STACKS; i++){
        if(!m_stacks[i].isEmpty())
            nonEmptyIndices.push_back(i);
    }
    return nonEmptyIndices;
}

std::vector<int> Game::nonEmptyStacks(int startIdx){
    std::vector<int> nonEmptyIndices;
    nonEmptyIndices.reserve(N_STACKS);
    for(size_t i = 0; i < N_STACKS; i++){
        int idx = (startIdx + i) % N_STACKS;
        if(!m_stacks[idx].isEmpty()){
            nonEmptyIndices.push_back(idx);
        }
    }
    return nonEmptyIndices;
}


void Game::moveStack(int srcPos){
    // TODO : State management
    auto nonEmptyIndices = nonEmptyStacks(srcPos);
    int nButtons = m_stacks[srcPos].nButtons();
    int nStacks = (int)nonEmptyIndices.size() - 1;
    if(nButtons <= nStacks){
        for(int i = 0; i < nButtons; i++){
            // avoid pushing to self, hence +1
            m_stacks[nonEmptyIndices[i + 1]].push(m_stacks[srcPos][i]);
        }
    }
    else{ // number of buttons is strictly superior to available stacks
        int i = 0;
        while(i < nStacks){
            // avoid pushing to self, hence +1
            m_stacks[nonEmptyIndices[i + 1]].push(m_stacks[srcPos][i]);
            i++;
        }
        // dump what's left on the buttons in the last usable stack
        int lastIdx = i;
        while(i < nButtons){
            m_stacks[nonEmptyIndices[lastIdx + 1]].push(m_stacks[srcPos][i]);
            i++;
        }
    }
    // non-stack operations were used and the current stack was emptied, reset is needed
    m_stacks[srcPos].reset();
    m_turns++; // increase turn counter after a successful move
}
