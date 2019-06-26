#include "handleEvents.h"
#include "physics2d.h"



SDL_Rect createRect(int x_pos, int y_pos, int width, int height) {
    SDL_Rect rect;
    rect.x = x_pos;
    rect.y = y_pos;
    rect.w = width;
    rect.h = height;
    
    return rect;
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
    player.sheetTexture = createTexture("imageFiles/mario.png", renderer);  

    player.sprite_w = 32;
    player.sprite_h = 64;
    eachFramex = 32;
    eachFramey = 64;
    
    // define where on the screen we want to draw the texture
    SDL_Rect player_dest = createRect(150, 75, eachFramex, eachFramey);
    SDL_Rect player_cur_sprite = createRect(eachFramex*player.currentSprite, 0, eachFramex, eachFramey);
    

    SDL_Rect block_dest = createRect(128, 200, 32, 32);
    Platform blocks = initPlatform("imageFiles/brick.png", block_dest, 8, renderer);

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
        
        block_dest.x = blocks.block_dest.x;
        
        for (int i = 0; i < blocks.numBlocks; i++) {
            SDL_RenderCopy(renderer, blocks.pTexture, NULL, &block_dest);
            block_dest.x += blocks.block_dest.w;
        }

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