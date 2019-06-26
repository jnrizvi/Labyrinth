#include "handleEvents.h"
#include "physics2d.h"

void gravity(PC *player, Platform *nextPlatform) {
    nextPlatform->leftEdge = nextPlatform->block_dest.x - player->sprite_w;
    // nextPlatform->rightEdge = 96 + (nextPlatform->block_dest.w * nextPlatform->numBlocks) + player->sprite_w;
    nextPlatform->rightEdge = (nextPlatform->block_dest.w * nextPlatform->numBlocks) + nextPlatform->block_dest.x;
    nextPlatform->top = nextPlatform->block_dest.y - player->sprite_h;

    player->y += player->dy;
    player->dy += 0.5;

    if(player->y > nextPlatform->top && (player->x > nextPlatform->leftEdge && player->x < nextPlatform->rightEdge)) {     // collision condition...
        player->y = nextPlatform->top;                                                                                    // behavior if collided
        player->dy = 0;
    }
}