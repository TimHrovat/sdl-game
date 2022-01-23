#include <SDL2/SDL.h>
#include <iostream>

void handleKeyDownEvent(SDL_Event event);
void moveRect(int x, int y);

SDL_Rect rect;
SDL_Renderer *renderer;

const int mult = 10;

int main()
{

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window =
		SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED,
						 SDL_WINDOWPOS_UNDEFINED, 1080, 720, SDL_WINDOW_OPENGL);

	if (window == NULL)
	{
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	rect.x = 10;
	rect.y = 10;
	rect.h = 300;
	rect.w = 300;

	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);

	SDL_Event event;

	bool quit = false;

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{

			case SDL_KEYDOWN:
				handleKeyDownEvent(event);
				break;

			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{

				case SDL_WINDOWEVENT_CLOSE:
					quit = true;
					break;
				}
				break;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

// ==== Key Events ====

void handleKeyDownEvent(SDL_Event event)
{
	std::cout << "Key pressed: ";
	std::cout << event.key.keysym.sym << '\n';

	if (event.key.keysym.sym == SDLK_UP)
		moveRect(0, -mult);
	if (event.key.keysym.sym == SDLK_DOWN)
		moveRect(0, mult);
	if (event.key.keysym.sym == SDLK_LEFT)
		moveRect(-mult, 0);
	if (event.key.keysym.sym == SDLK_RIGHT)
		moveRect(mult, 0);
}

void moveRect(int x, int y)
{
	rect.x += x;
	rect.y += y;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
}