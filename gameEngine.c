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
    // if (keystate[SDL_SCANCODE_S]) {
    //     agent->currentFramex = 6;

    // }
    
}

int main(int argc, char** argv) {
    
    initEnvironment();
    SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, SDL_WINDOW_OPENGL);

    // create a renderer (accelerated and in-sync with the display referesh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // load audio files
    Mix_Chunk *jumpEffect = Mix_LoadWAV("audioFiles/Jump6.wav");
    Mix_Chunk *laserEffect = Mix_LoadWAV("audioFiles/Laser_Shoot7.wav");
    
    SDL_Rect player_dest;
    Agent player;

    int refGrid[20][25] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    Platform *brickCoords = malloc(sizeof(Platform));
    Coll *allRects = malloc(sizeof(Coll));
    int index = 0;
    int numRects = 0;
    // int nTotal = sizeof(refGrid)/sizeof(int);
    int nColumns = sizeof(refGrid[0])/sizeof(int);
    int nRows = sizeof(refGrid)/sizeof(refGrid[0]);
    // printf("#Rows: %d, #Columns: %d\n", nRows, nColumns);
    for (int i =0; i < nRows; i++) {
        for (int j = 0; j < nColumns; j++) {
            if (refGrid[i][j] == 1) {
                Platform *temp = (Platform*)realloc(brickCoords, ((index+2)*sizeof(Platform)));
                if (temp != NULL) {
                    brickCoords =temp;
                }
                else {
                    printf("realloc failed\n");
                }
                // printf("j: %d, i: %d\n", j, i);
                SDL_Rect dest = createRect(j*32, i*32, 32, 32);
                brickCoords[index] = initPlatform("imageFiles/brick.png", dest, 1, renderer);

                allRects = (Coll*)realloc(allRects, ((numRects+2)*sizeof(Coll)));
                allRects[numRects] = brickCoords[index].coll;
                numRects++;

                index++;
            }
            else if (refGrid[i][j] == 2) {
                player_dest = createRect(j*32, i*32, 32, 64);
                player = initAgent("imageFiles/mario.png", player_dest, 0, 0, 0, renderer);

                allRects = (Coll*)realloc(allRects, ((numRects+2)*sizeof(Coll)));
                allRects[numRects] = player.coll;
                numRects++;
            }
        }
    }
    // printf("Index: %d\n", index);
    // printf("numRects: %d\n", numRects);
    int done = 0;
    int frameTime = 0;
    
    // Coll testBrick;

    // testBrick.leftEdge = 352;
    // testBrick.top = 224;
    // testBrick.rightEdge = 384;
    // testBrick.bottom = 256;
    
    int sum;
    
    while(done == 0) {
        float curr[4] = {0, 0, 0, 0};
        float reve[4] = {0, 0, 0, 0};
        done = eventHandler(&player);
        // move(&player, collideRect(player.coll, testBrick));
        allRects[0] = player.coll;
        sum = 0;  
              
        for (int i = 0; i < 1; i++) {
            // int r = numRects-1;
            for (int j = i+1; j < numRects; j++) {
                // comparison of two rectangles (for collision) go here
                // printf("before - right: %0.1f left: %0.1f top: %0.1f bottom: %0.1f\n", allRects[i].rightEdge, allRects[i].leftEdge, allRects[i].top, allRects[i].bottom);
                printf("j: %d j-1: %d\n", j, j-1);
                int currCount = 0;
                int reveCount = 0;
                memcpy(curr, collideRect(allRects[i], allRects[j]), sizeof(curr));
                if (j-1 >= 1) {
                    memcpy(reve, collideRect(allRects[i], allRects[j-1]), sizeof(reve));
                }

                for (int k = 0; k < 4; k++) {
                    if (curr[k] != 0) {
                        currCount += 1;
                    }
                    if (reve[k] != 0) {
                        reveCount += 1;
                    }
                }

                if (currCount > 1 && reveCount <= 1) {
                    memcpy(curr, reve, sizeof(reve));
                }

                if (curr[0] != 0) {
                    allRects[i].leftEdge += -curr[0];
                    allRects[i].rightEdge += -curr[0];
                }
                if (curr[1] != 0) {
                    allRects[i].leftEdge += curr[1];
                    allRects[i].rightEdge += curr[1];
                }
                if (curr[2] != 0) {
                    allRects[i].top += -curr[2];
                    allRects[i].bottom += -curr[2];
                }
                if (curr[3] != 0) {
                    allRects[i].top += curr[3];
                    allRects[i].bottom += curr[3];   
                }
                move(&player, curr);
                // r--;
                // printf("after - right: %0.1f left: %0.1f top: %0.1f bottom: %0.1f\n", allRects[i].rightEdge, allRects[i].leftEdge, allRects[i].top, allRects[i].bottom);
                sum += 1;
            }
               
        }

        // printf("sum: %d\n", sum);


        frameTime += 1;
        if (FPS / frameTime == 10) {
            frameTime = 0;
            updateSpriteFrame(&player);
        }
        
        // clear screen by making it black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        player_dest = createRect(player.x, player.y, player.sprite_w, player.sprite_h);
        setCurrentSprite(&player, &player.currentSprite);

        SDL_RenderCopyEx(renderer, player.sheetTexture, &player.currentSprite, &player_dest, 0, NULL, player.facingLeft);

        for (int i = 0; i < index; i++) {
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
    free(brickCoords);
    free(allRects);
    destroyEnvironment();
    return 0;
}