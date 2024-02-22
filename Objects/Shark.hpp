#ifndef Shark_hpp
#define Shark_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <ctime>

class Shark {
private:
    SDL_Texture* sharkTexture;
    SDL_Rect sharkRect;
    
    int angle = 0;
    SDL_Point center;
    SDL_RendererFlip flip;
    unsigned int sharkSpeed = 4;
    
    bool turn = false;
public:
    Shark();
    ~Shark();
    
    SDL_Rect& getSharkRect();
    
    void init(SDL_Renderer* ren, const int screenHeight);
    void move(Shark* shark, const int screenWidth, const int screenHeight);
    void render(SDL_Renderer* ren);
};

#endif /* Shark_hpp */
