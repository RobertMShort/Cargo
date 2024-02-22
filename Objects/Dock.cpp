#include "Dock.hpp"

Dock::Dock() {}

Dock::~Dock()
{
    SDL_DestroyTexture(this->dockTexture);
    this->dockTexture = NULL;
    std::cout << "Dock texture destroyed.\n";
}

SDL_Rect& Dock::getDockRect()
{
    return this->dockRect;
}

void Dock::init(const char* path, SDL_Renderer* ren, float x, float y)
{
    SDL_Surface* surface = IMG_Load(path);
    dockTexture = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);
    
    this->dockRect.x = x;
    this->dockRect.y = y;
    this->dockRect.w = 150;
    this->dockRect.h = 150;
}

void Dock::render(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, this->dockTexture, NULL, &this->dockRect);
}
