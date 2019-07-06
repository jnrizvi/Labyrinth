#ifndef RESOURCES
#define RESOURCES

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
    float bottom;
    float top;
    float rightEdge;
    float leftEdge;
    int currentFramex;
    int currentFramey;
    int walking;
    int facingLeft;
    int sprite_w, sprite_h;
    SDL_Texture *sheetTexture;
    SDL_Rect currentSprite;
} Agent;

typedef struct {
    SDL_Texture *pTexture;
    SDL_Rect block_dest;
    int numBlocks;                          // how many blocks of platform you want to make (i.e. 1, 2, etc.)
    float leftEdge;                        // leftEdge = block_dest.x - player.sprite_w
    float rightEdge;                      // rightEdge = (block_dest.w * numBlocks) + block_dest.x
    float top;                           // top = block_dest.y - player.sprite_h
    float bottom;                       // bottom = block_dest.y + block_dest.h
} Platform;


int processEvents(Agent *agent);

#endif /* RESOURCES */