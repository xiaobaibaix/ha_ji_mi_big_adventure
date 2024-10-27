#include "pch.h"
#include "Manager_sentence.h"

#include <regex>

Manager_sentence::Manager_sentence()
{

}

Manager_sentence::~Manager_sentence()
{
}

void Manager_sentence::set_text(const std::string& text)
{
    std::regex pattern("([^.!?]+[.!?]+\\s*)");
    std::sregex_iterator it(text.begin(), text.end(), pattern);
    std::sregex_iterator end;

    while (it != end) {
        std::string currentSentence= it->str();
        ++it;
        // ȥ������ǰ��Ŀհ��ַ�
        currentSentence.erase(0, currentSentence.find_first_not_of(" \t\n\r\f\v"));
        currentSentence.erase(currentSentence.find_last_not_of(" \t\n\r\f\v")+1);

        sentence_pool.push_back(currentSentence);
    }
}

std::string* Manager_sentence::get_sentence(int idx)
{
    if (idx < 0 || idx >= sentence_pool.size())return nullptr;
    return &(sentence_pool[idx]);
}

int Manager_sentence::get_w_sentence(int idex)
{
    return sentence_pool.size();
}

