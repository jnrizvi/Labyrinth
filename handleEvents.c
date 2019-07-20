#include "headers/handleEvents.h"
#include "headers/physics2d.h"

int eventHandler(Agent *agent) {
    SDL_Event event;
    int done = 0;
    float normalSpeed = 1;
    
    SDL_Rect testBrick;

    testBrick.x = 352;
    testBrick.y = 224;
    testBrick.w = 32;
    testBrick.h = 32;

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            done = 1;
        }
    }

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_A]) {
        move(agent, -normalSpeed, 0);
        if (collideRect(agent, &testBrick)==1) {
            move(agent, normalSpeed, 0);
        }
        agent->facingLeft = 1;
    }
    else if (keystate[SDL_SCANCODE_D]) {
        move(agent, normalSpeed, 0);
        if (collideRect(agent, &testBrick)==1) {
            move(agent, -normalSpeed, 0);
        }
        agent->facingLeft = 0;
    }
    if (keystate[SDL_SCANCODE_W]) {
        move(agent, -normalSpeed, 1);
        if (collideRect(agent, &testBrick)==1) {
            move(agent, normalSpeed, 1);
        }
    }
    else if (keystate[SDL_SCANCODE_S]) {
        move(agent, normalSpeed, 1);
        if (collideRect(agent, &testBrick)==1) {
            move(agent, -normalSpeed, 1);
        }
    }

    return done;
}

int processEvents(Agent *agent, int *curX, int *curY) {
    SDL_Event event;
    int done = 0;
    float normalSpeed = 3;
    // int refGrid[][4] = {
    //     {0, 0, 0, 0},
    //     {0, 0, 0, 0},
    //     {0, 0, 0, 0},
    //     {0, 0, 0, 0},
    //     {0, 0, 0, 0},
    //     {1, 0, 1, 0},
    //     {1, 1, 1, 0}
    // };
    int refGrid[20][25] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    int nColumns = sizeof(refGrid[0])/sizeof(int);
    int nRows = sizeof(refGrid)/sizeof(refGrid[0]);
    
    int bCurY, fCurY, lCurX, uCurX;
    uCurX = ((agent->coll.bottom-32) / 32);

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            done = 1;
        }
    }

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    
    
    if (keystate[SDL_SCANCODE_A]) {
        agent->facingLeft = 1;
        bCurY = ((agent->coll.rightEdge) / 32);
        
        if ( fmod(agent->coll.rightEdge, 32.0)==0.0) {
            bCurY -= 1;
        }

        fCurY = ((agent->coll.leftEdge) / 32);

        if (bCurY >= nColumns) {
            bCurY = nColumns-1;
        }

        // decision function
        if (*curX +1 < nRows && uCurX -2 >= 0) {
            if (((refGrid[*curX+1][bCurY]==0) && (refGrid[*curX+1][fCurY]==0)) || ((refGrid[*curX+1][bCurY]==1) && (refGrid[*curX+1][fCurY]==1))) {
                *curY = bCurY;
                
            }
            else if ((refGrid[*curX+1][bCurY]==1) && (refGrid[*curX+1][fCurY]==0)) {
                *curY = bCurY;
            }
            if ((refGrid[*curX+1][bCurY]==0 && refGrid[*curX+1][fCurY]==1) || (refGrid[uCurX-2][bCurY]==0 && refGrid[uCurX-2][fCurY]==1)) {
                *curY = fCurY;
            }    
        } 
        else {
            if (((refGrid[*curX][bCurY]==0) && (refGrid[*curX][fCurY]==0)) || ((refGrid[*curX][bCurY]==1) && (refGrid[*curX][fCurY]==1))) {
                *curY = bCurY;
                
            }
            else if ((refGrid[*curX][bCurY]==1) && (refGrid[*curX][fCurY]==0)) {
                *curY = bCurY;
            }
            if ((refGrid[*curX][bCurY]==0 && refGrid[*curX][fCurY]==1) || (refGrid[uCurX][bCurY]==0 && refGrid[uCurX][fCurY]==1)) {
                *curY = fCurY;
            } 
        }
        
        // printf("*curX: %d, *curY: %d\n", *curX, *curY);
        // printf("Back (looking down): %d, Front (looking down): %d\n", refGrid[*curX+1][*bCurY], refGrid[*curX+1][*fCurY]);

        if (bCurY-1 >= 0 ) {
            if (refGrid[*curX][bCurY-1]==0 ) {
                // *curY = bCurY;
                
                // printf("difference: %f\n", (agent->coll.leftEdge - (*bCurY-1)*32));
                if (normalSpeed > (agent->coll.leftEdge - (bCurY-1)*32)) {
                    normalSpeed = (agent->coll.leftEdge - (bCurY-1)*32);
                }
                move(agent, -normalSpeed, 0);
            }   
        }
    }

    else if(keystate[SDL_SCANCODE_D]) {
        agent->facingLeft = 0;
        bCurY = ((agent->coll.leftEdge) / 32);
        fCurY = ((agent->coll.rightEdge-1) / 32);
        
        if (fCurY >= nColumns) {
            fCurY = nColumns-1;
        }

        if (*curX +1 < nRows && uCurX -2 >= 0) {
            if (((refGrid[*curX+1][bCurY]==0) && (refGrid[*curX+1][fCurY]==0)) || ((refGrid[*curX+1][bCurY]==1) && (refGrid[*curX+1][fCurY]==1))) {
                
                *curY = bCurY;
                
            }
            else if ((refGrid[*curX+1][bCurY]==1) && (refGrid[*curX+1][fCurY]==0)) {
                *curY = bCurY;
            }
            if ((refGrid[*curX+1][bCurY]==0 && refGrid[*curX+1][fCurY]==1) || (refGrid[uCurX-2][bCurY]==0 && refGrid[uCurX-2][fCurY]==1)) {
                *curY = fCurY;
            }
        }
        else {
            if (((refGrid[*curX][bCurY]==0) && (refGrid[*curX][fCurY]==0)) || ((refGrid[*curX][bCurY]==1) && (refGrid[*curX][fCurY]==1))) {
                *curY = bCurY;
                
            }
            else if ((refGrid[*curX][bCurY]==1) && (refGrid[*curX][fCurY]==0)) {
                *curY = bCurY;
            }
            if ((refGrid[*curX][bCurY]==0 && refGrid[*curX][fCurY]==1) || (refGrid[uCurX][bCurY]==0 && refGrid[uCurX][fCurY]==1)) {
                *curY = fCurY;
            } 
        }

        // printf("*curX: %d, *curY: %d\n", *curX, *curY);
        // printf("Back (looking down): %d, Front (looking down): %d\n", refGrid[*curX+1][*bCurY], refGrid[*curX+1][*fCurY]);
        
        if (bCurY+1 < nColumns ) {
            if (refGrid[*curX][bCurY+1]==0) {
                // *curY = bCurY;
                // printf("difference: %f\n", ((*bCurY+1)*32+32 - agent->coll.rightEdge));
                
                if (normalSpeed > ((bCurY+1)*32+32 - agent->coll.rightEdge)) {
                    normalSpeed = ((bCurY+1)*32+32 - agent->coll.rightEdge);
                }
                move(agent, normalSpeed, 0);
            }
        }
    }
    
    if (keystate[SDL_SCANCODE_W]) {
        // agent->dy = -10;
        // agent->jumpAgain = false;
        lCurX = (agent->coll.bottom / 32);
        uCurX = ((agent->coll.bottom-32) / 32);
        
        *curX = lCurX;
        
        if (uCurX-1 >= 0 ) {
            if (refGrid[uCurX-1][*curY]==0) {

                move(agent, -normalSpeed, 1);
            }
        }
    }

    else if (keystate[SDL_SCANCODE_S]) {
        lCurX = ((agent->coll.bottom-1) / 32);
        uCurX = ((agent->coll.bottom-32) / 32);

        *curX = lCurX;

        if (*curX >= nRows) {
            *curX = nRows-1;
        }

        printf("lCurX: %d\n", lCurX);
        if (uCurX+1 < nRows) {
            // printf("can move down\n");
            if (refGrid[uCurX+1][*curY]==0 ) {
                
                move(agent, normalSpeed, 1);
            }
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


