#include "pieces.cpp"

#define EMPTY 0
#define KING 1
#define QUEEN 2
#define BISHOP 3
#define KNIGHT 4
#define ROOK 5
#define PAWN 6

// Board class

class BoardNM{

private:

	std::vector<std::vector<int>> board;
	Pieces pieces;
	sf::Vector3i moving_piece;

public:

	BoardNM(){

		std::vector<std::vector<int>> board;
		this->board = board;
		Pieces pieces;
		this->pieces = pieces;
		this->moving_piece.x = -1;
		this->moving_piece.y = -1;
		this->moving_piece.z = 0;
	}

	BoardNM(std::vector<std::vector<int>> board, Pieces pieces, sf::Vector3i moving_piece){

		this->board = board;
		this->pieces = pieces;
		this->moving_piece = moving_piece;
	}

	void set_board(std::vector<std::vector<int>> board){

		this->board = board;
	}

	void set_pieces(Pieces pieces){

		this->pieces = pieces;
	}

	void set_moving_piece(sf::Vector3i pos){

		this->moving_piece = pos;
	}

	void set_texture_size(sf::Vector2u texture_size){

		this->pieces.set_texture_size(texture_size);
	}

	std::vector<std::vector<int>> get_board(){

		std::vector<std::vector<int>> board = this->board;
		return board;
	}

	Pieces get_pieces(){

		Pieces pieces = this->pieces;
		return pieces;
	}

	sf::Vector3i get_moving_piece(){

		sf::Vector3i p = this->moving_piece;
		return p;
	}

	std::map<int, sf::Sprite> get_pieces_map(){

		return this->pieces.get_pieces();
	}

	void set_piece_number(int num, int i, int j){

		this->board[i][j] = num;
	}

	int get_piece_number(int i, int j){

		int number = this->board[i][j];
		return number;
	}

	int countDigit(long long n){

		int count = 0;

		while (n != 0){

			n = n / 10;
			count++;
		}

		return count;
	}

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

	void load_pieces(int squares_number, float resolution){

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
					sprite.setScale(sf::Vector2f((resolution / squares_number) / this->pieces.get_texture_size().x, (resolution / squares_number) / this->pieces.get_texture_size().y));

					sprite.setPosition(j * (resolution / squares_number), i * (resolution / squares_number));
					
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
					this->pieces.insert_elem(this->board[i][j], sprite);
				}
			}
		}
	}

	sf::Vector2i get_piece_index(sf::Vector2f mouse_coords, float resolution, int squares_number){

		sf::Vector2i b_pos(-1, -1);

		if (mouse_coords.x >= 0.0f && mouse_coords.x <= resolution && mouse_coords.y >= 0.0f && mouse_coords.y <= resolution){
			
			b_pos.x = static_cast<int>(mouse_coords.y / (resolution / squares_number));

			b_pos.y = static_cast<int>(mouse_coords.x / (resolution / squares_number));

			// std::cout << "square: " << b_pos.x << ", " << b_pos.y << "\n";
		}

		return b_pos;
	}

	void move_piece(float resolution, int squares_number, int num, int prev_x, int prev_y, int new_x, int new_y){

		// int res = this->board[new_x][new_y];
		std::cout << "prev: " << prev_x << ", " << prev_y << " new: " << new_x << ", " << new_y << "\n";

		if (prev_x != new_x || prev_y != new_y){

			this->board[new_x][new_y] = num;
			this->board[prev_x][prev_y] = 0;

			int x = (resolution / squares_number) * new_y;
			int y = (resolution / squares_number) * new_x;

			this->pieces.set_piece_pos(num, x, y);

			// if (res != 0){

			// 	this->pieces.delete_piece(res);
			// }
		}
	}

	int piece_side(int i, int j){

		if(this->board[i][j]) return this->board[i][j] / std::abs(this->board[i][j]);
	}
};
