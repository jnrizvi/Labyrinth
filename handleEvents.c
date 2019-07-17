#include "headers/handleEvents.h"

int processEvents(Agent *agent, int *curX, int *curY, int *bCurY, int *fCurY) {
    SDL_Event event;
    int done = 0;
    float normalSpeed = 3;
    int refGrid[][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 1, 0},
        {1, 1, 1, 0}
    };
    
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            done = 1;
        }
    }

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    
    
    if (keystate[SDL_SCANCODE_A]) {
        agent->facingLeft = 1;
        *bCurY = ((agent->coll.rightEdge) / 32);
        // printf("value: %f\n", fmod(agent->coll.rightEdge, 32.0));
        
        if ( fmod(agent->coll.rightEdge, 32.0)==0.0) {
            // printf("boop.\n");
            *bCurY -= 1;
        }

        // printf("value: %f\n", fmod(agent->coll.leftEdge, 32.0));
        *fCurY = ((agent->coll.leftEdge) / 32);

        if (*bCurY > 3) {
            *bCurY = 3;
        }

        // decision function
        if (*curX +1 <= 6) {
            if (((refGrid[*curX+1][*bCurY]==0) && (refGrid[*curX+1][*fCurY]==0)) || ((refGrid[*curX+1][*bCurY]==1) && (refGrid[*curX+1][*fCurY]==1))) {
                *curY = *bCurY;
                
            }
            else if ((refGrid[*curX+1][*bCurY]==1) && (refGrid[*curX+1][*fCurY]==0)) {
                *curY = *bCurY;
            }
            else if ((refGrid[*curX+1][*bCurY]==0) && (refGrid[*curX+1][*fCurY]==1)) {
                *curY = *fCurY;
            }    
        } 
        else {
            if (((refGrid[*curX][*bCurY]==0) && (refGrid[*curX][*fCurY]==0)) || ((refGrid[*curX][*bCurY]==1) && (refGrid[*curX][*fCurY]==1))) {
                *curY = *bCurY;
                
            }
            else if ((refGrid[*curX][*bCurY]==1) && (refGrid[*curX][*fCurY]==0)) {
                *curY = *bCurY;
            }
            else if ((refGrid[*curX][*bCurY]==0) && (refGrid[*curX][*fCurY]==1)) {
                *curY = *fCurY;
            } 
        }
        
        // printf("*curX: %d, *curY: %d\n", *curX, *curY);
        // printf("Back (looking down): %d, Front (looking down): %d\n", refGrid[*curX+1][*bCurY], refGrid[*curX+1][*fCurY]);

        // if ((*fCurY >= 0 && agent->coll.leftEdge-normalSpeed>0) ) {
        if (*bCurY-1 >= 0 ) {
            if (refGrid[*curX][*bCurY-1]==0 ) {  // MUST ADJUST normalSpeed: to get the exact value at which remaider will be 0.0
                *curY = *bCurY;
                printf("difference: %f\n", (agent->coll.leftEdge - (*bCurY-1)*32));
                if (normalSpeed > (agent->coll.leftEdge - (*bCurY-1)*32)) {
                    normalSpeed = (agent->coll.leftEdge - (*bCurY-1)*32);
                }
                move(agent, -normalSpeed, 0);
            }   
        }
    }

    else if(keystate[SDL_SCANCODE_D]) {
        agent->facingLeft = 0;
        *bCurY = ((agent->coll.leftEdge) / 32);
        *fCurY = ((agent->coll.rightEdge) / 32);
        
        if (*fCurY > 3) {
            *fCurY = 3;
        }

        if (*curX +1 <= 6) {
            if (((refGrid[*curX+1][*bCurY]==0) && (refGrid[*curX+1][*fCurY]==0)) || ((refGrid[*curX+1][*bCurY]==1) && (refGrid[*curX+1][*fCurY]==1))) {
                
                *curY = *bCurY;
                
            }
            else if ((refGrid[*curX+1][*bCurY]==1) && (refGrid[*curX+1][*fCurY]==0)) {
                *curY = *bCurY;
            }
            else if ((refGrid[*curX+1][*bCurY]==0) && (refGrid[*curX+1][*fCurY]==1)) {
                *curY = *fCurY;
            }
        }
        else {
            if (((refGrid[*curX][*bCurY]==0) && (refGrid[*curX][*fCurY]==0)) || ((refGrid[*curX][*bCurY]==1) && (refGrid[*curX][*fCurY]==1))) {
                *curY = *bCurY;
                
            }
            else if ((refGrid[*curX][*bCurY]==1) && (refGrid[*curX][*fCurY]==0)) {
                *curY = *bCurY;
            }
            else if ((refGrid[*curX][*bCurY]==0) && (refGrid[*curX][*fCurY]==1)) {
                *curY = *fCurY;
            } 
        }

        // printf("*curX: %d, *curY: %d\n", *curX, *curY);
        // printf("Back (looking down): %d, Front (looking down): %d\n", refGrid[*curX+1][*bCurY], refGrid[*curX+1][*fCurY]);
        
        if (*bCurY+1 < 4 ) {
            if (refGrid[*curX][*bCurY+1]==0) {
                *curY = *bCurY;
                // printf("difference: %f\n", ((*bCurY+1)*32+32 - agent->coll.rightEdge));
                if (normalSpeed > ((*bCurY+1)*32+32 - agent->coll.rightEdge)) {
                    normalSpeed = ((*bCurY+1)*32+32 - agent->coll.rightEdge);
                }
                move(agent, normalSpeed, 0);
            }
        }
    }
    
    if (keystate[SDL_SCANCODE_W]) {
        // agent->dy = -10;
        // agent->jumpAgain = false;
        *curX = ((agent->coll.top) / 32);
        
        if ((*curX >= 0) && (agent->coll.top>0) ) {
            move(agent, -normalSpeed, 1);
        }
    }

    else if (keystate[SDL_SCANCODE_S]) {
        *curX = ((agent->coll.bottom) / 32);
        if (*curX > 6) {
            *curX = 6;
        }
        if ((*curX < 7) && (agent->coll.bottom+normalSpeed<=224)) {
            move(agent, normalSpeed, 1);
        }
    }

    return done;
}

void move(Agent *agent, int distance, int dir) {
    if (dir == 0) {
        if (distance>0) {
            agent->facingLeft = 0;
        }
        else {
            agent->facingLeft = 1;
        }
        agent->x += distance;
        agent->coll.leftEdge += distance;
        agent->coll.rightEdge += distance;
    }
    else {
        agent->y += distance;
        agent->coll.top += distance;
        agent->coll.bottom += distance;
        
    }
}


