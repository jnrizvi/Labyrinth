#ifndef HANDLE_EVENTS
#define HANDLE_EVENTS

#include <stdio.h>
#include "SDL2/SDL.h"
#include <stdbool.h>
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_image.h"

#define FPS 60

int eachFramex;
int eachFramey;

typedef struct {
    float x, y, dy;
    int currentFramex;
    int currentFramey;
    int walking;
    int facingLeft;
    int sprite_w, sprite_h;
    SDL_Texture *sheetTexture;
    SDL_Rect currentSprite;
} Agent;

int processEvents(Agent *agent);

#endif /* HANDLE_EVENTS */