/*
 * GUI header
 *
 */
#ifndef _GUI_HPP_
#define _GUI_HPP_

#include <chrono>
#include <thread>
#include "config.hpp"
#include "window.hpp"

namespace app
{
	class GUI
	{
		private:
			Conf_GUI * cfg;

		public:
			GUI(Conf_GUI *) throw(Flaw);
			~GUI();
			void show(Conf_Content *) throw(Flaw);
	};
} // namespace app

#endif //_GUI_HPP_
