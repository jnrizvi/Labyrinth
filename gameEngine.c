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

    // SDL_Rect brick_dest = createRect(0, 160, 32, 32);
    // Platform brick = initPlatform("imageFiles/brick.png", brick_dest, 7, renderer);

    // SDL_Rect brick1_dest = createRect(0, 192, 32, 32);
    // Platform brick1 = initPlatform("imageFiles/brick.png", brick1_dest, 7, renderer);

    // SDL_Rect brick2_dest = createRect(32, 192, 32, 32);
    // Platform brick2 = initPlatform("imageFiles/brick.png", brick2_dest, 7, renderer);

    // SDL_Rect brick3_dest = createRect(64, 192, 32, 32);
    // Platform brick3 = initPlatform("imageFiles/brick.png", brick3_dest, 7, renderer);

    

    // Platform platforms[] = {brick, brick1, brick2, brick3};   // must be sorted by platforms's y position, ascending
    // int lenPlatforms = sizeof(platforms) / sizeof(platforms[0]);
    
    int refGrid[7][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 1, 0},
        {1, 1, 1, 0}
    };

    Platform brickCoords[5] = {0};
    int index = 0;
    // int nTotal = sizeof(refGrid)/sizeof(int);
    int nColumns = sizeof(refGrid[0])/sizeof(int);
    int nRows = sizeof(refGrid)/sizeof(refGrid[0]);
    // printf("#Rows: %d, #Columns: %d\n", nRows, nColumns);
    for (int i =0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            if (refGrid[i][j] == 1) {
                // printf("j: %d, i: %d\n", j, i);
                SDL_Rect dest = createRect(j*32, i*32, 32, 32);
                brickCoords[index] = initPlatform("imageFiles/brick.png", dest, 1, renderer);
                index++;
            }
        }
    }

    int done = 0;
    int frameTime = 0;
    int current_platform = 0;
    // bool noMorePlat =false;
    int curX = 0;
    int curY = 0;
    int bCurY = 0;
    int fCurY = 0;
    
    while(done == 0) {
        done = processEvents(&player, &curX, &curY, &bCurY, &fCurY);
        printf("curX: %d, curY: %d\n", curX, curY);
        printf("Back (looking down): %d, Front (looking down): %d\n", refGrid[curX+1][bCurY], refGrid[curX+1][fCurY]);
        // printf("rightEdge: %f\n", player.coll.rightEdge);
        frameTime += 1;
        if (FPS / frameTime == 10) {
            frameTime = 0;
            updateSpriteFrame(&player);
        }
        
        // gravity(&player);
        // curX = ((player.coll.bottom) / 32)-1;
        
        // if (curX > 6) {
        //     curX = 6;
        // }
        // if ((curX < 7) && (refGrid[curX+1][curY]==0) && (player.dy > 0)) {
            // player.y += player.dy;
            // player.coll.bottom += player.dy;
            // player.coll.top += player.dy;
            // move(&player, 3, 1);
        // }
        // else if ((curX >= 0) && (player.coll.top>0) && (player.dy < 0)) {
            // player.y += player.dy;
            // player.coll.bottom += player.dy;
            // player.coll.top += player.dy;
            // move(&player, -3, 1);
        // }
        // else {
            // player.dy = 0;
            // player.jumpAgain = true;
        // }
        

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

        for (int i = 0; i < sizeof(brickCoords)/sizeof(brickCoords[0]); i++) {
            SDL_RenderCopy(renderer, brickCoords[i].pTexture, NULL, &brickCoords[i].block_dest);
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
    for (int i =0; i < sizeof(brickCoords)/sizeof(brickCoords[0]); i++) {
        SDL_DestroyTexture(brickCoords[i].pTexture);
    }
    destroyEnvironment();
    return 0;
}