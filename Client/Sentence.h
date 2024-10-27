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


	void render_str_tex();//��Ⱦ����

	void add_idx();
	void set_sentence(std::string* str);
	void set_pos(const Vector2D& pos);
private:
	void generate_face();//��������
	void cover_tex();//��������
private:
	const int FONT_SIZE = 16;
private:
	SDL_Color b_color = {50,50,50};//ǰ
	SDL_Color e_color = {50,50,225};//��

	Vector2D pos;

	SDL_Rect rect_border;
	SDL_Rect rect_content;

	std::unordered_map<int, TexRect> tex_pool;//������ռ������ͼƬ
	SDL_Texture* box = nullptr;

	TTF_Font* font = nullptr;
	
	int idx_cur = 0;//���뵽���ַ��±��

	std::string* str = nullptr;;
};

