#include "pch.h"
#include "Player.h"
#include "Manager_game.h"
#include "Manager_resource.h"
#include "Keys.h"
Player::Player(Player::PlayerId id):id(id)
{
    timer.set_one_shot(true);
    timer.set_on_timeout(
        [&]() {
            is_can_move = false;
        }
    );

    setPos(route.get_cur());
    size = { 96,96 };
}

Player::~Player()
{
}

void Player::on_input(const SDL_Event* event)
{
    if (id == PlayerId::Other)return;
    switch (event->type) {
    case SDL_KEYDOWN:
        if (event->key.keysym.scancode == SDL_SCANCODE_LSHIFT || event->key.keysym.scancode==SDL_SCANCODE_RSHIFT)
            is_down_shift = true;
        break;
    case SDL_KEYUP:
        if (event->key.keysym.scancode == SDL_SCANCODE_LSHIFT || event->key.keysym.scancode == SDL_SCANCODE_RSHIFT)
            is_down_shift = false;
        if (event->key.keysym.scancode >= 4 && event->key.keysym.scancode <= 57) {
            if (event->key.keysym.scancode == SDL_SCANCODE_CAPSLOCK)//锁定大小
                is_down_capslock = !is_down_capslock;
            key_code = event->key.keysym.scancode;
            if (is_down_shift || is_down_capslock)key_code += 56;
            //std::cout << "输入:" << "( " << get_press_key_code() << " )"<< std::endl;
        }
        break;
    default:
        key_code = -1;
    }
    //std::cout << key_code << std::endl;
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
    Vector2D delta = {size.x/2,size.y/2};
    if (animation_cur)animation_cur->on_render(Vector2D(pos- delta - camera_ps)/ mulmag);
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

char Player::get_press_key_code()
{
    if (key_code == -1)return '\0';
    return key_value[key_code];
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

const Vector2D& Player::get_size() const
{
    return size;
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

void Player::set_size(const Vector2D& size)
{

}
