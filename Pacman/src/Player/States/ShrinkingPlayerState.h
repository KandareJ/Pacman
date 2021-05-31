#ifndef SHRINKING_PLAYER_STATE
#define SHRINKING_PLAYER_STATE

#include "PlayerState.h"
#include "../../Graphics/Draw.h"

class ShrinkingPlayerState : public PlayerState {
public:
    ShrinkingPlayerState(HumanPlayer* c);
    bool update();
    void draw(int x, int y, int dir, int r, int g, int b);
    bool isBig();
    void die();

private:
    int counter;
    bool shrinking;
};

#endif