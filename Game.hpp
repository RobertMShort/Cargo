#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <sstream>

#include "Objects/Water.hpp"
#include "Objects/Ship.hpp"
#include "Objects/Dock.hpp"
#include "Objects/Pirate.hpp"
#include "Objects/Shark.hpp"

#include "Screens/Splash.hpp"
#include "Screens/Instructions.hpp"

class Game {
private:
    const int screenWidth = 1000;
    const int screenHeight = 800;
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    
    const int loadingDockx = 800;
    const int loadingDocky = 30;
    const int recDockx = 15;
    const int recDocky = 640;
    
    unsigned int score = 0;
    std::string textScore;
    
    TTF_Font* font;
    SDL_Texture* scoreTexture;
    SDL_Rect scoreRect;
    
    bool paused = false;
    
    Water water;
    Ship ship;
    Dock loadingDock;
    Dock recDock;
    Pirate pirate;
    Shark shark;
    
    Splash splash;
    Instructions inst;
    
    bool onSplashScreen = true;
    bool OnInst = false;

    bool collided = false;
    bool resetScore = false;
    
    SDL_Texture* restartText;
    SDL_Rect restartRect;
    
    Mix_Chunk *ocean = NULL;
    Mix_Chunk *coin = NULL;
    Mix_Chunk *alert = NULL;
    Mix_Chunk *hit = NULL;
    
public:
    Game(const char* title, int x, int y, bool fullscreen);
    ~Game();
    
    const bool running() const;
    void startFrame();
    void delayFrame();
    
    void handleEvents();
    void collision();
    void keepScore();
    
    void createText(const char* text, SDL_Color color, SDL_Texture** texture, SDL_Rect* rect, int x, int y, int w, int h);
    
    void update();
    void render();
};

#endif /* Game_hpp */
