//============================================================================
//
// file: content3d.cpp
//
// Формирование графического контента
//
//============================================================================
#include "content3d.hpp"

namespace app {

////////
// Конструктор класса
//Content3D::Content3D() {}

////////
//
// Создание шейдерной программы и начальное заполнение 3D-сцены.
//
// Сюда необходимо передать как-то ссылку на функцию для
// - подключения к серверу данных (аутентификация/авторизация)
// 		TODO: впрочем, аутентификацию и авторизацию надо проводить раньше,
// 			лучше всего наверно из функции, которая создает экземпляр
// 			локального сервера. Чтобы там была возможность вместо этого выполнить
// 			подключение к удаленному серверу.
//
// - получить список шейдеров для создания GLSL-программы
// - координаты положения камеры в пространстве
// - массив объектов в отображаемом объеме
//
bool Content3D::init(Conf_Content * shaders)
{
	cfg = shaders;
	prog = new lib::GLSLProgram();
	prog->addShader(cfg->vshader_pname->c_str());
	prog->addShader(cfg->fshader_pname->c_str());
	prog->use();
	prog->addTexture(cfg->texture_pname->c_str());

	gl::Enable(gl::BLEND);
	gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);
	gl::ClearColor(0.5f, 0.69f, 1.0f, 1.0f);
	gl::Enable(gl::DEPTH_TEST);
	gl::DepthFunc(gl::LESS);

	load_space();

	return true;
}

// Элемент пространства для отображения имеет два базовых параметра
// 		1. координаты "position"
// 		2. индекс текстуры "material_id"
// и два логических значения:
// - render: (по-умолчанию TRUE)
// - vao: устанавливается по значению из функции GLSL-программы после
// 	 генерации VAO и передачи данных в графический конвеер.
//
// 	 Если элемент удаляется из 3D пространства, то устанавливаем значение
// 	 render = FALSE, что является для GLSL программы признаком удаления
// 	 из графического буфера элемента с указанным VAO.
//
struct SpaceBit
{
	glm::vec3 position = glm::vec3(0.0f);
	short	material_id = 0.0f;
	bool render = true;
	GLuint vao = 0;
};


////////
// Начальная загрузка окружающего пространства
//
// Лучше бы это делать процессом, отделенным от обработчика пользовательского
// ввода. Но можно установить что-то вроде таймера кадров и загружать
// пространство в режиме прерывания/продолжения.
//
short Content3D::load_space()
{
	prog->debug_make_area();
	return 1;
	/*
	Cube * _c = new Cube();
	int x, z;
	for(x=0; x<2; x++)
		for(z=0; z<2; z++)
		{
			*_c = Cube((glm::vec3((float)x, 0.0f, (float)z)), 1);
			prog->pushFace4v(glm::value_ptr(_c->top.lay), glm::value_ptr(_c->top.tex));
		}
	delete _c;
	return 1;
	*/
}

////////
// Деструктор
//
Content3D::~Content3D(void)
{
	free_resources();
	return;
}

////////
//
//
void Content3D::resize_viewport(int w, int h)
{
	if(h == 0) win_aspect = 1.0;
	else win_aspect = (float)w/(float)h;
	gl::Viewport(0, 0, w, h);
	return;
}

////////
// Constracting scene viewing
//
void Content3D::make_view(glm::vec3 looking, glm::vec3 moving)
{
 	look_to = look_fr + looking + moving * speed;
	look_fr += moving * speed;

	glm::mat4 view = glm::lookAt(look_fr, look_to, upward);
	glm::mat4 projection = glm::perspective(45.0f, win_aspect, 0.1f, 50.0f);

	prog->setUniform("mvp", projection * view * model);

	return;
}

/* (render) построение изображения */
void Content3D::rendering(glm::vec3 l, glm::vec3 m)
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	prog->use();
	make_view(l, m);
	prog->draw();
	return;
}

void Content3D::free_resources(void)
{
	delete prog;
	/*
	 * TODO - проверить деструктор класса программы на наличие
	gl::DeleteBuffers(1, &vbo_cube_vertices);
	gl::DeleteBuffers(1, &vbo_cube_texcoords);
	gl::DeleteBuffers(1, &ibo_cube_elements);
	gl::DeleteTextures(1, &texture_id);
	*/

	return;
}
//////////////////
} // namespace app

