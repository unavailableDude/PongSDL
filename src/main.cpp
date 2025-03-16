/*
	main.cpp
	Created on: 13.03.2025
	by: Mohammad Ayad Ghanim	"full M.A.G"
*/


//C++
#include <iostream>
#include <stdint.h>
#include <vector>

//3rd party
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_keyboard.h"

//1st party
#include "../include/GameContext.hpp"
#include "../include/Paddle.hpp"
#include "../include/PongBall.hpp"


const int SCRW = 800;
const int SCRH = 600;


void DrawGameBG(SDL_Renderer *renderer, int width, int height){
	SDL_Color cachedColor;
	SDL_GetRenderDrawColor(renderer, &cachedColor.r, &cachedColor.g, &cachedColor.b, &cachedColor.a);

	int bgw = width;
	int bgh = height;
	Vec2int topLeft(0, 0);
	Vec2int topRight(bgw, 0);
	Vec2int bottomLeft(0, bgh);
	Vec2int bottomRight(bgw, bgh);
	Vec2int topMiddle(bgw / 2, 0);
	Vec2int bottomMiddle(bgw / 2, bgh);

	SDL_Rect gameFieldRect = {topLeft._x, topLeft._y, bottomRight._x, bottomRight._y};

	SDL_RenderDrawRect(renderer, &gameFieldRect);
	SDL_RenderDrawLine(renderer, topMiddle._x, topMiddle._y, bottomMiddle._x, bottomMiddle._y);

	SDL_SetRenderDrawColor(renderer, cachedColor.r, cachedColor.g, cachedColor.b, cachedColor.a);
}


int main(int argc, char* argv[]){
	//initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cerr << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	SDL_Window* window1 = SDL_CreateWindow("Ping Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCRW, SCRH, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer1 = SDL_CreateRenderer(window1, -1, SDL_RENDERER_ACCELERATED);
	if(window1 == NULL){
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	if(renderer1 == NULL){
		std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	
	//initialize game objects
	GameContext gameContext;
	Paddle paddle1(10, SCRH / 2 - 50, 20, 100);			//x, y, w, h. at top left corner
	Paddle paddle2(SCRW - 30, SCRH / 2- 50, 20, 100);
	PongBall ball(SCRW / 2, SCRH / 2, 16);
	paddle1.SetColor({255, 255, 50, 255});
	paddle2.SetColor({255, 255, 50, 255});
	ball.SetColor({255, 255, 50, 255});
	ball.SetVelocity(Vec2f(3.0f, -2.0f));

	gameContext._windowSize = Vec2int(SCRW, SCRH);
	paddle1.SetGameContext(&gameContext);
	paddle2.SetGameContext(&gameContext);
	ball.SetGameContext(&gameContext);
	gameContext._paddle1 = (int*)&paddle1;
	gameContext._paddle2 = (int*)&paddle2;
	gameContext._ball = (int*)&ball;

	int moveSpeed = 8;

	SDL_Event event;
	bool running = true;
	while(running){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE){
				running = false;
				SDL_DestroyWindow(window1);
				return 0;
			}
			else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					case SDLK_w:
						paddle1.SetVelocity(Vec2f(0.0f, -1.0f * moveSpeed));
						break;
					case SDLK_s:
						paddle1.SetVelocity(Vec2f(0.0f, 1.0f * moveSpeed));
						break;

					case SDLK_UP:
						paddle2.SetVelocity(Vec2f(0.0f, -1.0f * moveSpeed));
						break;
					case SDLK_DOWN:
						paddle2.SetVelocity(Vec2f(0.0f, 1.0f * moveSpeed));
						break;
				}
			}
			else if(event.type == SDL_KEYUP){
				switch(event.key.keysym.sym){
					case SDLK_w:
						paddle1.SetVelocity(Vec2f(0.0f, 0.0f * moveSpeed));
						break;
					case SDLK_s:
						paddle1.SetVelocity(Vec2f(0.0f, 0.0f * moveSpeed));
						break;

						case SDLK_UP:
						paddle2.SetVelocity(Vec2f(0.0f, 0.0f * moveSpeed));
						break;
					case SDLK_DOWN:
						paddle2.SetVelocity(Vec2f(0.0f, 0.0f * moveSpeed));
						break;
				}
			}
		}
		
		//physcis update
		ball.Update();
		paddle1.UpdatePosition();
		paddle2.UpdatePosition();

		SDL_SetRenderDrawColor(renderer1, 0, 0, 0, 255);
		SDL_RenderClear(renderer1);

		//draw game
		SDL_SetRenderDrawColor(renderer1, 255, 64, 127, 255);
		DrawGameBG(renderer1, SCRW, SCRH);
		
		SDL_SetRenderDrawColor(renderer1, 255, 255, 255, 255);
		paddle1.DrawFilled(renderer1);
		paddle2.DrawFilled(renderer1);
		ball.DrawFilled(renderer1);

		SDL_RenderPresent(renderer1);
		SDL_Delay(30);
	}

	return 0;
}