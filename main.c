#include "maze.h"



int main(int argc, char *args[])
{
	Uint32 oldTime
	SDL_Instance instance;
	SDL_Surface *screenSurface = NULL;
	double posX = 22, posY = 12, dirX = -1, dirY = 0, planeX = 0, planeY = 1;
	SDL_Surface texture, *original = IMG_Load("textures/colorstone.png");

	if (!original)
	{
		printf("error loading image\n");
		return (0);
	}
	texture = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0);
	SDL_BlitScaled(original, NULL, texture, NULL);
	worldMap = parser("map.txt");
	if (init_instance(&instance, SCREEN_WIDTH, SCREEN_HEIGHT, "Maze") != 0)
		return (1);
	screenSurface = SDL_GetWindowSurface(instance.window);
	oldTime = SDL_GetTicks();
	init_rain();
	while (1)
	{
		floor_tex(&posX, &posY, &dirX, &dirY,
			&planeX, &planeY, screenSurface, instance);
		wall_tex(texture, &posX, &posY, &dirX,
			&dirY, &planeX, &planeY, screenSurface);
		draw_weapon(screenSurface, w);
		draw_enemies(screenSurface,  posX, posY, dirX, dirY, planeX, planeY);
		SDL_UpdateWindowSurface(instance.window);
		if (keys(&posX, &posY, &dirX, &dirY, &planeX, &planeY,
			screenSurface, instance, &oldTime) == 2)
			return (1);
	}
	return (0)
}
