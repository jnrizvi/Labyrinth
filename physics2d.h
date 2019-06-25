#ifndef PHYSICS_2D
#define PHYSICS_2D

typedef struct {
    SDL_Texture *pTexture;
} Platform;

void gravity(PC *player, Platform *nextPlatform);

#endif /* PHYSICS_2D */