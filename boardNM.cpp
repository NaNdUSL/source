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
	std::stack<std::vector<std::vector<int>>> stack;
	int dir;
	int turn;

public:

	BoardNM(){

		std::vector<std::vector<int>> board;
		this->board = board;
		Pieces pieces;
		this->pieces = pieces;
		this->moving_piece = sf::Vector3i(-1, -1, 0);
		this->dir = 0;
		this->turn = 1;
	}

	BoardNM(std::vector<std::vector<int>> board, Pieces pieces, sf::Vector3i moving_piece, int dir, int turn){

		this->board = board;
		this->pieces = pieces;
		this->moving_piece = moving_piece;
		this->dir = dir;
		this->turn = turn;
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

	void set_stack(std::stack<std::vector<std::vector<int>>> stack){

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

	std::stack<std::vector<std::vector<int>>> get_stack(){

		std::stack<std::vector<std::vector<int>>> stack = this->stack;
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

					switch (curr_board[i][j] / 10){

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

		std::stack<std::vector<std::vector<int>>> stack = this->get_stack();

		// Create and open a text file
		std::ofstream Saves("saves.txt");

		Saves << this->get_board_state(this->get_board()) << "\n";

		while (!stack.empty()){

			std::vector<std::vector<int>> aux = stack.top();

			stack.pop();

			// Write to the file
			Saves << this->get_board_state(aux) << "\n";
		}

		// Close the file
		Saves.close();
	}

	void update_state(){

		std::vector<std::vector<int>> aux = this->board;
		this->stack.push(aux);
	}

	void undo_play(){

		if (!this->stack.empty()){

			std::vector<std::vector<int>> aux = this->stack.top();

			this->stack.pop();

			this->set_board(aux);
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

	sf::Vector2i check_knight(sf::Vector2i pos, int piece_side){

		// up and left

		int i = pos.x - 1;
		int j = pos.y + 2;

		if (i >= 0 && j < 8 && std::abs(this->get_board()[i][j] / 10) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// up and right

		i = pos.x + 1;
		j = pos.y + 2;

		std::cout << "cheguei ao fim do knight: " << std::abs(this->get_board()[i][j] / 10) << ", " << KNIGHT << "\n" << this->piece_side(i,j) << ", " << piece_side << "\n";
		if (i < 8 && j < 8 && std::abs(this->get_board()[i][j] / 10) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// down right

		i = pos.x + 2;
		j = pos.y + 1;

		if (i < 8 && j < 8 && std::abs(this->get_board()[i][j] / 10) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// down left

		i = pos.x + 2;
		j = pos.y - 1;

		if (i < 8 && j >= 0 && std::abs(this->get_board()[i][j] / 10) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// down left

		i = pos.x + 1;
		j = pos.y - 2;

		if (i < 8 && j >= 0 && std::abs(this->get_board()[i][j] / 10) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// down left

		i = pos.x - 1;
		j = pos.y - 2;

		if (i >= 0 && j >= 0 && std::abs(this->get_board()[i][j] / 10) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// down left

		i = pos.x - 2;
		j = pos.y - 1;

		if (i >= 0 && j >= 0 && std::abs(this->get_board()[i][j] / 10) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// down left

		i = pos.x - 2;
		j = pos.y + 1;

		if (i >= 0 && j < 8 && std::abs(this->get_board()[i][j] / 10) == KNIGHT && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);


		return sf::Vector2i(-1, -1);
	}

	sf::Vector2i check_bishop(sf::Vector2i pos, int piece_side, std::vector<std::vector<int>> temp_board){

		// up and left

		int i = pos.x - 1;
		int j = pos.y - 1;

		while (i >= 0 && j >= 0 && temp_board[i][j] == 0){i--; j--;}

		if (i >= 0 && j >= 0 && (std::abs(temp_board[i][j] / 10) == BISHOP || std::abs(temp_board[i][j] / 10) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		// up and right

		i = pos.x - 1;
		j = pos.y + 1;

		while (i >= 0 && j < 8 && temp_board[i][j] == 0){i--; j++;}

		if (i >= 0  && j < 8 && (std::abs(temp_board[i][j] / 10) == BISHOP || std::abs(temp_board[i][j] / 10) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		// down right

		i = pos.x + 1;
		j = pos.y + 1;

		while (i < 8 && j < 8 && temp_board[i][j] == 0){i++; j++;}

		if (i < 8 && j < 8 && (std::abs(temp_board[i][j] / 10) == BISHOP || std::abs(temp_board[i][j] / 10) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		// down left

		i = pos.x + 1;
		j = pos.y - 1;

		while (i < 8 && j >= 0 && temp_board[i][j] == 0){i++; j--;}

		if (i < 8 && j >= 0 && (std::abs(temp_board[i][j] / 10) == BISHOP || std::abs(temp_board[i][j] / 10) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		return sf::Vector2i(-1, -1);
	}

	// returns position of the other player's piece if there is one either on the same line or column of the current player's piece, if it's clear returns (-1, -1)

	sf::Vector2i check_rook(sf::Vector2i pos, int piece_side, std::vector<std::vector<int>> temp_board){

		// up

		int i, j;

		j = pos.y;

		for (i = pos.x - 1; i >= 0 && temp_board[i][j] == 0; i--);

			if (i >= 0 && (std::abs(temp_board[i][j] / 10) == ROOK || std::abs(temp_board[i][j] / 10) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		// down

		for (i = pos.x + 1; i < 8 && temp_board[i][j] == 0; i++);

			if (i < 8 && (std::abs(temp_board[i][j] / 10) == ROOK || std::abs(temp_board[i][j] / 10) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		// left

		i = pos.x;

		for (j = pos.y - 1; j >= 0 && temp_board[i][j] == 0; j--);

			if (j >= 0 && (std::abs(temp_board[i][j] / 10) == ROOK || std::abs(temp_board[i][j] / 10) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		// right

		for (j = pos.y + 1; j < 8 && temp_board[i][j] == 0; j++);

			if (j < 8 && (std::abs(temp_board[i][j] / 10) == ROOK || std::abs(temp_board[i][j] / 10) == QUEEN) && this->piece_side(i, j, temp_board) != piece_side) return sf::Vector2i(i, j);

		return sf::Vector2i(-1, -1);
	}

	sf::Vector2i check_pawn(sf::Vector2i pos, int piece_side){

		// left square

		int i = pos.x + this->dir;
		int j = pos.y - 1;

		if (i >= 0 && i < 8 && j >= 0 && std::abs(this->get_board()[i][j] / 10) == PAWN && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

		// right square

		i = pos.x + this->dir;
		j = pos.y + 1;

		if (i >= 0 && i < 8 && j < 8 && std::abs(this->get_board()[i][j] / 10) == PAWN && this->piece_side(i,j) != piece_side) return sf::Vector2i(i, j);

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

		if(dir_vetor.y == 0){

			if(dir_vetor.x == this->dir){

				if(this->board[new_pos.x][new_pos.y] == EMPTY){

					return true;
				}
			}

			if(dir_vetor.x == this->dir * 2){

				if(this->board[prev_pos.x + this->dir][prev_pos.y] == EMPTY && this->board[new_pos.x][new_pos.y] == EMPTY){

					if((this->dir == -1 && prev_pos.x == 6) || (this->dir == 1 && prev_pos.x == 1)){

						return true;
					}
				}
			}
		}
		else if(dir_vetor.y == -1 || dir_vetor.y == 1){

			if(dir_vetor.x == this->dir){

				if(this->board[new_pos.x][new_pos.y] != EMPTY && this->piece_side(prev_pos.x, prev_pos.y) != this->piece_side(new_pos.x, new_pos.y)){

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

				std::cout << curr_poss.x << ", " << curr_poss.y << "\n";

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

			std::cout << curr_poss.x << ", " << curr_poss.y << "\n";

			curr_poss.x += dir_vetor.x;
			curr_poss.y += dir_vetor.y;

			for (int i = 0; curr_poss != new_pos; i++){

				std::cout << curr_poss.x << ", " << curr_poss.y << "\n";

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
		if (!this->check(prev_pos, new_pos, this->piece_side(prev_pos.x, prev_pos.y))){

			if(prev_pos.x - 1 == new_pos.x && prev_pos.y - 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if(prev_pos.x - 1 == new_pos.x && prev_pos.y == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if(prev_pos.x - 1 == new_pos.x && prev_pos.y + 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if(prev_pos.x == new_pos.x && prev_pos.y - 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if(prev_pos.x == new_pos.x && prev_pos.y + 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if(prev_pos.x + 1 == new_pos.x && prev_pos.y - 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if(prev_pos.x + 1 == new_pos.x && prev_pos.y == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}

			if(prev_pos.x + 1 == new_pos.x && prev_pos.y + 1 == new_pos.y && this->piece_side(new_pos.x, new_pos.y) != this->piece_side(prev_pos.x, prev_pos.y)){

				return true;
			}
		}

		return false;
	}

	bool legal_move(sf::Vector2i prev_pos, sf::Vector2i new_pos){

		switch(std::abs(this->board[prev_pos.x][prev_pos.y]) / 10){

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

	bool check(sf::Vector2i prev_pos, sf::Vector2i new_pos, int piece_side){

		std::vector<std::vector<int>> temp_board = this->get_board();
		temp_board[new_pos.x][new_pos.y] = temp_board[prev_pos.x][prev_pos.y];
		temp_board[prev_pos.x][prev_pos.y] = 0;

		std::cout << "temp board ->>>>>>>>>>>>> \n";
		this->display_board(temp_board);

		// if(this->check_pawn(pos, piece_side) != sf::Vector2i(-1, -1)){

		// 	std::cout << "pawn check " <<  this->check_pawn(pos, piece_side).x << ", " << this->check_pawn(pos, piece_side).y << "\n";
		// 	return true;
		// }

		// if(this->check_knight(pos, piece_side) != sf::Vector2i(-1, -1)){

		// 	std::cout << "knight check " <<  this->check_knight(pos, piece_side).x << ", " << this->check_knight(pos, piece_side).y << "\n";
		// 	return true;
		// }

		if(this->check_bishop(new_pos, piece_side, temp_board) != sf::Vector2i(-1, -1)){

			std::cout << "bishop check " <<  this->check_bishop(new_pos, piece_side, temp_board).x << ", " << this->check_bishop(new_pos, piece_side, temp_board).y << "\n";
			return true;
		}

		if(this->check_rook(new_pos, piece_side, temp_board) != sf::Vector2i(-1, -1)){

			std::cout << "rook check " <<  this->check_rook(new_pos, piece_side, temp_board).x << ", " << this->check_rook(new_pos, piece_side, temp_board).y << "\n";
			return true;
		}

		return false;
	}

	bool check_mate(){

		return true;
	}

	void move_piece(float resolution, int squares_number, int num, int prev_x, int prev_y, int new_x, int new_y){

		// int res = this->board[new_x][new_y];
		// std::cout << "prev: " << prev_x << ", " << prev_y << " new: " << new_x << ", " << new_y << "\n";

		if ((prev_x != new_x || prev_y != new_y) && this->legal_move(sf::Vector2i(prev_x, prev_y), sf::Vector2i(new_x, new_y))){

			this->board[new_x][new_y] = num;
			this->board[prev_x][prev_y] = 0;

			int x = (resolution / squares_number) * new_y;
			int y = (resolution / squares_number) * new_x;

			this->pieces.set_piece_pos(num, x, y);

			this->set_dir(this->get_dir() * (-1));
			this->set_turn(this->get_turn() * (-1));
		}
	}
};