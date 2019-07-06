#include "mapEditor.h"

void setCurrentSprite(Agent *agent, SDL_Rect *rect) {
    agent->currentSprite.x = agent->sprite_w * agent->currentFramex;
    agent->currentSprite.y = agent->sprite_h * agent->currentFramey;
    agent->currentSprite.w = agent->sprite_w;
    agent->currentSprite.h = agent->sprite_h;
}

Agent initAgent(char* textureName, SDL_Rect agent_dest, int facingLeft, int currentFramex, int currentFramey, SDL_Renderer *renderer) {
    Agent agent;
    agent.sheetTexture = createTexture(textureName, renderer);
    agent.x = agent_dest.x;
    agent.y = agent_dest.y;
    agent.sprite_w = agent_dest.w;
    agent.sprite_h = agent_dest.h;
    
    agent.dy = 0;
    agent.facingLeft = facingLeft;
    agent.currentFramex = currentFramex;
    agent.currentFramey = currentFramey;
    SDL_Rect currentSprite;
    agent.currentSprite = currentSprite;
    setCurrentSprite(&agent, &agent.currentSprite);
    
    agent.leftEdge = agent.x;
    agent.rightEdge = agent.x + agent.sprite_w;
    agent.bottom = agent.y + agent.sprite_h;
    agent.top = agent.x;
    

    return agent;
}

Platform initPlatform(char* textureName, SDL_Rect block_dest, int numBlocks, SDL_Renderer *renderer) {
    Platform platform;
    platform.pTexture = createTexture(textureName, renderer);
    platform.block_dest = block_dest;
    platform.numBlocks = numBlocks;

    platform.leftEdge = platform.block_dest.x;
    platform.rightEdge = (platform.block_dest.w * platform.numBlocks) + platform.block_dest.x;
    platform.bottom = platform.block_dest.y + platform.block_dest.h;
    platform.top = platform.block_dest.y; 

    return platform;
}

SDL_Texture *createTexture(char *img_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(img_name);
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}

