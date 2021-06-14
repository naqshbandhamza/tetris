#pragma once
#include "Piece.h"

class game;

class horizontal_top_left :public Piece
{
	game* ptr;
	char color;
public:
	horizontal_top_left(game* ptr, std::string type);
	void update_pos(int p1_r, int p1_c, int p2_r, int p2_c, int p3_r, int p3_c, int p4_r, int p4_c);
	void create();
	~horizontal_top_left();
};

