#pragma once
#include "Player.h"
class PlayerHajimi :
    public Player
{
public:
    PlayerHajimi(PlayerId id);
    ~PlayerHajimi();

    void on_input(const SDL_Event* event)override;

    void on_update(double delta_time)override;

    void on_draw()override;

private:
};

