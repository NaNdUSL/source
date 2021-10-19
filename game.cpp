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
#include <ctime>

#define EMPTY 0
#define KING 1
#define QUEEN 2
#define BISHOP 3
#define KNIGHT 4
#define ROOK 5
#define PAWN 6

// Piece class

class Piece{

private:

	int id;
	sf::Sprite piece;

public:

	Piece(){

		this->id = EMPTY;
		sf::Sprite sprite;
		this->piece = sprite;
	}

	Piece(int id, sf::Sprite sprite){

		this->id = id;
		this->piece = sprite;
	}

	void set_id(int id){

		this->id = id;
	}

	void set_piece(sf::Sprite sprite){

		this->piece = sprite;
	}

	int get_id(){

		int id = this->id;
		return id;
	}

	sf::Sprite get_piece(){

		sf::Sprite sprite;
		sprite = this->piece;
		return sprite;
	}
};

// Pieces class

class Pieces{

private:

	std::map<int, Piece> pieces;
	std::string texture;
	sf::Vector2u texture_size;

public:


	Pieces(){

		std::map<int, Piece> pieces;
		this->pieces = pieces;
		this->texture = "default.png";
		sf::Vector2u texture_size(0.0f, 0.0f);
		this->texture_size = texture_size;
	}

	Pieces(std::map<int, Piece> pieces, char str[], sf::Vector2u texture_size){

		this->pieces = pieces;
		this->texture = str;
		this->texture_size = texture_size;
	}

	void set_pieces(std::map<int, Piece> pieces){

		this->pieces = pieces;
	}

	void set_texture(std::string str){

		this->texture = str;
	}

	void set_texture_size(sf::Vector2u texture_size){

		this->texture_size = texture_size;
	}

	std::map<int, Piece> get_pieces(){

		std::map<int, Piece> pieces;
		pieces = this->pieces;
		return pieces;
	}

	std::string get_texture(){

		std::string str = this->texture;
		return str;
	}

	sf::Vector2u get_texture_size(){

		sf::Vector2u texture_size;
		texture_size = this->texture_size;
		return texture_size;
	}

	void insert_elem(int num, Piece piece){

		this->pieces.insert({num, piece});
	}
};


// Board class

class Boards{

private:

	std::vector<std::vector<sf::RectangleShape>> board_image;
	std::vector<std::vector<int>> board;
	int square_size;
	Pieces pieces;

public:

	Boards(){

		std::vector<std::vector<int>> board;
		this->board = board;
		std::vector<std::vector<sf::RectangleShape>> board_image;
		this->board_image = board_image;
		this->square_size = 8;
	}

	Boards(std::vector<std::vector<sf::RectangleShape>> board_image, std::vector<std::vector<int>> board, int square_size){

		this->board_image = board_image;
		this->board = board;
		this->square_size = square_size;
	}

	void set_board(std::vector<std::vector<int>> board){

		this->board = board;
	}

	void set_board_image(std::vector<std::vector<sf::RectangleShape>> board_image){

		this->board_image = board_image;
	}

	void set_square_size(int square_size){

		this->square_size = square_size;
	}

	std::vector<std::vector<int>> get_board(){

		std::vector<std::vector<int>> board;
		board = this->board;
		return board;
	}

	std::vector<std::vector<sf::RectangleShape>> get_board_image(){

		std::vector<std::vector<sf::RectangleShape>> board_image;
		board_image = this->board_image;
		return board_image;
	}

	int get_square_size(){

		int size = this->square_size;
		return size;
	}

	Pieces get_pieces(){

		Pieces pieces = this->pieces;
		return pieces;
	}

	// read from string input

	void fill_board(std::string input){

		// "RCBQKBCRPPPPPPPP8888_P_P_P_P_P_P_P_P_R_C_B_K_Q_B_C_R"

		int row = 0;
		int col = 0;
		std::vector<int> aux;
		int is_black = 1;
		int pawn = 1;
		int bishop = 1;
		int rook = 1;
		int knight = 1;

		for (int i = 0; i < input.length(); i++){

			if (!std::isdigit(static_cast<unsigned char>(input[i]))){

				if (input[i] == '_'){

					is_black = -1;
					i++;
				}

				switch (input[i]){

					case 'R':
					if (rook > 2) rook = 0;
					aux.push_back((50 + rook++) * is_black);
					break;

					case 'C':
					if (knight > 2) knight = 0;
					aux.push_back((40 + knight++) * is_black);
					break;

					case 'B':
					if (bishop > 2) bishop = 0;
					aux.push_back((30 + bishop++) * is_black);
					break;

					case 'Q':
					aux.push_back(20 * is_black);
					break;

					case 'K':
					aux.push_back(10 * is_black);
					break;

					case 'P':
					if (pawn > 8) pawn = 0;
					aux.push_back((60 + pawn++) * is_black);
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

	void fill_helping_board(){

		std::vector<sf::RectangleShape> aux;
		bool color;

		for (int row = 0; row < 8; row++){

			if (row % 2 == 0){

				color = true;
			}
			else{

				color = false;
			}

			aux.clear();

			for (int col = 0; col < 8; col++){

				sf::RectangleShape square;
				square.setSize(sf::Vector2f(static_cast<int> (800 / this->square_size), static_cast<int> (800 / this->square_size)));
				square.setPosition(static_cast<float> (col * static_cast<int> (800 / this->square_size)), static_cast<float> (row * static_cast<int> (800 / this->square_size)));

				if (color == true){

					square.setFillColor(sf::Color::White);
					color = false;
				}
				else{

					square.setFillColor(sf::Color(60, 60, 60, 255));
					color = true;
				}

				aux.push_back(square);
			}

			this->board_image.push_back(aux);
		}
	}

	void load_pieces(){

		int color_piece = 0;
		int color_sprite = 0;

		for (int i = 0; i < 8; i++){

			for (int j = 0; j < 8; j++){

				if (this->board[i][j] != EMPTY){

					if (this->board[i][j] < 0){

						color_piece = 1;
						color_sprite = 2;
					}

					sf::Sprite sprite;
					sprite.setScale(sf::Vector2f(this->square_size * 0.035, this->square_size * 0.035));
					sprite.setPosition(static_cast<float> (j * static_cast<int> (800 / this->square_size)), static_cast<float> (i * static_cast<int> (800 / this->square_size)));
					sf::Vector2u texture_size = this->pieces.get_texture_size();
					
					switch (std::abs(this->board[i][j]) / 10) {

						case ROOK:
					// std::cout << "3";

						sprite.setTextureRect(sf::IntRect(texture_size.x * 4, texture_size.y * color_piece, texture_size.x, texture_size.y));
						break;

						case KNIGHT:
						sprite.setTextureRect(sf::IntRect(texture_size.x * 3, texture_size.y * color_piece, texture_size.x, texture_size.y));
					// std::cout << "4";
						break;

						case BISHOP:
						sprite.setTextureRect(sf::IntRect(texture_size.x * 2, texture_size.y * color_piece, texture_size.x, texture_size.y));
					// std::cout << "5";
						break;

						case QUEEN:
						sprite.setTextureRect(sf::IntRect(texture_size.x, texture_size.y * color_piece, texture_size.x, texture_size.y));
					// std::cout << "2";
						break;

						case KING:
						sprite.setTextureRect(sf::IntRect(texture_size.x * 0, texture_size.y * color_piece, texture_size.x, texture_size.y));
					// std::cout << "1";
						break;

						case PAWN:
						sprite.setTextureRect(sf::IntRect(texture_size.x * 5, texture_size.y * color_piece, texture_size.x, texture_size.y));
					// std::cout << "6";
						break;
					}

					color_piece = 0;
					Piece result(this->board[i][j], sprite);
					this->pieces.insert_elem(this->board[i][j], result);
				}
			}
		}
	}

	void set_texture_size(sf::Vector2u size, int x, int y){

		sf::Vector2u aux(size.x / x, size.y / y);
		this->pieces.set_texture_size(aux);
	}
};


// Game class

class Game{

private:

	// Window vars

	sf::RenderWindow* window;
	sf::VideoMode video_mode;
	sf::Event event;

	// Mouse vars

	sf::Vector2i mouse_pos;
	sf::Vector2f mouse_pos_view;

	// Other classes

	Boards boards;
	sf::Texture texture;

	// Helping vars

	bool mouse_held;
	bool holding;
	bool dragging;
	int piece_held;
	
	// Private methods

	void init_vars(){

		this->window = nullptr;
		if(!this->texture.loadFromFile("Pieces.png")){

			std::cout << "Problem loading textures\n";
		}
		this->holding = false;
		this->dragging = false;
		this->piece_held = 0;
	}

	void init_window(){

		this->video_mode.height = 800;
		this->video_mode.width = 800;
		this->window = new sf::RenderWindow(this->video_mode, "Default", sf::Style::Titlebar | sf::Style::Close);
		this->window->setFramerateLimit(144);
	}

public:

	// Constructors / Destructors

	Game(){

		this->init_vars();
		this->boards.set_texture_size(this->texture.getSize(), 6, 2);
		this->boards.fill_board("RCBQKBCRPPPPPPPP8888_P_P_P_P_P_P_P_P_R_C_B_Q_K_B_C_R");
		this->boards.fill_helping_board();
		this->boards.load_pieces();
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

/*
 51  41  31  20  10  32  42  52
 61  62  63  64  65  66  60  61
  0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0
  0   0   0   0   0   0   0   0
-62 -63 -64 -65 -66 -60 -61 -62
-50 -40 -30 -20 -10 -31 -41 -51
*/

	void update_board(){

		if(!this->dragging){

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){

				this->dragging = true;

				for (std::pair<int, sf::Sprite> element : this->boards.get_pieces()){

					if (element.second.getGlobalBounds().contains(this->mouse_pos_view)){

						this->piece_held = element.first;
					}
				}

			}
            this->setPosition(mousePosition.x - this->sprite.getGlobalBounds().width/2,mousePosition.y - this->sprite.getGlobalBounds().height/2);
        }
        else{

            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                this->moving = true;
                movingAPiece = true;
            }
        }

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){

				if (!this->piece_held){

					for (std::pair<int, sf::Sprite> element : this->pieces){

						if (element.second.getGlobalBounds().contains(this->mouse_pos_view)){

							this->holding = true;
							this->piece_held = element.first;
						}
					}
				}

				this->pieces.find(this->piece_held)->second.setPosition(static_cast<float> (this->mouse_pos_view.x - static_cast<float> (this->texture_size.x) / this->square_size), static_cast<float> (this->mouse_pos_view.y - static_cast<float> (this->texture_size.y) / this->square_size));
			}
		else if (sf::Event::MouseButtonReleased(sf::Mouse::Left)){

			this->holding = false;
		}
	}



// 			if (this->mouse_held == false){

// 				this->mouse_held = true;

// 				for(int row = 0; row < this->square_size; row++){

// 					for(int col = 0; col < this->square_size; col++){

// 						if (this->board[row][col].getFillColor() == sf::Color::Green){

// 							this->board[row][col].setFillColor(sf::Color::White);
// 						}

// 						if (this->board[row][col].getGlobalBounds().contains(this->mouse_pos_view)){

// 							this->start.clear();
// 							this->start.push_back(row);
// 							this->start.push_back(col);
// 							this->board[row][col].setFillColor(sf::Color::Green);
// 							// std::cout << "pos: " << this->start[0] << ", " << this->start[1] << "\n";
// 						}
// 					}
// 				}
// 			}
// */
// 		// if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){

// 		// 	if (this->mouse_held == false){

// 		// 		this->mouse_held = true;

// 		// 		for(int row = 0; row < this->square_size; row++){

// 		// 			for(int col = 0; col < this->square_size; col++){

// 		// 				if (this->board[row][col].getFillColor() == sf::Color::Red){

// 		// 					this->board[row][col].setFillColor(sf::Color::White);
// 		// 				}

// 		// 				if (this->board[row][col].getGlobalBounds().contains(this->mouse_pos_view)){

// 		// 					this->board[row][col].setFillColor(sf::Color::Red);
// 		// 				}
// 		// 			}
// 		// 		}
// 		// 	}
// 		// }
// /*
// 		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){

// 			for(int row = 0; row < this->square_size; row++){

// 				for(int col = 0; col < this->square_size; col++){

// 					if (this->board[row][col].getGlobalBounds().contains(this->mouse_pos_view)){

// 						this->board[row][col].setFillColor(sf::Color::Black);
// 					}
// 				}
// 			}
// 		}

// 		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)){

// 			for(int row = 0; row < this->square_size; row++){

// 				for(int col = 0; col < this->square_size; col++){

// 					this->board[row][col].setFillColor(sf::Color::White);
// 				}
// 			}
// 		}

	// }

	void update_mouse_pos(){

		this->mouse_pos = sf::Mouse::getPosition(*this->window);
		this->mouse_pos_view = this->window->mapPixelToCoords(this->mouse_pos);
	}

	void render_board(sf::RenderTarget &target){

		bool color;

		for (auto &e: this->boards.get_board_image()){

			for (auto &d: e){

				target.draw(d);
			}
		}

		for (int i = 0; i < 8; i++){

			for (int j = 0; j < 8; j++){

				sf::Sprite sprite;
				sprite = this->boards.get_pieces().get_pieces().find(this->boards.get_board()[i][j])->second.get_piece();
				sprite.setTexture(this->texture);
				target.draw(sprite);
			}
		}
	}

	void update(){

		this->poll_events();

		this->update_mouse_pos();

		this->update_board();

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