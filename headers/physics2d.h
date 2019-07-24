#ifndef PHYSICS_2D
#define PHYSICS_2D

#include "resources.h"

float *collideRect(Agent *rect1, SDL_Rect *rect2);
void bump(Agent *agent, Platform *platform);
int changePlatforms(Agent *agent, Platform platforms[], int current_platform, bool *noMorePlat, int lenPlatforms);
int onLedge(Agent *agent, Platform *platform);
void gravity(Agent *agent);

#endif /* PHYSICS_2D */