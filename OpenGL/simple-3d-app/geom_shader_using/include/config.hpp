//============================================================================
//
// file: config.hpp
//
// Заголовок класса управления настройками приложения
//
//============================================================================
#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include "main.hpp"

namespace tr
{
	extern glm::mat4 MatProjection;

	struct GuiParams
	{
		int w = 0;
		int h = 0;
		float aspect = 1.0f;
	};

	enum FileDestination {
		FONT,
		TEXTURE,
		VERT_SHADER,
		GEOM_SHADER,
		FRAG_SHADER,
	};

	class Config
	{
		private:
			Config(const tr::Config&);
			Config operator= (const tr::Config&);
			int value = 0;

		public:
			Config(void){};

			static GuiParams gui;
			static std::unordered_map<tr::FileDestination, std::string> fp_name;

			void load(void);
			void save(void);
			int get_value(void);
			static void set_size(int w, int h);
			static int get_w(void);
			static int get_h(void);
			static std::string filepath(tr::FileDestination);
	};
} //namespace

#endif
