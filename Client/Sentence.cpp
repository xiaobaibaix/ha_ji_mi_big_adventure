#include "pch.h"
#include "Sentence.h"
#include "Manager_resource.h"
#include "Manager_game.h"

Sentence::Sentence():pos(0,0)
{
	font = TTF_OpenFont(Manager_resource::instance()->find_font_path("font").c_str(), FONT_SIZE);
    box = Manager_resource::instance()->find_texture("ui_textbox");

    int w, h;
    SDL_QueryTexture(box, nullptr, nullptr, &w, &h);

    rect_border = { 0,0,640,100 };//相对pos的坐标

    rect_content = { 90,45,640 - 180,0 };//相对rect_border坐标

}

Sentence::~Sentence()
{
}

void Sentence::generate_face()
{
    auto* renderer=Manager_game::instance()->get_renderer();
    // 分别渲染每个字符
    int w=0, h=0;
    for (int i = 0; i < str->length(); ++i) {
        std::string charText = str->substr(i, 1);
        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, charText.c_str(), b_color);

        w = surface->w, h = surface->h;
        tex_pool[i] = {SDL_CreateTextureFromSurface(renderer, surface), 
            { (i-1<0)? 0:tex_pool[i - 1].rect_src.x+ tex_pool[i - 1].rect_src.w,0,w,h }};
        SDL_FreeSurface(surface);
    }
    rect_content.h = h;
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

    int idx = idx_cur - 1 < 0 ? 0 : idx_cur - 1;

    int move_delta= tex_pool[idx].rect_src.x+ tex_pool[idx].rect_src.w/2> rect_content.w / 2 ? tex_pool[idx].rect_src.x+ tex_pool[idx].rect_src.w / 2 - rect_content.w / 2 : 0 ;

    int sum = tex_pool[idx].rect_src.w/2;
    for (int i = idx+1; i < tex_pool.size();i++) {
        sum+=tex_pool[i].rect_src.w;
    }

    if (sum < rect_content.w/2)move_delta -= (rect_content.w/2 - sum);

    SDL_Rect border = { pos.x + rect_border.x,pos.y + rect_border.y,rect_border.w,rect_border.h };
    SDL_RenderCopy(renderer, box, nullptr, &border);

    for (int l = idx; l >= 0;l--) {
        if (tex_pool[l].rect_src.x + pos.x + rect_border.x + rect_content.x - move_delta < pos.x+rect_border.x+rect_content.x)break;
        SDL_Rect rect_dst = { 
            tex_pool[l].rect_src.x + pos.x + rect_border.x + rect_content.x - move_delta,
            pos.y + rect_border.y + rect_content.y,
            tex_pool[l].rect_src.w,
            tex_pool[l].rect_src.h 
        };
        SDL_RenderCopy(renderer, tex_pool[l].tex, nullptr, &rect_dst);
    }
    for (int r = idx+1; r < tex_pool.size();r++) {
        if (tex_pool[r].rect_src.x + pos.x + rect_border.x + rect_content.x - move_delta > 640-(pos.x+rect_border.x+rect_content.x))break;
        SDL_Rect rect_dst = { 
            tex_pool[r].rect_src.x + pos.x + rect_border.x + rect_content.x- move_delta,
            pos.y + rect_border.y + rect_content.y,
            tex_pool[r].rect_src.w,
            tex_pool[r].rect_src.h 
        };
        SDL_RenderCopy(renderer, tex_pool[r].tex, nullptr, &rect_dst);
    }
}

void Sentence::add_idx()
{
    if (idx_cur == tex_pool.size()) {
        return;
    }
    cover_tex();
    idx_cur++;
}

void Sentence::set_sentence(std::string* str)
{
    for (auto it = tex_pool.begin(); it != tex_pool.end();++it) {
        SDL_Texture* tex=it->second.tex;
        SDL_DestroyTexture(tex);
    }
    idx_cur = 0;
    tex_pool.clear();
	this->str = str;
	generate_face();
}

void Sentence::set_pos(const Vector2D& pos)
{
    this->pos = pos;
}

const char& Sentence::get_char() const
{
    return str->c_str()[idx_cur];
}
