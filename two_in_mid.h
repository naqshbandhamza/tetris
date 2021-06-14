#pragma once
#include "Piece.h"

class game;

class two_in_mid :public Piece
{
	game* ptr;
	char color;
public:
	two_in_mid(game* ptr, std::string type);
	void update_pos(int p1_r, int p1_c, int p2_r, int p2_c, int p3_r, int p3_c, int p4_r, int p4_c);
	void create();
	~two_in_mid();
};

