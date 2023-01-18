#define _ROWS            40 // 40
#define _COLUMNS         70 // 50
#define _SQUARESIZE      10
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600
#define _DEAD             0
#define _ALIVE            1
#define _DELAY          500



#include <iostream>
#include <fstream>
#include <string>
#include <SDL_ttf.h>
//#include "SDL_TTF.h"

using namespace std;


void save_flat_file_matriz(string  file_name, uint16_t(&matriz)[_ROWS][_COLUMNS]) {
	ofstream myfile;
	myfile.open(file_name);
	string line = "";

	for (uint16_t f = 0; f < _ROWS; f++)
	{
		for (uint16_t c = 0; c < _COLUMNS; c++)
		{
			auto str = to_string(matriz[f][c]);
			line.append(str + " ");
		}
		myfile << line + "\n";
		line = "";
	}

	myfile.close();
}

void save_info(string data) {
	ofstream myfile;
	myfile.open("data.txt", ios_base::app);
	myfile << data + "\n";
	myfile.close();
}

void init_matriz(uint16_t(&matriz)[_ROWS][_COLUMNS]) {

	for (uint16_t f = 0; f < _ROWS; f++)
	{
		for (uint16_t c = 0; c < _COLUMNS; c++)
		{
			matriz[f][c] = _DEAD;
		}
	}
}

void draw_square_filled(SDL_Renderer* m_window_renderer, uint16_t f, uint16_t c) {
	SDL_Rect rect;
	rect.x = _SQUARESIZE + c;
	rect.y = _SQUARESIZE + f;
	rect.w = _SQUARESIZE;
	rect.h = _SQUARESIZE;

	// Set the color WHITE  255,255,255 
	SDL_SetRenderDrawColor(m_window_renderer, 255, 255, 255, 255);
	// Draw Rect
	SDL_RenderDrawRect(m_window_renderer, &rect);
	// Fill Rect 
	SDL_RenderFillRect(m_window_renderer, &rect);
	SDL_RenderPresent(m_window_renderer);
}

void draw_square_black(SDL_Renderer* m_window_renderer, uint16_t f, uint16_t c) {
	SDL_Rect rect;
	rect.x = _SQUARESIZE + c;
	rect.y = _SQUARESIZE + f;
	rect.w = _SQUARESIZE;
	rect.h = _SQUARESIZE;

	// Set the color used  Black 0, 0, 0
	SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);
	// Draw Rect
	SDL_RenderDrawRect(m_window_renderer, &rect);
	// Fill Rect 
	SDL_RenderFillRect(m_window_renderer, &rect);
	//SDL_RenderPresent(m_window_renderer);
}


void draw_grid_squares(SDL_Renderer* renderer) {

	uint16_t pos = (SCREEN_WIDTH / 2) - ((_COLUMNS * _SQUARESIZE) / 2);
	for (uint16_t f = 0; f < _ROWS; f++)
	{
		for (uint16_t c = 0; c < _COLUMNS; c++)
		{
			SDL_Rect rect;

			rect.x = _SQUARESIZE + (c * _SQUARESIZE) + pos;
			rect.y = _SQUARESIZE + (f * _SQUARESIZE);
			rect.w = _SQUARESIZE;
			rect.h = _SQUARESIZE;

			// Set the color used  Black 0, 0, 0
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			// Draw Rect
			SDL_RenderDrawRect(renderer, &rect);
			SDL_RenderPresent(renderer);
		}
	}
	// update screen .. refresh

	SDL_RenderPresent(renderer);
}

void draw_grid(SDL_Renderer* renderer, uint16_t(&matriz)[_ROWS][_COLUMNS]) {

	for (uint16_t f = 0; f < _ROWS; f++)
	{
		for (uint16_t c = 0; c < _COLUMNS; c++)
		{
			if (matriz[f][c] == _ALIVE)
				draw_square_filled(renderer, f * _SQUARESIZE, c * _SQUARESIZE);
			else
				draw_square_black(renderer, f * _SQUARESIZE, c * _SQUARESIZE);
		}
	}
	// update screen .. refresh

	SDL_RenderPresent(renderer);
}

void add_oscillators_blinker(uint16_t(&matriz)[_ROWS][_COLUMNS]) {
	uint16_t rows = 5;
	uint16_t cols = 5;
	matriz[rows][cols] = _ALIVE;
	matriz[rows][(cols)+1] = _ALIVE;
	matriz[rows][(cols)+2] = _ALIVE;
}

void add_oscillators_toad(uint16_t(&matriz)[_ROWS][_COLUMNS]) {

	uint16_t rows = 10;
	uint16_t cols = 5;

	matriz[rows][cols] = _ALIVE;
	matriz[rows + 1][cols] = _ALIVE;
	matriz[rows + 2][(cols)+1] = _ALIVE;
	matriz[rows + 2][cols + 1] = _ALIVE;
	matriz[rows - 1][cols + 2] = _ALIVE;
	matriz[rows][cols + 3] = _ALIVE;
	matriz[rows + 1][cols + 3] = _ALIVE;
}

void add_oscillators_beacom(uint16_t(&matriz)[_ROWS][_COLUMNS]) {

	uint16_t rows = 15;
	uint16_t cols = 5;

	matriz[rows][cols] = _ALIVE;
	matriz[rows][cols + 1] = _ALIVE;
	matriz[rows + 1][cols] = _ALIVE;
	matriz[rows + 1][cols + 1] = _ALIVE;

	matriz[rows + 2][cols + 2] = _ALIVE;
	matriz[rows + 2][cols + 2 + 1] = _ALIVE;
	matriz[rows + 3][cols + 2] = _ALIVE;
	matriz[rows + 3][cols + 2 + 1] = _ALIVE;
}

void add_oscillators_pentadecation(uint16_t(&matriz)[_ROWS][_COLUMNS]) {

	uint16_t rows = 25;
	uint16_t cols = 7;

	for (size_t f = 0; f < 8; f++)
	{
		for (size_t c = 0; c < 3; c++)
		{
			matriz[rows + f][cols + c] = _ALIVE;
		}
	}

}


void add_spaceships_glider(uint16_t(&matriz)[_ROWS][_COLUMNS]) {
	uint16_t rows = 5;
	uint16_t cols = 15;
	// Left to Right
	matriz[rows][cols] = _ALIVE;
	matriz[rows + 1][cols + 1] = _ALIVE;
	matriz[rows + 1][(cols)+2] = _ALIVE;
	matriz[rows - 1][cols + 2] = _ALIVE;
	matriz[rows][cols + 2] = _ALIVE;
	// Right to left
	rows = 5;
	cols = _COLUMNS - 10;
	//matriz[rows][cols] = _ALIVE;
	matriz[rows][cols] = _ALIVE;
	matriz[rows + 1][cols] = _ALIVE;
	matriz[rows + 1][cols + 2] = _ALIVE;
	matriz[rows + 2][cols] = _ALIVE;
	matriz[rows + 2][cols + 1] = _ALIVE;

}


void add_spaceships_lightweight(uint16_t(&matriz)[_ROWS][_COLUMNS]) {
	uint16_t rows = 25;
	uint16_t cols = 15;

	matriz[rows + 1][cols - 1] = _ALIVE;
	matriz[rows + 3][cols - 1] = _ALIVE;
	//matriz[rows + 4][cols + 2] = _ALIVE;
	matriz[rows][cols] = _ALIVE;
	matriz[rows][cols + 1] = _ALIVE;
	matriz[rows][cols + 2] = _ALIVE;
	matriz[rows][cols + 3] = _ALIVE;
	matriz[rows + 1][cols + 3] = _ALIVE;
	matriz[rows + 2][cols + 3] = _ALIVE;
	matriz[rows + 3][cols - 1] = _ALIVE;

	matriz[rows + 3][cols + 2] = _ALIVE;
}

/// <summary>
/// Nace: Si una célula muerta tiene exactamente 3 células vecinas 
///       vivas "nace" (es decir, al turno siguiente estará viva).
/// </summary>
void alive_cell(uint16_t(&matriz)[_ROWS][_COLUMNS],
	uint16_t(&matriz_temporal)[_ROWS][_COLUMNS]) {

	uint16_t count_alive_cells = 0;

	for (uint16_t f = 0; f < _ROWS; f++)
	{
		for (uint16_t c = 0; c < _COLUMNS; c++)
		{
			// Found Alive cell
			if (matriz[f][c] == _DEAD) {

				// Count alive cells
				// Head
				count_alive_cells += matriz[f - 1][c - 1] == _ALIVE ? 1 : 0;
				count_alive_cells += matriz[f - 1][c] == _ALIVE ? 1 : 0;
				count_alive_cells += matriz[f - 1][c + 1] == _ALIVE ? 1 : 0;
				// Mid
				count_alive_cells += matriz[f][c - 1] == _ALIVE ? 1 : 0;
				count_alive_cells += matriz[f][c + 1] == _ALIVE ? 1 : 0;
				// Tail
				count_alive_cells += matriz[f + 1][c - 1] == _ALIVE ? 1 : 0;
				count_alive_cells += matriz[f + 1][c] == _ALIVE ? 1 : 0;
				count_alive_cells += matriz[f + 1][c + 1] == _ALIVE ? 1 : 0;

				if (count_alive_cells == 3) {

					matriz_temporal[f][c] = _ALIVE;
				}
				else {
					matriz_temporal[f][c] = matriz[f][c];
				}
				count_alive_cells = 0;
			}
		}
	}
}

/// <summary>
/// Muere: Una célula viva puede morir por uno de 2 casos:
///    1- Sobrepoblación: Si tiene más de tres vecinos al rededor
///    2- Aislamiento : Si tiene solo un vecino alrededor.
/// </summary>
void dead_cell(uint16_t(&matriz)[_ROWS][_COLUMNS],
	uint16_t(&matriz_temporal)[_ROWS][_COLUMNS]) {

	uint16_t count_alive_cells = 0;

	for (uint16_t f = 0; f < _ROWS; f++)
	{
		for (uint16_t c = 0; c < _COLUMNS; c++)
		{
			// 0 0 0 0 0
			// 0 1 1 1 0
			// 0 0 0 0 0

			// Found Alive cell
			if (matriz[f][c] == _ALIVE) {

				// Cound alive cells
				// Head
				count_alive_cells += matriz[f - 1][c - 1] == _ALIVE ? 1 : 0;
				count_alive_cells += matriz[f - 1][c] == _ALIVE ? 1 : 0;
				count_alive_cells += matriz[f - 1][c + 1] == _ALIVE ? 1 : 0;
				// Mid
				count_alive_cells += matriz[f][c - 1] == _ALIVE ? 1 : 0;
				count_alive_cells += matriz[f][c + 1] == _ALIVE ? 1 : 0;
				// Tail
				count_alive_cells += matriz[f + 1][c - 1] == _ALIVE ? 1 : 0;
				count_alive_cells += matriz[f + 1][c] == _ALIVE ? 1 : 0;
				count_alive_cells += matriz[f + 1][c + 1] == _ALIVE ? 1 : 0;

				/// Muere: Una célula viva puede morir por uno de 2 casos:
				///    1- Sobrepoblación: Si tiene más de tres vecinos al rededor
				///    2- Aislamiento : Si tiene solo un vecino alrededor.

				//if (count_dead_cells > 1 && count_alive_cells < 2) {
				if (count_alive_cells == 0 || count_alive_cells == 1 || count_alive_cells > 3) {
					matriz_temporal[f][c] = _DEAD;
				}
				else {
					matriz_temporal[f][c] = matriz[f][c];
				}
				count_alive_cells = 0;
			}
		}
	}

}


void update_dead_alive_matriz(uint16_t(&matriz)[_ROWS][_COLUMNS],
	uint16_t(&matriz_temporal)[_ROWS][_COLUMNS]) {

	for (size_t f = 0; f < _ROWS; f++)
	{
		for (size_t c = 0; c < _COLUMNS; c++)
		{
			matriz[f][c] = matriz_temporal[f][c];
		}
	}

}


void square_move_onscreen_loop() {

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		SDL_Window* window = SDL_CreateWindow("Square Move",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			SDL_Renderer* m_window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			//Fill the surface white
			//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(window);

			//Hack to get window to stay up
			SDL_Event e;
			bool quit = false;
			uint16_t i = 0;
			SDL_Rect old;
			old.x = -1;
			while (!quit) {

				while (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}

					/* funciona
					if (e.key.keysym.sym == SDLK_LEFT) {
						quit = true;
					}
					*/


					//if (e.type == SDLK_F1){
					if (e.key.keysym.sym == SDLK_RIGHT) {
						//if (e.type == SDL_KEYDOWN) {
							//quit = true;
							//for (size_t i = 0; i < 10; i++)
							//{
						++i;
						/* Works No 1 just clear last block
						if (old.x != -1) {
							SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);
							// Draw Rect
							SDL_RenderDrawRect(m_window_renderer, &old);
							// Fill Rect
							SDL_RenderFillRect(m_window_renderer, &old);
							//SDL_RenderPresent(m_window_renderer);
							//SDL_Delay(300);
						}
						*/


						SDL_Rect rect;
						rect.x = _SQUARESIZE + 50 + i;
						rect.y = _SQUARESIZE + 50;
						rect.w = _SQUARESIZE;
						rect.h = _SQUARESIZE;
						old = rect;


						// Works No 2
						// clean the whole screen
						SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);
						SDL_RenderClear(m_window_renderer);
						SDL_RenderPresent(m_window_renderer);
						// *******************************************

						// Set the color used  Black 0, 0, 0
						SDL_SetRenderDrawColor(m_window_renderer, 255, 255, 255, 255);
						// Draw Rect
						SDL_RenderDrawRect(m_window_renderer, &rect);
						// Fill Rect 
						SDL_RenderFillRect(m_window_renderer, &rect);

						SDL_RenderPresent(m_window_renderer);
						SDL_Delay(10);
						//}
					}
				}
			}
		}

		//Destroy window
		SDL_DestroyWindow(window);

		//Quit SDL subsystems
		SDL_Quit();
	}
}

void show_text(SDL_Renderer* render,
	TTF_Font* font,
	string text,
	uint16_t x,
	uint16_t y) {

	SDL_Color textColor = { 255, 0, 0, 0 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, textSurface);
	int text_width = textSurface->w;
	int text_height = textSurface->h;
	SDL_FreeSurface(textSurface);
	SDL_Rect renderQuad = { x, y, text_width, text_height };
	SDL_RenderCopy(render, texture, NULL, &renderQuad);

}


/// <summary>
/// Main loop
/// </summary>
void game_of_life_main_loop() {

	uint16_t matriz[_ROWS][_COLUMNS];
	uint16_t matriz_temporal[_ROWS][_COLUMNS];
	uint16_t delay = _DELAY;
	uint8_t result = 0;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	//Create window
	SDL_Window* window = SDL_CreateWindow("Game of Life Conway",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Get window surface
		screenSurface = SDL_GetWindowSurface(window);

		SDL_Renderer* m_window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		int result = SDL_Init(SDL_INIT_VIDEO);
		result = TTF_Init();
		TTF_Font* font = TTF_OpenFont("RobotoBlack.ttf", 15);

		string text = "(F1) Clean (F2) Add spaceships glider (F3) Add spaceships lightweight (F4) Add oscilators";
		string text2 = "(Key Up) Delay Increase (Key Down) Decrease ";

		show_text(m_window_renderer, font, text, 10, 480);
		show_text(m_window_renderer, font, text2, 10, 500);
		//show_text(m_window_renderer, font, text, 10, 700);

		//Hack to get window to stay up
		SDL_Event e;
		bool quit = false;

		// init/clear matriz with cero
		init_matriz(matriz);
		init_matriz(matriz_temporal);

		// draw oscillator 
		add_oscillators_pentadecation(matriz);
		add_oscillators_blinker(matriz);
		add_oscillators_toad(matriz);
		add_oscillators_beacom(matriz);
		// draw spaceships
		add_spaceships_glider(matriz);
		add_spaceships_lightweight(matriz);

		// draw grid
		draw_grid(m_window_renderer, matriz);
		SDL_Delay(delay);

		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				// Clean matris
				if (e.key.keysym.sym == SDLK_F1) {
					init_matriz(matriz);
					init_matriz(matriz_temporal);
					cout << "F1" << endl;
				}

				if (e.key.keysym.sym == SDLK_F2) {
					add_spaceships_glider(matriz);
					cout << "F2" << endl;
				}

				if (e.key.keysym.sym == SDLK_F3) {
					add_spaceships_lightweight(matriz);
					cout << "F3" << endl;
				}
				if (e.key.keysym.sym == SDLK_F4) {
					// draw oscillator 
					add_oscillators_pentadecation(matriz);
					add_oscillators_blinker(matriz);
					add_oscillators_toad(matriz);
					add_oscillators_beacom(matriz);
					cout << "F4" << endl;
				}



				if (e.key.keysym.sym == SDLK_UP) {
					delay += 100;
					cout << "Delay value (+) " << delay << endl;
				}

				if (e.key.keysym.sym == SDLK_DOWN) {

					if (delay - 100 >= 100) {
						delay = delay - 100;
						cout << "Minimal delay reached :" << delay << endl;
					}
					else
						cout << "Delay value (-) " << delay << endl;
				}


			}

			// *******************************************
			// Works ok
			alive_cell(matriz, matriz_temporal);
			dead_cell(matriz, matriz_temporal);
			update_dead_alive_matriz(matriz, matriz_temporal);
			draw_grid(m_window_renderer, matriz);

			init_matriz(matriz_temporal);
			//SDL_RenderCopy(m_window_renderer, texture, NULL, &renderQuad);

			SDL_Delay(delay);
			SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);
			// Do not use it, cause clean whole screen
			//SDL_RenderClear(m_window_renderer);
			SDL_RenderPresent(m_window_renderer);

		}

		//SDL_DestroyTexture(texture);
		SDL_FreeSurface(screenSurface);
		SDL_DestroyRenderer(m_window_renderer);
		TTF_CloseFont(font);
		TTF_Quit();

	}




	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

}

