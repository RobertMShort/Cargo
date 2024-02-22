#ifndef Pirate_hpp
#define Pirate_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Ship.hpp"

class Pirate
{
private:
    SDL_Texture* pirateTexture;
    SDL_Rect pirateRect;
    
    int angle = 0;
    SDL_Point center;
    SDL_RendererFlip flip;
    unsigned int pirateSpeed = 4;
    
public:
    Pirate();
    ~Pirate();
    
    SDL_Rect& getPirateRect();
    
    void init(SDL_Renderer* ren);
    void direction(float dirX, float dirY, unsigned int speed);
    void move(Ship* ship, const int screenWidth, const int screenHeight);
    void render(SDL_Renderer& renderer);
};

#endif /* Pirate_hpp */
