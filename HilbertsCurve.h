#pragma once
#include <vector>
#include "Grid.h"

class HilbertsCurve
{
public:

	void Draw();
	void ScaleUpGrid(std::vector<int>& DestVec, const std::vector<int>& SrcVec, int chunkSize);
	void GenerateCurve(int XYSize);
	Grid& GetCurve();
private:

	void flipLeft(std::vector<int>::iterator start, int chunkSize, std::vector<int> vec);
	void flipRight(std::vector<int>::iterator start, int chunkSize, std::vector<int> vec);
	Grid Curve;
	int GridSize;

};
