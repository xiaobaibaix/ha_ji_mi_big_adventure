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
	const int FONT_SIZE = 24;
private:
	SDL_Color b_color = {10,10,10};//ǰ
	SDL_Color e_color = {255,0,0};//��

	Vector2D pos;

	std::unordered_map<int, TexRect> tex_pool;//������ռ������ͼƬ

	int w, h;

	TTF_Font* font = nullptr;
	
	int idx_cur = 0;//���뵽���ַ��±��

	std::string* str = nullptr;;
};

