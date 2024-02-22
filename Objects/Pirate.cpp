#include "Pirate.hpp"

Pirate::Pirate() {}
Pirate::~Pirate() 
{
    SDL_DestroyTexture(this->pirateTexture);
    this->pirateTexture = NULL;
    std::cout << "Pirate texture destroyed.\n";
}

SDL_Rect& Pirate::getPirateRect()
{
    return this->pirateRect;
}

void Pirate::init(SDL_Renderer* ren)
{
    SDL_Surface* surface = IMG_Load("assets/pirate.png");
    this->pirateTexture = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);
    
    this->pirateRect.x = 0;
    this->pirateRect.y = 0;
    this->pirateRect.w = 120;
    this->pirateRect.h = 120;
}

void Pirate::direction(float dirX, float dirY, unsigned int speed)
{
    int diffx = this->pirateRect.x - dirX;
    int diffy = this->pirateRect.y - dirY;
    
    float h = sqrt(pow(diffx, 2) + pow(diffy, 2));
    
    double vx = -diffx/h*speed;
    double vy = diffy/h*speed;
    
    this->pirateRect.x += vx;
    this->pirateRect.y -= vy;
    
    angle = vx + vy;
    
    if (vx > 0) {
        flip = SDL_FLIP_HORIZONTAL;
    } else {
        flip = SDL_FLIP_NONE;
    }
}

void Pirate::move(Ship* ship, const int screenWidth, const int screenHeight)
{
    center.x = this->pirateRect.w / 2;
    center.y = this->pirateRect.h / 2;
    
    flip = SDL_FLIP_NONE;
    
    if (ship->getLoaded() == 1) {
        this->direction(ship->getDirection().x, ship->getDirection().y, this->pirateSpeed);
    } else {
        if (this->pirateRect.x > 0 && this->pirateRect.y > 0) {
            this->direction(0, 0, 3);
        }
    }
}

void Pirate::render(SDL_Renderer& renderer)
{
    //SDL_RenderCopy(&renderer, this->pirateTexture, NULL, &this->pirateRect);
    SDL_RenderCopyEx(&renderer, this->pirateTexture, NULL, &this->pirateRect, this->angle, &this->center, this->flip);
}
