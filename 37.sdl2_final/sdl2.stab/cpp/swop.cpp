#include "../hpp/swop.hpp"

namespace app {

	Interface_WE::Interface_WE() {}

	////
	// добавление клиента в список рассылки
	//
	bool Interface_WE::init(Conf_Content * options)
	{
		content.init(options);
		if(content.err.empty()) return true;
		else
		{
			err = content.err;
			return false;
		}
	}

	////
	// Отправка сообщения о событии окна
	void Interface_WE::push_e(ParamsWindow e)
	{
		content.push_params(e);
		return;
	}

	////
	// Отправка сообщения о действии пользователя
	void Interface_WE::push_a(const ActionsUser & a)
	{
		if(KEY_DOWN == a.ev)
		{
			switch(a.key)
			{
				case SDLK_SPACE:
					mov.y = 1;
					break;
				case SDLK_LSHIFT:
					mov.y = -1;
					break;
			}
		}
		if(KEY_UP == a.ev)
		{
			switch(a.key)
			{
				case SDLK_SPACE:
				case SDLK_LSHIFT:
					mov.y = 0;
					break;
			}
		}
		content.push_moving(mov);
		return;
	}

} //namespace app
