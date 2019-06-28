
#include "physics2d.h"

void gravity(Agent *agent, Platform platforms[2]) {
    agent->y += agent->dy;
    agent->dy += 0.5;

    
    for (int i = 0; i < 2; i++) {
        // printf("%d\n",platforms[i].top);
        platforms[i].top = platforms[i].block_dest.y - agent->sprite_h;
        if (agent->y <= platforms[i].top) {
            
            platforms[i].leftEdge = platforms[i].block_dest.x - agent->sprite_w;
            platforms[i].rightEdge = (platforms[i].block_dest.w * platforms[i].numBlocks) + platforms[i].block_dest.x;
            

            if ( !(agent->y > platforms[i].top && (agent->x > platforms[i].leftEdge && agent->x < platforms[i].rightEdge)) ) {
                printf("Beep\n");
                agent->y = platforms[i].top;                                                                                    
                agent->dy = 0;
            }
            else {
                break;
            }
        }
        
    }
    
}