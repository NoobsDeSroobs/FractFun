#include "HilbertsCurve.h"
#include <SDL.h>
#include "Grid.h"
#undef main



int main(void)
{
	HilbertsCurve h;
	h.Init();
	h.GenerateCurve(4);
	h.Draw();
	bool Run = true;
	int DrawDelay = 5;
	while (Run)
	{
		SDL_Event event;
		
		if (SDL_PollEvent(&event))
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_KP_PLUS:
				h.ScaleUpGrid();
				h.Draw(DrawDelay);
				break;

			case SDLK_KP_MINUS:
				h.ScaleDownGrid();
				h.Draw(DrawDelay);
				break;

			case SDLK_ESCAPE:
				Run = false;
				break;
			}
	}

		SDL_Delay(10);

	}
	h.CleanUp();
	return 0;
}
