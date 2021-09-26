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
	int square_size;

	// Mouse vars

	sf::Vector2i mouse_pos;
	sf::Vector2f mouse_pos_view;
	bool mouse_held;

	// Private methods

	void init_vars(){

		this->window = nullptr;
		this->fill_board("RCBQKBCRPPPPPPPP8888PPPPPPPPRCBKQBCR");
		this->square_size = 8;
		this->mouse_held = false;
	}

	void init_window(){

		this->video_mode.height = 800;
		this->video_mode.width = 800;
		this->window = new sf::RenderWindow(this->video_mode, "Default", sf::Style::Titlebar | sf::Style::Close);
		this->window->setFramerateLimit(60);
	}

	void fill_board(std::string input){

		// "RCBQKBCNPPPPPPPP8888PPPPPPPPNCBKQBCR" parseInt

		int row = 0;
		int col = 0;
		std::vector<int> aux;

		for (int i = 0; i < input.length(); i++){

			if (col == 8){

				// std::cout << "\n";
				this->board.push_back(aux);
				aux.clear();
				col = 0;
				row++;
			}

			if (!std::isdigit(static_cast<unsigned char>(input[i]))){

				switch (input[i]){

					case 'R':
					// std::cout << "3";
					aux.push_back(3);
					break;

					case 'C':
					// std::cout << "4";
					aux.push_back(4);
					break;
					
					case 'B':
					// std::cout << "5";
					aux.push_back(5);
					break;
					
					case 'Q':
					// std::cout << "2";
					aux.push_back(2);
					break;
					
					case 'K':
					// std::cout << "1";
					aux.push_back(1);
					break;

					case 'P':
					// std::cout << "6";
					aux.push_back(6);
					break;
				}

				col++;
			}

			else{

				std::string str(1,input[i]);
				int num = std::stoi(str);

				while (num > 0){

					// std::cout << "0";
					aux.push_back(0);
					num--;
					col++;
				}
			}
		}
	}

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

				for(int row = 0; row < this->square_size; row++){

					for(int col = 0; col < this->square_size; col++){

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

				for(int row = 0; row < this->square_size; row++){

					for(int col = 0; col < this->square_size; col++){

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

			for(int row = 0; row < this->square_size; row++){

				for(int col = 0; col < this->square_size; col++){

					if (this->board[row][col].getGlobalBounds().contains(this->mouse_pos_view)){

						this->board[row][col].setFillColor(sf::Color::Black);
					}
				}
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)){

			for(int row = 0; row < this->square_size; row++){

				for(int col = 0; col < this->square_size; col++){

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

	void render_board(sf::RenderTarget &target){

		bool color;

		for (int row = 0; row < 8; row++){

			if (row % 2 == 0){

				color = true;
			}
			else{

				color = false;
			}

			for (int col = 0; col < 8; col++){

				sf::RectangleShape square;
				square.setSize(sf::Vector2f(static_cast<int> (800 / this->square_size), static_cast<int> (800 / this->square_size)));
				square.setPosition(static_cast<float> (col*static_cast<int> (800 / this->square_size)), static_cast<float> (row*static_cast<int> (800 / this->square_size)));

				if (color == true){

					square.setFillColor(sf::Color::White);
					color = false;
				}
				else{

					square.setFillColor(sf::Color::Black);
					color = true;
				}

				target.draw(square);
			}
		}

		/*for (auto &e: this->board){

			for (auto &d: e){

				target.draw(d);
			}
		}*/
	}

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

		this->render_board(*this->window);

		this->window->display();
	}
};