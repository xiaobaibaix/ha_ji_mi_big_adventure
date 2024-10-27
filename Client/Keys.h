#pragma once

#include <string>
#include <unordered_map>
#include <SDL.h>

//SDL_SCANCODE_A = 4,
//SDL_SCANCODE_B = 5,
//SDL_SCANCODE_C = 6,
//SDL_SCANCODE_D = 7,
//SDL_SCANCODE_E = 8,
//SDL_SCANCODE_F = 9,
//SDL_SCANCODE_G = 10,
//SDL_SCANCODE_H = 11,
//SDL_SCANCODE_I = 12,
//SDL_SCANCODE_J = 13,
//SDL_SCANCODE_K = 14,
//SDL_SCANCODE_L = 15,
//SDL_SCANCODE_M = 16,
//SDL_SCANCODE_N = 17,
//SDL_SCANCODE_O = 18,
//SDL_SCANCODE_P = 19,
//SDL_SCANCODE_Q = 20,
//SDL_SCANCODE_R = 21,
//SDL_SCANCODE_S = 22,
//SDL_SCANCODE_T = 23,
//SDL_SCANCODE_U = 24,
//SDL_SCANCODE_V = 25,
//SDL_SCANCODE_W = 26,
//SDL_SCANCODE_X = 27,
//SDL_SCANCODE_Y = 28,
//SDL_SCANCODE_Z = 29,
//
//SDL_SCANCODE_1 = 30,
//SDL_SCANCODE_2 = 31,
//SDL_SCANCODE_3 = 32,
//SDL_SCANCODE_4 = 33,
//SDL_SCANCODE_5 = 34,
//SDL_SCANCODE_6 = 35,
//SDL_SCANCODE_7 = 36,
//SDL_SCANCODE_8 = 37,
//SDL_SCANCODE_9 = 38,
//SDL_SCANCODE_0 = 39,

//SDL_SCANCODE_RETURN = 40����ʾ�س�����Enter����
//SDL_SCANCODE_ESCAPE = 41����ʾEsc����Escape����
//SDL_SCANCODE_BACKSPACE = 42����ʾ�˸����Backspace����
//SDL_SCANCODE_TAB = 43����ʾ�Ʊ����Tab����
//SDL_SCANCODE_SPACE			= 44����ʾ�ո����Spacebar����
//SDL_SCANCODE_MINUS			= 45����ʾ���ż��� - ����
//SDL_SCANCODE_EQUALS			= 46����ʾ�Ⱥż��� = ����
//SDL_SCANCODE_LEFTBRACKET		= 47����ʾ�����ż���[����
//SDL_SCANCODE_RIGHTBRACKET		= 48����ʾ�ҷ����ż���]����
//SDL_SCANCODE_BACKSLASH		= 49����ʾ��б�ܼ���\����
//SDL_SCANCODE_NONUSHASH		= 50����ʾ��������׼���̵ľ��ż���#�����������ĳЩ���̲����д��ڣ�����ISO���̡�
//SDL_SCANCODE_SEMICOLON		= 51����ʾ�ֺż���; ����
//SDL_SCANCODE_APOSTROPHE		= 52����ʾ�����ż���'����
//SDL_SCANCODE_GRAVE			= 53����ʾ�����ż���`������ĳЩ���̲����У������Ҳ������������ţ��粨�˺ţ�~����
//SDL_SCANCODE_COMMA			= 54����ʾ���ż���, ����
//SDL_SCANCODE_PERIOD			= 55����ʾ��ż���.����
//SDL_SCANCODE_SLASH			= 56����ʾб�ܼ��� / ����
//SDL_SCANCODE_CAPSLOCK			= 57����ʾ��д��������Caps Lock����

typedef enum 
{
	A=60,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
	One,Two,Three,Four,Five,Six,Seven,Eight,Nine,Zero,
	SPACE=100,MINUS,EQUALS,LEFTBRACKET, RIGHTBRACKET, BACKSLASH, NONUSHASH, SEMICOLON, APOSTROPHE,GRAVE,COMMA, PERIOD, SLASH
}KeyWithShift;

std::unordered_map<int, char> key_value = {
	{SDL_SCANCODE_A,'a'},
	{SDL_SCANCODE_B,'b'},
	{SDL_SCANCODE_C,'c'},
	{SDL_SCANCODE_D,'d'},
	{SDL_SCANCODE_E,'e'},
	{SDL_SCANCODE_F,'f'},
	{SDL_SCANCODE_G,'g'},
	{SDL_SCANCODE_H,'h'},
	{SDL_SCANCODE_I,'i'},
	{SDL_SCANCODE_J,'j'},
	{SDL_SCANCODE_K,'k'},
	{SDL_SCANCODE_L,'l'},
	{SDL_SCANCODE_M,'m'},
	{SDL_SCANCODE_N,'n'},
	{SDL_SCANCODE_O,'o'},
	{SDL_SCANCODE_P,'p'},
	{SDL_SCANCODE_Q,'q'},
	{SDL_SCANCODE_R,'r'},
	{SDL_SCANCODE_S,'s'},
	{SDL_SCANCODE_T,'t'},
	{SDL_SCANCODE_U,'u'},
	{SDL_SCANCODE_V,'v'},
	{SDL_SCANCODE_W,'w'},
	{SDL_SCANCODE_X,'x'},
	{SDL_SCANCODE_Y,'y'},
	{SDL_SCANCODE_Z,'z'},
	{SDL_SCANCODE_1,'1'},
	{SDL_SCANCODE_2,'2'},
	{SDL_SCANCODE_3,'3'},
	{SDL_SCANCODE_4,'4'},
	{SDL_SCANCODE_5,'5'},
	{SDL_SCANCODE_6,'6'},
	{SDL_SCANCODE_7,'7'},
	{SDL_SCANCODE_8,'8'},
	{SDL_SCANCODE_9,'9'},
	{SDL_SCANCODE_0,'0'},
	{SDL_SCANCODE_SPACE,' '},
	{SDL_SCANCODE_MINUS,'-',},
	{SDL_SCANCODE_EQUALS,'='},
	{SDL_SCANCODE_LEFTBRACKET,'['},
	{SDL_SCANCODE_RIGHTBRACKET,']'},
	{SDL_SCANCODE_BACKSLASH,'\\'},
	{SDL_SCANCODE_NONUSHASH,'#'},
	{SDL_SCANCODE_SEMICOLON,';'},
	{SDL_SCANCODE_APOSTROPHE,'\''},
	{SDL_SCANCODE_GRAVE,'`'},
	{SDL_SCANCODE_COMMA,','},
	{SDL_SCANCODE_PERIOD,'.'},
	{SDL_SCANCODE_SLASH,'/' },
	{A,'A'},
	{B,'B'},
	{C,'C'},
	{D,'D'},
	{E,'E'},
	{F,'F'},
	{G,'G'},
	{H,'H'},
	{I,'I'},
	{J,'J'},
	{K,'K'},
	{L,'L'},
	{M,'M'},
	{N,'N'},
	{O,'O'},
	{P,'P'},
	{Q,'Q'},
	{R,'R'},
	{S,'S'},
	{T,'T'},
	{U,'U'},
	{V,'V'},
	{W,'W'},
	{X,'X'},
	{Y,'Y'},
	{Z,'Z'},
	{Zero,')'},
	{Nine,'('},
	{Eight,'*'},
	{Seven,'&'},
	{Six,'^'},
	{Five,'%'},
	{Four,'$'},
	{Three,'#'},
	{Two,'@'},
	{One,'!'},
	{GRAVE,'~'},
	{MINUS,'_'},
	{EQUALS,'+'},
	{LEFTBRACKET,'{'},
	{RIGHTBRACKET,'}'}, 
	{BACKSLASH,'|'},
	{NONUSHASH,'#'}, 
	{SEMICOLON,':'},
	{APOSTROPHE,'"'},
	{COMMA,'<'},
	{PERIOD,'>'},
	{SLASH,'?'},
	{GRAVE,' '}
};