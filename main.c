#include "maze.h"

<<<<<<< HEAD
int g = 0, m = 0;
Uint32 buffer[1260][720];
#define texWidth 64 
#define texHeight 64
const int SCREEN_WIDTH = 1260;
const int SCREEN_HEIGHT = 720;
int **worldMap;
int mapWidth = 1, mapHeight = 0;


int main(int argc, char* args[])
{
    int pitch = 0; 
    SDL_Instance instance;
    SDL_Surface* screenSurface = NULL;
    SDL_Instance instance2;
    SDL_Surface* screenSurface2 = NULL;
    double posX = 22, posY = 12; 
    double dirX = -01, dirY = 0; 
    double planeX = 0, planeY = 0.66; 
    worldMap = parser("map.txt");
    SDL_Surface* original = IMG_Load("textures/colorstone.png");
    SDL_Surface* texture = SDL_CreateRGBSurface(0, 128, 128, 32, 0, 0, 0, 0);
    SDL_BlitScaled(original, NULL, texture, NULL);
    if (init_instance(&instance, SCREEN_WIDTH, SCREEN_HEIGHT, "Maze") != 0)
        return (1);
    screenSurface = SDL_GetWindowSurface(instance.window);
    Uint32 oldTime = SDL_GetTicks();
    while (1)
    {
        floor_tex(&posX, &posY, dirX, dirY, &planeX, &planeY, screenSurface, instance);
        for(int x = 0; x < SCREEN_WIDTH; x++)
        {
            double cameraX = 2 * x / (double)SCREEN_WIDTH - 1; 
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
            int mapX = (int)posX;
            int mapY = (int)posY;
            double sideDistX;
            double sideDistY;
            double deltaDistX = fabs(1 / rayDirX);
            double deltaDistY = fabs(1 / rayDirY);
            int stepX;
            int stepY;
            int hit = 0;
            int side;
            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
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
                if (worldMap[mapX][mapY] > 0) hit = 1;
             }
             double perpWallDist;
             if (side == 0)
                perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
             else
                perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
             int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
             int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
             if(drawStart < 0) drawStart = 0;
             int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
             if(drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;
             double wallX;
             if(side == 0) wallX = posY + perpWallDist * rayDirY;
             else          wallX = posX + perpWallDist * rayDirX;
             wallX -= floor((wallX));
             int texX = (int)(wallX * (double)texture->w);
             double step = 1.0 * texture->h / lineHeight;
             double texPos = (drawStart - pitch - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
             Uint32* pixels = (Uint32*)texture->pixels;
             for(int y = drawStart; y < drawEnd; y++)
             {
                 int texY = (int)texPos & (texture->h - 1);
                 texPos += step;
                 Uint32 color = pixels[texY * texture->w + texX];
                 putpixel(screenSurface, x, y, color);
             }
        }
        SDL_UpdateWindowSurface(instance.window);
        SDL_Event event;
        while (1)
        {
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT)
                return 0;
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_m)
                {
                    if (m == 0)
                    {
                        if (init_instance(&instance2, 260, 160, "Maps") != 0)
                            return (0);
                        screenSurface2 = SDL_GetWindowSurface(instance2.window);
                        draw(screenSurface2, instance2, posX, posY);
                        m = 1;
                    }
                    else if (m == 1)
                    {
                        SDL_DestroyWindow(instance2.window);
                        m = 0;
                    }
                }
                Uint32 time = SDL_GetTicks();
                double frameTime = (time - oldTime) / 1000.0;
                oldTime = time;
                pmove(&event, &posX, &posY, dirX, dirY, &planeX, &planeY, frameTime);
                if (m == 1)
                    draw(screenSurface2, instance2, posX, posY);
                printf("finished %d\n",g);
                g++;
                SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));
                break;
            }
        }
    }
=======

int main()
{
    SDL_Instance instance;

    if (init_instance(&instance) != 0)
        return (1);
>>>>>>> 55d536e3aa3e967bc4df23e0c5f8c675942079fe
    return (0);
}
