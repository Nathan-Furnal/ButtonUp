#ifndef GAME_H
#define GAME_H
#include <vector>
#include "buttonstack.h"

class Game {

public:
    static const int N_STACKS = 9;
    enum GameState{
        BEGIN = 0,
        RED,
        BLACK,
        GAME_OVER
    };
    Game();
    constexpr GameState getState();
    constexpr void setState(GameState gs);
    void moveStack(int srcPos);
    constexpr bool isGameOver();
    constexpr void reset();
    void shuffleStacks();
    std::vector<int> nonEmptyStacks();
    std::vector<int> nonEmptyStacks(int startIdx);

private:
    std::vector<ButtonStack> m_stacks;
    GameState m_state = GameState::BEGIN;
    int m_redVictoryPoints = 0;
    int m_blackVictoryPoints = 0;
    int m_turns = 0;
    std::array<Button, N_STACKS> buttons {Button::WHITE, Button::WHITE, Button::WHITE,
                        Button::RED, Button::RED, Button::RED,
                        Button::BLACK, Button::BLACK, Button::BLACK};
};

#endif // GAME_H
