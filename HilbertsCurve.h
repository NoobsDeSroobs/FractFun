#pragma once
#include <vector>
#include "Grid.h"
#include <SDL.h>

class HilbertsCurve
{
public:

	void Draw();
	void Draw(int Delay);
	void ScaleUpGrid();
	void GenerateCurve(int XYSize);
	Grid& GetCurve();
	void ScaleDownGrid();
	void CleanUp();
	void Init();
private:
	int CurrentGrid;
	void flipLeft(std::vector<int>::iterator start, int chunkSize, std::vector<int> vec);
	void flipRight(std::vector<int>::iterator start, int chunkSize, std::vector<int> vec);
	std::vector<Grid> Curve;
	int GridSize;
	////The image
	SDL_Window* screen = NULL;
	SDL_Renderer* renderer = NULL;

};
