#include "maze.h"

/**
* draw - Used to draw a map of the whole maze and the 
* location of the player and his direction
* @screenSurface: surface of the screen to draw on
* @instance: sdl instance to update
* @posX: position x of the player
* @posY: position y of the player
* @dirX: x coordinate of the direction plane
* @dirY: y coordinate of the direction plane
*/

void draw(SDL_Surface *screenSurface, SDL_Instance instance,
	int posx, int posy, double dirX, double dirY)
{
	Uint32 color;
	int x, y, blockWidth = 260 / 24, blockHeight = 160 / 24;
	for(x = 0; x < 24; x++)
	{
		for(y = 0; y < 24; y++)
		{
			if (worldMap[x][y] == 0)
				color = SDL_MapRGB(screenSurface->format, 0, 0, 0);
			else
				color = SDL_MapRGB(screenSurface->format, 255, 0, 0);
		}
		SDL_Rect block;
		block.x = x * blockWidth;
		block.y = y * blockHeight;
		block.w = blockWidth;
		block.h = blockHeight;
		SDL_FillRect(screenSurface, &block, color);
	}
	SDL_Rect player;
	player.x = posx * blockWidth;
	player.y = posy * blockHeight;
	player.w = blockWidth;
	player.h = blockHeight;
	SDL_FillRect(screenSurface, &player, SDL_MapRGB(screenSurface->format, 0, 255, 0));
	SDL_Rect fov;
	fov.x = (posx + dirX) * blockWidth;
	fov.y = (posy + dirY) * blockHeight;
	fov.w = blockWidth;
	fov.h = blockHeight;
	SDL_FillRect(screenSurface, &fov, SDL_MapRGB(screenSurface->format, 0, 0, 255));
	SDL_UpdateWindowSurface(instance.window);
}
