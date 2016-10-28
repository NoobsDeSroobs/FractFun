#pragma once
#include <vector>
#include <memory>
#include <math.h>

//This class encapsulates the idea of a grid. 
//A grid can be the entire current grid or a subgrid of another grid.
class Grid
{
	enum Position
	{
		BL = 2,
		TL = 0,
		TR = 1,
		BR = 3
	};
public:
	int GridSideSize;
	std::vector<int> GridOrder;
	void SetSubGrid(Position pos, const Grid* OldGrid);
	void AddVector(int StartPos, int EndPos, const std::vector<int>& vec, int Pos);
	Grid FlipGridLeft() const;
	Grid FlipGridRight() const;
public:
	Grid();
	Grid(int SideSize);
	Grid(std::vector<int>& vector);
	~Grid();
	int GetSideSize() const;
	int GetQuarterSideSize() const;
	std::unique_ptr<Grid*> GetQuarterGrid();

	Grid ScaleUp() const;

	int Size() const;

	Grid GetCopy();

};
