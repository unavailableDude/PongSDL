#include "../include/PongBall.hpp"
#include "../include/Paddle.hpp"
#include <iostream>


void CircleDrawOutlined(SDL_Renderer *renderer, Vec2int _coords, int _r);
void CircleDrawFilled(SDL_Renderer *renderer, Vec2int _coords, int _r);


PongBall::PongBall(int x, int y, int r) : _position{x, y}, _velocity{0.0f, 0.0f}, _color{255, 255, 255, 255}, _radius{r}{}

void PongBall::SetColor(SDL_Color col){
	_color = col;
}

void PongBall::Draw(SDL_Renderer* renderer){
	SDL_Color cachedColor;
	SDL_GetRenderDrawColor(renderer, &cachedColor.r, &cachedColor.g, &cachedColor.b, &cachedColor.a);
	
	SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);
	CircleDrawOutlined(renderer, _position, _radius);

	SDL_SetRenderDrawColor(renderer, cachedColor.r, cachedColor.g, cachedColor.b, cachedColor.a);
}

void PongBall::DrawFilled(SDL_Renderer* renderer){
	SDL_Color cachedColor;
	SDL_GetRenderDrawColor(renderer, &cachedColor.r, &cachedColor.g, &cachedColor.b, &cachedColor.a);
	
	SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);
	CircleDrawFilled(renderer, _position, _radius);

	SDL_SetRenderDrawColor(renderer, cachedColor.r, cachedColor.g, cachedColor.b, cachedColor.a);
}

void PongBall::SetVelocity(Vec2f velocity){
	_velocity = velocity;
}

void PongBall::Update(){
	//pdate position based on velocity
	_position._x += _velocity._x;
	_position._y += _velocity._y;

	Paddle* paddle1ref = (Paddle*)_gameContext->_paddle1;
	Paddle* paddle2ref = (Paddle*)_gameContext->_paddle2;

	//check for collisions with top and bottom of window
	if(_position._y - _radius <= 0 || _position._y + _radius >= _gameContext->_windowSize._y){
		_velocity._y *= -1;
	}

	//check for collisions with left and right of window
	if(_position._x - _radius <= 0 || _position._x + _radius >= _gameContext->_windowSize._x){
		_velocity._x *= -1;
		_velocity._y *= -1;
		_position = Vec2int(_gameContext->_windowSize._x / 2, _gameContext->_windowSize._y / 2);
	}

	//check for collisions with paddles
	//paddle1
	if(_position._x - _radius <= paddle1ref->GetX() + paddle1ref->GetW() && _position._y >= paddle1ref->GetY() && _position._y <= paddle1ref->GetY() + paddle1ref->GetH()){
		_velocity._x *= -1;
		// std::cout << "collision with paddle 1 (left)\n";
	}
	//paddle2
	if(_position._x + _radius >= paddle2ref->GetX() && _position._y >= paddle2ref->GetY() && _position._y <= paddle2ref->GetY() + paddle2ref->GetH()){
		_velocity._x *= -1;
		// std::cout << "collision with paddle 2 (right)\n";
	}
}

void PongBall::SetGameContext(GameContext* gameContext){
	_gameContext = gameContext;
}

//util
void CircleDrawOutlined(SDL_Renderer *renderer, Vec2int _coords, int _r){
	const int diameter = (_r * 2);
	int xCurr = _r - 1;
	int yCurr = 0;
	int tX = 1;
	int tY = 1;
	int error = tX - diameter;

	while(xCurr >= yCurr){

		//render 8 octants of the circle
		SDL_RenderDrawPoint(renderer, _coords._x + xCurr, _coords._y - yCurr);
		SDL_RenderDrawPoint(renderer, _coords._x + xCurr, _coords._y + yCurr);
		SDL_RenderDrawPoint(renderer, _coords._x - xCurr, _coords._y - yCurr);
		SDL_RenderDrawPoint(renderer, _coords._x - xCurr, _coords._y + yCurr);
		SDL_RenderDrawPoint(renderer, _coords._x + yCurr, _coords._y - xCurr);
		SDL_RenderDrawPoint(renderer, _coords._x + yCurr, _coords._y + xCurr);
		SDL_RenderDrawPoint(renderer, _coords._x - yCurr, _coords._y - xCurr);
		SDL_RenderDrawPoint(renderer, _coords._x - yCurr, _coords._y + xCurr);
		
		//update coords
		if(error <= 0){
			++yCurr;
			error += tY;
			tY += 2;
		}

		if(error > 0){
			--xCurr;
			tX += 2;
			error += (tX - diameter);
		}
	}
}
void CircleDrawFilled(SDL_Renderer *renderer, Vec2int _coords, int _r){
	const int diameter = (_r * 2);
	int xCurr = _r - 1;
	int yCurr = 0;
	int tX = 1;
	int tY = 1;
	int error = tX - diameter;

	while(xCurr >= yCurr){
		//render 8 octants of the circle
		SDL_RenderDrawLine(renderer, _coords._x + xCurr, _coords._y - yCurr, _coords._x + xCurr, _coords._y + yCurr);
		SDL_RenderDrawLine(renderer, _coords._x - xCurr, _coords._y - yCurr, _coords._x - xCurr, _coords._y + yCurr);
		SDL_RenderDrawLine(renderer, _coords._x + yCurr, _coords._y - xCurr, _coords._x + yCurr, _coords._y + xCurr);
		SDL_RenderDrawLine(renderer, _coords._x - yCurr, _coords._y - xCurr, _coords._x - yCurr, _coords._y + xCurr);
		
		//update coords
		if(error <= 0){
			++yCurr;
			error += tY;
			tY += 2;
		}

		if(error > 0){
			--xCurr;
			tX += 2;
			error += (tX - diameter);
		}
	}
}
