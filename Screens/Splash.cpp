#include "Splash.hpp"

Splash::Splash() {}

Splash::~Splash()
{
    SDL_DestroyTexture(enterToPlay);
    SDL_DestroyTexture(splashTitle);
    std::cout << "Splash textures destroyed.\n";
}

void Splash::init(SDL_Renderer* ren)
{
    font = TTF_OpenFont("assets/BlackOpsOne-Regular.ttf", 48);
    if(font == NULL) {std::cout << "Error loading font\n";}
    
    SDL_Surface* surfaceText1 = TTF_RenderText_Solid(font, "Cargo", {255,255,255});
    splashTitle = SDL_CreateTextureFromSurface(ren, surfaceText1);
    SDL_FreeSurface(surfaceText1);
    
    splashTextRect.x = 350;
    splashTextRect.y = 150;
    splashTextRect.w = 250;
    splashTextRect.h = 200;
    
    // Enter to play
    SDL_Surface* surfaceText2 = TTF_RenderText_Solid(font, "Press Enter", {0,255,0});
    enterToPlay = SDL_CreateTextureFromSurface(ren, surfaceText2);
    SDL_FreeSurface(surfaceText2);
    
    enterRect.x = 370;
    enterRect.y = 350;
    enterRect.w = 200;
    enterRect.h = 200;
    
    // Instructions
    SDL_Surface* surfaceText3 = TTF_RenderText_Solid(font, "Press i for instructions", {0,0,0});
    instructions = SDL_CreateTextureFromSurface(ren, surfaceText3);
    SDL_FreeSurface(surfaceText3);
    
    instructionsRect.x = 50;
    instructionsRect.y = 675;
    instructionsRect.w = 275;
    instructionsRect.h = 150;
}

void Splash::render(SDL_Renderer* ren)
{
    // Title
    SDL_RenderCopy(ren, splashTitle, NULL, &splashTextRect);
    
    // Enter to play
    SDL_RenderCopy(ren, enterToPlay, NULL, &enterRect);
    
    // Instructions
    SDL_RenderCopy(ren, instructions, NULL, &instructionsRect);
}
