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

//1st party
#include "../include/GameContext.hpp"
#include "../include/Paddle.hpp"
#include "../include/PongBall.hpp"


const int SCRW = 800;
const int SCRH = 600;


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
	ball.SetVelocity(Vec2f(3.0f, -2.0f));

	gameContext._windowSize = Vec2int(SCRW, SCRH);
	paddle1.SetGameContext(&gameContext);
	paddle2.SetGameContext(&gameContext);
	ball.SetGameContext(&gameContext);
	gameContext._paddle1 = (int*)&paddle1;
	gameContext._paddle2 = (int*)&paddle2;
	gameContext._ball = (int*)&ball;

	int moveSpeed = 16;

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
						paddle1.MoveUp(moveSpeed);
						paddle2.MoveUp(moveSpeed);
						break;
					case SDLK_s:
						paddle1.MoveDown(moveSpeed);
						paddle2.MoveDown(moveSpeed);
						break;  
					case SDLK_a:
						break;
					case SDLK_d:
						break;
				}
			}
		}
		ball.Update();

		SDL_SetRenderDrawColor(renderer1, 0, 0, 0, 255);
		SDL_RenderClear(renderer1);

		paddle1.DrawFilled(renderer1);
		paddle2.DrawFilled(renderer1);
		ball.DrawFilled(renderer1);

		SDL_RenderPresent(renderer1);
		SDL_Delay(30);
	}

	return 0;
}