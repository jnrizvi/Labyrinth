#include "headers/handleEvents.h"
#include "headers/mapEditor.h"
#include "headers/physics2d.h"
#include "utils.c"

void updateSpriteFrame(Agent *agent) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    
    // continuous-response keys
    if (keystate[SDL_SCANCODE_A]) {
        agent->currentFramex++;
        agent->currentFramex %= 3;
    }
    else if (keystate[SDL_SCANCODE_D]) {
        agent->currentFramex++;
        agent->currentFramex %= 3;
    }
    else {
        agent->currentFramex = 0;
    }
}

int main(int argc, char** argv) {
    
    initEnvironment();
    SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);

    // create a renderer (accelerated and in-sync with the display referesh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // load audio files
    Mix_Chunk *jumpEffect = Mix_LoadWAV("audioFiles/Jump6.wav");
    Mix_Chunk *laserEffect = Mix_LoadWAV("audioFiles/Laser_Shoot7.wav");
    
    
    // define where on the screen we want to draw the texture
    SDL_Rect player_dest = createRect(300, 50, 32, 64);
    Agent player = initAgent("imageFiles/mario.png", player_dest, 0, 0, 0, renderer);

    SDL_Rect brick_dest = createRect(256, 200, 32, 32);
    Platform brick = initPlatform("imageFiles/brick.png", brick_dest, 7, renderer);

    SDL_Rect brick1_dest = createRect(150, 300, 32, 32);
    Platform brick1 = initPlatform("imageFiles/brick.png", brick1_dest, 7, renderer);

    Platform platforms[2] = {brick, brick1};
    int done = 0;

    int frameTime = 0;

    int current_platform = 0;
    bool noMorePlat =false;
    
    while(done == 0) {
        
        done = processEvents(&player);
        frameTime += 1;
        if (FPS / frameTime == 10) {
            frameTime = 0;
            updateSpriteFrame(&player);
        }

        
        gravity(&player);
        if (noMorePlat == false){
            changePlatforms(&player, platforms, &current_platform, &noMorePlat);
        } 
        // else {
        //     printf("Game Over!\n");
        // }

        // clear screen by making it black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect player_dest = createRect(player.x, player.y, player.sprite_w, player.sprite_h);
        setCurrentSprite(&player, &player.currentSprite);

        // draw an image
        SDL_RenderCopyEx(renderer, player.sheetTexture, &player.currentSprite, &player_dest, 0, NULL, player.facingLeft);
        
        brick_dest.x = brick.block_dest.x;
        brick1_dest.x = brick1.block_dest.x;
        for (int i = 0; i < brick.numBlocks; i++) {
            SDL_RenderCopy(renderer, brick.pTexture, NULL, &brick_dest);
            SDL_RenderCopy(renderer, brick1.pTexture, NULL, &brick1_dest);
            brick_dest.x += brick.block_dest.w;
            brick1_dest.x += brick1.block_dest.w;
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    // release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeChunk(jumpEffect);
    Mix_FreeChunk(laserEffect);
    SDL_DestroyTexture(player.sheetTexture);
    SDL_DestroyTexture(brick.pTexture);
    destroyEnvironment();
    return 0;
}