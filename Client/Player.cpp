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
    timer.pause();

    setPos(route.get_cur_pos());
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
        switch (event->key.keysym.sym) {
        case SDLK_UP:
            //is_move_up = false;
            break;
        case SDLK_DOWN:
            //is_move_down = false;
            break;
        case SDLK_LEFT:
            //is_move_left = false;
            break;
        case SDLK_RIGHT:
            //is_move_right = false;
            break;
        }
        if (event->key.keysym.scancode == SDL_SCANCODE_LSHIFT || event->key.keysym.scancode==SDL_SCANCODE_RSHIFT)
            is_down_shift = true;
        break;
    case SDL_KEYUP:
        switch (event->key.keysym.sym) {
        case SDLK_UP:
            is_move_up = true;
            break;
        case SDLK_DOWN:
            is_move_down = true;
            break;
        case SDLK_LEFT:
            is_move_left = true;
            break;
        case SDLK_RIGHT:
            is_move_right = true;
            break;
        }
        if (event->key.keysym.scancode == SDL_SCANCODE_LSHIFT || event->key.keysym.scancode == SDL_SCANCODE_RSHIFT)
            is_down_shift = false;
        if (event->key.keysym.scancode >= 4 && event->key.keysym.scancode <= 57) {
            if (event->key.keysym.scancode == SDL_SCANCODE_CAPSLOCK)//Ëø¶¨´óÐ¡
                is_down_capslock = !is_down_capslock;
            key_code = event->key.keysym.scancode;
            if (is_down_shift || is_down_capslock)key_code += 56;
            std::cout <<"press:" << "(" << get_press_key_code() << ")" << std::endl;
            key_code_pool.push(get_press_key_code());
            key_code = -1;
        }
        else {
            key_code = -1;
        }
        break;
    default:
        key_code = -1;
    }
    //std::cout << key_code << std::endl;
}

void Player::on_update(double delta_time)
{
    timer.on_update(delta_time);
    if (is_can_move) {
        if ((route.get_cur_pos() - pos).length() <= 0.05) {
            pos = route.get_cur_pos();
            route.add_idex();
        }
        dir = route.get_move_dir(pos);
        speed = dir * SPEED;
        pos += speed * delta_time;
    }
    //std::cout << "player:" << get_press_key_code() << std::endl;
    //if (is_move_up) {
    //    setMoveTime(0.8);
    //    dir = { 0,-1 };
    //    is_move_up = false;
    //}
    //if (is_move_down) {
    //    setMoveTime(0.8);
    //    dir = { 0,1 };
    //    is_move_down = false;
    //}
    //if (is_move_left) {
    //    setMoveTime(0.8);
    //    dir = { -1,0 };
    //    is_move_left = false;
    //}
    //if (is_move_right) {
    //    setMoveTime(0.8); 
    //    dir = { 1,0 };
    //    is_move_right = false;
    //}

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

char Player::pressed_key_code()
{
    if (!key_code_pool.empty()) {
        char c = key_code_pool.front();
        key_code_pool.pop();
        return c;
    }
    else return '\0';
}

char Player::get_press_key_code()
{
    return key_value[key_code];
}

bool Player::can_move()
{
    return is_can_move;
}

Vector2D Player::get_move_dir()
{
    return dir;
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
    this->size = size;
}
