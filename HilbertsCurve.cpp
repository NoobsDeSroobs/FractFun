#include "HilbertsCurve.h"
#include <assert.h>
#include <SDL.h>


void HilbertsCurve::GenerateCurve(int XYSize)
{
	GridSize = XYSize;
	bool isPowOf2 = (XYSize != 0) && ((XYSize & (XYSize - 1)) == 0);
	assert(isPowOf2);


	std::vector<int> tempVec = { 2, 0, 1, 3 };

	Grid NewGrid(tempVec);
	while (NewGrid.GetSideSize() < XYSize) {
		NewGrid = NewGrid.ScaleUp();
	}
	
	Curve = NewGrid;
}

Grid& HilbertsCurve::GetCurve()
{
	return Curve;
}

void HilbertsCurve::Draw() {
	size_t size = Curve.GetSideSize();
	////The image
	SDL_Window* screen = NULL;
	SDL_Renderer* renderer = NULL;
	//
	////Start SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	float CellSizePx = 800.0f / size;
	SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_SHOWN, &screen, &renderer);
	//std::vector<int> tempVec = h.GetCurve();// { 0, 4, 5, 1, 2, 3, 7, 6, 10, 11, 15, 14, 13 ,9, 8, 12};

	SDL_Event event;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	const std::vector<int>&& ToRender = std::move(Curve.GridOrder);
	SDL_PollEvent(&event);
	bool Rendered = false;
	while(event.key.keysym.sym != SDLK_ESCAPE){
		for (int i = 0; !Rendered && i < ToRender.size() - 1; ++i)
		{
			uint32_t colour = (i / (float)ToRender.size())* std::numeric_limits<uint32_t>::max();
			uint32_t r = colour >> (8*3);
			r = r & 255;
			uint32_t g = colour >> (8 * 2);
			g = g & 255;
			uint32_t b = colour >> (8 * 1);
			b = b & 255;
			uint32_t a = 255;

			SDL_SetRenderDrawColor(renderer, r, g, b, a);
			int x1 = ToRender[i] % size;
			int y1 = ToRender[i] / size;
			int x2 = ToRender[i + 1] % size;
			int y2 = ToRender[i + 1] / size;
			SDL_Delay(10);
			SDL_RenderDrawLine(renderer, (x1*CellSizePx) + CellSizePx / 2, (y1*CellSizePx) + CellSizePx / 2, (x2*CellSizePx) + CellSizePx / 2, (y2*CellSizePx) + CellSizePx / 2);
			SDL_RenderPresent(renderer);
			SDL_PollEvent(&event);
		}
		Rendered = true;
		SDL_RenderPresent(renderer);
		//Take a quick break after all that hard work
		SDL_Delay(10);
		SDL_PollEvent(&event);
	}
	//Quit SDL
	SDL_Quit();
}