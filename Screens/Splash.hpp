#ifndef Splash_hpp
#define Splash_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Splash
{
private:
    TTF_Font* font;
    SDL_Texture* splashTitle;
    SDL_Rect splashTextRect;
    
    SDL_Texture* enterToPlay;
    SDL_Rect enterRect;
    
    SDL_Texture* instructions;
    SDL_Rect instructionsRect;
public:
    Splash();
    ~Splash();
    
    void init(SDL_Renderer* ren);
    void render(SDL_Renderer* ren);
};

#endif /* Splash_hpp */
