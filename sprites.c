#include "maze.h"

/**
* draw_enemies - Used to draw enemies on the map
* @screenSurface: surface of the screen to draw on
* @posX: position x of the player
* @posY: position y of the player
* @dirX: x coordinate of the direction plane
* @dirY: y coordinate of the direction plane
* @planeX: x coordinate of the camera plane
* @planeY: y coordinate of the camera plane
*/

void draw_enemies(SDL_Surface *screenSurface, double posX, double posY, double dirX, double dirY, double planeX, double planeY)
{
	double spriteX, spriteY, invDet, transformX, transformY;
	int spriteScreenX, spriteHeight, drawStartY, drawEndY, spriteWidth,
		drawStartX, drawEndX, stripe, y, texX, d, texY, i;
	Uint32 color;
	SDL_Surface *original = IMG_Load("textures/enemyt.png");
	SDL_Surface *spriteImage = SDL_CreateRGBSurface(0, 250, 202, 32, 0, 0, 0, 0);

	SDL_BlitScaled(original, NULL, spriteImage, NULL);
	for (i = 0; i < 3; i++)
	{
		spriteX = sprite[i].x - posX;
		spriteY = sprite[i].y - posY;
		invDet = 1.0 / (planeX * dirY - dirX * planeY);
		transformX = invDet * (dirY * spriteX - dirX * spriteY);
		transformY = invDet * (-planeY * spriteX + planeX * spriteY);
		spriteScreenX = (int)((SCREEN_WIDTH / 2) * (1 + transformX / transformY));
		spriteHeight = abs((int)(SCREEN_HEIGHT / (transformY)));
		drawStartY = -spriteHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStartY < 0)
			drawStartY = 0;
		drawEndY = spriteHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEndY >= SCREEN_HEIGHT)
			drawEndY = SCREEN_HEIGHT - 1;
		spriteWidth = abs((int)(SCREEN_HEIGHT / (transformY)));
		drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= SCREEN_WIDTH)
			drawEndX = SCREEN_WIDTH - 1;
		for (stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * spriteImage->w / spriteWidth) / 256;
			if (transformY > 0 && stripe > 0 && stripe < SCREEN_WIDTH && transformY < depthBuffer[stripe])
			{
				for (y = drawStartY; y < drawEndY; y++)
				{
					d = (y) * 256 - SCREEN_HEIGHT * 128 + spriteHeight * 128;
					texY = ((d * spriteImage->h) / spriteHeight) / 256;
					color = ((Uint32 *)spriteImage->pixels)[texY * spriteImage->w + texX];
					if (color == 0x0000)
						continue;
					color_pixel(screenSurface, stripe, y, color);
				}
			}
		}
	}
	SDL_FreeSurface(spriteImage);
}

/**
* draw_weapon - Used to draw different weapons on the screen
* @screenSurface: surface to draw on
* @weapon_ch: number of weapon to use
*/
void draw_weapon(SDL_Surface *screenSurface, int weapon_ch)
{
	int weaponPosX, weaponPosY;
	SDL_Surface *originalWeapon = IMG_Load(weapon[weapon_ch]);
	SDL_Surface *weaponImage = SDL_CreateRGBSurface(0, 500, 404, 32, 0, 0, 0, 0);
	Uint32 colorkey = SDL_MapRGB(weaponImage->format, 255, 255, 255);
	SDL_Rect weaponRect;

	SDL_FillRect(weaponImage, NULL, colorkey);
	SDL_BlitScaled(originalWeapon, NULL, weaponImage, NULL);
	SDL_SetColorKey(weaponImage, SDL_TRUE, colorkey);
	SDL_FreeSurface(originalWeapon);
	weaponPosX = SCREEN_WIDTH / 2 - weaponImage->w / 2;
	weaponPosY = SCREEN_HEIGHT - weaponImage->h;
	weaponRect.x = weaponPosX;
	weaponRect.y = weaponPosY;
	weaponRect.w = weaponImage->w;
	weaponRect.h = weaponImage->h;
	SDL_BlitSurface(weaponImage, NULL, screenSurface, &weaponRect);
}
