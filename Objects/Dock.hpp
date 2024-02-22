#ifndef Dock_hpp
#define Dock_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Dock
{
private:
    SDL_Texture* dockTexture;
    SDL_Rect dockRect;
public:
    Dock();
    ~Dock();
    
    SDL_Rect& getDockRect();
    
    void init(const char* path, SDL_Renderer* ren, float x, float y);
    void render(SDL_Renderer* ren);
};

#endif /* Dock_hpp */
