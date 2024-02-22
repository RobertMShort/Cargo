#include "Shark.hpp"

Shark::Shark() {}

Shark::~Shark()
{
    SDL_DestroyTexture(this->sharkTexture);
    this->sharkTexture = NULL;
    std::cout << "Shark texture destroyed.\n";
}

SDL_Rect& Shark::getSharkRect()
{
    return this->sharkRect;
}

void Shark::init(SDL_Renderer* ren, const int screenHeight)
{
    SDL_Surface* surface = IMG_Load("assets/shark.png");
    this->sharkTexture = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);
    
    this->sharkRect.x = -100;
    this->sharkRect.y = 400;
    this->sharkRect.w = 120;
    this->sharkRect.h = 120;
    
    srand(static_cast<unsigned>(time(NULL)));
    this->sharkRect.y = (rand() % screenHeight - 200) + 150;
}

void Shark::move(Shark* shark, const int screenWidth, const int screenHeight)
{
    if (this->sharkRect.x < screenWidth + this->sharkRect.w && this->turn == false) {
        this->sharkRect.x += this->sharkSpeed;
        flip = SDL_FLIP_HORIZONTAL;
    } else {
        this->sharkRect.x -= this->sharkSpeed;
        this->turn = true;
        flip = SDL_FLIP_NONE;
        
        if (this->sharkRect.x < -this->sharkRect.w) {
            this->turn = false;
            this->sharkRect.y = (rand() % screenHeight - 200) + 150;
        }
    }

}

void Shark::render(SDL_Renderer* ren)
{
    SDL_RenderCopyEx(ren, this->sharkTexture, NULL, &this->sharkRect, this->angle, &this->center, this->flip);
}
