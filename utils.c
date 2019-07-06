SDL_Rect createRect(int x_pos, int y_pos, int width, int height) {
    SDL_Rect rect;
    rect.x = x_pos;
    rect.y = y_pos;
    rect.w = width;
    rect.h = height;
    
    return rect;
}

Float_Rect createFRect(float x_pos, float y_pos, float width, float height) {
    Float_Rect rect;
    rect.x = x_pos;
    rect.y = y_pos;
    rect.w = width;
    rect.h = height;

    return rect;
}

bool keyCool(bool isCool, int timer) {
    if (isCool == true && timer > 0) {
        return true;
    }
    else {
        return false;
    }
}

void initEnvironment() {
    // initialize SDL video and audio systems
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    // initialize SDL mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
}

void destroyEnvironment() {
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();
}