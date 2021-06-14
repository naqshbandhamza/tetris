#pragma once

#include <string>

class Piece
{
	friend class game;
protected:
	std::string type;
	int pos_p1_r;
	int pos_p1_c;
	int pos_p2_r;
	int pos_p2_c;
	int pos_p3_r;
	int pos_p3_c;
	int pos_p4_r;
	int pos_p4_c;
public:
	Piece();
	virtual void update_pos(int p1_r, int p1_c, int p2_r, int p2_c, int p3_r, int p3_c, int p4_r, int p4_c) = 0;
	virtual void create() = 0;
	virtual ~Piece();
};

