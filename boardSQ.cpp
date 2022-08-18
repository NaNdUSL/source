// Board class

class BoardSQ{

private:

	std::vector<std::vector<sf::RectangleShape>> board_image;
	int dir;
	sf::Vector2i selected;
	sf::Color prev_color;

public:

	BoardSQ(){

		std::vector<std::vector<sf::RectangleShape>> board_image;
		this->board_image = board_image;
		this->dir = 1;
		this->selected.x = -1;
		this->selected.y = -1;
		this->prev_color = sf::Color::White;
	}

	BoardSQ(std::vector<std::vector<sf::RectangleShape>> board_image, int dir, sf::Vector2i selected){

		this->board_image = board_image;
		this->dir = dir;
		this->selected = selected;
	}

	void set_board(std::vector<std::vector<sf::RectangleShape>> board){

		this->board_image = board;
	}

	void set_dir(int dir){

		this->dir = dir;
	}

	void set_selected(sf::Vector2i selected){

		this->selected = selected;;
	}

	std::vector<std::vector<sf::RectangleShape>> get_board_image(){

		std::vector<std::vector<sf::RectangleShape>> board = this->board_image;
		return board;
	}

	int get_dir(){

		int dir = this->dir;
		return dir;
	}

	sf::Vector2i get_selected(){

		sf::Vector2i sel = this->selected;
		return sel;
	}

	sf::Color get_prev_color(){

		sf::Color color = this->prev_color;
		return color;
	}

	sf::RectangleShape get_square(int i, int j){

		sf::RectangleShape square = this->board_image[i][j];
		return square;
	}

	void set_square(sf::RectangleShape square, int i, int j){

		this->board_image[i][j] = square;
	}

	void set_prev_color(sf::Color color){

		this->prev_color = color;
	}

	void change_fill_color(sf::Color color, int i, int j){

		sf::RectangleShape square = this->get_square(i,j);
		square.setFillColor(color);
		set_square(square, i, j);
	}

	void change_outline_color(sf::Color color, int i, int j){

		sf::RectangleShape square = this->get_square(i,j);
		square.setOutlineColor(color);
		set_square(square, i, j);
	}

	void change_square_size(sf::Vector2f size, int i, int j){

		sf::RectangleShape square = this->get_square(i,j);
		square.setSize(size);
		set_square(square, i, j);
	}

	sf::Vector2f get_square_size(int i, int j){

		sf::RectangleShape square = this->board_image[i][j];
		return square.getSize();
	}

	sf::Color get_square_fill_color(int i, int j){

		sf::RectangleShape square = this->board_image[i][j];
		return square.getFillColor();
	}

	sf::Color get_square_outline_color(int i, int j){

		sf::RectangleShape square = this->board_image[i][j];
		return square.getOutlineColor();
	}

	void fill_board(int squares_number, float resolution, sf::Color color1, sf::Color color2){

		std::vector<sf::RectangleShape> aux;
		bool color;

		for (int row = 0; row < 8; row++){

			aux.clear();

			for (int col = 0; col < 8; col++){

				sf::RectangleShape square;
				square.setSize(sf::Vector2f(resolution / squares_number, resolution / squares_number));
				square.setPosition(col * resolution / squares_number, row * resolution / squares_number);

				if ((row + col) % 2 == 0){

					square.setFillColor(color1);
				}
				else{

					square.setFillColor(color2);
				}

				aux.push_back(square);
			}

			this->board_image.push_back(aux);
		}
	}

	sf::Vector2i highlight_square(sf::Color color, sf::Vector2f mouse_coords, float resolution, int squares_number){

		sf::Vector2i board_pos(-1, -1);

		for (std::vector<sf::RectangleShape> vec : get_board_image()){

			for (sf::RectangleShape element : vec){

				if (element.getGlobalBounds().contains(mouse_coords)){

					board_pos.x = static_cast<int> (element.getPosition().y * squares_number / resolution);
					board_pos.y = static_cast<int> (element.getPosition().x * squares_number / resolution);
				}
			}
		}

		return board_pos;
	}

	void select_new_square(sf::Vector2f mouse_coords, float resolution, int squares_number, sf::Color main_color, sf::Color color1, sf::Color color2){

		sf::Vector2i square = highlight_square(main_color, mouse_coords, resolution, squares_number);

		if ((this->selected.x != -1 && this->selected.y != -1) && (this->selected.x != square.x || this->selected.y != square.y)){

			this->change_fill_color(this->get_prev_color(), this->selected.x, this->selected.y);
		}

		this->set_prev_color(this->get_square_fill_color(square.x, square.y));
		this->change_fill_color(main_color, square.x, square.y);
		this->change_outline_color(main_color, square.x, square.y);
		this->set_selected(square);
	}

	void undo_prev_color(sf::Color color1, sf::Color color2){

		if (this->selected.x != -1 && this->selected.y != -1){

			this->change_fill_color(this->get_prev_color(), this->selected.x, this->selected.y);
		}

		this->set_selected(sf::Vector2i(-1, -1));
	}

	void clean(int squares_number, float resolution, sf::Color color1, sf::Color color2){

		for (int row = 0; row < 8; row++){

			for (int col = 0; col < 8; col++){

				if ((row + col) % 2 == 0){

					this->change_fill_color(color1, row, col);
				}
				else{

					this->change_fill_color(color2, row, col);
				}
			}
		}

		this->set_selected(sf::Vector2i(-1, -1));
	}
};

/*
Wolves asleep amidst the trees
Bats all swaying in the breeze
But one soul lies anxious, wide awake
Fearing all manner of ghouls, hags and wraiths
For your dolly polly sleep has flown
Don't dare let her tremble alone
For the Witcher
Heartless cold
Paid in coin of gold
He comes, he'll go, leave naught behind
But heartache and woe
Deep, deep woe
Birds are silent for the night
Cows turned in as daylight dies
But one soul lies anxious wide awake
Fearing all manner of ghouls, hags and wraiths
My dear dolly polly shut your eyes
Lie still, lie silent utter no cries
As the Witcher
Brave and bold
Paid in coin of gold
He'll chop and slice you
Gut and dice you
Eat you up whole
Eat you whole
*/