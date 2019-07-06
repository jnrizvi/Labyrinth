#include "physics2d.h"

void collideRect(Agent *agent, Platform *platform) {

}

void changePlatforms(Agent *agent, Platform platforms[2], int *current_platform, bool *noMorePlat) {
    bool incremented = false;
    for (int i =0; i <= *current_platform; i++) {
        if (*current_platform >= 2) {
            printf("You fell off!\n");
            *noMorePlat = true;
            *current_platform -= 1;
        }
        // printf("agent->y: %f, *current_platform: %d\n", agent->y, *current_platform);
        if (onLedge(agent, &platforms[*current_platform]) == 0) {
            // printf("remained on platform %d\n", *current_platform);
            incremented = false;
            break;
        }
        else if (onLedge(agent, &platforms[*current_platform]) == 1) {
            if (incremented == false && *current_platform <= 1) {
                // printf("*current_platform: %d\n", *current_platform);
                *current_platform += 1;
                incremented = true;
            }
        }
        
        // printf("agent->y: %f, *current_platform: %d\n", agent->y, *current_platform);
        if (*current_platform -1 >= 0) {
            // printf("agent->y: %f, *current_platform: %d\n", agent->y, *current_platform);
            if (agent->bottom <= platforms[*current_platform-1].top) {
                // jumped at the level of a platform above
                *current_platform -= 1;
            }
        }
    }
}

int onLedge(Agent *agent, Platform *platform) {
    int result;
    if ( agent->bottom >= platform->top) {
        // above/on the current platform
        if (agent->rightEdge >= platform->leftEdge && agent->leftEdge <= platform->rightEdge) {
            // remained on the current platform
            agent->y = platform->top - agent->sprite_h;
            agent->jumpAgain = true;
            agent->bottom = platform->top; 
            agent->top = agent->y;                                                                            
            agent->dy = 0;
            result = 0; 
        }
        else {
            // fell off the current platform
            result = 1;
        }    
    }
    return result;
}

void gravity(Agent *agent) {
    agent->y += agent->dy;
    agent->bottom += agent->dy;
    agent->top += agent->dy;
    agent->dy += 0.5;
}