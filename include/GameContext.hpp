#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP


#include "Vec2int.hpp"


class GameContext{
public:
	GameContext();

	Vec2int _windowSize;
	int* _paddle1;
	int* _paddle2;
	int* _ball;
};


#endif