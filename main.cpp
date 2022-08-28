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
	int turn;

	std::fstream Myfile("boardstates.txt");

	std::cout << "boards:\n";

    // display boars here.
    // this is used for testing, the boards can be edited in the boardstates.txt for example adding this line:

    // CBKQBCRPPPPPPPP8888_P_P_P_P_P_P_P_P_R_C_B_K_Q_B_C_R

    // always create a new board where the player with the white pieces is at the bottom of the board (this is a must) otherwise it will mess the players turns and the direction that they have to play

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

	// the program doesn't take in consideration wrong user input!!!! (take care of this later)

	std::cout << "board number:\n";
	std::cin >> board;
	std::cout << "\n";

	std::cout << "white: 1, black: 0\n";
	std::cin >> player;
	std::cout << "\n";

	std::cout << "white turn: 1, black turn: -1\n";
	std::cin >> turn;
	std::cout << "\n";

	Game game(player, board, turn);

	while(game.running()){

		game.update();
		game.render();
	}

	return 0;
}