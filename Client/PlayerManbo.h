#pragma once
#include "Player.h"
class PlayerManbo :
    public Player
{
public:
    PlayerManbo();
    ~PlayerManbo();

    void on_input(const SDL_Event* event)override;

    void on_update(double delta_time)override;

    void on_draw()override;

private:
};

