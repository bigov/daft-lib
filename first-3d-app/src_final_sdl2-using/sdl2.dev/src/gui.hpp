/*
 * GUI header
 *
 */
#ifndef __GUI_HPP__
#define __GUI_HPP__

#include <chrono>
#include <thread>
#include "config.hpp"
#include "window.hpp"

namespace app
{
	class GUI
	{
		private:
			Conf_GUI * cfg;	// структура с конфигураций, передаваемая конструктору
			GUI(const GUI &);
			GUI operator=(const GUI &);

		public:
			GUI(Conf_GUI *);
			~GUI();
			void show(Conf_Content *);
	};
} // namespace app

#endif //__GUI_HPP__
