#include "resources.h"

void setCurrentSprite(Agent *agent, SDL_Rect *rect);
Agent initAgent(char* textureName, SDL_Rect agent_dest, int facingLeft, int currentFramex, int currentFramey, SDL_Renderer *renderer);
Platform initPlatform(char* textureName, SDL_Rect block_dest, int numBlocks, SDL_Renderer *renderer);
SDL_Texture *createTexture(char *img_name, SDL_Renderer *renderer);