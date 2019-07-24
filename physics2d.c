#include "headers/physics2d.h"

float *collideRect(Agent *rect1, SDL_Rect *rect2) {
    // int collided;
    
    // printf("%f should be >= %d\n", rect1->coll.leftEdge, (rect2->x + rect2->w));  // if B exceeds A by 32, then B, C, D are irrelevant and A is relevant
    // printf("%f should be <= %d\n", rect1->coll.rightEdge, rect2->x);             //  if A exceeds B by 32, then A, C, D are irrelevant and B is relevant
    // printf("%f should be >= %d\n", rect1->coll.top, (rect2->y + rect2->h));     //   if D exceeds C by 32+32, then D, B, A are irrelevant and C is relevant
    // printf("%f should be <= %d\n", rect1->coll.bottom, rect2->y);              //    if C exceeds D by 32+32, then C, B, A are irrelevant and D is relevant

    int A = fabsf(rect1->coll.leftEdge - (rect2->x + rect2->w));
    int B = fabsf(rect2->x - rect1->coll.rightEdge);
    int C = fabsf(rect1->coll.top - (rect2->y + rect2->h));
    int D = fabsf(rect2->y - rect1->coll.bottom);

    float toReturn[4] = {A, B, C, D};
    float min = A;
    // float temp;
    
    if ((rect1->coll.leftEdge < rect2->x + rect2->w) && (rect1->coll.rightEdge > rect2->x) && (rect1->coll.top < rect2->y + rect2->h) && (rect1->coll.bottom > rect2->y)) {
        // collision detected!
        // printf("Collision!\n");
        
        for (int i = 0; i < 4; i++) {
            if (toReturn[i] <= min) {
                min = toReturn[i];
            }
        }
        for (int j = 0; j < 4; j++) {
            if (toReturn[j] != min) {
                toReturn[j] = 0;
            }
            else {
                toReturn[j] = -toReturn[j];
            }
        }
        // printf("min: %f\n", min);

        // printf("A: %f\n", toReturn[0]);
        // printf("B: %f\n", toReturn[1]);
        // printf("C: %f\n", toReturn[2]);
        // printf("D: %f\n", toReturn[3]);

        // collided = min;
    }
    else {
        // printf("\n");
        // collided = 0;
        for (int i = 0; i < 4; i++) {
            toReturn[i] = 0;
        }
    }
    // if rect1 and rect2 are both static, there's no need to check collisions between them. No adjustment for either rects
    // if rect1 is dynamic and rect2 is static, rect1 is adjusted (simpleStop).
    float *p = toReturn;
    return p;
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

void gravity(Agent *agent) {
    
    // agent->y += agent->dy;
    // agent->coll.bottom += agent->dy;
    // agent->coll.top += agent->dy;
    
    agent->dy += 0.5;
}

