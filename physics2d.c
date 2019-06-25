#include "handleEvents.h"
#include "physics2d.h"

void gravity(PC *player, Platform *nextPlatform) {
    player->y += player->dy;
    player->dy += 0.5;
    if(player->y > 350 && (player->x > 128-32 && player->x < 324+32)) {
        player->y = 350;
        player->dy = 0;
    }
}