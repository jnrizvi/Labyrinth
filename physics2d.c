
#include "physics2d.h"

void collideRect(Agent *agent, Platform *platform) {

}

void changePlatforms(Agent *agent, Platform platforms[2], int *current_platform, bool *noMorePlat) {
    for (int i =0; i <= *current_platform; i++) {
        // printf("agent->y: %f, *current_platform: %d\n", agent->y, *current_platform);
        // printf("*current_platform: %d\n", *current_platform);
        if (onLedge(agent, &platforms[*current_platform]) == 0) {
            // remained on the current platform
            break;
        }
        else if (onLedge(agent, &platforms[*current_platform]) == 1) {
            // fell off the current platform
            if (*current_platform < 1) {
                *current_platform += 1;
            }
            if (*current_platform > 1) {
                printf("You fell off!\n");
                *noMorePlat = true;
            }
            
        }
        
        // printf("agent->y: %f, *current_platform: %d\n", agent->y, *current_platform);
        if (*current_platform -1 >= 0) {
            printf("agent->y: %f, *current_platform: %d\n", agent->y, *current_platform);
            if (agent->bottom <= platforms[*current_platform-1].top) {
                // jumped onto a platform above
                *current_platform -= 1;
            }
        }
    }
}

int onLedge(Agent *agent, Platform *platform) {
    int result;
    // printf("platform->top: %f\n", platform->top);
    if ( agent->bottom >= platform->top) {
        if (agent->rightEdge >= platform->leftEdge && agent->leftEdge <= platform->rightEdge) {
            agent->y = platform->top - agent->sprite_h;
            
            agent->bottom = platform->top; 
            
            agent->top = agent->y;
            // printf("agent->top: %f\n", agent->top);                                                                                
            agent->dy = 0;
            result = 0; 
        }
        else {
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