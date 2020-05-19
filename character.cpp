#include "character.h"

void Character::updateMotion(SDL_Event &ev, int frameWidth, int frameHeight, int textureWidth){
    if(ev.type == SDL_KEYDOWN){
        switch(ev.key.keysym.sym){
            case SDLK_UP:
                playerPos.y -= 8;
                Character::updateAnimation(frameWidth, frameHeight, textureWidth, kUp);
                if(playerPos.y <= 0)
                    playerPos.y =  480 - playerPos.h;
                break;
            case SDLK_DOWN:
                playerPos.y += 8;
                Character::updateAnimation(frameWidth, frameHeight, textureWidth, kDown);
                if(playerPos.y >= 480)
                    playerPos.y = 0;
                break;
            case SDLK_LEFT:
                playerPos.x -= 8;
                Character::updateAnimation(frameWidth, frameHeight, textureWidth, kLeft);
                if(playerPos.x <= 0)
                    playerPos.x = 640 - playerPos.w;
                break;
            case SDLK_RIGHT:
                playerPos.x += 8;
                Character::updateAnimation(frameWidth, frameHeight, textureWidth, kRight);
                if(playerPos.x >= 640)
                    playerPos.x = 0;
                break;
        }
    }
}

void Character::initailizeAnimation(int frameHeight, int frameWidth){
    playerRect.x = 0;
    playerRect.y = frameHeight * 2;
    playerRect.w = frameWidth;
    playerRect.h = frameHeight;
}

void Character::updateAnimation(int frameWidth, int frameHeight, int textureWidth, Dir dir){
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