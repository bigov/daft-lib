/*
 * GUI header
 *
 */

#include "rigs.hpp"

namespace app
{
	class GUI
	{
		Config *cfg;
		SDL_Window *win0;
		SDL_DisplayMode displayMode;
		float *win0_ratio;
		//saving current params when switch in fullscreen mode and return back
		int *guiW, *guiH, *guiX, *guiY;

		void switch_fullscreen(void);
		void fullscreen_enable(void);
		void fullscreen_disable(void);
		void onResize(int width, int height);
		void flash_params(void);

	public:
		GUI();
		~GUI();
		void show();
	};
} // namespace app
