#include "headers/handleEvents.h"

int processEvents(Agent *agent) {
    SDL_Event event;
    int done = 0;
    float normalSpeed = 3;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            done = 1;
        }
    }

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_S]) {
        normalSpeed *= 0.5;
    }
    if (keystate[SDL_SCANCODE_A]) {
        agent->x -= normalSpeed;
        agent->coll.leftEdge -= normalSpeed;
        agent->coll.rightEdge -= normalSpeed;
        agent->walking = 1;
        agent->facingLeft = 1;
    }
    else if(keystate[SDL_SCANCODE_D]) {
        agent->x += normalSpeed;
        agent->coll.leftEdge += normalSpeed;
        agent->coll.rightEdge += normalSpeed;
        agent->walking = 1;
        agent->facingLeft = 0;
    }
    else {
        agent->walking = 0;
    }

    if (keystate[SDL_SCANCODE_W] && agent->dy==0 && agent->jumpAgain==true) {
        agent->falling = true;
        agent->jumpAgain = false;
        agent->dy = -10;
    }
    
    
    

    return done;
}