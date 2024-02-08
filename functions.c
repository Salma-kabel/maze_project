#include "maze.h"



void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    switch(bpp) 
	{
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;
    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void pmove(SDL_Event *event, double *posX, double *posY, double dirX, double dirY, double *planeX, double *planeY, double frameTime)
{
    double moveSpeed = frameTime * 1.5;
    double rotSpeed =  frameTime * 0.5;
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_w:
                if(worldMap[(int)(*posX + dirX * moveSpeed)][(int)(*posY)] == false) *posX += dirX * moveSpeed;
                break;
            case SDLK_s:
                if(worldMap[(int)(*posX - dirX * moveSpeed)][(int)(*posY)] == false) *posX -= dirX * moveSpeed;
                break;
            case SDLK_a:
                if(worldMap[(int)(*posX)][(int)(*posY + dirY * moveSpeed)] == false) *posY += dirX * moveSpeed;
                break;
            case SDLK_d:
                if(worldMap[(int)(*posX)][(int)(*posY - dirY * moveSpeed)] == false) *posY -= dirX * moveSpeed;
                break;
        }
    }
}
