#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <string>

class Character{
    public:   
    Character(){
        playerPos.x = playerPos.y = 0;
        playerPos.w = playerPos.h = 64;

    }
    enum Dir{kUp, kDown, kLeft, kRight};
    void updateMotion(SDL_Event &ev, int frameWidth, int frameHeight, int textureWidth);
    void updateAnimation(int frameWidth, int frameHeight, int textureWidth, Dir);
    void initailizeAnimation(int frameHeight, int frameWidth);
    // Getters
    SDL_Rect& getPlayerPos(){ return playerPos; }
    SDL_Rect& getPlayerRect(){ return playerRect; }

    private:
    SDL_Rect playerRect;
    SDL_Rect playerPos;
    
};