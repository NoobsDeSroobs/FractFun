#include "HilbertsCurve.h"



void HilbertsCurve::GenerateCurve(size_t XYSize)
{
	GridSize = XYSize;
	bool isPowOf2 = (XYSize != 0) && ((XYSize & (XYSize - 1)) == 0);
	
	if (!isPowOf2) {
		fprintf(stderr, "Grid size not a power of two.");
		return;
	}

	curve.resize(XYSize*XYSize);

	std::vector<size_t> tempVec = { 2, 0, 1, 3 };


	size_t currSize = 2;
	while (currSize < XYSize) {
		currSize = currSize * 2;
		//Create the new vector by appending the prior vector four times, with the required rotations.
		std::vector<size_t> CurrentGrid(currSize*currSize);
		//Add 4 copies of tempVec
		ScaleUpGrid(CurrentGrid, tempVec, currSize);
		size_t quarter = currSize/2;
		flipLeft(CurrentGrid.begin(), quarter, CurrentGrid);
		flipRight(CurrentGrid.begin()+(quarter*quarter)*3, quarter, CurrentGrid);

		tempVec = std::vector<size_t>(CurrentGrid);
	}
	
	curve = std::vector<size_t>(tempVec);
}

std::vector<size_t> HilbertsCurve::GetCurve()
{
	return curve;
}

void HilbertsCurve::flipLeft(std::vector<size_t>::iterator start, size_t chunkSize, std::vector<size_t> vec)
{
	std::vector<size_t>::iterator chunkStart = start;
	std::vector<size_t>::iterator chunkEnd = start + (chunkSize*chunkSize);

	std::vector<size_t> chunk(chunkStart, chunkEnd);
	std::vector<size_t> smallChunk(chunk.size());

	//Translate from NxN to (N/2)x(N/2)
	for (int i = 0; i < chunk.size(); ++i) {
		size_t largeIndex = chunk[i];
		int largeX = largeIndex % (chunkSize*chunkSize);
		int largeY = largeIndex / (chunkSize*chunkSize);

		int XOffset = 0;
		int YOffset = chunkSize;

		int smallX = largeX - XOffset;
		int smallY = largeY - YOffset;

		int smallIndex = smallX + (smallY*chunkSize);

		smallChunk[i] = smallIndex;
	}

	//Flip
	for (int i = 0; i < chunkSize; i++)
	{
		int val = smallChunk[i];
		int x = val % chunkSize;
		int y = val / chunkSize;

		int mirrorX = (chunkSize - 1 - y);
		int mirrorY = (chunkSize - 1 - x);
		int mirrorIndex = (mirrorY*chunkSize) + mirrorX;//((chunkSize - 1 - j)*chunkSize) + (chunkSize - 1 - i);
		int j = -1;

		for (int test = 0; test < smallChunk.size(); ++test) {
			if(smallChunk[test] == mirrorIndex) {
				j = test;
				break;
			}
		}
		
		if (j != -1)
		{
			int temp = smallChunk[i];
			smallChunk[i] = smallChunk[j];
			smallChunk[j] = temp;
		}
	}
	//Translate from (N/2)x(N/2) to NxN
	for (int i = 0; i < smallChunk.size(); ++i)
	{
		size_t smallIndex = smallChunk[i];
		int smallX = smallIndex % chunkSize;
		int smallY = smallIndex / chunkSize;

		int XOffset = 0;
		int YOffset = chunkSize;

		int largeX = smallX + XOffset;
		int largeY = smallY + YOffset;

		int largeIndex = largeX + (largeY*(chunkSize*chunkSize));

		chunk[i] = largeIndex;
	}


	std::copy(chunk.begin(), chunk.end(), start);
}

void HilbertsCurve::flipRight(std::vector<size_t>::iterator start, size_t chunkSize, std::vector<size_t> vec)
{

	std::vector<size_t>::iterator chunkStart = start;
	std::vector<size_t>::iterator chunkEnd = start + (chunkSize*chunkSize);

	std::vector<size_t> chunk(chunkStart, chunkEnd);
	std::vector<size_t> smallChunk(chunk.size());

	//Translate from NxN to (N/2)x(N/2)
	for (int i = 0; i < chunk.size(); ++i)
	{
		size_t largeIndex = chunk[i];
		int largeX = largeIndex % (chunkSize*chunkSize);
		int largeY = largeIndex / (chunkSize*chunkSize);

		int XOffset = chunkSize;
		int YOffset = chunkSize;

		int smallX = largeX - XOffset;
		int smallY = largeY - YOffset;

		int smallIndex = smallX + (smallY*chunkSize);

		smallChunk[i] = smallIndex;
	}

	//Flip
	for (int i = 0; i < chunkSize; i++)
	{
		int val = smallChunk[i];
		int x = val % chunkSize;
		int y = val / chunkSize;

		int mirrorX = y;
		int mirrorY = x;
		int mirrorIndex = (mirrorY*chunkSize) + mirrorX;//((chunkSize - 1 - j)*chunkSize) + (chunkSize - 1 - i);
		
		
		int j = -1;
		for (int test = 0; test < smallChunk.size(); ++test)
		{
			if (smallChunk[test] == mirrorIndex)
			{
				j = test;
				break;
			}
		}


		if (j != -1)
		{
			int temp = smallChunk[i];
			smallChunk[i] = smallChunk[j];
			smallChunk[j] = temp;
		}
	}
	//Translate from (N/2)x(N/2) to NxN
	for (int i = 0; i < smallChunk.size(); ++i)
	{
		size_t smallIndex = smallChunk[i];
		int smallX = smallIndex % chunkSize;
		int smallY = smallIndex / chunkSize;

		int XOffset = chunkSize;
		int YOffset = chunkSize;

		int largeX = smallX + XOffset;
		int largeY = smallY + YOffset;

		int largeIndex = largeX + (largeY*(chunkSize*chunkSize));

		chunk[i] = largeIndex;
	}
	

	std::copy(chunk.begin(), chunk.end(), start);




	//std::vector<size_t>::iterator chunkStart = start;
	//std::vector<size_t>::iterator chunkEnd = start + (chunkSize*chunkSize);

	//std::vector<size_t> chunk(chunkStart, chunkEnd);
	//std::vector<size_t> smallChunk(chunk.size());

	////Translate from NxN to (N/2)x(N/2)
	//for (int i = 0; i < chunk.size(); ++i)
	//{
	//	size_t largeIndex = chunk[i];
	//	int largeX = largeIndex % (chunkSize*chunkSize);
	//	int largeY = largeIndex / (chunkSize*chunkSize);

	//	int XOffset = 0;
	//	int YOffset = chunkSize;

	//	int smallX = largeX - XOffset;
	//	int smallY = largeY - YOffset;

	//	int smallIndex = smallX + (smallY*chunkSize);

	//	smallChunk[i] = smallIndex;
	//}

	//std::vector<size_t> smallChunkFlipped(chunk.size());
	////Flip
	//for (int i = 0; i < smallChunkFlipped.size(); ++i)
	//{
	//	int x = i % chunkSize;
	//	int y = i / chunkSize;

	//	int t = chunkSize - 1 - x;
	//	x = chunkSize - 1 - y;
	//	y = t;

	//	int flippedIndex = y + (x*chunkSize);
	//	smallChunkFlipped[flippedIndex] = smallChunk[i];
	//}

	////Translate from (N/2)x(N/2) to NxN
	//for (int i = 0; i < smallChunkFlipped.size(); ++i)
	//{
	//	size_t smallIndex = smallChunkFlipped[i];
	//	int smallX = smallIndex % chunkSize;
	//	int smallY = smallIndex / chunkSize;

	//	int XOffset = 0;
	//	int YOffset = chunkSize;

	//	int largeX = smallX + XOffset;
	//	int largeY = smallY + YOffset;

	//	int largeIndex = largeX + (largeY*(chunkSize*chunkSize));

	//	chunk[i] = largeIndex;
	//}


	//std::copy(chunk.begin(), chunk.end(), start);
}

void HilbertsCurve::Draw()
{

}

void HilbertsCurve::ScaleUpGrid(std::vector<size_t>& DestVec, const std::vector<size_t>& SrcVec, size_t largeSize)
{
	int ctr = 0;
	int order[] = {2, 0, 1, 3};
	for (int i = 0; i < 4; ++i)
	{
		int currNum = order[i];
		int smallSize = largeSize/2;

		int xMult = currNum % 2;
		int yMult = currNum / 2;
		int xOffset = smallSize*xMult;
		int yOffset = smallSize*yMult;

		for (int smallIndex = 0; smallIndex < SrcVec.size(); smallIndex++)
		{
			size_t val = SrcVec[smallIndex];
						
			int largeX = xOffset + val%smallSize;
			int largeY = yOffset + val / smallSize;
			int index = largeX + (largeY*largeSize);
			DestVec[ctr] = index;
			ctr++;
		}
	}

	for (int i = 0; i < 4; ++i) {
		
	}

}
