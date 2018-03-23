//============================================================================
//
// file: glsl.hpp
//
// GLSL shaders program class header
//
//============================================================================
#ifndef __GLSL_HPP__
#define __GLSL_HPP__

#include "main.hpp"
#include "io.hpp"

namespace tr
{
	class Glsl
	{
		public:
			Glsl(void);
			~Glsl(void);
			void attach_shader(GLenum shader_type, 
				const std::string & file_name);
			void attach_shaders(
				const std::string & vertex_shader_filename,
				const std::string & geometric_shader_filename,
				const std::string & fragment_shader_filename
			);
			GLuint get_id(void);

			GLuint attrib_location_get(const char *);
			GLint uniform_location_get(const char *);
			void set_uniform(const char *, const glm::mat4 &);
			void set_uniform(const char *, const glm::vec3 &);
			void set_uniform(const char *, const glm::vec4 &);
			void set_uniform(const char * name, GLint u);
			void link(void);
			void use(void);
			void unuse(void);
			void validate(void);

		private:
			GLuint id = 0;
			GLint isLinked = 0;
			Glsl(const Glsl &);
			Glsl operator= (const Glsl &);

		protected:
	};
} //namespace tr
#endif
