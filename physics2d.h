#ifndef PHYSICS_2D
#define PHYSICS_2D

#include "mapEditor.h"

int changePlatforms(Agent *agent, Platform platforms[2], int *current_platform);
int onLedge(Agent *agent, Platform *platform);
void gravity(Agent *agent);

#endif /* PHYSICS_2D */