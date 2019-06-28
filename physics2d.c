
#include "physics2d.h"

int onLedge(Agent *agent, Platform *platform) {
    

    
    platform->top = platform->block_dest.y - agent->sprite_h;
    platform->leftEdge = platform->block_dest.x - agent->sprite_w;
    platform->rightEdge = (platform->block_dest.w * platform->numBlocks) + platform->block_dest.x;
    
    
    if ( agent->y >= platform->top && (agent->x >= platform->leftEdge && agent->x <= platform->rightEdge) ) {
        agent->y = platform->top;                                                                                    
        agent->dy = 0;
        return 0;
    }
    else if (agent->y >= platform->top && !(agent->x >= platform->leftEdge && agent->x <= platform->rightEdge) ) {
        // printf("Beep\n");
        return 1;
    }
    return -1;
    
    
}

void gravity(Agent *agent) {
    agent->y += agent->dy;
    agent->dy += 0.5;
}