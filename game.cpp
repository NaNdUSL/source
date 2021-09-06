#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>

#define NORMAL 0
#define START 1
#define END 2

class Game{

private:

	// Window vars

	sf::RenderWindow* window;
	sf::VideoMode video_mode;
	sf::Event event;

	int board_side;
	int square_size;
	std::vector<std::vector<sf::RectangleShape>> board;

	// Mouse vars

	sf::Vector2i mouse_pos;
	sf::Vector2f mouse_pos_view;
	bool mouse_held;

	// Private methods

	void init_vars(){

		this->window = nullptr;
		this->board_side = 50;
		this->square_size = 10;
		this->mouse_held = false;
	}

	void init_window(){

		this->video_mode.height = 800;
		this->video_mode.width = 800;
		this->window = new sf::RenderWindow(this->video_mode, "Default", sf::Style::Titlebar | sf::Style::Close);
		this->window->setFramerateLimit(60);
	}

	void fill_board(){

		for (int row = 0; row < this->board_side; row++){

			std::vector<sf::RectangleShape> aux;

			for (int col = 0; col < this->board_side; col++){

				sf::RectangleShape square;
				square.setFillColor(sf::Color::White);
				square.setSize(sf::Vector2f(static_cast<int> (800 / this->board_side), static_cast<int> (800 / this->board_side)));
				square.setPosition(static_cast<float> (col*static_cast<int> (800 / this->board_side)), static_cast<float> (row*static_cast<int> (800 / this->board_side)));
				square.setOutlineThickness(1.2f);
				square.setOutlineColor(sf::Color::Black);
				aux.push_back(square);
			}

			board.push_back(aux);
		}
	}

public:

	// Constructors / Destructors

	Game(){

		this->init_vars();
		this->fill_board();
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

	void update_board(){

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){

			if (this->mouse_held == false){

				this->mouse_held = true;

				for(int row = 0; row < this->board_side; row++){

					for(int col = 0; col < this->board_side; col++){

						if (this->board[row][col].getFillColor() == sf::Color::Green){

							this->board[row][col].setFillColor(sf::Color::White);
						}

						if (this->board[row][col].getGlobalBounds().contains(this->mouse_pos_view)){

							this->board[row][col].setFillColor(sf::Color::Green);
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

		else{

			this->mouse_held = false;
		}
	}

	void update_mouse_pos(){

		this->mouse_pos = sf::Mouse::getPosition(*this->window);
		this->mouse_pos_view = this->window->mapPixelToCoords(this->mouse_pos);
	}

	void render_board(sf::RenderTarget &target){

		for (auto &e: this->board){

			for (auto &d: e){

				target.draw(d);
			}
		}
	}

	void update(){

		this->poll_events();

		this->update_mouse_pos();

		this->update_board();

		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
			
		// 	find_path();
		// }
	}

	void render(){

		this->window->clear(sf::Color(0,0,0,255));

		this->render_board(*this->window);

		this->window->display();
	}
};
