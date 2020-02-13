#pragma once
#include "Punkt.h"

class Waz
{
public:
	Punkt * tab = nullptr;
	int size = 0;

	Waz();
	~Waz();
	Waz& operator=(const Waz& src)
	{
		this->size = src.size;
		for (int i = 0; i < size; i++)
			this->tab[i] = src.tab[i];
		return *this;
	}
	void reset();

};