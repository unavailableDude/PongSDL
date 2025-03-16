#ifndef PINGPONGBALL_HPP
#define PINGPONGBALL_HPP


#include "SDL2/SDL.h"
#include "Vec2f.hpp"
#include "Vec2int.hpp"

#include "GameContext.hpp"


class PongBall{
public:
	PongBall(int x, int y, int r);

	void SetColor(SDL_Color col);
	void Draw(SDL_Renderer* renderer);
	void DrawFilled(SDL_Renderer* renderer);
	// void Move();
	void SetVelocity(Vec2f velocity);
	// void SetPosition(Vec2int position);
	void Update();
	void SetGameContext(GameContext* gameContext);
	// int GetX();
	// int GetY();
	// int GetR();

private:
	Vec2int _position;
	Vec2f _velocity;
	SDL_Color _color;
	int _radius;
	GameContext* _gameContext;
};


#endif