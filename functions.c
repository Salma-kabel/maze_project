#include "maze.h"



void color_pixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
	int bytes_pp = surface->format->BytesPerPixel;
	Uint8 *ptr = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_pp;

	*ptr = color;
}

void move_rot(double *planeX, double *planeY, double *posX, double *posY,
	double *dirX, double *dirY, double frameTime)
{
	double moveSpeed = frameTime * 2, rotSpeed =  0.1, oldDirX, oldPlaneX;
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	SDL_PumpEvents();
	if (state[SDL_SCANCODE_W])
	{
		if (worldMap[(int)(*posX + *dirX * moveSpeed)][(int)(*posY)] == false)
			*posX += *dirX * moveSpeed;
		if (worldMap[(int)(*posX)][(int)(*posY + *dirY * moveSpeed)] == false)
			*posY += *dirY * moveSpeed;
	}
	if (state[SDL_SCANCODE_S])
	{
		if (worldMap[(int)(*posX - *dirX * moveSpeed)][(int)(*posY)] == false)
			*posX -= *dirX * moveSpeed;
		if (worldMap[(int)(*posX)][(int)(*posY - *dirY * moveSpeed)] == false)
			*posY -= *dirY * moveSpeed;
	}
	if (state[SDL_SCANCODE_A])
	{
		if (worldMap[(int)(*posX - *dirY * moveSpeed)][(int)(*posY)] == false)
			*posX -= *dirY * moveSpeed;
		if (worldMap[(int)(*posX)][(int)(*posY - *dirX * moveSpeed)] == false)
			*posY += *dirX * moveSpeed;
	}
	if (state[SDL_SCANCODE_D])
	{
		if (worldMap[(int)(*posX + *dirY * moveSpeed)][(int)(*posY)] == false)
			*posX += *dirY * moveSpeed;
		if (worldMap[(int)(*posX)][(int)(*posY + *dirX * moveSpeed)] == false)
			*posY -= *dirX * moveSpeed;
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		oldDirX = *dirX;
		*dirX = *dirX * cos(-rotSpeed) - *dirY * sin(-rotSpeed);
		*dirY = oldDirX * sin(-rotSpeed) + *dirY * cos(-rotSpeed);
		oldPlaneX = *planeX;
		*planeX = *planeX * cos(-rotSpeed) - *planeY * sin(-rotSpeed);
		*planeY = oldPlaneX * sin(-rotSpeed) + *planeY * cos(-rotSpeed);
	}
	if (state[SDL_SCANCODE_LEFT])
	{
		oldDirX = *dirX;
		*dirX = *dirX * cos(rotSpeed) - *dirY * sin(rotSpeed);
		*dirY = oldDirX * sin(rotSpeed) + *dirY * cos(rotSpeed);
		oldPlaneX = *planeX;
		*planeX = *planeX * cos(rotSpeed) - *planeY * sin(rotSpeed);
		*planeY = oldPlaneX * sin(rotSpeed) + *planeY * cos(rotSpeed);
	}
}
