#include "Game.hpp"

int main(int argc, const char * argv[]) {
    
    Game game("Cargo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);
    
    while (game.running()) {
        
        game.startFrame();
        
        game.handleEvents();
        game.update();
        game.render();
        
        game.delayFrame();

    }
    
    return 0;
}
