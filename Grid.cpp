#include "Grid.h"

Grid::Grid() {}

Grid::Grid(int SideSize)
{
	GridSideSize = SideSize;
	GridOrder = std::vector<int>(SideSize*SideSize);
}

Grid::Grid(std::vector<int>& vector)
{
	GridSideSize = sqrt(vector.size());
	GridOrder = std::vector<int>(vector);
}

Grid::~Grid() {}

int Grid::GetSideSize() const
{
	return GridSideSize;
}

int Grid::GetQuarterSideSize() const
{
	return GridSideSize / 2;
}

void Grid::AddVector(int StartPos, int EndPos, const std::vector<int>& vec, int Pos)
{
	int currNum = Pos;
	int smallSize = GetQuarterSideSize();

	int xMult = currNum % 2;
	int yMult = currNum / 2;
	int xOffset = smallSize*xMult;
	int yOffset = smallSize*yMult;

	for (int smallIndex = 0; smallIndex < vec.size(); smallIndex++)
	{
		int val = vec[smallIndex];

		int largeX = xOffset + val%smallSize;
		int largeY = yOffset + val / smallSize;
		int index = largeX + (largeY*GetSideSize());
		GridOrder[StartPos+smallIndex] = index;
	}
}

void Grid::SetSubGrid(Position pos, const Grid* OldGrid)
{
	int QuarterSideSize = OldGrid->GetSideSize();
	int SubSquareSize = QuarterSideSize*QuarterSideSize;
	int StartPos = 0;
	int EndPos = 0;
	int ctr = 0;
	Grid Flipped;
	switch (pos) {
	case Position::TL:
		StartPos = SubSquareSize*1;
		EndPos = StartPos + SubSquareSize;
		AddVector(StartPos, EndPos, OldGrid->GridOrder, Position::TL);
		break;
	case Position::TR:
		StartPos = SubSquareSize*2;
		EndPos = StartPos + SubSquareSize;
		AddVector(StartPos, EndPos, OldGrid->GridOrder, Position::TR);
		break;
	case Position::BL:
		StartPos = SubSquareSize*0;
		EndPos = StartPos + SubSquareSize;
		Flipped = OldGrid->FlipGridLeft();
		AddVector(StartPos, EndPos, Flipped.GridOrder, Position::BL);
		break;
	case Position::BR:
		StartPos = SubSquareSize * 3;
		EndPos = StartPos + SubSquareSize;
		Flipped = OldGrid->FlipGridRight();
		AddVector(StartPos, EndPos, Flipped.GridOrder, Position::BR);
		break;
	default:
		printf("Please use the enum Position found within this Grid class to specify location.");
		break;

	}
}

Grid Grid::ScaleUp() const
{
	Grid ReturnGrid(GetSideSize()*2);

	ReturnGrid.SetSubGrid(Position::BL, this);
	ReturnGrid.SetSubGrid(Position::TL, this);
	ReturnGrid.SetSubGrid(Position::TR, this);
	ReturnGrid.SetSubGrid(Position::BR, this);

	return ReturnGrid;
}

int Grid::Size() const
{
	return GridOrder.size();
}

Grid Grid::FlipGridLeft() const
{
	std::vector<int> GridArray(GridOrder);

	int SideSize = GetSideSize();

	for (int i = 0; i < GridArray.size(); i++)
	{
		int val = GridArray[i];
		int x = val % SideSize;
		int y = val / SideSize;

		int mirrorX = (SideSize - 1 - y);
		int mirrorY = (SideSize - 1 - x);
		int mirrorIndex = (mirrorY*SideSize) + mirrorX;//((chunkSize - 1 - j)*chunkSize) + (chunkSize - 1 - i);
		int j = -1;

		for (int test = i; test < GridArray.size(); ++test)
		{
			if (GridArray[test] == mirrorIndex)
			{
				j = test;
				break;
			}
		}

		if (j != -1)
		{
			int temp = GridArray[i];
			GridArray[i] = GridArray[j];
			GridArray[j] = temp;
		}else {
			j = 4;
		}
	}


	Grid ReturnGrid(GridArray);
	return ReturnGrid;
}

Grid Grid::FlipGridRight() const
{
	std::vector<int> GridArray(GridOrder);
	int SideSize = GetSideSize();
	//Flip
	for (int i = 0; i < GridArray.size(); i++)
	{
		int val = GridArray[i];
		int x = val % SideSize;
		int y = val / SideSize;

		int mirrorX = y;
		int mirrorY = x;
		int mirrorIndex = (mirrorY*SideSize) + mirrorX;


		int j = -1;
		for (int test = i; test < GridArray.size(); ++test)
		{
			if (GridArray[test] == mirrorIndex)
			{
				j = test;
				break;
			}
		}


		if (j != -1)
		{
			int temp = GridArray[i];
			GridArray[i] = GridArray[j];
			GridArray[j] = temp;
		} else
		{
			j = 4;
		}
	}


	Grid ReturnGrid(GridArray);
	return ReturnGrid;
}

Grid Grid::GetCopy()
{
	return Grid(GridOrder);
}
