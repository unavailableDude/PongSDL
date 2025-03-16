#include "../include/Paddle.hpp"


Paddle::Paddle(int x, int y, int w, int h) : _position(x, y), _rect{x, y, w, h}, _color{255, 255, 255, 255}, _velocity(0.0f, 0.0f){}

void Paddle::SetColor(SDL_Color col){
	_color = col;
}

void Paddle::Draw(SDL_Renderer* renderer){
	SDL_Color cachedColor;
	SDL_GetRenderDrawColor(renderer, &cachedColor.r, &cachedColor.g, &cachedColor.b, &cachedColor.a);
	
	SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);
	SDL_RenderDrawRect(renderer, &_rect);

	SDL_SetRenderDrawColor(renderer, cachedColor.r, cachedColor.g, cachedColor.b, cachedColor.a);
}

void Paddle::DrawFilled(SDL_Renderer* renderer){
	SDL_Color cachedColor;
	SDL_GetRenderDrawColor(renderer, &cachedColor.r, &cachedColor.g, &cachedColor.b, &cachedColor.a);
	
	SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);
	SDL_RenderFillRect(renderer, &_rect);

	SDL_SetRenderDrawColor(renderer, cachedColor.r, cachedColor.g, cachedColor.b, cachedColor.a);
}

void Paddle::MoveUp(int step){
	_position._y -= step;
	_rect.y = _position._y;
}

void Paddle::MoveDown(int step){
	_position._y += step;
	_rect.y = _position._y;
}

void Paddle::UpdatePosition(){
	_position._x += _velocity._x;
	_position._y += _velocity._y;
	_rect.x = _position._x;
	_rect.y = _position._y;
}

void Paddle::SetVelocity(Vec2f velocity){
	_velocity = velocity;
}

void Paddle::SetGameContext(GameContext* gameContext){
	_gameContext = gameContext;
}

int Paddle::GetX(){
	return _position._x;
}
int Paddle::GetY(){
	return _position._y;
}
int Paddle::GetW(){
	return _rect.w;
}
int Paddle::GetH(){
	return _rect.h;
}
