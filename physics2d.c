#include "handleEvents.h"
#include "physics2d.h"

void gravity(Agent *agent, Platform *nextPlatform) {
    nextPlatform->leftEdge = nextPlatform->block_dest.x - agent->sprite_w;
    nextPlatform->rightEdge = (nextPlatform->block_dest.w * nextPlatform->numBlocks) + nextPlatform->block_dest.x;
    nextPlatform->top = nextPlatform->block_dest.y - agent->sprite_h;

    agent->y += agent->dy;
    agent->dy += 0.5;

    if(agent->y > nextPlatform->top && (agent->x > nextPlatform->leftEdge && agent->x < nextPlatform->rightEdge)) {     // collision condition...
        agent->y = nextPlatform->top;                                                                                    // behavior if collided
        agent->dy = 0;
    }
}