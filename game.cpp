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

	void set_pos(float x, float y){

		this->piece.setPosition(x, y);
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

	void set_piece_pos(int num, float x, float y){

		this->pieces.find(num)->second.set_pos(x, y);
	}

	void delete_piece(int num){

		std::map<int, Piece>::iterator piece = this->pieces.find(num);
		this->pieces.erase(piece); 
	}
};


// Board class

class Boards{

private:

	std::vector<std::vector<sf::RectangleShape>> board_image;
	std::vector<std::vector<int>> board;
	int square_size;
	Pieces pieces;
	int dir;
	std::vector<int> check_piece;


public:

	Boards(){

		std::vector<std::vector<int>> board;
		this->board = board;
		std::vector<std::vector<sf::RectangleShape>> board_image;
		this->board_image = board_image;
		this->square_size = 8;
	}

	Boards(std::vector<std::vector<sf::RectangleShape>> board_image, std::vector<std::vector<int>> board, int square_size, int dir){

		this->board_image = board_image;
		this->board = board;
		this->square_size = square_size;
		this->dir = dir;
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

	void set_check_piece(std::vector<int> piece){

		this->check_piece = piece;
	}

	void set_dir(int dir){

		this->dir = dir;
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

	std::vector<int> get_check_piece(){

		std::vector<int> piece = this->check_piece;
		return piece;
	}

	int get_dir(){

		int dir = this->dir;
		return dir;
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
					if (rook > 2) rook = 1;
					aux.push_back((50 + rook++) * is_black);
					break;

					case 'C':
					if (knight > 2) knight = 1;
					aux.push_back((40 + knight++) * is_black);
					break;

					case 'B':
					if (bishop > 2) bishop = 1;
					aux.push_back((30 + bishop++) * is_black);
					break;

					case 'Q':
					aux.push_back(20 * is_black);
					break;

					case 'K':
					aux.push_back(10 * is_black);
					break;

					case 'P':
					if (pawn > 8) pawn = 1;
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

					square.setFillColor(sf::Color(150, 150, 150, 255));
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

	void set_pieces_pos(int num, float x, float y){

		this->pieces.set_piece_pos(num, x, y);
	}


	int countDigit(long long n){

		int count = 0;

		while (n != 0){

			n = n / 10;
			count++;
		}

		return count;
	}

	void display_board(){

		for (int i = 0; i < 8; i++){

			for (int j = 0; j < 8; j++){

				int var = countDigit(this->board[i][j]);

				if (this->board[i][j] > 0){

					var--;
				}

				while(3 - var > 0){

					std::cout << " ";
					var++;
				}

				std::cout << this->board[i][j];
			}

			std::cout << "\n";
		}

		std::cout << "\n\n\n";
	}

	void new_pos(int prev_x, int prev_y, int new_x, int new_y){

		int prev_piece = this->board[prev_x][prev_y];
		int res = this->board[new_x][new_y];

		if (prev_x != new_x || prev_y != new_y){

			this->board[new_x][new_y] = prev_piece;
			this->board[prev_x][prev_y] = 0;

			if (res != 0){

				this->pieces.delete_piece(res);
			}
		}
	}

	bool not_check(int pos_x, int pos_y, int piece, bool update){

		bool safe = true;
		int signal = piece / std::abs(piece);
		bool not_found = true;


		// Check upwards

		for (int i = 1; not_found && pos_x - i >= 0; i++){
			
			if (this->board[pos_x - i][pos_y] != 0){

				not_found = false;

				if (std::abs(this->board[pos_x - i][pos_y]) / 10 == KING && std::abs(i) == 1 && signal * this->board[pos_x - i][pos_y] < 0){

					safe = false;
					// std::cout << "safe 1: " << safe  << "\n";
				}

				if ((std::abs(this->board[pos_x - i][pos_y]) / 10 == ROOK || std::abs(this->board[pos_x - i][pos_y]) / 10 == QUEEN) && signal * this->board[pos_x - i][pos_y] < 0){

					safe = false;

					if (update){

						std::vector<int> check_piece;
						check_piece.push_back(this->board[pos_x - i][pos_y]);
						check_piece.push_back(pos_x - i);
						check_piece.push_back(pos_y);
						this->set_check_piece(check_piece);
					}
					// std::cout << "safe 1: " << safe  << "\n";
				}
			}
		}


		// Check downwards

		not_found = true;

		for (int i = 1; not_found && pos_x + i < 8; i++){
			
			if (this->board[pos_x + i][pos_y] != 0){

				not_found = false;

				if (std::abs(this->board[pos_x + i][pos_y]) / 10 == KING && std::abs(i) == 1 && signal * this->board[pos_x + i][pos_y] < 0){

					safe = false;
					// std::cout << "safe 2: " << safe  << "\n";
				}

				if ((std::abs(this->board[pos_x + i][pos_y]) / 10 == ROOK || std::abs(this->board[pos_x + i][pos_y]) / 10 == QUEEN) && signal * this->board[pos_x + i][pos_y] < 0){

					safe = false;

					if (update){

						std::vector<int> check_piece;
						check_piece.push_back(this->board[pos_x + i][pos_y]);
						check_piece.push_back(pos_x + i);
						check_piece.push_back(pos_y);
						this->set_check_piece(check_piece);
					}
					// std::cout << "safe 2: " << safe  << "\n";
				}
			}
		}


		// Check left

		not_found = true;

		for (int i = 1; not_found && pos_y - i >= 0; i++){
			
			if (this->board[pos_x][pos_y - i] != 0){

				not_found = false;

				if (std::abs(this->board[pos_x][pos_y - i]) / 10 == KING && std::abs(i) == 1 && signal * this->board[pos_x][pos_y - i] < 0){

					safe = false;
					// std::cout << "safe 3: " << safe  << "\n";
				}

				if ((std::abs(this->board[pos_x][pos_y - i]) / 10 == ROOK || std::abs(this->board[pos_x][pos_y - i]) / 10 == QUEEN) && signal * this->board[pos_x][pos_y - i] < 0){

					safe = false;

					if (update){

						std::vector<int> check_piece;
						check_piece.push_back(this->board[pos_x][pos_y - i]);
						check_piece.push_back(pos_x);
						check_piece.push_back(pos_y - i);
						this->set_check_piece(check_piece);
					}
					// std::cout << "safe 3: " << safe  << "\n";
				}
			}
		}


		// Check right

		not_found = true;

		for (int i = 1; not_found && pos_y + i < 8; i++){
			
			if (this->board[pos_x][pos_y + i] != 0){

				not_found = false;

				if (std::abs(this->board[pos_x][pos_y + i]) / 10 == KING && std::abs(i) == 1 && signal * this->board[pos_x][pos_y + i] < 0){

					safe = false;
					// std::cout << "safe 4: " << safe  << "\n";
				}

				if ((std::abs(this->board[pos_x][pos_y + i]) / 10 == ROOK || std::abs(this->board[pos_x][pos_y + i]) / 10 == QUEEN) && signal * this->board[pos_x][pos_y + i] < 0){

					safe = false;

					if (update){

						std::vector<int> check_piece;
						check_piece.push_back(this->board[pos_x][pos_y + i]);
						check_piece.push_back(pos_x);
						check_piece.push_back(pos_y + i);
						this->set_check_piece(check_piece);
					}
					// std::cout << "safe 4: " << safe  << "\n";
				}
			}
		}


		// up left

		not_found = true;

		for (int i = 1; not_found && pos_x - i >= 0 && pos_y - i >= 0; i++){
			
			if (this->board[pos_x - i][pos_y - i] != 0){

				not_found = false;

				if (std::abs(this->board[pos_x - i][pos_y - i]) / 10 == KING && std::abs(i) == 1 && signal * this->board[pos_x - i][pos_y - i] < 0){

					safe = false;
					// std::cout << "safe 5: " << safe  << "\n";
				}

				if(this->dir == -i){

					if (std::abs(this->board[pos_x - i][pos_y - i]) / 10 == PAWN && std::abs(i) == 1 && signal * this->board[pos_x - i][pos_y - i] < 0){

						safe = false;

						if (update){

							std::vector<int> check_piece;
							check_piece.push_back(this->board[pos_x - i][pos_y - i]);
							check_piece.push_back(pos_x - i);
							check_piece.push_back(pos_y - i);
							this->set_check_piece(check_piece);
						}
						// std::cout << "safe 5: " << safe  << "\n";
					}
				}

				if ((std::abs(this->board[pos_x - i][pos_y - i]) / 10 == BISHOP || std::abs(this->board[pos_x - i][pos_y - i]) / 10 == QUEEN) && signal * this->board[pos_x - i][pos_y - i] < 0){

					safe = false;

					if (update){

						std::vector<int> check_piece;
						check_piece.push_back(this->board[pos_x - i][pos_y - i]);
						check_piece.push_back(pos_x - i);
						check_piece.push_back(pos_y - i);
						this->set_check_piece(check_piece);
					}
					// std::cout << "safe 5: " << safe  << "\n";
				}
			}
		}


		// up right

		not_found = true;

		for (int i = 1; not_found && pos_x - i >= 0 && pos_y + i < 8; i++){
			
			if (this->board[pos_x - i][pos_y + i] != 0){

				not_found = false;

				if (std::abs(this->board[pos_x - i][pos_y + i]) / 10 == KING && std::abs(i) == 1 && signal * this->board[pos_x - i][pos_y + i] < 0){

					safe = false;
					// std::cout << "safe 6: " << safe  << "\n";
				}

				if(this->dir == -i){

					if (std::abs(this->board[pos_x - i][pos_y + i]) / 10 == PAWN && std::abs(i) == 1 && signal * this->board[pos_x - i][pos_y + i] < 0){

						safe = false;

						if (update){

							std::vector<int> check_piece;
							check_piece.push_back(this->board[pos_x - i][pos_y + i]);
							check_piece.push_back(pos_x - i);
							check_piece.push_back(pos_y + i);
							this->set_check_piece(check_piece);
						}
						// std::cout << "safe 6: " << safe  << "\n";
					}
				}

				if ((std::abs(this->board[pos_x - i][pos_y + i]) / 10 == BISHOP || std::abs(this->board[pos_x - i][pos_y + i]) / 10 == QUEEN) && signal * this->board[pos_x - i][pos_y + i] < 0){

					safe = false;

					if (update){

						std::vector<int> check_piece;
						check_piece.push_back(this->board[pos_x - i][pos_y + i]);
						check_piece.push_back(pos_x - i);
						check_piece.push_back(pos_y + i);
						this->set_check_piece(check_piece);
					}
					// std::cout << "safe 6: " << safe  << "\n";
				}
			}
		}


		// down left

		not_found = true;

		for (int i = 1; not_found && pos_x + i < 8 && pos_y - i >= 0; i++){
			
			if (this->board[pos_x + i][pos_y - i] != 0){

				not_found = false;

				if (std::abs(this->board[pos_x + i][pos_y - i]) / 10 == KING && std::abs(i) == 1 && signal * this->board[pos_x + i][pos_y - i] < 0){

					safe = false;
					// std::cout << "safe 7: " << safe  << "\n";
				}

				if(this->dir == i){

					if (std::abs(this->board[pos_x + i][pos_y - i]) / 10 == PAWN && std::abs(i) == 1 && signal * this->board[pos_x + i][pos_y - i] < 0){

						safe = false;

						if (update){

							std::vector<int> check_piece;
							check_piece.push_back(this->board[pos_x + i][pos_y - i]);
							check_piece.push_back(pos_x + i);
							check_piece.push_back(pos_y - i);
							this->set_check_piece(check_piece);
						}
						// std::cout << "safe 7: " << safe  << "\n";
					}
				}

				if ((std::abs(this->board[pos_x + i][pos_y - i]) / 10 == BISHOP || std::abs(this->board[pos_x + i][pos_y - i]) / 10 == QUEEN) && signal * this->board[pos_x + i][pos_y - i] < 0){

					safe = false;

					if (update){

						std::vector<int> check_piece;
						check_piece.push_back(this->board[pos_x + i][pos_y - i]);
						check_piece.push_back(pos_x + i);
						check_piece.push_back(pos_y - i);
						this->set_check_piece(check_piece);
					}
				}
			}
		}


		// down right

		not_found = true;

		for (int i = 1; not_found && pos_x + i < 8 && pos_y + i < 8; i++){
			
			if (this->board[pos_x + i][pos_y + i] != 0){

				not_found = false;

				if (std::abs(this->board[pos_x + i][pos_y + i]) / 10 == KING && std::abs(i) == 1 && signal * this->board[pos_x + i][pos_y + i] < 0){

					safe = false;
					// std::cout << "safe 8: " << safe  << "\n";
				}

				if(this->dir == i){

					if (std::abs(this->board[pos_x + i][pos_y + i]) / 10 == PAWN && std::abs(i) == 1 && signal * this->board[pos_x + i][pos_y + i] < 0){

						safe = false;

						if (update){

							std::vector<int> check_piece;
							check_piece.push_back(this->board[pos_x + i][pos_y + i]);
							check_piece.push_back(pos_x + i);
							check_piece.push_back(pos_y + i);
							this->set_check_piece(check_piece);
						}
						// std::cout << "safe 8: " << safe  << "\n";
					}
				}

				if ((std::abs(this->board[pos_x + i][pos_y + i]) / 10 == BISHOP || std::abs(this->board[pos_x + i][pos_y + i]) / 10 == QUEEN) && signal * this->board[pos_x + i][pos_y + i] < 0){

					safe = false;

					if (update){

						std::vector<int> check_piece;
						check_piece.push_back(this->board[pos_x + i][pos_y + i]);
						check_piece.push_back(pos_x + i);
						check_piece.push_back(pos_y + i);
						this->set_check_piece(check_piece);
					}
					// std::cout << "safe 8: " << safe  << "\n";
				}
			}
		}


		// Knight check

		if (pos_x - 1 >= 0 && pos_y - 2 >= 0 && this->board[pos_x - 1][pos_y - 2] != 0){

			if (std::abs(this->board[pos_x - 1][pos_y - 2]) / 10 == KNIGHT && signal * this->board[pos_x - 1][pos_y - 2] < 0){

				safe = false;

				if (update){

					std::vector<int> check_piece;
					check_piece.push_back(this->board[pos_x - 1][pos_y - 2]);
					check_piece.push_back(pos_x - 1);
					check_piece.push_back(pos_y - 2);
					this->set_check_piece(check_piece);
				}
				// std::cout << "safe 9: " << safe  << "\n";
			}
		}

		if (pos_x - 2 >= 0 && pos_y - 1 >= 0 && this->board[pos_x - 2][pos_y - 1] != 0){

			if (std::abs(this->board[pos_x - 2][pos_y - 1]) / 10 == KNIGHT && signal * this->board[pos_x - 2][pos_y - 1] < 0){

				safe = false;

				if (update){

					std::vector<int> check_piece;
					check_piece.push_back(this->board[pos_x - 2][pos_y - 1]);
					check_piece.push_back(pos_x - 2);
					check_piece.push_back(pos_y - 1);
					this->set_check_piece(check_piece);
				}
				// std::cout << "safe 9: " << safe  << "\n";
			}
		}

		if (pos_x - 2 >= 0 && pos_y + 1 < 8 && this->board[pos_x - 2][pos_y + 1] != 0){

			if (std::abs(this->board[pos_x - 2][pos_y + 1]) / 10 == KNIGHT && signal * this->board[pos_x - 2][pos_y + 1] < 0){

				safe = false;

				if (update){

					std::vector<int> check_piece;
					check_piece.push_back(this->board[pos_x - 2][pos_y + 1]);
					check_piece.push_back(pos_x - 2);
					check_piece.push_back(pos_y + 1);
					this->set_check_piece(check_piece);
				}
				// std::cout << "safe 9: " << safe  << "\n";
			}
		}

		if (pos_x - 1 >= 0 && pos_y + 2 < 8 && this->board[pos_x - 1][pos_y + 2] != 0){

			if (std::abs(this->board[pos_x - 1][pos_y + 2]) / 10 == KNIGHT && signal * this->board[pos_x - 1][pos_y + 2] < 0){

				safe = false;

				if (update){

					std::vector<int> check_piece;
					check_piece.push_back(this->board[pos_x - 1][pos_y + 2]);
					check_piece.push_back(pos_x - 1);
					check_piece.push_back(pos_y + 2);
					this->set_check_piece(check_piece);
				}
				// std::cout << "safe 9: " << safe  << "\n";
			}
		}

		if (pos_x + 1 < 8 && pos_y + 2 < 8 && this->board[pos_x + 1][pos_y + 2] != 0){

			if (std::abs(this->board[pos_x + 1][pos_y + 2]) / 10 == KNIGHT && signal * this->board[pos_x + 1][pos_y + 2] < 0){

				safe = false;

				if (update){

					std::vector<int> check_piece;
					check_piece.push_back(this->board[pos_x + 1][pos_y + 2]);
					check_piece.push_back(pos_x + 1);
					check_piece.push_back(pos_y + 2);
					this->set_check_piece(check_piece);
				}
				// std::cout << "safe 9: " << safe  << "\n";
			}
		}

		if (pos_x + 2 < 8 && pos_y + 1 < 8 && this->board[pos_x + 2][pos_y + 1] != 0){

			if (std::abs(this->board[pos_x + 2][pos_y + 1]) / 10 == KNIGHT && signal * this->board[pos_x + 2][pos_y + 1] < 0){

				safe = false;

				if (update){

					std::vector<int> check_piece;
					check_piece.push_back(this->board[pos_x + 2][pos_y + 1]);
					check_piece.push_back(pos_x + 2);
					check_piece.push_back(pos_y + 1);
					this->set_check_piece(check_piece);
				}
				// std::cout << "safe 9: " << safe  << "\n";
			}
		}

		if (pos_x + 2 < 8 && pos_y - 1 >= 0 && this->board[pos_x + 2][pos_y - 1] != 0){

			if (std::abs(this->board[pos_x + 2][pos_y - 1]) / 10 == KNIGHT && signal * this->board[pos_x + 2][pos_y - 1] < 0){

				safe = false;

				if (update){

					std::vector<int> check_piece;
					check_piece.push_back(this->board[pos_x + 2][pos_y - 1]);
					check_piece.push_back(pos_x + 2);
					check_piece.push_back(pos_y - 1);
					this->set_check_piece(check_piece);
				}
				// std::cout << "safe 9: " << safe  << "\n";
			}
		}

		if (pos_x + 1 < 8 && pos_y - 2 >= 0 && this->board[pos_x + 1][pos_y - 2] != 0){

			if (std::abs(this->board[pos_x + 1][pos_y - 2]) / 10 == KNIGHT && signal * this->board[pos_x + 1][pos_y - 2] < 0){

				safe = false;

				if (update){

					std::vector<int> check_piece;
					check_piece.push_back(this->board[pos_x + 1][pos_y - 2]);
					check_piece.push_back(pos_x + 1);
					check_piece.push_back(pos_y - 2);
					this->set_check_piece(check_piece);
				}
				// std::cout << "safe 9: " << safe  << "\n";
			}
		}

		// if (!safe) std::cout << "piece: " << piece  << ", " << pos_x << ", " << pos_y  << "\n";

		return safe;
	}

	bool check_mate(int pos_x, int pos_y, int king){

		bool mate = true;
		int signal = king / std::abs(king);
		std::cout << "check_mate?\n";
		std::cout << "king_on_check_mate " << king << ", " << pos_x << ", " << pos_y << "\n";
		std::cout << "check piece 1: " << this->check_piece[0] << "\n";

		if (this->check_piece[0] != 0){

		// Checks if the king can move


			for (int i = -1; i < 2; i++){

				for (int j = -1; j < 2; j++){

					if (pos_x + i >= 0 && pos_y + j >= 0 && pos_x + i < 8 && pos_y + j < 8){

						if (this->board[pos_x + i][pos_y + j] * signal <= 0 && this->not_check(pos_x + i, pos_y + j, this->board[pos_x + i][pos_y + j], false)){
							std::cout << "nigger\n";
							mate = false;
						}
					}
				}
			}

			std::cout << "mate 1: " << mate << "\n";

		// Checks if the piece doing the check can be blocked (only happens to rooks, bishops or queens)
		// So just gotta check out the vector that has origin in the piece's square and is pointing to the king
		// Then just follow the track and see if any square is in check, this means that is blockable

			std::cout << "check piece 3: " << this->check_piece[0] << "\n";

			int vec_x = pos_x - this->check_piece[1];
			int vec_y = pos_y - this->check_piece[2];

			if (std::abs(this->check_piece[0]) / 10 == ROOK || std::abs(this->check_piece[0]) / 10 == QUEEN || std::abs(this->check_piece[0]) / 10 == BISHOP){

				int aux_x = static_cast<int>(vec_x / std::abs(vec_x));
				int aux_y = static_cast<int>(vec_y / std::abs(vec_y));

				std::cout << "aux " << aux_x << ", " << aux_y << "\n";
				for (int i = 0; i < std::abs(vec_x + vec_y); i++){

					if (!this->not_check(this->check_piece[1] + (i * aux_x), this->check_piece[2] + (i * aux_y), this->board[this->check_piece[1] + (i * aux_x)][this->check_piece[2] + (i * aux_y)], false)){

						mate = false;
					}
				}
			}

			std::cout << "mate 3: " << mate << "\n";
		}

		if (mate){

			std::cout << "check mate\n";
		}
			std::cout << "\n\n\n";

		return mate;
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

	bool legal_move(int prev_x, int prev_y, int new_x, int new_y, int king, int king_pos_x, int king_pos_y){

		bool legal = true;

		if ((prev_x != new_x || prev_y != new_y) && not_check(king_pos_x, king_pos_y, king, false)){

			int prev_piece = this->board[prev_x][prev_y];
			float vector_x = (new_x - prev_x) / sqrt((new_x - prev_x) * (new_x - prev_x) + (new_y - prev_y) * (new_y - prev_y));
			float vector_y = (new_y - prev_y) / sqrt((new_x - prev_x) * (new_x - prev_x) + (new_y - prev_y) * (new_y - prev_y));			

			// std::cout << "vector " << vector_x << ", " << vector_y  << "\n";
			// // std::cout << "dir " << this->dir << "\n";
			// std::cout << "piece " << this->board[prev_x][prev_y]  << "\n";
			// std::cout << "prev_pos " << prev_x << ", " << prev_y  << "\n";
			// std::cout << "new pos " << new_x << ", " << new_y  << "\n";
			// std::cout << "king " << king << "\n";
			// std::cout << "king_pos " << king_pos_x << ", " << king_pos_y  << "\n\n\n";

			switch (std::abs(prev_piece) / 10){

				case ROOK:

				if (vector_x * vector_y != 0.0f){
					
					legal = false;
				}
				else{

					int vec_x = static_cast<int>(vector_x);
					int vec_y = static_cast<int>(vector_y);

					prev_x += vec_x;
					prev_y += vec_y;

					while (std::abs(new_x - prev_x) > 0 || std::abs(new_y - prev_y) > 0){

						if (this->board[prev_x][prev_y] != 0){

							legal = false;
						}

						prev_x += vec_x;
						prev_y += vec_y;
					}
				}

				break;

				case KNIGHT:

				if (!(std::abs(new_x - prev_x) == 2 && std::abs(new_y - prev_y) == 1 || (std::abs(new_x - prev_x) == 1 && std::abs(new_y - prev_y) == 2))){

					legal = false;
				}

				break;

				case BISHOP:

				if (std::abs(vector_x) != std::abs(vector_y)){

					legal = false;
				}
				else{

					int vec_x = static_cast<int>(vector_x / std::abs(vector_x));
					int vec_y = static_cast<int>(vector_y / std::abs(vector_y));

					prev_x += vec_x;
					prev_y += vec_y;

					while (std::abs(new_x - prev_x) > 0 || std::abs(new_y - prev_y) > 0){


						if (this->board[prev_x][prev_y] != 0){

							legal = false;
						}

						prev_x += vec_x;
						prev_y += vec_y;
					}
				}

				break;

				case QUEEN:

				if (std::abs(vector_x) != std::abs(vector_y) && vector_x * vector_y != 0.0f){

					legal = false;
				}
				else{

					int vec_x = static_cast<int>(vector_x / std::abs(vector_x));
					int vec_y = static_cast<int>(vector_y / std::abs(vector_y));

					prev_x += vec_x;
					prev_y += vec_y;

					while (std::abs(new_x - prev_x) > 0 || std::abs(new_y - prev_y) > 0){


						if (this->board[prev_x][prev_y] != 0){

							legal = false;
						}

						prev_x += vec_x;
						prev_y += vec_y;
					}
				}

				break;

				case KING:

				if (std::abs(new_x - prev_x) > 1 || std::abs(new_y - prev_y) > 1){

					legal = false;
				}
				else{

					if (!not_check(new_x, new_y, prev_piece, false)){

						legal = false;
					}
				}

				break;

				case PAWN:

				if (this->board[new_x][new_y] != 0){

					int vec_x = static_cast<int>(vector_x / std::abs(vector_x));
					int vec_y = static_cast<int>(vector_y / std::abs(vector_y));

					if (!(std::abs(new_x - prev_x) * this->dir * vec_x == 1 && std::abs(new_y - prev_y) * this->dir * vec_y == 1 || std::abs(new_x - prev_x) * this->dir * vec_x == 1 && std::abs(new_y - prev_y) * this->dir * vec_y == -1)){
						
						legal = false;
					}
				}
				else{

					if (vector_x * vector_y != 0.0f){ 

						legal = false;
					}
					else{

						if (vector_x * this->dir <= 0){
							
							legal = false;
						}
						else{

							int vec_x = static_cast<int>(vector_x);
							int vec_y = static_cast<int>(vector_y);

							if (std::abs(new_x - prev_x) > 2){

								legal = false;
							}
							else{

								if (std::abs(new_x - prev_x) == 2){

									if (this->board[prev_x + 1 * this->dir][prev_y] != 0){

										legal = false;
									}

									if (this->dir < 0 && prev_x != 6){

										legal = false;
									}

									else if (this->dir > 0 && prev_x != 1){

										legal = false;
									}
								}
							}
						}
					}
				}

				break;
			}
		}

		if (legal){

			int temp = this->board[new_x][new_y];

			this->new_pos(prev_x, prev_y, new_x, new_y);

			// std::cout << "prev pos: " << prev_x << ", " << prev_y << "\n";
			// std::cout << "new pos: " << new_x << ", " << new_y << "\n";
			// std::cout << "king pos: " << king << " " << king_pos_x << ", " << king_pos_y << "\n";
			// this->display_board();

			if (!not_check(king_pos_x, king_pos_y, king, false)){

				legal = false;
			}
			// std::cout << "end board\n";

			this->new_pos(new_x, new_y, prev_x, prev_y);

			this->board[new_x][new_y] = temp;
		}

		return legal;
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
	int player;

	// Helping vars

	bool mouse_held;
	bool holding;
	bool dragging;
	int piece_held;
	sf::Vector2f prev_place;
	int changed;

	// Private methods

	void init_vars(int player){

		this->player = player;
		this->window = nullptr;
		this->changed = 1;
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
		this->window->setFramerateLimit(60);
	}

public:

	// Constructors / Destructors

	Game(int player){

		this->init_vars(player);

		std::vector<int> check_piece;
		check_piece.push_back(0);
		check_piece.push_back(0);
		check_piece.push_back(0);
		this->boards.set_check_piece(check_piece);

		this->boards.set_texture_size(this->texture.getSize(), 6, 2);
		if (this->player == -1){

			this->boards.fill_board("RCBKQBCRPPPPPPPP8888_P_P_P_P_P_P_P_P_R_C_B_K_Q_B_C_R");
			this->boards.set_dir(1);
		}
		else{

			this->boards.fill_board("_R_C_B_Q_K_B_C_R_P_P_P_P_P_P_P_P8888PPPPPPPPRCBQKBCR");
			this->boards.set_dir(-1);
		}
		if (this->player = -1) this->player *= -1;
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

// se calhar pegar na peça que tou a segurar e desenhar depois de todas as outras!!!!!!!!!!!

	void update_board(){

		int king, pos_x, pos_y, king_op, pos_x_op, pos_y_op;

		for (int i = 0; i < 8; i++){

			for (int j = 0; j < 8; j++){

				if (std::abs(this->boards.get_board()[i][j]) / 10 == KING && this->boards.get_board()[i][j] * this->player > 0){

					king = this->boards.get_board()[i][j];
					pos_x = i;
					pos_y = j;
				}

				if (std::abs(this->boards.get_board()[i][j]) / 10 == KING && this->boards.get_board()[i][j] * this->player < 0){

					king_op = this->boards.get_board()[i][j];
					pos_x_op = i;
					pos_y_op = j;
				}
			}
		}

		if (this->changed){

			this->changed = 0;
			std::cout << "player " << this->player << "\n";
			std::cout << "dir " << this->boards.get_dir() << "\n";
			std::cout << "king: " << king << ", " << pos_x << ", " << pos_y << "\n";
			std::cout << "king_op: " << king_op << ", " << pos_x_op << ", " << pos_y_op << "\n\n\n";
		}

		if (this->boards.not_check(pos_x, pos_y, king, true) || !this->boards.check_mate(pos_x, pos_y, king)){

			if (this->mouse_pos_view.x <= this->window->getSize().x && this->mouse_pos_view.y <= this->window->getSize().y && this->mouse_pos_view.x >= 0 && this->mouse_pos_view.y >= 0){

				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){

					if (!this->holding){

						int board_pos_x;
						int board_pos_y;

						for (std::vector<sf::RectangleShape> vec : this->boards.get_board_image()){

							for (sf::RectangleShape element : vec){

								if (element.getGlobalBounds().contains(this->mouse_pos_view)){

									board_pos_x = static_cast<int> (element.getPosition().y * this->boards.get_square_size() / 800);
									board_pos_y = static_cast<int> (element.getPosition().x * this->boards.get_square_size() / 800);
								}
							}
						}

						for (std::pair<int, Piece> element : this->boards.get_pieces().get_pieces()){

							if (this->boards.get_board()[board_pos_x][board_pos_y] * this->player > 0 && element.second.get_piece().getGlobalBounds().contains(this->mouse_pos_view)){

								this->prev_place = element.second.get_piece().getPosition();
								this->piece_held = element.first;
								this->holding = true;
							}
						}
					}
					else{

						this->boards.set_pieces_pos(this->piece_held, this->mouse_pos_view.x - (this->boards.get_pieces().get_texture_size().x / 6), this->mouse_pos_view.y - (this->boards.get_pieces().get_texture_size().y) / 5);
					}
				}

				else if(sf::Event::MouseButtonReleased && this->event.mouseButton.button == sf::Mouse::Left){
		// std::cout << "king: "  << king << ", " << pos_x << ", " << pos_y << "\n";
		// std::cout << "king_op: "  << king_op << ", " << pos_x_op << ", " << pos_y_op << "\n";

					if (this->holding){

						for (std::vector<sf::RectangleShape> vec : this->boards.get_board_image()){

							for (sf::RectangleShape element : vec){

								if (element.getGlobalBounds().contains(this->mouse_pos_view)){

									int prev_x = static_cast<int> (this->prev_place.y * this->boards.get_square_size() / 800);
									int prev_y = static_cast<int> (this->prev_place.x * this->boards.get_square_size() / 800);
									int new_x = static_cast<int> (element.getPosition().y * this->boards.get_square_size() / 800);
									int new_y = static_cast<int> (element.getPosition().x * this->boards.get_square_size() / 800);

									if (this->boards.get_board()[new_x][new_y] * this->boards.get_board()[prev_x][prev_y] <= 0 && this->boards.legal_move(prev_x, prev_y, new_x, new_y, king_op, pos_x_op, pos_y_op)){

										this->boards.set_pieces_pos(this->piece_held, element.getPosition().x, element.getPosition().y);

										this->boards.new_pos(prev_x, prev_y, new_x, new_y);

										this->boards.display_board();

										if (prev_x != new_x || prev_y != new_y){

											this->player *= -1;
											this->changed = 1;
											this->boards.set_dir(this->boards.get_dir() * (-1));
										}
									}
									else{

										this->boards.set_pieces_pos(this->piece_held, this->prev_place.x, this->prev_place.y);

									}
								}
							}
						}

						this->holding = false;
					}
				}
			}
		}
		else{

			std::cout << "End game!\n";
		}
	}
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

		sf::Sprite is_it;

		for (int i = 0; i < 8; i++){

			for (int j = 0; j < 8; j++){

				sf::Sprite sprite;
				sprite = this->boards.get_pieces().get_pieces().find(this->boards.get_board()[i][j])->second.get_piece();
				sprite.setTexture(this->texture);

				if (this->boards.get_pieces().get_pieces().find(this->boards.get_board()[i][j])->first == this->piece_held){

					is_it = sprite;
				}

				target.draw(sprite);
			}
		}

		target.draw(is_it);
	}

	void update(){

		this->poll_events();

		this->update_mouse_pos();

		this->update_board();
	}

	void render(){

		this->window->clear(sf::Color(0,0,0,255));

		this->render_board(*this->window);

		this->window->display();
	}
};