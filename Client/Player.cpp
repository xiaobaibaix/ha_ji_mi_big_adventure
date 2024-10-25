#include "pch.h"
#include "Player.h"
#include "Manager_game.h"
#include "Manager_resource.h"

Player::Player(Player::PlayerId id):id(id)
{
    timer.set_one_shot(true);
    timer.set_on_timeout(
        [&]() {
            is_can_move = false;
        }
    );
}

Player::~Player()
{
}

void Player::on_input(const SDL_Event* event)
{
    switch (event->type) {
    case SDL_KEYDOWN:
        if (event->key.keysym.sym>=5&& event->key.keysym.sym<=59) {
            key_code = event->key.keysym.sym;
        }
        else {

        }
        break;
    }
}

void Player::on_update(double delta_time)
{

    if (is_can_move) {
        auto dir = route.get_move_dir(pos);
        if (dir.x == 0 && dir.y == 0) {
            route.add_idex();
            dir = route.get_move_dir(pos);
        }
        speed = dir * SPEED;
        pos += speed * delta_time;
    }
    status_machine.on_update(delta_time);

    if (animation_cur) {
        animation_cur->on_update(delta_time);
        animation_cur->set_position(pos);
    }


}

void Player::on_draw()
{
    Vector2D camera_ps=Manager_game::instance()->get_camera()->get_pos();
    float mulmag = Manager_game::instance()->get_camera()->get_mulMag();

    if (animation_cur)animation_cur->on_render(Vector2D(pos- camera_ps)/ mulmag);
}

Player::PlayerId Player::getId()
{
    return id;
}

void Player::setSpeed(const Vector2D& speed)
{
    this->speed = speed;
}

void Player::setPos(const Vector2D& pos)
{
    this->pos = pos;
}

Vector2D Player::getSpeed()
{
    return speed;
}

Vector2D Player::getPosition()
{
    return pos;
}

int Player::get_press_key_code()
{
    return key_code;
}

bool Player::can_move()
{
    return is_can_move;
}

Vector2D Player::get_move_dir()
{
    return Vector2D();
}

StatusMachine* Player::get_statusMachine()
{
    return &status_machine;
}

void Player::setMoveTime(float time)
{
    timer.set_wait_time(time);
    timer.restart();
    is_can_move = true;
}

void Player::set_animation(std::string id)
{
    animation_cur= animation_pool.find(id)->second;
    animation_cur->reset();
}
