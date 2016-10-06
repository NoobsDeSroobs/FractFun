#pragma once
#include <vector>

class HilbertsCurve
{
public:

	void Draw();
	void ScaleUpGrid(std::vector<size_t>& DestVec, const std::vector<size_t>& SrcVec, size_t chunkSize);
	void GenerateCurve(size_t XYSize);
	std::vector<size_t> GetCurve();
private:

	void flipLeft(std::vector<size_t>::iterator start, size_t chunkSize, std::vector<size_t> vec);
	void flipRight(std::vector<size_t>::iterator start, size_t chunkSize, std::vector<size_t> vec);
	std::vector<size_t> curve;
	size_t GridSize;

};