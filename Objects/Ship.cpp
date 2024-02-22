#include "Ship.hpp"

Ship::Ship() {}
Ship::~Ship()
{
    SDL_DestroyTexture(this->shipFullTexture);
    SDL_DestroyTexture(this->shipEmptyTexture);
    this->shipFullTexture = NULL;
    this->shipEmptyTexture = NULL;
    std::cout << "Ship textures destroyed.\n";
}

bool Ship::getLoaded()
{
    return this->loaded;
}

SDL_Rect& Ship::getDirection()
{
    return this->shipRect;
}

SDL_Texture& Ship::getFullShipTexture()
{
    return *this->shipFullTexture;
}

SDL_Texture& Ship::getEmptyShipTexture()
{
    return *this->shipEmptyTexture;
}

void Ship::setLoaded()
{
    this->loaded = 0;
}

void Ship::init(SDL_Renderer* ren)
{
    SDL_Surface* surface1 = IMG_Load("assets/ship-empty.png");
    this->shipEmptyTexture = SDL_CreateTextureFromSurface(ren, surface1);
    SDL_FreeSurface(surface1);
    
    SDL_Surface* surface2 = IMG_Load("assets/ship-full.png");
    this->shipFullTexture = SDL_CreateTextureFromSurface(ren, surface2);
    SDL_FreeSurface(surface2);
    
    this->shipRect.x = 250;
    this->shipRect.y = 650;
    this->shipRect.w = 120;
    this->shipRect.h = 120;
}

void Ship::setDirection(int upSwitch, int downSwitch, int leftSwitch, int rightSwitch)
{
    this->up = upSwitch;
    this->down = downSwitch;
    this->left = leftSwitch;
    this->right = rightSwitch;
}

void Ship::move(const int screenWidth, const int screenHeight)
{
    center.x = this->shipRect.w / 2;
    center.y = this->shipRect.h / 2;
    
    // Move ship
    if(right == 1 && this->shipRect.x < screenWidth - this->shipRect.w) {
        this->shipRect.x += this->shipSpeed;
        flip = SDL_FLIP_HORIZONTAL;
        angle = 320;
    } else if (left == 1 && this->shipRect.x > 0) {
        this->shipRect.x -= this->shipSpeed;
        flip = SDL_FLIP_NONE;
        angle = 40;
    } else if (down == 1 && this->shipRect.y < screenHeight - this->shipRect.h) {
        this->shipRect.y += this->shipSpeed;
        flip = SDL_FLIP_NONE;
        angle = -50;
    } else if (up == 1 && this->shipRect.y > 0) {
        this->shipRect.y -= this->shipSpeed;
        flip = SDL_FLIP_VERTICAL;
        angle = 50;
    }
}

void Ship::load(float LdockX, float LdockY, float RdockX, float RdockY)
{
    if(this->shipRect.x >= LdockX - 120 && this->shipRect.y <= LdockY + 140) { this->loaded = 1; }
    else if(this->shipRect.x <= RdockX + 120 && this->shipRect.y >= RdockY - 120){ this->loaded = 0; }
}

void Ship::render(SDL_Renderer& renderer)
{
    if(this->loaded == 1) { SDL_RenderCopyEx(&renderer, this->shipFullTexture, NULL, &this->shipRect, this->angle, &this->center, flip); }
    else { SDL_RenderCopyEx(&renderer, this->shipEmptyTexture, NULL, &this->shipRect, this->angle, &this->center, this->flip); }
}
