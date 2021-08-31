// Contains the main function and probably some testing

#include "game.cpp"

int main(int argc, char const *argv[]){

    // std::srand(static_cast<unsigned>(time(NULL)));

    // init game engine

    Game game;

    while(game.running()){

        game.update();
        game.render();
    }

    return 0;
}