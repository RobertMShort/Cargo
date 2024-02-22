#ifndef Water_hpp
#define Water_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Water
{
private:
    SDL_Texture* waterTexture;
    SDL_Texture* waterTexture2;
    SDL_Rect rect1, rect2, rect3, rect4;
public:
    Water();
    ~Water();
    
    SDL_Texture* getWaterTexture();
    
    void init(SDL_Renderer* ren, const int screenWidth, const int screenHeight);
    void update(const int screenWidth, const int screenHeight);
    void render(SDL_Renderer* ren);
};

#endif /* Water_hpp */
