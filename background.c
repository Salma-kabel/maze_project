#include "maze.h"



void floor_tex(double *posX, double *posY, double *dirX, double *dirY,
	double *planeX,	double *planeY,
	SDL_Surface *screenSurface, SDL_Instance instance)
{
	float rayDirX0, rayDirY0, rayDirX1, rayDirY1, posZ, rowDistance, floorStepX,
		floorStepY, floorX, floorY;
	int cellX, cellY, x, ty, tx, p;
	Uint32 color;
	SDL_Surface *original = IMG_Load("textures/redbrick.png");
	SDL_Surface *texture = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0);

	SDL_BlitScaled(original, NULL, texture, NULL);
	for (int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y++)
	{
		rayDirX0 = *dirX - *planeX;
		rayDirY0 = *dirY - *planeY;
		rayDirX1 = *dirX + *planeX;
		rayDirY1 = *dirY + *planeY;
		p = y - SCREEN_HEIGHT / 2;
		posZ = 0.5 * SCREEN_HEIGHT;
		rowDistance = posZ / p;
		floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
		floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;
		floorX = *posX + rowDistance * rayDirX0;
		floorY = *posY + rowDistance * rayDirY0;
		for (x = 0; x < SCREEN_WIDTH; ++x)
		{
			cellX = floor(floorX);
			cellY = floor(floorY);
			tx = (int)(texture->w * (floorX - cellX)) & (texture->w - 1);
			ty = (int)(texture->h * (floorY - cellY)) & (texture->h - 1);
			floorX += floorStepX;
			floorY += floorStepY;
			color = ((Uint32 *)texture->pixels)[ty * texture->w + tx];
			color = color / 2;
			color_pixel(screenSurface, x, y, color);
		}
	}
	SDL_UpdateWindowSurface(instance.window);
}


void wall_tex(SDL_Surface *texture, double *posX, double *posY, double *dirX,
	double *dirY, double *planeX, double *planeY, SDL_Surface *screenSurface)
{
	int x, y, pitch = 0, mapX, mapY, stepX, stepY, hit, side, lineHeight,
		drawStart, drawEnd, texX, texY;
	double cameraX, rayDirX, rayDirY, sideDistX, sideDistY, deltaDistX,
		deltaDistY, perpWallDist, wallX, step, texPos;
	Uint32 color, *pixels;

	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
		rayDirX = *dirX + *planeX * cameraX;
		rayDirY = *dirY + *planeY * cameraX;
		mapX = (int)(*posX);
		mapY = (int)(*posY);
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (*posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - *posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (*posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - *posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - *posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - *posY + (1 - stepY) / 2) / rayDirY;
		lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;
		if (side == 0)
			wallX = *posY + perpWallDist * rayDirY;
		else
			wallX = *posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		texX = (int)(wallX * (double)texture->w);
		step = (double)texture->h / lineHeight;
		texPos = (drawStart - pitch - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
		pixels = (Uint32 *)texture->pixels;
		for (y = drawStart; y < drawEnd; y++)
		{
			depthBuffer[x] = perpWallDist;
			texY = (int)texPos & (texture->h - 1);
			texPos += step;
			color = pixels[texY * texture->w + texX];
			if (side == 1)
				color = color / 2;
			color_pixel(screenSurface, x, y, color);
		}
	}
}
