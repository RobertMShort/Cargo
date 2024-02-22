#include "Water.hpp"

Water::Water() {}
Water::~Water() 
{
    SDL_DestroyTexture(waterTexture2);
    SDL_DestroyTexture(waterTexture);
    this->waterTexture = NULL;
    this->waterTexture2 = NULL;
    std::cout << "Water textures destroyed\n";
}

SDL_Texture* Water::getWaterTexture()
{
    return waterTexture2;
}

void Water::init(SDL_Renderer* ren, const int screenWidth, const int screenHeight)
{
    SDL_Surface* surface = IMG_Load("assets/water.jpg");
    this->waterTexture = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);
    
    SDL_Surface* surface2 = IMG_Load("assets/water.jpg");
    this->waterTexture2 = SDL_CreateTextureFromSurface(ren, surface2);
    SDL_FreeSurface(surface2);
    
    rect1.x = 0;
    rect1.y = 0;
    rect1.w = screenWidth;
    rect1.h = screenHeight;
    
    rect2.x = screenWidth - 1;
    rect2.y = 0;
    rect2.w = screenWidth;
    rect2.h = screenHeight;
    
    rect3.x = 0;
    rect3.y = 0;
    rect3.w = screenWidth;
    rect3.h = screenHeight;
    
    rect4.x = 0;
    rect4.y = -screenHeight;
    rect4.w = screenWidth;
    rect4.h = screenHeight;
}

void Water::update(const int screenWidth, const int screenHeight)
{
    rect1.x++;
    if(rect1.x > screenWidth - 1) { rect1.x = -(screenWidth - 1); }
    rect2.x++;
    if(rect2.x > screenWidth - 1) { rect2.x = -(screenWidth - 1); }
    
    rect3.y++;
    if(rect3.y > screenHeight - 1) { rect3.y = -screenHeight; }
    rect4.y++;
    if(rect4.y > screenHeight - 1) { rect4.y = -screenHeight; }
}

void Water::render(SDL_Renderer* ren)
{
    int w, h;
    SDL_QueryTexture(waterTexture, NULL, NULL, &w, &h);
    SDL_Delay(20);
    
    // Water
    SDL_SetTextureBlendMode(waterTexture, SDL_BLENDMODE_NONE);
    //SDL_SetTextureBlendMode(waterTexture2, SDL_BLENDMODE_MOD);
    SDL_RenderCopy(ren, waterTexture, NULL, &rect1);
    SDL_RenderCopy(ren, waterTexture, NULL, &rect2);
    SDL_RenderCopy(ren, waterTexture2, NULL, &rect3);
    SDL_RenderCopy(ren, waterTexture2, NULL, &rect4);
}
