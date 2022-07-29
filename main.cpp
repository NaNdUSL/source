// Contains the main function
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <cmath>

#include "game.cpp"

int main(int argc, char const *argv[]){

    // std::srand(static_cast<unsigned>(time(NULL)));

    // init game engine

	int player;
	int board;

	std::fstream Myfile("boardstates.txt");

	std::cout << "boards:\n";

    // display boars here.
    // this is used for testing, the boards can be edited in the boardstates.txt for example adding these 2 lines:

    // CBKQBCRPPPPPPPP8888_P_P_P_P_P_P_P_P_R_C_B_K_Q_B_C_R
    // _R_C_B_Q_K_B_C_R_P_P_P_P_P_P_P_P8888PPPPPPPPRCBQKBCR

    // each piece is represented by letters and the numbers represent lines of empty squares (min. 1, max. 8).
    // letters without underscore before them are white pieces and vice-versa

    //each board is represented by 2 lines wich the one used is gonna depend on the color the player wants to play (i'm a little lazy to create a method
    // that reads back to front depending on the side the user starts... maybe i'll add that... idk)

	if (Myfile.is_open()){

		int bn = 1;
		std::string line;

		while(getline(Myfile, line)){

			std::cout << bn << ". ---> " << line << '\n';
			bn++;
		}
		Myfile.close();
	}
	else std::cout << "Unable to open file"; 

	std::cout << "board number:\n";
	std::cin >> board;
	std::cout << "\n";

	std::cout << "white: 1, black: 0\n";
	std::cin >> player;
	std::cout << "\n";

	Game game(player, board);

	while(game.running()){

		game.update();
		game.render();
	}

	return 0;
}