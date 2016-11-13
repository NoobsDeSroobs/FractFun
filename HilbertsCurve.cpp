#include "HilbertsCurve.h"
#include <assert.h>


void HilbertsCurve::GenerateCurve(int XYSize)
{
	GridSize = XYSize;
	CurrentGrid = -1;
	bool isPowOf2 = (XYSize != 0) && ((XYSize & (XYSize - 1)) == 0);
	assert(isPowOf2);


	std::vector<int> tempVec = { 2, 0, 1, 3 };

	Grid NewGrid(tempVec);
	while (NewGrid.GetSideSize() < XYSize) {
		NewGrid = NewGrid.ScaleUp();
		Curve.push_back(NewGrid);
		CurrentGrid++;
	}
}

Grid& HilbertsCurve::GetCurve()
{
	return Curve[CurrentGrid];
}

void HilbertsCurve::Draw() {
	size_t size = Curve[CurrentGrid].GetSideSize();
	SDL_Event event;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	const std::vector<int>&& ToRender = std::move(Curve[CurrentGrid].GridOrder);
	SDL_PollEvent(&event);
	float CellSizePx = 800.0f / size;
	float ratio = std::numeric_limits<uint32_t>::max() / (float)ToRender.size();
	for (int i = 0; i < ToRender.size() - 1; ++i)
	{
		uint32_t colour = i * ratio;  ;
		uint32_t r = colour >> (8*3);
		r = r & 255;
		uint32_t g = colour >> (8 * 2);
		g = g & 255;
		uint32_t b = colour >> (8 * 1);
		b = b & 255;
		uint32_t a = 255;

		SDL_SetRenderDrawColor(renderer, 0, 255, 25, 255);
		int x1 = ToRender[i] % size;
		int y1 = ToRender[i] / size;
		int x2 = ToRender[i + 1] % size;
		int y2 = ToRender[i + 1] / size;
		SDL_RenderDrawLine(renderer, (x1*CellSizePx) + CellSizePx / 2, (y1*CellSizePx) + CellSizePx / 2, (x2*CellSizePx) + CellSizePx / 2, (y2*CellSizePx) + CellSizePx / 2);
		SDL_RenderPresent(renderer);
		SDL_PollEvent(&event);
	}
}

void HilbertsCurve::Draw(int Delay)
{
	size_t size = Curve[CurrentGrid].GetSideSize();
	SDL_Event event;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	const std::vector<int>&& ToRender = std::move(Curve[CurrentGrid].GridOrder);
	SDL_PollEvent(&event);
	float CellSizePx = 800.0f / size;
	float ratio = std::numeric_limits<uint32_t>::max() / (float)ToRender.size();
	for (int i = 0; i < ToRender.size() - 1; ++i)
	{
		uint32_t colour = i * ratio; ;
		uint32_t r = colour >> (8 * 3);
		r = r & 255;
		uint32_t g = colour >> (8 * 2);
		g = g & 255;
		uint32_t b = colour >> (8 * 1);
		b = b & 255;
		uint32_t a = 255;

		SDL_SetRenderDrawColor(renderer, 0, 255, 25, 255);
		int x1 = ToRender[i] % size;
		int y1 = ToRender[i] / size;
		int x2 = ToRender[i + 1] % size;
		int y2 = ToRender[i + 1] / size;
		SDL_Delay(Delay);
		SDL_RenderDrawLine(renderer, (x1*CellSizePx) + CellSizePx / 2, (y1*CellSizePx) + CellSizePx / 2, (x2*CellSizePx) + CellSizePx / 2, (y2*CellSizePx) + CellSizePx / 2);
		SDL_RenderPresent(renderer);
		SDL_PollEvent(&event);
	}
}

void HilbertsCurve::ScaleUpGrid()
{
	CurrentGrid++;
	if (CurrentGrid >= Curve.size())
	{
		Curve.push_back(Curve[CurrentGrid-1].ScaleUp());
	}
}

void HilbertsCurve::ScaleDownGrid() {
	if (CurrentGrid > 0)
	{
		CurrentGrid--;
	}
}

void HilbertsCurve::CleanUp()
{
	//Quit SDL
	SDL_Quit();
}

void HilbertsCurve::Init()
{

	////Start SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_SHOWN, &screen, &renderer);
}
