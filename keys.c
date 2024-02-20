#include "maze.h"



int keys(double *posX, double *posY, double *dirX, double *dirY,
	double *planeX, double *planeY, SDL_Surface *screenSurface,
	SDL_Instance instance, Uint32 *oldTime)
{
	Uint32 time;
	double frameTime;
	SDL_Event event;

	while (1)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			return (2);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_m)
			{
				if (m == 0)
				{
					if (init_instance(&instance2, 260, 160, "Maps") != 0)
						return (2);
					screenSurface2 = SDL_GetWindowSurface(instance2.window);
					draw(screenSurface2, instance2, *posX, *posY, *dirX, *dirY);
					m = 1;
				}
				else if (m == 1)
				{
					SDL_DestroyWindow(instance2.window;
					 m = 0;
				}
			}
			if (event.key.keysym.sym == SDLK_g)
			{
				if (w == 4)
					w = 0;
				else
					w++;
				draw_weapon(screenSurface, w);
			}
			if (event.key.keysym.sym == SDLK_r && r == 0)
			{
				r = 1;
				draw_rain(instance, screenSurface);
			}
			else if (event.key.keysym.sym == SDLK_r && r == 1)
				r = 0;
			else if (r == 1)
				draw_rain(instance, screenSurface);
			time = SDL_GetTicks();
			frameTime = (time - *oldTime) / 1000.0;
			*oldTime = time;
			move_rot(planeX, planeY, posX, posY, dirX, dirY, frameTime);
			if (m == 1)
				draw(screenSurface2, instance2, *posX, *posY, *dirX, *dirY);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
			break;
		}
	}
}
