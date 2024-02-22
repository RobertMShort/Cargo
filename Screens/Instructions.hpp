#ifndef Instructions_hpp
#define Instructions_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Instructions
{
private:
    TTF_Font* font;
    SDL_Texture* instText;
    SDL_Rect instRect;
    
    SDL_Texture* gameInstText;
    SDL_Rect gameInstRect;
public:
    Instructions();
    ~Instructions();
    
    void init(SDL_Renderer* ren);
    void render(SDL_Renderer* ren);
};

#endif /* Instructions_hpp */
