#include "Instructions.hpp"

Instructions::Instructions() {}

Instructions::~Instructions()
{
    SDL_DestroyTexture(instText);
    SDL_DestroyTexture(gameInstText);
    std::cout << "Inst textures destroyed.\n";
}

void Instructions::init(SDL_Renderer* ren)
{
    font = TTF_OpenFont("assets/BlackOpsOne-Regular.ttf", 48);
    if(font == NULL) {std::cout << "Error loading font\n";}
    
    SDL_Surface* surfaceText1 = TTF_RenderText_Blended_Wrapped(font, "Instructions:\n Use arrow keys to move.\n Press 'p' to pause, 'r' to resume.\n Exit window or press Escape to quit.\n", {255,255,255}, 700);
    instText = SDL_CreateTextureFromSurface(ren, surfaceText1);
    SDL_FreeSurface(surfaceText1);
    
    instRect.x = 50;
    instRect.y = 50;
    instRect.w = 200;
    instRect.h = 200;
    
    SDL_Surface* surfaceText2 = TTF_RenderText_Blended_Wrapped(font, "Game:\n Load ship at loading dock (top right).\n Unload at receiving dock (bottom left) for points.\n If you run into the shark or pirate, you lose.\n\n Press Enter to start!", {255,255,255}, 700);
    gameInstText = SDL_CreateTextureFromSurface(ren, surfaceText2);
    SDL_FreeSurface(surfaceText2);
    
    gameInstRect.x = 50;
    gameInstRect.y = 350;
    gameInstRect.w = 200;
    gameInstRect.h = 200;
}

void Instructions::render(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, instText, NULL, &instRect);
    SDL_RenderCopy(ren, gameInstText, NULL, &gameInstRect);
}
