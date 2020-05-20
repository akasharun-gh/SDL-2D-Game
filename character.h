#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <string>

class Character{
    public:   
    Character(std::string filepath, SDL_Renderer *renderTarget);
    ~Character();

    enum Dir{kUp, kDown, kLeft, kRight};
    void updateMotion(SDL_Event &ev);
    void automateMotion(int &frameRate, int &switchDir);
    void updateAnimation(Dir);
    void initPlayerPos(int&& xy_init_pos); //, int&& wh_init_val
    void initPlayerRect( int&& sprite_w, int&& sprite_h, int&& x, int&& y);

    // Getters
    SDL_Rect& getPlayerPos(){ return playerPos; }
    SDL_Rect& getPlayerRect(){ return playerRect; }
    SDL_Texture *getCharImage(){ return charImage; } 

    SDL_Texture *LoadTexture(std::string filepath, SDL_Renderer *renderTarget);

    private:
    SDL_Rect playerRect;
    SDL_Rect playerPos;
    int frameWidth, frameHeight;
    int textureWidth, textureHeight;
    SDL_Texture *charImage = nullptr;
    
};