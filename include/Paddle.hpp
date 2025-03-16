#ifndef PADDLE_HPP
#define PADDLE_HPP


#include "SDL2/SDL.h"
#include "Vec2f.hpp"
#include "Vec2int.hpp"
#include "GameContext.hpp"


class Paddle{
public:
	Paddle(int x, int y, int w, int h);

	void SetColor(SDL_Color col);
	void Draw(SDL_Renderer* renderer);
	void DrawFilled(SDL_Renderer* renderer);
	void MoveUp(int step);
	void MoveDown(int step);
	// void moveLeft();
	// void moveRight();
	void UpdatePosition();
	void SetVelocity(Vec2f velocity);
	void SetGameContext(GameContext* gameContext);
	int GetX();
	int GetY();
	int GetW();
	int GetH();

private:
	Vec2int _position;
	Vec2f _velocity;
	SDL_Rect _rect;
	SDL_Color _color;
	GameContext* _gameContext;
};

#endif