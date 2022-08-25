#include "pieces.cpp"
#include "boardSQ.cpp"
#include <string.h>
#include <map>

#define EMPTY 0
#define KING 1
#define QUEEN 2
#define BISHOP 3
#define KNIGHT 4
#define ROOK 5
#define PAWN 6

class Saves{

public:

	std::vector<std::vector<int>> board;
	int dir;
	int turn;
	sf::Vector3i en_passant_piece;
	sf::Vector3i K_R_moved;
};

// Board class

class BoardNM{

private:

	std::vector<std::vector<int>> board;
	int dir;
	int turn;
	Pieces pieces;
	sf::Vector3i moving_piece;
	std::stack<Saves> stack;

	// Castling and en passant

	sf::Vector3i en_passant_piece;
	bool castles;
	std::map<int, int> K_R_moved;

public:

	BoardNM(){

		std::vector<std::vector<int>> board;
		this->board = board;
		Pieces pieces;
		this->pieces = pieces;
		this->moving_piece = sf::Vector3i(-1, -1, 0);
		this->dir = 0;
		this->turn = 1;
		this->en_passant_piece = sf::Vector3i(-1, -1, -1);
		// this->K_R_moved = std::map<int, int>;
		this->castles = false;
	}

	BoardNM(std::vector<std::vector<int>> board, Pieces pieces, sf::Vector3i moving_piece, int dir, int turn){

		this->board = board;
		this->pieces = pieces;
		this->moving_piece = moving_piece;
		this->dir = dir;
		this->turn = turn;
		this->en_passant_piece = sf::Vector3i(-1, -1, -1);
		// this->K_R_moved = std::map<int, int>;
		this->castles = false;
	}

	void set_board(std::vector<std::vector<int>> board){

		this->board = board;
	}

	void set_dir(int dir){

		this->dir = dir;
	}

	void set_turn(int turn){

		this->turn = turn;
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

	void set_stack(std::stack<Saves> stack){

		this->stack = stack;
	}

	std::vector<std::vector<int>> get_board(){

		std::vector<std::vector<int>> board = this->board;
		return board;
	}

	Pieces get_pieces(){

		Pieces pieces = this->pieces;
		return pieces;
	}

	std::stack<Saves> get_stack(){

		std::stack<Saves> stack = this->stack;
		return stack;
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

	int get_dir(){

		int dir = this->dir;
		return dir;
	}

	int get_turn(){

		int turn = this->turn;
		return turn;
	}

	int get_piece_number(int i, int j){

		int number = this->board[i][j];
		return number;
	}

	sf::Vector2i get_piece_pos(int piece){

		for (int i = 0; i < 8; i++){

			for (int j = 0; j < 8; j++){

				std::cout << ">>>>>>>>>>>>>>>>>>>>>>> " << this->board[i][j] << "==" << piece << "\n";
				if (this->board[i][j] == piece){


					return sf::Vector2i(i, j);
				}
			}
		}

		return sf::Vector2i(-1, -1);
	}

	int get_piece_number(int i, int j, std::vector<std::vector<int>> board){

		int number = board[i][j];
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

	std::vector<std::vector<int>> get_board_from_string(std::string input){

		// "RCBQKBCRPPPPPPPP8888_P_P_P_P_P_P_P_P_R_C_B_K_Q_B_C_R"
		// "_R_C_B_Q_K_B1_R_P_P_P_P1_P_P_P4_P36C14_C34P3PPPP1PPPRCBQKB1R"

		std::vector<std::vector<int>> board;
		int row = 0;
		int col = 0;
		std::vector<int> aux;
		int is_black = 1;
		int pawn = 1;
		int bishop = 1;
		int rook = 1;
		int knight = 1;
		int king = 1;
		int queen = 1;

		for (int i = 0; i < input.length(); i++){

			if (!std::isdigit(static_cast<unsigned char>(input[i]))){

				if (input[i] == '_'){

					is_black = -1;
					i++;
				}

				switch (input[i]){

					case 'R':
					aux.push_back((500 + rook) * is_black);
					this->K_R_moved.insert(std::pair<int, int>((500 + rook++) * is_black, 0));
					break;

					case 'C':
					aux.push_back((400 + knight++) * is_black);
					break;

					case 'B':
					aux.push_back((300 + bishop++) * is_black);
					break;

					case 'Q':
					aux.push_back((200 + queen++) * is_black);
					break;

					case 'K':
					aux.push_back((100 + king) * is_black);
					this->K_R_moved.insert(std::pair<int, int>((100 + king++) * is_black, 0));
					break;

					case 'P':
					aux.push_back((600 + pawn++) * is_black);
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

				board.push_back(aux);
				aux.clear();
				col = 0;
				row++;
			}
		}

		return board;
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
		int king = 1;
		int queen = 1;

		for (int i = 0; i < input.length(); i++){

			if (!std::isdigit(static_cast<unsigned char>(input[i]))){

				if (input[i] == '_'){

					is_black = -1;
					i++;
				}

				switch (input[i]){

					case 'R':
					aux.push_back((500 + rook) * is_black);
					this->K_R_moved.insert(std::pair<int, int>((500 + rook++) * is_black, 0));
					break;

					case 'C':
					aux.push_back((400 + knight++) * is_black);
					break;

					case 'B':
					aux.push_back((300 + bishop++) * is_black);
					break;

					case 'Q':
					aux.push_back((200 + queen++) * is_black);
					break;

					case 'K':
					aux.push_back((100 + king) * is_black);
					this->K_R_moved.insert(std::pair<int, int>((100 + king++) * is_black, 0));
					break;

					case 'P':
					aux.push_back((600 + pawn++) * is_black);
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

	std::string get_board_state(std::vector<std::vector<int>> curr_board){

		std::string result;

		for (int i = 0; i < 8; i++){

			for (int j = 0; j < 8;){

				if (curr_board[i][j] == EMPTY){

					int aux = 0;

					while (j < 8 && curr_board[i][j] == EMPTY){

						aux++;
						j++;
					}

					std::string num = std::to_string(aux);

					result.append(num);
				}
				else{

					//_R_C_B_Q_K_B_C_R_P_P_P_P_P_P_P_P8888PPPPPPPPRCBQKBCR

					switch (curr_board[i][j] / 100){

						case -1 * ROOK:

						result.append("_R");
						break;

						case ROOK:
						
						result.append("R");
						break;

						case -1 * KNIGHT:

						result.append("_C");
						break;

						case KNIGHT:
						
						result.append("C");
						break;

						case -1 * BISHOP:

						result.append("_B");
						break;

						case BISHOP:
						
						result.append("B");
						break;

						case -1 * QUEEN:

						result.append("_Q");
						break;

						case QUEEN:
						
						result.append("Q");
						break;

						case -1 * KING:

						result.append("_K");
						break;

						case KING:
						
						result.append("K");
						break;

						case -1 * PAWN:

						result.append("_P");
						break;

						case PAWN:
						
						result.append("P");
						break;
					}

					j++;
				}
			}
		}

		// std::cout << result;

		return result;
	}

	void save_board_state(){

		std::stack<Saves> stack = this->get_stack();

		// Create and open a text file
		std::ofstream Boards("saves.txt");

		// Boards << this->get_board_state(this->get_board()) << ";" << this->get_turn() << ";" << this->get_dir() << "\n";

		while (!stack.empty()){

			Saves aux = stack.top();

			stack.pop();

			// Write to the file
			Boards << this->get_board_state(aux.board) << ";" << aux.turn << ";" << aux.dir << ";" << aux.en_passant_piece.x << ";" << aux.en_passant_piece.y << ";" << aux.en_passant_piece.z << "\n";
		}

		// Close the file
		Boards.close();
	}

	std::stack<Saves> invert_stack(std::stack<Saves> stack){

		std::stack<Saves> s = stack;
		std::stack<Saves> aux;

		while (!s.empty()){

			Saves temp = s.top();
			s.pop();

			aux.push(temp);
		}

		return aux;
	}

	void print_stack(std::stack<Saves> stack){

		std::stack<Saves> aux = stack;

		while (!aux.empty()){

			Saves temp = aux.top();
			aux.pop();
			std::cout << "board: " << this->get_board_state(temp.board) << "|||| turn: " << temp.turn << "|||| dir: " << temp.dir << "|||| en passant: " << temp.en_passant_piece.x << ", " << temp.en_passant_piece.y << ", " << temp.en_passant_piece.z << "\n";
		}
	}

	void load_from_saves(){

		std::fstream Myfile("saves.txt");

		if (Myfile.is_open()){

			std::stack<Saves> aux_stack;
			std::string line;

			while(getline(Myfile, line)){

				std::cout << line << "\n";

				char* ptr = strtok(const_cast<char*>(line.c_str()), ";");

				Saves aux;
				const char *s = ptr;
				std::string str(s);
				aux.board = this->get_board_from_string(s);
				ptr = strtok(NULL, ";");
				aux.turn = std::stoi(ptr);
				ptr = strtok(NULL, ";");
				aux.dir = std::stoi(ptr);
				ptr = strtok(NULL, ";");
				aux.en_passant_piece.x = std::stoi(ptr);
				ptr = strtok(NULL, ";");
				aux.en_passant_piece.y = std::stoi(ptr);
				ptr = strtok(NULL, ";");
				aux.en_passant_piece.z = std::stoi(ptr);
				aux_stack.push(aux);
			}

			Myfile.close();
			this->set_stack(this->invert_stack(aux_stack));
			Saves recent = this->stack.top();
			this->set_board(recent.board);
			this->turn = recent.turn;
			this->dir = recent.dir;
			this->en_passant_piece = recent.en_passant_piece;
		}
		else std::cout << "Unable to open file"; 
	}

	void update_state(){

		std::vector<std::vector<int>> aux = this->board;
		Saves saves;
		saves.board = aux;
		saves.turn = this->turn;
		saves.dir = this->dir;
		saves.en_passant_piece = this->en_passant_piece;
		this->stack.push(saves);
		std::cout << "update_state--------------------------------------------------\n";
	}

	void undo_play(BoardSQ &board, float resolution, int squares_number){

		if (this->stack.size() > 1){

			this->stack.pop();

			Saves prev_save = this->stack.top();

			this->set_board(prev_save.board);
			this->set_turn(prev_save.turn);
			this->set_dir(prev_save.dir);
			this->en_passant_piece = prev_save.en_passant_piece;
			board.clean(squares_number, resolution, sf::Color::White, sf::Color(150, 150, 150, 255));

			std::cout << "undo ---------------------------------------------------------\n";
		}
	}

	// void print_special_pieces(){

	// 	for (int i = 0; i < 2; i++){

	// 		for (int j = 0; j < 8; j++){

	// 			std::cout << " || " << this->pawns[i][j];
	// 		}

	// 		std::cout << "\n";
	// 	}
	// }

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

	void display_board(std::vector<std::vector<int>> board){

		for (int i = 0; i < 8; i++){

			for (int j = 0; j < 8; j++){

				int var = countDigit(board[i][j]);

				if (board[i][j] > 0){

					var--;
				}

				while(3 - var > 0){

					std::cout << " ";
					var++;
				}

				std::cout << board[i][j];
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

					switch (std::abs(this->board[i][j]) / 100) {

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
					std::map<int, sf::Sprite>::iterator piece = this->pieces.get_pieces().find(this->board[i][j]);

					if (piece != this->pieces.get_pieces().end()){

						this->pieces.delete_piece(this->board[i][j]);
					}

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

	int piece_side(int i, int j){

		if(this->board[i][j]) return this->board[i][j] / std::abs(this->board[i][j]);
		else return 0;
	}

	int piece_side(int i, int j, std::vector<std::vector<int>> board){

		if(board[i][j]) return board[i][j] / std::abs(board[i][j]);
		else return 0;
	}

	sf::Vector2i check_knight(sf::Vector2i pos, int piece_side, std::vector<std::vector<int>> temp_board){

		// up and left

		int i = pos.x - 1;
		int j = pos.y + 2;

		if (i >= 0 && j < 8 && std::abs(temp_board[i][j] / 100) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// up and right

		i = pos.x + 1;
		j = pos.y + 2;

		if (i < 8 && j < 8 && std::abs(temp_board[i][j] / 100) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// down right

		i = pos.x + 2;
		j = pos.y + 1;

		if (i < 8 && j < 8 && std::abs(temp_board[i][j] / 100) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// down left

		i = pos.x + 2;
		j = pos.y - 1;

		if (i < 8 && j >= 0 && std::abs(temp_board[i][j] / 100) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// down left

		i = pos.x + 1;
		j = pos.y - 2;

		if (i < 8 && j >= 0 && std::abs(temp_board[i][j] / 100) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// down left

		i = pos.x - 1;
		j = pos.y - 2;

		if (i >= 0 && j >= 0 && std::abs(temp_board[i][j] / 100) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// down left

		i = pos.x - 2;
		j = pos.y - 1;

		if (i >= 0 && j >= 0 && std::abs(temp_board[i][j] / 100) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// down left

		i = pos.x - 2;
		j = pos.y + 1;

		if (i >= 0 && j < 8 && std::abs(temp_board[i][j] / 100) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);


		return sf::Vector2i(-1, -1);
	}

	sf::Vector2i check_bishop(sf::Vector2i pos, int piece_side, std::vector<std::vector<int>> temp_board){

		// up and left

		int i = pos.x - 1;
		int j = pos.y - 1;

		while (i >= 0 && j >= 0 && temp_board[i][j] == 0){i--; j--;}

		if (i >= 0 && j >= 0 && (std::abs(temp_board[i][j] / 100) == BISHOP || std::abs(temp_board[i][j] / 100) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		// up and right

		i = pos.x - 1;
		j = pos.y + 1;

		while (i >= 0 && j < 8 && temp_board[i][j] == 0){i--; j++;}

		if (i >= 0  && j < 8 && (std::abs(temp_board[i][j] / 100) == BISHOP || std::abs(temp_board[i][j] / 100) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		// down right

		i = pos.x + 1;
		j = pos.y + 1;

		while (i < 8 && j < 8 && temp_board[i][j] == 0){i++; j++;}

		if (i < 8 && j < 8 && (std::abs(temp_board[i][j] / 100) == BISHOP || std::abs(temp_board[i][j] / 100) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		// down left

		i = pos.x + 1;
		j = pos.y - 1;

		while (i < 8 && j >= 0 && temp_board[i][j] == 0){i++; j--;}

		if (i < 8 && j >= 0 && (std::abs(temp_board[i][j] / 100) == BISHOP || std::abs(temp_board[i][j] / 100) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		return sf::Vector2i(-1, -1);
	}

	sf::Vector2i check_king(sf::Vector2i pos, int piece_side, std::vector<std::vector<int>> temp_board){

		// up

		if (pos.x - 1 >= 0 && std::abs(temp_board[pos.x - 1][pos.y] / 100) == KING && this->piece_side(pos.x - 1, pos.y) != piece_side) return sf::Vector2i(pos.x - 1, pos.y);

		// down

		if (pos.x + 1 < 8 && std::abs(temp_board[pos.x + 1][pos.y] / 100) == KING && this->piece_side(pos.x + 1, pos.y) != piece_side) return sf::Vector2i(pos.x + 1, pos.y);

		// left

		if (pos.y - 1 >= 0 && std::abs(temp_board[pos.x][pos.y - 1] / 100) == KING && this->piece_side(pos.x, pos.y - 1) != piece_side) return sf::Vector2i(pos.x, pos.y - 1);

		// right

		if (pos.y + 1 < 8 && std::abs(temp_board[pos.x][pos.y + 1] / 100) == KING && this->piece_side(pos.x, pos.y + 1) != piece_side) return sf::Vector2i(pos.x, pos.y + 1);

		// up and left

		if (pos.x - 1 >= 0 && pos.y - 1 >= 0 && std::abs(temp_board[pos.x - 1][pos.y - 1] / 100) == KING && this->piece_side(pos.x - 1, pos.y - 1) != piece_side) return sf::Vector2i(pos.x - 1, pos.y - 1);

		// up and right

		if (pos.x - 1 >= 0 && pos.y + 1 < 8 && std::abs(temp_board[pos.x - 1][pos.y + 1] / 100) == KING && this->piece_side(pos.x - 1, pos.y + 1) != piece_side) return sf::Vector2i(pos.x - 1, pos.y + 1);

		// down right

		if (pos.x + 1 < 8 && pos.y + 1 < 8 && std::abs(temp_board[pos.x + 1][pos.y + 1] / 100) == KING && this->piece_side(pos.x + 1, pos.y + 1) != piece_side) return sf::Vector2i(pos.x + 1, pos.y + 1);

		// down left

		if (pos.x + 1 < 8 && pos.y - 1 >= 0 && std::abs(temp_board[pos.x + 1][pos.y - 1] / 100) == KING && this->piece_side(pos.x +1, pos.y - 1) != piece_side) return sf::Vector2i(pos.x +1, pos.y - 1);

		return sf::Vector2i(-1, -1);
	}

	// returns position of the other player's piece if there is one either on the same line or column of the current player's piece, if it's clear returns (-1, -1)

	sf::Vector2i check_rook(sf::Vector2i pos, int piece_side, std::vector<std::vector<int>> temp_board){

		// up

		int i, j;

		j = pos.y;

		for (i = pos.x - 1; i >= 0 && temp_board[i][j] == 0; i--);

			if (i >= 0 && (std::abs(temp_board[i][j] / 100) == ROOK || std::abs(temp_board[i][j] / 100) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		// down

		for (i = pos.x + 1; i < 8 && temp_board[i][j] == 0; i++);

			if (i < 8 && (std::abs(temp_board[i][j] / 100) == ROOK || std::abs(temp_board[i][j] / 100) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		// left

		i = pos.x;

		for (j = pos.y - 1; j >= 0 && temp_board[i][j] == 0; j--);

			if (j >= 0 && (std::abs(temp_board[i][j] / 100) == ROOK || std::abs(temp_board[i][j] / 100) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		// right

		for (j = pos.y + 1; j < 8 && temp_board[i][j] == 0; j++);

			if (j < 8 && (std::abs(temp_board[i][j] / 100) == ROOK || std::abs(temp_board[i][j] / 100) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		return sf::Vector2i(-1, -1);
	}

	sf::Vector2i check_pawn(sf::Vector2i pos, int piece_side, std::vector<std::vector<int>> temp_board){

		// left square

		int i = pos.x + this->dir;
		int j = pos.y - 1;

		if (i >= 0 && i < 8 && j >= 0 && std::abs(temp_board[i][j] / 100) == PAWN && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// right square

		i = pos.x + this->dir;
		j = pos.y + 1;

		if (i >= 0 && i < 8 && j < 8 && std::abs(temp_board[i][j] / 100) == PAWN && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		return sf::Vector2i(-1, -1);
	}

	sf::Vector2i get_vector_dir(sf::Vector2i prevp, sf::Vector2i newp){

		sf::Vector2i res = sf::Vector2i(newp.x - prevp.x, newp.y - prevp.y);

		if(res.x != 0){

			res.x = res.x/std::abs(res.x);
		}

		if(res.y != 0){

			res.y = res.y/std::abs(res.y);
		}

		return res;
	}

	bool legal_pawn(sf::Vector2i prev_pos, sf::Vector2i new_pos){

		sf::Vector2i dir_vetor = sf::Vector2i(new_pos.x - prev_pos.x, new_pos.y - prev_pos.y);

		if (dir_vetor.y == 0){

			if (dir_vetor.x == this->dir){

				if (this->board[new_pos.x][new_pos.y] == EMPTY){

					return true;
				}
			}

			if (dir_vetor.x == this->dir * 2){

				if (this->board[prev_pos.x + this->dir][prev_pos.y] == EMPTY && this->board[new_pos.x][new_pos.y] == EMPTY){

					if ((this->dir == -1 && prev_pos.x == 6) || (this->dir == 1 && prev_pos.x == 1)){

						this->en_passant_piece = sf::Vector3i(0, new_pos.x, new_pos.y);

						return true;
					}
				}
			}
		}
		else if (dir_vetor.y == -1 || dir_vetor.y == 1){

			if (dir_vetor.x == this->dir){


				if (this->board[new_pos.x][new_pos.y] != EMPTY && this->piece_side(prev_pos.x, prev_pos.y) != this->piece_side(new_pos.x, new_pos.y)){

					return true;
				}
				else if (this->board[new_pos.x - this->dir][new_pos.y] != PAWN && this->piece_side(prev_pos.x, prev_pos.y) != this->piece_side(new_pos.x - this->dir, new_pos.y) && sf::Vector2i(this->en_passant_piece.y, this->en_passant_piece.z) == sf::Vector2i(new_pos.x - this->dir, new_pos.y)){

					this->en_passant_piece.x = 1;

					return true;
				}
			}
		}

		return false;
	}

	bool legal_rook(sf::Vector2i prev_pos, sf::Vector2i new_pos){

		sf::Vector2i dir_vetor = this->get_vector_dir(prev_pos, new_pos);
		sf::Vector2i curr_poss = prev_pos;

		if (dir_vetor.x == 0 || dir_vetor.y == 0){

			std::cout << curr_poss.x << ", " << curr_poss.y << "\n";
			curr_poss.x += dir_vetor.x;
			curr_poss.y += dir_vetor.y;

			for (int i = 0; curr_poss != new_pos; i++){

				// std::cout << curr_poss.x << ", " << curr_poss.y << "\n";

				if (this->board[curr_poss.x][curr_poss.y] != EMPTY){

					return false;
				}

				curr_poss.x += dir_vetor.x;
				curr_poss.y += dir_vetor.y;
			}

			return true;
		}

		return false;
	}

	bool legal_bishop(sf::Vector2i prev_pos, sf::Vector2i new_pos){

		sf::Vector2i dir_vetor = this->get_vector_dir(prev_pos, new_pos);
		sf::Vector2i res = sf::Vector2i(new_pos.x - prev_pos.x, new_pos.y - prev_pos.y);
		sf::Vector2i curr_poss = prev_pos;

		if (std::abs(res.x) == std::abs(res.y)){

			// std::cout << curr_poss.x << ", " << curr_poss.y << "\n";

			curr_poss.x += dir_vetor.x;
			curr_poss.y += dir_vetor.y;

			for (int i = 0; curr_poss != new_pos; i++){

				// std::cout << curr_poss.x << ", " << curr_poss.y << "\n";

				if (this->board[curr_poss.x][curr_poss.y] != EMPTY){

					return false;
				}

				curr_poss.x += dir_vetor.x;
				curr_poss.y += dir_vetor.y;
			}

			return true;
		}

		return false;
	}

	bool legal_knight(sf::Vector2i prev_pos, sf::Vector2i new_pos){

		if(prev_pos.x - 2 == new_pos.x && prev_pos.y - 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

			return true;
		}

		if(prev_pos.x - 1 == new_pos.x && prev_pos.y - 2 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

			return true;
		}

		if(prev_pos.x - 2 == new_pos.x && prev_pos.y + 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

			return true;
		}

		if(prev_pos.x - 1 == new_pos.x && prev_pos.y + 2 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

			return true;
		}

		if(prev_pos.x + 1 == new_pos.x && prev_pos.y - 2 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

			return true;
		}

		if(prev_pos.x + 2 == new_pos.x && prev_pos.y - 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

			return true;
		}

		if(prev_pos.x + 1 == new_pos.x && prev_pos.y + 2== new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

			return true;
		}

		if(prev_pos.x + 2 == new_pos.x && prev_pos.y + 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

			return true;
		}

		return false;
	}

	bool legal_queen(sf::Vector2i prev_pos, sf::Vector2i new_pos){

		return legal_rook(prev_pos, new_pos) || legal_bishop(prev_pos, new_pos);
	}

	bool legal_king(sf::Vector2i prev_pos, sf::Vector2i new_pos){

		// std::cout << new_pos.x << ", " << new_pos.y << ": "  << this->check(new_pos) << "\n";
		if (this->check(prev_pos, new_pos, this->piece_side(prev_pos.x, prev_pos.y)) == sf::Vector2i(-1, -1)){

			if (prev_pos.x - 1 == new_pos.x && prev_pos.y - 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if (prev_pos.x - 1 == new_pos.x && prev_pos.y == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if (prev_pos.x - 1 == new_pos.x && prev_pos.y + 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if(prev_pos.x == new_pos.x && prev_pos.y - 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if (prev_pos.x == new_pos.x && prev_pos.y + 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if (prev_pos.x + 1 == new_pos.x && prev_pos.y - 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if (prev_pos.x + 1 == new_pos.x && prev_pos.y == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if (prev_pos.x + 1 == new_pos.x && prev_pos.y + 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if (this->legal_castling(new_pos)){

				return true;
			}
		}

		return false;
	}

	bool castling(sf::Vector2i curr_king_pos, sf::Vector2i curr_rook, int L_R){

    	// Your king and rook have not moved!
		// 2x - 1 = y
		// x = (y + 1) / 2

		if (this->K_R_moved[this->board[curr_king_pos.x][curr_king_pos.y]] == 1 || this->K_R_moved[this->board[curr_rook.x][curr_rook.y]] == 1){

			return false;
		}

		std::cout << "Your king and rook have not moved!\n";

		// Your king is NOT in check! (this was already checked when this function is called)

		// if (this->check(sf::Vector2i(-1, -1), sf::Vector2i(curr_king_pos.x, curr_king_pos.y), this->piece_side(curr_king_pos.x, curr_king_pos.y)) != sf::Vector2i(-1, -1)){

		// 	return false;
		// }

		// No pieces between the king and rook!

		sf::Vector2i dir_vetor = this->get_vector_dir(curr_king_pos, curr_rook);

		for (int i = dir_vetor.y; sf::Vector2i(curr_king_pos.x, curr_king_pos.y + i) != curr_rook; i += dir_vetor.y){

			if(this->board[curr_king_pos.x][curr_king_pos.y + i] != EMPTY){

				return false;
			}
		}

		std::cout << "No pieces between the king and rook!\n";
		// Your king does not pass through check!

		for (int i = dir_vetor.y; std::abs(i) < 3; i += dir_vetor.y){

			if (this->check(sf::Vector2i(-1, -1), sf::Vector2i(curr_king_pos.x, curr_king_pos.y + i), this->piece_side(curr_king_pos.x, curr_king_pos.y)) != sf::Vector2i(-1, -1)){

				return false;
			}
		}
		std::cout << "Your king does not pass through check!\n";

		this->castles = true;

		return true;
	}

	bool legal_castling(sf::Vector2i new_pos){

		sf::Vector2i curr_king_pos = this->get_curr_king();

		if (new_pos == sf::Vector2i(curr_king_pos.x, curr_king_pos.y - 2) && std::abs(this->board[curr_king_pos.x][0]) / 100 == ROOK){

			return this->castling(curr_king_pos, sf::Vector2i(curr_king_pos.x, 0), 1);
		}
		else if (new_pos == sf::Vector2i(curr_king_pos.x, curr_king_pos.y + 2) && std::abs(this->board[curr_king_pos.x][7]) / 100 == ROOK){

			return this->castling(curr_king_pos, sf::Vector2i(curr_king_pos.x, 7), 2);
		}

		return false;
	}

	bool legal_move(sf::Vector2i prev_pos, sf::Vector2i new_pos){

		switch(std::abs(this->board[prev_pos.x][prev_pos.y]) / 100){

			case ROOK:
			return legal_rook(prev_pos, new_pos);
			break;

			case BISHOP:
			return legal_bishop(prev_pos, new_pos);
			break;

			case QUEEN:
			return legal_queen(prev_pos, new_pos);
			break;

			case KING:
			return legal_king(prev_pos, new_pos);
			break;

			case KNIGHT:
			return legal_knight(prev_pos, new_pos);
			break;

			case PAWN:
			return legal_pawn(prev_pos, new_pos);
			break;
		}

		return true;
	}

	sf::Vector2i check(sf::Vector2i prev_pos, sf::Vector2i new_pos, int piece_side){

		std::vector<std::vector<int>> temp_board = this->get_board();

		// std::cout << "deu asneira aqui? " << (prev_pos != sf::Vector2i(-1, -1)) << "\n";
		if (prev_pos != sf::Vector2i(-1, -1)){

			temp_board[new_pos.x][new_pos.y] = temp_board[prev_pos.x][prev_pos.y];
			temp_board[prev_pos.x][prev_pos.y] = 0;
		}

		// std::cout << "temp board ->>>>>>>>>>>>> \n";
		// this->display_board(temp_board);

		if(this->check_pawn(new_pos, piece_side, temp_board) != sf::Vector2i(-1, -1)){

			std::cout << "pawn check " <<  this->check_pawn(new_pos, piece_side, temp_board).x << ", " << this->check_pawn(new_pos, piece_side, temp_board).y << "\n";
			return this->check_pawn(new_pos, piece_side, temp_board);
		}


		if(this->check_knight(new_pos, piece_side, temp_board) != sf::Vector2i(-1, -1)){

			std::cout << "knight check " <<  this->check_knight(new_pos, piece_side, temp_board).x << ", " << this->check_knight(new_pos, piece_side, temp_board).y << "\n";
			return this->check_knight(new_pos, piece_side, temp_board);
		}

		if(this->check_bishop(new_pos, piece_side, temp_board) != sf::Vector2i(-1, -1)){

			std::cout << "bishop check " <<  this->check_bishop(new_pos, piece_side, temp_board).x << ", " << this->check_bishop(new_pos, piece_side, temp_board).y << "\n";
			return this->check_bishop(new_pos, piece_side, temp_board);
		}

		if(this->check_rook(new_pos, piece_side, temp_board) != sf::Vector2i(-1, -1)){

			std::cout << "rook check " <<  this->check_rook(new_pos, piece_side, temp_board).x << ", " << this->check_rook(new_pos, piece_side, temp_board).y << "\n";
			return this->check_rook(new_pos, piece_side, temp_board);
		}

		if(this->check_king(new_pos, piece_side, temp_board) != sf::Vector2i(-1, -1)){

			std::cout << "king check " <<  this->check_king(new_pos, piece_side, temp_board).x << ", " << this->check_king(new_pos, piece_side, temp_board).y << "\n";
			return this->check_king(new_pos, piece_side, temp_board);
		}

		return sf::Vector2i(-1, -1);
	}


// -----------------------------------------------------------------------------------------------------------------------


	bool is_king_stuck(sf::Vector2i curr_king_pos){

		// std::cout << "check????????????????????????\n";

		for (int x = curr_king_pos.x - 1; x <= curr_king_pos.x + 1; x++){

			for (int y = curr_king_pos.y - 1; y <= curr_king_pos.y + 1; y++){

					// std::cout << "square available: " << x << ", " << y << " >>>> " << (curr_king_pos.y - 1 >= 0 && curr_king_pos.y + 1 < 8 && curr_king_pos.x - 1 >= 0 && curr_king_pos.x + 1 < 8 && this->legal_king(curr_king_pos, sf::Vector2i(x, y))) << "\n";

				if (y >= 0 && y < 8 && x >= 0 && x < 8 && this->legal_king(curr_king_pos, sf::Vector2i(x, y))){

					return false;
				}
			}
		}

		return true;
	}


	bool defend_king(sf::Vector2i curr_king_pos){

		std::vector<std::vector<int>> temp_board = this->get_board();

		sf::Vector2i piece_pos = this->check(sf::Vector2i(-1, -1), curr_king_pos, this->piece_side(curr_king_pos.x, curr_king_pos.y));

		if (piece_pos != sf::Vector2i(-1, -1)){

			sf::Vector2i dir_vetor = this->get_vector_dir(curr_king_pos, piece_pos);

			if (dir_vetor.x == 0 || dir_vetor.y == 0){

				sf::Vector2i curr_square(curr_king_pos.x, curr_king_pos.y);

				while (curr_square != piece_pos){

					curr_square.x = curr_square.x + dir_vetor.x;
					curr_square.y = curr_square.y + dir_vetor.y;

					sf::Vector2i blocker_piece = this->check(sf::Vector2i(-1, -1), curr_square, this->piece_side(piece_pos.x, piece_pos.y));

					if (blocker_piece != sf::Vector2i(-1, -1)){

						// std::cout << "deu asneira aqui?\n";
						if (this->check(blocker_piece, curr_square, this->piece_side(blocker_piece.x, blocker_piece.y)) == sf::Vector2i(-1, -1)){

							return false;
						}
					}
				}
			}
		}

		return true;
	}

	bool check_mate(){

		sf::Vector2i curr_king_pos = this->get_curr_king();

		// checks if the king is able to legally move away from the current check

		// this->is_king_stuck(curr_king_pos);

		// checks if the piece can be intercepted or taken out

		// this->defend_king(curr_king_pos);

		if (this->check(sf::Vector2i(-1, -1), sf::Vector2i(curr_king_pos.x, curr_king_pos.y), this->piece_side(curr_king_pos.x, curr_king_pos.y)) != sf::Vector2i(-1, -1) && is_king_stuck(curr_king_pos) && defend_king(curr_king_pos)){

			return true;
		}

		return false;
	}


// -----------------------------------------------------------------------------------------------------------------------

	sf::Vector2i get_curr_king(){

		for (int i = 0; i < 8; i++){

			for (int j = 0; j < 8; j++){

				if (std::abs(this->get_board()[i][j] / 100) == KING && this->piece_side(i, j) * this->get_turn() > 0){

					return sf::Vector2i(i, j);
				}
			}
		}

		return sf::Vector2i(-1, -1);
	}

	void move_piece(float resolution, int squares_number, int num, int prev_x, int prev_y, int new_x, int new_y, sf::Vector2f mouse_pos_view, BoardSQ &boardsq, bool &mated){

		if ((prev_x != new_x || prev_y != new_y) && this->legal_move(sf::Vector2i(prev_x, prev_y), sf::Vector2i(new_x, new_y))){

			// kinda lame way to keep track of the previous king just to change the color of the square

			sf::Vector2i prev_king_pos = this->get_curr_king();

			int temp_piece = this->board[new_x][new_y];
			this->board[new_x][new_y] = num;
			this->board[prev_x][prev_y] = 0;

			sf::Vector2i curr_king_pos = this->get_curr_king();

			if (this->check(sf::Vector2i(-1, -1), sf::Vector2i(curr_king_pos.x, curr_king_pos.y), this->piece_side(curr_king_pos.x, curr_king_pos.y)) == sf::Vector2i(-1, -1)){

				int x = (resolution / squares_number) * new_y;
				int y = (resolution / squares_number) * new_x;

				this->pieces.set_piece_pos(num, x, y);

				this->set_dir(this->get_dir() * (-1));
				this->set_turn(this->get_turn() * (-1));

				// boardsq.undo_prev_color(sf::Color::White, sf::Color(150, 150, 150, 255));

				boardsq.change_fill_color(sf::Color(30, 100, 210, 255), new_x, new_y);

				if ((prev_king_pos.x + prev_king_pos.y) % 2 == 0){

					boardsq.change_fill_color(sf::Color::White, prev_king_pos.x, prev_king_pos.y);
				}
				else{

					boardsq.change_fill_color(sf::Color(150, 150, 150, 255), prev_king_pos.x, prev_king_pos.y);
				}

				if (this->en_passant_piece.x == 1){

					this->board[this->en_passant_piece.y][this->en_passant_piece.z] = 0;
				}

				// sentido contrario do vetor colorcar lá a torre

				if (this->castles){

					this->castles = false;
					int temp_rook;

					sf::Vector2i dir_vetor = this->get_vector_dir(sf::Vector2i(prev_x, prev_y), sf::Vector2i(new_x, new_y));
					std::cout << "castles\n";

					if (dir_vetor.y == -1){

						std::cout << "castles -1\n";
						this->K_R_moved[this->board[new_x][0]] = 1;
						temp_rook = this->board[new_x][0];
						this->board[new_x][new_y - dir_vetor.y] = temp_rook;
						this->board[new_x][0] = 0;

					}
					else if (dir_vetor.y == 1){

						std::cout << "castles 1\n";
						this->K_R_moved[this->board[new_x][7]] = 1;
						temp_rook = this->board[new_x][7];
						this->board[new_x][new_y - dir_vetor.y] = temp_rook;
						this->board[new_x][7] = 0;
					}

					int x = (resolution / squares_number) * (new_y - dir_vetor.y);
					int y = (resolution / squares_number) * new_x;

					this->pieces.set_piece_pos(temp_rook, x, y);
				}

				if (std::abs(this->board[new_x][new_y]) / 100 == ROOK || std::abs(this->board[new_x][new_y]) / 100 == KING){

					this->K_R_moved[this->board[new_x][new_y]] = 1;
				}

				this->update_state();
				mated = false;

			}
			else{

				this->board[new_x][new_y] = temp_piece;
				this->board[prev_x][prev_y] = num;
				this->en_passant_piece = sf::Vector3i(-1, -1, -1);
			}
		}
	}
};