#include "HilbertsCurve.h"
#include <SDL.h>
#include "Grid.h"
#undef main



int main(void)
{

	std::vector<int> tempVec = { 2, 0, 1, 3 };
/*	{
	
		12,
		13,
		9	,
		8	,
		4	,
		0	,
		1	,
		5	,
		6	,
		2	,
		3	,
		7	,
		11,
		10,
		14,
		15
	}*/;// { 0, 4, 5, 1, 2, 3, 7, 6, 10, 11, 15, 14, 13, 9, 8, 12 };
	/*Grid test(tempVec);

	Grid flipped = test.ScaleUp();

	tempVec = std::vector<int>(flipped.GridOrder);
*/














	HilbertsCurve h;
	h.GenerateCurve(32);
	
	h.Draw();




	return 0;
}
