#include "pch.h"
#include "Sentence.h"
#include "Manager_resource.h"
#include "Manager_game.h"

Sentence::Sentence():pos(0,0)
{
	font = TTF_OpenFont(Manager_resource::instance()->find_font_path("font").c_str(), FONT_SIZE);
}

Sentence::~Sentence()
{
}

void Sentence::generate_face()
{
    auto* renderer=Manager_game::instance()->get_renderer();
    // 分别渲染每个字符
    int w, h;
    for (int i = 0; i < str->length(); ++i) {
        std::string charText = str->substr(i, 1);
        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, charText.c_str(), b_color);
        if (!surface) {
            std::cout << "生成表面失败！" << std::endl;
            return;
        }
        w = surface->w, h = surface->h;
        this->w += w;
        tex_pool[i] = {SDL_CreateTextureFromSurface(renderer, surface), { (i-1<0)?0:tex_pool[i-1].rect_src.x+ tex_pool[i - 1].rect_src.w,0,w,h }};
        SDL_FreeSurface(surface);
    }
    this->h = h;
}

void Sentence::cover_tex()
{
    auto* renderer = Manager_game::instance()->get_renderer();
    
    SDL_Texture* tex = tex_pool[idx_cur].tex;

    std::string charText = str->substr(idx_cur, 1);
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, charText.c_str(), e_color);
    tex_pool[idx_cur].tex = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(tex);
}



void Sentence::render_str_tex()
{
    auto* renderer = Manager_game::instance()->get_renderer();

    int move_delta = tex_pool[idx_cur].rect_src.x > 640 / 2 ? tex_pool[idx_cur].rect_src.x-640/2 :0;

    for (auto& tex: tex_pool) {
        SDL_Rect rect_dst = {tex.second.rect_src.x+ pos.x- move_delta,pos.y,tex.second.rect_src.w,tex.second.rect_src.h};
        SDL_RenderCopy(renderer, tex.second.tex, nullptr, &rect_dst);
    }
}

void Sentence::add_idx()
{
    if (idx_cur >= tex_pool.size())return;
    cover_tex();
    idx_cur++;
}

void Sentence::set_sentence(std::string* str)
{
	this->str = str;
	generate_face();
}

void Sentence::set_pos(const Vector2D& pos)
{
    this->pos = pos;
}
