#include "Game.hpp"

Game::Game(const char* title, int x, int y, bool fullscreen)
{
    Uint8 flags = 0;
    if(fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }
    
    // SDL Init
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL Initialized.\n";
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
        
        // Create window
        window = SDL_CreateWindow(title, x, y, screenWidth, screenHeight, flags);
        if(window) {
            std::cout << "Window created.\n";
            
            // IMG init
            if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) { std::cout << "SDL Image initalized.\n"; }
            else { std::cout << "Error initalizing SDL Image: " << IMG_GetError() << "\n"; }
            
            // TTF init
            if(TTF_Init() == 0) { std::cout << "TTF initialized.\n"; }
            else { std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << "\n"; }
            
            // Mixer init
            if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == 0) { std::cout << "Mix initalized\n"; }
            else { std::cout << "Error initializing SDL_Mix: " << Mix_GetError() << "\n"; }
            
        } else {
            std::cout << "Could not create window: " << SDL_GetError() << "\n";
        }
        
        // Create renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer) { std::cout << "Renderer created.\n"; }
        else { std::cout << "Could not create renderer: " << SDL_GetError() << "\n"; }
        
        isRunning = true;
    } else {
        std::cout << "SDL could not initialize: " << SDL_GetError() << "\n";
        isRunning = false;
    }
    
    // Water
    water.init(renderer, screenWidth, screenHeight);
    
    // Ship
    ship.init(renderer);

    // Loading dock image
    loadingDock.init("assets/loadingDock.png", renderer, loadingDockx, loadingDocky);
    
    // Receiving dock image
    recDock.init("assets/recDock.png", renderer, recDockx, recDocky);
    
    // Pirate
    pirate.init(renderer);
    
    // Shark
    shark.init(renderer, screenHeight);
    
    // Font
    font = TTF_OpenFont("assets/BlackOpsOne-Regular.ttf", 48);
    if(font == NULL) {std::cout << "Error loading font\n";}
    
    // Splash screen text
    splash.init(renderer);
    
    // Instructions screen text
    inst.init(renderer);
    
    // Score
    createText("Score: 0", {255,255,255}, &scoreTexture, &scoreRect, 450, 10, 120, 100);
    
    // Restart text
    createText("Press Space to restart", {255,0,0}, &restartText, &restartRect, 350, 350, 350, 250);
    
    // Sound
    ocean = Mix_LoadWAV("assets/ocean.wav");
    coin = Mix_LoadWAV("assets/coin.wav");
    alert = Mix_LoadWAV("assets/alert.wav");
    hit = Mix_LoadWAV("assets/hit.wav");
    
    Mix_PlayChannel(-1, ocean, -1);
}

Game::~Game()
{
    SDL_DestroyTexture(restartText);
    SDL_DestroyTexture(scoreTexture);
    
    TTF_CloseFont(font);
    
    Mix_FreeChunk(ocean);
    Mix_FreeChunk(coin);
    Mix_FreeChunk(alert);
    Mix_CloseAudio();
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    std::cout << "SDL Deconstructed.\n";
}

const bool Game::running() const
{
    return isRunning;
}

void Game::startFrame()
{
    frameStart = SDL_GetTicks();
}

void Game::delayFrame()
{
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) { SDL_Delay(frameDelay - frameTime); }
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
 
                case SDLK_p:
                    paused = true;
                    break;
                case SDLK_r:
                    paused = false;
                    break;
                    
                case SDLK_RETURN:
                    onSplashScreen = false;
                    SDL_SetTextureBlendMode(water.getWaterTexture(), SDL_BLENDMODE_MOD);
                    break;
                    
                case SDLK_i:
                    if (onSplashScreen == true) {
                        OnInst = true;
                    }
                    
                case SDLK_SPACE:
                    collided = false;
                    resetScore = true;
                    pirate.~Pirate();
                    pirate.init(renderer);
                    ship.~Ship();
                    ship.init(renderer);
                    ship.setLoaded();
                    shark.~Shark();
                    shark.init(renderer, screenHeight);
                    SDL_SetTextureBlendMode(water.getWaterTexture(), SDL_BLENDMODE_MOD);
                    break;
                    
                case SDLK_UP: ship.setDirection(1, 0, 0, 0); break;
                case SDLK_DOWN: ship.setDirection(0, 1, 0, 0); break;
                case SDLK_LEFT: ship.setDirection(0, 0, 1, 0); break;
                case SDLK_RIGHT: ship.setDirection(0, 0, 0, 1); break;
            }
            break;
    }
}

void Game::collision()
{
    // Ship hits pirate
    if ((SDL_HasIntersection(&ship.getDirection(), &pirate.getPirateRect()) && ship.getLoaded() == 1) || SDL_HasIntersection(&ship.getDirection(), &shark.getSharkRect())) {
        SDL_SetTextureColorMod(&ship.getFullShipTexture(), 255, 0, 0);
        SDL_SetTextureBlendMode(water.getWaterTexture(), SDL_BLENDMODE_ADD);
        collided = true;
        Mix_PlayChannel(-1, hit, 0);
    } else {
        SDL_SetTextureColorMod(&ship.getFullShipTexture(), 255, 255, 255);
    }
    
    // Ship hits shark
    if (SDL_HasIntersection(&ship.getDirection(), &shark.getSharkRect())) {
        SDL_SetTextureColorMod(&ship.getEmptyShipTexture(), 255, 0, 0);
        SDL_SetTextureBlendMode(water.getWaterTexture(), SDL_BLENDMODE_ADD);
        collided = true;
        Mix_PlayChannel(-1, hit, 0);
    } else {
        SDL_SetTextureColorMod(&ship.getEmptyShipTexture(), 255, 255, 255);
    }
}

void Game::keepScore()
{
    if (SDL_HasIntersection(&ship.getDirection(), &recDock.getDockRect()) && ship.getLoaded() == 1) {
        
        Mix_PlayChannel(-1, coin, 0);

        SDL_DestroyTexture(scoreTexture);
        
        score += 100;
        std::string textScore = "Score: " + std::to_string(score);
        
        createText(textScore.c_str(), {255,255,255}, &scoreTexture, &scoreRect, 450, 10, 120, 100);
        
        scoreRect.w = 150;
        
        if(score >= 1000) {
            scoreRect.w = 170;
        }
    }
}

void Game::createText(const char* text, SDL_Color color, SDL_Texture** texture, SDL_Rect* rect, int x, int y, int w, int h)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

void Game::update()
{
    if (paused == false && collided == false) {
        // Water
        water.update(screenWidth, screenHeight);
        
        // Ship
        ship.move(screenWidth, screenHeight);
        ship.load(loadingDockx, loadingDocky, recDockx, recDocky);
        
        // Pirate
        pirate.move(&ship, screenWidth, screenHeight);
        
        // Shark
        if (onSplashScreen == false) {
            shark.move(&shark, screenWidth, screenHeight);
        }
        
        // Collision w/ Pirate or Shark
        collision();
        
        if (resetScore == true) {
            SDL_DestroyTexture(scoreTexture);
            createText("Score: 0", {255,255,255}, &scoreTexture, &scoreRect, 450, 10, 120, 100);
            score = 0;
            resetScore = false;
        }
        
        // Score
        keepScore();
        
        if (SDL_HasIntersection(&ship.getDirection(), &loadingDock.getDockRect())) {
            Mix_PlayChannel(-1, alert, 0);
        }
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Water
    water.render(renderer);
    
    if (onSplashScreen == true) {
        
        // Water mode
        SDL_SetTextureBlendMode(water.getWaterTexture(), SDL_BLENDMODE_BLEND);
        
        // Splash screen text
        if (OnInst == false) {
            splash.render(renderer);
        }
        
        if (OnInst == true) {
            inst.render(renderer);
        }
        
    } else {
        // Shark
        shark.render(renderer);
        
        // Ship
        ship.render(*renderer);
        
        // Score
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
        
        // Loading dock
        loadingDock.render(renderer);
        
        // Receiving dock
        recDock.render(renderer);
        
        // Pirate
        pirate.render(*renderer);
    }
    
    if (collided == true) {
        SDL_RenderCopy(renderer, restartText, NULL, &restartRect);
    }
    
    SDL_RenderPresent(renderer);
}
