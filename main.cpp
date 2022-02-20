// Contains the main function and probably some testing
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

#include "game.cpp"

int main(int argc, char const *argv[]){

    // std::srand(static_cast<unsigned>(time(NULL)));

    // init game engine

    int white;

    std::cout << "white: 1, black: 0\n";
    std::cin >> white;
    std::cout << "\n";

    Game game(white);

    while(game.running()){

        game.update();
        game.render();
    }

    return 0;
}