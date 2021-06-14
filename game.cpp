#include "game.h"
#include "square.h"
#include "horizontal_piece.h"
#include "horizontal_top_left.h"
#include "two_in_mid.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include <Windows.h>
using namespace std;

game::game(sf::RenderWindow & win)
{
	this->rotation_no = 0;
	vertical_trigger = false;
	this->component_count = 0;
	this->list_of_pieces[this->component_count] = new square(this,"square");
	this->component_count++;
	this->list_of_pieces[this->component_count] = new horizontal_piece(this,"horizontal");
	this->component_count++;
	this->list_of_pieces[this->component_count] = new horizontal_top_left(this, "horizontaltopleft");
	this->component_count++;
	this->list_of_pieces[this->component_count] = new two_in_mid(this, "twoinmid");
	this->component_count++;

	this->rows = 20;
	this->cols = 10;
	this->grid = new char* [this->rows];
	sf::Vector2f pos;
	pos.x = 450; pos.y = 50;
	for (int i = 0; i < this->rows; i++)
	{
		grid[i] = new char[this->cols];
		pos.x = 450;
		for (int j = 0; j < this->cols; j++)
		{
			grid[i][j] = 'e';
			this->colorgrid[i][j].setFillColor(sf::Color::Black);
			this->colorgrid[i][j].setOutlineColor(sf::Color::White);
			this->colorgrid[i][j].setOutlineThickness(1);
			this->colorgrid[i][j].setSize(sf::Vector2f(30,30));
			this->colorgrid[i][j].setPosition(pos);
			pos.x += 30;
		}
		pos.y += 30;
	}

}

void game::display_grid(sf::RenderWindow &win)
{
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			win.draw(this->colorgrid[i][j]);
		}
	}
	
}

bool game::check_if_can_move_left(int c,std::string extra_t)
{
	if (list_of_pieces[c]->type == "square")
	{
		if (list_of_pieces[c]->pos_p1_c -1  >= 0 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e'
			&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c - 1] == 'e'
			)
			return true;
	}
	else if (list_of_pieces[c]->type == "horizontal")
	{
		if (extra_t != "verticalH")
		{
			if (list_of_pieces[c]->pos_p1_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e')
				return true;
		}
		else
		{
			if (list_of_pieces[c]->pos_p1_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e'
				&& this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c - 1] == 'e'
				&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c - 1] == 'e'
				&& this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c - 1] == 'e'
				)
				return true;
		}
	}
	else if (list_of_pieces[c]->type == "horizontaltopleft")
	{
		if (rotation_no == 0)
		{
			if (list_of_pieces[c]->pos_p2_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c - 1] == 'e'
				&& this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e'
				)
				return true;
		}
		else if (rotation_no == 1)
		{
			if (list_of_pieces[c]->pos_p2_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c - 1] == 'e'
				&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c - 1] == 'e'
				&& this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c - 1] == 'e'
				)
				return true;
		}
		else if (rotation_no == 2)
		{
			if (list_of_pieces[c]->pos_p4_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e'
				&& this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c - 1] == 'e'
				)
				return true;
		}
		else if (rotation_no == 3)
		{
			if ( (list_of_pieces[c]->pos_p1_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e'
				&& list_of_pieces[c]->pos_p1_r==list_of_pieces[c]->pos_p2_r && this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c - 1] == 'e'
				&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c - 1] == 'e') ||

				(list_of_pieces[c]->pos_p1_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e'
					&& list_of_pieces[c]->pos_p1_r == list_of_pieces[c]->pos_p3_r && this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c - 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c - 1] == 'e') ||

				(list_of_pieces[c]->pos_p1_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e'
						&& list_of_pieces[c]->pos_p1_r == list_of_pieces[c]->pos_p4_r && this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c - 1] == 'e'
						&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c - 1] == 'e')
				)
				return true;
		}
	}
	else if (list_of_pieces[c]->type == "twoinmid")
	{
		if (rotation_no == 0)
		{
			if ( list_of_pieces[c]->pos_p1_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e'
				&& (this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c - 1] == 'e' ||
					this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c - 1] == 'e'))
				return true;
		}
		else if (rotation_no == 2)
		{
				if (list_of_pieces[c]->pos_p4_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c - 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c - 1] == 'e')
					return true;
		}
		else if (rotation_no == 1)
		{
			if (list_of_pieces[c]->pos_p1_c > list_of_pieces[c]->pos_p4_c)
			{
				if (list_of_pieces[c]->pos_p3_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c - 1] == 'e' &&
						this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c - 1] == 'e')
					return true;
			}
			else
			{
				if (list_of_pieces[c]->pos_p2_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c - 1] == 'e' &&
						this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c - 1] == 'e')
					return true;
			}
		}
		else if (rotation_no == 3)
		{

			if (list_of_pieces[c]->pos_p1_c > list_of_pieces[c]->pos_p4_c)
			{
				//green wala
				if (list_of_pieces[c]->pos_p3_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c - 1] == 'e' &&
					this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c - 1] == 'e')
					return true;
			}
			else
			{
				//red wala
				if (list_of_pieces[c]->pos_p2_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c - 1] == 'e' &&
					this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c - 1] == 'e')
					return true;
			}
		}
	}
	return false;
}

bool game::check_if_can_move_right(int c,std::string extra_t)
{
	if (list_of_pieces[c]->pos_p4_c + 1 < 10
		)
	{
		if (list_of_pieces[c]->type == "square")
		{
			if (this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c + 1] == 'e'
				&& this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c + 1] == 'e')
			{
				return true;
			}
		}
		else if (list_of_pieces[c]->type == "horizontal")
		{
			if (extra_t != "verticalH")
			{
				if (
					this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c + 1] == 'e'
					)
				{
					return true;
				}
			}
			else
			{

				if (
					this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c + 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c + 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c + 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c + 1] == 'e'
					)
				{
					return true;
				}
			}
		}
		else if (list_of_pieces[c]->type == "horizontaltopleft")
		{
			if (rotation_no == 0)
			{
				if (
					this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c + 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c + 1] == 'e'
					)
				{
					return true;
				}
			}
			else if (rotation_no == 1)
			{
				if ((list_of_pieces[c]->pos_p1_c + 1 < 10 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c + 1] == 'e'
					&& list_of_pieces[c]->pos_p1_r == list_of_pieces[c]->pos_p2_r && this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c + 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c + 1] == 'e') ||

					(list_of_pieces[c]->pos_p1_c + 1 < 10 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c + 1] == 'e'
						&& list_of_pieces[c]->pos_p1_r == list_of_pieces[c]->pos_p3_r && this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c + 1] == 'e'
						&& this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c + 1] == 'e') ||

						(list_of_pieces[c]->pos_p1_c + 1 < 10 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c + 1] == 'e'
							&& list_of_pieces[c]->pos_p1_r == list_of_pieces[c]->pos_p4_r && this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c + 1] == 'e'
							&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c + 1] == 'e')
					)
					return true;
			}
			else if (rotation_no == 2)
			{
				if (list_of_pieces[c]->pos_p2_c + 1 < 10 && this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c + 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c + 1] == 'e'
					)
					return true;
			}
			else if (rotation_no == 3)
			{
				if (list_of_pieces[c]->pos_p2_c + 1 < 10 && this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c + 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c + 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c + 1] == 'e'
					)
					return true;
			}
		}
		else if (list_of_pieces[c]->type == "twoinmid")
		{
			if (rotation_no == 0)
			{
				if (
					
					(this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c + 1] == 'e' ||
						this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c + 1] == 'e')
					&& this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c + 1] == 'e')
				{
					return true;
				}
			}
			else if (rotation_no == 2)
			{
				if (list_of_pieces[c]->pos_p1_c + 1 < 10 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c + 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c + 1] == 'e')
					return true;
			}
			else if (rotation_no == 1)
			{
				if (list_of_pieces[c]->pos_p1_c > list_of_pieces[c]->pos_p4_c)
				{
					if (list_of_pieces[c]->pos_p2_c + 1 < 10 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c + 1] == 'e'
						&& this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c + 1] == 'e' &&
						this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c + 1] == 'e')
						return true;
				}
				else
				{
					if (list_of_pieces[c]->pos_p3_c + 1 < 10 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c + 1] == 'e'
						&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c + 1] == 'e' &&
						this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c + 1] == 'e')
						return true;
				}
			}
			else if (rotation_no == 3)
			{
				if (list_of_pieces[c]->pos_p1_c > list_of_pieces[c]->pos_p4_c)
				{
					if (list_of_pieces[c]->pos_p2_c + 1 < 10 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c + 1] == 'e'
						&& this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c + 1] == 'e' &&
						this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c + 1] == 'e')
						return true;
				}
				else
				{
					if (list_of_pieces[c]->pos_p3_c + 1 < 10 && this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c + 1] == 'e'
						&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c + 1] == 'e' &&
						this->grid[list_of_pieces[c]->pos_p4_r][list_of_pieces[c]->pos_p4_c + 1] == 'e')
						return true;
				}
			}
		}
	}
	return false;
}

void game::rotate(int c)
{
	if (list_of_pieces[c]->type == "square")
		cout << "no need to do any roataion" << endl;
	else if (list_of_pieces[c]->type == "horizontal")
	{
		if (vertical_trigger == false)
		{
			if (list_of_pieces[c]->pos_p1_r >= 3)
			{

				if (this->grid[list_of_pieces[c]->pos_p4_r - 3][list_of_pieces[c]->pos_p4_c] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p4_r - 2][list_of_pieces[c]->pos_p4_c] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p4_r - 1][list_of_pieces[c]->pos_p4_c] == 'e'
					)
				{
					list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p4_r - 3, list_of_pieces[c]->pos_p4_c,
						list_of_pieces[c]->pos_p4_r - 2, list_of_pieces[c]->pos_p4_c,
						list_of_pieces[c]->pos_p4_r - 1, list_of_pieces[c]->pos_p4_c,
						list_of_pieces[c]->pos_p4_r, list_of_pieces[c]->pos_p4_c);
					vertical_trigger = true;
				}
			}
			else
			{
				if (this->grid[list_of_pieces[c]->pos_p1_r + 1][list_of_pieces[c]->pos_p1_c] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p1_r + 2][list_of_pieces[c]->pos_p1_c] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p1_r + 3][list_of_pieces[c]->pos_p1_c] == 'e'
					)
				{
					list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p1_r, list_of_pieces[c]->pos_p1_c,
						list_of_pieces[c]->pos_p1_r + 1, list_of_pieces[c]->pos_p1_c,
						list_of_pieces[c]->pos_p1_r + 2, list_of_pieces[c]->pos_p1_c,
						list_of_pieces[c]->pos_p1_r + 3, list_of_pieces[c]->pos_p1_c);
					vertical_trigger = true;
				}
			}
		}
		else
		{
			if (list_of_pieces[c]->pos_p1_c < 7)
			{

				if (this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c+1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c+2] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c+3] == 'e'
					)
				{
					list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p1_r, list_of_pieces[c]->pos_p1_c,
						list_of_pieces[c]->pos_p1_r, list_of_pieces[c]->pos_p1_c + 1,
						list_of_pieces[c]->pos_p1_r, list_of_pieces[c]->pos_p1_c + 2,
						list_of_pieces[c]->pos_p1_r, list_of_pieces[c]->pos_p1_c + 3);
					vertical_trigger = false;
				}
			}
			else
			{
				if (this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 2] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p1_r][list_of_pieces[c]->pos_p1_c - 3] == 'e'
					)
				{
					list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p1_r, list_of_pieces[c]->pos_p1_c - 3,
						list_of_pieces[c]->pos_p1_r, list_of_pieces[c]->pos_p1_c - 2,
						list_of_pieces[c]->pos_p1_r, list_of_pieces[c]->pos_p1_c - 1,
						list_of_pieces[c]->pos_p1_r, list_of_pieces[c]->pos_p1_c);
					vertical_trigger = false;
				}
			}
		}

		//list_of_pieces[c]->type = "vertical";
	}
	else if (list_of_pieces[c]->type == "horizontaltopleft")
	{
		int topchoice = -1;
		if (list_of_pieces[c]->pos_p1_c == list_of_pieces[c]->pos_p2_c ||
			list_of_pieces[c]->pos_p1_r == list_of_pieces[c]->pos_p2_r)
			topchoice = 0;
		else if (list_of_pieces[c]->pos_p1_c == list_of_pieces[c]->pos_p3_c ||
			list_of_pieces[c]->pos_p1_r == list_of_pieces[c]->pos_p3_r
			)
			topchoice = 1;
		else if (list_of_pieces[c]->pos_p1_c == list_of_pieces[c]->pos_p4_c || 
			list_of_pieces[c]->pos_p1_r == list_of_pieces[c]->pos_p4_r
			)
			topchoice = 2;

		if (rotation_no == 0)
		{
			int x = -1;
			if (topchoice == 0)
				x = list_of_pieces[c]->pos_p3_r - 1;
			else if(topchoice==1)
				x = list_of_pieces[c]->pos_p3_r;
			else if(topchoice==2)
				x = list_of_pieces[c]->pos_p3_r + 1;

			if ( (topchoice==0 || topchoice==2) && this->grid[x][list_of_pieces[c]->pos_p3_c + 1]=='e'
				 && this->grid[list_of_pieces[c]->pos_p3_r - 1][list_of_pieces[c]->pos_p3_c]=='e'
				&& this->grid[list_of_pieces[c]->pos_p3_r + 1][list_of_pieces[c]->pos_p3_c]=='e'
				)
			{
				list_of_pieces[c]->update_pos(x, list_of_pieces[c]->pos_p3_c + 1,
					list_of_pieces[c]->pos_p3_r - 1, list_of_pieces[c]->pos_p3_c,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c,
					list_of_pieces[c]->pos_p3_r + 1, list_of_pieces[c]->pos_p3_c);
				rotation_no++;
			}
			else if (topchoice == 1 
				&& this->grid[list_of_pieces[c]->pos_p3_r + 1][list_of_pieces[c]->pos_p3_c] == 'e')
			{
				list_of_pieces[c]->update_pos(x, list_of_pieces[c]->pos_p3_c + 1,
					list_of_pieces[c]->pos_p3_r - 1, list_of_pieces[c]->pos_p3_c,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c,
					list_of_pieces[c]->pos_p3_r + 1, list_of_pieces[c]->pos_p3_c);
				rotation_no++;
			}
		}
		else if (rotation_no == 1)
		{
			int x =-1;
			if (topchoice == 0)
				x = list_of_pieces[c]->pos_p3_c + 1;
			else if (topchoice == 1)
				x = list_of_pieces[c]->pos_p3_c;
			else if (topchoice == 2)
				x = list_of_pieces[c]->pos_p3_c - 1;

			if ( (topchoice==0 || topchoice==2) && this->grid[list_of_pieces[c]->pos_p3_r + 1][x] == 'e' &&
				this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c + 1] == 'e' &&
				this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c - 1] == 'e')
			{
				list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p3_r + 1, x,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c + 1,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c - 1);
				rotation_no++;
			}
			else if (topchoice == 1 &&
				this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c - 1] == 'e')
			{
				list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p3_r + 1, x,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c + 1,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c - 1);
				rotation_no++;
			}
		}
		else if (rotation_no == 2)
		{
			int x = -1;
			if (topchoice == 0)
				x = list_of_pieces[c]->pos_p3_r + 1;
			else if (topchoice == 1)
				x = list_of_pieces[c]->pos_p3_r;
			else if (topchoice == 2)
				x = list_of_pieces[c]->pos_p3_r - 1;

			if ((topchoice==0 || topchoice==2) && this->grid[x][list_of_pieces[c]->pos_p3_c - 1] == 'e' &&
				this->grid[list_of_pieces[c]->pos_p3_r + 1][list_of_pieces[c]->pos_p3_c] == 'e' &&
				this->grid[list_of_pieces[c]->pos_p3_r - 1][list_of_pieces[c]->pos_p3_c] == 'e')
			{
				list_of_pieces[c]->update_pos(x, list_of_pieces[c]->pos_p3_c - 1,
					list_of_pieces[c]->pos_p3_r + 1, list_of_pieces[c]->pos_p3_c,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c,
					list_of_pieces[c]->pos_p3_r - 1, list_of_pieces[c]->pos_p3_c);
				rotation_no++;
			}
			else if (topchoice == 1  &&
				this->grid[list_of_pieces[c]->pos_p3_r - 1][list_of_pieces[c]->pos_p3_c] == 'e')
			{
				list_of_pieces[c]->update_pos(x, list_of_pieces[c]->pos_p3_c - 1,
					list_of_pieces[c]->pos_p3_r + 1, list_of_pieces[c]->pos_p3_c,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c,
					list_of_pieces[c]->pos_p3_r - 1, list_of_pieces[c]->pos_p3_c);
				rotation_no++;
			}
		}
		else if (rotation_no == 3)
		{
			int x = -1;
			if (topchoice == 0)
				x = list_of_pieces[c]->pos_p3_c - 1;
			else if (topchoice == 1)
				x = list_of_pieces[c]->pos_p3_c;
			else if (topchoice == 2)
				x = list_of_pieces[c]->pos_p3_c + 1;

			if ( (topchoice==0 || topchoice==2) && this->grid[list_of_pieces[c]->pos_p3_r - 1][x] == 'e' &&
				this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c - 1] == 'e' &&
				this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c + 1] == 'e')
			{
				list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p3_r - 1, x,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c - 1,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c + 1);
				rotation_no = 0;
			}
			else if (topchoice == 1  &&
				this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c + 1] == 'e')
			{
				list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p3_r - 1, x,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c - 1,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c,
					list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c + 1);
				rotation_no = 0;
			}
		}
	}
	else if (list_of_pieces[c]->type == "twoinmid")
	{
	    int top_x = -1;

		if (rotation_no == 0)
		{
			if (list_of_pieces[c]->pos_p1_r > list_of_pieces[c]->pos_p4_r)
				top_x = 0;
			else
				top_x = 1;

			if (top_x == 0)
			{
				if (this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c + 1]=='e' &&
					this->grid[list_of_pieces[c]->pos_p2_r + 1][list_of_pieces[c]->pos_p2_c + 1] == 'e')
				{
					list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p2_r - 1, list_of_pieces[c]->pos_p2_c,
						list_of_pieces[c]->pos_p2_r, list_of_pieces[c]->pos_p2_c,
						list_of_pieces[c]->pos_p2_r, list_of_pieces[c]->pos_p2_c + 1,
						list_of_pieces[c]->pos_p2_r + 1, list_of_pieces[c]->pos_p2_c + 1);
					rotation_no++;
				}
			}
			else if (top_x == 1)
			{

				if (this->grid[list_of_pieces[c]->pos_p3_r - 1][list_of_pieces[c]->pos_p3_c + 1] == 'e' &&
					this->grid[list_of_pieces[c]->pos_p3_r + 1][list_of_pieces[c]->pos_p3_c] == 'e')
				{
					list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p3_r - 1, list_of_pieces[c]->pos_p3_c + 1,
						list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c + 1,
						list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c,
						list_of_pieces[c]->pos_p3_r + 1, list_of_pieces[c]->pos_p3_c);
					rotation_no++;
				}
			}

		}
		else if (rotation_no == 1)
		{
			if (list_of_pieces[c]->pos_p1_c < list_of_pieces[c]->pos_p4_c)
				top_x = 0;
			else
				top_x = 1;

			if (top_x == 0)
			{
				if (list_of_pieces[c]->pos_p2_c-1>=0 && this->grid[list_of_pieces[c]->pos_p2_r + 1][list_of_pieces[c]->pos_p2_c]=='e'
					&& this->grid[list_of_pieces[c]->pos_p2_r + 1][list_of_pieces[c]->pos_p2_c - 1]=='e')
				{
					list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p2_r, list_of_pieces[c]->pos_p2_c + 1,
						list_of_pieces[c]->pos_p2_r, list_of_pieces[c]->pos_p2_c,
						list_of_pieces[c]->pos_p2_r + 1, list_of_pieces[c]->pos_p2_c,
						list_of_pieces[c]->pos_p2_r + 1, list_of_pieces[c]->pos_p2_c - 1);
					rotation_no++;
				}
			}
			else if (top_x == 1)
			{
				if (list_of_pieces[c]->pos_p3_c - 1 >= 0 && this->grid[list_of_pieces[c]->pos_p3_r + 1][list_of_pieces[c]->pos_p3_c + 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c - 1] == 'e')
				{
					list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p3_r + 1, list_of_pieces[c]->pos_p3_c + 1,
						list_of_pieces[c]->pos_p3_r + 1, list_of_pieces[c]->pos_p3_c,
						list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c,
						list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c - 1);
					rotation_no++;
				}
			}
		}
		else if (rotation_no == 2)
		{
			if (list_of_pieces[c]->pos_p1_r < list_of_pieces[c]->pos_p4_r)
				top_x = 0;
			else
				top_x = 1;

			if (top_x == 0)
			{
				if (this->grid[list_of_pieces[c]->pos_p2_r][list_of_pieces[c]->pos_p2_c - 1] == 'e' &&
					this->grid[list_of_pieces[c]->pos_p2_r - 1][list_of_pieces[c]->pos_p2_c - 1] == 'e')
				{
					list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p2_r + 1, list_of_pieces[c]->pos_p2_c,
						list_of_pieces[c]->pos_p2_r, list_of_pieces[c]->pos_p2_c,
						list_of_pieces[c]->pos_p2_r, list_of_pieces[c]->pos_p2_c - 1,
						list_of_pieces[c]->pos_p2_r - 1, list_of_pieces[c]->pos_p2_c - 1);
					rotation_no++;
				}
			}
			else if (top_x == 1)
			{
				if (this->grid[list_of_pieces[c]->pos_p3_r + 1][list_of_pieces[c]->pos_p3_c - 1] == 'e' &&
					this->grid[list_of_pieces[c]->pos_p3_r - 1][list_of_pieces[c]->pos_p3_c] == 'e')
				{
					list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p3_r + 1, list_of_pieces[c]->pos_p3_c - 1,
						list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c - 1,
						list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c,
						list_of_pieces[c]->pos_p3_r - 1, list_of_pieces[c]->pos_p3_c);
					rotation_no++;
				}
			}
		}
		else if (rotation_no == 3)
		{
			if (list_of_pieces[c]->pos_p1_c < list_of_pieces[c]->pos_p4_c)
				top_x = 1;
			else
				top_x = 0;

			if (top_x == 0)
			{
				if (list_of_pieces[c]->pos_p2_c + 1 < 10 && this->grid[list_of_pieces[c]->pos_p2_r - 1][list_of_pieces[c]->pos_p2_c] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p2_r - 1][list_of_pieces[c]->pos_p2_c + 1] == 'e')
				{
					list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p2_r, list_of_pieces[c]->pos_p2_c - 1,
						list_of_pieces[c]->pos_p2_r, list_of_pieces[c]->pos_p2_c,
						list_of_pieces[c]->pos_p2_r - 1, list_of_pieces[c]->pos_p2_c,
						list_of_pieces[c]->pos_p2_r - 1, list_of_pieces[c]->pos_p2_c + 1);
					rotation_no = 0;
				}
			}
			else if (top_x == 1)
			{
				if (list_of_pieces[c]->pos_p3_c + 1 < 10 && this->grid[list_of_pieces[c]->pos_p3_r - 1][list_of_pieces[c]->pos_p3_c - 1] == 'e'
					&& this->grid[list_of_pieces[c]->pos_p3_r][list_of_pieces[c]->pos_p3_c + 1] == 'e')
				{
					list_of_pieces[c]->update_pos(list_of_pieces[c]->pos_p3_r - 1, list_of_pieces[c]->pos_p3_c - 1,
						list_of_pieces[c]->pos_p3_r - 1, list_of_pieces[c]->pos_p3_c,
						list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c,
						list_of_pieces[c]->pos_p3_r, list_of_pieces[c]->pos_p3_c + 1);
					rotation_no = 0;
				}
			}
		}
	}
    
}




void game::shift_all_above_down_at(int row)
{
	for(int i = row; i > 0; i--)
	{
		for (int j = 0; j < this->cols; j++)
		{
			this->grid[i][j] = this->grid[i-1][j];
			this->grid[i - 1][j] = 'e';
		}
	}


	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			sf::Color colorf = sf::Color::Black;

			if (this->grid[i][j] == 'r')
			{
				colorf = sf::Color::Red;
			}
			else if (this->grid[i][j] == 'y')
			{
				colorf = sf::Color::Yellow;
			}
			else if (this->grid[i][j] == 'g')
			{
				colorf = sf::Color::Green;
			}
			else if (this->grid[i][j] == 'b')
			{
				colorf = sf::Color::Blue;
			}
			else if (this->grid[i][j] == 'p')
			{
				colorf = sf::Color(153, 0, 153);
			}
			else if (this->grid[i][j] == 'o')
			{
				colorf = sf::Color(255, 128, 0);
			}
			else if (this->grid[i][j] == 'P')
			{
				colorf = sf::Color(255, 0, 255);
			}

			this->colorgrid[i][j].setFillColor(colorf);
		}
	}

}

void game::check_and_burst_if(sf::RenderWindow& win, sf::Sprite& sprite)
{
	for (int i = this->rows - 1; i > 0; i--)
	{
		bool flag = true;
		for (int j = 0; j < 10; j++)
		{
			if (this->grid[i][j] == 'e')
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			for (int k = 0; k < 10; k++)
			{
				this->grid[i][k] = 'e';
				this->colorgrid[i][k].setFillColor(sf::Color::Black);
			}

			win.clear();
			win.draw(sprite);
			this->display_grid(win);
			win.display();
			Sleep(300);

			this->shift_all_above_down_at(i);

			sf::SoundBuffer buffer;
			buffer.loadFromFile("pop.wav");
				

			sf::Sound sound;
			sound.setBuffer(buffer);
			sound.setVolume(100);
			sound.setPitch(1);
			sound.play();


			win.clear();
			win.draw(sprite);
			this->display_grid(win);
			win.display();
			Sleep(300);


			i++;
		}
	}
}

bool game::can_rotate(int c)
{
	if (list_of_pieces[c]->type == "horizontaltopleft")
	{
		if (rotation_no == 0)
		{
			if (list_of_pieces[c]->pos_p2_r + 1 < this->rows)
			{
				return true;
			}
			else
				return false;
		}
	}
	return true;
}

int game::conmplete_piece_cycle(sf::RenderWindow& win,sf::Sprite& sprite)
{
	bool flag = true;
	srand(time(NULL));
	int v2 = rand() % this->component_count;
	this->list_of_pieces[v2]->create();
	int bala_choice = 0;
	int count = 0; bool inner_flag = false;
	while (flag)
	{
		sf::Event event;
		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				flag = false;
				win.close();
			}
			if(flag)
			{ 
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Up)
					{
						cout << "up pressed" << endl;
						if (this->can_rotate(v2))
						{
							this->rotate(v2);
							this->display_grid(win);
							win.display();
							Sleep(300);
						}
					}
					else if (event.key.code == sf::Keyboard::Right)
					{
						bool condition;
						if (list_of_pieces[v2]->type == "horizontal" && vertical_trigger == true)
							condition = this->check_if_can_move_right(v2, "verticalH");
						else
							condition = this->check_if_can_move_right(v2);

						if (condition)
						{
							list_of_pieces[v2]->update_pos(list_of_pieces[v2]->pos_p1_r, list_of_pieces[v2]->pos_p1_c + 1, list_of_pieces[v2]->pos_p2_r, list_of_pieces[v2]->pos_p2_c + 1
								, list_of_pieces[v2]->pos_p3_r, list_of_pieces[v2]->pos_p3_c + 1, list_of_pieces[v2]->pos_p4_r, list_of_pieces[v2]->pos_p4_c + 1);
							this->display_grid(win);
							win.display();
							Sleep(300);
						}
					}
					else if (event.key.code == sf::Keyboard::Left)
					{
						bool condition;
						if (list_of_pieces[v2]->type == "horizontal" && vertical_trigger == true)
							condition = this->check_if_can_move_left(v2, "verticalH");
						else
							condition = this->check_if_can_move_left(v2);


						if (condition)
						{
							list_of_pieces[v2]->update_pos(list_of_pieces[v2]->pos_p1_r, list_of_pieces[v2]->pos_p1_c - 1, list_of_pieces[v2]->pos_p2_r, list_of_pieces[v2]->pos_p2_c - 1
								, list_of_pieces[v2]->pos_p3_r, list_of_pieces[v2]->pos_p3_c - 1, list_of_pieces[v2]->pos_p4_r, list_of_pieces[v2]->pos_p4_c - 1);
							this->display_grid(win);
							win.display();
							Sleep(300);
						}
					}
				}
			}

		}
		if(inner_flag)
		{
			cout << "inside inner flag" << endl;

			inner_flag = false;
			if (list_of_pieces[v2]->type == "square")
			{
				if (list_of_pieces[0]->pos_p3_r + 1 < this->rows && this->grid[list_of_pieces[0]->pos_p3_r + 1][list_of_pieces[0]->pos_p3_c] == 'e'
					&& this->grid[list_of_pieces[0]->pos_p4_r + 1][list_of_pieces[0]->pos_p4_c] == 'e')
				{
					list_of_pieces[0]->update_pos(list_of_pieces[0]->pos_p1_r + 1, list_of_pieces[0]->pos_p1_c, list_of_pieces[0]->pos_p2_r + 1, list_of_pieces[0]->pos_p2_c
						, list_of_pieces[0]->pos_p3_r + 1, list_of_pieces[0]->pos_p3_c, list_of_pieces[0]->pos_p4_r + 1, list_of_pieces[0]->pos_p4_c);

					count = 0;
				}
				else
				{
					if (list_of_pieces[0]->pos_p1_r == 0)
						bala_choice = -1;
					flag = false;
				}
			}
			else if (list_of_pieces[v2]->type == "horizontal" && vertical_trigger == false)
			{
				cout << "horizontal" << endl;
				if (list_of_pieces[1]->pos_p1_r + 1 < this->rows && this->grid[list_of_pieces[1]->pos_p3_r + 1][list_of_pieces[1]->pos_p3_c] == 'e'
					&& this->grid[list_of_pieces[1]->pos_p4_r + 1][list_of_pieces[1]->pos_p4_c] == 'e'
					&& this->grid[list_of_pieces[1]->pos_p2_r + 1][list_of_pieces[1]->pos_p2_c] == 'e'
					&& this->grid[list_of_pieces[1]->pos_p1_r + 1][list_of_pieces[1]->pos_p1_c] == 'e')
				{
					list_of_pieces[1]->update_pos(list_of_pieces[1]->pos_p1_r + 1, list_of_pieces[1]->pos_p1_c, list_of_pieces[1]->pos_p2_r + 1, list_of_pieces[1]->pos_p2_c
						, list_of_pieces[1]->pos_p3_r + 1, list_of_pieces[1]->pos_p3_c, list_of_pieces[1]->pos_p4_r + 1, list_of_pieces[1]->pos_p4_c);

					count = 0;
				}
				else
				{
					if (list_of_pieces[1]->pos_p1_r == 0)
						bala_choice = -1;
					flag = false;
				}
			}
			else if (list_of_pieces[v2]->type == "horizontaltopleft")
			{
				if (rotation_no == 0)
				{
					if (list_of_pieces[2]->pos_p2_r + 1 < this->rows && this->grid[list_of_pieces[2]->pos_p3_r + 1][list_of_pieces[2]->pos_p3_c] == 'e'
						&& this->grid[list_of_pieces[2]->pos_p4_r + 1][list_of_pieces[2]->pos_p4_c] == 'e'
						&& this->grid[list_of_pieces[2]->pos_p2_r + 1][list_of_pieces[2]->pos_p2_c] == 'e'
						)
					{
						list_of_pieces[2]->update_pos(list_of_pieces[2]->pos_p1_r + 1, list_of_pieces[2]->pos_p1_c, list_of_pieces[2]->pos_p2_r + 1, list_of_pieces[2]->pos_p2_c
							, list_of_pieces[2]->pos_p3_r + 1, list_of_pieces[2]->pos_p3_c, list_of_pieces[2]->pos_p4_r + 1, list_of_pieces[2]->pos_p4_c);

						count = 0;
					}
					else
					{
						if (list_of_pieces[2]->pos_p1_r == 0)
							bala_choice = -1;
						flag = false;
						inner_flag = false;
						break;
					}
				}
				else if (rotation_no == 1)
				{
					if (list_of_pieces[2]->pos_p4_r + 1 < this->rows && this->grid[list_of_pieces[2]->pos_p4_r + 1][list_of_pieces[2]->pos_p4_c] == 'e'
						&& this->grid[list_of_pieces[2]->pos_p1_r + 1][list_of_pieces[2]->pos_p1_c] == 'e'
						)
					{
						list_of_pieces[2]->update_pos(list_of_pieces[2]->pos_p1_r + 1, list_of_pieces[2]->pos_p1_c, list_of_pieces[2]->pos_p2_r + 1, list_of_pieces[2]->pos_p2_c
							, list_of_pieces[2]->pos_p3_r + 1, list_of_pieces[2]->pos_p3_c, list_of_pieces[2]->pos_p4_r + 1, list_of_pieces[2]->pos_p4_c);

						count = 0;
					}
					else
					{
						if (list_of_pieces[2]->pos_p2_r == 0)
							bala_choice = -1;
						flag = false;
						inner_flag = false;
						break;
					}
				}
				else if (rotation_no == 2)
				{
					if (list_of_pieces[2]->pos_p1_r + 1 < this->rows && this->grid[list_of_pieces[2]->pos_p1_r + 1][list_of_pieces[2]->pos_p1_c] == 'e')
					{
						if ((this->grid[list_of_pieces[2]->pos_p4_r + 1][list_of_pieces[2]->pos_p4_c] == 'e'
							&& this->grid[list_of_pieces[2]->pos_p2_r + 1][list_of_pieces[2]->pos_p2_c] == 'e'
							&& list_of_pieces[2]->pos_p1_c == list_of_pieces[2]->pos_p3_c) ||

							(this->grid[list_of_pieces[2]->pos_p4_r + 1][list_of_pieces[2]->pos_p4_c] == 'e'
								&& this->grid[list_of_pieces[2]->pos_p3_r + 1][list_of_pieces[2]->pos_p3_c] == 'e'
								&& list_of_pieces[2]->pos_p1_c == list_of_pieces[2]->pos_p2_c) ||

								(this->grid[list_of_pieces[2]->pos_p3_r + 1][list_of_pieces[2]->pos_p3_c] == 'e'
									&& this->grid[list_of_pieces[2]->pos_p2_r + 1][list_of_pieces[2]->pos_p2_c] == 'e'
									&& list_of_pieces[2]->pos_p1_c == list_of_pieces[2]->pos_p4_c)
							)
						{
							list_of_pieces[2]->update_pos(list_of_pieces[2]->pos_p1_r + 1, list_of_pieces[2]->pos_p1_c, list_of_pieces[2]->pos_p2_r + 1, list_of_pieces[2]->pos_p2_c
								, list_of_pieces[2]->pos_p3_r + 1, list_of_pieces[2]->pos_p3_c, list_of_pieces[2]->pos_p4_r + 1, list_of_pieces[2]->pos_p4_c);

							count = 0;
						}
						else
						{
							if (list_of_pieces[2]->pos_p2_r == 0)
								bala_choice = -1;
							flag = false;
							inner_flag = false;
							break;
						}
					}
					else
					{
						if (list_of_pieces[2]->pos_p2_r == 0)
							bala_choice = -1;
						flag = false;
						inner_flag = false;
						break;
					}
				}
				else if (rotation_no == 3)
				{
					if (list_of_pieces[2]->pos_p2_r + 1 < this->rows && this->grid[list_of_pieces[2]->pos_p2_r + 1][list_of_pieces[2]->pos_p2_c] == 'e'
						&& this->grid[list_of_pieces[2]->pos_p1_r + 1][list_of_pieces[2]->pos_p1_c] == 'e'
						)
					{
						list_of_pieces[2]->update_pos(list_of_pieces[2]->pos_p1_r + 1, list_of_pieces[2]->pos_p1_c, list_of_pieces[2]->pos_p2_r + 1, list_of_pieces[2]->pos_p2_c
							, list_of_pieces[2]->pos_p3_r + 1, list_of_pieces[2]->pos_p3_c, list_of_pieces[2]->pos_p4_r + 1, list_of_pieces[2]->pos_p4_c);

						count = 0;
					}
					else
					{
						if (list_of_pieces[2]->pos_p4_r == 0)
							bala_choice = -1;
						flag = false;
						inner_flag = false;
						break;
					}
				}
			}
			else if (list_of_pieces[v2]->type == "twoinmid")
			{
				if (rotation_no == 0 || rotation_no == 2)
				{
					if (list_of_pieces[3]->pos_p1_r + 1 < this->rows && list_of_pieces[3]->pos_p4_r + 1 < this->rows
						&& this->grid[list_of_pieces[3]->pos_p4_r + 1][list_of_pieces[3]->pos_p4_c] == 'e'
						&& (this->grid[list_of_pieces[3]->pos_p3_r + 1][list_of_pieces[3]->pos_p3_c] == 'e' || this->grid[list_of_pieces[3]->pos_p2_r + 1][list_of_pieces[3]->pos_p2_c] == 'e')
						&& this->grid[list_of_pieces[3]->pos_p1_r + 1][list_of_pieces[3]->pos_p1_c] == 'e')
					{
						list_of_pieces[3]->update_pos(list_of_pieces[3]->pos_p1_r + 1, list_of_pieces[3]->pos_p1_c, list_of_pieces[3]->pos_p2_r + 1, list_of_pieces[3]->pos_p2_c
							, list_of_pieces[3]->pos_p3_r + 1, list_of_pieces[3]->pos_p3_c, list_of_pieces[3]->pos_p4_r + 1, list_of_pieces[3]->pos_p4_c);

						count = 0;
					}
					else
					{

						if (list_of_pieces[3]->pos_p1_r == 0 || list_of_pieces[3]->pos_p4_r == 0)
							bala_choice = -1;
						flag = false;

					}
				}
				else if (rotation_no == 1)
				{
					if (list_of_pieces[3]->pos_p4_r + 1 < this->rows && this->grid[list_of_pieces[3]->pos_p4_r + 1][list_of_pieces[3]->pos_p4_c] == 'e'
						&& this->grid[list_of_pieces[3]->pos_p2_r + 1][list_of_pieces[3]->pos_p2_c] == 'e')
					{
						list_of_pieces[3]->update_pos(list_of_pieces[3]->pos_p1_r + 1, list_of_pieces[3]->pos_p1_c, list_of_pieces[3]->pos_p2_r + 1, list_of_pieces[3]->pos_p2_c
							, list_of_pieces[3]->pos_p3_r + 1, list_of_pieces[3]->pos_p3_c, list_of_pieces[3]->pos_p4_r + 1, list_of_pieces[3]->pos_p4_c);

						count = 0;
					}
					else
					{
						if (list_of_pieces[3]->pos_p1_r == 0 )
							bala_choice = -1;
						flag = false;
					}
				}
				else if (rotation_no == 3)
				{
					if (list_of_pieces[3]->pos_p1_r + 1 < this->rows && this->grid[list_of_pieces[3]->pos_p1_r + 1][list_of_pieces[3]->pos_p1_c] == 'e'
						&& this->grid[list_of_pieces[3]->pos_p3_r + 1][list_of_pieces[3]->pos_p3_c] == 'e')
					{
						list_of_pieces[3]->update_pos(list_of_pieces[3]->pos_p1_r + 1, list_of_pieces[3]->pos_p1_c, list_of_pieces[3]->pos_p2_r + 1, list_of_pieces[3]->pos_p2_c
							, list_of_pieces[3]->pos_p3_r + 1, list_of_pieces[3]->pos_p3_c, list_of_pieces[3]->pos_p4_r + 1, list_of_pieces[3]->pos_p4_c);

						count = 0;
					}
					else
					{
						if (list_of_pieces[3]->pos_p4_r == 0)
							bala_choice = -1;
						flag = false;
					}
				}
			}
			else if (vertical_trigger)
			{
				cout << "here in vertical" << endl;
				if(list_of_pieces[v2]->pos_p4_r + 1 < this->rows 
					&& this->grid[list_of_pieces[v2]->pos_p4_r+1][list_of_pieces[v2]->pos_p4_c]=='e'
					)
				{
					list_of_pieces[v2]->update_pos(list_of_pieces[v2]->pos_p1_r + 1, list_of_pieces[v2]->pos_p1_c, list_of_pieces[v2]->pos_p2_r + 1, list_of_pieces[v2]->pos_p2_c
						, list_of_pieces[v2]->pos_p3_r + 1, list_of_pieces[v2]->pos_p3_c, list_of_pieces[v2]->pos_p4_r + 1, list_of_pieces[v2]->pos_p4_c);
					count = 0;
				}
				else
				{
					if (list_of_pieces[v2]->pos_p1_r == 0)
						bala_choice = -1;
					flag = false;
				}
			}
		}
		win.clear();
		win.draw(sprite);
		this->display_grid(win);
		win.display();
		Sleep(300);
		if (count == 0)
		{
			count++;
			inner_flag = true;
		}
	}
	this->vertical_trigger = false;
	this->rotation_no = 0;
	return bala_choice;
}

void game::add_character_at_pos(int r, int c,char temp)
{
	this->grid[r][c] = temp;
}

void game::remove_character_at_pos(int r, int c)
{
	this->grid[r][c] = 'e';
}

game::~game()
{
	cout << "game destructor called" << endl;
	for (int i = 0; i < this->component_count; i++)
	{
		delete list_of_pieces[i];
	}

	for (int i = 0; i < this->rows; i++)
	{
		delete[]this->grid[i];
	}
	delete[]this->grid;
}