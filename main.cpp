#include "character.cpp"
#include "cleanup.h"

SDL_Texture *LoadTexture(std::string filepath, SDL_Renderer *renderTarget){
    SDL_Texture *texture = nullptr;
    SDL_Surface *surface = IMG_Load(filepath.c_str());
    if(surface == NULL)
        std::cout << "Error: " << SDL_GetError() << std::endl; 
    else {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if(texture == NULL){
            std::cout << "Error: " << SDL_GetError() << std::endl;
        }
    }

    SDL_FreeSurface(surface);

    return texture;
}

int main(int argc, char* argv[]){

    SDL_Window *window = nullptr;
    SDL_Texture *currImage = nullptr;
    SDL_Texture *game_background = nullptr;
    SDL_Renderer *renderTarget = nullptr;
    Character boy;

    int frameWidth, frameHeight;
    int textureWidth, textureHeight;

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "Error:" << SDL_GetError() << std::endl;
        return 1;
    }

    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
        std::cout << "Error: " << IMG_GetError() << std::endl;

    window = SDL_CreateWindow("Keypress switch example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    currImage = LoadTexture("game_images/anime_character.png", renderTarget);
    game_background = LoadTexture("game_images/game_background.png", renderTarget);

    SDL_QueryTexture(currImage, NULL, NULL, &textureWidth, &textureHeight);

    frameWidth = textureWidth / 13;
    frameHeight = textureHeight / 21;

    boy.initailizeAnimation(frameHeight, frameWidth);
    bool isRunning = true;
    SDL_Event ev;

    while(isRunning){
        while(SDL_PollEvent(&ev) != 0){
            if(ev.type == SDL_QUIT)
                isRunning = false;    
            else {
                    boy.updateMotion(ev, frameWidth, frameHeight, textureWidth); 
            }                    
        }
    
        SDL_RenderClear(renderTarget);
        SDL_RenderCopy(renderTarget, game_background, NULL, NULL);
        SDL_RenderCopy(renderTarget, currImage, &boy.getPlayerRect(), &boy.getPlayerPos());
        SDL_RenderPresent(renderTarget);
    }

    cleanup(window, currImage, game_background);

    currImage = nullptr;
    window = nullptr;
    renderTarget = nullptr;
    game_background = nullptr;
    
    SDL_Quit();
    return 0;
}