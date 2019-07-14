#ifndef RESOURCES
#define RESOURCES

#include <stdio.h>
#include "SDL2/SDL.h"
#include <stdbool.h>
#include <math.h>
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_image.h"

#define FPS 60

typedef struct {
    float leftEdge;
    float rightEdge;
    float top;
    float bottom;
} Coll;

typedef struct {
    float x, y, dy;
    int currentFramex;
    int currentFramey;
    int walking;
    bool falling;
    int facingLeft;
    bool jumpAgain;
    int sprite_w, sprite_h;
    SDL_Texture *sheetTexture;
    SDL_Rect currentSprite;
    Coll coll;
} Agent;

typedef struct {
    SDL_Texture *pTexture;
    SDL_Rect block_dest;
    int numBlocks;                          // how many blocks of platform you want to make (i.e. 1, 2, etc.)
    Coll coll;                     
} Platform;

typedef struct {
    float x;
    float y;
    float w;
    float h;
} Float_Rect;



// int processEvents(Agent *agent);

#endif /* RESOURCES */