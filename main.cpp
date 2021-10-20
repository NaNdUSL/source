// Contains the main function and probably some testing

#include "game.cpp"

int main(int argc, char const *argv[]){

    // std::srand(static_cast<unsigned>(time(NULL)));

    // init game engine

    int player;

    std::cout << "white: 1, black: -1\n";
    std::cin >> player;
    std::cout << "\n";

    Game game(player);

    while(game.running()){

        game.update();
        game.render();
    }

    return 0;
}