
#include "physics2d.h"

void collideRect(Agent *agent, Platform *platform) {
    // if there's something in the way, DON'T keep falling
    // platform->top = platform->block_dest.y - agent->sprite_h;
    // platform->leftEdge = platform->block_dest.x - agent->sprite_w;
    // platform->rightEdge = (platform->block_dest.w * platform->numBlocks) + platform->block_dest.x;

    // agent->bottom
}

void changePlatforms(Agent *agent, Platform platforms[2], int *current_platform) {
    
    for (int i =0; i <= *current_platform; i++) {
        
        if (onLedge(agent, &platforms[*current_platform]) == 0) {
            break;
        }
        else if (onLedge(agent, &platforms[*current_platform]) == 1) {
            if (*current_platform < 1) {
                *current_platform += 1;
            }
        }
        if (*current_platform -1 >= 0) {
            if (agent->bottom <= platforms[*current_platform-1].top) {
                // printf("agent->y: %f, *current_platform: %d\n", agent->y, *current_platform);
                *current_platform -= 1;
            }
        }
    }
}

int onLedge(Agent *agent, Platform *platform) {
    
    // platform->top = platform->block_dest.y - agent->sprite_h;
    // platform->leftEdge = platform->block_dest.x - agent->sprite_w;
    // platform->rightEdge = (platform->block_dest.w * platform->numBlocks) + platform->block_dest.x;
    
    
    if ( agent->bottom >= platform->top && (agent->rightEdge >= platform->leftEdge && agent->leftEdge <= platform->rightEdge) ) {
        agent->y = platform->top - agent->sprite_h;
        
        agent->bottom = platform->top; 
        agent->top = agent->bottom - agent->sprite_h;
                                                                                           
        agent->dy = 0;
        return 0;
    }
    else if ( agent->bottom >= platform->top && !(agent->leftEdge >= platform->leftEdge && agent->rightEdge <= platform->rightEdge) ) {
        // printf("Beep\n");
        return 1;
    }
    return -1;
    
    
}

void gravity(Agent *agent) {
    agent->y += agent->dy;

    agent->bottom += agent->dy;
    agent->top += agent->dy;
    
    agent->dy += 0.5;
}