#include "maze.h"

/**
* color_pixel - colors pixels on the screen to a specific color
* @surface: surface of the pixels
* @x: x coordinate of the pixel
* @y: y coordinate of the pixel
* @color: color to use on the pixel
*/

void color_pixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
	int bytes_pp = surface->format->BytesPerPixel;
	Uint8 *ptr = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_pp;

	*ptr = color;
}

/**
* move_rot - Handles the move of the player and rotation of camera
* @planeX: x coordinate of the camera plane
* @planeY: y coordinate of the camera plane
* @posX: position x of the player
* @posY: position y of the player
* @dirX: x coordinate of the direction plane
* @dirY: y coordinate of the direction plane
* @frameTime: frametime to use
*/
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
