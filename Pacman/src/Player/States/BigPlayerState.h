#ifndef BIG_PLAYER_STATE
#define BIG_PLAYER_STATE

#include "PlayerState.h"
#include "../../Graphics/Draw.h"

class BigPlayerState : public PlayerState {
public:
    BigPlayerState(HumanPlayer* c);
    bool update();
    void draw(int x, int y, int dir, int r, int g, int b);
	bool isBig();
    void powerUp();
    void die();

private:
    int counter;
};

#endif