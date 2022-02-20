// Pieces class

class Pieces{

private:

	std::map<int, sf::Sprite> pieces;
	std::string texture;
	sf::Vector2u texture_size;

public:


	Pieces(){

		std::map<int, sf::Sprite> pieces;
		this->pieces = pieces;
		this->texture = "default.png";
		sf::Vector2u texture_size(0.0f, 0.0f);
		this->texture_size = texture_size;
	}

	Pieces(std::map<int, sf::Sprite> pieces, char str[], sf::Vector2u texture_size){

		this->pieces = pieces;
		this->texture = str;
		this->texture_size = texture_size;
	}

	void set_pieces(std::map<int, sf::Sprite> pieces){

		this->pieces = pieces;
	}

	void set_texture(std::string str){

		this->texture = str;
	}

	void set_texture_size(sf::Vector2u texture_size){

		this->texture_size = texture_size;
	}

	std::map<int, sf::Sprite> get_pieces(){

		std::map<int, sf::Sprite> pieces;
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

	void insert_elem(int num, sf::Sprite piece){

		this->pieces.insert({num, piece});
	}

	void set_piece_pos(int num, float x, float y){

		this->pieces.find(num)->second.setPosition(x, y);
	}

	void delete_piece(int num){

		std::map<int, sf::Sprite>::iterator piece = this->pieces.find(num);
		this->pieces.erase(piece); 
	}

	sf::Sprite get_piece(int num){

		sf::Sprite piece = this->pieces.find(num)->second;
		return piece;
	}
};