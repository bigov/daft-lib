//============================================================================
//
// file: scene.cpp
//
// Управление пространством 3D сцены
//
//============================================================================
#include "space.hpp"

namespace tr
{

	// размерность текстурной карты (8х8)
	GLubyte texture_scale = 8;
	// шаг сетки текстуры по-умолчанию = 256/8
	GLubyte tS = 32;

	// элементы 3D пространства сцены
	std::unordered_map
		< float, std::unordered_map
	 		< float, std::unordered_map
				< float, rig >>> space_map {};

//====================== FUNCTIONS ===========================================

	//### Check space 3D coordinate
	//
	// проверка существования элемента с указанными координатами
	//
	// ВНИМАНИЕ!
	// Проверка выполняется только для для одной точки в пространстве,
	// соответствующей центру занимаемого объема. Если координаты [xyz]
	// указывают на любую другую точку внутри ЗАНЯТОГО объема, то на выходе
	// всегда будет получен результат СВОБОДНО
	//
	bool space_is_empty(float x, float y, float z)
	{
		try {
			if (0 != space_map.at(x).at(y).at(z).type) { return false; }
			else // элементы == 0 соответствуют воздуху
			{
				space_map[x][y].erase(z);
				if (space_map[x][y].empty()) space_map[x].erase(y);
				if (space_map[x].empty()) space_map.erase(x);
				return false;
			}
		} catch (...) { return true; }
		return false;
	}

	// Для проверки положения персонажа (камеры) внутри блока (воды).
	// (используется для замедления движения в воде).
	//
	bool space_is_empty(glm::vec3 l)
	{
		return space_is_empty(
			static_cast<float>(round(l.x)),
			static_cast<float>(round(l.y)),
			static_cast<float>(round(l.z))
		);
	}

	////////
	// Покадровый опрос и отрисовка элементов сцены
	//
	// TODO Пока опрос не завершится - запретить изменять "space_map"
	//
	void Scene::space_array_fill(void)
	{
		if (load_complete) return;

		static auto it_x = space_map.begin();
		static auto it_y = it_x->second.begin();
		static auto it_z = it_y->second.begin();

		// Размещение элемента указанного типа в массиве прорисовки сцены
		space_place(it_x->first, it_y->first, it_z->first);

		// обход списка элементов по оси Z
		if (++it_z != it_y->second.end()) return;

		// если список по Z закончился, то берем новый Z-список из следющего Y
		if (++it_y != it_x->second.end())
		{
			it_z = it_y->second.begin();
			return;
		}

		// если Y закончился, то переключаем X и загружаем очередные списки Y и Z
		if (++it_x != space_map.end())
		{
			it_y = it_x->second.begin();
			it_z = it_y->second.begin();
			return;
		}

		load_complete = true; // по завершении установим флаг завершения обхода
		glDisable(GL_CULL_FACE); // и включим отображение обратных поверхностей

		return;
	}

	//### проверка существования такого-же элемента
	// TODO
	bool Scene::element_exist(GLfloat x, GLfloat y, GLfloat z) {
		if((x+y+z) > 0) return false;
		else return false;
	}

	//### обновление данных в GPU
	// TODO
	void Scene::element_update(GLfloat x, GLfloat y, GLfloat z)
	{
		if(element_exist(x,y,z)) return;
		else return;
	}

	//### Проверка наличия соседних элементов для расчета отображаемых граней
	float near_is_empty(const float* d, float gage)
	{
		float pX, nX, pY, nY, pZ, nZ,
		x = d[0], y = d[1], z = d[2];

		pX = space_is_empty(x + gage, y, z) ? 1.f : 0.f;
		nX = space_is_empty(x - gage, y, z) ? 1.f : 0.f;
		pY = space_is_empty(x, y + gage, z) ? 1.f : 0.f;
		nY = space_is_empty(x, y - gage, z) ? 1.f : 0.f;
		pZ = space_is_empty(x, y, z + gage) ? 1.f : 0.f;
		nZ = space_is_empty(x, y, z - gage) ? 1.f : 0.f;

		return pX + nX * 10 + pY * 100 +  nY * 1000 + pZ * 10000 + nZ * 100000;
	}

	//### добавление данных для одного элемента пространства в GPU
	//
	void Scene::element_insert(GLfloat x, GLfloat y, GLfloat z)
	{
		glBindVertexArray(vao_id);

		// заполнить VBO буферы данными элемента c указанными координатами
		float d[3] = {x,y,z};
		auto it = VBOs.begin();
    while (it != VBOs.end()) it++ ->SubData(d);
		glBindVertexArray(0);
		++count; // счетчик элементов пространства
		return;
	}

	/// удаление элемента
	/// TODO добавить реализцию функции
	void Scene::element_remove(GLfloat x, GLfloat y, GLfloat z) {
		if(element_exist(x,y,z)) return;
		else return;
	}

	//### Добавление элементов в массив отображения 3D пространства
	//
	void Scene::space_place(GLfloat x, GLfloat y, GLfloat z)
	{
		if(element_exist(x,y,z)) element_update(x, y, z);
		else element_insert(x, y, z);
		return;
	}

	//### Отображение 2D контента
	//
	void Scene::draw_hud(void)
	{
		return;
	}

	//### Вычисляет число миллисекунд от начала суток
	//
	int get_msec()
	{
		std::chrono::milliseconds ms =
			std::chrono::duration_cast< std::chrono::milliseconds >
			(std::chrono::system_clock::now().time_since_epoch());
		int k = 1000 * 60 * 60 * 24; // миллисекунд в сутках
		return static_cast<int>(ms.count() % k);
	}

	//### Начальная генерация 3D пространства
	//
	void Scene::space_generate(void)
	{
		space_map.clear();

		float s = 50.f; // число элементов пространства для отображения
		float y;
		for (float x = 0.f - s; x < s; x += 1.f)
		for (float z = 0.f - s; z < s; z += 1.f)
		{
			y = static_cast<float>(std::rand() % 2);
			space_map[x][y][z].type = 1;
			space_map[x][y][z].msec = get_msec();
		}

		space_map[0.f][3.f][0.f].type = 2;
		space_map[0.f][3.f][0.f].msec = get_msec();

		// Общее число элементов = 2s * 2s + 1
		points = static_cast<GLsizeiptr>(4 * s * s + 1);

		return;
	}

	//### Передача в VBO координат 3d точки
	//
	void _fn_c3df(const float* d, float* result)
	{
		result[0] = d[0];
		result[1] = d[1];
		result[2] = d[2];
		return;
	}

	//### тип элемента
	//
	void _fn_type(const float* d, float* result)
	{
		tr::rig p = space_map[d[0]][d[1]][d[2]];
		result[0] = static_cast<GLfloat>(p.type);
		return;
	}

	//### Масштаб
	//
	void _fn_gage(const float* d, float* result)
	{
		tr::rig p = space_map[d[0]][d[1]][d[2]];
		result[0] = static_cast<GLfloat>(p.gage);
		return;
	}

	//### активные стороны
	//
	void _fn_side(const float* d, float* result)
	{
		tr::rig p = space_map[d[0]][d[1]][d[2]];
		result[0] = near_is_empty(d, p.gage);
		return;
	}

	//### Поворот
	//
	void _fn_ramp(const float* d, float* result)
	{
		tr::rig p = space_map[d[0]][d[1]][d[2]];
		result[0] = p.x;
		result[1] = p.y;
		result[2] = p.z;
		return;
	}


	////////
	// Формирование 3D пространства
	//
	void Scene::init(void)
	{
		space_generate();

		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE); // после загрузки сцены опция выключается
	 	glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND); // поддержка прозрачности
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		prog.attach_shaders(
			tr::Config::filepath(VERT_SHADER),
			tr::Config::filepath(GEOM_SHADER),
			tr::Config::filepath(FRAG_SHADER));

		prog.use();

		// инициализация VAO
		glGenVertexArrays(1, &vao_id);
		glBindVertexArray(vao_id);

		// Создать объекты для управления VBO буферами
		VBOs.emplace_back(3, GL_FLOAT, prog.attrib_location_get("C3df"), _fn_c3df);
		VBOs.emplace_back(3, GL_FLOAT, prog.attrib_location_get("Ramp"), _fn_ramp);
		VBOs.emplace_back(1, GL_FLOAT, prog.attrib_location_get("Type"), _fn_type);
		VBOs.emplace_back(1, GL_FLOAT, prog.attrib_location_get("Side"), _fn_side);
		VBOs.emplace_back(1, GL_FLOAT, prog.attrib_location_get("Gage"), _fn_gage);

		// Выделить GPU память под VBO буферы на требуемое количество элементов
		auto it = VBOs.begin();
    while (it != VBOs.end()) it++ ->allocate_mem(points);

		glBindVertexArray(0);
		prog.unuse();

		// Загрузка из файла данных текстуры
		//pngImg texture = get_png_img(tr::Config::filepath(TEXTURE));

		GLuint m_textureObj;
		glGenTextures(1, &m_textureObj);
		glActiveTexture(GL_TEXTURE0); // можно загрузить не меньше 48
		glBindTexture(GL_TEXTURE_2D, m_textureObj);

		GLint level_of_details = 0;
		GLint frame = 0;
		glTexImage2D(GL_TEXTURE_2D, level_of_details, GL_RGBA,
			image.w, image.h,	frame, GL_RGBA, GL_UNSIGNED_BYTE, image.d);

		// Установка опций отрисовки текстур
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		return;
	}

	////////
	//	Расчет положения и направления движения камеры
	//
	void Scene::calc_position(const evInput & ev)
	{
		look_a += ev.dx * k_mouse;
		if(look_a > two_pi) look_a -= two_pi;
		if(look_a < 0) look_a += two_pi;

		look_t -= ev.dy * k_mouse;
		if(look_t > look_up) look_t = look_up;
		if(look_t < look_down) look_t = look_down;

		float _k = k_sense / static_cast<float>(ev.fps); // корректировка по FPS
		if (!space_is_empty(ViewFrom)) _k *= 0.1f;  // в воде TODO: добавить туман

		rl = _k * static_cast<float>(ev.rl);   // скорости движения
		fb = _k * static_cast<float>(ev.fb);   // по трем осям
		ud = _k * static_cast<float>(ev.ud);

		// промежуточные скаляры для ускорения расчета координат точек вида
		float
			_ca = static_cast<float>(cos(look_a)),
			_sa = static_cast<float>(sin(look_a)),
			_ct = static_cast<float>(cos(look_t));

		ViewFrom += glm::vec3(fb*_ca + rl*sin(look_a - pi), ud,	fb*_sa + rl*_ca);
		ViewTo = ViewFrom + glm::vec3(_ca*_ct, sin(look_t), _sa*_ct);

		// Расчет матрицы вида
		MatView = glm::lookAt(ViewFrom, ViewTo, upward);

		//Направление взгляда
		//lookDir = glm::vec4(glm::normalize(ViewTo - ViewFrom), 0.0f);

		return;
	}

	////////
	// Функция рендеринга, используемая в цикле окна для отрисовки сцены
	//
	void Scene::draw(const evInput & ev)
	{
		// обновление/заполнение массива по 10 объектов сцены за каждый кадр
		// TODO вынести в паралельный процесс
		if (!load_complete) for (int i = 0; i < 10; i++) space_array_fill();

		calc_position(ev);

		// Матрицу модели в расчетах не используем, так как
		// она единичная и на положение элементов влияние не оказывает
		prog.use(); 	// включить шейдерную программу
		prog.set_uniform("mvp", MatProjection * MatView);
		prog.set_uniform("ViewFrom", ViewFrom);

		glBindVertexArray(vao_id);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_POINTS, 0, count);
		glBindVertexArray(0);

		prog.unuse(); // отключить шейдерную программу
		draw_hud();

		return;
	}

} // namespace tr
