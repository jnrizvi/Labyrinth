#include <stdio.h>
#include "SDL2/SDL.h"
#include <stdbool.h>
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_image.h"
#include "handleEvents.h"
#include "physics2d.h"

#define FPS 60
int eachFramex;
int eachFramey;
int sheetx;
int sheety;

SDL_Rect createRect(int x_pos, int y_pos, int width, int height) {
    SDL_Rect rect;
    rect.x = x_pos;
    rect.y = y_pos;
    rect.w = width;
    rect.h = height;
    
    return rect;
}

SDL_Texture *createTexture(char *img_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(img_name);
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}

void loopFrames(PC *player) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    
    // continuous-response keys
    if (keystate[SDL_SCANCODE_A]) {
        player->currentSprite++;
        player->currentSprite %= 3;
    }
    else if (keystate[SDL_SCANCODE_D]) {
        player->currentSprite++;
        player->currentSprite %= 3;
    }
    else {
        player->currentSprite = 0;
    }
}

void handleMovement(SDL_Rect *texture_destination, SDL_Event event) {
    
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    
    //continuous-response keys
    // maybe only push to the stack if the previously pushed key (using peak) was not the current one?
    if (keystate[SDL_SCANCODE_A]) {
        texture_destination->x -= 3;    
    }
    if (keystate[SDL_SCANCODE_D]) {
        texture_destination->x += 3;
    }
    if (keystate[SDL_SCANCODE_W]) {
        texture_destination->y -= 3;
    }
    if (keystate[SDL_SCANCODE_S]) {
        texture_destination->y += 3;
                
    }
    
}

bool keyCool(bool isCool, int timer) {
    if (isCool == true && timer > 0) {
        return true;
    }
    else {
        return false;
    }
}

int main(int argc, char** argv) {
    
    // initialize SDL video and audio systems
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    // create an SDL window
    SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);

    // create a renderer (accelerated and in-sync with the display referesh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    // turn sprite around
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    // initialize SDL mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // initialize support for loading png and jpg images
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    // load audio files
    Mix_Chunk *jumpEffect = Mix_LoadWAV("audioFiles/Jump6.wav");
    Mix_Chunk *laserEffect = Mix_LoadWAV("audioFiles/Laser_Shoot7.wav");


    PC player;
    player.x = 150;
    player.y = 150;
    player.dy = 0;
    player.currentSprite = 0;
    player.facingLeft = 0;

     // load image files
    Platform blocks;
    blocks.pTexture = createTexture("imageFiles/brick.png", renderer);
    player.sheetTexture = createTexture("imageFiles/mario.png", renderer);  

    eachFramex = 32;
    eachFramey = 64;
    sheetx = 336;
    
    // define where on the screen we want to draw the texture
    SDL_Rect player_dest = createRect(150, 150, eachFramex, eachFramey);
    SDL_Rect player_cur_sprite = createRect(eachFramex*player.currentSprite, 0, eachFramex, eachFramey);
    
    SDL_Rect block_dest = createRect(168, 350+eachFramey, 32, 32);

    int done = 0;
    
    SDL_Event event;
    
    bool cool = false;
    int coolTime;

    int frameTime = 0;
    char dir;

    while(!done) {
        
        done = processEvents(&player);
        frameTime += 1;
        if (FPS / frameTime == 10) {
            frameTime = 0;
            loopFrames(&player);
        }
        gravity(&player, &blocks);
        
        // clear screen by making it black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        
        
        // printf("currentSprite: %d\n", player.currentSprite);
        SDL_Rect player_dest = createRect(player.x, player.y, eachFramex, eachFramey);;
        SDL_Rect player_cur_sprite = createRect(eachFramex*player.currentSprite, 0, eachFramex, eachFramey);
        

        // draw an image
        SDL_RenderCopyEx(renderer, player.sheetTexture, &player_cur_sprite, &player_dest, 0, NULL, player.facingLeft);
        
        block_dest.x = 128;
        SDL_RenderCopy(renderer, blocks.pTexture, NULL, &block_dest);
        block_dest.x += 32;
        SDL_RenderCopy(renderer, blocks.pTexture, NULL, &block_dest);
        block_dest.x += 32;
        SDL_RenderCopy(renderer, blocks.pTexture, NULL, &block_dest);
        block_dest.x += 32;
        SDL_RenderCopy(renderer, blocks.pTexture, NULL, &block_dest);
        block_dest.x += 32;
        SDL_RenderCopy(renderer, blocks.pTexture, NULL, &block_dest);
        block_dest.x += 32;
        SDL_RenderCopy(renderer, blocks.pTexture, NULL, &block_dest);
        block_dest.x += 32;
        SDL_RenderCopy(renderer, blocks.pTexture, NULL, &block_dest);

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    // release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeChunk(jumpEffect);
    Mix_FreeChunk(laserEffect);
    Mix_CloseAudio();
    IMG_Quit();
    SDL_DestroyTexture(player.sheetTexture);
    SDL_DestroyTexture(blocks.pTexture);
    SDL_Quit();
    return 0;
}