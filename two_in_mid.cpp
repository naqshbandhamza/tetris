#include "two_in_mid.h"
#include "game.h"
#include <cstdlib>
#include <iostream>

using namespace std;

two_in_mid::two_in_mid(game* ptr, std::string type)
{
	this->ptr = ptr;
	this->type = type;
}

void two_in_mid::create()
{
	char arr[7] = { 'r','y','g','b','p','o','P' };//p for purple and P for pink
	srand(time(NULL));
	int v2 = rand() % 7;
	this->color = arr[v2];

	int xchoice = rand() % 2;


	if (xchoice == 1)
	{
		this->pos_p1_r = this->pos_p2_r = 0;
		this->pos_p3_r = this->pos_p4_r = 1;
	}
	else
	{
		this->pos_p1_r = this->pos_p2_r = 1;
		this->pos_p3_r = this->pos_p4_r = 0;
	}


	srand(time(NULL));
	this->pos_p1_c = rand() % 10;
	while (this->pos_p1_c + 2 >= 10)
	{
		this->pos_p1_c = rand() % 10;
	}


	this->pos_p2_c = this->pos_p3_c = this->pos_p1_c + 1;
	this->pos_p4_c = this->pos_p3_c + 1;


	cout << "pos p1r:" << pos_p1_r << endl;
	cout << "pos p1c:" << pos_p1_c << endl;
	cout << "pos p2r:" << pos_p2_r << endl;
	cout << "pos p2c:" << pos_p2_c << endl;
	cout << "pos p3r:" << pos_p3_r << endl;
	cout << "pos p3c:" << pos_p3_c << endl;
	cout << "pos p4r:" << pos_p4_r << endl;
	cout << "pos p4c:" << pos_p4_c << endl;


	ptr->grid[this->pos_p1_r][this->pos_p1_c] = this->color;
	ptr->grid[this->pos_p2_r][this->pos_p2_c] = this->color;
	ptr->grid[this->pos_p3_r][this->pos_p3_c] = this->color;
	ptr->grid[this->pos_p4_r][this->pos_p4_c] = this->color;

	sf::Color colorf;

	if (this->color == 'r')
	{
		colorf = sf::Color::Red;
	}
	else if (this->color == 'y')
	{
		colorf = sf::Color::Yellow;
	}
	else if (this->color == 'g')
	{
		colorf = sf::Color::Green;
	}
	else if (color == 'b')
	{
		colorf = sf::Color::Blue;
	}
	else if (color == 'p')
	{
		colorf = sf::Color(153, 0, 153);
	}
	else if (color == 'o')
	{
		colorf = sf::Color(255, 128, 0);
	}
	else if (color == 'P')
	{
		colorf = sf::Color(255, 0, 255);
	}

	ptr->colorgrid[this->pos_p1_r][this->pos_p1_c].setFillColor(colorf);
	ptr->colorgrid[this->pos_p2_r][this->pos_p2_c].setFillColor(colorf);
	ptr->colorgrid[this->pos_p3_r][this->pos_p3_c].setFillColor(colorf);
	ptr->colorgrid[this->pos_p4_r][this->pos_p4_c].setFillColor(colorf);



}

void two_in_mid::update_pos(int p1_r, int p1_c, int p2_r, int p2_c, int p3_r, int p3_c, int p4_r, int p4_c)
{
	ptr->remove_character_at_pos(this->pos_p1_r, this->pos_p1_c);
	ptr->remove_character_at_pos(this->pos_p2_r, this->pos_p2_c);
	ptr->remove_character_at_pos(this->pos_p3_r, this->pos_p3_c);
	ptr->remove_character_at_pos(this->pos_p4_r, this->pos_p4_c);

	ptr->colorgrid[this->pos_p1_r][this->pos_p1_c].setFillColor(sf::Color::Black);
	ptr->colorgrid[this->pos_p2_r][this->pos_p2_c].setFillColor(sf::Color::Black);
	ptr->colorgrid[this->pos_p3_r][this->pos_p3_c].setFillColor(sf::Color::Black);
	ptr->colorgrid[this->pos_p4_r][this->pos_p4_c].setFillColor(sf::Color::Black);

	this->pos_p1_c = p1_c;
	this->pos_p1_r = p1_r;

	this->pos_p2_c = p2_c;
	this->pos_p2_r = p2_r;

	this->pos_p3_c = p3_c;
	this->pos_p3_r = p3_r;

	this->pos_p4_c = p4_c;
	this->pos_p4_r = p4_r;

	ptr->add_character_at_pos(this->pos_p1_r, this->pos_p1_c, this->color);
	ptr->add_character_at_pos(this->pos_p2_r, this->pos_p2_c, this->color);
	ptr->add_character_at_pos(this->pos_p3_r, this->pos_p3_c, this->color);
	ptr->add_character_at_pos(this->pos_p4_r, this->pos_p4_c, this->color);

	sf::Color colorf;

	if (this->color == 'r')
	{
		colorf = sf::Color::Red;
	}
	else if (this->color == 'y')
	{
		colorf = sf::Color::Yellow;
	}
	else if (this->color == 'g')
	{
		colorf = sf::Color::Green;
	}
	else if (color == 'b')
	{
		colorf = sf::Color::Blue;
	}
	else if (color == 'p')
	{
		colorf = sf::Color(153, 0, 153);
	}
	else if (color == 'o')
	{
		colorf = sf::Color(255, 128, 0);
	}
	else if (color == 'P')
	{
		colorf = sf::Color(255, 0, 255);
	}

	ptr->colorgrid[this->pos_p1_r][this->pos_p1_c].setFillColor(colorf);
	ptr->colorgrid[this->pos_p2_r][this->pos_p2_c].setFillColor(colorf);
	ptr->colorgrid[this->pos_p3_r][this->pos_p3_c].setFillColor(colorf);
	ptr->colorgrid[this->pos_p4_r][this->pos_p4_c].setFillColor(colorf);

}

two_in_mid::~two_in_mid()
{
	cout << "horizontal piece destructor called" << endl;
}