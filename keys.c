#include "maze.h"

/**
* keys - Handles the keyboard input from the player and calls
* suitable function based on that input
* @posX: position x of the player
* @posY: position y of the player
* @dirX: x coordinate of the direction plane
* @dirY: y coordinate of the direction plane
* @planeX: x coordinate of the camera plane
* @planeY: y coordinate of the camera plane
* @screenSurface: surface of the screen to draw on
* @instance: sdl instance to update
* @oldTime: previous time of the frame
* Return: 0 if success , 2 otherwise
*/

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
				if (map_st_sp == 0)
				{
					if (init_instance(&instance2, 260, 160, "Maps") != 0)
						return (2);
					screenSurface2 = SDL_GetWindowSurface(instance2.window);
					draw(screenSurface2, instance2, *posX, *posY, *dirX, *dirY);
					map_st_sp = 1;
				}
				else if (map_st_sp == 1)
				{
					SDL_DestroyWindow(instance2.window);
					 map_st_sp = 0;
				}
			}
			if (event.key.keysym.sym == SDLK_g)
			{
				if (weapon_ch == 4)
					weapon_ch = 0;
				else
					weapon_ch++;
				draw_weapon(screenSurface, weapon_ch);
			}
			if (event.key.keysym.sym == SDLK_r && rain_st_sp == 0)
			{
				rain_st_sp = 1;
				draw_rain(instance, screenSurface);
			}
			else if (event.key.keysym.sym == SDLK_r && rain_st_sp == 1)
				rain_st_sp = 0;
			else if (rain_st_sp == 1)
				draw_rain(instance, screenSurface);
			time = SDL_GetTicks();
			frameTime = (time - *oldTime) / 1000.0;
			*oldTime = time;
			move_rot(planeX, planeY, posX, posY, dirX, dirY, frameTime);
			if (map_st_sp == 1)
				draw(screenSurface2, instance2, *posX, *posY, *dirX, *dirY);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
			break;
		}
	}
	return (0);
}
