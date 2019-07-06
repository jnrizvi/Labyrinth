#include "headers/handleEvents.h"

int processEvents(Agent *agent) {
    SDL_Event event;
    int done = 0;

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            done = 1;
        }
    }

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    
    if (keystate[SDL_SCANCODE_A]) {
        agent->x -= 3;
        agent->leftEdge -= 3;
        agent->rightEdge -= 3;
        agent->walking = 1;
        agent->facingLeft = 1;
    }
    else if(keystate[SDL_SCANCODE_D]) {
        agent->x += 3;
        agent->leftEdge += 3;
        agent->rightEdge += 3;
        agent->walking = 1;
        agent->facingLeft = 0;
    }
    else {
        agent->walking = 0;
    }

    if (keystate[SDL_SCANCODE_W] && agent->dy==0 && agent->jumpAgain==true) {
        agent->jumpAgain = false;
        agent->dy = -10;
    }
    
    
    // if(keystate[SDL_SCANCODE_DOWN])
    // {
    //     //agent->y += 10;  change to mario's crouch animation
    // }

    return done;
}