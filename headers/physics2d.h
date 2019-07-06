#ifndef PHYSICS_2D
#define PHYSICS_2D

#include "resources.h"

void collideRect(Agent *agent, Platform *platform);
void changePlatforms(Agent *agent, Platform platforms[2], int *current_platform, bool *noMorePlat);
int onLedge(Agent *agent, Platform *platform);
void gravity(Agent *agent);

#endif /* PHYSICS_2D */