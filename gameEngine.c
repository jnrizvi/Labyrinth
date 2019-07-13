#include "headers/handleEvents.h"
#include "headers/mapEditor.h"
#include "headers/physics2d.h"
#include "utils.c"

void updateSpriteFrame(Agent *agent) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    
    // continuous-response keys
    if (keystate[SDL_SCANCODE_A]) {
        // agent->currentFramey = 1;
        agent->currentFramex++;
        agent->currentFramex %= 3;
        agent->currentFramex++;
    }
    else if (keystate[SDL_SCANCODE_D]) {
        // agent->currentFramey = 1;
        agent->currentFramex++;
        agent->currentFramex %= 3;
        agent->currentFramex++;
    }
    else {
        // agent->currentFramey = 0;
        agent->currentFramex++;
        agent->currentFramex = 0;
    }
    if (keystate[SDL_SCANCODE_S]) {
        agent->currentFramex = 6;

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
    

    SDL_Rect player_dest = createRect(0, 0, 32, 64);
    Agent player = initAgent("imageFiles/mario.png", player_dest, 0, 0, 0, renderer);

    SDL_Rect brick_dest = createRect(96, 64, 32, 32);
    Platform brick = initPlatform("imageFiles/brick.png", brick_dest, 7, renderer);

    SDL_Rect brick1_dest = createRect(64, 68, 32, 32);
    Platform brick1 = initPlatform("imageFiles/brick.png", brick1_dest, 7, renderer);

    SDL_Rect brick2_dest = createRect(32, 66, 32, 32);
    Platform brick2 = initPlatform("imageFiles/brick.png", brick2_dest, 7, renderer);

    SDL_Rect brick3_dest = createRect(0, 64, 32, 32);
    Platform brick3 = initPlatform("imageFiles/brick.png", brick3_dest, 7, renderer);

    

    Platform platforms[] = {brick, brick1, brick2, brick3};   // must be sorted by platforms's y position, ascending
    int lenPlatforms = sizeof(platforms) / sizeof(platforms[0]);
    
    int refGrid[][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 0}
    };
    int done = 0;
    int frameTime = 0;
    int current_platform = 0;
    bool noMorePlat =false;
    float refX = 0;
    float refY = 0;
    int curX =0;
    int curY = 0;
    int delay = 0;
    while(done == 0) {
        done = processEvents(&player, &curX, &curY, &delay);
        printf("curX: %d, curY: %d\n", curX, curY);
        frameTime += 1;
        if (FPS / frameTime == 10) {
            frameTime = 0;
            updateSpriteFrame(&player);
        }
        
        // gravity(&player, &refY);
        
        

        // if (noMorePlat == false){
        //     current_platform = changePlatforms(&player, platforms, current_platform, &noMorePlat, lenPlatforms);
        // }
        
        // clear screen by making it black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect player_dest = createRect(player.x, player.y, player.sprite_w, player.sprite_h);
        setCurrentSprite(&player, &player.currentSprite);

        SDL_RenderCopyEx(renderer, player.sheetTexture, &player.currentSprite, &player_dest, 0, NULL, player.facingLeft);
        
        // for (int i = 0; i < lenPlatforms; i++) {           // through the platforms array
        //     for (int j = 0; j < platforms[i].numBlocks; j++) {
        //         SDL_RenderCopy(renderer, platforms[i].pTexture, NULL, &platforms[i].block_dest);
        //         platforms[i].block_dest.x += platforms[i].block_dest.w;
        //     }  
        // }
        // for (int h = 0; h < lenPlatforms; h++) {
        //     platforms[h].block_dest.x -= (platforms[h].block_dest.w * platforms[h].numBlocks);
        // }

        SDL_RenderCopy(renderer, platforms[0].pTexture, NULL, &platforms[0].block_dest);
        SDL_RenderCopy(renderer, platforms[1].pTexture, NULL, &platforms[1].block_dest);
        SDL_RenderCopy(renderer, platforms[2].pTexture, NULL, &platforms[2].block_dest);
        SDL_RenderCopy(renderer, platforms[3].pTexture, NULL, &platforms[3].block_dest);
        
        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    // release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeChunk(jumpEffect);
    Mix_FreeChunk(laserEffect);
    SDL_DestroyTexture(player.sheetTexture);
    for (int i =0; i < lenPlatforms; i++) {
        SDL_DestroyTexture(platforms[i].pTexture);
    }
    destroyEnvironment();
    return 0;
}