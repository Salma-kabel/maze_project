#ifndef MAZE_H

#define MAZE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern int mapWidth;
extern int mapHeight;
int map_st_sp= 0;
Uint32 buffer[1260][720];
const int SCREEN_WIDTH = 1260;
const int SCREEN_HEIGHT = 720;
int **worldMap;
double depthBuffer[1260];


char *weapon[5] = {"textures/we1.png", "textures/we2.png",
	"textures/we3.png", "textures/we4.png", "textures/we6.png"};
int weapon_ch = 0, rain_st_sp = 0;
/**
* Sprite - enemies struct
* @x: x position on the map
* @y: y position on the map
*/
struct Sprite
{
  double x;
  double y;
};
struct Sprite sprite[3] =
{
 {6,3},
 {12,23},
 {20,6},
};

/**
* Raindrop - rain drops struct
* @x: x position on the map
* @y: y position on the map
* @speed: speed of falling of the raindrop
*/
typedef struct Raindrop
{
    double x, y;
    double speed;
} Raindrop;

Raindrop raindrops[1000];

/* SDL_Instance - instance of sdl
* @window: window of instance
* @renderer: renderer of instance
*/
typedef struct SDL_Instance
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Instance;
SDL_Instance instance2;
SDL_Surface *screenSurface2 = NULL;

int init_instance(SDL_Instance *instance, const int SCREEN_WIDTH,
	const int SCREEN_HEIGHT, char *name);
void map(void);
void color_pixel(SDL_Surface *surface, int x, int y, Uint32 color);
void move_rot(double *planeX, double *planeY, double *posX,
	double *posY, double *dirX, double *dirY, double frameTime);
void wall_tex(SDL_Surface *texture, double *posX, double *posY,
	double *dirX, double *dirY, double *planeX, double *planeY,
	SDL_Surface *screenSurface);
void floor_tex(double *posX, double *posY, double *dirX, double *dirY,
	double *planeX, double *planeY, SDL_Surface *screenSurface,
	SDL_Instance instance);
int **parser(char *path);
void draw(SDL_Surface *screenSurface, SDL_Instance instance,
	int posx, int posy, double dirX, double dirY);
void draw_enemies( SDL_Surface *screenSurface, double posX, double posY,
	double dirX, double dirY, double planeX, double planeY);
void draw_weapon(SDL_Surface *screenSurface, int weapon_ch);
void init_rain();
void draw_rain(SDL_Instance instance, SDL_Surface *screenSurface);
int keys(double *posX, double *posY, double *dirX, double *dirY,
	double *planeX, double *planeY, SDL_Surface *screenSurface,
	SDL_Instance instance, Uint32 *oldTime);


#endif
