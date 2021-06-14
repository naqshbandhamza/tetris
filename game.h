#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Piece;

class game
{
	friend class square;
	friend class horizontal_piece;
	friend class horizontal_top_left;
	friend class two_in_mid;
private:
	int rows;
	int cols;
	char** grid;
	sf::RectangleShape colorgrid[20][10];
	static const int total_shapes = 7;
	Piece* list_of_pieces[total_shapes];
	int component_count;
	bool vertical_trigger;
	int rotation_no;
public:
	game(sf::RenderWindow& win);
	
	bool can_rotate(int c);
	void check_and_burst_if(sf::RenderWindow& win, sf::Sprite& sprite);
	void shift_all_above_down_at(int row);
	void display_grid(sf::RenderWindow& win);
	bool check_if_can_move_right(int c,std::string extra_t = "");
	bool check_if_can_move_left(int c,std::string extra_t = "");
	void rotate(int c);
	void add_character_at_pos(int r, int c,char temp);
	int conmplete_piece_cycle(sf::RenderWindow& win,sf::Sprite& sprite);
	void remove_character_at_pos(int r, int c);
	~game();
};

