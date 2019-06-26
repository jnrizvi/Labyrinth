#include "mapEditor.h"

// mapEditor.c should use gravity()

Platform initPlatform(char* textureName, SDL_Rect block_dest, int numBlocks, SDL_Renderer *renderer) {
    Platform platform;
    platform.pTexture = createTexture(textureName, renderer);
    platform.block_dest = block_dest;
    platform.numBlocks = numBlocks;
    platform.bottom = platform.block_dest.y + platform.block_dest.h;

    return platform;
}

SDL_Texture *createTexture(char *img_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(img_name);
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}