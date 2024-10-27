#pragma once
#include "Rect.h"

#include <string>
#include <vector>
#include <unordered_map>

struct TexRect
{
	SDL_Texture* tex = nullptr;
	SDL_Rect rect_src;
};

class Sentence
{
public:
	Sentence();
	~Sentence();


	void render_str_tex();//渲染纹理

	void add_idx();
	void set_sentence(std::string* str);
	void set_pos(const Vector2D& pos);
private:
	void generate_face();//生成纹理
	void cover_tex();//覆盖纹理
private:
	const int FONT_SIZE = 16;
private:
	SDL_Color b_color = {50,50,50};//前
	SDL_Color e_color = {50,50,225};//后

	Vector2D pos;

	SDL_Rect rect_border;
	SDL_Rect rect_content;

	std::unordered_map<int, TexRect> tex_pool;//句子所占的纹理图片
	SDL_Texture* box = nullptr;

	TTF_Font* font = nullptr;
	
	int idx_cur = 0;//输入到的字符下表标

	std::string* str = nullptr;;
};

