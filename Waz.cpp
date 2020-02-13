#include "Waz.h"
#include "Snake.h"
Waz::Waz()
{
	reset();
}


Waz::~Waz()
{
	if (tab != nullptr)
	{
		delete[] tab;
		size = 0;
		tab = nullptr;
	}
}

void Waz::reset()
{
	if (tab != nullptr)
	{
		delete[] tab;
		size = 0;
		tab = nullptr;
	}
	size = 3;
	tab = new Punkt[3];
	tab[0] = Punkt((Snake::width - 2 * Snake::r) / 2, (Snake::height - 2 * Snake::r) / 2 + Snake::move);
	tab[1] = Punkt(tab[0].x - Snake::move, tab[0].y);
	tab[2] = Punkt(tab[1].x - Snake::move, tab[0].y);
}