#include "headers/physics2d.h"

void collideRect(Agent *agent, Platform *platform) {

}

int changePlatforms(Agent *agent, Platform platforms[], int current_platform, bool *noMorePlat, int lenPlatforms) {
    bool incremented = false;
    // printf("lenPlatforms: %d\n", lenPlatforms);
    int index = current_platform;
    for (int i =0; i <= index; i++) {
        if (index >= lenPlatforms+1) {
            printf("You fell off!\n");
            *noMorePlat = true;
            index -= 1;
        }
        printf("hello\n");
        // printf("agent->y: %f, *current_platform: %d\n", agent->y, *current_platform);
        // printf("agent->x: %f\n", agent->x);
        // bump(agent, &platforms[*current_platform]);
        if (onLedge(agent, &platforms[index]) == 0) {
            // printf("remained on platform %d\n", *current_platform);
            incremented = false;
            break;
        }
        else if (onLedge(agent, &platforms[index]) == 1) {
            if (incremented == false && index <= lenPlatforms) {
                // printf("*current_platform: %d\n", *current_platform);
                index += 1;
                incremented = true;
            }
        }
        
        // printf("agent->y: %f, *current_platform: %d\n", agent->y, *current_platform);
        if (index -1 >= 0) {
            // printf("agent->y: %f, *current_platform: %d\n", agent->y, *current_platform);
            if (agent->coll.bottom <= platforms[index-1].coll.top) {
                // jumped at the level of a platform above
                index -= 1;
            }
            
        }
    }
    return index;
}

void bump(Agent *agent, Platform *platform) {
    if ( (agent->coll.leftEdge <= 300) ) {
    // if ((platform->coll.top - agent->coll.top) < agent->sprite_h && (agent->coll.leftEdge <= platform->coll.rightEdge)) {
        // if (agent->coll.leftEdge <= platform->coll.rightEdge) {
        // agent->x = platform->coll.rightEdge;
        agent->x = 300;
        // }
    }
    else if ((agent->coll.bottom - platform->coll.bottom) < agent->sprite_h && (agent->coll.rightEdge >= platform->coll.leftEdge)) {

    }
}

int onLedge(Agent *agent, Platform *platform) {
    int result;
    if ( agent->coll.bottom >= platform->coll.top) {
        // above/on the current platform
        if (agent->coll.rightEdge >= platform->coll.leftEdge && agent->coll.leftEdge <= platform->coll.rightEdge) {
            // remained on the current platform
            agent->y = platform->coll.top - agent->sprite_h;
            agent->jumpAgain = true;
            agent->coll.bottom = platform->coll.top; 
            agent->coll.top = agent->y;                                                                            
            agent->dy = 0;
            agent->falling = false;
            result = 0; 
        }
        else {
            // fell off the current platform
            agent->falling = true;
            result = 1;
        }    
    }
    return result;
}

void gravity(Agent *agent, float *refY) {
    
    agent->y += agent->dy;
    agent->coll.bottom += agent->dy;
    agent->coll.top += agent->dy;
    *refY += agent->dy;
    agent->dy += 0.5;
}

