
#include "pch.h"
#include "Animation.h"
#include "Manager_game.h"

#include <SDL_image.h>

Animation::Animation() :position(0, 0) {
	timer.set_one_shot(false);
	timer.set_on_timeout(
		[&]() {
			idx_frame++;
			if (idx_frame >= frame_list.size()) {
				idx_frame = is_loop ? 0 : frame_list.size()-1;
				if (!is_loop && on_finished) {
					on_finished();
				}
			}
		}
	);
}

Animation::~Animation() {

}

void Animation::reset() {
	timer.restart();
	idx_frame = 0;
}

void Animation::set_ancher_mode(AncherMode mode) {
	ancher_mode = mode;
}

void Animation::set_position(const Vector2D& pos) {
	position = pos;
}

void Animation::set_loop(bool flag) {
	is_loop = flag;
}

void Animation::set_interval(float val) {
	timer.set_wait_time(val);
}

void Animation::set_on_finished(std::function<void()> on_finished) {
	this->on_finished = on_finished;
}

void Animation::add_frame(SDL_Texture* img, int num_h) {
	int w ;
	int h ;
	SDL_QueryTexture(img, nullptr, nullptr, &w, &h);
	int width_frame = w / num_h;

	for (int i = 0; i < num_h; i++) {
		SDL_Rect rect_src;
		rect_src.x = i * width_frame;
		rect_src.y = 0;

		rect_src.w = width_frame;
		rect_src.h = h;

		frame_list.emplace_back(img, rect_src);
	}
}

void Animation::add_frame(Atlas* atlas) {
	for (int i = 0; i < atlas->get_size(); i++) {

		SDL_Texture* img = atlas->get_image(i);
		int w;
		int h;
		SDL_QueryTexture(img, nullptr, nullptr, &w, &h);

		SDL_Rect rect_src;
		rect_src.x = 0;
		rect_src.y = 0;

		rect_src.w = w;
		rect_src.h = h;

		frame_list.emplace_back(img, rect_src);
	}
}

void Animation::on_update(float delta) {
	timer.on_update(delta);
}

void Animation::on_render() {
	const Frame& frame = frame_list[idx_frame];

	SDL_Rect rect_dst;
	rect_dst.x = (int)position.x - frame.rect_src.w / 2;
	rect_dst.y = (ancher_mode == AncherMode::Centerd) ? (int)position.y - frame.rect_src.h / 2 : (int)position.y- frame.rect_src.h;
	rect_dst.w = frame.rect_src.w;
	rect_dst.h = frame.rect_src.h;

	SDL_Renderer* renderer=Manager_game::instance()->get_renderer();
	
	SDL_RenderCopy(renderer, frame.img, &frame.rect_src, &rect_dst);

}
