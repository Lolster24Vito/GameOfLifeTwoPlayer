#include "Pattern.h"

Pattern::Pattern()
{
	bool empty[7][7] = {
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0  },
	{ 0,0,0,0,0,0,0  },
	{ 0,0,0,0,0,0,0  },
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0 },

	};
	setShape(empty);
	setName("");
}

void Pattern::Rotate()
{
}

void Pattern::setShape(bool shapee[7][7])
{
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			shape[j][i] = shapee[i][j];
		}
	}
}

void Pattern::setName(std::string name)
{
	this->name = name;
}

std::string Pattern::getName()
{
	return name;
}
