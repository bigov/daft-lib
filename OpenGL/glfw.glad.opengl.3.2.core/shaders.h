
static const char* vertex_shader_text =
"uniform mat4 MVP;\n"
"uniform vec2 vC2;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
//"    vPos.x = vPos.x + vC2.x;\n"
//"    vPos.y = vPos.y + vC2.y;\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

