#include "maze.h"



void floor_tex(double *posX, double *posY, double dirX, double dirY, double *planeX, double *planeY, SDL_Surface* screenSurface, SDL_Instance instance)
{
    SDL_Surface* original = IMG_Load("textures/redbrick.png");
    SDL_Surface* texture = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0);
    SDL_BlitScaled(original, NULL, texture, NULL);
    for(int y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y++)
    {
      float rayDirX0 = dirX - *planeX;
      float rayDirY0 = dirY - *planeY;
      float rayDirX1 = dirX + *planeX;
      float rayDirY1 = dirY + *planeY;
      int p = y - SCREEN_HEIGHT / 2
      float posZ = 0.5 * SCREEN_HEIGHT;
      float rowDistance = posZ / p;
      float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / SCREEN_WIDTH;
      float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / SCREEN_WIDTH;
      float floorX = *posX + rowDistance * rayDirX0;
      float floorY = *posY + rowDistance * rayDirY0;
      for(int x = 0; x < SCREEN_WIDTH; ++x)
      {
        int cellX = (int)(floorX);
        int cellY = (int)(floorY);
        int tx = (int)(texture->w * (floorX - cellX)) & (texture->w - 1);
        int ty = (int)(texture->h * (floorY - cellY)) & (texture->h - 1);
        floorX += floorStepX;
        floorY += floorStepY;
        Uint32 color;
        color = ((Uint32*)texture->pixels)[ty * texture->w + tx];
        color = (color >> 1) & 8355711;
        putpixel(screenSurface, x, y, color);
      }
    }
    SDL_UpdateWindowSurface(instance.window);
}
