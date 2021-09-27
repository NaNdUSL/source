#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

#define EMPTY 0
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
		this->fill_board("RCBQKBCRPPPPPPPP8888_P_P_P_P_P_P_P_P_R_C_B_K_Q_B_C_R");
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

		// "RCBQKBCRPPPPPPPP8888_P_P_P_P_P_P_P_P_R_C_B_K_Q_B_C_R"

		int row = 0;
		int col = 0;
		std::vector<int> aux;
		int is_black = 1;

		for (int i = 0; i < input.length(); i++){

			if (!std::isdigit(static_cast<unsigned char>(input[i]))){

				if (input[i] == '_'){

					is_black = -1;
					i++;
				}

				switch (input[i]){

					case 'R':
					aux.push_back(5 * is_black);
					break;

					case 'C':
					aux.push_back(4 * is_black);
					break;
					
					case 'B':
					aux.push_back(3 * is_black);
					break;
					
					case 'Q':
					aux.push_back(2 * is_black);
					break;
					
					case 'K':
					aux.push_back(1 * is_black);
					break;

					case 'P':
					aux.push_back(6 * is_black);
					break;
				}

				is_black = 1;
				col++;
			}

			else{

				std::string str(1,input[i]);
				int num = std::stoi(str);

				while (num > 0){

					aux.push_back(0);
					num--;
					col++;
				}
			}

			if (col == 8){

				this->board.push_back(aux);
				aux.clear();
				col = 0;
				row++;
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
				square.setSize(sf::Vector2f(static_cast<int> (800 / 4), static_cast<int> (800 / 4)));
				square.setPosition(static_cast<float> (col*static_cast<int> (800 / this->square_size)), static_cast<float> (row*static_cast<int> (800 / this->square_size)));

				if (color == true){

					square.setFillColor(sf::Color::White);
					color = false;
				}
				else{

					square.setFillColor(sf::Color::Green);
					color = true;
				}

				target.draw(square);
			}
		}

		sf::Sprite sprite;
		sf::Texture texture;
		texture.loadFromFile("Pieces.png");
		sf::Vector2u texture_size = texture.getSize();
		texture_size.x /= 6;
		texture_size.y /= 2;
		sprite.setTexture(texture);
		int draw_it = 1;

		int color_piece = 0;

		for (int i = 0; i < 8; i++){

			for (int j = 0; j < 8; j++){

				if (this->board[i][j] < 0){

					color_piece = 1;
				}

				switch (std::abs(this->board[i][j])){

					case ROOK:
					// std::cout << "3";
					sprite.setTextureRect(sf::IntRect(texture_size.x * 4, texture_size.y * (0 + color_piece), texture_size.x, texture_size.y));
					break;

					case KNIGHT:
					sprite.setTextureRect(sf::IntRect(texture_size.x * 3, texture_size.y * (0 + color_piece), texture_size.x, texture_size.y));
					// std::cout << "4";
					break;

					case BISHOP:
					sprite.setTextureRect(sf::IntRect(texture_size.x * 2, texture_size.y * (0 + color_piece), texture_size.x, texture_size.y));
					// std::cout << "5";
					break;

					case QUEEN:
					sprite.setTextureRect(sf::IntRect(texture_size.x, texture_size.y * (0 + color_piece), texture_size.x, texture_size.y));
					// std::cout << "2";
					break;

					case KING:
					sprite.setTextureRect(sf::IntRect(texture_size.x * 0, texture_size.y * (0 + color_piece), texture_size.x, texture_size.y));
					// std::cout << "1";
					break;

					case PAWN:
					sprite.setTextureRect(sf::IntRect(texture_size.x * 5, texture_size.y * (0 + color_piece), texture_size.x, texture_size.y));
					// std::cout << "6";
					break;

					case EMPTY:
					draw_it = 0;
					break;
				}

				color_piece = 0;

				if (draw_it){

					sprite.setScale(sf::Vector2f(this->square_size * 0.035, this->square_size * 0.035));
					sprite.setPosition(static_cast<float> (j*static_cast<int> (800 / this->square_size)), static_cast<float> (i*static_cast<int> (800 / this->square_size)));
					target.draw(sprite);
				}

				draw_it = 1;
			}
		}
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