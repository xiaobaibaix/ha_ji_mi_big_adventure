
#include "pch.h"
#include "Animation.h"
#include "Manager_game.h"

#include <SDL_image.h>

Animation::Animation() :position(0, 0) {
	timer.set_one_shot(false);
	timer.set_on_timeout(
		[&]() {
			//std::cout << idx_frame << std::endl;
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

void Animation::on_render(const Vector2D& pos_dst) {
	const Frame& frame = frame_list[idx_frame];

	int w, h;
	SDL_QueryTexture(frame.img, nullptr, nullptr, &w, &h);
	float mulmag = Manager_game::instance()->get_camera()->get_mulMag();

	SDL_Rect dst = { (int)pos_dst.x,(int)pos_dst.y,(int)(w*2/ mulmag),(int)(h*2/ mulmag) };

	SDL_Renderer* renderer=Manager_game::instance()->get_renderer();
	
	SDL_RenderCopy(renderer, frame.img, &frame.rect_src, &dst);

}
