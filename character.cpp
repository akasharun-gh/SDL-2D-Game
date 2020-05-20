#include "character.h"

//Constructor: initailize private members
Character::Character(std::string filepath, SDL_Renderer *renderTarget){
        playerPos.x = playerPos.y = 0;
        playerPos.w = playerPos.h = 64;

        charImage = Character::LoadTexture(filepath, renderTarget);
        SDL_QueryTexture(charImage, NULL, NULL, &textureWidth, &textureHeight);
        frameWidth = textureWidth / 13;
        frameHeight = textureHeight / 21;

        //Initialize Animation
        playerRect.x = 0;
        playerRect.y = frameHeight * 2;
        playerRect.w = frameWidth;
        playerRect.h = frameHeight;

}

// Destructor
Character::~Character(){
    SDL_DestroyTexture(charImage);
}

// Method to update the motion of the character
void Character::updateMotion(SDL_Event &ev){
    if(ev.type == SDL_KEYDOWN){
        switch(ev.key.keysym.sym){
            case SDLK_UP:
                playerPos.y -= 8;
                Character::updateAnimation(kUp);
                if(playerPos.y <= 0)
                    playerPos.y =  480 - playerPos.h;
                break;
            case SDLK_DOWN:
                playerPos.y += 8;
                Character::updateAnimation(kDown);
                if(playerPos.y >= (480 - playerPos.h))
                    playerPos.y = 0;
                break;
            case SDLK_LEFT:
                playerPos.x -= 8;
                Character::updateAnimation(kLeft);
                if(playerPos.x <= 0)
                    playerPos.x = 640 - playerPos.w;
                break;
            case SDLK_RIGHT:
                playerPos.x += 8;
                Character::updateAnimation(kRight);
                if(playerPos.x >= (640 - playerPos.h))
                    playerPos.x = 0;
                break;
        }
    }
}

// Method to update charcter animation from sprite sheet
void Character::updateAnimation(Dir dir){
    switch(dir){
        case kUp:
            playerRect.y = frameHeight * 8;
            playerRect.x += frameWidth;
            if(playerRect.x >= (textureWidth - frameWidth*4))
                playerRect.x = 0;
            break; 
        case kDown:
            playerRect.y = frameHeight * 10;
            playerRect.x += frameWidth;
            if(playerRect.x >= (textureWidth - frameWidth*4))
                playerRect.x = 0;
            break;
        case kLeft:
            playerRect.y = frameHeight * 9;
            playerRect.x += frameWidth;
            if(playerRect.x >= (textureWidth - frameWidth*4))
                playerRect.x = 0;
            break;
        case kRight: 
            playerRect.y = frameHeight * 11;
            playerRect.x += frameWidth;
            if(playerRect.x >= (textureWidth - frameWidth*4))
                playerRect.x = 0;
            break;
    }
    
}

// Method to load the texture from provided image
SDL_Texture *Character::LoadTexture(std::string filepath, SDL_Renderer *renderTarget){
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