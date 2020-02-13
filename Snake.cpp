#include "Snake.h"

int Snake::width = 400;
int Snake::height = 400;
int Snake::r = 10;
int Snake::move = 2 * r;
int Snake::frame = 20;

Snake* Snake::instance = nullptr;

Snake* Snake::getInstance()
{
	if (instance == nullptr)
		instance = new Snake();
	return instance;
}


Snake::Snake()
{
	al_init();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	color = al_map_rgb(255, 82, 150);
	font = al_load_ttf_font("calibri.ttf", 32, 0);
	fontb = al_load_ttf_font("calibri.ttf", 24, 0);
}
Snake::~Snake()
{
	al_destroy_font(font);
	al_destroy_font(fontb);
}
void Snake::losuj()
{
	start:
	food.x = (rand() % ((width - 2 * r) / move)) * move + r;
	food.y = (rand() % ((height - 2 * r) / move)) * move + r + frame;

		for (int i = 0; i < waz.size; i++)
			if (waz.tab[i] == food)
				goto start;
}

void Snake::ruch(direction dir)
{
	if(!eat)
		for (int i = waz.size - 1; i > 0; i--)
			waz.tab[i] = waz.tab[i - 1];
	else
	{
		waz.size++;
		Punkt *temp = new Punkt[waz.size];
		temp[waz.size - 1] = waz.tab[waz.size - 2];
		for (int i = 1; i < waz.size - 1; i++)
			temp[i] = waz.tab[i - 1];
		temp[0] = waz.tab[0];
		delete[] waz.tab;
		waz.tab = new Punkt[waz.size];
		for (int i = 0; i < waz.size; i++)
			waz.tab[i] = temp[i];
		delete[] temp;	

		eat = 0;
		losuj();
	}

	switch (dir)
	{
	case direction::up:
		first().y -= move;
		break;
	case direction::down:
		first().y += move;
		break;
	case direction::left:
		first().x -= move;
		break;
	case direction::right:
		first().x += move;
		break;
	}	
	
	if (first().x > width - r)
		first().x = r;
	if (first().x < r)
		first().x = width - r;
	if (first().y > height + frame - r)
		first().y = r + frame;
	if (first().y < r + frame)
		first().y = height + frame - r;

	if (first() == food)
		eat = 1;
		

	for (int i = 0; i < waz.size; i++)
		rysujPunkt(waz.tab[i]);
	rysujPunkt(food);
	std::string score = "Score: ";
	score += std::to_string(waz.size - 3);
	al_draw_text(fontb, color, width - 10, 0, ALLEGRO_ALIGN_RIGHT, score.c_str());
	al_draw_line(0, frame, width, frame, color, 2);
	al_draw_line(1, 1, width, 1, color, 2);
	al_draw_line(1, 0, 1, height + frame, color, 2);
	al_draw_line(width - 1, 0, width - 1, height + frame, color, 2);
	al_draw_line(0, height + frame - 1, width, height + frame - 1, color, 2);
	al_flip_display();

		
	for (int i = 1; i < waz.size; i++)
		if (first() == waz.tab[i] && waz.size > 3)
		{
			done = 1;
			al_rest(1);
		}
			
			
	lock = 0;
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void Snake::rysujPunkt(Punkt p)
{
	al_draw_filled_circle(p.x, p.y, r, color);
}

int Snake::gra()
{
	waz.reset();
	ALLEGRO_EVENT event;
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_TIMER* timerFPS = al_create_timer(1 / FPS);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	srand(time(0));
	losuj();
	rysujPunkt(food);
	al_flip_display();	

	al_register_event_source(queue, al_get_timer_event_source(timerFPS));
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());

	direction kierunek = direction::left;
	done = 0;
	al_start_timer(timerFPS);
	while (!done)
	{
		al_wait_for_event(queue, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			al_destroy_event_queue(queue);
			al_destroy_timer(timerFPS);
			return 1;
			done = 1;
			break;
		case ALLEGRO_EVENT_TIMER:
			ruch(kierunek);
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if (!lock)
			{
				if (kierunek != direction::down && (event.keyboard.keycode == ALLEGRO_KEY_W || event.keyboard.keycode == ALLEGRO_KEY_UP))
				{
					lock = 1;
					kierunek = direction::up;
				}
				if (kierunek != direction::up && (event.keyboard.keycode == ALLEGRO_KEY_S || event.keyboard.keycode == ALLEGRO_KEY_DOWN))
				{
					lock = 1;
					kierunek = direction::down;
				}
				if (kierunek != direction::right && (event.keyboard.keycode == ALLEGRO_KEY_A || event.keyboard.keycode == ALLEGRO_KEY_LEFT))
				{
					lock = 1;
					kierunek = direction::left;
				}
				if (kierunek != direction::left && (event.keyboard.keycode == ALLEGRO_KEY_D || event.keyboard.keycode == ALLEGRO_KEY_RIGHT))
				{
					lock = 1;
					kierunek = direction::right;
				}
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					done = 1;
				break;
			}
		default:break;
		}
	}
	std::string a = "Press space to play again";
	std::string b = "Escape to exit";
	std::string c = "Score: ";
	c += std::to_string(waz.size - 3);
	al_draw_text(font, color, width / 2, height / 2-80, ALLEGRO_ALIGN_CENTER, a.c_str());
	al_draw_text(font, color, width / 2, height / 2-40, ALLEGRO_ALIGN_CENTER, b.c_str());
	al_draw_text(font, color, width / 2, height / 2, ALLEGRO_ALIGN_CENTER, c.c_str());
	al_flip_display();

	bool over = 0;
	int zwrot = 0;
	while (!over)
	{
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_SPACE)
		{
			over = 1;
			again = 1;
		}			
		if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			over = 1;
			zwrot = 1;
		}			
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			over = 1;
			zwrot = 1;
		}		
	}
	al_destroy_event_queue(queue);
	al_destroy_timer(timerFPS);
	return zwrot;
}

void Snake::nowaGra()
{		
	ALLEGRO_EVENT event;
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	display = al_create_display(width, height + frame);

	al_draw_text(font, color, width / 2, height / 2 - 40, ALLEGRO_ALIGN_CENTER, "Press Space to play");
	al_draw_text(font, color, width / 2, height / 2, ALLEGRO_ALIGN_CENTER, "Escape to exit");
	al_flip_display();	

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());

	bool over = 0;
	while (!over)
	{
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			over = 1;
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			over = 1;
		if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_SPACE || again)
			over = gra();		
	}
	al_destroy_display(display);
	al_destroy_event_queue(queue);
}