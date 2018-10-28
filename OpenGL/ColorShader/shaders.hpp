//----------------------------------------------------------------------------
//
// file: shaders.hpp
//
// Код шейдеров для работы программы
//
//----------------------------------------------------------------------------

#define GLSL(src) "#version 330\n" #src

//### Код вершинного шейдера
const GLchar * vert_shader = GLSL(

                                  in vec3 pos;

                                  void main()
                                  {
                                      gl_Position = vec4(pos, 1.0);
                                  }
                                  );

//### Код геометрического шейдера
const GLchar * geom_shader = GLSL (

                                   layout(points) in;
                                   layout(triangle_strip, max_vertices = 26) out;
                                   uniform mat4 MVP;

                                   out vec4 fColor;
                                   flat out int enable;

                                   vec4 P = MVP * gl_in[0].gl_Position;

                                   void paint(vec4 v)
                                   {
                                       gl_Position = P + v;
                                       EmitVertex();
                                       return;
                                   };

                                   void main()
                                   {
                                       enable = 1;

                                       // координты вершин куба
                                       vec4 p0 = MVP * vec4( 0.2, -0.2,  0.2, 0.0);
                                       vec4 p1 = MVP * vec4( 0.2, -0.2, -0.2, 0.0);
                                       vec4 p2 = MVP * vec4( 0.2,  0.2, -0.2, 0.0);
                                       vec4 p3 = MVP * vec4( 0.2,  0.2,  0.2, 0.0);
                                       vec4 p4 = MVP * vec4(-0.2, -0.2,  0.2, 0.0);
                                       vec4 p5 = MVP * vec4(-0.2, -0.2, -0.2, 0.0);
                                       vec4 p6 = MVP * vec4(-0.2,  0.2, -0.2, 0.0);
                                       vec4 p7 = MVP * vec4(-0.2,  0.2,  0.2, 0.0);

                                       // для построения (одноцветного) куба порядок обхода вершин
                                       // против часовой стрелки: 0,1,3,2,6,1,5,0,4,3,7,6,4,5
                                       //     по часовой стрелке: 3,0,7,4,5,0,1,3,2,7,6,5,2,1

                                       // pX
                                       fColor = vec4(0.0, 1.0, 0.0, 0.8);
                                       paint(p0);
                                       paint(p1);
                                       paint(p3);
                                       paint(p2);

                                       // pY
                                       fColor = vec4(1.0, 0.0, 0.0, 0.8);
                                       paint(p2);
                                       paint(p6);
                                       paint(p3);
                                       paint(p7);

                                       // pZ
                                       fColor = vec4(0.0, 1.0, 1.0, 0.8);
                                       paint(p7);
                                       paint(p4);
                                       paint(p3);
                                       paint(p0);

                                       // discard
                                       enable = 0; paint(p4); enable = 1;

                                       // nY
                                       fColor = vec4(0.0, 0.0, 1.0, 0.8);
                                       paint(p4);
                                       paint(p5);
                                       paint(p0);
                                       paint(p1);

                                       // nZ
                                       fColor = vec4(1.0, 0.0, 1.0, 0.8);
                                       paint(p1);
                                       paint(p5);
                                       paint(p2);
                                       paint(p6);

                                       // nX
                                       fColor = vec4(1.0, 1.0, 0.0, 0.8);
                                       paint(p6);
                                       paint(p5);
                                       paint(p7);
                                       paint(p4);

                                       EndPrimitive();
                                   }
                                   );

//### Код фрагментного шейдера
const GLchar * frag_shader = GLSL(
                                  in vec4 fColor;
                                  flat in int enable;
                                  out vec4 outColor;

                                  void main()
                                  {
                                      //if(fColor == vec4(0.0, 0.0, 0.0, 0.0)) discard;
                                      if(enable == 0) discard;

                                      outColor = fColor;
                                  }
                                  );
