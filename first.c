#include "maze.h"

/**
* init_instance - Used to initialize sdl instance and create window and renderer
* @instance: pointer to instance to initialize
* @SCREEN_WIDTH: width of the created window
* @SCREEN_HEIGHT: height of the created window
* @name: name of the created window
* Return: 0 if success 1 otherwise
*/

int init_instance(SDL_Instance *instance, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, char *name)
{
    printf("Initializing SDL...\n");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return (1);
    }
    printf("Creating window...\n");
    instance->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (instance->window == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }
    printf("Creating renderer...\n");
    instance->renderer = SDL_CreateRenderer(instance->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (instance->renderer == NULL)
    {
        SDL_DestroyWindow(instance->window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }
    printf("Initialization successful!\n");
    return (0);
}

