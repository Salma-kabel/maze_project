#include "maze.h"


int main()
{
    SDL_Instance instance;

    if (init_instance(&instance) != 0)
        return (1);
    return (0);
}
