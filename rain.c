#include "maze.h"

/**
* init_rain - Used to initialize raindrops giving each on
* a random position and a specific speed
*/

void init_rain(void)
{
	int drops = 1000;

	for (int i = 0; i < drops; i++)
	{
		raindrops[i].x = (double)rand() / RAND_MAX * SCREEN_WIDTH;
		raindrops[i].y = (double)rand() / RAND_MAX * SCREEN_HEIGHT;
		raindrops[i].speed = 8;
	}
}

/*
* draw_rain - Used to draw raindrops on the screen and update its
* position and speed
* @instance: instance to update
* @screenSurface: surface to draw on
*/
void draw_rain(SDL_Instance instance, SDL_Surface *screenSurface)
{
	SDL_Rect raindropRect;

	raindropRect.w = 1;
	raindropRect.h = 6;
	for (int i = 0; i < 1000; i++)
	{
		raindrops[i].y += raindrops[i].speed;
		if (raindrops[i].y > SCREEN_HEIGHT)
		{
		raindrops[i].x = (double)rand() / RAND_MAX * SCREEN_WIDTH;
		raindrops[i].y = 0;
		raindrops[i].speed = 8;
		}
		raindropRect.x = raindrops[i].x;
		raindropRect.y = raindrops[i].y;
		SDL_FillRect(screenSurface, &raindropRect,
			     SDL_MapRGB(screenSurface->format, 200, 200, 200));
	}
	SDL_UpdateWindowSurface(instance.window);
}
