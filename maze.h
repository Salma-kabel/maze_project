#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
<<<<<<< HEAD
#include <stdbool.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern int **worldMap;
extern int mapWidth;
extern int mapHeight;
=======

>>>>>>> 55d536e3aa3e967bc4df23e0c5f8c675942079fe

typedef struct SDL_Instance
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Instance;

<<<<<<< HEAD
int init_instance(SDL_Instance *instance, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, char *name);
void map(void);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void pmove(SDL_Event *event, double *posX, double *posY, double dirX, double dirY, double *planeX, double *planeY, double frameTime);
void rotation(SDL_Event *event, double *posX, double *posY, double dirX, double dirY, double *planeX, double *planeY, double frameTime);
void floor_tex(double *posX, double *posY, double dirX, double dirY, double *planeX, double *planeY, SDL_Surface* screenSurface, SDL_Instance instance);
int **parser(char *path);
void draw(SDL_Surface *screenSurface, SDL_Instance instance, int posx, int posy);
=======
int init_instance(SDL_Instance *);
>>>>>>> 55d536e3aa3e967bc4df23e0c5f8c675942079fe

#endif
