#include "handleEvents.h"

typedef struct {
    SDL_Texture *pTexture;
    SDL_Rect block_dest;
    int numBlocks;                        // how many blocks of platform you want to make (i.e. 1, 2, etc.)
    int leftEdge;                        // leftEdge = block_dest.x - player.sprite_w
    int rightEdge;                      // rightEdge = (block_dest.w * numBlocks) + player.sprite_w
    int top;                           // top = block_dest.y - player.sprite_h
    int bottom;                       // bottom = block_dest.y + block_dest.h
    
} Platform;

Platform initPlatform(char* textureName, SDL_Rect block_dest, int numBlocks, SDL_Renderer *renderer);
SDL_Texture *createTexture(char *img_name, SDL_Renderer *renderer);