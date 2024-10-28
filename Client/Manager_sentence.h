#pragma once
#include "Manager.h"
#include <string>
#include <Vector>

class Manager_sentence:public Manager<Manager_sentence>
{
	friend class Manager<Manager_sentence>;
public:

	void set_text(const std::string& text);

	std::string* get_sentence();
	void add_idx();

	int get_w_sentence(int idex);
private:

	Manager_sentence();
	~Manager_sentence();
private:
	std::vector<std::string> sentence_pool;
	int idx = 0;
};

