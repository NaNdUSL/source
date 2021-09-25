#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

#define KING 1
#define QUEEN 2
#define BISHOP 3
#define KNIGHT 4
#define ROOK 5
#define PAWN 6

class Game{

private:

	// Window vars

	sf::RenderWindow* window;
	sf::VideoMode video_mode;
	sf::Event event;

	std::vector<std::vector<int>> board;

	// Mouse vars

	sf::Vector2i mouse_pos;
	sf::Vector2f mouse_pos_view;
	bool mouse_held;

	// Private methods

	void init_vars(){

		this->window = nullptr;
		this->mouse_held = false;
	}

	void init_window(){

		this->video_mode.height = 800;
		this->video_mode.width = 800;
		this->window = new sf::RenderWindow(this->video_mode, "Default", sf::Style::Titlebar | sf::Style::Close);
		this->window->setFramerateLimit(60);
	}

	// void fill_board(std::string input){

	// 	// "RCBQKBCNPPPPPPPP8888PPPPPPPPNCBKQBCR" parseInt

	// 	int row = 0;

	// 	for (int i = 0; i < input.size(); i++){

	// 		if (!input[i].isdigit()){

	// 			switch (input[i]){

	// 				case "R":
	// 				this->board.push_back(ROOK);
	// 				break;

	// 				case "C":
	// 				this->board.push_back(KNIGHT);
	// 				break;
					
	// 				case "B":
	// 				this->board.push_back(BISHOP);
	// 				break;
					
	// 				case "Q":
	// 				this->board.push_back(QUEEN);
	// 				break;
					
	// 				case "K":
	// 				this->board.push_back(KING);
	// 				break;

	// 				case "P":
	// 				this->board.push_back(PAWN);
	// 				break;
	// 			}
	// 		}

	// 		else{


	// 		}
	// 	}
	// }

public:

	// Constructors / Destructors

	Game(){

		this->init_vars();
		// this->fill_board();
		this->init_window();
	}

	virtual ~Game(){

		delete this->window;
	}

	// Accessors

	const bool running(){

		return this->window->isOpen();
	}

	// Methods

	void poll_events(){

		while(this->window->pollEvent(this->event)){

			switch(this->event.type){

				case sf::Event::Closed:

				this->window->close();
			}
		}
	}

/*	void update_board(){

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){

			if (this->mouse_held == false){

				this->mouse_held = true;

				for(int row = 0; row < this->board_side; row++){

					for(int col = 0; col < this->board_side; col++){

						if (this->board[row][col].getFillColor() == sf::Color::Green){

							this->board[row][col].setFillColor(sf::Color::White);
						}

						if (this->board[row][col].getGlobalBounds().contains(this->mouse_pos_view)){

							this->start.clear();
							this->start.push_back(row);
							this->start.push_back(col);
							this->board[row][col].setFillColor(sf::Color::Green);
							// std::cout << "pos: " << this->start[0] << ", " << this->start[1] << "\n";
						}
					}
				}
			}
		}

		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){

			if (this->mouse_held == false){

				this->mouse_held = true;

				for(int row = 0; row < this->board_side; row++){

					for(int col = 0; col < this->board_side; col++){

						if (this->board[row][col].getFillColor() == sf::Color::Red){

							this->board[row][col].setFillColor(sf::Color::White);
						}

						if (this->board[row][col].getGlobalBounds().contains(this->mouse_pos_view)){

							this->board[row][col].setFillColor(sf::Color::Red);
						}
					}
				}
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){

			for(int row = 0; row < this->board_side; row++){

				for(int col = 0; col < this->board_side; col++){

					if (this->board[row][col].getGlobalBounds().contains(this->mouse_pos_view)){

						this->board[row][col].setFillColor(sf::Color::Black);
					}
				}
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)){

			for(int row = 0; row < this->board_side; row++){

				for(int col = 0; col < this->board_side; col++){

					this->board[row][col].setFillColor(sf::Color::White);
				}
			}
		}

		else{

			this->mouse_held = false;
		}
	}
*/
	void update_mouse_pos(){

		this->mouse_pos = sf::Mouse::getPosition(*this->window);
		this->mouse_pos_view = this->window->mapPixelToCoords(this->mouse_pos);
	}

	/*void render_board(sf::RenderTarget &target){

		for (auto &e: this->board){

			for (auto &d: e){

				target.draw(d);
			}
		}
	}*/

	void update(){

		this->poll_events();

		// this->update_mouse_pos();

		// this->update_board();

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
			
			find_path();
		}*/
	}

	void render(){

		this->window->clear(sf::Color(0,0,0,255));

		// this->render_board(*this->window);

		this->window->display();
	}
};