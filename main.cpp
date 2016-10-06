#include "HilbertsCurve.h"
#include <SDL.h>
#undef main


int main(void)
{
	HilbertsCurve h;


	size_t size = 8;
	h.GenerateCurve(size);
	//The image
	SDL_Window* screen = NULL;
	SDL_Renderer* renderer = NULL;
	
	//Start SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	float CellSizePx = 800.0f / size;
	SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_SHOWN, &screen, &renderer);
	std::vector<size_t> tempVec = h.GetCurve();// { 0, 4, 5, 1, 2, 3, 7, 6, 10, 11, 15, 14, 13 ,9, 8, 12};

	SDL_Event event;
	while (true)	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		for (int i = 0; i < tempVec.size()-1; ++i){
			int colour = (i*50) % 255;
			SDL_SetRenderDrawColor(renderer, colour, 0, 255-colour, 255);
			int x1 = tempVec[i] % size;
			int y1 = tempVec[i] / size;
			int x2 = tempVec[i+1] % size;
			int y2 = tempVec[i+1] / size;
			SDL_RenderDrawLine(renderer, (x1*CellSizePx)+ CellSizePx/2, (y1*CellSizePx) + CellSizePx/2, (x2*CellSizePx) + CellSizePx/2, (y2*CellSizePx) + CellSizePx/2);
		}
		SDL_RenderPresent(renderer);
		//Take a quick break after all that hard work
		SDL_Delay(100);
		SDL_PollEvent(&event);
		if(event.type == SDL_KEYDOWN){
			size *= 2;
			CellSizePx = 800.0f / size;
			h.GenerateCurve(size);
			tempVec = h.GetCurve();
		}
	}
	//Quit SDL
	SDL_Quit();





	return 0;
}