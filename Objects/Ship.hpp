#ifndef Ship_hpp
#define Ship_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Ship
{
private:
    SDL_Texture* shipEmptyTexture;
    SDL_Texture* shipFullTexture;
    SDL_Rect shipRect;
    bool loaded = 0;
    int angle = 0;
    SDL_Point center;
    SDL_RendererFlip flip;
    unsigned int up = 0, down = 0, left = 0, right = 0;
    unsigned int shipSpeed = 5;
public:
    Ship();
    ~Ship();
    
    bool getLoaded();
    SDL_Rect& getDirection();
    SDL_Texture& getFullShipTexture();
    SDL_Texture& getEmptyShipTexture();
    
    void setLoaded();
    
    void init(SDL_Renderer* ren);
    void setDirection(int upSwitch, int downSwitch, int leftSwitch, int rightSwitch);
    void move(const int screenWidth, const int screenHeight);
    void load(float LdockX, float LdockY, float RdockX, float RdockY);
    
    void render(SDL_Renderer& renderer);
};

#endif /* Ship_hpp */
