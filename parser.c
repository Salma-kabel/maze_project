#include "maze.h"


int **parser(char *path)
{
	int i, j, c;
	FILE *ptr;
	ptr = fopen(path,"r");
	if(ptr == NULL)
	{
		printf("Error!");
		return (NULL);
	}
	while ((c = fgetc(ptr)) != EOF)
	{
		if (c == '\n')
		mapWidth++;
		else if (mapWidth == 1)
		mapHeight++;
	}
	rewind(ptr);
	worldMap = malloc(sizeof(int *) * mapWidth);
	if (worldMap == NULL)
		return (0);
	for (i = 0; i < mapWidth; i++)
	{
		worldMap[i] = malloc(sizeof(int) * mapHeight);
		if (worldMap[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(worldMap[j]);
			free(worldMap);
			fclose(ptr);
			return (NULL);
		}
		for (j = 0; j < mapHeight; j++)
		{
			worldMap[i][j] = fgetc(ptr) - 48;
		}
		fgetc(ptr);
	}
	fclose(ptr);
	return (worldMap);
}

