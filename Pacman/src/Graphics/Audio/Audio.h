#ifndef AUDIO_H
#define AUDIO_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Audio {
public:
    static Audio* instance();
    void death();
    void eatFruit();
    void eatGhost();
    void powerUp();
    void endPowerUp();
    void menuMove();
    void menuSelect();
protected:
    Audio();
    ~Audio();
private:
    static Audio* _instance;
    ALLEGRO_SAMPLE* deathSound;
    ALLEGRO_SAMPLE* eatGhostSound;
    ALLEGRO_SAMPLE* eatFruitSound;
    ALLEGRO_SAMPLE* powerUpSound;
    ALLEGRO_SAMPLE* endPowerUpSound;
    ALLEGRO_SAMPLE* menuMoveSound;
    ALLEGRO_SAMPLE* menuSelectSound;
};

#endif