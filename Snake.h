#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <cstdlib>
#include <time.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include <iostream>
#include <string>

#include "Waz.h"

enum class direction { up, down, left, right };

class Snake
{		
	Waz waz;
	double FPS = 10.0;
	Punkt food;
	bool eat = 0;
	bool done;
	bool again = 0;
	bool lock = 0;
	ALLEGRO_COLOR color;
	ALLEGRO_FONT *font = nullptr;
	ALLEGRO_FONT *fontb = nullptr;
	ALLEGRO_DISPLAY* display = nullptr;


	static Snake* instance;
	Snake();
	
public:	
	static Snake* getInstance();
	static int width;
	static int height;
	static int r;
	static int move;
	static int frame;

	~Snake();

	Punkt& last() { return waz.tab[waz.size-1]; }
	Punkt& first() { return waz.tab[0]; }


	void ruch(direction);
	void nowaGra();
	void rysujPunkt(Punkt);
	void losuj();
	int gra();
};

