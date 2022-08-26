#include "boardNM.cpp"
// #include "boardSQ.cpp"

// Game class

class Game{

private:

	// Window vars

	sf::RenderWindow* window;
	sf::VideoMode video_mode;
	sf::Event event;
	float resolution;
	int squares_number;
	bool holding;
	bool pressing;
	bool mated;

	// Mouse vars

	sf::Vector2i mouse_pos;
	sf::Vector2f mouse_pos_view;
	sf::Texture texture;

	// Other classes

	BoardSQ boardsq;
	BoardNM boardnm;

	// Private methods

	void init_vars(){

		this->window = nullptr;
		this->resolution = 800.0f;
		this->squares_number = 8;
		this->holding = false;
		this->pressing = false;
		this->mated = false;

		if(!this->texture.loadFromFile("Pieces.png")){

			std::cout << "Problem loading textures\n";
		}
	}

	void init_window(){

		this->video_mode.height = this->resolution;
		this->video_mode.width = this->resolution;
		this->window = new sf::RenderWindow(this->video_mode, "Default", sf::Style::Titlebar | sf::Style::Close);
		this->window->setFramerateLimit(144);
	}

public: 

	// Constructors / Destructors

	Game(int white, int pboard){

		this->init_vars();
		this->init_window();
		this->boardsq.fill_board(this->squares_number, this->resolution, sf::Color::White, sf::Color(150, 150, 150, 255));

		sf::Vector2u aux(this->texture.getSize().x / 6, this->texture.getSize().y / 2);
		this->boardnm.set_texture_size(aux);

		std::fstream Myfile("boardstates.txt");
		std::string line;

		// gets the board chosen

		for (int i = 0; i < pboard; i++){

			getline(Myfile, line);
		}

		if (!white){

			this->boardnm.fill_board(line);
		}
		else{

			std::string new_line = this->reverse_board(line, line.length());
			this->boardnm.fill_board(new_line);
		}
		this->boardnm.set_turn(1);
		this->boardnm.set_dir(-2 * white + 1);
		// std::cout << line << "sup\n";
		this->boardnm.load_pieces(this->squares_number, this->resolution);
		this->boardnm.update_state();
		this->boardnm.display_board();
		// this->boardnm.get_board_state();
	}

	virtual ~Game(){

		delete this->window;
	}

	// Accessors

	const bool running(){

		return this->window->isOpen();
	}

	// Methods

	std::string reverse_board(std::string s, int N){

		std::string new_str = "\0";

		for (int i = 0; i < N; i++){

			if (s[i] == '_'){

				new_str.insert(0, 1, s[i+1]);
				new_str.insert(0, 1, s[i++]);
			}
			else{

				new_str.insert(0, 1, s[i]);
			}
		}

		return new_str;
	}

	void poll_events(){

		while(this->window->pollEvent(this->event)){

			switch(this->event.type){

				case sf::Event::Closed:

				this->window->close();
			}
		}
	}

	void update_mouse_pos(){

		this->mouse_pos = sf::Mouse::getPosition(*this->window);
		this->mouse_pos_view = this->window->mapPixelToCoords(this->mouse_pos);
		// std::cout << "mouse position: x_" << this->mouse_pos_view.x << " y_" << this->mouse_pos_view.y << "\n";
	}

	void update_board(){

		sf::Vector2i curr_king_pos = this->boardnm.get_curr_king();

		if (!this->mated){

			this->mated = true;

			if ((this->boardnm.get_moving_piece().x != curr_king_pos.x || this->boardnm.get_moving_piece().y != curr_king_pos.y) && this->boardnm.check(sf::Vector2i(-1, -1), sf::Vector2i(curr_king_pos.x, curr_king_pos.y), this->boardnm.piece_side(curr_king_pos.x, curr_king_pos.y)) != sf::Vector2i(-1, -1)){

				this->boardsq.change_fill_color(sf::Color(155, 155, 0, 255), curr_king_pos.x, curr_king_pos.y);
			}

			if (this->boardnm.check_mate()){

				this->boardsq.change_fill_color(sf::Color(255, 30, 30, 255), curr_king_pos.x, curr_king_pos.y);
			}
			else if (this->boardnm.stalemate()){

				this->boardsq.change_fill_color(sf::Color(30, 255, 30, 255), curr_king_pos.x, curr_king_pos.y);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->mouse_pos_view.x >= 0.0f && this->mouse_pos_view.x <= resolution && this->mouse_pos_view.y >= 0.0f && this->mouse_pos_view.y <= resolution){

			if (!this->holding){

				this->holding = true;

				sf::Vector2i pos = this->boardnm.get_piece_index(this->mouse_pos_view, this->resolution, this->squares_number);

				sf::Vector3i aux = this->boardnm.get_moving_piece();

				std::cout << "turn: " << this->boardnm.get_turn() << "\n";

				// std::cout << "pos: " << pos.x << ", " << pos.y << "\n";

				// std::cout << "aux: " << aux.x << ", " << aux.y << ", " << aux.z << "\n";

				if (pos.x != -1 && pos.y != -1 && (pos.x != aux.x || pos.y != aux.y)){

					// this->boardsq.clean(this->squares_number, this->resolution, sf::Color::White, sf::Color(150, 150, 150, 255));

					this->boardsq.undo_prev_color(sf::Color::White, sf::Color(150, 150, 150, 255));

					this->boardsq.select_new_square(this->mouse_pos_view, this->resolution, this->squares_number, sf::Color(30, 50, 150, 255), sf::Color::White, sf::Color(150, 150, 150, 255));

					// if i didn't select one piece that i wanna play and i click on one piece and not on an empty square then "grab" that piece

					if(this->boardnm.get_moving_piece().z == 0 && this->boardnm.get_piece_number(pos.x, pos.y) != 0){

						int piece_type = this->boardnm.get_piece_number(pos.x, pos.y);

						aux = sf::Vector3i(pos.x, pos.y, piece_type);

						if (aux.z * this->boardnm.get_turn() > 0){

							this->boardnm.set_moving_piece(aux);
						}
					} // else if i already have one piece grabbed then check if i can play it
					else if (this->boardnm.get_moving_piece().z != 0){

						// if I'm clicking on a piece from the other player or on an empty square check if i can play it
						if (this->boardnm.piece_side(pos.x, pos.y) != this->boardnm.piece_side(aux.x, aux.y)){

							this->boardnm.move_piece(this->resolution, this->squares_number, aux.z, aux.x, aux.y, pos.x, pos.y, this->mouse_pos_view, this->boardsq, this->mated);

							std::cout << "prev: " << this->boardnm.get_board()[aux.x][aux.y] << "-> " << aux.x << ", " << aux.y << "\n";

							std::cout << "new: " << this->boardnm.get_board()[pos.x][pos.y] << "-> " << pos.x << ", " << pos.y << "\n";

							// this->boardsq.undo_prev_color(this->mouse_pos_view, this->resolution, this->squares_number, sf::Color::White, sf::Color(150, 150, 150, 255));

							this->boardnm.set_moving_piece(sf::Vector3i(-1, -1, 0));

							// this->boardsq.set_selected(sf::Vector2i(-1, -1));

							// this->mated = false;

							// std::cout << "curr moving piece: " << aux.x << ", " << aux.y << ", " << aux.z << "\n";

							// this->boardnm.display_board();
						}
						else{

							int piece_type = this->boardnm.get_piece_number(pos.x, pos.y);

							aux = sf::Vector3i(pos.x, pos.y, piece_type);

							this->boardnm.set_moving_piece(aux);
						}
					}
				}
			}
		}
		else{

			this->holding = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){

			this->boardsq.clean(this->squares_number, this->resolution, sf::Color::White, sf::Color(150, 150, 150, 255));
			this->boardnm.set_moving_piece(sf::Vector3i(-1, -1, 0));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)){

			if (!this->pressing){

				this->pressing = true;

				this->mated = false;

				this->boardnm.undo_play(this->boardsq, this->resolution, this->squares_number);

				this->boardnm.load_pieces(this->squares_number, this->resolution);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){

			if (!this->pressing){

				this->pressing = true;

				this->boardnm.save_board_state();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){

			if (!this->pressing){

				this->pressing = true;

				this->boardnm.display_board();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){

			if (!this->pressing){

				this->pressing = true;

				std::cout << "clicked on P\n";

				// this->boardnm.print_special_pieces();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)){

			if (!this->pressing){

				this->boardsq.clean(this->squares_number, this->resolution, sf::Color::White, sf::Color(150, 150, 150, 255));

				this->pressing = true;

				this->mated = false;

				std::cout << "clicked on L\n";

				this->boardnm.load_from_saves();

				// this->boardnm.display_board();

				this->boardnm.load_pieces(this->squares_number, this->resolution);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){

			if (!this->pressing){

				this->pressing = true;

				std::cout << "clicked on E\n";

				this->boardnm.print_stack(this->boardnm.get_stack());

				// this->boardnm.display_board();

				// this->boardnm.load_pieces(this->squares_number, this->resolution);
			}
		}
		else{

			this->pressing = false;
		}
	}

	void update(){

		this->poll_events();

		this->update_mouse_pos();

		this->update_board();
	}

	void render_board(sf::RenderTarget &target){

		bool color;

		for (auto &e: this->boardsq.get_board_image()){

			for (auto &d: e){

				target.draw(d);
			}
		}

		for (int i = 0; i < 8; i++){

			for (int j = 0; j < 8; j++){

				if (this->boardnm.get_board()[i][j]){

					sf::Sprite sprite;
					sprite = this->boardnm.get_pieces_map().find(this->boardnm.get_board()[i][j])->second;
					sprite.setTexture(this->texture);
					target.draw(sprite);
				}
			}
		}
	}

	void render(){

		this->window->clear(sf::Color(30,30,30,255));

		this->render_board(*this->window);

		this->window->display();
	}
};