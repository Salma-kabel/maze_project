#include "maze.h"

int blockWidth = 260 / 24;
int blockHeight = 160 / 24;

void draw(SDL_Surface *screenSurface, SDL_Instance instance, int posx, int posy)
{
    for(int x = 0; x < 24; x++)
    {
        for(int y = 0; y < 24; y++)
        {
            Uint32 color;
            switch(worldMap[x][y])
            {
                case 0:  color = SDL_MapRGB(screenSurface->format, 0, 0, 0);  break;
                default:  color = SDL_MapRGB(screenSurface->format, 255, 0, 0);
            }
            SDL_Rect block;
            block.x = x * blockWidth;
            block.y = y * blockHeight;
            block.w = blockWidth;
            block.h = blockHeight;
            SDL_FillRect(screenSurface, &block, color);
        }
    }
    SDL_Rect player;
    player.x = posx * blockWidth;
    player.y = posy * blockHeight;
    player.w = blockWidth;
    player.h = blockHeight;
    SDL_FillRect(screenSurface, &player, SDL_MapRGB(screenSurface->format, 0, 255, 0));
    SDL_UpdateWindowSurface(instance.window);
}
