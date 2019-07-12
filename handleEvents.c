#include "headers/handleEvents.h"

int processEvents(Agent *agent, float *refX, float *refY, int *row, int *col) {
    SDL_Event event;
    int done = 0;
    float normalSpeed = 3;
    int refGrid[][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 1, 1, 0}
    };
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            done = 1;
        }
    }

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_S]) {
        normalSpeed *= 0.5;
    }
    if (keystate[SDL_SCANCODE_A]) {
        if (*col > 0) {
            *refX -= normalSpeed;
        }
        agent->x -= normalSpeed;
        agent->coll.leftEdge -= normalSpeed;
        agent->coll.rightEdge -= normalSpeed;
        agent->walking = 1;
        agent->facingLeft = 1;
        if (*refX < -32) {
            *refX = 0;
            if (*col-1 >= 0) {
                *col -= 1;
            }
        }
    }
    else if(keystate[SDL_SCANCODE_D]) {
        if (*col < 3){
            *refX += normalSpeed;
        }
        agent->x += normalSpeed;
        agent->coll.leftEdge += normalSpeed;
        agent->coll.rightEdge += normalSpeed;
        agent->walking = 1;
        agent->facingLeft = 0;
        if (*refX > 32) {
            *refX = 0;
            if (*col+1 < 4) {
                *col += 1;
            }
        }
    }
    else {
        agent->walking = 0;
    }

    if (keystate[SDL_SCANCODE_W] && agent->falling==false && agent->jumpAgain==true) {
        agent->falling = true;
        agent->jumpAgain = false;
        agent->dy = -10;
    }
    
    
    

    return done;
}

// void foo() {
//     printf("row: %d\n", row);
//     if (refY > 32) {
//         // if (row+1 <= 6) {
            
//         // printf("refGrid[row+1][col]: %d\n", refGrid[row+1][col]);
//         printf("player.coll.bottom : %f\n", player.coll.bottom);
//         if (refGrid[row+1][col] == 0) {
//             // printf("refY being reset\n");
//             refY = 0;
//             if (row + 1 <= 6) {
//                 row++;
//             }
//         }

//         if (player.coll.bottom >= 192) {  //(row+1)*32)
//             player.y = 192 - player.sprite_h;  // (row+1)*32)
//             player.jumpAgain = true;
//             player.falling = false;
//             player.coll.bottom = 192; //(row+1)*32) +64
//             player.coll.top = player.y;                                                                            
//             player.dy = 0;
//         }
//         printf("refY: %f\n", refY);
//         // }
//     }
//     if (refY < -32) {
//         if (row-1 >= 0) {
//             // printf("refY being reset\n");
//             if (refGrid[row-1][col] == 0) {
               
//                 refY = 0;
//                 if (row -1 >= 0)
//                     row--;
//             } 
//         }
//     }
// }


