#ifndef FUNCTION_CPP_GENERATED_HEADEROPENGL_HPP
#define FUNCTION_CPP_GENERATED_HEADEROPENGL_HPP

#if defined(__glew_h__) || defined(__GLEW_H__)
#error Attempt to include auto-generated header after including glew.h
#endif
#if defined(__gl_h_) || defined(__GL_H__)
#error Attempt to include auto-generated header after including gl.h
#endif
#if defined(__glext_h_) || defined(__GLEXT_H_)
#error Attempt to include auto-generated header after including glext.h
#endif
#if defined(__gltypes_h_)
#error Attempt to include auto-generated header after gltypes.h
#endif
#if defined(__gl_ATI_h_)
#error Attempt to include auto-generated header after including glATI.h
#endif

#define __glew_h__
#define __GLEW_H__
#define __gl_h_
#define __GL_H__
#define __glext_h_
#define __GLEXT_H_
#define __gltypes_h_
#define __gl_ATI_h_

#ifndef APIENTRY
	#if defined(__MINGW32__)
		#ifndef WIN32_LEAN_AND_MEAN
			#define WIN32_LEAN_AND_MEAN 1
		#endif
		#ifndef NOMINMAX
			#define NOMINMAX
		#endif
		#include <windows.h>
	#elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
		#ifndef WIN32_LEAN_AND_MEAN
			#define WIN32_LEAN_AND_MEAN 1
		#endif
		#ifndef NOMINMAX
			#define NOMINMAX
		#endif
		#include <windows.h>
	#else
		#define APIENTRY
	#endif
#endif /*APIENTRY*/

#ifndef CODEGEN_FUNCPTR
	#define CODEGEN_REMOVE_FUNCPTR
	#if defined(_WIN32)
		#define CODEGEN_FUNCPTR APIENTRY
	#else
		#define CODEGEN_FUNCPTR
	#endif
#endif /*CODEGEN_FUNCPTR*/

#ifndef GLAPI
	#define GLAPI extern
#endif


#ifndef GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS
#define GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS


#endif /*GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS*/

#include <stddef.h>
#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GL_EXT_timer_query extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif
	typedef unsigned int GLenum;
	typedef unsigned char GLboolean;
	typedef unsigned int GLbitfield;
	typedef void GLvoid;
	typedef signed char GLbyte;
	typedef short GLshort;
	typedef int GLint;
	typedef unsigned char GLubyte;
	typedef unsigned short GLushort;
	typedef unsigned int GLuint;
	typedef int GLsizei;
	typedef float GLfloat;
	typedef float GLclampf;
	typedef double GLdouble;
	typedef double GLclampd;
	typedef char GLchar;
	typedef char GLcharARB;
	#ifdef __APPLE__
typedef void *GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif
		typedef unsigned short GLhalfARB;
		typedef unsigned short GLhalf;
		typedef GLint GLfixed;
		typedef ptrdiff_t GLintptr;
		typedef ptrdiff_t GLsizeiptr;
		typedef int64_t GLint64;
		typedef uint64_t GLuint64;
		typedef ptrdiff_t GLintptrARB;
		typedef ptrdiff_t GLsizeiptrARB;
		typedef int64_t GLint64EXT;
		typedef uint64_t GLuint64EXT;
		typedef struct __GLsync *GLsync;
		struct _cl_context;
		struct _cl_event;
		typedef void (APIENTRY *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
		typedef void (APIENTRY *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
		typedef void (APIENTRY *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
		typedef unsigned short GLhalfNV;
		typedef GLintptr GLvdpauSurfaceNV;

namespace gl
{
	namespace exts
	{
		class LoadTest
		{
		private:
			//Safe bool idiom. Joy!
			typedef void (LoadTest::*bool_type)() const;
			void big_long_name_that_really_doesnt_matter() const {}
			
		public:
			operator bool_type() const
			{
				return m_isLoaded ? &LoadTest::big_long_name_that_really_doesnt_matter : 0;
			}
			
			int GetNumMissing() const {return m_numMissing;}
			
			LoadTest() : m_isLoaded(false), m_numMissing(0) {}
			LoadTest(bool isLoaded, int numMissing) : m_isLoaded(isLoaded), m_numMissing(numMissing) {}
		private:
			bool m_isLoaded;
			int m_numMissing;
		};
		
	} //namespace exts
	enum
	{
		_2D                              = 0x0600,
		_2_BYTES                         = 0x1407,
		_3D                              = 0x0601,
		_3D_COLOR                        = 0x0602,
		_3D_COLOR_TEXTURE                = 0x0603,
		_3_BYTES                         = 0x1408,
		_4D_COLOR_TEXTURE                = 0x0604,
		_4_BYTES                         = 0x1409,
		ACCUM                            = 0x0100,
		ACCUM_ALPHA_BITS                 = 0x0D5B,
		ACCUM_BLUE_BITS                  = 0x0D5A,
		ACCUM_BUFFER_BIT                 = 0x00000200,
		ACCUM_CLEAR_VALUE                = 0x0B80,
		ACCUM_GREEN_BITS                 = 0x0D59,
		ACCUM_RED_BITS                   = 0x0D58,
		ADD                              = 0x0104,
		ALL_ATTRIB_BITS                  = 0xFFFFFFFF,
		ALPHA                            = 0x1906,
		ALPHA12                          = 0x803D,
		ALPHA16                          = 0x803E,
		ALPHA4                           = 0x803B,
		ALPHA8                           = 0x803C,
		ALPHA_BIAS                       = 0x0D1D,
		ALPHA_BITS                       = 0x0D55,
		ALPHA_SCALE                      = 0x0D1C,
		ALPHA_TEST                       = 0x0BC0,
		ALPHA_TEST_FUNC                  = 0x0BC1,
		ALPHA_TEST_REF                   = 0x0BC2,
		ALWAYS                           = 0x0207,
		AMBIENT                          = 0x1200,
		AMBIENT_AND_DIFFUSE              = 0x1602,
		AND                              = 0x1501,
		AND_INVERTED                     = 0x1504,
		AND_REVERSE                      = 0x1502,
		ATTRIB_STACK_DEPTH               = 0x0BB0,
		AUTO_NORMAL                      = 0x0D80,
		AUX0                             = 0x0409,
		AUX1                             = 0x040A,
		AUX2                             = 0x040B,
		AUX3                             = 0x040C,
		AUX_BUFFERS                      = 0x0C00,
		BACK                             = 0x0405,
		BACK_LEFT                        = 0x0402,
		BACK_RIGHT                       = 0x0403,
		BITMAP                           = 0x1A00,
		BITMAP_TOKEN                     = 0x0704,
		BLEND                            = 0x0BE2,
		BLEND_DST                        = 0x0BE0,
		BLEND_SRC                        = 0x0BE1,
		BLUE                             = 0x1905,
		BLUE_BIAS                        = 0x0D1B,
		BLUE_BITS                        = 0x0D54,
		BLUE_SCALE                       = 0x0D1A,
		BYTE                             = 0x1400,
		C3F_V3F                          = 0x2A24,
		C4F_N3F_V3F                      = 0x2A26,
		C4UB_V2F                         = 0x2A22,
		C4UB_V3F                         = 0x2A23,
		CCW                              = 0x0901,
		CLAMP                            = 0x2900,
		CLEAR                            = 0x1500,
		CLIENT_ALL_ATTRIB_BITS           = 0xFFFFFFFF,
		CLIENT_ATTRIB_STACK_DEPTH        = 0x0BB1,
		CLIENT_PIXEL_STORE_BIT           = 0x00000001,
		CLIENT_VERTEX_ARRAY_BIT          = 0x00000002,
		CLIP_PLANE0                      = 0x3000,
		CLIP_PLANE1                      = 0x3001,
		CLIP_PLANE2                      = 0x3002,
		CLIP_PLANE3                      = 0x3003,
		CLIP_PLANE4                      = 0x3004,
		CLIP_PLANE5                      = 0x3005,
		COEFF                            = 0x0A00,
		COLOR                            = 0x1800,
		COLOR_ARRAY                      = 0x8076,
		COLOR_ARRAY_POINTER              = 0x8090,
		COLOR_ARRAY_SIZE                 = 0x8081,
		COLOR_ARRAY_STRIDE               = 0x8083,
		COLOR_ARRAY_TYPE                 = 0x8082,
		COLOR_BUFFER_BIT                 = 0x00004000,
		COLOR_CLEAR_VALUE                = 0x0C22,
		COLOR_INDEX                      = 0x1900,
		COLOR_INDEXES                    = 0x1603,
		COLOR_LOGIC_OP                   = 0x0BF2,
		COLOR_MATERIAL                   = 0x0B57,
		COLOR_MATERIAL_FACE              = 0x0B55,
		COLOR_MATERIAL_PARAMETER         = 0x0B56,
		COLOR_WRITEMASK                  = 0x0C23,
		COMPILE                          = 0x1300,
		COMPILE_AND_EXECUTE              = 0x1301,
		CONSTANT_ATTENUATION             = 0x1207,
		COPY                             = 0x1503,
		COPY_INVERTED                    = 0x150C,
		COPY_PIXEL_TOKEN                 = 0x0706,
		CULL_FACE                        = 0x0B44,
		CULL_FACE_MODE                   = 0x0B45,
		CURRENT_BIT                      = 0x00000001,
		CURRENT_COLOR                    = 0x0B00,
		CURRENT_INDEX                    = 0x0B01,
		CURRENT_NORMAL                   = 0x0B02,
		CURRENT_RASTER_COLOR             = 0x0B04,
		CURRENT_RASTER_DISTANCE          = 0x0B09,
		CURRENT_RASTER_INDEX             = 0x0B05,
		CURRENT_RASTER_POSITION          = 0x0B07,
		CURRENT_RASTER_POSITION_VALID    = 0x0B08,
		CURRENT_RASTER_TEXTURE_COORDS    = 0x0B06,
		CURRENT_TEXTURE_COORDS           = 0x0B03,
		CW                               = 0x0900,
		DECAL                            = 0x2101,
		DECR                             = 0x1E03,
		DEPTH                            = 0x1801,
		DEPTH_BIAS                       = 0x0D1F,
		DEPTH_BITS                       = 0x0D56,
		DEPTH_BUFFER_BIT                 = 0x00000100,
		DEPTH_CLEAR_VALUE                = 0x0B73,
		DEPTH_COMPONENT                  = 0x1902,
		DEPTH_FUNC                       = 0x0B74,
		DEPTH_RANGE                      = 0x0B70,
		DEPTH_SCALE                      = 0x0D1E,
		DEPTH_TEST                       = 0x0B71,
		DEPTH_WRITEMASK                  = 0x0B72,
		DIFFUSE                          = 0x1201,
		DITHER                           = 0x0BD0,
		DOMAIN_                          = 0x0A02,
		DONT_CARE                        = 0x1100,
		DOUBLE                           = 0x140A,
		DOUBLEBUFFER                     = 0x0C32,
		DRAW_BUFFER                      = 0x0C01,
		DRAW_PIXEL_TOKEN                 = 0x0705,
		DST_ALPHA                        = 0x0304,
		DST_COLOR                        = 0x0306,
		EDGE_FLAG                        = 0x0B43,
		EDGE_FLAG_ARRAY                  = 0x8079,
		EDGE_FLAG_ARRAY_POINTER          = 0x8093,
		EDGE_FLAG_ARRAY_STRIDE           = 0x808C,
		EMISSION                         = 0x1600,
		ENABLE_BIT                       = 0x00002000,
		EQUAL                            = 0x0202,
		EQUIV                            = 0x1509,
		EVAL_BIT                         = 0x00010000,
		EXP                              = 0x0800,
		EXP2                             = 0x0801,
		EXTENSIONS                       = 0x1F03,
		EYE_LINEAR                       = 0x2400,
		EYE_PLANE                        = 0x2502,
		FALSE_                           = 0,
		FASTEST                          = 0x1101,
		FEEDBACK                         = 0x1C01,
		FEEDBACK_BUFFER_POINTER          = 0x0DF0,
		FEEDBACK_BUFFER_SIZE             = 0x0DF1,
		FEEDBACK_BUFFER_TYPE             = 0x0DF2,
		FILL                             = 0x1B02,
		FLAT                             = 0x1D00,
		FLOAT                            = 0x1406,
		FOG                              = 0x0B60,
		FOG_BIT                          = 0x00000080,
		FOG_COLOR                        = 0x0B66,
		FOG_DENSITY                      = 0x0B62,
		FOG_END                          = 0x0B64,
		FOG_HINT                         = 0x0C54,
		FOG_INDEX                        = 0x0B61,
		FOG_MODE                         = 0x0B65,
		FOG_START                        = 0x0B63,
		FRONT                            = 0x0404,
		FRONT_AND_BACK                   = 0x0408,
		FRONT_FACE                       = 0x0B46,
		FRONT_LEFT                       = 0x0400,
		FRONT_RIGHT                      = 0x0401,
		GEQUAL                           = 0x0206,
		GREATER                          = 0x0204,
		GREEN                            = 0x1904,
		GREEN_BIAS                       = 0x0D19,
		GREEN_BITS                       = 0x0D53,
		GREEN_SCALE                      = 0x0D18,
		HINT_BIT                         = 0x00008000,
		INCR                             = 0x1E02,
		INDEX_ARRAY                      = 0x8077,
		INDEX_ARRAY_POINTER              = 0x8091,
		INDEX_ARRAY_STRIDE               = 0x8086,
		INDEX_ARRAY_TYPE                 = 0x8085,
		INDEX_BITS                       = 0x0D51,
		INDEX_CLEAR_VALUE                = 0x0C20,
		INDEX_LOGIC_OP                   = 0x0BF1,
		INDEX_MODE                       = 0x0C30,
		INDEX_OFFSET                     = 0x0D13,
		INDEX_SHIFT                      = 0x0D12,
		INDEX_WRITEMASK                  = 0x0C21,
		INT                              = 0x1404,
		INTENSITY                        = 0x8049,
		INTENSITY12                      = 0x804C,
		INTENSITY16                      = 0x804D,
		INTENSITY4                       = 0x804A,
		INTENSITY8                       = 0x804B,
		INVALID_ENUM                     = 0x0500,
		INVALID_OPERATION                = 0x0502,
		INVALID_VALUE                    = 0x0501,
		INVERT                           = 0x150A,
		KEEP                             = 0x1E00,
		LEFT                             = 0x0406,
		LEQUAL                           = 0x0203,
		LESS                             = 0x0201,
		LIGHT0                           = 0x4000,
		LIGHT1                           = 0x4001,
		LIGHT2                           = 0x4002,
		LIGHT3                           = 0x4003,
		LIGHT4                           = 0x4004,
		LIGHT5                           = 0x4005,
		LIGHT6                           = 0x4006,
		LIGHT7                           = 0x4007,
		LIGHTING                         = 0x0B50,
		LIGHTING_BIT                     = 0x00000040,
		LIGHT_MODEL_AMBIENT              = 0x0B53,
		LIGHT_MODEL_LOCAL_VIEWER         = 0x0B51,
		LIGHT_MODEL_TWO_SIDE             = 0x0B52,
		LINE                             = 0x1B01,
		LINEAR                           = 0x2601,
		LINEAR_ATTENUATION               = 0x1208,
		LINEAR_MIPMAP_LINEAR             = 0x2703,
		LINEAR_MIPMAP_NEAREST            = 0x2701,
		LINES                            = 0x0001,
		LINE_BIT                         = 0x00000004,
		LINE_LOOP                        = 0x0002,
		LINE_RESET_TOKEN                 = 0x0707,
		LINE_SMOOTH                      = 0x0B20,
		LINE_SMOOTH_HINT                 = 0x0C52,
		LINE_STIPPLE                     = 0x0B24,
		LINE_STIPPLE_PATTERN             = 0x0B25,
		LINE_STIPPLE_REPEAT              = 0x0B26,
		LINE_STRIP                       = 0x0003,
		LINE_TOKEN                       = 0x0702,
		LINE_WIDTH                       = 0x0B21,
		LINE_WIDTH_GRANULARITY           = 0x0B23,
		LINE_WIDTH_RANGE                 = 0x0B22,
		LIST_BASE                        = 0x0B32,
		LIST_BIT                         = 0x00020000,
		LIST_INDEX                       = 0x0B33,
		LIST_MODE                        = 0x0B30,
		LOAD                             = 0x0101,
		LOGIC_OP                         = 0x0BF1,
		LOGIC_OP_MODE                    = 0x0BF0,
		LUMINANCE                        = 0x1909,
		LUMINANCE12                      = 0x8041,
		LUMINANCE12_ALPHA12              = 0x8047,
		LUMINANCE12_ALPHA4               = 0x8046,
		LUMINANCE16                      = 0x8042,
		LUMINANCE16_ALPHA16              = 0x8048,
		LUMINANCE4                       = 0x803F,
		LUMINANCE4_ALPHA4                = 0x8043,
		LUMINANCE6_ALPHA2                = 0x8044,
		LUMINANCE8                       = 0x8040,
		LUMINANCE8_ALPHA8                = 0x8045,
		LUMINANCE_ALPHA                  = 0x190A,
		MAP1_COLOR_4                     = 0x0D90,
		MAP1_GRID_DOMAIN                 = 0x0DD0,
		MAP1_GRID_SEGMENTS               = 0x0DD1,
		MAP1_INDEX                       = 0x0D91,
		MAP1_NORMAL                      = 0x0D92,
		MAP1_TEXTURE_COORD_1             = 0x0D93,
		MAP1_TEXTURE_COORD_2             = 0x0D94,
		MAP1_TEXTURE_COORD_3             = 0x0D95,
		MAP1_TEXTURE_COORD_4             = 0x0D96,
		MAP1_VERTEX_3                    = 0x0D97,
		MAP1_VERTEX_4                    = 0x0D98,
		MAP2_COLOR_4                     = 0x0DB0,
		MAP2_GRID_DOMAIN                 = 0x0DD2,
		MAP2_GRID_SEGMENTS               = 0x0DD3,
		MAP2_INDEX                       = 0x0DB1,
		MAP2_NORMAL                      = 0x0DB2,
		MAP2_TEXTURE_COORD_1             = 0x0DB3,
		MAP2_TEXTURE_COORD_2             = 0x0DB4,
		MAP2_TEXTURE_COORD_3             = 0x0DB5,
		MAP2_TEXTURE_COORD_4             = 0x0DB6,
		MAP2_VERTEX_3                    = 0x0DB7,
		MAP2_VERTEX_4                    = 0x0DB8,
		MAP_COLOR                        = 0x0D10,
		MAP_STENCIL                      = 0x0D11,
		MATRIX_MODE                      = 0x0BA0,
		MAX_ATTRIB_STACK_DEPTH           = 0x0D35,
		MAX_CLIENT_ATTRIB_STACK_DEPTH    = 0x0D3B,
		MAX_CLIP_PLANES                  = 0x0D32,
		MAX_EVAL_ORDER                   = 0x0D30,
		MAX_LIGHTS                       = 0x0D31,
		MAX_LIST_NESTING                 = 0x0B31,
		MAX_MODELVIEW_STACK_DEPTH        = 0x0D36,
		MAX_NAME_STACK_DEPTH             = 0x0D37,
		MAX_PIXEL_MAP_TABLE              = 0x0D34,
		MAX_PROJECTION_STACK_DEPTH       = 0x0D38,
		MAX_TEXTURE_SIZE                 = 0x0D33,
		MAX_TEXTURE_STACK_DEPTH          = 0x0D39,
		MAX_VIEWPORT_DIMS                = 0x0D3A,
		MODELVIEW                        = 0x1700,
		MODELVIEW_MATRIX                 = 0x0BA6,
		MODELVIEW_STACK_DEPTH            = 0x0BA3,
		MODULATE                         = 0x2100,
		MULT                             = 0x0103,
		N3F_V3F                          = 0x2A25,
		NAME_STACK_DEPTH                 = 0x0D70,
		NAND                             = 0x150E,
		NEAREST                          = 0x2600,
		NEAREST_MIPMAP_LINEAR            = 0x2702,
		NEAREST_MIPMAP_NEAREST           = 0x2700,
		NEVER                            = 0x0200,
		NICEST                           = 0x1102,
		NONE                             = 0,
		NOOP                             = 0x1505,
		NOR                              = 0x1508,
		NORMALIZE                        = 0x0BA1,
		NORMAL_ARRAY                     = 0x8075,
		NORMAL_ARRAY_POINTER             = 0x808F,
		NORMAL_ARRAY_STRIDE              = 0x807F,
		NORMAL_ARRAY_TYPE                = 0x807E,
		NOTEQUAL                         = 0x0205,
		NO_ERROR_                        = 0,
		OBJECT_LINEAR                    = 0x2401,
		OBJECT_PLANE                     = 0x2501,
		ONE                              = 1,
		ONE_MINUS_DST_ALPHA              = 0x0305,
		ONE_MINUS_DST_COLOR              = 0x0307,
		ONE_MINUS_SRC_ALPHA              = 0x0303,
		ONE_MINUS_SRC_COLOR              = 0x0301,
		OR                               = 0x1507,
		ORDER                            = 0x0A01,
		OR_INVERTED                      = 0x150D,
		OR_REVERSE                       = 0x150B,
		OUT_OF_MEMORY                    = 0x0505,
		PACK_ALIGNMENT                   = 0x0D05,
		PACK_LSB_FIRST                   = 0x0D01,
		PACK_ROW_LENGTH                  = 0x0D02,
		PACK_SKIP_PIXELS                 = 0x0D04,
		PACK_SKIP_ROWS                   = 0x0D03,
		PACK_SWAP_BYTES                  = 0x0D00,
		PASS_THROUGH_TOKEN               = 0x0700,
		PERSPECTIVE_CORRECTION_HINT      = 0x0C50,
		PIXEL_MAP_A_TO_A                 = 0x0C79,
		PIXEL_MAP_A_TO_A_SIZE            = 0x0CB9,
		PIXEL_MAP_B_TO_B                 = 0x0C78,
		PIXEL_MAP_B_TO_B_SIZE            = 0x0CB8,
		PIXEL_MAP_G_TO_G                 = 0x0C77,
		PIXEL_MAP_G_TO_G_SIZE            = 0x0CB7,
		PIXEL_MAP_I_TO_A                 = 0x0C75,
		PIXEL_MAP_I_TO_A_SIZE            = 0x0CB5,
		PIXEL_MAP_I_TO_B                 = 0x0C74,
		PIXEL_MAP_I_TO_B_SIZE            = 0x0CB4,
		PIXEL_MAP_I_TO_G                 = 0x0C73,
		PIXEL_MAP_I_TO_G_SIZE            = 0x0CB3,
		PIXEL_MAP_I_TO_I                 = 0x0C70,
		PIXEL_MAP_I_TO_I_SIZE            = 0x0CB0,
		PIXEL_MAP_I_TO_R                 = 0x0C72,
		PIXEL_MAP_I_TO_R_SIZE            = 0x0CB2,
		PIXEL_MAP_R_TO_R                 = 0x0C76,
		PIXEL_MAP_R_TO_R_SIZE            = 0x0CB6,
		PIXEL_MAP_S_TO_S                 = 0x0C71,
		PIXEL_MAP_S_TO_S_SIZE            = 0x0CB1,
		PIXEL_MODE_BIT                   = 0x00000020,
		POINT                            = 0x1B00,
		POINTS                           = 0x0000,
		POINT_BIT                        = 0x00000002,
		POINT_SIZE                       = 0x0B11,
		POINT_SIZE_GRANULARITY           = 0x0B13,
		POINT_SIZE_RANGE                 = 0x0B12,
		POINT_SMOOTH                     = 0x0B10,
		POINT_SMOOTH_HINT                = 0x0C51,
		POINT_TOKEN                      = 0x0701,
		POLYGON                          = 0x0009,
		POLYGON_BIT                      = 0x00000008,
		POLYGON_MODE                     = 0x0B40,
		POLYGON_OFFSET_FACTOR            = 0x8038,
		POLYGON_OFFSET_FILL              = 0x8037,
		POLYGON_OFFSET_LINE              = 0x2A02,
		POLYGON_OFFSET_POINT             = 0x2A01,
		POLYGON_OFFSET_UNITS             = 0x2A00,
		POLYGON_SMOOTH                   = 0x0B41,
		POLYGON_SMOOTH_HINT              = 0x0C53,
		POLYGON_STIPPLE                  = 0x0B42,
		POLYGON_STIPPLE_BIT              = 0x00000010,
		POLYGON_TOKEN                    = 0x0703,
		POSITION                         = 0x1203,
		PROJECTION                       = 0x1701,
		PROJECTION_MATRIX                = 0x0BA7,
		PROJECTION_STACK_DEPTH           = 0x0BA4,
		PROXY_TEXTURE_1D                 = 0x8063,
		PROXY_TEXTURE_2D                 = 0x8064,
		Q                                = 0x2003,
		QUADRATIC_ATTENUATION            = 0x1209,
		QUADS                            = 0x0007,
		QUAD_STRIP                       = 0x0008,
		R                                = 0x2002,
		R3_G3_B2                         = 0x2A10,
		READ_BUFFER                      = 0x0C02,
		RED                              = 0x1903,
		RED_BIAS                         = 0x0D15,
		RED_BITS                         = 0x0D52,
		RED_SCALE                        = 0x0D14,
		RENDER                           = 0x1C00,
		RENDERER                         = 0x1F01,
		RENDER_MODE                      = 0x0C40,
		REPEAT                           = 0x2901,
		REPLACE                          = 0x1E01,
		RETURN                           = 0x0102,
		RGB                              = 0x1907,
		RGB10                            = 0x8052,
		RGB10_A2                         = 0x8059,
		RGB12                            = 0x8053,
		RGB16                            = 0x8054,
		RGB4                             = 0x804F,
		RGB5                             = 0x8050,
		RGB5_A1                          = 0x8057,
		RGB8                             = 0x8051,
		RGBA                             = 0x1908,
		RGBA12                           = 0x805A,
		RGBA16                           = 0x805B,
		RGBA2                            = 0x8055,
		RGBA4                            = 0x8056,
		RGBA8                            = 0x8058,
		RGBA_MODE                        = 0x0C31,
		RIGHT                            = 0x0407,
		S                                = 0x2000,
		SCISSOR_BIT                      = 0x00080000,
		SCISSOR_BOX                      = 0x0C10,
		SCISSOR_TEST                     = 0x0C11,
		SELECT                           = 0x1C02,
		SELECTION_BUFFER_POINTER         = 0x0DF3,
		SELECTION_BUFFER_SIZE            = 0x0DF4,
		SET                              = 0x150F,
		SHADE_MODEL                      = 0x0B54,
		SHININESS                        = 0x1601,
		SHORT                            = 0x1402,
		SMOOTH                           = 0x1D01,
		SPECULAR                         = 0x1202,
		SPHERE_MAP                       = 0x2402,
		SPOT_CUTOFF                      = 0x1206,
		SPOT_DIRECTION                   = 0x1204,
		SPOT_EXPONENT                    = 0x1205,
		SRC_ALPHA                        = 0x0302,
		SRC_ALPHA_SATURATE               = 0x0308,
		SRC_COLOR                        = 0x0300,
		STACK_OVERFLOW                   = 0x0503,
		STACK_UNDERFLOW                  = 0x0504,
		STENCIL                          = 0x1802,
		STENCIL_BITS                     = 0x0D57,
		STENCIL_BUFFER_BIT               = 0x00000400,
		STENCIL_CLEAR_VALUE              = 0x0B91,
		STENCIL_FAIL                     = 0x0B94,
		STENCIL_FUNC                     = 0x0B92,
		STENCIL_INDEX                    = 0x1901,
		STENCIL_PASS_DEPTH_FAIL          = 0x0B95,
		STENCIL_PASS_DEPTH_PASS          = 0x0B96,
		STENCIL_REF                      = 0x0B97,
		STENCIL_TEST                     = 0x0B90,
		STENCIL_VALUE_MASK               = 0x0B93,
		STENCIL_WRITEMASK                = 0x0B98,
		STEREO                           = 0x0C33,
		SUBPIXEL_BITS                    = 0x0D50,
		T                                = 0x2001,
		T2F_C3F_V3F                      = 0x2A2A,
		T2F_C4F_N3F_V3F                  = 0x2A2C,
		T2F_C4UB_V3F                     = 0x2A29,
		T2F_N3F_V3F                      = 0x2A2B,
		T2F_V3F                          = 0x2A27,
		T4F_C4F_N3F_V4F                  = 0x2A2D,
		T4F_V4F                          = 0x2A28,
		TEXTURE                          = 0x1702,
		TEXTURE_1D                       = 0x0DE0,
		TEXTURE_2D                       = 0x0DE1,
		TEXTURE_ALPHA_SIZE               = 0x805F,
		TEXTURE_BINDING_1D               = 0x8068,
		TEXTURE_BINDING_2D               = 0x8069,
		TEXTURE_BIT                      = 0x00040000,
		TEXTURE_BLUE_SIZE                = 0x805E,
		TEXTURE_BORDER                   = 0x1005,
		TEXTURE_BORDER_COLOR             = 0x1004,
		TEXTURE_COMPONENTS               = 0x1003,
		TEXTURE_COORD_ARRAY              = 0x8078,
		TEXTURE_COORD_ARRAY_POINTER      = 0x8092,
		TEXTURE_COORD_ARRAY_SIZE         = 0x8088,
		TEXTURE_COORD_ARRAY_STRIDE       = 0x808A,
		TEXTURE_COORD_ARRAY_TYPE         = 0x8089,
		TEXTURE_ENV                      = 0x2300,
		TEXTURE_ENV_COLOR                = 0x2201,
		TEXTURE_ENV_MODE                 = 0x2200,
		TEXTURE_GEN_MODE                 = 0x2500,
		TEXTURE_GEN_Q                    = 0x0C63,
		TEXTURE_GEN_R                    = 0x0C62,
		TEXTURE_GEN_S                    = 0x0C60,
		TEXTURE_GEN_T                    = 0x0C61,
		TEXTURE_GREEN_SIZE               = 0x805D,
		TEXTURE_HEIGHT                   = 0x1001,
		TEXTURE_INTENSITY_SIZE           = 0x8061,
		TEXTURE_INTERNAL_FORMAT          = 0x1003,
		TEXTURE_LUMINANCE_SIZE           = 0x8060,
		TEXTURE_MAG_FILTER               = 0x2800,
		TEXTURE_MATRIX                   = 0x0BA8,
		TEXTURE_MIN_FILTER               = 0x2801,
		TEXTURE_PRIORITY                 = 0x8066,
		TEXTURE_RED_SIZE                 = 0x805C,
		TEXTURE_RESIDENT                 = 0x8067,
		TEXTURE_STACK_DEPTH              = 0x0BA5,
		TEXTURE_WIDTH                    = 0x1000,
		TEXTURE_WRAP_S                   = 0x2802,
		TEXTURE_WRAP_T                   = 0x2803,
		TRANSFORM_BIT                    = 0x00001000,
		TRIANGLES                        = 0x0004,
		TRIANGLE_FAN                     = 0x0006,
		TRIANGLE_STRIP                   = 0x0005,
		TRUE_                            = 1,
		UNPACK_ALIGNMENT                 = 0x0CF5,
		UNPACK_LSB_FIRST                 = 0x0CF1,
		UNPACK_ROW_LENGTH                = 0x0CF2,
		UNPACK_SKIP_PIXELS               = 0x0CF4,
		UNPACK_SKIP_ROWS                 = 0x0CF3,
		UNPACK_SWAP_BYTES                = 0x0CF0,
		UNSIGNED_BYTE                    = 0x1401,
		UNSIGNED_INT                     = 0x1405,
		UNSIGNED_SHORT                   = 0x1403,
		V2F                              = 0x2A20,
		V3F                              = 0x2A21,
		VENDOR                           = 0x1F00,
		VERSION                          = 0x1F02,
		VERTEX_ARRAY                     = 0x8074,
		VERTEX_ARRAY_POINTER             = 0x808E,
		VERTEX_ARRAY_SIZE                = 0x807A,
		VERTEX_ARRAY_STRIDE              = 0x807C,
		VERTEX_ARRAY_TYPE                = 0x807B,
		VIEWPORT                         = 0x0BA2,
		VIEWPORT_BIT                     = 0x00000800,
		XOR                              = 0x1506,
		ZERO                             = 0,
		ZOOM_X                           = 0x0D16,
		ZOOM_Y                           = 0x0D17,
		
		ALIASED_LINE_WIDTH_RANGE         = 0x846E,
		ALIASED_POINT_SIZE_RANGE         = 0x846D,
		BGR                              = 0x80E0,
		BGRA                             = 0x80E1,
		CLAMP_TO_EDGE                    = 0x812F,
		LIGHT_MODEL_COLOR_CONTROL        = 0x81F8,
		MAX_3D_TEXTURE_SIZE              = 0x8073,
		MAX_ELEMENTS_INDICES             = 0x80E9,
		MAX_ELEMENTS_VERTICES            = 0x80E8,
		PACK_IMAGE_HEIGHT                = 0x806C,
		PACK_SKIP_IMAGES                 = 0x806B,
		PROXY_TEXTURE_3D                 = 0x8070,
		RESCALE_NORMAL                   = 0x803A,
		SEPARATE_SPECULAR_COLOR          = 0x81FA,
		SINGLE_COLOR                     = 0x81F9,
		SMOOTH_LINE_WIDTH_GRANULARITY    = 0x0B23,
		SMOOTH_LINE_WIDTH_RANGE          = 0x0B22,
		SMOOTH_POINT_SIZE_GRANULARITY    = 0x0B13,
		SMOOTH_POINT_SIZE_RANGE          = 0x0B12,
		TEXTURE_3D                       = 0x806F,
		TEXTURE_BASE_LEVEL               = 0x813C,
		TEXTURE_BINDING_3D               = 0x806A,
		TEXTURE_DEPTH                    = 0x8071,
		TEXTURE_MAX_LEVEL                = 0x813D,
		TEXTURE_MAX_LOD                  = 0x813B,
		TEXTURE_MIN_LOD                  = 0x813A,
		TEXTURE_WRAP_R                   = 0x8072,
		UNPACK_IMAGE_HEIGHT              = 0x806E,
		UNPACK_SKIP_IMAGES               = 0x806D,
		UNSIGNED_BYTE_2_3_3_REV          = 0x8362,
		UNSIGNED_BYTE_3_3_2              = 0x8032,
		UNSIGNED_INT_10_10_10_2          = 0x8036,
		UNSIGNED_INT_2_10_10_10_REV      = 0x8368,
		UNSIGNED_INT_8_8_8_8             = 0x8035,
		UNSIGNED_INT_8_8_8_8_REV         = 0x8367,
		UNSIGNED_SHORT_1_5_5_5_REV       = 0x8366,
		UNSIGNED_SHORT_4_4_4_4           = 0x8033,
		UNSIGNED_SHORT_4_4_4_4_REV       = 0x8365,
		UNSIGNED_SHORT_5_5_5_1           = 0x8034,
		UNSIGNED_SHORT_5_6_5             = 0x8363,
		UNSIGNED_SHORT_5_6_5_REV         = 0x8364,
		
		ACTIVE_TEXTURE                   = 0x84E0,
		ADD_SIGNED                       = 0x8574,
		CLAMP_TO_BORDER                  = 0x812D,
		CLIENT_ACTIVE_TEXTURE            = 0x84E1,
		COMBINE                          = 0x8570,
		COMBINE_ALPHA                    = 0x8572,
		COMBINE_RGB                      = 0x8571,
		COMPRESSED_ALPHA                 = 0x84E9,
		COMPRESSED_INTENSITY             = 0x84EC,
		COMPRESSED_LUMINANCE             = 0x84EA,
		COMPRESSED_LUMINANCE_ALPHA       = 0x84EB,
		COMPRESSED_RGB                   = 0x84ED,
		COMPRESSED_RGBA                  = 0x84EE,
		COMPRESSED_TEXTURE_FORMATS       = 0x86A3,
		CONSTANT                         = 0x8576,
		DOT3_RGB                         = 0x86AE,
		DOT3_RGBA                        = 0x86AF,
		INTERPOLATE                      = 0x8575,
		MAX_CUBE_MAP_TEXTURE_SIZE        = 0x851C,
		MAX_TEXTURE_UNITS                = 0x84E2,
		MULTISAMPLE                      = 0x809D,
		MULTISAMPLE_BIT                  = 0x20000000,
		NORMAL_MAP                       = 0x8511,
		NUM_COMPRESSED_TEXTURE_FORMATS   = 0x86A2,
		OPERAND0_ALPHA                   = 0x8598,
		OPERAND0_RGB                     = 0x8590,
		OPERAND1_ALPHA                   = 0x8599,
		OPERAND1_RGB                     = 0x8591,
		OPERAND2_ALPHA                   = 0x859A,
		OPERAND2_RGB                     = 0x8592,
		PREVIOUS                         = 0x8578,
		PRIMARY_COLOR                    = 0x8577,
		PROXY_TEXTURE_CUBE_MAP           = 0x851B,
		REFLECTION_MAP                   = 0x8512,
		RGB_SCALE                        = 0x8573,
		SAMPLES                          = 0x80A9,
		SAMPLE_ALPHA_TO_COVERAGE         = 0x809E,
		SAMPLE_ALPHA_TO_ONE              = 0x809F,
		SAMPLE_BUFFERS                   = 0x80A8,
		SAMPLE_COVERAGE                  = 0x80A0,
		SAMPLE_COVERAGE_INVERT           = 0x80AB,
		SAMPLE_COVERAGE_VALUE            = 0x80AA,
		SOURCE0_ALPHA                    = 0x8588,
		SOURCE0_RGB                      = 0x8580,
		SOURCE1_ALPHA                    = 0x8589,
		SOURCE1_RGB                      = 0x8581,
		SOURCE2_ALPHA                    = 0x858A,
		SOURCE2_RGB                      = 0x8582,
		SUBTRACT                         = 0x84E7,
		TEXTURE0                         = 0x84C0,
		TEXTURE1                         = 0x84C1,
		TEXTURE10                        = 0x84CA,
		TEXTURE11                        = 0x84CB,
		TEXTURE12                        = 0x84CC,
		TEXTURE13                        = 0x84CD,
		TEXTURE14                        = 0x84CE,
		TEXTURE15                        = 0x84CF,
		TEXTURE16                        = 0x84D0,
		TEXTURE17                        = 0x84D1,
		TEXTURE18                        = 0x84D2,
		TEXTURE19                        = 0x84D3,
		TEXTURE2                         = 0x84C2,
		TEXTURE20                        = 0x84D4,
		TEXTURE21                        = 0x84D5,
		TEXTURE22                        = 0x84D6,
		TEXTURE23                        = 0x84D7,
		TEXTURE24                        = 0x84D8,
		TEXTURE25                        = 0x84D9,
		TEXTURE26                        = 0x84DA,
		TEXTURE27                        = 0x84DB,
		TEXTURE28                        = 0x84DC,
		TEXTURE29                        = 0x84DD,
		TEXTURE3                         = 0x84C3,
		TEXTURE30                        = 0x84DE,
		TEXTURE31                        = 0x84DF,
		TEXTURE4                         = 0x84C4,
		TEXTURE5                         = 0x84C5,
		TEXTURE6                         = 0x84C6,
		TEXTURE7                         = 0x84C7,
		TEXTURE8                         = 0x84C8,
		TEXTURE9                         = 0x84C9,
		TEXTURE_BINDING_CUBE_MAP         = 0x8514,
		TEXTURE_COMPRESSED               = 0x86A1,
		TEXTURE_COMPRESSED_IMAGE_SIZE    = 0x86A0,
		TEXTURE_COMPRESSION_HINT         = 0x84EF,
		TEXTURE_CUBE_MAP                 = 0x8513,
		TEXTURE_CUBE_MAP_NEGATIVE_X      = 0x8516,
		TEXTURE_CUBE_MAP_NEGATIVE_Y      = 0x8518,
		TEXTURE_CUBE_MAP_NEGATIVE_Z      = 0x851A,
		TEXTURE_CUBE_MAP_POSITIVE_X      = 0x8515,
		TEXTURE_CUBE_MAP_POSITIVE_Y      = 0x8517,
		TEXTURE_CUBE_MAP_POSITIVE_Z      = 0x8519,
		TRANSPOSE_COLOR_MATRIX           = 0x84E6,
		TRANSPOSE_MODELVIEW_MATRIX       = 0x84E3,
		TRANSPOSE_PROJECTION_MATRIX      = 0x84E4,
		TRANSPOSE_TEXTURE_MATRIX         = 0x84E5,
		
		BLEND_COLOR                      = 0x8005,
		BLEND_DST_ALPHA                  = 0x80CA,
		BLEND_DST_RGB                    = 0x80C8,
		BLEND_SRC_ALPHA                  = 0x80CB,
		BLEND_SRC_RGB                    = 0x80C9,
		COLOR_SUM                        = 0x8458,
		COMPARE_R_TO_TEXTURE             = 0x884E,
		CONSTANT_ALPHA                   = 0x8003,
		CONSTANT_COLOR                   = 0x8001,
		CURRENT_FOG_COORDINATE           = 0x8453,
		CURRENT_SECONDARY_COLOR          = 0x8459,
		DECR_WRAP                        = 0x8508,
		DEPTH_COMPONENT16                = 0x81A5,
		DEPTH_COMPONENT24                = 0x81A6,
		DEPTH_COMPONENT32                = 0x81A7,
		DEPTH_TEXTURE_MODE               = 0x884B,
		FOG_COORDINATE                   = 0x8451,
		FOG_COORDINATE_ARRAY             = 0x8457,
		FOG_COORDINATE_ARRAY_POINTER     = 0x8456,
		FOG_COORDINATE_ARRAY_STRIDE      = 0x8455,
		FOG_COORDINATE_ARRAY_TYPE        = 0x8454,
		FOG_COORDINATE_SOURCE            = 0x8450,
		FRAGMENT_DEPTH                   = 0x8452,
		FUNC_ADD                         = 0x8006,
		FUNC_REVERSE_SUBTRACT            = 0x800B,
		FUNC_SUBTRACT                    = 0x800A,
		GENERATE_MIPMAP                  = 0x8191,
		GENERATE_MIPMAP_HINT             = 0x8192,
		INCR_WRAP                        = 0x8507,
		MAX                              = 0x8008,
		MAX_TEXTURE_LOD_BIAS             = 0x84FD,
		MIN                              = 0x8007,
		MIRRORED_REPEAT                  = 0x8370,
		ONE_MINUS_CONSTANT_ALPHA         = 0x8004,
		ONE_MINUS_CONSTANT_COLOR         = 0x8002,
		POINT_DISTANCE_ATTENUATION       = 0x8129,
		POINT_FADE_THRESHOLD_SIZE        = 0x8128,
		POINT_SIZE_MAX                   = 0x8127,
		POINT_SIZE_MIN                   = 0x8126,
		SECONDARY_COLOR_ARRAY            = 0x845E,
		SECONDARY_COLOR_ARRAY_POINTER    = 0x845D,
		SECONDARY_COLOR_ARRAY_SIZE       = 0x845A,
		SECONDARY_COLOR_ARRAY_STRIDE     = 0x845C,
		SECONDARY_COLOR_ARRAY_TYPE       = 0x845B,
		TEXTURE_COMPARE_FUNC             = 0x884D,
		TEXTURE_COMPARE_MODE             = 0x884C,
		TEXTURE_DEPTH_SIZE               = 0x884A,
		TEXTURE_FILTER_CONTROL           = 0x8500,
		TEXTURE_LOD_BIAS                 = 0x8501,
		
		ARRAY_BUFFER                     = 0x8892,
		ARRAY_BUFFER_BINDING             = 0x8894,
		BUFFER_ACCESS                    = 0x88BB,
		BUFFER_MAPPED                    = 0x88BC,
		BUFFER_MAP_POINTER               = 0x88BD,
		BUFFER_SIZE                      = 0x8764,
		BUFFER_USAGE                     = 0x8765,
		COLOR_ARRAY_BUFFER_BINDING       = 0x8898,
		CURRENT_FOG_COORD                = 0x8453,
		CURRENT_QUERY                    = 0x8865,
		DYNAMIC_COPY                     = 0x88EA,
		DYNAMIC_DRAW                     = 0x88E8,
		DYNAMIC_READ                     = 0x88E9,
		EDGE_FLAG_ARRAY_BUFFER_BINDING   = 0x889B,
		ELEMENT_ARRAY_BUFFER             = 0x8893,
		ELEMENT_ARRAY_BUFFER_BINDING     = 0x8895,
		FOG_COORD                        = 0x8451,
		FOG_COORDINATE_ARRAY_BUFFER_BINDING = 0x889D,
		FOG_COORD_ARRAY                  = 0x8457,
		FOG_COORD_ARRAY_BUFFER_BINDING   = 0x889D,
		FOG_COORD_ARRAY_POINTER          = 0x8456,
		FOG_COORD_ARRAY_STRIDE           = 0x8455,
		FOG_COORD_ARRAY_TYPE             = 0x8454,
		FOG_COORD_SRC                    = 0x8450,
		INDEX_ARRAY_BUFFER_BINDING       = 0x8899,
		NORMAL_ARRAY_BUFFER_BINDING      = 0x8897,
		QUERY_COUNTER_BITS               = 0x8864,
		QUERY_RESULT                     = 0x8866,
		QUERY_RESULT_AVAILABLE           = 0x8867,
		READ_ONLY                        = 0x88B8,
		READ_WRITE                       = 0x88BA,
		SAMPLES_PASSED                   = 0x8914,
		SECONDARY_COLOR_ARRAY_BUFFER_BINDING = 0x889C,
		SRC0_ALPHA                       = 0x8588,
		SRC0_RGB                         = 0x8580,
		SRC1_ALPHA                       = 0x8589,
		SRC1_RGB                         = 0x8581,
		SRC2_ALPHA                       = 0x858A,
		SRC2_RGB                         = 0x8582,
		STATIC_COPY                      = 0x88E6,
		STATIC_DRAW                      = 0x88E4,
		STATIC_READ                      = 0x88E5,
		STREAM_COPY                      = 0x88E2,
		STREAM_DRAW                      = 0x88E0,
		STREAM_READ                      = 0x88E1,
		TEXTURE_COORD_ARRAY_BUFFER_BINDING = 0x889A,
		VERTEX_ARRAY_BUFFER_BINDING      = 0x8896,
		VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = 0x889F,
		WEIGHT_ARRAY_BUFFER_BINDING      = 0x889E,
		WRITE_ONLY                       = 0x88B9,
		
		ACTIVE_ATTRIBUTES                = 0x8B89,
		ACTIVE_ATTRIBUTE_MAX_LENGTH      = 0x8B8A,
		ACTIVE_UNIFORMS                  = 0x8B86,
		ACTIVE_UNIFORM_MAX_LENGTH        = 0x8B87,
		ATTACHED_SHADERS                 = 0x8B85,
		BLEND_EQUATION_ALPHA             = 0x883D,
		BLEND_EQUATION_RGB               = 0x8009,
		BOOL                             = 0x8B56,
		BOOL_VEC2                        = 0x8B57,
		BOOL_VEC3                        = 0x8B58,
		BOOL_VEC4                        = 0x8B59,
		COMPILE_STATUS                   = 0x8B81,
		COORD_REPLACE                    = 0x8862,
		CURRENT_PROGRAM                  = 0x8B8D,
		CURRENT_VERTEX_ATTRIB            = 0x8626,
		DELETE_STATUS                    = 0x8B80,
		DRAW_BUFFER0                     = 0x8825,
		DRAW_BUFFER1                     = 0x8826,
		DRAW_BUFFER10                    = 0x882F,
		DRAW_BUFFER11                    = 0x8830,
		DRAW_BUFFER12                    = 0x8831,
		DRAW_BUFFER13                    = 0x8832,
		DRAW_BUFFER14                    = 0x8833,
		DRAW_BUFFER15                    = 0x8834,
		DRAW_BUFFER2                     = 0x8827,
		DRAW_BUFFER3                     = 0x8828,
		DRAW_BUFFER4                     = 0x8829,
		DRAW_BUFFER5                     = 0x882A,
		DRAW_BUFFER6                     = 0x882B,
		DRAW_BUFFER7                     = 0x882C,
		DRAW_BUFFER8                     = 0x882D,
		DRAW_BUFFER9                     = 0x882E,
		FLOAT_MAT2                       = 0x8B5A,
		FLOAT_MAT3                       = 0x8B5B,
		FLOAT_MAT4                       = 0x8B5C,
		FLOAT_VEC2                       = 0x8B50,
		FLOAT_VEC3                       = 0x8B51,
		FLOAT_VEC4                       = 0x8B52,
		FRAGMENT_SHADER                  = 0x8B30,
		FRAGMENT_SHADER_DERIVATIVE_HINT  = 0x8B8B,
		INFO_LOG_LENGTH                  = 0x8B84,
		INT_VEC2                         = 0x8B53,
		INT_VEC3                         = 0x8B54,
		INT_VEC4                         = 0x8B55,
		LINK_STATUS                      = 0x8B82,
		LOWER_LEFT                       = 0x8CA1,
		MAX_COMBINED_TEXTURE_IMAGE_UNITS = 0x8B4D,
		MAX_DRAW_BUFFERS                 = 0x8824,
		MAX_FRAGMENT_UNIFORM_COMPONENTS  = 0x8B49,
		MAX_TEXTURE_COORDS               = 0x8871,
		MAX_TEXTURE_IMAGE_UNITS          = 0x8872,
		MAX_VARYING_FLOATS               = 0x8B4B,
		MAX_VERTEX_ATTRIBS               = 0x8869,
		MAX_VERTEX_TEXTURE_IMAGE_UNITS   = 0x8B4C,
		MAX_VERTEX_UNIFORM_COMPONENTS    = 0x8B4A,
		POINT_SPRITE                     = 0x8861,
		POINT_SPRITE_COORD_ORIGIN        = 0x8CA0,
		SAMPLER_1D                       = 0x8B5D,
		SAMPLER_1D_SHADOW                = 0x8B61,
		SAMPLER_2D                       = 0x8B5E,
		SAMPLER_2D_SHADOW                = 0x8B62,
		SAMPLER_3D                       = 0x8B5F,
		SAMPLER_CUBE                     = 0x8B60,
		SHADER_SOURCE_LENGTH             = 0x8B88,
		SHADER_TYPE                      = 0x8B4F,
		SHADING_LANGUAGE_VERSION         = 0x8B8C,
		STENCIL_BACK_FAIL                = 0x8801,
		STENCIL_BACK_FUNC                = 0x8800,
		STENCIL_BACK_PASS_DEPTH_FAIL     = 0x8802,
		STENCIL_BACK_PASS_DEPTH_PASS     = 0x8803,
		STENCIL_BACK_REF                 = 0x8CA3,
		STENCIL_BACK_VALUE_MASK          = 0x8CA4,
		STENCIL_BACK_WRITEMASK           = 0x8CA5,
		UPPER_LEFT                       = 0x8CA2,
		VALIDATE_STATUS                  = 0x8B83,
		VERTEX_ATTRIB_ARRAY_ENABLED      = 0x8622,
		VERTEX_ATTRIB_ARRAY_NORMALIZED   = 0x886A,
		VERTEX_ATTRIB_ARRAY_POINTER      = 0x8645,
		VERTEX_ATTRIB_ARRAY_SIZE         = 0x8623,
		VERTEX_ATTRIB_ARRAY_STRIDE       = 0x8624,
		VERTEX_ATTRIB_ARRAY_TYPE         = 0x8625,
		VERTEX_PROGRAM_POINT_SIZE        = 0x8642,
		VERTEX_PROGRAM_TWO_SIDE          = 0x8643,
		VERTEX_SHADER                    = 0x8B31,
		
		COMPRESSED_SLUMINANCE            = 0x8C4A,
		COMPRESSED_SLUMINANCE_ALPHA      = 0x8C4B,
		COMPRESSED_SRGB                  = 0x8C48,
		COMPRESSED_SRGB_ALPHA            = 0x8C49,
		CURRENT_RASTER_SECONDARY_COLOR   = 0x845F,
		FLOAT_MAT2x3                     = 0x8B65,
		FLOAT_MAT2x4                     = 0x8B66,
		FLOAT_MAT3x2                     = 0x8B67,
		FLOAT_MAT3x4                     = 0x8B68,
		FLOAT_MAT4x2                     = 0x8B69,
		FLOAT_MAT4x3                     = 0x8B6A,
		PIXEL_PACK_BUFFER                = 0x88EB,
		PIXEL_PACK_BUFFER_BINDING        = 0x88ED,
		PIXEL_UNPACK_BUFFER              = 0x88EC,
		PIXEL_UNPACK_BUFFER_BINDING      = 0x88EF,
		SLUMINANCE                       = 0x8C46,
		SLUMINANCE8                      = 0x8C47,
		SLUMINANCE8_ALPHA8               = 0x8C45,
		SLUMINANCE_ALPHA                 = 0x8C44,
		SRGB                             = 0x8C40,
		SRGB8                            = 0x8C41,
		SRGB8_ALPHA8                     = 0x8C43,
		SRGB_ALPHA                       = 0x8C42,
		
		ALPHA_INTEGER                    = 0x8D97,
		BGRA_INTEGER                     = 0x8D9B,
		BGR_INTEGER                      = 0x8D9A,
		BLUE_INTEGER                     = 0x8D96,
		BUFFER_ACCESS_FLAGS              = 0x911F,
		BUFFER_MAP_LENGTH                = 0x9120,
		BUFFER_MAP_OFFSET                = 0x9121,
		CLAMP_FRAGMENT_COLOR             = 0x891B,
		CLAMP_READ_COLOR                 = 0x891C,
		CLAMP_VERTEX_COLOR               = 0x891A,
		CLIP_DISTANCE0                   = 0x3000,
		CLIP_DISTANCE1                   = 0x3001,
		CLIP_DISTANCE2                   = 0x3002,
		CLIP_DISTANCE3                   = 0x3003,
		CLIP_DISTANCE4                   = 0x3004,
		CLIP_DISTANCE5                   = 0x3005,
		CLIP_DISTANCE6                   = 0x3006,
		CLIP_DISTANCE7                   = 0x3007,
		COLOR_ATTACHMENT0                = 0x8CE0,
		COLOR_ATTACHMENT1                = 0x8CE1,
		COLOR_ATTACHMENT10               = 0x8CEA,
		COLOR_ATTACHMENT11               = 0x8CEB,
		COLOR_ATTACHMENT12               = 0x8CEC,
		COLOR_ATTACHMENT13               = 0x8CED,
		COLOR_ATTACHMENT14               = 0x8CEE,
		COLOR_ATTACHMENT15               = 0x8CEF,
		COLOR_ATTACHMENT16               = 0x8CF0,
		COLOR_ATTACHMENT17               = 0x8CF1,
		COLOR_ATTACHMENT18               = 0x8CF2,
		COLOR_ATTACHMENT19               = 0x8CF3,
		COLOR_ATTACHMENT2                = 0x8CE2,
		COLOR_ATTACHMENT20               = 0x8CF4,
		COLOR_ATTACHMENT21               = 0x8CF5,
		COLOR_ATTACHMENT22               = 0x8CF6,
		COLOR_ATTACHMENT23               = 0x8CF7,
		COLOR_ATTACHMENT24               = 0x8CF8,
		COLOR_ATTACHMENT25               = 0x8CF9,
		COLOR_ATTACHMENT26               = 0x8CFA,
		COLOR_ATTACHMENT27               = 0x8CFB,
		COLOR_ATTACHMENT28               = 0x8CFC,
		COLOR_ATTACHMENT29               = 0x8CFD,
		COLOR_ATTACHMENT3                = 0x8CE3,
		COLOR_ATTACHMENT30               = 0x8CFE,
		COLOR_ATTACHMENT31               = 0x8CFF,
		COLOR_ATTACHMENT4                = 0x8CE4,
		COLOR_ATTACHMENT5                = 0x8CE5,
		COLOR_ATTACHMENT6                = 0x8CE6,
		COLOR_ATTACHMENT7                = 0x8CE7,
		COLOR_ATTACHMENT8                = 0x8CE8,
		COLOR_ATTACHMENT9                = 0x8CE9,
		COMPARE_REF_TO_TEXTURE           = 0x884E,
		COMPRESSED_RED                   = 0x8225,
		COMPRESSED_RED_RGTC1             = 0x8DBB,
		COMPRESSED_RG                    = 0x8226,
		COMPRESSED_RG_RGTC2              = 0x8DBD,
		COMPRESSED_SIGNED_RED_RGTC1      = 0x8DBC,
		COMPRESSED_SIGNED_RG_RGTC2       = 0x8DBE,
		CONTEXT_FLAGS                    = 0x821E,
		CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT = 0x00000001,
		DEPTH24_STENCIL8                 = 0x88F0,
		DEPTH32F_STENCIL8                = 0x8CAD,
		DEPTH_ATTACHMENT                 = 0x8D00,
		DEPTH_COMPONENT32F               = 0x8CAC,
		DEPTH_STENCIL                    = 0x84F9,
		DEPTH_STENCIL_ATTACHMENT         = 0x821A,
		DRAW_FRAMEBUFFER                 = 0x8CA9,
		DRAW_FRAMEBUFFER_BINDING         = 0x8CA6,
		FIXED_ONLY                       = 0x891D,
		FLOAT_32_UNSIGNED_INT_24_8_REV   = 0x8DAD,
		FRAMEBUFFER                      = 0x8D40,
		FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE = 0x8215,
		FRAMEBUFFER_ATTACHMENT_BLUE_SIZE = 0x8214,
		FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING = 0x8210,
		FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE = 0x8211,
		FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE = 0x8216,
		FRAMEBUFFER_ATTACHMENT_GREEN_SIZE = 0x8213,
		FRAMEBUFFER_ATTACHMENT_OBJECT_NAME = 0x8CD1,
		FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = 0x8CD0,
		FRAMEBUFFER_ATTACHMENT_RED_SIZE  = 0x8212,
		FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE = 0x8217,
		FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE = 0x8CD3,
		FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER = 0x8CD4,
		FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL = 0x8CD2,
		FRAMEBUFFER_BINDING              = 0x8CA6,
		FRAMEBUFFER_COMPLETE             = 0x8CD5,
		FRAMEBUFFER_DEFAULT              = 0x8218,
		FRAMEBUFFER_INCOMPLETE_ATTACHMENT = 0x8CD6,
		FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER = 0x8CDB,
		FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = 0x8CD7,
		FRAMEBUFFER_INCOMPLETE_MULTISAMPLE = 0x8D56,
		FRAMEBUFFER_INCOMPLETE_READ_BUFFER = 0x8CDC,
		FRAMEBUFFER_SRGB                 = 0x8DB9,
		FRAMEBUFFER_UNDEFINED            = 0x8219,
		FRAMEBUFFER_UNSUPPORTED          = 0x8CDD,
		GREEN_INTEGER                    = 0x8D95,
		HALF_FLOAT                       = 0x140B,
		INTERLEAVED_ATTRIBS              = 0x8C8C,
		INT_SAMPLER_1D                   = 0x8DC9,
		INT_SAMPLER_1D_ARRAY             = 0x8DCE,
		INT_SAMPLER_2D                   = 0x8DCA,
		INT_SAMPLER_2D_ARRAY             = 0x8DCF,
		INT_SAMPLER_3D                   = 0x8DCB,
		INT_SAMPLER_CUBE                 = 0x8DCC,
		INVALID_FRAMEBUFFER_OPERATION    = 0x0506,
		MAJOR_VERSION                    = 0x821B,
		MAP_FLUSH_EXPLICIT_BIT           = 0x0010,
		MAP_INVALIDATE_BUFFER_BIT        = 0x0008,
		MAP_INVALIDATE_RANGE_BIT         = 0x0004,
		MAP_READ_BIT                     = 0x0001,
		MAP_UNSYNCHRONIZED_BIT           = 0x0020,
		MAP_WRITE_BIT                    = 0x0002,
		MAX_ARRAY_TEXTURE_LAYERS         = 0x88FF,
		MAX_CLIP_DISTANCES               = 0x0D32,
		MAX_COLOR_ATTACHMENTS            = 0x8CDF,
		MAX_PROGRAM_TEXEL_OFFSET         = 0x8905,
		MAX_RENDERBUFFER_SIZE            = 0x84E8,
		MAX_SAMPLES                      = 0x8D57,
		MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS = 0x8C8A,
		MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS = 0x8C8B,
		MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS = 0x8C80,
		MAX_VARYING_COMPONENTS           = 0x8B4B,
		MINOR_VERSION                    = 0x821C,
		MIN_PROGRAM_TEXEL_OFFSET         = 0x8904,
		NUM_EXTENSIONS                   = 0x821D,
		PRIMITIVES_GENERATED             = 0x8C87,
		PROXY_TEXTURE_1D_ARRAY           = 0x8C19,
		PROXY_TEXTURE_2D_ARRAY           = 0x8C1B,
		QUERY_BY_REGION_NO_WAIT          = 0x8E16,
		QUERY_BY_REGION_WAIT             = 0x8E15,
		QUERY_NO_WAIT                    = 0x8E14,
		QUERY_WAIT                       = 0x8E13,
		R11F_G11F_B10F                   = 0x8C3A,
		R16                              = 0x822A,
		R16F                             = 0x822D,
		R16I                             = 0x8233,
		R16UI                            = 0x8234,
		R32F                             = 0x822E,
		R32I                             = 0x8235,
		R32UI                            = 0x8236,
		R8                               = 0x8229,
		R8I                              = 0x8231,
		R8UI                             = 0x8232,
		RASTERIZER_DISCARD               = 0x8C89,
		READ_FRAMEBUFFER                 = 0x8CA8,
		READ_FRAMEBUFFER_BINDING         = 0x8CAA,
		RED_INTEGER                      = 0x8D94,
		RENDERBUFFER                     = 0x8D41,
		RENDERBUFFER_ALPHA_SIZE          = 0x8D53,
		RENDERBUFFER_BINDING             = 0x8CA7,
		RENDERBUFFER_BLUE_SIZE           = 0x8D52,
		RENDERBUFFER_DEPTH_SIZE          = 0x8D54,
		RENDERBUFFER_GREEN_SIZE          = 0x8D51,
		RENDERBUFFER_HEIGHT              = 0x8D43,
		RENDERBUFFER_INTERNAL_FORMAT     = 0x8D44,
		RENDERBUFFER_RED_SIZE            = 0x8D50,
		RENDERBUFFER_SAMPLES             = 0x8CAB,
		RENDERBUFFER_STENCIL_SIZE        = 0x8D55,
		RENDERBUFFER_WIDTH               = 0x8D42,
		RG                               = 0x8227,
		RG16                             = 0x822C,
		RG16F                            = 0x822F,
		RG16I                            = 0x8239,
		RG16UI                           = 0x823A,
		RG32F                            = 0x8230,
		RG32I                            = 0x823B,
		RG32UI                           = 0x823C,
		RG8                              = 0x822B,
		RG8I                             = 0x8237,
		RG8UI                            = 0x8238,
		RGB16F                           = 0x881B,
		RGB16I                           = 0x8D89,
		RGB16UI                          = 0x8D77,
		RGB32F                           = 0x8815,
		RGB32I                           = 0x8D83,
		RGB32UI                          = 0x8D71,
		RGB8I                            = 0x8D8F,
		RGB8UI                           = 0x8D7D,
		RGB9_E5                          = 0x8C3D,
		RGBA16F                          = 0x881A,
		RGBA16I                          = 0x8D88,
		RGBA16UI                         = 0x8D76,
		RGBA32F                          = 0x8814,
		RGBA32I                          = 0x8D82,
		RGBA32UI                         = 0x8D70,
		RGBA8I                           = 0x8D8E,
		RGBA8UI                          = 0x8D7C,
		RGBA_INTEGER                     = 0x8D99,
		RGB_INTEGER                      = 0x8D98,
		RG_INTEGER                       = 0x8228,
		SAMPLER_1D_ARRAY                 = 0x8DC0,
		SAMPLER_1D_ARRAY_SHADOW          = 0x8DC3,
		SAMPLER_2D_ARRAY                 = 0x8DC1,
		SAMPLER_2D_ARRAY_SHADOW          = 0x8DC4,
		SAMPLER_CUBE_SHADOW              = 0x8DC5,
		SEPARATE_ATTRIBS                 = 0x8C8D,
		STENCIL_ATTACHMENT               = 0x8D20,
		STENCIL_INDEX1                   = 0x8D46,
		STENCIL_INDEX16                  = 0x8D49,
		STENCIL_INDEX4                   = 0x8D47,
		STENCIL_INDEX8                   = 0x8D48,
		TEXTURE_1D_ARRAY                 = 0x8C18,
		TEXTURE_2D_ARRAY                 = 0x8C1A,
		TEXTURE_ALPHA_TYPE               = 0x8C13,
		TEXTURE_BINDING_1D_ARRAY         = 0x8C1C,
		TEXTURE_BINDING_2D_ARRAY         = 0x8C1D,
		TEXTURE_BLUE_TYPE                = 0x8C12,
		TEXTURE_DEPTH_TYPE               = 0x8C16,
		TEXTURE_GREEN_TYPE               = 0x8C11,
		TEXTURE_RED_TYPE                 = 0x8C10,
		TEXTURE_SHARED_SIZE              = 0x8C3F,
		TEXTURE_STENCIL_SIZE             = 0x88F1,
		TRANSFORM_FEEDBACK_BUFFER        = 0x8C8E,
		TRANSFORM_FEEDBACK_BUFFER_BINDING = 0x8C8F,
		TRANSFORM_FEEDBACK_BUFFER_MODE   = 0x8C7F,
		TRANSFORM_FEEDBACK_BUFFER_SIZE   = 0x8C85,
		TRANSFORM_FEEDBACK_BUFFER_START  = 0x8C84,
		TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN = 0x8C88,
		TRANSFORM_FEEDBACK_VARYINGS      = 0x8C83,
		TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH = 0x8C76,
		UNSIGNED_INT_10F_11F_11F_REV     = 0x8C3B,
		UNSIGNED_INT_24_8                = 0x84FA,
		UNSIGNED_INT_5_9_9_9_REV         = 0x8C3E,
		UNSIGNED_INT_SAMPLER_1D          = 0x8DD1,
		UNSIGNED_INT_SAMPLER_1D_ARRAY    = 0x8DD6,
		UNSIGNED_INT_SAMPLER_2D          = 0x8DD2,
		UNSIGNED_INT_SAMPLER_2D_ARRAY    = 0x8DD7,
		UNSIGNED_INT_SAMPLER_3D          = 0x8DD3,
		UNSIGNED_INT_SAMPLER_CUBE        = 0x8DD4,
		UNSIGNED_INT_VEC2                = 0x8DC6,
		UNSIGNED_INT_VEC3                = 0x8DC7,
		UNSIGNED_INT_VEC4                = 0x8DC8,
		UNSIGNED_NORMALIZED              = 0x8C17,
		VERTEX_ARRAY_BINDING             = 0x85B5,
		VERTEX_ATTRIB_ARRAY_INTEGER      = 0x88FD,
		
		ACTIVE_UNIFORM_BLOCKS            = 0x8A36,
		ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH = 0x8A35,
		COPY_READ_BUFFER                 = 0x8F36,
		COPY_WRITE_BUFFER                = 0x8F37,
		INT_SAMPLER_2D_RECT              = 0x8DCD,
		INT_SAMPLER_BUFFER               = 0x8DD0,
		INVALID_INDEX                    = 0xFFFFFFFF,
		MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS = 0x8A33,
		MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS = 0x8A32,
		MAX_COMBINED_UNIFORM_BLOCKS      = 0x8A2E,
		MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS = 0x8A31,
		MAX_FRAGMENT_UNIFORM_BLOCKS      = 0x8A2D,
		MAX_GEOMETRY_UNIFORM_BLOCKS      = 0x8A2C,
		MAX_RECTANGLE_TEXTURE_SIZE       = 0x84F8,
		MAX_TEXTURE_BUFFER_SIZE          = 0x8C2B,
		MAX_UNIFORM_BLOCK_SIZE           = 0x8A30,
		MAX_UNIFORM_BUFFER_BINDINGS      = 0x8A2F,
		MAX_VERTEX_UNIFORM_BLOCKS        = 0x8A2B,
		PRIMITIVE_RESTART                = 0x8F9D,
		PRIMITIVE_RESTART_INDEX          = 0x8F9E,
		PROXY_TEXTURE_RECTANGLE          = 0x84F7,
		R16_SNORM                        = 0x8F98,
		R8_SNORM                         = 0x8F94,
		RG16_SNORM                       = 0x8F99,
		RG8_SNORM                        = 0x8F95,
		RGB16_SNORM                      = 0x8F9A,
		RGB8_SNORM                       = 0x8F96,
		RGBA16_SNORM                     = 0x8F9B,
		RGBA8_SNORM                      = 0x8F97,
		SAMPLER_2D_RECT                  = 0x8B63,
		SAMPLER_2D_RECT_SHADOW           = 0x8B64,
		SAMPLER_BUFFER                   = 0x8DC2,
		SIGNED_NORMALIZED                = 0x8F9C,
		TEXTURE_BINDING_BUFFER           = 0x8C2C,
		TEXTURE_BINDING_RECTANGLE        = 0x84F6,
		TEXTURE_BUFFER                   = 0x8C2A,
		TEXTURE_BUFFER_DATA_STORE_BINDING = 0x8C2D,
		TEXTURE_RECTANGLE                = 0x84F5,
		UNIFORM_ARRAY_STRIDE             = 0x8A3C,
		UNIFORM_BLOCK_ACTIVE_UNIFORMS    = 0x8A42,
		UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES = 0x8A43,
		UNIFORM_BLOCK_BINDING            = 0x8A3F,
		UNIFORM_BLOCK_DATA_SIZE          = 0x8A40,
		UNIFORM_BLOCK_INDEX              = 0x8A3A,
		UNIFORM_BLOCK_NAME_LENGTH        = 0x8A41,
		UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER = 0x8A46,
		UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER = 0x8A45,
		UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER = 0x8A44,
		UNIFORM_BUFFER                   = 0x8A11,
		UNIFORM_BUFFER_BINDING           = 0x8A28,
		UNIFORM_BUFFER_OFFSET_ALIGNMENT  = 0x8A34,
		UNIFORM_BUFFER_SIZE              = 0x8A2A,
		UNIFORM_BUFFER_START             = 0x8A29,
		UNIFORM_IS_ROW_MAJOR             = 0x8A3E,
		UNIFORM_MATRIX_STRIDE            = 0x8A3D,
		UNIFORM_NAME_LENGTH              = 0x8A39,
		UNIFORM_OFFSET                   = 0x8A3B,
		UNIFORM_SIZE                     = 0x8A38,
		UNIFORM_TYPE                     = 0x8A37,
		UNSIGNED_INT_SAMPLER_2D_RECT     = 0x8DD5,
		UNSIGNED_INT_SAMPLER_BUFFER      = 0x8DD8,
		
		ALREADY_SIGNALED                 = 0x911A,
		CONDITION_SATISFIED              = 0x911C,
		CONTEXT_COMPATIBILITY_PROFILE_BIT = 0x00000002,
		CONTEXT_CORE_PROFILE_BIT         = 0x00000001,
		CONTEXT_PROFILE_MASK             = 0x9126,
		DEPTH_CLAMP                      = 0x864F,
		FIRST_VERTEX_CONVENTION          = 0x8E4D,
		FRAMEBUFFER_ATTACHMENT_LAYERED   = 0x8DA7,
		FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS = 0x8DA8,
		GEOMETRY_INPUT_TYPE              = 0x8917,
		GEOMETRY_OUTPUT_TYPE             = 0x8918,
		GEOMETRY_SHADER                  = 0x8DD9,
		GEOMETRY_VERTICES_OUT            = 0x8916,
		INT_SAMPLER_2D_MULTISAMPLE       = 0x9109,
		INT_SAMPLER_2D_MULTISAMPLE_ARRAY = 0x910C,
		LAST_VERTEX_CONVENTION           = 0x8E4E,
		LINES_ADJACENCY                  = 0x000A,
		LINE_STRIP_ADJACENCY             = 0x000B,
		MAX_COLOR_TEXTURE_SAMPLES        = 0x910E,
		MAX_DEPTH_TEXTURE_SAMPLES        = 0x910F,
		MAX_FRAGMENT_INPUT_COMPONENTS    = 0x9125,
		MAX_GEOMETRY_INPUT_COMPONENTS    = 0x9123,
		MAX_GEOMETRY_OUTPUT_COMPONENTS   = 0x9124,
		MAX_GEOMETRY_OUTPUT_VERTICES     = 0x8DE0,
		MAX_GEOMETRY_TEXTURE_IMAGE_UNITS = 0x8C29,
		MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS = 0x8DE1,
		MAX_GEOMETRY_UNIFORM_COMPONENTS  = 0x8DDF,
		MAX_INTEGER_SAMPLES              = 0x9110,
		MAX_SAMPLE_MASK_WORDS            = 0x8E59,
		MAX_SERVER_WAIT_TIMEOUT          = 0x9111,
		MAX_VERTEX_OUTPUT_COMPONENTS     = 0x9122,
		OBJECT_TYPE                      = 0x9112,
		PROGRAM_POINT_SIZE               = 0x8642,
		PROVOKING_VERTEX                 = 0x8E4F,
		PROXY_TEXTURE_2D_MULTISAMPLE     = 0x9101,
		PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY = 0x9103,
		QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION = 0x8E4C,
		SAMPLER_2D_MULTISAMPLE           = 0x9108,
		SAMPLER_2D_MULTISAMPLE_ARRAY     = 0x910B,
		SAMPLE_MASK                      = 0x8E51,
		SAMPLE_MASK_VALUE                = 0x8E52,
		SAMPLE_POSITION                  = 0x8E50,
		SIGNALED                         = 0x9119,
		SYNC_CONDITION                   = 0x9113,
		SYNC_FENCE                       = 0x9116,
		SYNC_FLAGS                       = 0x9115,
		SYNC_FLUSH_COMMANDS_BIT          = 0x00000001,
		SYNC_GPU_COMMANDS_COMPLETE       = 0x9117,
		SYNC_STATUS                      = 0x9114,
		TEXTURE_2D_MULTISAMPLE           = 0x9100,
		TEXTURE_2D_MULTISAMPLE_ARRAY     = 0x9102,
		TEXTURE_BINDING_2D_MULTISAMPLE   = 0x9104,
		TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY = 0x9105,
		TEXTURE_CUBE_MAP_SEAMLESS        = 0x884F,
		TEXTURE_FIXED_SAMPLE_LOCATIONS   = 0x9107,
		TEXTURE_SAMPLES                  = 0x9106,
		TIMEOUT_EXPIRED                  = 0x911B,
		TIMEOUT_IGNORED                  = 0xFFFFFFFFFFFFFFFF,
		TRIANGLES_ADJACENCY              = 0x000C,
		TRIANGLE_STRIP_ADJACENCY         = 0x000D,
		UNSIGNALED                       = 0x9118,
		UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE = 0x910A,
		UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = 0x910D,
		WAIT_FAILED_                     = 0x911D,
		
		ANY_SAMPLES_PASSED               = 0x8C2F,
		INT_2_10_10_10_REV               = 0x8D9F,
		MAX_DUAL_SOURCE_DRAW_BUFFERS     = 0x88FC,
		ONE_MINUS_SRC1_ALPHA             = 0x88FB,
		ONE_MINUS_SRC1_COLOR             = 0x88FA,
		RGB10_A2UI                       = 0x906F,
		SAMPLER_BINDING                  = 0x8919,
		SRC1_COLOR                       = 0x88F9,
		TEXTURE_SWIZZLE_A                = 0x8E45,
		TEXTURE_SWIZZLE_B                = 0x8E44,
		TEXTURE_SWIZZLE_G                = 0x8E43,
		TEXTURE_SWIZZLE_R                = 0x8E42,
		TEXTURE_SWIZZLE_RGBA             = 0x8E46,
		TIMESTAMP                        = 0x8E28,
		TIME_ELAPSED                     = 0x88BF,
		VERTEX_ATTRIB_ARRAY_DIVISOR      = 0x88FE,
		
		ACTIVE_SUBROUTINES               = 0x8DE5,
		ACTIVE_SUBROUTINE_MAX_LENGTH     = 0x8E48,
		ACTIVE_SUBROUTINE_UNIFORMS       = 0x8DE6,
		ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS = 0x8E47,
		ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH = 0x8E49,
		COMPATIBLE_SUBROUTINES           = 0x8E4B,
		DOUBLE_MAT2                      = 0x8F46,
		DOUBLE_MAT2x3                    = 0x8F49,
		DOUBLE_MAT2x4                    = 0x8F4A,
		DOUBLE_MAT3                      = 0x8F47,
		DOUBLE_MAT3x2                    = 0x8F4B,
		DOUBLE_MAT3x4                    = 0x8F4C,
		DOUBLE_MAT4                      = 0x8F48,
		DOUBLE_MAT4x2                    = 0x8F4D,
		DOUBLE_MAT4x3                    = 0x8F4E,
		DOUBLE_VEC2                      = 0x8FFC,
		DOUBLE_VEC3                      = 0x8FFD,
		DOUBLE_VEC4                      = 0x8FFE,
		DRAW_INDIRECT_BUFFER             = 0x8F3F,
		DRAW_INDIRECT_BUFFER_BINDING     = 0x8F43,
		FRACTIONAL_EVEN                  = 0x8E7C,
		FRACTIONAL_ODD                   = 0x8E7B,
		FRAGMENT_INTERPOLATION_OFFSET_BITS = 0x8E5D,
		GEOMETRY_SHADER_INVOCATIONS      = 0x887F,
		INT_SAMPLER_CUBE_MAP_ARRAY       = 0x900E,
		ISOLINES                         = 0x8E7A,
		MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS = 0x8E1E,
		MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS = 0x8E1F,
		MAX_FRAGMENT_INTERPOLATION_OFFSET = 0x8E5C,
		MAX_GEOMETRY_SHADER_INVOCATIONS  = 0x8E5A,
		MAX_PATCH_VERTICES               = 0x8E7D,
		MAX_PROGRAM_TEXTURE_GATHER_OFFSET = 0x8E5F,
		MAX_SUBROUTINES                  = 0x8DE7,
		MAX_SUBROUTINE_UNIFORM_LOCATIONS = 0x8DE8,
		MAX_TESS_CONTROL_INPUT_COMPONENTS = 0x886C,
		MAX_TESS_CONTROL_OUTPUT_COMPONENTS = 0x8E83,
		MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS = 0x8E81,
		MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS = 0x8E85,
		MAX_TESS_CONTROL_UNIFORM_BLOCKS  = 0x8E89,
		MAX_TESS_CONTROL_UNIFORM_COMPONENTS = 0x8E7F,
		MAX_TESS_EVALUATION_INPUT_COMPONENTS = 0x886D,
		MAX_TESS_EVALUATION_OUTPUT_COMPONENTS = 0x8E86,
		MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS = 0x8E82,
		MAX_TESS_EVALUATION_UNIFORM_BLOCKS = 0x8E8A,
		MAX_TESS_EVALUATION_UNIFORM_COMPONENTS = 0x8E80,
		MAX_TESS_GEN_LEVEL               = 0x8E7E,
		MAX_TESS_PATCH_COMPONENTS        = 0x8E84,
		MAX_TRANSFORM_FEEDBACK_BUFFERS   = 0x8E70,
		MAX_VERTEX_STREAMS               = 0x8E71,
		MIN_FRAGMENT_INTERPOLATION_OFFSET = 0x8E5B,
		MIN_PROGRAM_TEXTURE_GATHER_OFFSET = 0x8E5E,
		MIN_SAMPLE_SHADING_VALUE         = 0x8C37,
		NUM_COMPATIBLE_SUBROUTINES       = 0x8E4A,
		PATCHES                          = 0x000E,
		PATCH_DEFAULT_INNER_LEVEL        = 0x8E73,
		PATCH_DEFAULT_OUTER_LEVEL        = 0x8E74,
		PATCH_VERTICES                   = 0x8E72,
		PROXY_TEXTURE_CUBE_MAP_ARRAY     = 0x900B,
		SAMPLER_CUBE_MAP_ARRAY           = 0x900C,
		SAMPLER_CUBE_MAP_ARRAY_SHADOW    = 0x900D,
		SAMPLE_SHADING                   = 0x8C36,
		TESS_CONTROL_OUTPUT_VERTICES     = 0x8E75,
		TESS_CONTROL_SHADER              = 0x8E88,
		TESS_EVALUATION_SHADER           = 0x8E87,
		TESS_GEN_MODE                    = 0x8E76,
		TESS_GEN_POINT_MODE              = 0x8E79,
		TESS_GEN_SPACING                 = 0x8E77,
		TESS_GEN_VERTEX_ORDER            = 0x8E78,
		TEXTURE_BINDING_CUBE_MAP_ARRAY   = 0x900A,
		TEXTURE_CUBE_MAP_ARRAY           = 0x9009,
		TRANSFORM_FEEDBACK               = 0x8E22,
		TRANSFORM_FEEDBACK_BINDING       = 0x8E25,
		TRANSFORM_FEEDBACK_BUFFER_ACTIVE = 0x8E24,
		TRANSFORM_FEEDBACK_BUFFER_PAUSED = 0x8E23,
		UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER = 0x84F0,
		UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER = 0x84F1,
		UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY = 0x900F,
		
		ACTIVE_PROGRAM                   = 0x8259,
		ALL_SHADER_BITS                  = 0xFFFFFFFF,
		FIXED                            = 0x140C,
		FRAGMENT_SHADER_BIT              = 0x00000002,
		GEOMETRY_SHADER_BIT              = 0x00000004,
		HIGH_FLOAT                       = 0x8DF2,
		HIGH_INT                         = 0x8DF5,
		IMPLEMENTATION_COLOR_READ_FORMAT = 0x8B9B,
		IMPLEMENTATION_COLOR_READ_TYPE   = 0x8B9A,
		LAYER_PROVOKING_VERTEX           = 0x825E,
		LOW_FLOAT                        = 0x8DF0,
		LOW_INT                          = 0x8DF3,
		MAX_FRAGMENT_UNIFORM_VECTORS     = 0x8DFD,
		MAX_VARYING_VECTORS              = 0x8DFC,
		MAX_VERTEX_UNIFORM_VECTORS       = 0x8DFB,
		MAX_VIEWPORTS                    = 0x825B,
		MEDIUM_FLOAT                     = 0x8DF1,
		MEDIUM_INT                       = 0x8DF4,
		NUM_PROGRAM_BINARY_FORMATS       = 0x87FE,
		NUM_SHADER_BINARY_FORMATS        = 0x8DF9,
		PROGRAM_BINARY_FORMATS           = 0x87FF,
		PROGRAM_BINARY_LENGTH            = 0x8741,
		PROGRAM_BINARY_RETRIEVABLE_HINT  = 0x8257,
		PROGRAM_PIPELINE_BINDING         = 0x825A,
		PROGRAM_SEPARABLE                = 0x8258,
		RGB565                           = 0x8D62,
		SHADER_BINARY_FORMATS            = 0x8DF8,
		SHADER_COMPILER                  = 0x8DFA,
		TESS_CONTROL_SHADER_BIT          = 0x00000008,
		TESS_EVALUATION_SHADER_BIT       = 0x00000010,
		UNDEFINED_VERTEX                 = 0x8260,
		VERTEX_SHADER_BIT                = 0x00000001,
		VIEWPORT_BOUNDS_RANGE            = 0x825D,
		VIEWPORT_INDEX_PROVOKING_VERTEX  = 0x825F,
		VIEWPORT_SUBPIXEL_BITS           = 0x825C,
		
		ACTIVE_ATOMIC_COUNTER_BUFFERS    = 0x92D9,
		ALL_BARRIER_BITS                 = 0xFFFFFFFF,
		ATOMIC_COUNTER_BARRIER_BIT       = 0x00001000,
		ATOMIC_COUNTER_BUFFER            = 0x92C0,
		ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS = 0x92C5,
		ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES = 0x92C6,
		ATOMIC_COUNTER_BUFFER_BINDING    = 0x92C1,
		ATOMIC_COUNTER_BUFFER_DATA_SIZE  = 0x92C4,
		ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER = 0x92CB,
		ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER = 0x92CA,
		ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER = 0x92C8,
		ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER = 0x92C9,
		ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER = 0x92C7,
		ATOMIC_COUNTER_BUFFER_SIZE       = 0x92C3,
		ATOMIC_COUNTER_BUFFER_START      = 0x92C2,
		BUFFER_UPDATE_BARRIER_BIT        = 0x00000200,
		COMMAND_BARRIER_BIT              = 0x00000040,
		COMPRESSED_RGBA_BPTC_UNORM       = 0x8E8C,
		COMPRESSED_RGB_BPTC_SIGNED_FLOAT = 0x8E8E,
		COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT = 0x8E8F,
		COMPRESSED_SRGB_ALPHA_BPTC_UNORM = 0x8E8D,
		COPY_READ_BUFFER_BINDING         = 0x8F36,
		COPY_WRITE_BUFFER_BINDING        = 0x8F37,
		ELEMENT_ARRAY_BARRIER_BIT        = 0x00000002,
		FRAMEBUFFER_BARRIER_BIT          = 0x00000400,
		IMAGE_1D                         = 0x904C,
		IMAGE_1D_ARRAY                   = 0x9052,
		IMAGE_2D                         = 0x904D,
		IMAGE_2D_ARRAY                   = 0x9053,
		IMAGE_2D_MULTISAMPLE             = 0x9055,
		IMAGE_2D_MULTISAMPLE_ARRAY       = 0x9056,
		IMAGE_2D_RECT                    = 0x904F,
		IMAGE_3D                         = 0x904E,
		IMAGE_BINDING_ACCESS             = 0x8F3E,
		IMAGE_BINDING_FORMAT             = 0x906E,
		IMAGE_BINDING_LAYER              = 0x8F3D,
		IMAGE_BINDING_LAYERED            = 0x8F3C,
		IMAGE_BINDING_LEVEL              = 0x8F3B,
		IMAGE_BINDING_NAME               = 0x8F3A,
		IMAGE_BUFFER                     = 0x9051,
		IMAGE_CUBE                       = 0x9050,
		IMAGE_CUBE_MAP_ARRAY             = 0x9054,
		IMAGE_FORMAT_COMPATIBILITY_BY_CLASS = 0x90C9,
		IMAGE_FORMAT_COMPATIBILITY_BY_SIZE = 0x90C8,
		IMAGE_FORMAT_COMPATIBILITY_TYPE  = 0x90C7,
		INT_IMAGE_1D                     = 0x9057,
		INT_IMAGE_1D_ARRAY               = 0x905D,
		INT_IMAGE_2D                     = 0x9058,
		INT_IMAGE_2D_ARRAY               = 0x905E,
		INT_IMAGE_2D_MULTISAMPLE         = 0x9060,
		INT_IMAGE_2D_MULTISAMPLE_ARRAY   = 0x9061,
		INT_IMAGE_2D_RECT                = 0x905A,
		INT_IMAGE_3D                     = 0x9059,
		INT_IMAGE_BUFFER                 = 0x905C,
		INT_IMAGE_CUBE                   = 0x905B,
		INT_IMAGE_CUBE_MAP_ARRAY         = 0x905F,
		MAX_ATOMIC_COUNTER_BUFFER_BINDINGS = 0x92DC,
		MAX_ATOMIC_COUNTER_BUFFER_SIZE   = 0x92D8,
		MAX_COMBINED_ATOMIC_COUNTERS     = 0x92D7,
		MAX_COMBINED_ATOMIC_COUNTER_BUFFERS = 0x92D1,
		MAX_COMBINED_IMAGE_UNIFORMS      = 0x90CF,
		MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS = 0x8F39,
		MAX_FRAGMENT_ATOMIC_COUNTERS     = 0x92D6,
		MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS = 0x92D0,
		MAX_FRAGMENT_IMAGE_UNIFORMS      = 0x90CE,
		MAX_GEOMETRY_ATOMIC_COUNTERS     = 0x92D5,
		MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS = 0x92CF,
		MAX_GEOMETRY_IMAGE_UNIFORMS      = 0x90CD,
		MAX_IMAGE_SAMPLES                = 0x906D,
		MAX_IMAGE_UNITS                  = 0x8F38,
		MAX_TESS_CONTROL_ATOMIC_COUNTERS = 0x92D3,
		MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS = 0x92CD,
		MAX_TESS_CONTROL_IMAGE_UNIFORMS  = 0x90CB,
		MAX_TESS_EVALUATION_ATOMIC_COUNTERS = 0x92D4,
		MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS = 0x92CE,
		MAX_TESS_EVALUATION_IMAGE_UNIFORMS = 0x90CC,
		MAX_VERTEX_ATOMIC_COUNTERS       = 0x92D2,
		MAX_VERTEX_ATOMIC_COUNTER_BUFFERS = 0x92CC,
		MAX_VERTEX_IMAGE_UNIFORMS        = 0x90CA,
		MIN_MAP_BUFFER_ALIGNMENT         = 0x90BC,
		NUM_SAMPLE_COUNTS                = 0x9380,
		PACK_COMPRESSED_BLOCK_DEPTH      = 0x912D,
		PACK_COMPRESSED_BLOCK_HEIGHT     = 0x912C,
		PACK_COMPRESSED_BLOCK_SIZE       = 0x912E,
		PACK_COMPRESSED_BLOCK_WIDTH      = 0x912B,
		PIXEL_BUFFER_BARRIER_BIT         = 0x00000080,
		SHADER_IMAGE_ACCESS_BARRIER_BIT  = 0x00000020,
		TEXTURE_FETCH_BARRIER_BIT        = 0x00000008,
		TEXTURE_IMMUTABLE_FORMAT         = 0x912F,
		TEXTURE_UPDATE_BARRIER_BIT       = 0x00000100,
		TRANSFORM_FEEDBACK_ACTIVE        = 0x8E24,
		TRANSFORM_FEEDBACK_BARRIER_BIT   = 0x00000800,
		TRANSFORM_FEEDBACK_PAUSED        = 0x8E23,
		UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX = 0x92DA,
		UNIFORM_BARRIER_BIT              = 0x00000004,
		UNPACK_COMPRESSED_BLOCK_DEPTH    = 0x9129,
		UNPACK_COMPRESSED_BLOCK_HEIGHT   = 0x9128,
		UNPACK_COMPRESSED_BLOCK_SIZE     = 0x912A,
		UNPACK_COMPRESSED_BLOCK_WIDTH    = 0x9127,
		UNSIGNED_INT_ATOMIC_COUNTER      = 0x92DB,
		UNSIGNED_INT_IMAGE_1D            = 0x9062,
		UNSIGNED_INT_IMAGE_1D_ARRAY      = 0x9068,
		UNSIGNED_INT_IMAGE_2D            = 0x9063,
		UNSIGNED_INT_IMAGE_2D_ARRAY      = 0x9069,
		UNSIGNED_INT_IMAGE_2D_MULTISAMPLE = 0x906B,
		UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY = 0x906C,
		UNSIGNED_INT_IMAGE_2D_RECT       = 0x9065,
		UNSIGNED_INT_IMAGE_3D            = 0x9064,
		UNSIGNED_INT_IMAGE_BUFFER        = 0x9067,
		UNSIGNED_INT_IMAGE_CUBE          = 0x9066,
		UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY = 0x906A,
		VERTEX_ATTRIB_ARRAY_BARRIER_BIT  = 0x00000001,
		
		ACTIVE_RESOURCES                 = 0x92F5,
		ACTIVE_VARIABLES                 = 0x9305,
		ANY_SAMPLES_PASSED_CONSERVATIVE  = 0x8D6A,
		ARRAY_SIZE                       = 0x92FB,
		ARRAY_STRIDE                     = 0x92FE,
		ATOMIC_COUNTER_BUFFER_INDEX      = 0x9301,
		ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER = 0x90ED,
		AUTO_GENERATE_MIPMAP             = 0x8295,
		BLOCK_INDEX                      = 0x92FD,
		BUFFER                           = 0x82E0,
		BUFFER_BINDING                   = 0x9302,
		BUFFER_DATA_SIZE                 = 0x9303,
		BUFFER_VARIABLE                  = 0x92E5,
		CAVEAT_SUPPORT                   = 0x82B8,
		CLEAR_BUFFER                     = 0x82B4,
		COLOR_COMPONENTS                 = 0x8283,
		COLOR_ENCODING                   = 0x8296,
		COLOR_RENDERABLE                 = 0x8286,
		COMPRESSED_R11_EAC               = 0x9270,
		COMPRESSED_RG11_EAC              = 0x9272,
		COMPRESSED_RGB8_ETC2             = 0x9274,
		COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 = 0x9276,
		COMPRESSED_RGBA8_ETC2_EAC        = 0x9278,
		COMPRESSED_SIGNED_R11_EAC        = 0x9271,
		COMPRESSED_SIGNED_RG11_EAC       = 0x9273,
		COMPRESSED_SRGB8_ALPHA8_ETC2_EAC = 0x9279,
		COMPRESSED_SRGB8_ETC2            = 0x9275,
		COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 = 0x9277,
		COMPUTE_SHADER                   = 0x91B9,
		COMPUTE_SHADER_BIT               = 0x00000020,
		COMPUTE_SUBROUTINE               = 0x92ED,
		COMPUTE_SUBROUTINE_UNIFORM       = 0x92F3,
		COMPUTE_TEXTURE                  = 0x82A0,
		COMPUTE_WORK_GROUP_SIZE          = 0x8267,
		CONTEXT_FLAG_DEBUG_BIT           = 0x00000002,
		DEBUG_CALLBACK_FUNCTION          = 0x8244,
		DEBUG_CALLBACK_USER_PARAM        = 0x8245,
		DEBUG_GROUP_STACK_DEPTH          = 0x826D,
		DEBUG_LOGGED_MESSAGES            = 0x9145,
		DEBUG_NEXT_LOGGED_MESSAGE_LENGTH = 0x8243,
		DEBUG_OUTPUT                     = 0x92E0,
		DEBUG_OUTPUT_SYNCHRONOUS         = 0x8242,
		DEBUG_SEVERITY_HIGH              = 0x9146,
		DEBUG_SEVERITY_LOW               = 0x9148,
		DEBUG_SEVERITY_MEDIUM            = 0x9147,
		DEBUG_SEVERITY_NOTIFICATION      = 0x826B,
		DEBUG_SOURCE_API                 = 0x8246,
		DEBUG_SOURCE_APPLICATION         = 0x824A,
		DEBUG_SOURCE_OTHER               = 0x824B,
		DEBUG_SOURCE_SHADER_COMPILER     = 0x8248,
		DEBUG_SOURCE_THIRD_PARTY         = 0x8249,
		DEBUG_SOURCE_WINDOW_SYSTEM       = 0x8247,
		DEBUG_TYPE_DEPRECATED_BEHAVIOR   = 0x824D,
		DEBUG_TYPE_ERROR                 = 0x824C,
		DEBUG_TYPE_MARKER                = 0x8268,
		DEBUG_TYPE_OTHER                 = 0x8251,
		DEBUG_TYPE_PERFORMANCE           = 0x8250,
		DEBUG_TYPE_POP_GROUP             = 0x826A,
		DEBUG_TYPE_PORTABILITY           = 0x824F,
		DEBUG_TYPE_PUSH_GROUP            = 0x8269,
		DEBUG_TYPE_UNDEFINED_BEHAVIOR    = 0x824E,
		DEPTH_COMPONENTS                 = 0x8284,
		DEPTH_RENDERABLE                 = 0x8287,
		DEPTH_STENCIL_TEXTURE_MODE       = 0x90EA,
		DISPATCH_INDIRECT_BUFFER         = 0x90EE,
		DISPATCH_INDIRECT_BUFFER_BINDING = 0x90EF,
		FILTER                           = 0x829A,
		FRAGMENT_SUBROUTINE              = 0x92EC,
		FRAGMENT_SUBROUTINE_UNIFORM      = 0x92F2,
		FRAGMENT_TEXTURE                 = 0x829F,
		FRAMEBUFFER_BLEND                = 0x828B,
		FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS = 0x9314,
		FRAMEBUFFER_DEFAULT_HEIGHT       = 0x9311,
		FRAMEBUFFER_DEFAULT_LAYERS       = 0x9312,
		FRAMEBUFFER_DEFAULT_SAMPLES      = 0x9313,
		FRAMEBUFFER_DEFAULT_WIDTH        = 0x9310,
		FRAMEBUFFER_RENDERABLE           = 0x8289,
		FRAMEBUFFER_RENDERABLE_LAYERED   = 0x828A,
		FULL_SUPPORT                     = 0x82B7,
		GEOMETRY_SUBROUTINE              = 0x92EB,
		GEOMETRY_SUBROUTINE_UNIFORM      = 0x92F1,
		GEOMETRY_TEXTURE                 = 0x829E,
		GET_TEXTURE_IMAGE_FORMAT         = 0x8291,
		GET_TEXTURE_IMAGE_TYPE           = 0x8292,
		IMAGE_CLASS_10_10_10_2           = 0x82C3,
		IMAGE_CLASS_11_11_10             = 0x82C2,
		IMAGE_CLASS_1_X_16               = 0x82BE,
		IMAGE_CLASS_1_X_32               = 0x82BB,
		IMAGE_CLASS_1_X_8                = 0x82C1,
		IMAGE_CLASS_2_X_16               = 0x82BD,
		IMAGE_CLASS_2_X_32               = 0x82BA,
		IMAGE_CLASS_2_X_8                = 0x82C0,
		IMAGE_CLASS_4_X_16               = 0x82BC,
		IMAGE_CLASS_4_X_32               = 0x82B9,
		IMAGE_CLASS_4_X_8                = 0x82BF,
		IMAGE_COMPATIBILITY_CLASS        = 0x82A8,
		IMAGE_PIXEL_FORMAT               = 0x82A9,
		IMAGE_PIXEL_TYPE                 = 0x82AA,
		IMAGE_TEXEL_SIZE                 = 0x82A7,
		INTERNALFORMAT_ALPHA_SIZE        = 0x8274,
		INTERNALFORMAT_ALPHA_TYPE        = 0x827B,
		INTERNALFORMAT_BLUE_SIZE         = 0x8273,
		INTERNALFORMAT_BLUE_TYPE         = 0x827A,
		INTERNALFORMAT_DEPTH_SIZE        = 0x8275,
		INTERNALFORMAT_DEPTH_TYPE        = 0x827C,
		INTERNALFORMAT_GREEN_SIZE        = 0x8272,
		INTERNALFORMAT_GREEN_TYPE        = 0x8279,
		INTERNALFORMAT_PREFERRED         = 0x8270,
		INTERNALFORMAT_RED_SIZE          = 0x8271,
		INTERNALFORMAT_RED_TYPE          = 0x8278,
		INTERNALFORMAT_SHARED_SIZE       = 0x8277,
		INTERNALFORMAT_STENCIL_SIZE      = 0x8276,
		INTERNALFORMAT_STENCIL_TYPE      = 0x827D,
		INTERNALFORMAT_SUPPORTED         = 0x826F,
		IS_PER_PATCH                     = 0x92E7,
		IS_ROW_MAJOR                     = 0x9300,
		LOCATION                         = 0x930E,
		LOCATION_INDEX                   = 0x930F,
		MANUAL_GENERATE_MIPMAP           = 0x8294,
		MATRIX_STRIDE                    = 0x92FF,
		MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS = 0x8266,
		MAX_COMBINED_DIMENSIONS          = 0x8282,
		MAX_COMBINED_SHADER_OUTPUT_RESOURCES = 0x8F39,
		MAX_COMBINED_SHADER_STORAGE_BLOCKS = 0x90DC,
		MAX_COMPUTE_ATOMIC_COUNTERS      = 0x8265,
		MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS = 0x8264,
		MAX_COMPUTE_IMAGE_UNIFORMS       = 0x91BD,
		MAX_COMPUTE_SHADER_STORAGE_BLOCKS = 0x90DB,
		MAX_COMPUTE_SHARED_MEMORY_SIZE   = 0x8262,
		MAX_COMPUTE_TEXTURE_IMAGE_UNITS  = 0x91BC,
		MAX_COMPUTE_UNIFORM_BLOCKS       = 0x91BB,
		MAX_COMPUTE_UNIFORM_COMPONENTS   = 0x8263,
		MAX_COMPUTE_WORK_GROUP_COUNT     = 0x91BE,
		MAX_COMPUTE_WORK_GROUP_INVOCATIONS = 0x90EB,
		MAX_COMPUTE_WORK_GROUP_SIZE      = 0x91BF,
		MAX_DEBUG_GROUP_STACK_DEPTH      = 0x826C,
		MAX_DEBUG_LOGGED_MESSAGES        = 0x9144,
		MAX_DEBUG_MESSAGE_LENGTH         = 0x9143,
		MAX_DEPTH                        = 0x8280,
		MAX_ELEMENT_INDEX                = 0x8D6B,
		MAX_FRAGMENT_SHADER_STORAGE_BLOCKS = 0x90DA,
		MAX_FRAMEBUFFER_HEIGHT           = 0x9316,
		MAX_FRAMEBUFFER_LAYERS           = 0x9317,
		MAX_FRAMEBUFFER_SAMPLES          = 0x9318,
		MAX_FRAMEBUFFER_WIDTH            = 0x9315,
		MAX_GEOMETRY_SHADER_STORAGE_BLOCKS = 0x90D7,
		MAX_HEIGHT                       = 0x827F,
		MAX_LABEL_LENGTH                 = 0x82E8,
		MAX_LAYERS                       = 0x8281,
		MAX_NAME_LENGTH                  = 0x92F6,
		MAX_NUM_ACTIVE_VARIABLES         = 0x92F7,
		MAX_NUM_COMPATIBLE_SUBROUTINES   = 0x92F8,
		MAX_SHADER_STORAGE_BLOCK_SIZE    = 0x90DE,
		MAX_SHADER_STORAGE_BUFFER_BINDINGS = 0x90DD,
		MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS = 0x90D8,
		MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS = 0x90D9,
		MAX_UNIFORM_LOCATIONS            = 0x826E,
		MAX_VERTEX_ATTRIB_BINDINGS       = 0x82DA,
		MAX_VERTEX_ATTRIB_RELATIVE_OFFSET = 0x82D9,
		MAX_VERTEX_SHADER_STORAGE_BLOCKS = 0x90D6,
		MAX_WIDTH                        = 0x827E,
		MIPMAP                           = 0x8293,
		NAME_LENGTH                      = 0x92F9,
		NUM_ACTIVE_VARIABLES             = 0x9304,
		NUM_SHADING_LANGUAGE_VERSIONS    = 0x82E9,
		OFFSET                           = 0x92FC,
		PRIMITIVE_RESTART_FIXED_INDEX    = 0x8D69,
		PROGRAM                          = 0x82E2,
		PROGRAM_INPUT                    = 0x92E3,
		PROGRAM_OUTPUT                   = 0x92E4,
		PROGRAM_PIPELINE                 = 0x82E4,
		QUERY                            = 0x82E3,
		READ_PIXELS                      = 0x828C,
		READ_PIXELS_FORMAT               = 0x828D,
		READ_PIXELS_TYPE                 = 0x828E,
		REFERENCED_BY_COMPUTE_SHADER     = 0x930B,
		REFERENCED_BY_FRAGMENT_SHADER    = 0x930A,
		REFERENCED_BY_GEOMETRY_SHADER    = 0x9309,
		REFERENCED_BY_TESS_CONTROL_SHADER = 0x9307,
		REFERENCED_BY_TESS_EVALUATION_SHADER = 0x9308,
		REFERENCED_BY_VERTEX_SHADER      = 0x9306,
		SAMPLER                          = 0x82E6,
		SHADER                           = 0x82E1,
		SHADER_IMAGE_ATOMIC              = 0x82A6,
		SHADER_IMAGE_LOAD                = 0x82A4,
		SHADER_IMAGE_STORE               = 0x82A5,
		SHADER_STORAGE_BARRIER_BIT       = 0x00002000,
		SHADER_STORAGE_BLOCK             = 0x92E6,
		SHADER_STORAGE_BUFFER            = 0x90D2,
		SHADER_STORAGE_BUFFER_BINDING    = 0x90D3,
		SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT = 0x90DF,
		SHADER_STORAGE_BUFFER_SIZE       = 0x90D5,
		SHADER_STORAGE_BUFFER_START      = 0x90D4,
		SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST = 0x82AC,
		SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE = 0x82AE,
		SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST = 0x82AD,
		SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE = 0x82AF,
		SRGB_READ                        = 0x8297,
		SRGB_WRITE                       = 0x8298,
		STENCIL_COMPONENTS               = 0x8285,
		STENCIL_RENDERABLE               = 0x8288,
		TESS_CONTROL_SUBROUTINE          = 0x92E9,
		TESS_CONTROL_SUBROUTINE_UNIFORM  = 0x92EF,
		TESS_CONTROL_TEXTURE             = 0x829C,
		TESS_EVALUATION_SUBROUTINE       = 0x92EA,
		TESS_EVALUATION_SUBROUTINE_UNIFORM = 0x92F0,
		TESS_EVALUATION_TEXTURE          = 0x829D,
		TEXTURE_BUFFER_OFFSET            = 0x919D,
		TEXTURE_BUFFER_OFFSET_ALIGNMENT  = 0x919F,
		TEXTURE_BUFFER_SIZE              = 0x919E,
		TEXTURE_COMPRESSED_BLOCK_HEIGHT  = 0x82B2,
		TEXTURE_COMPRESSED_BLOCK_SIZE    = 0x82B3,
		TEXTURE_COMPRESSED_BLOCK_WIDTH   = 0x82B1,
		TEXTURE_GATHER                   = 0x82A2,
		TEXTURE_GATHER_SHADOW            = 0x82A3,
		TEXTURE_IMAGE_FORMAT             = 0x828F,
		TEXTURE_IMAGE_TYPE               = 0x8290,
		TEXTURE_IMMUTABLE_LEVELS         = 0x82DF,
		TEXTURE_SHADOW                   = 0x82A1,
		TEXTURE_VIEW                     = 0x82B5,
		TEXTURE_VIEW_MIN_LAYER           = 0x82DD,
		TEXTURE_VIEW_MIN_LEVEL           = 0x82DB,
		TEXTURE_VIEW_NUM_LAYERS          = 0x82DE,
		TEXTURE_VIEW_NUM_LEVELS          = 0x82DC,
		TOP_LEVEL_ARRAY_SIZE             = 0x930C,
		TOP_LEVEL_ARRAY_STRIDE           = 0x930D,
		TRANSFORM_FEEDBACK_VARYING       = 0x92F4,
		TYPE                             = 0x92FA,
		UNIFORM                          = 0x92E1,
		UNIFORM_BLOCK                    = 0x92E2,
		UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER = 0x90EC,
		VERTEX_ATTRIB_ARRAY_LONG         = 0x874E,
		VERTEX_ATTRIB_BINDING            = 0x82D4,
		VERTEX_ATTRIB_RELATIVE_OFFSET    = 0x82D5,
		VERTEX_BINDING_BUFFER            = 0x8F4F,
		VERTEX_BINDING_DIVISOR           = 0x82D6,
		VERTEX_BINDING_OFFSET            = 0x82D7,
		VERTEX_BINDING_STRIDE            = 0x82D8,
		VERTEX_SUBROUTINE                = 0x92E8,
		VERTEX_SUBROUTINE_UNIFORM        = 0x92EE,
		VERTEX_TEXTURE                   = 0x829B,
		VIEW_CLASS_128_BITS              = 0x82C4,
		VIEW_CLASS_16_BITS               = 0x82CA,
		VIEW_CLASS_24_BITS               = 0x82C9,
		VIEW_CLASS_32_BITS               = 0x82C8,
		VIEW_CLASS_48_BITS               = 0x82C7,
		VIEW_CLASS_64_BITS               = 0x82C6,
		VIEW_CLASS_8_BITS                = 0x82CB,
		VIEW_CLASS_96_BITS               = 0x82C5,
		VIEW_CLASS_BPTC_FLOAT            = 0x82D3,
		VIEW_CLASS_BPTC_UNORM            = 0x82D2,
		VIEW_CLASS_RGTC1_RED             = 0x82D0,
		VIEW_CLASS_RGTC2_RG              = 0x82D1,
		VIEW_CLASS_S3TC_DXT1_RGB         = 0x82CC,
		VIEW_CLASS_S3TC_DXT1_RGBA        = 0x82CD,
		VIEW_CLASS_S3TC_DXT3_RGBA        = 0x82CE,
		VIEW_CLASS_S3TC_DXT5_RGBA        = 0x82CF,
		VIEW_COMPATIBILITY_CLASS         = 0x82B6,
		
		BUFFER_IMMUTABLE_STORAGE         = 0x821F,
		BUFFER_STORAGE_FLAGS             = 0x8220,
		CLEAR_TEXTURE                    = 0x9365,
		CLIENT_MAPPED_BUFFER_BARRIER_BIT = 0x00004000,
		CLIENT_STORAGE_BIT               = 0x0200,
		DYNAMIC_STORAGE_BIT              = 0x0100,
		LOCATION_COMPONENT               = 0x934A,
		MAP_COHERENT_BIT                 = 0x0080,
		MAP_PERSISTENT_BIT               = 0x0040,
		MAX_VERTEX_ATTRIB_STRIDE         = 0x82E5,
		MIRROR_CLAMP_TO_EDGE             = 0x8743,
		PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED = 0x8221,
		QUERY_BUFFER                     = 0x9192,
		QUERY_BUFFER_BARRIER_BIT         = 0x00008000,
		QUERY_BUFFER_BINDING             = 0x9193,
		QUERY_RESULT_NO_WAIT             = 0x9194,
		TEXTURE_BUFFER_BINDING           = 0x8C2A,
		TRANSFORM_FEEDBACK_BUFFER_INDEX  = 0x934B,
		TRANSFORM_FEEDBACK_BUFFER_STRIDE = 0x934C,
		
		CLIP_DEPTH_MODE                  = 0x935D,
		CLIP_ORIGIN                      = 0x935C,
		CONTEXT_FLAG_ROBUST_ACCESS_BIT   = 0x00000004,
		CONTEXT_LOST                     = 0x0507,
		CONTEXT_RELEASE_BEHAVIOR         = 0x82FB,
		CONTEXT_RELEASE_BEHAVIOR_FLUSH   = 0x82FC,
		GUILTY_CONTEXT_RESET             = 0x8253,
		INNOCENT_CONTEXT_RESET           = 0x8254,
		LOSE_CONTEXT_ON_RESET            = 0x8252,
		MAX_COMBINED_CLIP_AND_CULL_DISTANCES = 0x82FA,
		MAX_CULL_DISTANCES               = 0x82F9,
		NEGATIVE_ONE_TO_ONE              = 0x935E,
		NO_RESET_NOTIFICATION            = 0x8261,
		QUERY_BY_REGION_NO_WAIT_INVERTED = 0x8E1A,
		QUERY_BY_REGION_WAIT_INVERTED    = 0x8E19,
		QUERY_NO_WAIT_INVERTED           = 0x8E18,
		QUERY_TARGET                     = 0x82EA,
		QUERY_WAIT_INVERTED              = 0x8E17,
		RESET_NOTIFICATION_STRATEGY      = 0x8256,
		TEXTURE_TARGET                   = 0x1006,
		UNKNOWN_CONTEXT_RESET            = 0x8255,
		ZERO_TO_ONE                      = 0x935F,
		
	};
	
	namespace _detail
	{
		extern void (CODEGEN_FUNCPTR *Accum)(GLenum op, GLfloat value);
		extern void (CODEGEN_FUNCPTR *AlphaFunc)(GLenum func, GLfloat ref);
		extern void (CODEGEN_FUNCPTR *Begin)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *Bitmap)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap);
		extern void (CODEGEN_FUNCPTR *BlendFunc)(GLenum sfactor, GLenum dfactor);
		extern void (CODEGEN_FUNCPTR *CallList)(GLuint list);
		extern void (CODEGEN_FUNCPTR *CallLists)(GLsizei n, GLenum type, const void * lists);
		extern void (CODEGEN_FUNCPTR *Clear)(GLbitfield mask);
		extern void (CODEGEN_FUNCPTR *ClearAccum)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		extern void (CODEGEN_FUNCPTR *ClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		extern void (CODEGEN_FUNCPTR *ClearDepth)(GLdouble depth);
		extern void (CODEGEN_FUNCPTR *ClearIndex)(GLfloat c);
		extern void (CODEGEN_FUNCPTR *ClearStencil)(GLint s);
		extern void (CODEGEN_FUNCPTR *ClipPlane)(GLenum plane, const GLdouble * equation);
		extern void (CODEGEN_FUNCPTR *Color3b)(GLbyte red, GLbyte green, GLbyte blue);
		extern void (CODEGEN_FUNCPTR *Color3bv)(const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *Color3d)(GLdouble red, GLdouble green, GLdouble blue);
		extern void (CODEGEN_FUNCPTR *Color3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *Color3f)(GLfloat red, GLfloat green, GLfloat blue);
		extern void (CODEGEN_FUNCPTR *Color3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *Color3i)(GLint red, GLint green, GLint blue);
		extern void (CODEGEN_FUNCPTR *Color3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *Color3s)(GLshort red, GLshort green, GLshort blue);
		extern void (CODEGEN_FUNCPTR *Color3sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *Color3ub)(GLubyte red, GLubyte green, GLubyte blue);
		extern void (CODEGEN_FUNCPTR *Color3ubv)(const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *Color3ui)(GLuint red, GLuint green, GLuint blue);
		extern void (CODEGEN_FUNCPTR *Color3uiv)(const GLuint * v);
		extern void (CODEGEN_FUNCPTR *Color3us)(GLushort red, GLushort green, GLushort blue);
		extern void (CODEGEN_FUNCPTR *Color3usv)(const GLushort * v);
		extern void (CODEGEN_FUNCPTR *Color4b)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
		extern void (CODEGEN_FUNCPTR *Color4bv)(const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *Color4d)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
		extern void (CODEGEN_FUNCPTR *Color4dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *Color4f)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		extern void (CODEGEN_FUNCPTR *Color4fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *Color4i)(GLint red, GLint green, GLint blue, GLint alpha);
		extern void (CODEGEN_FUNCPTR *Color4iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *Color4s)(GLshort red, GLshort green, GLshort blue, GLshort alpha);
		extern void (CODEGEN_FUNCPTR *Color4sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *Color4ub)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
		extern void (CODEGEN_FUNCPTR *Color4ubv)(const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *Color4ui)(GLuint red, GLuint green, GLuint blue, GLuint alpha);
		extern void (CODEGEN_FUNCPTR *Color4uiv)(const GLuint * v);
		extern void (CODEGEN_FUNCPTR *Color4us)(GLushort red, GLushort green, GLushort blue, GLushort alpha);
		extern void (CODEGEN_FUNCPTR *Color4usv)(const GLushort * v);
		extern void (CODEGEN_FUNCPTR *ColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
		extern void (CODEGEN_FUNCPTR *ColorMaterial)(GLenum face, GLenum mode);
		extern void (CODEGEN_FUNCPTR *CopyPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
		extern void (CODEGEN_FUNCPTR *CullFace)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *DeleteLists)(GLuint list, GLsizei range);
		extern void (CODEGEN_FUNCPTR *DepthFunc)(GLenum func);
		extern void (CODEGEN_FUNCPTR *DepthMask)(GLboolean flag);
		extern void (CODEGEN_FUNCPTR *DepthRange)(GLdouble ren_near, GLdouble ren_far);
		extern void (CODEGEN_FUNCPTR *Disable)(GLenum cap);
		extern void (CODEGEN_FUNCPTR *DrawBuffer)(GLenum buf);
		extern void (CODEGEN_FUNCPTR *DrawPixels)(GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *EdgeFlag)(GLboolean flag);
		extern void (CODEGEN_FUNCPTR *EdgeFlagv)(const GLboolean * flag);
		extern void (CODEGEN_FUNCPTR *Enable)(GLenum cap);
		extern void (CODEGEN_FUNCPTR *End)(void);
		extern void (CODEGEN_FUNCPTR *EndList)(void);
		extern void (CODEGEN_FUNCPTR *EvalCoord1d)(GLdouble u);
		extern void (CODEGEN_FUNCPTR *EvalCoord1dv)(const GLdouble * u);
		extern void (CODEGEN_FUNCPTR *EvalCoord1f)(GLfloat u);
		extern void (CODEGEN_FUNCPTR *EvalCoord1fv)(const GLfloat * u);
		extern void (CODEGEN_FUNCPTR *EvalCoord2d)(GLdouble u, GLdouble v);
		extern void (CODEGEN_FUNCPTR *EvalCoord2dv)(const GLdouble * u);
		extern void (CODEGEN_FUNCPTR *EvalCoord2f)(GLfloat u, GLfloat v);
		extern void (CODEGEN_FUNCPTR *EvalCoord2fv)(const GLfloat * u);
		extern void (CODEGEN_FUNCPTR *EvalMesh1)(GLenum mode, GLint i1, GLint i2);
		extern void (CODEGEN_FUNCPTR *EvalMesh2)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
		extern void (CODEGEN_FUNCPTR *EvalPoint1)(GLint i);
		extern void (CODEGEN_FUNCPTR *EvalPoint2)(GLint i, GLint j);
		extern void (CODEGEN_FUNCPTR *FeedbackBuffer)(GLsizei size, GLenum type, GLfloat * buffer);
		extern void (CODEGEN_FUNCPTR *Finish)(void);
		extern void (CODEGEN_FUNCPTR *Flush)(void);
		extern void (CODEGEN_FUNCPTR *Fogf)(GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *Fogfv)(GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *Fogi)(GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *Fogiv)(GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *FrontFace)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *Frustum)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
		extern GLuint (CODEGEN_FUNCPTR *GenLists)(GLsizei range);
		extern void (CODEGEN_FUNCPTR *GetBooleanv)(GLenum pname, GLboolean * data);
		extern void (CODEGEN_FUNCPTR *GetClipPlane)(GLenum plane, GLdouble * equation);
		extern void (CODEGEN_FUNCPTR *GetDoublev)(GLenum pname, GLdouble * data);
		extern GLenum (CODEGEN_FUNCPTR *GetError)(void);
		extern void (CODEGEN_FUNCPTR *GetFloatv)(GLenum pname, GLfloat * data);
		extern void (CODEGEN_FUNCPTR *GetIntegerv)(GLenum pname, GLint * data);
		extern void (CODEGEN_FUNCPTR *GetLightfv)(GLenum light, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetLightiv)(GLenum light, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetMapdv)(GLenum target, GLenum query, GLdouble * v);
		extern void (CODEGEN_FUNCPTR *GetMapfv)(GLenum target, GLenum query, GLfloat * v);
		extern void (CODEGEN_FUNCPTR *GetMapiv)(GLenum target, GLenum query, GLint * v);
		extern void (CODEGEN_FUNCPTR *GetMaterialfv)(GLenum face, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetMaterialiv)(GLenum face, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetPixelMapfv)(GLenum map, GLfloat * values);
		extern void (CODEGEN_FUNCPTR *GetPixelMapuiv)(GLenum map, GLuint * values);
		extern void (CODEGEN_FUNCPTR *GetPixelMapusv)(GLenum map, GLushort * values);
		extern void (CODEGEN_FUNCPTR *GetPolygonStipple)(GLubyte * mask);
		extern const GLubyte * (CODEGEN_FUNCPTR *GetString)(GLenum name);
		extern void (CODEGEN_FUNCPTR *GetTexEnvfv)(GLenum target, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetTexEnviv)(GLenum target, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetTexGendv)(GLenum coord, GLenum pname, GLdouble * params);
		extern void (CODEGEN_FUNCPTR *GetTexGenfv)(GLenum coord, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetTexGeniv)(GLenum coord, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetTexImage)(GLenum target, GLint level, GLenum format, GLenum type, void * pixels);
		extern void (CODEGEN_FUNCPTR *GetTexLevelParameterfv)(GLenum target, GLint level, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetTexLevelParameteriv)(GLenum target, GLint level, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetTexParameterfv)(GLenum target, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetTexParameteriv)(GLenum target, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *Hint)(GLenum target, GLenum mode);
		extern void (CODEGEN_FUNCPTR *IndexMask)(GLuint mask);
		extern void (CODEGEN_FUNCPTR *Indexd)(GLdouble c);
		extern void (CODEGEN_FUNCPTR *Indexdv)(const GLdouble * c);
		extern void (CODEGEN_FUNCPTR *Indexf)(GLfloat c);
		extern void (CODEGEN_FUNCPTR *Indexfv)(const GLfloat * c);
		extern void (CODEGEN_FUNCPTR *Indexi)(GLint c);
		extern void (CODEGEN_FUNCPTR *Indexiv)(const GLint * c);
		extern void (CODEGEN_FUNCPTR *Indexs)(GLshort c);
		extern void (CODEGEN_FUNCPTR *Indexsv)(const GLshort * c);
		extern void (CODEGEN_FUNCPTR *InitNames)(void);
		extern GLboolean (CODEGEN_FUNCPTR *IsEnabled)(GLenum cap);
		extern GLboolean (CODEGEN_FUNCPTR *IsList)(GLuint list);
		extern void (CODEGEN_FUNCPTR *LightModelf)(GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *LightModelfv)(GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *LightModeli)(GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *LightModeliv)(GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *Lightf)(GLenum light, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *Lightfv)(GLenum light, GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *Lighti)(GLenum light, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *Lightiv)(GLenum light, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *LineStipple)(GLint factor, GLushort pattern);
		extern void (CODEGEN_FUNCPTR *LineWidth)(GLfloat width);
		extern void (CODEGEN_FUNCPTR *ListBase)(GLuint base);
		extern void (CODEGEN_FUNCPTR *LoadIdentity)(void);
		extern void (CODEGEN_FUNCPTR *LoadMatrixd)(const GLdouble * m);
		extern void (CODEGEN_FUNCPTR *LoadMatrixf)(const GLfloat * m);
		extern void (CODEGEN_FUNCPTR *LoadName)(GLuint name);
		extern void (CODEGEN_FUNCPTR *LogicOp)(GLenum opcode);
		extern void (CODEGEN_FUNCPTR *Map1d)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points);
		extern void (CODEGEN_FUNCPTR *Map1f)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points);
		extern void (CODEGEN_FUNCPTR *Map2d)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points);
		extern void (CODEGEN_FUNCPTR *Map2f)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points);
		extern void (CODEGEN_FUNCPTR *MapGrid1d)(GLint un, GLdouble u1, GLdouble u2);
		extern void (CODEGEN_FUNCPTR *MapGrid1f)(GLint un, GLfloat u1, GLfloat u2);
		extern void (CODEGEN_FUNCPTR *MapGrid2d)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
		extern void (CODEGEN_FUNCPTR *MapGrid2f)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
		extern void (CODEGEN_FUNCPTR *Materialf)(GLenum face, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *Materialfv)(GLenum face, GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *Materiali)(GLenum face, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *Materialiv)(GLenum face, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *MatrixMode)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *MultMatrixd)(const GLdouble * m);
		extern void (CODEGEN_FUNCPTR *MultMatrixf)(const GLfloat * m);
		extern void (CODEGEN_FUNCPTR *NewList)(GLuint list, GLenum mode);
		extern void (CODEGEN_FUNCPTR *Normal3b)(GLbyte nx, GLbyte ny, GLbyte nz);
		extern void (CODEGEN_FUNCPTR *Normal3bv)(const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *Normal3d)(GLdouble nx, GLdouble ny, GLdouble nz);
		extern void (CODEGEN_FUNCPTR *Normal3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *Normal3f)(GLfloat nx, GLfloat ny, GLfloat nz);
		extern void (CODEGEN_FUNCPTR *Normal3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *Normal3i)(GLint nx, GLint ny, GLint nz);
		extern void (CODEGEN_FUNCPTR *Normal3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *Normal3s)(GLshort nx, GLshort ny, GLshort nz);
		extern void (CODEGEN_FUNCPTR *Normal3sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *Ortho)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
		extern void (CODEGEN_FUNCPTR *PassThrough)(GLfloat token);
		extern void (CODEGEN_FUNCPTR *PixelMapfv)(GLenum map, GLsizei mapsize, const GLfloat * values);
		extern void (CODEGEN_FUNCPTR *PixelMapuiv)(GLenum map, GLsizei mapsize, const GLuint * values);
		extern void (CODEGEN_FUNCPTR *PixelMapusv)(GLenum map, GLsizei mapsize, const GLushort * values);
		extern void (CODEGEN_FUNCPTR *PixelStoref)(GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *PixelStorei)(GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *PixelTransferf)(GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *PixelTransferi)(GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *PixelZoom)(GLfloat xfactor, GLfloat yfactor);
		extern void (CODEGEN_FUNCPTR *PointSize)(GLfloat size);
		extern void (CODEGEN_FUNCPTR *PolygonMode)(GLenum face, GLenum mode);
		extern void (CODEGEN_FUNCPTR *PolygonStipple)(const GLubyte * mask);
		extern void (CODEGEN_FUNCPTR *PopAttrib)(void);
		extern void (CODEGEN_FUNCPTR *PopMatrix)(void);
		extern void (CODEGEN_FUNCPTR *PopName)(void);
		extern void (CODEGEN_FUNCPTR *PushAttrib)(GLbitfield mask);
		extern void (CODEGEN_FUNCPTR *PushMatrix)(void);
		extern void (CODEGEN_FUNCPTR *PushName)(GLuint name);
		extern void (CODEGEN_FUNCPTR *RasterPos2d)(GLdouble x, GLdouble y);
		extern void (CODEGEN_FUNCPTR *RasterPos2dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *RasterPos2f)(GLfloat x, GLfloat y);
		extern void (CODEGEN_FUNCPTR *RasterPos2fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *RasterPos2i)(GLint x, GLint y);
		extern void (CODEGEN_FUNCPTR *RasterPos2iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *RasterPos2s)(GLshort x, GLshort y);
		extern void (CODEGEN_FUNCPTR *RasterPos2sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *RasterPos3d)(GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *RasterPos3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *RasterPos3f)(GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *RasterPos3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *RasterPos3i)(GLint x, GLint y, GLint z);
		extern void (CODEGEN_FUNCPTR *RasterPos3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *RasterPos3s)(GLshort x, GLshort y, GLshort z);
		extern void (CODEGEN_FUNCPTR *RasterPos3sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *RasterPos4d)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		extern void (CODEGEN_FUNCPTR *RasterPos4dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *RasterPos4f)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		extern void (CODEGEN_FUNCPTR *RasterPos4fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *RasterPos4i)(GLint x, GLint y, GLint z, GLint w);
		extern void (CODEGEN_FUNCPTR *RasterPos4iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *RasterPos4s)(GLshort x, GLshort y, GLshort z, GLshort w);
		extern void (CODEGEN_FUNCPTR *RasterPos4sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *ReadBuffer)(GLenum src);
		extern void (CODEGEN_FUNCPTR *ReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels);
		extern void (CODEGEN_FUNCPTR *Rectd)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
		extern void (CODEGEN_FUNCPTR *Rectdv)(const GLdouble * v1, const GLdouble * v2);
		extern void (CODEGEN_FUNCPTR *Rectf)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
		extern void (CODEGEN_FUNCPTR *Rectfv)(const GLfloat * v1, const GLfloat * v2);
		extern void (CODEGEN_FUNCPTR *Recti)(GLint x1, GLint y1, GLint x2, GLint y2);
		extern void (CODEGEN_FUNCPTR *Rectiv)(const GLint * v1, const GLint * v2);
		extern void (CODEGEN_FUNCPTR *Rects)(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
		extern void (CODEGEN_FUNCPTR *Rectsv)(const GLshort * v1, const GLshort * v2);
		extern GLint (CODEGEN_FUNCPTR *RenderMode)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *Rotated)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *Rotatef)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *Scaled)(GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *Scalef)(GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *Scissor)(GLint x, GLint y, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *SelectBuffer)(GLsizei size, GLuint * buffer);
		extern void (CODEGEN_FUNCPTR *ShadeModel)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *StencilFunc)(GLenum func, GLint ref, GLuint mask);
		extern void (CODEGEN_FUNCPTR *StencilMask)(GLuint mask);
		extern void (CODEGEN_FUNCPTR *StencilOp)(GLenum fail, GLenum zfail, GLenum zpass);
		extern void (CODEGEN_FUNCPTR *TexCoord1d)(GLdouble s);
		extern void (CODEGEN_FUNCPTR *TexCoord1dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *TexCoord1f)(GLfloat s);
		extern void (CODEGEN_FUNCPTR *TexCoord1fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *TexCoord1i)(GLint s);
		extern void (CODEGEN_FUNCPTR *TexCoord1iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *TexCoord1s)(GLshort s);
		extern void (CODEGEN_FUNCPTR *TexCoord1sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *TexCoord2d)(GLdouble s, GLdouble t);
		extern void (CODEGEN_FUNCPTR *TexCoord2dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *TexCoord2f)(GLfloat s, GLfloat t);
		extern void (CODEGEN_FUNCPTR *TexCoord2fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *TexCoord2i)(GLint s, GLint t);
		extern void (CODEGEN_FUNCPTR *TexCoord2iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *TexCoord2s)(GLshort s, GLshort t);
		extern void (CODEGEN_FUNCPTR *TexCoord2sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *TexCoord3d)(GLdouble s, GLdouble t, GLdouble r);
		extern void (CODEGEN_FUNCPTR *TexCoord3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *TexCoord3f)(GLfloat s, GLfloat t, GLfloat r);
		extern void (CODEGEN_FUNCPTR *TexCoord3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *TexCoord3i)(GLint s, GLint t, GLint r);
		extern void (CODEGEN_FUNCPTR *TexCoord3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *TexCoord3s)(GLshort s, GLshort t, GLshort r);
		extern void (CODEGEN_FUNCPTR *TexCoord3sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *TexCoord4d)(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
		extern void (CODEGEN_FUNCPTR *TexCoord4dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *TexCoord4f)(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
		extern void (CODEGEN_FUNCPTR *TexCoord4fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *TexCoord4i)(GLint s, GLint t, GLint r, GLint q);
		extern void (CODEGEN_FUNCPTR *TexCoord4iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *TexCoord4s)(GLshort s, GLshort t, GLshort r, GLshort q);
		extern void (CODEGEN_FUNCPTR *TexCoord4sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *TexEnvf)(GLenum target, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *TexEnvfv)(GLenum target, GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *TexEnvi)(GLenum target, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *TexEnviv)(GLenum target, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *TexGend)(GLenum coord, GLenum pname, GLdouble param);
		extern void (CODEGEN_FUNCPTR *TexGendv)(GLenum coord, GLenum pname, const GLdouble * params);
		extern void (CODEGEN_FUNCPTR *TexGenf)(GLenum coord, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *TexGenfv)(GLenum coord, GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *TexGeni)(GLenum coord, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *TexGeniv)(GLenum coord, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *TexImage1D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *TexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *TexParameterf)(GLenum target, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *TexParameterfv)(GLenum target, GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *TexParameteri)(GLenum target, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *TexParameteriv)(GLenum target, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *Translated)(GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *Translatef)(GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *Vertex2d)(GLdouble x, GLdouble y);
		extern void (CODEGEN_FUNCPTR *Vertex2dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *Vertex2f)(GLfloat x, GLfloat y);
		extern void (CODEGEN_FUNCPTR *Vertex2fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *Vertex2i)(GLint x, GLint y);
		extern void (CODEGEN_FUNCPTR *Vertex2iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *Vertex2s)(GLshort x, GLshort y);
		extern void (CODEGEN_FUNCPTR *Vertex2sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *Vertex3d)(GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *Vertex3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *Vertex3f)(GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *Vertex3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *Vertex3i)(GLint x, GLint y, GLint z);
		extern void (CODEGEN_FUNCPTR *Vertex3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *Vertex3s)(GLshort x, GLshort y, GLshort z);
		extern void (CODEGEN_FUNCPTR *Vertex3sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *Vertex4d)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		extern void (CODEGEN_FUNCPTR *Vertex4dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *Vertex4f)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		extern void (CODEGEN_FUNCPTR *Vertex4fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *Vertex4i)(GLint x, GLint y, GLint z, GLint w);
		extern void (CODEGEN_FUNCPTR *Vertex4iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *Vertex4s)(GLshort x, GLshort y, GLshort z, GLshort w);
		extern void (CODEGEN_FUNCPTR *Vertex4sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *Viewport)(GLint x, GLint y, GLsizei width, GLsizei height);
		
		extern GLboolean (CODEGEN_FUNCPTR *AreTexturesResident)(GLsizei n, const GLuint * textures, GLboolean * residences);
		extern void (CODEGEN_FUNCPTR *ArrayElement)(GLint i);
		extern void (CODEGEN_FUNCPTR *BindTexture)(GLenum target, GLuint texture);
		extern void (CODEGEN_FUNCPTR *ColorPointer)(GLint size, GLenum type, GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *CopyTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
		extern void (CODEGEN_FUNCPTR *CopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
		extern void (CODEGEN_FUNCPTR *CopyTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
		extern void (CODEGEN_FUNCPTR *CopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *DeleteTextures)(GLsizei n, const GLuint * textures);
		extern void (CODEGEN_FUNCPTR *DisableClientState)(GLenum ren_array);
		extern void (CODEGEN_FUNCPTR *DrawArrays)(GLenum mode, GLint first, GLsizei count);
		extern void (CODEGEN_FUNCPTR *DrawElements)(GLenum mode, GLsizei count, GLenum type, const void * indices);
		extern void (CODEGEN_FUNCPTR *EdgeFlagPointer)(GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *EnableClientState)(GLenum ren_array);
		extern void (CODEGEN_FUNCPTR *GenTextures)(GLsizei n, GLuint * textures);
		extern void (CODEGEN_FUNCPTR *GetPointerv)(GLenum pname, void ** params);
		extern void (CODEGEN_FUNCPTR *IndexPointer)(GLenum type, GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *Indexub)(GLubyte c);
		extern void (CODEGEN_FUNCPTR *Indexubv)(const GLubyte * c);
		extern void (CODEGEN_FUNCPTR *InterleavedArrays)(GLenum format, GLsizei stride, const void * pointer);
		extern GLboolean (CODEGEN_FUNCPTR *IsTexture)(GLuint texture);
		extern void (CODEGEN_FUNCPTR *NormalPointer)(GLenum type, GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *PolygonOffset)(GLfloat factor, GLfloat units);
		extern void (CODEGEN_FUNCPTR *PopClientAttrib)(void);
		extern void (CODEGEN_FUNCPTR *PrioritizeTextures)(GLsizei n, const GLuint * textures, const GLfloat * priorities);
		extern void (CODEGEN_FUNCPTR *PushClientAttrib)(GLbitfield mask);
		extern void (CODEGEN_FUNCPTR *TexCoordPointer)(GLint size, GLenum type, GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *TexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *TexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *VertexPointer)(GLint size, GLenum type, GLsizei stride, const void * pointer);
		
		extern void (CODEGEN_FUNCPTR *CopyTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *DrawRangeElements)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices);
		extern void (CODEGEN_FUNCPTR *TexImage3D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *TexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
		
		extern void (CODEGEN_FUNCPTR *ActiveTexture)(GLenum texture);
		extern void (CODEGEN_FUNCPTR *ClientActiveTexture)(GLenum texture);
		extern void (CODEGEN_FUNCPTR *CompressedTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexImage3D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *CompressedTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *GetCompressedTexImage)(GLenum target, GLint level, void * img);
		extern void (CODEGEN_FUNCPTR *LoadTransposeMatrixd)(const GLdouble * m);
		extern void (CODEGEN_FUNCPTR *LoadTransposeMatrixf)(const GLfloat * m);
		extern void (CODEGEN_FUNCPTR *MultTransposeMatrixd)(const GLdouble * m);
		extern void (CODEGEN_FUNCPTR *MultTransposeMatrixf)(const GLfloat * m);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1d)(GLenum target, GLdouble s);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1dv)(GLenum target, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1f)(GLenum target, GLfloat s);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1fv)(GLenum target, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1i)(GLenum target, GLint s);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1iv)(GLenum target, const GLint * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1s)(GLenum target, GLshort s);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord1sv)(GLenum target, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2d)(GLenum target, GLdouble s, GLdouble t);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2dv)(GLenum target, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2f)(GLenum target, GLfloat s, GLfloat t);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2fv)(GLenum target, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2i)(GLenum target, GLint s, GLint t);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2iv)(GLenum target, const GLint * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2s)(GLenum target, GLshort s, GLshort t);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord2sv)(GLenum target, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3d)(GLenum target, GLdouble s, GLdouble t, GLdouble r);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3dv)(GLenum target, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3f)(GLenum target, GLfloat s, GLfloat t, GLfloat r);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3fv)(GLenum target, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3i)(GLenum target, GLint s, GLint t, GLint r);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3iv)(GLenum target, const GLint * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3s)(GLenum target, GLshort s, GLshort t, GLshort r);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord3sv)(GLenum target, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4d)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4dv)(GLenum target, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4f)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4fv)(GLenum target, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4i)(GLenum target, GLint s, GLint t, GLint r, GLint q);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4iv)(GLenum target, const GLint * v);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4s)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
		extern void (CODEGEN_FUNCPTR *MultiTexCoord4sv)(GLenum target, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *SampleCoverage)(GLfloat value, GLboolean invert);
		
		extern void (CODEGEN_FUNCPTR *BlendColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		extern void (CODEGEN_FUNCPTR *BlendEquation)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *BlendFuncSeparate)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
		extern void (CODEGEN_FUNCPTR *FogCoordPointer)(GLenum type, GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *FogCoordd)(GLdouble coord);
		extern void (CODEGEN_FUNCPTR *FogCoorddv)(const GLdouble * coord);
		extern void (CODEGEN_FUNCPTR *FogCoordf)(GLfloat coord);
		extern void (CODEGEN_FUNCPTR *FogCoordfv)(const GLfloat * coord);
		extern void (CODEGEN_FUNCPTR *MultiDrawArrays)(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount);
		extern void (CODEGEN_FUNCPTR *MultiDrawElements)(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount);
		extern void (CODEGEN_FUNCPTR *PointParameterf)(GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *PointParameterfv)(GLenum pname, const GLfloat * params);
		extern void (CODEGEN_FUNCPTR *PointParameteri)(GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *PointParameteriv)(GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3b)(GLbyte red, GLbyte green, GLbyte blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3bv)(const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3d)(GLdouble red, GLdouble green, GLdouble blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3f)(GLfloat red, GLfloat green, GLfloat blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3i)(GLint red, GLint green, GLint blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3s)(GLshort red, GLshort green, GLshort blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3ub)(GLubyte red, GLubyte green, GLubyte blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3ubv)(const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3ui)(GLuint red, GLuint green, GLuint blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3uiv)(const GLuint * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3us)(GLushort red, GLushort green, GLushort blue);
		extern void (CODEGEN_FUNCPTR *SecondaryColor3usv)(const GLushort * v);
		extern void (CODEGEN_FUNCPTR *SecondaryColorPointer)(GLint size, GLenum type, GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *WindowPos2d)(GLdouble x, GLdouble y);
		extern void (CODEGEN_FUNCPTR *WindowPos2dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *WindowPos2f)(GLfloat x, GLfloat y);
		extern void (CODEGEN_FUNCPTR *WindowPos2fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *WindowPos2i)(GLint x, GLint y);
		extern void (CODEGEN_FUNCPTR *WindowPos2iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *WindowPos2s)(GLshort x, GLshort y);
		extern void (CODEGEN_FUNCPTR *WindowPos2sv)(const GLshort * v);
		extern void (CODEGEN_FUNCPTR *WindowPos3d)(GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *WindowPos3dv)(const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *WindowPos3f)(GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *WindowPos3fv)(const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *WindowPos3i)(GLint x, GLint y, GLint z);
		extern void (CODEGEN_FUNCPTR *WindowPos3iv)(const GLint * v);
		extern void (CODEGEN_FUNCPTR *WindowPos3s)(GLshort x, GLshort y, GLshort z);
		extern void (CODEGEN_FUNCPTR *WindowPos3sv)(const GLshort * v);
		
		extern void (CODEGEN_FUNCPTR *BeginQuery)(GLenum target, GLuint id);
		extern void (CODEGEN_FUNCPTR *BindBuffer)(GLenum target, GLuint buffer);
		extern void (CODEGEN_FUNCPTR *BufferData)(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
		extern void (CODEGEN_FUNCPTR *BufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
		extern void (CODEGEN_FUNCPTR *DeleteBuffers)(GLsizei n, const GLuint * buffers);
		extern void (CODEGEN_FUNCPTR *DeleteQueries)(GLsizei n, const GLuint * ids);
		extern void (CODEGEN_FUNCPTR *EndQuery)(GLenum target);
		extern void (CODEGEN_FUNCPTR *GenBuffers)(GLsizei n, GLuint * buffers);
		extern void (CODEGEN_FUNCPTR *GenQueries)(GLsizei n, GLuint * ids);
		extern void (CODEGEN_FUNCPTR *GetBufferParameteriv)(GLenum target, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetBufferPointerv)(GLenum target, GLenum pname, void ** params);
		extern void (CODEGEN_FUNCPTR *GetBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, void * data);
		extern void (CODEGEN_FUNCPTR *GetQueryObjectiv)(GLuint id, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetQueryObjectuiv)(GLuint id, GLenum pname, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetQueryiv)(GLenum target, GLenum pname, GLint * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsBuffer)(GLuint buffer);
		extern GLboolean (CODEGEN_FUNCPTR *IsQuery)(GLuint id);
		extern void * (CODEGEN_FUNCPTR *MapBuffer)(GLenum target, GLenum access);
		extern GLboolean (CODEGEN_FUNCPTR *UnmapBuffer)(GLenum target);
		
		extern void (CODEGEN_FUNCPTR *AttachShader)(GLuint program, GLuint shader);
		extern void (CODEGEN_FUNCPTR *BindAttribLocation)(GLuint program, GLuint index, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *BlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha);
		extern void (CODEGEN_FUNCPTR *CompileShader)(GLuint shader);
		extern GLuint (CODEGEN_FUNCPTR *CreateProgram)(void);
		extern GLuint (CODEGEN_FUNCPTR *CreateShader)(GLenum type);
		extern void (CODEGEN_FUNCPTR *DeleteProgram)(GLuint program);
		extern void (CODEGEN_FUNCPTR *DeleteShader)(GLuint shader);
		extern void (CODEGEN_FUNCPTR *DetachShader)(GLuint program, GLuint shader);
		extern void (CODEGEN_FUNCPTR *DisableVertexAttribArray)(GLuint index);
		extern void (CODEGEN_FUNCPTR *DrawBuffers)(GLsizei n, const GLenum * bufs);
		extern void (CODEGEN_FUNCPTR *EnableVertexAttribArray)(GLuint index);
		extern void (CODEGEN_FUNCPTR *GetActiveAttrib)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetActiveUniform)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetAttachedShaders)(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
		extern GLint (CODEGEN_FUNCPTR *GetAttribLocation)(GLuint program, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
		extern void (CODEGEN_FUNCPTR *GetProgramiv)(GLuint program, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
		extern void (CODEGEN_FUNCPTR *GetShaderSource)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
		extern void (CODEGEN_FUNCPTR *GetShaderiv)(GLuint shader, GLenum pname, GLint * params);
		extern GLint (CODEGEN_FUNCPTR *GetUniformLocation)(GLuint program, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetUniformfv)(GLuint program, GLint location, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetUniformiv)(GLuint program, GLint location, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribPointerv)(GLuint index, GLenum pname, void ** pointer);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribdv)(GLuint index, GLenum pname, GLdouble * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribfv)(GLuint index, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribiv)(GLuint index, GLenum pname, GLint * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsProgram)(GLuint program);
		extern GLboolean (CODEGEN_FUNCPTR *IsShader)(GLuint shader);
		extern void (CODEGEN_FUNCPTR *LinkProgram)(GLuint program);
		extern void (CODEGEN_FUNCPTR *ShaderSource)(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length);
		extern void (CODEGEN_FUNCPTR *StencilFuncSeparate)(GLenum face, GLenum func, GLint ref, GLuint mask);
		extern void (CODEGEN_FUNCPTR *StencilMaskSeparate)(GLenum face, GLuint mask);
		extern void (CODEGEN_FUNCPTR *StencilOpSeparate)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
		extern void (CODEGEN_FUNCPTR *Uniform1f)(GLint location, GLfloat v0);
		extern void (CODEGEN_FUNCPTR *Uniform1fv)(GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *Uniform1i)(GLint location, GLint v0);
		extern void (CODEGEN_FUNCPTR *Uniform1iv)(GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *Uniform2f)(GLint location, GLfloat v0, GLfloat v1);
		extern void (CODEGEN_FUNCPTR *Uniform2fv)(GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *Uniform2i)(GLint location, GLint v0, GLint v1);
		extern void (CODEGEN_FUNCPTR *Uniform2iv)(GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *Uniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
		extern void (CODEGEN_FUNCPTR *Uniform3fv)(GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *Uniform3i)(GLint location, GLint v0, GLint v1, GLint v2);
		extern void (CODEGEN_FUNCPTR *Uniform3iv)(GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *Uniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
		extern void (CODEGEN_FUNCPTR *Uniform4fv)(GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *Uniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
		extern void (CODEGEN_FUNCPTR *Uniform4iv)(GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UseProgram)(GLuint program);
		extern void (CODEGEN_FUNCPTR *ValidateProgram)(GLuint program);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1d)(GLuint index, GLdouble x);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1f)(GLuint index, GLfloat x);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1fv)(GLuint index, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1s)(GLuint index, GLshort x);
		extern void (CODEGEN_FUNCPTR *VertexAttrib1sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2d)(GLuint index, GLdouble x, GLdouble y);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2f)(GLuint index, GLfloat x, GLfloat y);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2fv)(GLuint index, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2s)(GLuint index, GLshort x, GLshort y);
		extern void (CODEGEN_FUNCPTR *VertexAttrib2sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3d)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3f)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3fv)(GLuint index, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3s)(GLuint index, GLshort x, GLshort y, GLshort z);
		extern void (CODEGEN_FUNCPTR *VertexAttrib3sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nbv)(GLuint index, const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Niv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nsv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nub)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nubv)(GLuint index, const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nuiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4Nusv)(GLuint index, const GLushort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4bv)(GLuint index, const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4d)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4f)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4fv)(GLuint index, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4s)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4ubv)(GLuint index, const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttrib4usv)(GLuint index, const GLushort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
		
		extern void (CODEGEN_FUNCPTR *UniformMatrix2x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix2x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		
		extern void (CODEGEN_FUNCPTR *BeginConditionalRender)(GLuint id, GLenum mode);
		extern void (CODEGEN_FUNCPTR *BeginTransformFeedback)(GLenum primitiveMode);
		extern void (CODEGEN_FUNCPTR *BindBufferBase)(GLenum target, GLuint index, GLuint buffer);
		extern void (CODEGEN_FUNCPTR *BindBufferRange)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
		extern void (CODEGEN_FUNCPTR *BindFragDataLocation)(GLuint program, GLuint color, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *BindFramebuffer)(GLenum target, GLuint framebuffer);
		extern void (CODEGEN_FUNCPTR *BindRenderbuffer)(GLenum target, GLuint renderbuffer);
		extern void (CODEGEN_FUNCPTR *BindVertexArray)(GLuint ren_array);
		extern void (CODEGEN_FUNCPTR *BlitFramebuffer)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
		extern GLenum (CODEGEN_FUNCPTR *CheckFramebufferStatus)(GLenum target);
		extern void (CODEGEN_FUNCPTR *ClampColor)(GLenum target, GLenum clamp);
		extern void (CODEGEN_FUNCPTR *ClearBufferfi)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
		extern void (CODEGEN_FUNCPTR *ClearBufferfv)(GLenum buffer, GLint drawbuffer, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ClearBufferiv)(GLenum buffer, GLint drawbuffer, const GLint * value);
		extern void (CODEGEN_FUNCPTR *ClearBufferuiv)(GLenum buffer, GLint drawbuffer, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *ColorMaski)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
		extern void (CODEGEN_FUNCPTR *DeleteFramebuffers)(GLsizei n, const GLuint * framebuffers);
		extern void (CODEGEN_FUNCPTR *DeleteRenderbuffers)(GLsizei n, const GLuint * renderbuffers);
		extern void (CODEGEN_FUNCPTR *DeleteVertexArrays)(GLsizei n, const GLuint * arrays);
		extern void (CODEGEN_FUNCPTR *Disablei)(GLenum target, GLuint index);
		extern void (CODEGEN_FUNCPTR *Enablei)(GLenum target, GLuint index);
		extern void (CODEGEN_FUNCPTR *EndConditionalRender)(void);
		extern void (CODEGEN_FUNCPTR *EndTransformFeedback)(void);
		extern void (CODEGEN_FUNCPTR *FlushMappedBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length);
		extern void (CODEGEN_FUNCPTR *FramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
		extern void (CODEGEN_FUNCPTR *FramebufferTexture1D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
		extern void (CODEGEN_FUNCPTR *FramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
		extern void (CODEGEN_FUNCPTR *FramebufferTexture3D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
		extern void (CODEGEN_FUNCPTR *FramebufferTextureLayer)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
		extern void (CODEGEN_FUNCPTR *GenFramebuffers)(GLsizei n, GLuint * framebuffers);
		extern void (CODEGEN_FUNCPTR *GenRenderbuffers)(GLsizei n, GLuint * renderbuffers);
		extern void (CODEGEN_FUNCPTR *GenVertexArrays)(GLsizei n, GLuint * arrays);
		extern void (CODEGEN_FUNCPTR *GenerateMipmap)(GLenum target);
		extern void (CODEGEN_FUNCPTR *GetBooleani_v)(GLenum target, GLuint index, GLboolean * data);
		extern GLint (CODEGEN_FUNCPTR *GetFragDataLocation)(GLuint program, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetIntegeri_v)(GLenum target, GLuint index, GLint * data);
		extern void (CODEGEN_FUNCPTR *GetRenderbufferParameteriv)(GLenum target, GLenum pname, GLint * params);
		extern const GLubyte * (CODEGEN_FUNCPTR *GetStringi)(GLenum name, GLuint index);
		extern void (CODEGEN_FUNCPTR *GetTexParameterIiv)(GLenum target, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetTexParameterIuiv)(GLenum target, GLenum pname, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetTransformFeedbackVarying)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetUniformuiv)(GLuint program, GLint location, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribIiv)(GLuint index, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribIuiv)(GLuint index, GLenum pname, GLuint * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsEnabledi)(GLenum target, GLuint index);
		extern GLboolean (CODEGEN_FUNCPTR *IsFramebuffer)(GLuint framebuffer);
		extern GLboolean (CODEGEN_FUNCPTR *IsRenderbuffer)(GLuint renderbuffer);
		extern GLboolean (CODEGEN_FUNCPTR *IsVertexArray)(GLuint ren_array);
		extern void * (CODEGEN_FUNCPTR *MapBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
		extern void (CODEGEN_FUNCPTR *RenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *RenderbufferStorageMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *TexParameterIiv)(GLenum target, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *TexParameterIuiv)(GLenum target, GLenum pname, const GLuint * params);
		extern void (CODEGEN_FUNCPTR *TransformFeedbackVaryings)(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode);
		extern void (CODEGEN_FUNCPTR *Uniform1ui)(GLint location, GLuint v0);
		extern void (CODEGEN_FUNCPTR *Uniform1uiv)(GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *Uniform2ui)(GLint location, GLuint v0, GLuint v1);
		extern void (CODEGEN_FUNCPTR *Uniform2uiv)(GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *Uniform3ui)(GLint location, GLuint v0, GLuint v1, GLuint v2);
		extern void (CODEGEN_FUNCPTR *Uniform3uiv)(GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *Uniform4ui)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
		extern void (CODEGEN_FUNCPTR *Uniform4uiv)(GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *VertexAttribI1i)(GLuint index, GLint x);
		extern void (CODEGEN_FUNCPTR *VertexAttribI1iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI1ui)(GLuint index, GLuint x);
		extern void (CODEGEN_FUNCPTR *VertexAttribI1uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI2i)(GLuint index, GLint x, GLint y);
		extern void (CODEGEN_FUNCPTR *VertexAttribI2iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI2ui)(GLuint index, GLuint x, GLuint y);
		extern void (CODEGEN_FUNCPTR *VertexAttribI2uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI3i)(GLuint index, GLint x, GLint y, GLint z);
		extern void (CODEGEN_FUNCPTR *VertexAttribI3iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI3ui)(GLuint index, GLuint x, GLuint y, GLuint z);
		extern void (CODEGEN_FUNCPTR *VertexAttribI3uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4bv)(GLuint index, const GLbyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4i)(GLuint index, GLint x, GLint y, GLint z, GLint w);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4iv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4sv)(GLuint index, const GLshort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4ubv)(GLuint index, const GLubyte * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4ui)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4uiv)(GLuint index, const GLuint * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribI4usv)(GLuint index, const GLushort * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribIPointer)(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
		
		extern void (CODEGEN_FUNCPTR *CopyBufferSubData)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
		extern void (CODEGEN_FUNCPTR *DrawArraysInstanced)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
		extern void (CODEGEN_FUNCPTR *DrawElementsInstanced)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount);
		extern void (CODEGEN_FUNCPTR *GetActiveUniformBlockName)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName);
		extern void (CODEGEN_FUNCPTR *GetActiveUniformBlockiv)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetActiveUniformName)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName);
		extern void (CODEGEN_FUNCPTR *GetActiveUniformsiv)(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params);
		extern GLuint (CODEGEN_FUNCPTR *GetUniformBlockIndex)(GLuint program, const GLchar * uniformBlockName);
		extern void (CODEGEN_FUNCPTR *GetUniformIndices)(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices);
		extern void (CODEGEN_FUNCPTR *PrimitiveRestartIndex)(GLuint index);
		extern void (CODEGEN_FUNCPTR *TexBuffer)(GLenum target, GLenum internalformat, GLuint buffer);
		extern void (CODEGEN_FUNCPTR *UniformBlockBinding)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
		
		extern GLenum (CODEGEN_FUNCPTR *ClientWaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout);
		extern void (CODEGEN_FUNCPTR *DeleteSync)(GLsync sync);
		extern void (CODEGEN_FUNCPTR *DrawElementsBaseVertex)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex);
		extern void (CODEGEN_FUNCPTR *DrawElementsInstancedBaseVertex)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex);
		extern void (CODEGEN_FUNCPTR *DrawRangeElementsBaseVertex)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex);
		extern GLsync (CODEGEN_FUNCPTR *FenceSync)(GLenum condition, GLbitfield flags);
		extern void (CODEGEN_FUNCPTR *FramebufferTexture)(GLenum target, GLenum attachment, GLuint texture, GLint level);
		extern void (CODEGEN_FUNCPTR *GetBufferParameteri64v)(GLenum target, GLenum pname, GLint64 * params);
		extern void (CODEGEN_FUNCPTR *GetInteger64i_v)(GLenum target, GLuint index, GLint64 * data);
		extern void (CODEGEN_FUNCPTR *GetInteger64v)(GLenum pname, GLint64 * data);
		extern void (CODEGEN_FUNCPTR *GetMultisamplefv)(GLenum pname, GLuint index, GLfloat * val);
		extern void (CODEGEN_FUNCPTR *GetSynciv)(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values);
		extern GLboolean (CODEGEN_FUNCPTR *IsSync)(GLsync sync);
		extern void (CODEGEN_FUNCPTR *MultiDrawElementsBaseVertex)(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount, const GLint * basevertex);
		extern void (CODEGEN_FUNCPTR *ProvokingVertex)(GLenum mode);
		extern void (CODEGEN_FUNCPTR *SampleMaski)(GLuint maskNumber, GLbitfield mask);
		extern void (CODEGEN_FUNCPTR *TexImage2DMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
		extern void (CODEGEN_FUNCPTR *TexImage3DMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
		extern void (CODEGEN_FUNCPTR *WaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout);
		
		extern void (CODEGEN_FUNCPTR *BindFragDataLocationIndexed)(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *BindSampler)(GLuint unit, GLuint sampler);
		extern void (CODEGEN_FUNCPTR *DeleteSamplers)(GLsizei count, const GLuint * samplers);
		extern void (CODEGEN_FUNCPTR *GenSamplers)(GLsizei count, GLuint * samplers);
		extern GLint (CODEGEN_FUNCPTR *GetFragDataIndex)(GLuint program, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetQueryObjecti64v)(GLuint id, GLenum pname, GLint64 * params);
		extern void (CODEGEN_FUNCPTR *GetQueryObjectui64v)(GLuint id, GLenum pname, GLuint64 * params);
		extern void (CODEGEN_FUNCPTR *GetSamplerParameterIiv)(GLuint sampler, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetSamplerParameterIuiv)(GLuint sampler, GLenum pname, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetSamplerParameterfv)(GLuint sampler, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetSamplerParameteriv)(GLuint sampler, GLenum pname, GLint * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsSampler)(GLuint sampler);
		extern void (CODEGEN_FUNCPTR *QueryCounter)(GLuint id, GLenum target);
		extern void (CODEGEN_FUNCPTR *SamplerParameterIiv)(GLuint sampler, GLenum pname, const GLint * param);
		extern void (CODEGEN_FUNCPTR *SamplerParameterIuiv)(GLuint sampler, GLenum pname, const GLuint * param);
		extern void (CODEGEN_FUNCPTR *SamplerParameterf)(GLuint sampler, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *SamplerParameterfv)(GLuint sampler, GLenum pname, const GLfloat * param);
		extern void (CODEGEN_FUNCPTR *SamplerParameteri)(GLuint sampler, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *SamplerParameteriv)(GLuint sampler, GLenum pname, const GLint * param);
		extern void (CODEGEN_FUNCPTR *VertexAttribDivisor)(GLuint index, GLuint divisor);
		extern void (CODEGEN_FUNCPTR *VertexAttribP1ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP1uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP2ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP2uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP3ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP3uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP4ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
		extern void (CODEGEN_FUNCPTR *VertexAttribP4uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
		
		extern void (CODEGEN_FUNCPTR *BeginQueryIndexed)(GLenum target, GLuint index, GLuint id);
		extern void (CODEGEN_FUNCPTR *BindTransformFeedback)(GLenum target, GLuint id);
		extern void (CODEGEN_FUNCPTR *BlendEquationSeparatei)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
		extern void (CODEGEN_FUNCPTR *BlendEquationi)(GLuint buf, GLenum mode);
		extern void (CODEGEN_FUNCPTR *BlendFuncSeparatei)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
		extern void (CODEGEN_FUNCPTR *BlendFunci)(GLuint buf, GLenum src, GLenum dst);
		extern void (CODEGEN_FUNCPTR *DeleteTransformFeedbacks)(GLsizei n, const GLuint * ids);
		extern void (CODEGEN_FUNCPTR *DrawArraysIndirect)(GLenum mode, const void * indirect);
		extern void (CODEGEN_FUNCPTR *DrawElementsIndirect)(GLenum mode, GLenum type, const void * indirect);
		extern void (CODEGEN_FUNCPTR *DrawTransformFeedback)(GLenum mode, GLuint id);
		extern void (CODEGEN_FUNCPTR *DrawTransformFeedbackStream)(GLenum mode, GLuint id, GLuint stream);
		extern void (CODEGEN_FUNCPTR *EndQueryIndexed)(GLenum target, GLuint index);
		extern void (CODEGEN_FUNCPTR *GenTransformFeedbacks)(GLsizei n, GLuint * ids);
		extern void (CODEGEN_FUNCPTR *GetActiveSubroutineName)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetActiveSubroutineUniformName)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetActiveSubroutineUniformiv)(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values);
		extern void (CODEGEN_FUNCPTR *GetProgramStageiv)(GLuint program, GLenum shadertype, GLenum pname, GLint * values);
		extern void (CODEGEN_FUNCPTR *GetQueryIndexediv)(GLenum target, GLuint index, GLenum pname, GLint * params);
		extern GLuint (CODEGEN_FUNCPTR *GetSubroutineIndex)(GLuint program, GLenum shadertype, const GLchar * name);
		extern GLint (CODEGEN_FUNCPTR *GetSubroutineUniformLocation)(GLuint program, GLenum shadertype, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetUniformSubroutineuiv)(GLenum shadertype, GLint location, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetUniformdv)(GLuint program, GLint location, GLdouble * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsTransformFeedback)(GLuint id);
		extern void (CODEGEN_FUNCPTR *MinSampleShading)(GLfloat value);
		extern void (CODEGEN_FUNCPTR *PatchParameterfv)(GLenum pname, const GLfloat * values);
		extern void (CODEGEN_FUNCPTR *PatchParameteri)(GLenum pname, GLint value);
		extern void (CODEGEN_FUNCPTR *PauseTransformFeedback)(void);
		extern void (CODEGEN_FUNCPTR *ResumeTransformFeedback)(void);
		extern void (CODEGEN_FUNCPTR *Uniform1d)(GLint location, GLdouble x);
		extern void (CODEGEN_FUNCPTR *Uniform1dv)(GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *Uniform2d)(GLint location, GLdouble x, GLdouble y);
		extern void (CODEGEN_FUNCPTR *Uniform2dv)(GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *Uniform3d)(GLint location, GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *Uniform3dv)(GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *Uniform4d)(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		extern void (CODEGEN_FUNCPTR *Uniform4dv)(GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix2dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix2x3dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix2x4dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3x2dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix3x4dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4x2dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformMatrix4x3dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *UniformSubroutinesuiv)(GLenum shadertype, GLsizei count, const GLuint * indices);
		
		extern void (CODEGEN_FUNCPTR *ActiveShaderProgram)(GLuint pipeline, GLuint program);
		extern void (CODEGEN_FUNCPTR *BindProgramPipeline)(GLuint pipeline);
		extern void (CODEGEN_FUNCPTR *ClearDepthf)(GLfloat d);
		extern GLuint (CODEGEN_FUNCPTR *CreateShaderProgramv)(GLenum type, GLsizei count, const GLchar *const* strings);
		extern void (CODEGEN_FUNCPTR *DeleteProgramPipelines)(GLsizei n, const GLuint * pipelines);
		extern void (CODEGEN_FUNCPTR *DepthRangeArrayv)(GLuint first, GLsizei count, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *DepthRangeIndexed)(GLuint index, GLdouble n, GLdouble f);
		extern void (CODEGEN_FUNCPTR *DepthRangef)(GLfloat n, GLfloat f);
		extern void (CODEGEN_FUNCPTR *GenProgramPipelines)(GLsizei n, GLuint * pipelines);
		extern void (CODEGEN_FUNCPTR *GetDoublei_v)(GLenum target, GLuint index, GLdouble * data);
		extern void (CODEGEN_FUNCPTR *GetFloati_v)(GLenum target, GLuint index, GLfloat * data);
		extern void (CODEGEN_FUNCPTR *GetProgramBinary)(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, void * binary);
		extern void (CODEGEN_FUNCPTR *GetProgramPipelineInfoLog)(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
		extern void (CODEGEN_FUNCPTR *GetProgramPipelineiv)(GLuint pipeline, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetShaderPrecisionFormat)(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision);
		extern void (CODEGEN_FUNCPTR *GetVertexAttribLdv)(GLuint index, GLenum pname, GLdouble * params);
		extern GLboolean (CODEGEN_FUNCPTR *IsProgramPipeline)(GLuint pipeline);
		extern void (CODEGEN_FUNCPTR *ProgramBinary)(GLuint program, GLenum binaryFormat, const void * binary, GLsizei length);
		extern void (CODEGEN_FUNCPTR *ProgramParameteri)(GLuint program, GLenum pname, GLint value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1d)(GLuint program, GLint location, GLdouble v0);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1dv)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1f)(GLuint program, GLint location, GLfloat v0);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1fv)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1i)(GLuint program, GLint location, GLint v0);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1iv)(GLuint program, GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1ui)(GLuint program, GLint location, GLuint v0);
		extern void (CODEGEN_FUNCPTR *ProgramUniform1uiv)(GLuint program, GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2d)(GLuint program, GLint location, GLdouble v0, GLdouble v1);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2dv)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2f)(GLuint program, GLint location, GLfloat v0, GLfloat v1);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2fv)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2i)(GLuint program, GLint location, GLint v0, GLint v1);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2iv)(GLuint program, GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2ui)(GLuint program, GLint location, GLuint v0, GLuint v1);
		extern void (CODEGEN_FUNCPTR *ProgramUniform2uiv)(GLuint program, GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3d)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3dv)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3f)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3fv)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3i)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3iv)(GLuint program, GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3ui)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
		extern void (CODEGEN_FUNCPTR *ProgramUniform3uiv)(GLuint program, GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4d)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4dv)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4f)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4fv)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4i)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4iv)(GLuint program, GLint location, GLsizei count, const GLint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4ui)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
		extern void (CODEGEN_FUNCPTR *ProgramUniform4uiv)(GLuint program, GLint location, GLsizei count, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix2dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix2fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix2x3dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix2x3fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix2x4dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix2x4fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix3dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix3fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix3x2dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix3x2fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix3x4dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix3x4fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix4dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix4fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix4x2dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix4x2fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix4x3dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		extern void (CODEGEN_FUNCPTR *ProgramUniformMatrix4x3fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ReleaseShaderCompiler)(void);
		extern void (CODEGEN_FUNCPTR *ScissorArrayv)(GLuint first, GLsizei count, const GLint * v);
		extern void (CODEGEN_FUNCPTR *ScissorIndexed)(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *ScissorIndexedv)(GLuint index, const GLint * v);
		extern void (CODEGEN_FUNCPTR *ShaderBinary)(GLsizei count, const GLuint * shaders, GLenum binaryformat, const void * binary, GLsizei length);
		extern void (CODEGEN_FUNCPTR *UseProgramStages)(GLuint pipeline, GLbitfield stages, GLuint program);
		extern void (CODEGEN_FUNCPTR *ValidateProgramPipeline)(GLuint pipeline);
		extern void (CODEGEN_FUNCPTR *VertexAttribL1d)(GLuint index, GLdouble x);
		extern void (CODEGEN_FUNCPTR *VertexAttribL1dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribL2d)(GLuint index, GLdouble x, GLdouble y);
		extern void (CODEGEN_FUNCPTR *VertexAttribL2dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribL3d)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
		extern void (CODEGEN_FUNCPTR *VertexAttribL3dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribL4d)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		extern void (CODEGEN_FUNCPTR *VertexAttribL4dv)(GLuint index, const GLdouble * v);
		extern void (CODEGEN_FUNCPTR *VertexAttribLPointer)(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
		extern void (CODEGEN_FUNCPTR *ViewportArrayv)(GLuint first, GLsizei count, const GLfloat * v);
		extern void (CODEGEN_FUNCPTR *ViewportIndexedf)(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
		extern void (CODEGEN_FUNCPTR *ViewportIndexedfv)(GLuint index, const GLfloat * v);
		
		extern void (CODEGEN_FUNCPTR *BindImageTexture)(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
		extern void (CODEGEN_FUNCPTR *DrawArraysInstancedBaseInstance)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
		extern void (CODEGEN_FUNCPTR *DrawElementsInstancedBaseInstance)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLuint baseinstance);
		extern void (CODEGEN_FUNCPTR *DrawElementsInstancedBaseVertexBaseInstance)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
		extern void (CODEGEN_FUNCPTR *DrawTransformFeedbackInstanced)(GLenum mode, GLuint id, GLsizei instancecount);
		extern void (CODEGEN_FUNCPTR *DrawTransformFeedbackStreamInstanced)(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
		extern void (CODEGEN_FUNCPTR *GetActiveAtomicCounterBufferiv)(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetInternalformativ)(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params);
		extern void (CODEGEN_FUNCPTR *MemoryBarrier)(GLbitfield barriers);
		extern void (CODEGEN_FUNCPTR *TexStorage1D)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
		extern void (CODEGEN_FUNCPTR *TexStorage2D)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *TexStorage3D)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
		
		extern void (CODEGEN_FUNCPTR *BindVertexBuffer)(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
		extern void (CODEGEN_FUNCPTR *ClearBufferData)(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data);
		extern void (CODEGEN_FUNCPTR *ClearBufferSubData)(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data);
		extern void (CODEGEN_FUNCPTR *CopyImageSubData)(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
		extern void (CODEGEN_FUNCPTR *DebugMessageCallback)(GLDEBUGPROC callback, const void * userParam);
		extern void (CODEGEN_FUNCPTR *DebugMessageControl)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled);
		extern void (CODEGEN_FUNCPTR *DebugMessageInsert)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf);
		extern void (CODEGEN_FUNCPTR *DispatchCompute)(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
		extern void (CODEGEN_FUNCPTR *DispatchComputeIndirect)(GLintptr indirect);
		extern void (CODEGEN_FUNCPTR *FramebufferParameteri)(GLenum target, GLenum pname, GLint param);
		extern GLuint (CODEGEN_FUNCPTR *GetDebugMessageLog)(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog);
		extern void (CODEGEN_FUNCPTR *GetFramebufferParameteriv)(GLenum target, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetInternalformati64v)(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params);
		extern void (CODEGEN_FUNCPTR *GetObjectLabel)(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label);
		extern void (CODEGEN_FUNCPTR *GetObjectPtrLabel)(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label);
		extern void (CODEGEN_FUNCPTR *GetProgramInterfaceiv)(GLuint program, GLenum programInterface, GLenum pname, GLint * params);
		extern GLuint (CODEGEN_FUNCPTR *GetProgramResourceIndex)(GLuint program, GLenum programInterface, const GLchar * name);
		extern GLint (CODEGEN_FUNCPTR *GetProgramResourceLocation)(GLuint program, GLenum programInterface, const GLchar * name);
		extern GLint (CODEGEN_FUNCPTR *GetProgramResourceLocationIndex)(GLuint program, GLenum programInterface, const GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetProgramResourceName)(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
		extern void (CODEGEN_FUNCPTR *GetProgramResourceiv)(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params);
		extern void (CODEGEN_FUNCPTR *InvalidateBufferData)(GLuint buffer);
		extern void (CODEGEN_FUNCPTR *InvalidateBufferSubData)(GLuint buffer, GLintptr offset, GLsizeiptr length);
		extern void (CODEGEN_FUNCPTR *InvalidateFramebuffer)(GLenum target, GLsizei numAttachments, const GLenum * attachments);
		extern void (CODEGEN_FUNCPTR *InvalidateSubFramebuffer)(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *InvalidateTexImage)(GLuint texture, GLint level);
		extern void (CODEGEN_FUNCPTR *InvalidateTexSubImage)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
		extern void (CODEGEN_FUNCPTR *MultiDrawArraysIndirect)(GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride);
		extern void (CODEGEN_FUNCPTR *MultiDrawElementsIndirect)(GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride);
		extern void (CODEGEN_FUNCPTR *ObjectLabel)(GLenum identifier, GLuint name, GLsizei length, const GLchar * label);
		extern void (CODEGEN_FUNCPTR *ObjectPtrLabel)(const void * ptr, GLsizei length, const GLchar * label);
		extern void (CODEGEN_FUNCPTR *PopDebugGroup)(void);
		extern void (CODEGEN_FUNCPTR *PushDebugGroup)(GLenum source, GLuint id, GLsizei length, const GLchar * message);
		extern void (CODEGEN_FUNCPTR *ShaderStorageBlockBinding)(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
		extern void (CODEGEN_FUNCPTR *TexBufferRange)(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
		extern void (CODEGEN_FUNCPTR *TexStorage2DMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
		extern void (CODEGEN_FUNCPTR *TexStorage3DMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
		extern void (CODEGEN_FUNCPTR *TextureView)(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
		extern void (CODEGEN_FUNCPTR *VertexAttribBinding)(GLuint attribindex, GLuint bindingindex);
		extern void (CODEGEN_FUNCPTR *VertexAttribFormat)(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
		extern void (CODEGEN_FUNCPTR *VertexAttribIFormat)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
		extern void (CODEGEN_FUNCPTR *VertexAttribLFormat)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
		extern void (CODEGEN_FUNCPTR *VertexBindingDivisor)(GLuint bindingindex, GLuint divisor);
		
		extern void (CODEGEN_FUNCPTR *BindBuffersBase)(GLenum target, GLuint first, GLsizei count, const GLuint * buffers);
		extern void (CODEGEN_FUNCPTR *BindBuffersRange)(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes);
		extern void (CODEGEN_FUNCPTR *BindImageTextures)(GLuint first, GLsizei count, const GLuint * textures);
		extern void (CODEGEN_FUNCPTR *BindSamplers)(GLuint first, GLsizei count, const GLuint * samplers);
		extern void (CODEGEN_FUNCPTR *BindTextures)(GLuint first, GLsizei count, const GLuint * textures);
		extern void (CODEGEN_FUNCPTR *BindVertexBuffers)(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides);
		extern void (CODEGEN_FUNCPTR *BufferStorage)(GLenum target, GLsizeiptr size, const void * data, GLbitfield flags);
		extern void (CODEGEN_FUNCPTR *ClearTexImage)(GLuint texture, GLint level, GLenum format, GLenum type, const void * data);
		extern void (CODEGEN_FUNCPTR *ClearTexSubImage)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * data);
		
		extern void (CODEGEN_FUNCPTR *BindTextureUnit)(GLuint unit, GLuint texture);
		extern void (CODEGEN_FUNCPTR *BlitNamedFramebuffer)(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
		extern GLenum (CODEGEN_FUNCPTR *CheckNamedFramebufferStatus)(GLuint framebuffer, GLenum target);
		extern void (CODEGEN_FUNCPTR *ClearNamedBufferData)(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data);
		extern void (CODEGEN_FUNCPTR *ClearNamedBufferSubData)(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data);
		extern void (CODEGEN_FUNCPTR *ClearNamedFramebufferfi)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat depth, GLint stencil);
		extern void (CODEGEN_FUNCPTR *ClearNamedFramebufferfv)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value);
		extern void (CODEGEN_FUNCPTR *ClearNamedFramebufferiv)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value);
		extern void (CODEGEN_FUNCPTR *ClearNamedFramebufferuiv)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value);
		extern void (CODEGEN_FUNCPTR *ClipControl)(GLenum origin, GLenum depth);
		extern void (CODEGEN_FUNCPTR *CompressedTextureSubImage1D)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *CompressedTextureSubImage2D)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *CompressedTextureSubImage3D)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
		extern void (CODEGEN_FUNCPTR *CopyNamedBufferSubData)(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
		extern void (CODEGEN_FUNCPTR *CopyTextureSubImage1D)(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
		extern void (CODEGEN_FUNCPTR *CopyTextureSubImage2D)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *CopyTextureSubImage3D)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *CreateBuffers)(GLsizei n, GLuint * buffers);
		extern void (CODEGEN_FUNCPTR *CreateFramebuffers)(GLsizei n, GLuint * framebuffers);
		extern void (CODEGEN_FUNCPTR *CreateProgramPipelines)(GLsizei n, GLuint * pipelines);
		extern void (CODEGEN_FUNCPTR *CreateQueries)(GLenum target, GLsizei n, GLuint * ids);
		extern void (CODEGEN_FUNCPTR *CreateRenderbuffers)(GLsizei n, GLuint * renderbuffers);
		extern void (CODEGEN_FUNCPTR *CreateSamplers)(GLsizei n, GLuint * samplers);
		extern void (CODEGEN_FUNCPTR *CreateTextures)(GLenum target, GLsizei n, GLuint * textures);
		extern void (CODEGEN_FUNCPTR *CreateTransformFeedbacks)(GLsizei n, GLuint * ids);
		extern void (CODEGEN_FUNCPTR *CreateVertexArrays)(GLsizei n, GLuint * arrays);
		extern void (CODEGEN_FUNCPTR *DisableVertexArrayAttrib)(GLuint vaobj, GLuint index);
		extern void (CODEGEN_FUNCPTR *EnableVertexArrayAttrib)(GLuint vaobj, GLuint index);
		extern void (CODEGEN_FUNCPTR *FlushMappedNamedBufferRange)(GLuint buffer, GLintptr offset, GLsizeiptr length);
		extern void (CODEGEN_FUNCPTR *GenerateTextureMipmap)(GLuint texture);
		extern void (CODEGEN_FUNCPTR *GetCompressedTextureImage)(GLuint texture, GLint level, GLsizei bufSize, void * pixels);
		extern void (CODEGEN_FUNCPTR *GetCompressedTextureSubImage)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void * pixels);
		extern GLenum (CODEGEN_FUNCPTR *GetGraphicsResetStatus)(void);
		extern void (CODEGEN_FUNCPTR *GetNamedBufferParameteri64v)(GLuint buffer, GLenum pname, GLint64 * params);
		extern void (CODEGEN_FUNCPTR *GetNamedBufferParameteriv)(GLuint buffer, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetNamedBufferPointerv)(GLuint buffer, GLenum pname, void ** params);
		extern void (CODEGEN_FUNCPTR *GetNamedBufferSubData)(GLuint buffer, GLintptr offset, GLsizeiptr size, void * data);
		extern void (CODEGEN_FUNCPTR *GetNamedFramebufferAttachmentParameteriv)(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetNamedFramebufferParameteriv)(GLuint framebuffer, GLenum pname, GLint * param);
		extern void (CODEGEN_FUNCPTR *GetNamedRenderbufferParameteriv)(GLuint renderbuffer, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetQueryBufferObjecti64v)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
		extern void (CODEGEN_FUNCPTR *GetQueryBufferObjectiv)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
		extern void (CODEGEN_FUNCPTR *GetQueryBufferObjectui64v)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
		extern void (CODEGEN_FUNCPTR *GetQueryBufferObjectuiv)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
		extern void (CODEGEN_FUNCPTR *GetTextureImage)(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
		extern void (CODEGEN_FUNCPTR *GetTextureLevelParameterfv)(GLuint texture, GLint level, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetTextureLevelParameteriv)(GLuint texture, GLint level, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetTextureParameterIiv)(GLuint texture, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetTextureParameterIuiv)(GLuint texture, GLenum pname, GLuint * params);
		extern void (CODEGEN_FUNCPTR *GetTextureParameterfv)(GLuint texture, GLenum pname, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetTextureParameteriv)(GLuint texture, GLenum pname, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetTextureSubImage)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
		extern void (CODEGEN_FUNCPTR *GetTransformFeedbacki64_v)(GLuint xfb, GLenum pname, GLuint index, GLint64 * param);
		extern void (CODEGEN_FUNCPTR *GetTransformFeedbacki_v)(GLuint xfb, GLenum pname, GLuint index, GLint * param);
		extern void (CODEGEN_FUNCPTR *GetTransformFeedbackiv)(GLuint xfb, GLenum pname, GLint * param);
		extern void (CODEGEN_FUNCPTR *GetVertexArrayIndexed64iv)(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param);
		extern void (CODEGEN_FUNCPTR *GetVertexArrayIndexediv)(GLuint vaobj, GLuint index, GLenum pname, GLint * param);
		extern void (CODEGEN_FUNCPTR *GetVertexArrayiv)(GLuint vaobj, GLenum pname, GLint * param);
		extern void (CODEGEN_FUNCPTR *GetnCompressedTexImage)(GLenum target, GLint lod, GLsizei bufSize, void * pixels);
		extern void (CODEGEN_FUNCPTR *GetnTexImage)(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
		extern void (CODEGEN_FUNCPTR *GetnUniformdv)(GLuint program, GLint location, GLsizei bufSize, GLdouble * params);
		extern void (CODEGEN_FUNCPTR *GetnUniformfv)(GLuint program, GLint location, GLsizei bufSize, GLfloat * params);
		extern void (CODEGEN_FUNCPTR *GetnUniformiv)(GLuint program, GLint location, GLsizei bufSize, GLint * params);
		extern void (CODEGEN_FUNCPTR *GetnUniformuiv)(GLuint program, GLint location, GLsizei bufSize, GLuint * params);
		extern void (CODEGEN_FUNCPTR *InvalidateNamedFramebufferData)(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments);
		extern void (CODEGEN_FUNCPTR *InvalidateNamedFramebufferSubData)(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height);
		extern void * (CODEGEN_FUNCPTR *MapNamedBuffer)(GLuint buffer, GLenum access);
		extern void * (CODEGEN_FUNCPTR *MapNamedBufferRange)(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
		extern void (CODEGEN_FUNCPTR *MemoryBarrierByRegion)(GLbitfield barriers);
		extern void (CODEGEN_FUNCPTR *NamedBufferData)(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage);
		extern void (CODEGEN_FUNCPTR *NamedBufferStorage)(GLuint buffer, GLsizeiptr size, const void * data, GLbitfield flags);
		extern void (CODEGEN_FUNCPTR *NamedBufferSubData)(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data);
		extern void (CODEGEN_FUNCPTR *NamedFramebufferDrawBuffer)(GLuint framebuffer, GLenum buf);
		extern void (CODEGEN_FUNCPTR *NamedFramebufferDrawBuffers)(GLuint framebuffer, GLsizei n, const GLenum * bufs);
		extern void (CODEGEN_FUNCPTR *NamedFramebufferParameteri)(GLuint framebuffer, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *NamedFramebufferReadBuffer)(GLuint framebuffer, GLenum src);
		extern void (CODEGEN_FUNCPTR *NamedFramebufferRenderbuffer)(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
		extern void (CODEGEN_FUNCPTR *NamedFramebufferTexture)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
		extern void (CODEGEN_FUNCPTR *NamedFramebufferTextureLayer)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
		extern void (CODEGEN_FUNCPTR *NamedRenderbufferStorage)(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *NamedRenderbufferStorageMultisample)(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *ReadnPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data);
		extern void (CODEGEN_FUNCPTR *TextureBarrier)(void);
		extern void (CODEGEN_FUNCPTR *TextureBuffer)(GLuint texture, GLenum internalformat, GLuint buffer);
		extern void (CODEGEN_FUNCPTR *TextureBufferRange)(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
		extern void (CODEGEN_FUNCPTR *TextureParameterIiv)(GLuint texture, GLenum pname, const GLint * params);
		extern void (CODEGEN_FUNCPTR *TextureParameterIuiv)(GLuint texture, GLenum pname, const GLuint * params);
		extern void (CODEGEN_FUNCPTR *TextureParameterf)(GLuint texture, GLenum pname, GLfloat param);
		extern void (CODEGEN_FUNCPTR *TextureParameterfv)(GLuint texture, GLenum pname, const GLfloat * param);
		extern void (CODEGEN_FUNCPTR *TextureParameteri)(GLuint texture, GLenum pname, GLint param);
		extern void (CODEGEN_FUNCPTR *TextureParameteriv)(GLuint texture, GLenum pname, const GLint * param);
		extern void (CODEGEN_FUNCPTR *TextureStorage1D)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
		extern void (CODEGEN_FUNCPTR *TextureStorage2D)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
		extern void (CODEGEN_FUNCPTR *TextureStorage2DMultisample)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
		extern void (CODEGEN_FUNCPTR *TextureStorage3D)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
		extern void (CODEGEN_FUNCPTR *TextureStorage3DMultisample)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
		extern void (CODEGEN_FUNCPTR *TextureSubImage1D)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *TextureSubImage2D)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *TextureSubImage3D)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
		extern void (CODEGEN_FUNCPTR *TransformFeedbackBufferBase)(GLuint xfb, GLuint index, GLuint buffer);
		extern void (CODEGEN_FUNCPTR *TransformFeedbackBufferRange)(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
		extern GLboolean (CODEGEN_FUNCPTR *UnmapNamedBuffer)(GLuint buffer);
		extern void (CODEGEN_FUNCPTR *VertexArrayAttribBinding)(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
		extern void (CODEGEN_FUNCPTR *VertexArrayAttribFormat)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
		extern void (CODEGEN_FUNCPTR *VertexArrayAttribIFormat)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
		extern void (CODEGEN_FUNCPTR *VertexArrayAttribLFormat)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
		extern void (CODEGEN_FUNCPTR *VertexArrayBindingDivisor)(GLuint vaobj, GLuint bindingindex, GLuint divisor);
		extern void (CODEGEN_FUNCPTR *VertexArrayElementBuffer)(GLuint vaobj, GLuint buffer);
		extern void (CODEGEN_FUNCPTR *VertexArrayVertexBuffer)(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
		extern void (CODEGEN_FUNCPTR *VertexArrayVertexBuffers)(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides);
		
	} //namespace _detail
	
	inline void Accum(GLenum op, GLfloat value){_detail::Accum(op, value);}
	inline void AlphaFunc(GLenum func, GLfloat ref){_detail::AlphaFunc(func, ref);}
	inline void Begin(GLenum mode){_detail::Begin(mode);}
	inline void Bitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap){_detail::Bitmap(width, height, xorig, yorig, xmove, ymove, bitmap);}
	inline void BlendFunc(GLenum sfactor, GLenum dfactor){_detail::BlendFunc(sfactor, dfactor);}
	inline void CallList(GLuint list){_detail::CallList(list);}
	inline void CallLists(GLsizei n, GLenum type, const void * lists){_detail::CallLists(n, type, lists);}
	inline void Clear(GLbitfield mask){_detail::Clear(mask);}
	inline void ClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){_detail::ClearAccum(red, green, blue, alpha);}
	inline void ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){_detail::ClearColor(red, green, blue, alpha);}
	inline void ClearDepth(GLdouble depth){_detail::ClearDepth(depth);}
	inline void ClearIndex(GLfloat c){_detail::ClearIndex(c);}
	inline void ClearStencil(GLint s){_detail::ClearStencil(s);}
	inline void ClipPlane(GLenum plane, const GLdouble * equation){_detail::ClipPlane(plane, equation);}
	inline void Color3b(GLbyte red, GLbyte green, GLbyte blue){_detail::Color3b(red, green, blue);}
	inline void Color3bv(const GLbyte * v){_detail::Color3bv(v);}
	inline void Color3d(GLdouble red, GLdouble green, GLdouble blue){_detail::Color3d(red, green, blue);}
	inline void Color3dv(const GLdouble * v){_detail::Color3dv(v);}
	inline void Color3f(GLfloat red, GLfloat green, GLfloat blue){_detail::Color3f(red, green, blue);}
	inline void Color3fv(const GLfloat * v){_detail::Color3fv(v);}
	inline void Color3i(GLint red, GLint green, GLint blue){_detail::Color3i(red, green, blue);}
	inline void Color3iv(const GLint * v){_detail::Color3iv(v);}
	inline void Color3s(GLshort red, GLshort green, GLshort blue){_detail::Color3s(red, green, blue);}
	inline void Color3sv(const GLshort * v){_detail::Color3sv(v);}
	inline void Color3ub(GLubyte red, GLubyte green, GLubyte blue){_detail::Color3ub(red, green, blue);}
	inline void Color3ubv(const GLubyte * v){_detail::Color3ubv(v);}
	inline void Color3ui(GLuint red, GLuint green, GLuint blue){_detail::Color3ui(red, green, blue);}
	inline void Color3uiv(const GLuint * v){_detail::Color3uiv(v);}
	inline void Color3us(GLushort red, GLushort green, GLushort blue){_detail::Color3us(red, green, blue);}
	inline void Color3usv(const GLushort * v){_detail::Color3usv(v);}
	inline void Color4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha){_detail::Color4b(red, green, blue, alpha);}
	inline void Color4bv(const GLbyte * v){_detail::Color4bv(v);}
	inline void Color4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha){_detail::Color4d(red, green, blue, alpha);}
	inline void Color4dv(const GLdouble * v){_detail::Color4dv(v);}
	inline void Color4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){_detail::Color4f(red, green, blue, alpha);}
	inline void Color4fv(const GLfloat * v){_detail::Color4fv(v);}
	inline void Color4i(GLint red, GLint green, GLint blue, GLint alpha){_detail::Color4i(red, green, blue, alpha);}
	inline void Color4iv(const GLint * v){_detail::Color4iv(v);}
	inline void Color4s(GLshort red, GLshort green, GLshort blue, GLshort alpha){_detail::Color4s(red, green, blue, alpha);}
	inline void Color4sv(const GLshort * v){_detail::Color4sv(v);}
	inline void Color4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha){_detail::Color4ub(red, green, blue, alpha);}
	inline void Color4ubv(const GLubyte * v){_detail::Color4ubv(v);}
	inline void Color4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha){_detail::Color4ui(red, green, blue, alpha);}
	inline void Color4uiv(const GLuint * v){_detail::Color4uiv(v);}
	inline void Color4us(GLushort red, GLushort green, GLushort blue, GLushort alpha){_detail::Color4us(red, green, blue, alpha);}
	inline void Color4usv(const GLushort * v){_detail::Color4usv(v);}
	inline void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha){_detail::ColorMask(red, green, blue, alpha);}
	inline void ColorMaterial(GLenum face, GLenum mode){_detail::ColorMaterial(face, mode);}
	inline void CopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type){_detail::CopyPixels(x, y, width, height, type);}
	inline void CullFace(GLenum mode){_detail::CullFace(mode);}
	inline void DeleteLists(GLuint list, GLsizei range){_detail::DeleteLists(list, range);}
	inline void DepthFunc(GLenum func){_detail::DepthFunc(func);}
	inline void DepthMask(GLboolean flag){_detail::DepthMask(flag);}
	inline void DepthRange(GLdouble ren_near, GLdouble ren_far){_detail::DepthRange(ren_near, ren_far);}
	inline void Disable(GLenum cap){_detail::Disable(cap);}
	inline void DrawBuffer(GLenum buf){_detail::DrawBuffer(buf);}
	inline void DrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels){_detail::DrawPixels(width, height, format, type, pixels);}
	inline void EdgeFlag(GLboolean flag){_detail::EdgeFlag(flag);}
	inline void EdgeFlagv(const GLboolean * flag){_detail::EdgeFlagv(flag);}
	inline void Enable(GLenum cap){_detail::Enable(cap);}
	inline void End(void){_detail::End();}
	inline void EndList(void){_detail::EndList();}
	inline void EvalCoord1d(GLdouble u){_detail::EvalCoord1d(u);}
	inline void EvalCoord1dv(const GLdouble * u){_detail::EvalCoord1dv(u);}
	inline void EvalCoord1f(GLfloat u){_detail::EvalCoord1f(u);}
	inline void EvalCoord1fv(const GLfloat * u){_detail::EvalCoord1fv(u);}
	inline void EvalCoord2d(GLdouble u, GLdouble v){_detail::EvalCoord2d(u, v);}
	inline void EvalCoord2dv(const GLdouble * u){_detail::EvalCoord2dv(u);}
	inline void EvalCoord2f(GLfloat u, GLfloat v){_detail::EvalCoord2f(u, v);}
	inline void EvalCoord2fv(const GLfloat * u){_detail::EvalCoord2fv(u);}
	inline void EvalMesh1(GLenum mode, GLint i1, GLint i2){_detail::EvalMesh1(mode, i1, i2);}
	inline void EvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2){_detail::EvalMesh2(mode, i1, i2, j1, j2);}
	inline void EvalPoint1(GLint i){_detail::EvalPoint1(i);}
	inline void EvalPoint2(GLint i, GLint j){_detail::EvalPoint2(i, j);}
	inline void FeedbackBuffer(GLsizei size, GLenum type, GLfloat * buffer){_detail::FeedbackBuffer(size, type, buffer);}
	inline void Finish(void){_detail::Finish();}
	inline void Flush(void){_detail::Flush();}
	inline void Fogf(GLenum pname, GLfloat param){_detail::Fogf(pname, param);}
	inline void Fogfv(GLenum pname, const GLfloat * params){_detail::Fogfv(pname, params);}
	inline void Fogi(GLenum pname, GLint param){_detail::Fogi(pname, param);}
	inline void Fogiv(GLenum pname, const GLint * params){_detail::Fogiv(pname, params);}
	inline void FrontFace(GLenum mode){_detail::FrontFace(mode);}
	inline void Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar){_detail::Frustum(left, right, bottom, top, zNear, zFar);}
	inline GLuint GenLists(GLsizei range){return _detail::GenLists(range);}
	inline void GetBooleanv(GLenum pname, GLboolean * data){_detail::GetBooleanv(pname, data);}
	inline void GetClipPlane(GLenum plane, GLdouble * equation){_detail::GetClipPlane(plane, equation);}
	inline void GetDoublev(GLenum pname, GLdouble * data){_detail::GetDoublev(pname, data);}
	inline GLenum GetError(void){return _detail::GetError();}
	inline void GetFloatv(GLenum pname, GLfloat * data){_detail::GetFloatv(pname, data);}
	inline void GetIntegerv(GLenum pname, GLint * data){_detail::GetIntegerv(pname, data);}
	inline void GetLightfv(GLenum light, GLenum pname, GLfloat * params){_detail::GetLightfv(light, pname, params);}
	inline void GetLightiv(GLenum light, GLenum pname, GLint * params){_detail::GetLightiv(light, pname, params);}
	inline void GetMapdv(GLenum target, GLenum query, GLdouble * v){_detail::GetMapdv(target, query, v);}
	inline void GetMapfv(GLenum target, GLenum query, GLfloat * v){_detail::GetMapfv(target, query, v);}
	inline void GetMapiv(GLenum target, GLenum query, GLint * v){_detail::GetMapiv(target, query, v);}
	inline void GetMaterialfv(GLenum face, GLenum pname, GLfloat * params){_detail::GetMaterialfv(face, pname, params);}
	inline void GetMaterialiv(GLenum face, GLenum pname, GLint * params){_detail::GetMaterialiv(face, pname, params);}
	inline void GetPixelMapfv(GLenum map, GLfloat * values){_detail::GetPixelMapfv(map, values);}
	inline void GetPixelMapuiv(GLenum map, GLuint * values){_detail::GetPixelMapuiv(map, values);}
	inline void GetPixelMapusv(GLenum map, GLushort * values){_detail::GetPixelMapusv(map, values);}
	inline void GetPolygonStipple(GLubyte * mask){_detail::GetPolygonStipple(mask);}
	inline const GLubyte * GetString(GLenum name){return _detail::GetString(name);}
	inline void GetTexEnvfv(GLenum target, GLenum pname, GLfloat * params){_detail::GetTexEnvfv(target, pname, params);}
	inline void GetTexEnviv(GLenum target, GLenum pname, GLint * params){_detail::GetTexEnviv(target, pname, params);}
	inline void GetTexGendv(GLenum coord, GLenum pname, GLdouble * params){_detail::GetTexGendv(coord, pname, params);}
	inline void GetTexGenfv(GLenum coord, GLenum pname, GLfloat * params){_detail::GetTexGenfv(coord, pname, params);}
	inline void GetTexGeniv(GLenum coord, GLenum pname, GLint * params){_detail::GetTexGeniv(coord, pname, params);}
	inline void GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels){_detail::GetTexImage(target, level, format, type, pixels);}
	inline void GetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params){_detail::GetTexLevelParameterfv(target, level, pname, params);}
	inline void GetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params){_detail::GetTexLevelParameteriv(target, level, pname, params);}
	inline void GetTexParameterfv(GLenum target, GLenum pname, GLfloat * params){_detail::GetTexParameterfv(target, pname, params);}
	inline void GetTexParameteriv(GLenum target, GLenum pname, GLint * params){_detail::GetTexParameteriv(target, pname, params);}
	inline void Hint(GLenum target, GLenum mode){_detail::Hint(target, mode);}
	inline void IndexMask(GLuint mask){_detail::IndexMask(mask);}
	inline void Indexd(GLdouble c){_detail::Indexd(c);}
	inline void Indexdv(const GLdouble * c){_detail::Indexdv(c);}
	inline void Indexf(GLfloat c){_detail::Indexf(c);}
	inline void Indexfv(const GLfloat * c){_detail::Indexfv(c);}
	inline void Indexi(GLint c){_detail::Indexi(c);}
	inline void Indexiv(const GLint * c){_detail::Indexiv(c);}
	inline void Indexs(GLshort c){_detail::Indexs(c);}
	inline void Indexsv(const GLshort * c){_detail::Indexsv(c);}
	inline void InitNames(void){_detail::InitNames();}
	inline GLboolean IsEnabled(GLenum cap){return _detail::IsEnabled(cap);}
	inline GLboolean IsList(GLuint list){return _detail::IsList(list);}
	inline void LightModelf(GLenum pname, GLfloat param){_detail::LightModelf(pname, param);}
	inline void LightModelfv(GLenum pname, const GLfloat * params){_detail::LightModelfv(pname, params);}
	inline void LightModeli(GLenum pname, GLint param){_detail::LightModeli(pname, param);}
	inline void LightModeliv(GLenum pname, const GLint * params){_detail::LightModeliv(pname, params);}
	inline void Lightf(GLenum light, GLenum pname, GLfloat param){_detail::Lightf(light, pname, param);}
	inline void Lightfv(GLenum light, GLenum pname, const GLfloat * params){_detail::Lightfv(light, pname, params);}
	inline void Lighti(GLenum light, GLenum pname, GLint param){_detail::Lighti(light, pname, param);}
	inline void Lightiv(GLenum light, GLenum pname, const GLint * params){_detail::Lightiv(light, pname, params);}
	inline void LineStipple(GLint factor, GLushort pattern){_detail::LineStipple(factor, pattern);}
	inline void LineWidth(GLfloat width){_detail::LineWidth(width);}
	inline void ListBase(GLuint base){_detail::ListBase(base);}
	inline void LoadIdentity(void){_detail::LoadIdentity();}
	inline void LoadMatrixd(const GLdouble * m){_detail::LoadMatrixd(m);}
	inline void LoadMatrixf(const GLfloat * m){_detail::LoadMatrixf(m);}
	inline void LoadName(GLuint name){_detail::LoadName(name);}
	inline void LogicOp(GLenum opcode){_detail::LogicOp(opcode);}
	inline void Map1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points){_detail::Map1d(target, u1, u2, stride, order, points);}
	inline void Map1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points){_detail::Map1f(target, u1, u2, stride, order, points);}
	inline void Map2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points){_detail::Map2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);}
	inline void Map2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points){_detail::Map2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);}
	inline void MapGrid1d(GLint un, GLdouble u1, GLdouble u2){_detail::MapGrid1d(un, u1, u2);}
	inline void MapGrid1f(GLint un, GLfloat u1, GLfloat u2){_detail::MapGrid1f(un, u1, u2);}
	inline void MapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2){_detail::MapGrid2d(un, u1, u2, vn, v1, v2);}
	inline void MapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2){_detail::MapGrid2f(un, u1, u2, vn, v1, v2);}
	inline void Materialf(GLenum face, GLenum pname, GLfloat param){_detail::Materialf(face, pname, param);}
	inline void Materialfv(GLenum face, GLenum pname, const GLfloat * params){_detail::Materialfv(face, pname, params);}
	inline void Materiali(GLenum face, GLenum pname, GLint param){_detail::Materiali(face, pname, param);}
	inline void Materialiv(GLenum face, GLenum pname, const GLint * params){_detail::Materialiv(face, pname, params);}
	inline void MatrixMode(GLenum mode){_detail::MatrixMode(mode);}
	inline void MultMatrixd(const GLdouble * m){_detail::MultMatrixd(m);}
	inline void MultMatrixf(const GLfloat * m){_detail::MultMatrixf(m);}
	inline void NewList(GLuint list, GLenum mode){_detail::NewList(list, mode);}
	inline void Normal3b(GLbyte nx, GLbyte ny, GLbyte nz){_detail::Normal3b(nx, ny, nz);}
	inline void Normal3bv(const GLbyte * v){_detail::Normal3bv(v);}
	inline void Normal3d(GLdouble nx, GLdouble ny, GLdouble nz){_detail::Normal3d(nx, ny, nz);}
	inline void Normal3dv(const GLdouble * v){_detail::Normal3dv(v);}
	inline void Normal3f(GLfloat nx, GLfloat ny, GLfloat nz){_detail::Normal3f(nx, ny, nz);}
	inline void Normal3fv(const GLfloat * v){_detail::Normal3fv(v);}
	inline void Normal3i(GLint nx, GLint ny, GLint nz){_detail::Normal3i(nx, ny, nz);}
	inline void Normal3iv(const GLint * v){_detail::Normal3iv(v);}
	inline void Normal3s(GLshort nx, GLshort ny, GLshort nz){_detail::Normal3s(nx, ny, nz);}
	inline void Normal3sv(const GLshort * v){_detail::Normal3sv(v);}
	inline void Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar){_detail::Ortho(left, right, bottom, top, zNear, zFar);}
	inline void PassThrough(GLfloat token){_detail::PassThrough(token);}
	inline void PixelMapfv(GLenum map, GLsizei mapsize, const GLfloat * values){_detail::PixelMapfv(map, mapsize, values);}
	inline void PixelMapuiv(GLenum map, GLsizei mapsize, const GLuint * values){_detail::PixelMapuiv(map, mapsize, values);}
	inline void PixelMapusv(GLenum map, GLsizei mapsize, const GLushort * values){_detail::PixelMapusv(map, mapsize, values);}
	inline void PixelStoref(GLenum pname, GLfloat param){_detail::PixelStoref(pname, param);}
	inline void PixelStorei(GLenum pname, GLint param){_detail::PixelStorei(pname, param);}
	inline void PixelTransferf(GLenum pname, GLfloat param){_detail::PixelTransferf(pname, param);}
	inline void PixelTransferi(GLenum pname, GLint param){_detail::PixelTransferi(pname, param);}
	inline void PixelZoom(GLfloat xfactor, GLfloat yfactor){_detail::PixelZoom(xfactor, yfactor);}
	inline void PointSize(GLfloat size){_detail::PointSize(size);}
	inline void PolygonMode(GLenum face, GLenum mode){_detail::PolygonMode(face, mode);}
	inline void PolygonStipple(const GLubyte * mask){_detail::PolygonStipple(mask);}
	inline void PopAttrib(void){_detail::PopAttrib();}
	inline void PopMatrix(void){_detail::PopMatrix();}
	inline void PopName(void){_detail::PopName();}
	inline void PushAttrib(GLbitfield mask){_detail::PushAttrib(mask);}
	inline void PushMatrix(void){_detail::PushMatrix();}
	inline void PushName(GLuint name){_detail::PushName(name);}
	inline void RasterPos2d(GLdouble x, GLdouble y){_detail::RasterPos2d(x, y);}
	inline void RasterPos2dv(const GLdouble * v){_detail::RasterPos2dv(v);}
	inline void RasterPos2f(GLfloat x, GLfloat y){_detail::RasterPos2f(x, y);}
	inline void RasterPos2fv(const GLfloat * v){_detail::RasterPos2fv(v);}
	inline void RasterPos2i(GLint x, GLint y){_detail::RasterPos2i(x, y);}
	inline void RasterPos2iv(const GLint * v){_detail::RasterPos2iv(v);}
	inline void RasterPos2s(GLshort x, GLshort y){_detail::RasterPos2s(x, y);}
	inline void RasterPos2sv(const GLshort * v){_detail::RasterPos2sv(v);}
	inline void RasterPos3d(GLdouble x, GLdouble y, GLdouble z){_detail::RasterPos3d(x, y, z);}
	inline void RasterPos3dv(const GLdouble * v){_detail::RasterPos3dv(v);}
	inline void RasterPos3f(GLfloat x, GLfloat y, GLfloat z){_detail::RasterPos3f(x, y, z);}
	inline void RasterPos3fv(const GLfloat * v){_detail::RasterPos3fv(v);}
	inline void RasterPos3i(GLint x, GLint y, GLint z){_detail::RasterPos3i(x, y, z);}
	inline void RasterPos3iv(const GLint * v){_detail::RasterPos3iv(v);}
	inline void RasterPos3s(GLshort x, GLshort y, GLshort z){_detail::RasterPos3s(x, y, z);}
	inline void RasterPos3sv(const GLshort * v){_detail::RasterPos3sv(v);}
	inline void RasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w){_detail::RasterPos4d(x, y, z, w);}
	inline void RasterPos4dv(const GLdouble * v){_detail::RasterPos4dv(v);}
	inline void RasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w){_detail::RasterPos4f(x, y, z, w);}
	inline void RasterPos4fv(const GLfloat * v){_detail::RasterPos4fv(v);}
	inline void RasterPos4i(GLint x, GLint y, GLint z, GLint w){_detail::RasterPos4i(x, y, z, w);}
	inline void RasterPos4iv(const GLint * v){_detail::RasterPos4iv(v);}
	inline void RasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w){_detail::RasterPos4s(x, y, z, w);}
	inline void RasterPos4sv(const GLshort * v){_detail::RasterPos4sv(v);}
	inline void ReadBuffer(GLenum src){_detail::ReadBuffer(src);}
	inline void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels){_detail::ReadPixels(x, y, width, height, format, type, pixels);}
	inline void Rectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2){_detail::Rectd(x1, y1, x2, y2);}
	inline void Rectdv(const GLdouble * v1, const GLdouble * v2){_detail::Rectdv(v1, v2);}
	inline void Rectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){_detail::Rectf(x1, y1, x2, y2);}
	inline void Rectfv(const GLfloat * v1, const GLfloat * v2){_detail::Rectfv(v1, v2);}
	inline void Recti(GLint x1, GLint y1, GLint x2, GLint y2){_detail::Recti(x1, y1, x2, y2);}
	inline void Rectiv(const GLint * v1, const GLint * v2){_detail::Rectiv(v1, v2);}
	inline void Rects(GLshort x1, GLshort y1, GLshort x2, GLshort y2){_detail::Rects(x1, y1, x2, y2);}
	inline void Rectsv(const GLshort * v1, const GLshort * v2){_detail::Rectsv(v1, v2);}
	inline GLint RenderMode(GLenum mode){return _detail::RenderMode(mode);}
	inline void Rotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z){_detail::Rotated(angle, x, y, z);}
	inline void Rotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z){_detail::Rotatef(angle, x, y, z);}
	inline void Scaled(GLdouble x, GLdouble y, GLdouble z){_detail::Scaled(x, y, z);}
	inline void Scalef(GLfloat x, GLfloat y, GLfloat z){_detail::Scalef(x, y, z);}
	inline void Scissor(GLint x, GLint y, GLsizei width, GLsizei height){_detail::Scissor(x, y, width, height);}
	inline void SelectBuffer(GLsizei size, GLuint * buffer){_detail::SelectBuffer(size, buffer);}
	inline void ShadeModel(GLenum mode){_detail::ShadeModel(mode);}
	inline void StencilFunc(GLenum func, GLint ref, GLuint mask){_detail::StencilFunc(func, ref, mask);}
	inline void StencilMask(GLuint mask){_detail::StencilMask(mask);}
	inline void StencilOp(GLenum fail, GLenum zfail, GLenum zpass){_detail::StencilOp(fail, zfail, zpass);}
	inline void TexCoord1d(GLdouble s){_detail::TexCoord1d(s);}
	inline void TexCoord1dv(const GLdouble * v){_detail::TexCoord1dv(v);}
	inline void TexCoord1f(GLfloat s){_detail::TexCoord1f(s);}
	inline void TexCoord1fv(const GLfloat * v){_detail::TexCoord1fv(v);}
	inline void TexCoord1i(GLint s){_detail::TexCoord1i(s);}
	inline void TexCoord1iv(const GLint * v){_detail::TexCoord1iv(v);}
	inline void TexCoord1s(GLshort s){_detail::TexCoord1s(s);}
	inline void TexCoord1sv(const GLshort * v){_detail::TexCoord1sv(v);}
	inline void TexCoord2d(GLdouble s, GLdouble t){_detail::TexCoord2d(s, t);}
	inline void TexCoord2dv(const GLdouble * v){_detail::TexCoord2dv(v);}
	inline void TexCoord2f(GLfloat s, GLfloat t){_detail::TexCoord2f(s, t);}
	inline void TexCoord2fv(const GLfloat * v){_detail::TexCoord2fv(v);}
	inline void TexCoord2i(GLint s, GLint t){_detail::TexCoord2i(s, t);}
	inline void TexCoord2iv(const GLint * v){_detail::TexCoord2iv(v);}
	inline void TexCoord2s(GLshort s, GLshort t){_detail::TexCoord2s(s, t);}
	inline void TexCoord2sv(const GLshort * v){_detail::TexCoord2sv(v);}
	inline void TexCoord3d(GLdouble s, GLdouble t, GLdouble r){_detail::TexCoord3d(s, t, r);}
	inline void TexCoord3dv(const GLdouble * v){_detail::TexCoord3dv(v);}
	inline void TexCoord3f(GLfloat s, GLfloat t, GLfloat r){_detail::TexCoord3f(s, t, r);}
	inline void TexCoord3fv(const GLfloat * v){_detail::TexCoord3fv(v);}
	inline void TexCoord3i(GLint s, GLint t, GLint r){_detail::TexCoord3i(s, t, r);}
	inline void TexCoord3iv(const GLint * v){_detail::TexCoord3iv(v);}
	inline void TexCoord3s(GLshort s, GLshort t, GLshort r){_detail::TexCoord3s(s, t, r);}
	inline void TexCoord3sv(const GLshort * v){_detail::TexCoord3sv(v);}
	inline void TexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q){_detail::TexCoord4d(s, t, r, q);}
	inline void TexCoord4dv(const GLdouble * v){_detail::TexCoord4dv(v);}
	inline void TexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q){_detail::TexCoord4f(s, t, r, q);}
	inline void TexCoord4fv(const GLfloat * v){_detail::TexCoord4fv(v);}
	inline void TexCoord4i(GLint s, GLint t, GLint r, GLint q){_detail::TexCoord4i(s, t, r, q);}
	inline void TexCoord4iv(const GLint * v){_detail::TexCoord4iv(v);}
	inline void TexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q){_detail::TexCoord4s(s, t, r, q);}
	inline void TexCoord4sv(const GLshort * v){_detail::TexCoord4sv(v);}
	inline void TexEnvf(GLenum target, GLenum pname, GLfloat param){_detail::TexEnvf(target, pname, param);}
	inline void TexEnvfv(GLenum target, GLenum pname, const GLfloat * params){_detail::TexEnvfv(target, pname, params);}
	inline void TexEnvi(GLenum target, GLenum pname, GLint param){_detail::TexEnvi(target, pname, param);}
	inline void TexEnviv(GLenum target, GLenum pname, const GLint * params){_detail::TexEnviv(target, pname, params);}
	inline void TexGend(GLenum coord, GLenum pname, GLdouble param){_detail::TexGend(coord, pname, param);}
	inline void TexGendv(GLenum coord, GLenum pname, const GLdouble * params){_detail::TexGendv(coord, pname, params);}
	inline void TexGenf(GLenum coord, GLenum pname, GLfloat param){_detail::TexGenf(coord, pname, param);}
	inline void TexGenfv(GLenum coord, GLenum pname, const GLfloat * params){_detail::TexGenfv(coord, pname, params);}
	inline void TexGeni(GLenum coord, GLenum pname, GLint param){_detail::TexGeni(coord, pname, param);}
	inline void TexGeniv(GLenum coord, GLenum pname, const GLint * params){_detail::TexGeniv(coord, pname, params);}
	inline void TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels){_detail::TexImage1D(target, level, internalformat, width, border, format, type, pixels);}
	inline void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels){_detail::TexImage2D(target, level, internalformat, width, height, border, format, type, pixels);}
	inline void TexParameterf(GLenum target, GLenum pname, GLfloat param){_detail::TexParameterf(target, pname, param);}
	inline void TexParameterfv(GLenum target, GLenum pname, const GLfloat * params){_detail::TexParameterfv(target, pname, params);}
	inline void TexParameteri(GLenum target, GLenum pname, GLint param){_detail::TexParameteri(target, pname, param);}
	inline void TexParameteriv(GLenum target, GLenum pname, const GLint * params){_detail::TexParameteriv(target, pname, params);}
	inline void Translated(GLdouble x, GLdouble y, GLdouble z){_detail::Translated(x, y, z);}
	inline void Translatef(GLfloat x, GLfloat y, GLfloat z){_detail::Translatef(x, y, z);}
	inline void Vertex2d(GLdouble x, GLdouble y){_detail::Vertex2d(x, y);}
	inline void Vertex2dv(const GLdouble * v){_detail::Vertex2dv(v);}
	inline void Vertex2f(GLfloat x, GLfloat y){_detail::Vertex2f(x, y);}
	inline void Vertex2fv(const GLfloat * v){_detail::Vertex2fv(v);}
	inline void Vertex2i(GLint x, GLint y){_detail::Vertex2i(x, y);}
	inline void Vertex2iv(const GLint * v){_detail::Vertex2iv(v);}
	inline void Vertex2s(GLshort x, GLshort y){_detail::Vertex2s(x, y);}
	inline void Vertex2sv(const GLshort * v){_detail::Vertex2sv(v);}
	inline void Vertex3d(GLdouble x, GLdouble y, GLdouble z){_detail::Vertex3d(x, y, z);}
	inline void Vertex3dv(const GLdouble * v){_detail::Vertex3dv(v);}
	inline void Vertex3f(GLfloat x, GLfloat y, GLfloat z){_detail::Vertex3f(x, y, z);}
	inline void Vertex3fv(const GLfloat * v){_detail::Vertex3fv(v);}
	inline void Vertex3i(GLint x, GLint y, GLint z){_detail::Vertex3i(x, y, z);}
	inline void Vertex3iv(const GLint * v){_detail::Vertex3iv(v);}
	inline void Vertex3s(GLshort x, GLshort y, GLshort z){_detail::Vertex3s(x, y, z);}
	inline void Vertex3sv(const GLshort * v){_detail::Vertex3sv(v);}
	inline void Vertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w){_detail::Vertex4d(x, y, z, w);}
	inline void Vertex4dv(const GLdouble * v){_detail::Vertex4dv(v);}
	inline void Vertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w){_detail::Vertex4f(x, y, z, w);}
	inline void Vertex4fv(const GLfloat * v){_detail::Vertex4fv(v);}
	inline void Vertex4i(GLint x, GLint y, GLint z, GLint w){_detail::Vertex4i(x, y, z, w);}
	inline void Vertex4iv(const GLint * v){_detail::Vertex4iv(v);}
	inline void Vertex4s(GLshort x, GLshort y, GLshort z, GLshort w){_detail::Vertex4s(x, y, z, w);}
	inline void Vertex4sv(const GLshort * v){_detail::Vertex4sv(v);}
	inline void Viewport(GLint x, GLint y, GLsizei width, GLsizei height){_detail::Viewport(x, y, width, height);}
	
	inline GLboolean AreTexturesResident(GLsizei n, const GLuint * textures, GLboolean * residences){return _detail::AreTexturesResident(n, textures, residences);}
	inline void ArrayElement(GLint i){_detail::ArrayElement(i);}
	inline void BindTexture(GLenum target, GLuint texture){_detail::BindTexture(target, texture);}
	inline void ColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer){_detail::ColorPointer(size, type, stride, pointer);}
	inline void CopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border){_detail::CopyTexImage1D(target, level, internalformat, x, y, width, border);}
	inline void CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border){_detail::CopyTexImage2D(target, level, internalformat, x, y, width, height, border);}
	inline void CopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width){_detail::CopyTexSubImage1D(target, level, xoffset, x, y, width);}
	inline void CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){_detail::CopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);}
	inline void DeleteTextures(GLsizei n, const GLuint * textures){_detail::DeleteTextures(n, textures);}
	inline void DisableClientState(GLenum ren_array){_detail::DisableClientState(ren_array);}
	inline void DrawArrays(GLenum mode, GLint first, GLsizei count){_detail::DrawArrays(mode, first, count);}
	inline void DrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices){_detail::DrawElements(mode, count, type, indices);}
	inline void EdgeFlagPointer(GLsizei stride, const void * pointer){_detail::EdgeFlagPointer(stride, pointer);}
	inline void EnableClientState(GLenum ren_array){_detail::EnableClientState(ren_array);}
	inline void GenTextures(GLsizei n, GLuint * textures){_detail::GenTextures(n, textures);}
	inline void GetPointerv(GLenum pname, void ** params){_detail::GetPointerv(pname, params);}
	inline void IndexPointer(GLenum type, GLsizei stride, const void * pointer){_detail::IndexPointer(type, stride, pointer);}
	inline void Indexub(GLubyte c){_detail::Indexub(c);}
	inline void Indexubv(const GLubyte * c){_detail::Indexubv(c);}
	inline void InterleavedArrays(GLenum format, GLsizei stride, const void * pointer){_detail::InterleavedArrays(format, stride, pointer);}
	inline GLboolean IsTexture(GLuint texture){return _detail::IsTexture(texture);}
	inline void NormalPointer(GLenum type, GLsizei stride, const void * pointer){_detail::NormalPointer(type, stride, pointer);}
	inline void PolygonOffset(GLfloat factor, GLfloat units){_detail::PolygonOffset(factor, units);}
	inline void PopClientAttrib(void){_detail::PopClientAttrib();}
	inline void PrioritizeTextures(GLsizei n, const GLuint * textures, const GLfloat * priorities){_detail::PrioritizeTextures(n, textures, priorities);}
	inline void PushClientAttrib(GLbitfield mask){_detail::PushClientAttrib(mask);}
	inline void TexCoordPointer(GLint size, GLenum type, GLsizei stride, const void * pointer){_detail::TexCoordPointer(size, type, stride, pointer);}
	inline void TexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels){_detail::TexSubImage1D(target, level, xoffset, width, format, type, pixels);}
	inline void TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels){_detail::TexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);}
	inline void VertexPointer(GLint size, GLenum type, GLsizei stride, const void * pointer){_detail::VertexPointer(size, type, stride, pointer);}
	
	inline void CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){_detail::CopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);}
	inline void DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices){_detail::DrawRangeElements(mode, start, end, count, type, indices);}
	inline void TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels){_detail::TexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);}
	inline void TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels){_detail::TexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);}
	
	inline void ActiveTexture(GLenum texture){_detail::ActiveTexture(texture);}
	inline void ClientActiveTexture(GLenum texture){_detail::ClientActiveTexture(texture);}
	inline void CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data){_detail::CompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);}
	inline void CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data){_detail::CompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);}
	inline void CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data){_detail::CompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);}
	inline void CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data){_detail::CompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);}
	inline void CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data){_detail::CompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);}
	inline void CompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data){_detail::CompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);}
	inline void GetCompressedTexImage(GLenum target, GLint level, void * img){_detail::GetCompressedTexImage(target, level, img);}
	inline void LoadTransposeMatrixd(const GLdouble * m){_detail::LoadTransposeMatrixd(m);}
	inline void LoadTransposeMatrixf(const GLfloat * m){_detail::LoadTransposeMatrixf(m);}
	inline void MultTransposeMatrixd(const GLdouble * m){_detail::MultTransposeMatrixd(m);}
	inline void MultTransposeMatrixf(const GLfloat * m){_detail::MultTransposeMatrixf(m);}
	inline void MultiTexCoord1d(GLenum target, GLdouble s){_detail::MultiTexCoord1d(target, s);}
	inline void MultiTexCoord1dv(GLenum target, const GLdouble * v){_detail::MultiTexCoord1dv(target, v);}
	inline void MultiTexCoord1f(GLenum target, GLfloat s){_detail::MultiTexCoord1f(target, s);}
	inline void MultiTexCoord1fv(GLenum target, const GLfloat * v){_detail::MultiTexCoord1fv(target, v);}
	inline void MultiTexCoord1i(GLenum target, GLint s){_detail::MultiTexCoord1i(target, s);}
	inline void MultiTexCoord1iv(GLenum target, const GLint * v){_detail::MultiTexCoord1iv(target, v);}
	inline void MultiTexCoord1s(GLenum target, GLshort s){_detail::MultiTexCoord1s(target, s);}
	inline void MultiTexCoord1sv(GLenum target, const GLshort * v){_detail::MultiTexCoord1sv(target, v);}
	inline void MultiTexCoord2d(GLenum target, GLdouble s, GLdouble t){_detail::MultiTexCoord2d(target, s, t);}
	inline void MultiTexCoord2dv(GLenum target, const GLdouble * v){_detail::MultiTexCoord2dv(target, v);}
	inline void MultiTexCoord2f(GLenum target, GLfloat s, GLfloat t){_detail::MultiTexCoord2f(target, s, t);}
	inline void MultiTexCoord2fv(GLenum target, const GLfloat * v){_detail::MultiTexCoord2fv(target, v);}
	inline void MultiTexCoord2i(GLenum target, GLint s, GLint t){_detail::MultiTexCoord2i(target, s, t);}
	inline void MultiTexCoord2iv(GLenum target, const GLint * v){_detail::MultiTexCoord2iv(target, v);}
	inline void MultiTexCoord2s(GLenum target, GLshort s, GLshort t){_detail::MultiTexCoord2s(target, s, t);}
	inline void MultiTexCoord2sv(GLenum target, const GLshort * v){_detail::MultiTexCoord2sv(target, v);}
	inline void MultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r){_detail::MultiTexCoord3d(target, s, t, r);}
	inline void MultiTexCoord3dv(GLenum target, const GLdouble * v){_detail::MultiTexCoord3dv(target, v);}
	inline void MultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r){_detail::MultiTexCoord3f(target, s, t, r);}
	inline void MultiTexCoord3fv(GLenum target, const GLfloat * v){_detail::MultiTexCoord3fv(target, v);}
	inline void MultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r){_detail::MultiTexCoord3i(target, s, t, r);}
	inline void MultiTexCoord3iv(GLenum target, const GLint * v){_detail::MultiTexCoord3iv(target, v);}
	inline void MultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r){_detail::MultiTexCoord3s(target, s, t, r);}
	inline void MultiTexCoord3sv(GLenum target, const GLshort * v){_detail::MultiTexCoord3sv(target, v);}
	inline void MultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q){_detail::MultiTexCoord4d(target, s, t, r, q);}
	inline void MultiTexCoord4dv(GLenum target, const GLdouble * v){_detail::MultiTexCoord4dv(target, v);}
	inline void MultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q){_detail::MultiTexCoord4f(target, s, t, r, q);}
	inline void MultiTexCoord4fv(GLenum target, const GLfloat * v){_detail::MultiTexCoord4fv(target, v);}
	inline void MultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q){_detail::MultiTexCoord4i(target, s, t, r, q);}
	inline void MultiTexCoord4iv(GLenum target, const GLint * v){_detail::MultiTexCoord4iv(target, v);}
	inline void MultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q){_detail::MultiTexCoord4s(target, s, t, r, q);}
	inline void MultiTexCoord4sv(GLenum target, const GLshort * v){_detail::MultiTexCoord4sv(target, v);}
	inline void SampleCoverage(GLfloat value, GLboolean invert){_detail::SampleCoverage(value, invert);}
	
	inline void BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){_detail::BlendColor(red, green, blue, alpha);}
	inline void BlendEquation(GLenum mode){_detail::BlendEquation(mode);}
	inline void BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha){_detail::BlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);}
	inline void FogCoordPointer(GLenum type, GLsizei stride, const void * pointer){_detail::FogCoordPointer(type, stride, pointer);}
	inline void FogCoordd(GLdouble coord){_detail::FogCoordd(coord);}
	inline void FogCoorddv(const GLdouble * coord){_detail::FogCoorddv(coord);}
	inline void FogCoordf(GLfloat coord){_detail::FogCoordf(coord);}
	inline void FogCoordfv(const GLfloat * coord){_detail::FogCoordfv(coord);}
	inline void MultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount){_detail::MultiDrawArrays(mode, first, count, drawcount);}
	inline void MultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount){_detail::MultiDrawElements(mode, count, type, indices, drawcount);}
	inline void PointParameterf(GLenum pname, GLfloat param){_detail::PointParameterf(pname, param);}
	inline void PointParameterfv(GLenum pname, const GLfloat * params){_detail::PointParameterfv(pname, params);}
	inline void PointParameteri(GLenum pname, GLint param){_detail::PointParameteri(pname, param);}
	inline void PointParameteriv(GLenum pname, const GLint * params){_detail::PointParameteriv(pname, params);}
	inline void SecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue){_detail::SecondaryColor3b(red, green, blue);}
	inline void SecondaryColor3bv(const GLbyte * v){_detail::SecondaryColor3bv(v);}
	inline void SecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue){_detail::SecondaryColor3d(red, green, blue);}
	inline void SecondaryColor3dv(const GLdouble * v){_detail::SecondaryColor3dv(v);}
	inline void SecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue){_detail::SecondaryColor3f(red, green, blue);}
	inline void SecondaryColor3fv(const GLfloat * v){_detail::SecondaryColor3fv(v);}
	inline void SecondaryColor3i(GLint red, GLint green, GLint blue){_detail::SecondaryColor3i(red, green, blue);}
	inline void SecondaryColor3iv(const GLint * v){_detail::SecondaryColor3iv(v);}
	inline void SecondaryColor3s(GLshort red, GLshort green, GLshort blue){_detail::SecondaryColor3s(red, green, blue);}
	inline void SecondaryColor3sv(const GLshort * v){_detail::SecondaryColor3sv(v);}
	inline void SecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue){_detail::SecondaryColor3ub(red, green, blue);}
	inline void SecondaryColor3ubv(const GLubyte * v){_detail::SecondaryColor3ubv(v);}
	inline void SecondaryColor3ui(GLuint red, GLuint green, GLuint blue){_detail::SecondaryColor3ui(red, green, blue);}
	inline void SecondaryColor3uiv(const GLuint * v){_detail::SecondaryColor3uiv(v);}
	inline void SecondaryColor3us(GLushort red, GLushort green, GLushort blue){_detail::SecondaryColor3us(red, green, blue);}
	inline void SecondaryColor3usv(const GLushort * v){_detail::SecondaryColor3usv(v);}
	inline void SecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer){_detail::SecondaryColorPointer(size, type, stride, pointer);}
	inline void WindowPos2d(GLdouble x, GLdouble y){_detail::WindowPos2d(x, y);}
	inline void WindowPos2dv(const GLdouble * v){_detail::WindowPos2dv(v);}
	inline void WindowPos2f(GLfloat x, GLfloat y){_detail::WindowPos2f(x, y);}
	inline void WindowPos2fv(const GLfloat * v){_detail::WindowPos2fv(v);}
	inline void WindowPos2i(GLint x, GLint y){_detail::WindowPos2i(x, y);}
	inline void WindowPos2iv(const GLint * v){_detail::WindowPos2iv(v);}
	inline void WindowPos2s(GLshort x, GLshort y){_detail::WindowPos2s(x, y);}
	inline void WindowPos2sv(const GLshort * v){_detail::WindowPos2sv(v);}
	inline void WindowPos3d(GLdouble x, GLdouble y, GLdouble z){_detail::WindowPos3d(x, y, z);}
	inline void WindowPos3dv(const GLdouble * v){_detail::WindowPos3dv(v);}
	inline void WindowPos3f(GLfloat x, GLfloat y, GLfloat z){_detail::WindowPos3f(x, y, z);}
	inline void WindowPos3fv(const GLfloat * v){_detail::WindowPos3fv(v);}
	inline void WindowPos3i(GLint x, GLint y, GLint z){_detail::WindowPos3i(x, y, z);}
	inline void WindowPos3iv(const GLint * v){_detail::WindowPos3iv(v);}
	inline void WindowPos3s(GLshort x, GLshort y, GLshort z){_detail::WindowPos3s(x, y, z);}
	inline void WindowPos3sv(const GLshort * v){_detail::WindowPos3sv(v);}
	
	inline void BeginQuery(GLenum target, GLuint id){_detail::BeginQuery(target, id);}
	inline void BindBuffer(GLenum target, GLuint buffer){_detail::BindBuffer(target, buffer);}
	inline void BufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage){_detail::BufferData(target, size, data, usage);}
	inline void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data){_detail::BufferSubData(target, offset, size, data);}
	inline void DeleteBuffers(GLsizei n, const GLuint * buffers){_detail::DeleteBuffers(n, buffers);}
	inline void DeleteQueries(GLsizei n, const GLuint * ids){_detail::DeleteQueries(n, ids);}
	inline void EndQuery(GLenum target){_detail::EndQuery(target);}
	inline void GenBuffers(GLsizei n, GLuint * buffers){_detail::GenBuffers(n, buffers);}
	inline void GenQueries(GLsizei n, GLuint * ids){_detail::GenQueries(n, ids);}
	inline void GetBufferParameteriv(GLenum target, GLenum pname, GLint * params){_detail::GetBufferParameteriv(target, pname, params);}
	inline void GetBufferPointerv(GLenum target, GLenum pname, void ** params){_detail::GetBufferPointerv(target, pname, params);}
	inline void GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data){_detail::GetBufferSubData(target, offset, size, data);}
	inline void GetQueryObjectiv(GLuint id, GLenum pname, GLint * params){_detail::GetQueryObjectiv(id, pname, params);}
	inline void GetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params){_detail::GetQueryObjectuiv(id, pname, params);}
	inline void GetQueryiv(GLenum target, GLenum pname, GLint * params){_detail::GetQueryiv(target, pname, params);}
	inline GLboolean IsBuffer(GLuint buffer){return _detail::IsBuffer(buffer);}
	inline GLboolean IsQuery(GLuint id){return _detail::IsQuery(id);}
	inline void * MapBuffer(GLenum target, GLenum access){return _detail::MapBuffer(target, access);}
	inline GLboolean UnmapBuffer(GLenum target){return _detail::UnmapBuffer(target);}
	
	inline void AttachShader(GLuint program, GLuint shader){_detail::AttachShader(program, shader);}
	inline void BindAttribLocation(GLuint program, GLuint index, const GLchar * name){_detail::BindAttribLocation(program, index, name);}
	inline void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha){_detail::BlendEquationSeparate(modeRGB, modeAlpha);}
	inline void CompileShader(GLuint shader){_detail::CompileShader(shader);}
	inline GLuint CreateProgram(void){return _detail::CreateProgram();}
	inline GLuint CreateShader(GLenum type){return _detail::CreateShader(type);}
	inline void DeleteProgram(GLuint program){_detail::DeleteProgram(program);}
	inline void DeleteShader(GLuint shader){_detail::DeleteShader(shader);}
	inline void DetachShader(GLuint program, GLuint shader){_detail::DetachShader(program, shader);}
	inline void DisableVertexAttribArray(GLuint index){_detail::DisableVertexAttribArray(index);}
	inline void DrawBuffers(GLsizei n, const GLenum * bufs){_detail::DrawBuffers(n, bufs);}
	inline void EnableVertexAttribArray(GLuint index){_detail::EnableVertexAttribArray(index);}
	inline void GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name){_detail::GetActiveAttrib(program, index, bufSize, length, size, type, name);}
	inline void GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name){_detail::GetActiveUniform(program, index, bufSize, length, size, type, name);}
	inline void GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders){_detail::GetAttachedShaders(program, maxCount, count, shaders);}
	inline GLint GetAttribLocation(GLuint program, const GLchar * name){return _detail::GetAttribLocation(program, name);}
	inline void GetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog){_detail::GetProgramInfoLog(program, bufSize, length, infoLog);}
	inline void GetProgramiv(GLuint program, GLenum pname, GLint * params){_detail::GetProgramiv(program, pname, params);}
	inline void GetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog){_detail::GetShaderInfoLog(shader, bufSize, length, infoLog);}
	inline void GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source){_detail::GetShaderSource(shader, bufSize, length, source);}
	inline void GetShaderiv(GLuint shader, GLenum pname, GLint * params){_detail::GetShaderiv(shader, pname, params);}
	inline GLint GetUniformLocation(GLuint program, const GLchar * name){return _detail::GetUniformLocation(program, name);}
	inline void GetUniformfv(GLuint program, GLint location, GLfloat * params){_detail::GetUniformfv(program, location, params);}
	inline void GetUniformiv(GLuint program, GLint location, GLint * params){_detail::GetUniformiv(program, location, params);}
	inline void GetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer){_detail::GetVertexAttribPointerv(index, pname, pointer);}
	inline void GetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params){_detail::GetVertexAttribdv(index, pname, params);}
	inline void GetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params){_detail::GetVertexAttribfv(index, pname, params);}
	inline void GetVertexAttribiv(GLuint index, GLenum pname, GLint * params){_detail::GetVertexAttribiv(index, pname, params);}
	inline GLboolean IsProgram(GLuint program){return _detail::IsProgram(program);}
	inline GLboolean IsShader(GLuint shader){return _detail::IsShader(shader);}
	inline void LinkProgram(GLuint program){_detail::LinkProgram(program);}
	inline void ShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length){_detail::ShaderSource(shader, count, string, length);}
	inline void StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask){_detail::StencilFuncSeparate(face, func, ref, mask);}
	inline void StencilMaskSeparate(GLenum face, GLuint mask){_detail::StencilMaskSeparate(face, mask);}
	inline void StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass){_detail::StencilOpSeparate(face, sfail, dpfail, dppass);}
	inline void Uniform1f(GLint location, GLfloat v0){_detail::Uniform1f(location, v0);}
	inline void Uniform1fv(GLint location, GLsizei count, const GLfloat * value){_detail::Uniform1fv(location, count, value);}
	inline void Uniform1i(GLint location, GLint v0){_detail::Uniform1i(location, v0);}
	inline void Uniform1iv(GLint location, GLsizei count, const GLint * value){_detail::Uniform1iv(location, count, value);}
	inline void Uniform2f(GLint location, GLfloat v0, GLfloat v1){_detail::Uniform2f(location, v0, v1);}
	inline void Uniform2fv(GLint location, GLsizei count, const GLfloat * value){_detail::Uniform2fv(location, count, value);}
	inline void Uniform2i(GLint location, GLint v0, GLint v1){_detail::Uniform2i(location, v0, v1);}
	inline void Uniform2iv(GLint location, GLsizei count, const GLint * value){_detail::Uniform2iv(location, count, value);}
	inline void Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2){_detail::Uniform3f(location, v0, v1, v2);}
	inline void Uniform3fv(GLint location, GLsizei count, const GLfloat * value){_detail::Uniform3fv(location, count, value);}
	inline void Uniform3i(GLint location, GLint v0, GLint v1, GLint v2){_detail::Uniform3i(location, v0, v1, v2);}
	inline void Uniform3iv(GLint location, GLsizei count, const GLint * value){_detail::Uniform3iv(location, count, value);}
	inline void Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){_detail::Uniform4f(location, v0, v1, v2, v3);}
	inline void Uniform4fv(GLint location, GLsizei count, const GLfloat * value){_detail::Uniform4fv(location, count, value);}
	inline void Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3){_detail::Uniform4i(location, v0, v1, v2, v3);}
	inline void Uniform4iv(GLint location, GLsizei count, const GLint * value){_detail::Uniform4iv(location, count, value);}
	inline void UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix2fv(location, count, transpose, value);}
	inline void UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix3fv(location, count, transpose, value);}
	inline void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix4fv(location, count, transpose, value);}
	inline void UseProgram(GLuint program){_detail::UseProgram(program);}
	inline void ValidateProgram(GLuint program){_detail::ValidateProgram(program);}
	inline void VertexAttrib1d(GLuint index, GLdouble x){_detail::VertexAttrib1d(index, x);}
	inline void VertexAttrib1dv(GLuint index, const GLdouble * v){_detail::VertexAttrib1dv(index, v);}
	inline void VertexAttrib1f(GLuint index, GLfloat x){_detail::VertexAttrib1f(index, x);}
	inline void VertexAttrib1fv(GLuint index, const GLfloat * v){_detail::VertexAttrib1fv(index, v);}
	inline void VertexAttrib1s(GLuint index, GLshort x){_detail::VertexAttrib1s(index, x);}
	inline void VertexAttrib1sv(GLuint index, const GLshort * v){_detail::VertexAttrib1sv(index, v);}
	inline void VertexAttrib2d(GLuint index, GLdouble x, GLdouble y){_detail::VertexAttrib2d(index, x, y);}
	inline void VertexAttrib2dv(GLuint index, const GLdouble * v){_detail::VertexAttrib2dv(index, v);}
	inline void VertexAttrib2f(GLuint index, GLfloat x, GLfloat y){_detail::VertexAttrib2f(index, x, y);}
	inline void VertexAttrib2fv(GLuint index, const GLfloat * v){_detail::VertexAttrib2fv(index, v);}
	inline void VertexAttrib2s(GLuint index, GLshort x, GLshort y){_detail::VertexAttrib2s(index, x, y);}
	inline void VertexAttrib2sv(GLuint index, const GLshort * v){_detail::VertexAttrib2sv(index, v);}
	inline void VertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z){_detail::VertexAttrib3d(index, x, y, z);}
	inline void VertexAttrib3dv(GLuint index, const GLdouble * v){_detail::VertexAttrib3dv(index, v);}
	inline void VertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z){_detail::VertexAttrib3f(index, x, y, z);}
	inline void VertexAttrib3fv(GLuint index, const GLfloat * v){_detail::VertexAttrib3fv(index, v);}
	inline void VertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z){_detail::VertexAttrib3s(index, x, y, z);}
	inline void VertexAttrib3sv(GLuint index, const GLshort * v){_detail::VertexAttrib3sv(index, v);}
	inline void VertexAttrib4Nbv(GLuint index, const GLbyte * v){_detail::VertexAttrib4Nbv(index, v);}
	inline void VertexAttrib4Niv(GLuint index, const GLint * v){_detail::VertexAttrib4Niv(index, v);}
	inline void VertexAttrib4Nsv(GLuint index, const GLshort * v){_detail::VertexAttrib4Nsv(index, v);}
	inline void VertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w){_detail::VertexAttrib4Nub(index, x, y, z, w);}
	inline void VertexAttrib4Nubv(GLuint index, const GLubyte * v){_detail::VertexAttrib4Nubv(index, v);}
	inline void VertexAttrib4Nuiv(GLuint index, const GLuint * v){_detail::VertexAttrib4Nuiv(index, v);}
	inline void VertexAttrib4Nusv(GLuint index, const GLushort * v){_detail::VertexAttrib4Nusv(index, v);}
	inline void VertexAttrib4bv(GLuint index, const GLbyte * v){_detail::VertexAttrib4bv(index, v);}
	inline void VertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w){_detail::VertexAttrib4d(index, x, y, z, w);}
	inline void VertexAttrib4dv(GLuint index, const GLdouble * v){_detail::VertexAttrib4dv(index, v);}
	inline void VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w){_detail::VertexAttrib4f(index, x, y, z, w);}
	inline void VertexAttrib4fv(GLuint index, const GLfloat * v){_detail::VertexAttrib4fv(index, v);}
	inline void VertexAttrib4iv(GLuint index, const GLint * v){_detail::VertexAttrib4iv(index, v);}
	inline void VertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w){_detail::VertexAttrib4s(index, x, y, z, w);}
	inline void VertexAttrib4sv(GLuint index, const GLshort * v){_detail::VertexAttrib4sv(index, v);}
	inline void VertexAttrib4ubv(GLuint index, const GLubyte * v){_detail::VertexAttrib4ubv(index, v);}
	inline void VertexAttrib4uiv(GLuint index, const GLuint * v){_detail::VertexAttrib4uiv(index, v);}
	inline void VertexAttrib4usv(GLuint index, const GLushort * v){_detail::VertexAttrib4usv(index, v);}
	inline void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer){_detail::VertexAttribPointer(index, size, type, normalized, stride, pointer);}
	
	inline void UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix2x3fv(location, count, transpose, value);}
	inline void UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix2x4fv(location, count, transpose, value);}
	inline void UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix3x2fv(location, count, transpose, value);}
	inline void UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix3x4fv(location, count, transpose, value);}
	inline void UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix4x2fv(location, count, transpose, value);}
	inline void UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::UniformMatrix4x3fv(location, count, transpose, value);}
	
	inline void BeginConditionalRender(GLuint id, GLenum mode){_detail::BeginConditionalRender(id, mode);}
	inline void BeginTransformFeedback(GLenum primitiveMode){_detail::BeginTransformFeedback(primitiveMode);}
	inline void BindBufferBase(GLenum target, GLuint index, GLuint buffer){_detail::BindBufferBase(target, index, buffer);}
	inline void BindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size){_detail::BindBufferRange(target, index, buffer, offset, size);}
	inline void BindFragDataLocation(GLuint program, GLuint color, const GLchar * name){_detail::BindFragDataLocation(program, color, name);}
	inline void BindFramebuffer(GLenum target, GLuint framebuffer){_detail::BindFramebuffer(target, framebuffer);}
	inline void BindRenderbuffer(GLenum target, GLuint renderbuffer){_detail::BindRenderbuffer(target, renderbuffer);}
	inline void BindVertexArray(GLuint ren_array){_detail::BindVertexArray(ren_array);}
	inline void BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter){_detail::BlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);}
	inline GLenum CheckFramebufferStatus(GLenum target){return _detail::CheckFramebufferStatus(target);}
	inline void ClampColor(GLenum target, GLenum clamp){_detail::ClampColor(target, clamp);}
	inline void ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil){_detail::ClearBufferfi(buffer, drawbuffer, depth, stencil);}
	inline void ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value){_detail::ClearBufferfv(buffer, drawbuffer, value);}
	inline void ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value){_detail::ClearBufferiv(buffer, drawbuffer, value);}
	inline void ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value){_detail::ClearBufferuiv(buffer, drawbuffer, value);}
	inline void ColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a){_detail::ColorMaski(index, r, g, b, a);}
	inline void DeleteFramebuffers(GLsizei n, const GLuint * framebuffers){_detail::DeleteFramebuffers(n, framebuffers);}
	inline void DeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers){_detail::DeleteRenderbuffers(n, renderbuffers);}
	inline void DeleteVertexArrays(GLsizei n, const GLuint * arrays){_detail::DeleteVertexArrays(n, arrays);}
	inline void Disablei(GLenum target, GLuint index){_detail::Disablei(target, index);}
	inline void Enablei(GLenum target, GLuint index){_detail::Enablei(target, index);}
	inline void EndConditionalRender(void){_detail::EndConditionalRender();}
	inline void EndTransformFeedback(void){_detail::EndTransformFeedback();}
	inline void FlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length){_detail::FlushMappedBufferRange(target, offset, length);}
	inline void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer){_detail::FramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);}
	inline void FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){_detail::FramebufferTexture1D(target, attachment, textarget, texture, level);}
	inline void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){_detail::FramebufferTexture2D(target, attachment, textarget, texture, level);}
	inline void FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset){_detail::FramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);}
	inline void FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer){_detail::FramebufferTextureLayer(target, attachment, texture, level, layer);}
	inline void GenFramebuffers(GLsizei n, GLuint * framebuffers){_detail::GenFramebuffers(n, framebuffers);}
	inline void GenRenderbuffers(GLsizei n, GLuint * renderbuffers){_detail::GenRenderbuffers(n, renderbuffers);}
	inline void GenVertexArrays(GLsizei n, GLuint * arrays){_detail::GenVertexArrays(n, arrays);}
	inline void GenerateMipmap(GLenum target){_detail::GenerateMipmap(target);}
	inline void GetBooleani_v(GLenum target, GLuint index, GLboolean * data){_detail::GetBooleani_v(target, index, data);}
	inline GLint GetFragDataLocation(GLuint program, const GLchar * name){return _detail::GetFragDataLocation(program, name);}
	inline void GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params){_detail::GetFramebufferAttachmentParameteriv(target, attachment, pname, params);}
	inline void GetIntegeri_v(GLenum target, GLuint index, GLint * data){_detail::GetIntegeri_v(target, index, data);}
	inline void GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params){_detail::GetRenderbufferParameteriv(target, pname, params);}
	inline const GLubyte * GetStringi(GLenum name, GLuint index){return _detail::GetStringi(name, index);}
	inline void GetTexParameterIiv(GLenum target, GLenum pname, GLint * params){_detail::GetTexParameterIiv(target, pname, params);}
	inline void GetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params){_detail::GetTexParameterIuiv(target, pname, params);}
	inline void GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name){_detail::GetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);}
	inline void GetUniformuiv(GLuint program, GLint location, GLuint * params){_detail::GetUniformuiv(program, location, params);}
	inline void GetVertexAttribIiv(GLuint index, GLenum pname, GLint * params){_detail::GetVertexAttribIiv(index, pname, params);}
	inline void GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params){_detail::GetVertexAttribIuiv(index, pname, params);}
	inline GLboolean IsEnabledi(GLenum target, GLuint index){return _detail::IsEnabledi(target, index);}
	inline GLboolean IsFramebuffer(GLuint framebuffer){return _detail::IsFramebuffer(framebuffer);}
	inline GLboolean IsRenderbuffer(GLuint renderbuffer){return _detail::IsRenderbuffer(renderbuffer);}
	inline GLboolean IsVertexArray(GLuint ren_array){return _detail::IsVertexArray(ren_array);}
	inline void * MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access){return _detail::MapBufferRange(target, offset, length, access);}
	inline void RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height){_detail::RenderbufferStorage(target, internalformat, width, height);}
	inline void RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height){_detail::RenderbufferStorageMultisample(target, samples, internalformat, width, height);}
	inline void TexParameterIiv(GLenum target, GLenum pname, const GLint * params){_detail::TexParameterIiv(target, pname, params);}
	inline void TexParameterIuiv(GLenum target, GLenum pname, const GLuint * params){_detail::TexParameterIuiv(target, pname, params);}
	inline void TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode){_detail::TransformFeedbackVaryings(program, count, varyings, bufferMode);}
	inline void Uniform1ui(GLint location, GLuint v0){_detail::Uniform1ui(location, v0);}
	inline void Uniform1uiv(GLint location, GLsizei count, const GLuint * value){_detail::Uniform1uiv(location, count, value);}
	inline void Uniform2ui(GLint location, GLuint v0, GLuint v1){_detail::Uniform2ui(location, v0, v1);}
	inline void Uniform2uiv(GLint location, GLsizei count, const GLuint * value){_detail::Uniform2uiv(location, count, value);}
	inline void Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2){_detail::Uniform3ui(location, v0, v1, v2);}
	inline void Uniform3uiv(GLint location, GLsizei count, const GLuint * value){_detail::Uniform3uiv(location, count, value);}
	inline void Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3){_detail::Uniform4ui(location, v0, v1, v2, v3);}
	inline void Uniform4uiv(GLint location, GLsizei count, const GLuint * value){_detail::Uniform4uiv(location, count, value);}
	inline void VertexAttribI1i(GLuint index, GLint x){_detail::VertexAttribI1i(index, x);}
	inline void VertexAttribI1iv(GLuint index, const GLint * v){_detail::VertexAttribI1iv(index, v);}
	inline void VertexAttribI1ui(GLuint index, GLuint x){_detail::VertexAttribI1ui(index, x);}
	inline void VertexAttribI1uiv(GLuint index, const GLuint * v){_detail::VertexAttribI1uiv(index, v);}
	inline void VertexAttribI2i(GLuint index, GLint x, GLint y){_detail::VertexAttribI2i(index, x, y);}
	inline void VertexAttribI2iv(GLuint index, const GLint * v){_detail::VertexAttribI2iv(index, v);}
	inline void VertexAttribI2ui(GLuint index, GLuint x, GLuint y){_detail::VertexAttribI2ui(index, x, y);}
	inline void VertexAttribI2uiv(GLuint index, const GLuint * v){_detail::VertexAttribI2uiv(index, v);}
	inline void VertexAttribI3i(GLuint index, GLint x, GLint y, GLint z){_detail::VertexAttribI3i(index, x, y, z);}
	inline void VertexAttribI3iv(GLuint index, const GLint * v){_detail::VertexAttribI3iv(index, v);}
	inline void VertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z){_detail::VertexAttribI3ui(index, x, y, z);}
	inline void VertexAttribI3uiv(GLuint index, const GLuint * v){_detail::VertexAttribI3uiv(index, v);}
	inline void VertexAttribI4bv(GLuint index, const GLbyte * v){_detail::VertexAttribI4bv(index, v);}
	inline void VertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w){_detail::VertexAttribI4i(index, x, y, z, w);}
	inline void VertexAttribI4iv(GLuint index, const GLint * v){_detail::VertexAttribI4iv(index, v);}
	inline void VertexAttribI4sv(GLuint index, const GLshort * v){_detail::VertexAttribI4sv(index, v);}
	inline void VertexAttribI4ubv(GLuint index, const GLubyte * v){_detail::VertexAttribI4ubv(index, v);}
	inline void VertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w){_detail::VertexAttribI4ui(index, x, y, z, w);}
	inline void VertexAttribI4uiv(GLuint index, const GLuint * v){_detail::VertexAttribI4uiv(index, v);}
	inline void VertexAttribI4usv(GLuint index, const GLushort * v){_detail::VertexAttribI4usv(index, v);}
	inline void VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer){_detail::VertexAttribIPointer(index, size, type, stride, pointer);}
	
	inline void CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size){_detail::CopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);}
	inline void DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount){_detail::DrawArraysInstanced(mode, first, count, instancecount);}
	inline void DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount){_detail::DrawElementsInstanced(mode, count, type, indices, instancecount);}
	inline void GetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName){_detail::GetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);}
	inline void GetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params){_detail::GetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);}
	inline void GetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName){_detail::GetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);}
	inline void GetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params){_detail::GetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);}
	inline GLuint GetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName){return _detail::GetUniformBlockIndex(program, uniformBlockName);}
	inline void GetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices){_detail::GetUniformIndices(program, uniformCount, uniformNames, uniformIndices);}
	inline void PrimitiveRestartIndex(GLuint index){_detail::PrimitiveRestartIndex(index);}
	inline void TexBuffer(GLenum target, GLenum internalformat, GLuint buffer){_detail::TexBuffer(target, internalformat, buffer);}
	inline void UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding){_detail::UniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);}
	
	inline GLenum ClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout){return _detail::ClientWaitSync(sync, flags, timeout);}
	inline void DeleteSync(GLsync sync){_detail::DeleteSync(sync);}
	inline void DrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex){_detail::DrawElementsBaseVertex(mode, count, type, indices, basevertex);}
	inline void DrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex){_detail::DrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);}
	inline void DrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex){_detail::DrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);}
	inline GLsync FenceSync(GLenum condition, GLbitfield flags){return _detail::FenceSync(condition, flags);}
	inline void FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level){_detail::FramebufferTexture(target, attachment, texture, level);}
	inline void GetBufferParameteri64v(GLenum target, GLenum pname, GLint64 * params){_detail::GetBufferParameteri64v(target, pname, params);}
	inline void GetInteger64i_v(GLenum target, GLuint index, GLint64 * data){_detail::GetInteger64i_v(target, index, data);}
	inline void GetInteger64v(GLenum pname, GLint64 * data){_detail::GetInteger64v(pname, data);}
	inline void GetMultisamplefv(GLenum pname, GLuint index, GLfloat * val){_detail::GetMultisamplefv(pname, index, val);}
	inline void GetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values){_detail::GetSynciv(sync, pname, bufSize, length, values);}
	inline GLboolean IsSync(GLsync sync){return _detail::IsSync(sync);}
	inline void MultiDrawElementsBaseVertex(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount, const GLint * basevertex){_detail::MultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);}
	inline void ProvokingVertex(GLenum mode){_detail::ProvokingVertex(mode);}
	inline void SampleMaski(GLuint maskNumber, GLbitfield mask){_detail::SampleMaski(maskNumber, mask);}
	inline void TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){_detail::TexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);}
	inline void TexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){_detail::TexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);}
	inline void WaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout){_detail::WaitSync(sync, flags, timeout);}
	
	inline void BindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name){_detail::BindFragDataLocationIndexed(program, colorNumber, index, name);}
	inline void BindSampler(GLuint unit, GLuint sampler){_detail::BindSampler(unit, sampler);}
	inline void DeleteSamplers(GLsizei count, const GLuint * samplers){_detail::DeleteSamplers(count, samplers);}
	inline void GenSamplers(GLsizei count, GLuint * samplers){_detail::GenSamplers(count, samplers);}
	inline GLint GetFragDataIndex(GLuint program, const GLchar * name){return _detail::GetFragDataIndex(program, name);}
	inline void GetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params){_detail::GetQueryObjecti64v(id, pname, params);}
	inline void GetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params){_detail::GetQueryObjectui64v(id, pname, params);}
	inline void GetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params){_detail::GetSamplerParameterIiv(sampler, pname, params);}
	inline void GetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params){_detail::GetSamplerParameterIuiv(sampler, pname, params);}
	inline void GetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params){_detail::GetSamplerParameterfv(sampler, pname, params);}
	inline void GetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params){_detail::GetSamplerParameteriv(sampler, pname, params);}
	inline GLboolean IsSampler(GLuint sampler){return _detail::IsSampler(sampler);}
	inline void QueryCounter(GLuint id, GLenum target){_detail::QueryCounter(id, target);}
	inline void SamplerParameterIiv(GLuint sampler, GLenum pname, const GLint * param){_detail::SamplerParameterIiv(sampler, pname, param);}
	inline void SamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint * param){_detail::SamplerParameterIuiv(sampler, pname, param);}
	inline void SamplerParameterf(GLuint sampler, GLenum pname, GLfloat param){_detail::SamplerParameterf(sampler, pname, param);}
	inline void SamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat * param){_detail::SamplerParameterfv(sampler, pname, param);}
	inline void SamplerParameteri(GLuint sampler, GLenum pname, GLint param){_detail::SamplerParameteri(sampler, pname, param);}
	inline void SamplerParameteriv(GLuint sampler, GLenum pname, const GLint * param){_detail::SamplerParameteriv(sampler, pname, param);}
	inline void VertexAttribDivisor(GLuint index, GLuint divisor){_detail::VertexAttribDivisor(index, divisor);}
	inline void VertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value){_detail::VertexAttribP1ui(index, type, normalized, value);}
	inline void VertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value){_detail::VertexAttribP1uiv(index, type, normalized, value);}
	inline void VertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value){_detail::VertexAttribP2ui(index, type, normalized, value);}
	inline void VertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value){_detail::VertexAttribP2uiv(index, type, normalized, value);}
	inline void VertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value){_detail::VertexAttribP3ui(index, type, normalized, value);}
	inline void VertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value){_detail::VertexAttribP3uiv(index, type, normalized, value);}
	inline void VertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value){_detail::VertexAttribP4ui(index, type, normalized, value);}
	inline void VertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value){_detail::VertexAttribP4uiv(index, type, normalized, value);}
	
	inline void BeginQueryIndexed(GLenum target, GLuint index, GLuint id){_detail::BeginQueryIndexed(target, index, id);}
	inline void BindTransformFeedback(GLenum target, GLuint id){_detail::BindTransformFeedback(target, id);}
	inline void BlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha){_detail::BlendEquationSeparatei(buf, modeRGB, modeAlpha);}
	inline void BlendEquationi(GLuint buf, GLenum mode){_detail::BlendEquationi(buf, mode);}
	inline void BlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha){_detail::BlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);}
	inline void BlendFunci(GLuint buf, GLenum src, GLenum dst){_detail::BlendFunci(buf, src, dst);}
	inline void DeleteTransformFeedbacks(GLsizei n, const GLuint * ids){_detail::DeleteTransformFeedbacks(n, ids);}
	inline void DrawArraysIndirect(GLenum mode, const void * indirect){_detail::DrawArraysIndirect(mode, indirect);}
	inline void DrawElementsIndirect(GLenum mode, GLenum type, const void * indirect){_detail::DrawElementsIndirect(mode, type, indirect);}
	inline void DrawTransformFeedback(GLenum mode, GLuint id){_detail::DrawTransformFeedback(mode, id);}
	inline void DrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream){_detail::DrawTransformFeedbackStream(mode, id, stream);}
	inline void EndQueryIndexed(GLenum target, GLuint index){_detail::EndQueryIndexed(target, index);}
	inline void GenTransformFeedbacks(GLsizei n, GLuint * ids){_detail::GenTransformFeedbacks(n, ids);}
	inline void GetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name){_detail::GetActiveSubroutineName(program, shadertype, index, bufsize, length, name);}
	inline void GetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name){_detail::GetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);}
	inline void GetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values){_detail::GetActiveSubroutineUniformiv(program, shadertype, index, pname, values);}
	inline void GetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values){_detail::GetProgramStageiv(program, shadertype, pname, values);}
	inline void GetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params){_detail::GetQueryIndexediv(target, index, pname, params);}
	inline GLuint GetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar * name){return _detail::GetSubroutineIndex(program, shadertype, name);}
	inline GLint GetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar * name){return _detail::GetSubroutineUniformLocation(program, shadertype, name);}
	inline void GetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params){_detail::GetUniformSubroutineuiv(shadertype, location, params);}
	inline void GetUniformdv(GLuint program, GLint location, GLdouble * params){_detail::GetUniformdv(program, location, params);}
	inline GLboolean IsTransformFeedback(GLuint id){return _detail::IsTransformFeedback(id);}
	inline void MinSampleShading(GLfloat value){_detail::MinSampleShading(value);}
	inline void PatchParameterfv(GLenum pname, const GLfloat * values){_detail::PatchParameterfv(pname, values);}
	inline void PatchParameteri(GLenum pname, GLint value){_detail::PatchParameteri(pname, value);}
	inline void PauseTransformFeedback(void){_detail::PauseTransformFeedback();}
	inline void ResumeTransformFeedback(void){_detail::ResumeTransformFeedback();}
	inline void Uniform1d(GLint location, GLdouble x){_detail::Uniform1d(location, x);}
	inline void Uniform1dv(GLint location, GLsizei count, const GLdouble * value){_detail::Uniform1dv(location, count, value);}
	inline void Uniform2d(GLint location, GLdouble x, GLdouble y){_detail::Uniform2d(location, x, y);}
	inline void Uniform2dv(GLint location, GLsizei count, const GLdouble * value){_detail::Uniform2dv(location, count, value);}
	inline void Uniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z){_detail::Uniform3d(location, x, y, z);}
	inline void Uniform3dv(GLint location, GLsizei count, const GLdouble * value){_detail::Uniform3dv(location, count, value);}
	inline void Uniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w){_detail::Uniform4d(location, x, y, z, w);}
	inline void Uniform4dv(GLint location, GLsizei count, const GLdouble * value){_detail::Uniform4dv(location, count, value);}
	inline void UniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix2dv(location, count, transpose, value);}
	inline void UniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix2x3dv(location, count, transpose, value);}
	inline void UniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix2x4dv(location, count, transpose, value);}
	inline void UniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix3dv(location, count, transpose, value);}
	inline void UniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix3x2dv(location, count, transpose, value);}
	inline void UniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix3x4dv(location, count, transpose, value);}
	inline void UniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix4dv(location, count, transpose, value);}
	inline void UniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix4x2dv(location, count, transpose, value);}
	inline void UniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::UniformMatrix4x3dv(location, count, transpose, value);}
	inline void UniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint * indices){_detail::UniformSubroutinesuiv(shadertype, count, indices);}
	
	inline void ActiveShaderProgram(GLuint pipeline, GLuint program){_detail::ActiveShaderProgram(pipeline, program);}
	inline void BindProgramPipeline(GLuint pipeline){_detail::BindProgramPipeline(pipeline);}
	inline void ClearDepthf(GLfloat d){_detail::ClearDepthf(d);}
	inline GLuint CreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const* strings){return _detail::CreateShaderProgramv(type, count, strings);}
	inline void DeleteProgramPipelines(GLsizei n, const GLuint * pipelines){_detail::DeleteProgramPipelines(n, pipelines);}
	inline void DepthRangeArrayv(GLuint first, GLsizei count, const GLdouble * v){_detail::DepthRangeArrayv(first, count, v);}
	inline void DepthRangeIndexed(GLuint index, GLdouble n, GLdouble f){_detail::DepthRangeIndexed(index, n, f);}
	inline void DepthRangef(GLfloat n, GLfloat f){_detail::DepthRangef(n, f);}
	inline void GenProgramPipelines(GLsizei n, GLuint * pipelines){_detail::GenProgramPipelines(n, pipelines);}
	inline void GetDoublei_v(GLenum target, GLuint index, GLdouble * data){_detail::GetDoublei_v(target, index, data);}
	inline void GetFloati_v(GLenum target, GLuint index, GLfloat * data){_detail::GetFloati_v(target, index, data);}
	inline void GetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, void * binary){_detail::GetProgramBinary(program, bufSize, length, binaryFormat, binary);}
	inline void GetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog){_detail::GetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);}
	inline void GetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params){_detail::GetProgramPipelineiv(pipeline, pname, params);}
	inline void GetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision){_detail::GetShaderPrecisionFormat(shadertype, precisiontype, range, precision);}
	inline void GetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params){_detail::GetVertexAttribLdv(index, pname, params);}
	inline GLboolean IsProgramPipeline(GLuint pipeline){return _detail::IsProgramPipeline(pipeline);}
	inline void ProgramBinary(GLuint program, GLenum binaryFormat, const void * binary, GLsizei length){_detail::ProgramBinary(program, binaryFormat, binary, length);}
	inline void ProgramParameteri(GLuint program, GLenum pname, GLint value){_detail::ProgramParameteri(program, pname, value);}
	inline void ProgramUniform1d(GLuint program, GLint location, GLdouble v0){_detail::ProgramUniform1d(program, location, v0);}
	inline void ProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble * value){_detail::ProgramUniform1dv(program, location, count, value);}
	inline void ProgramUniform1f(GLuint program, GLint location, GLfloat v0){_detail::ProgramUniform1f(program, location, v0);}
	inline void ProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat * value){_detail::ProgramUniform1fv(program, location, count, value);}
	inline void ProgramUniform1i(GLuint program, GLint location, GLint v0){_detail::ProgramUniform1i(program, location, v0);}
	inline void ProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint * value){_detail::ProgramUniform1iv(program, location, count, value);}
	inline void ProgramUniform1ui(GLuint program, GLint location, GLuint v0){_detail::ProgramUniform1ui(program, location, v0);}
	inline void ProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint * value){_detail::ProgramUniform1uiv(program, location, count, value);}
	inline void ProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1){_detail::ProgramUniform2d(program, location, v0, v1);}
	inline void ProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble * value){_detail::ProgramUniform2dv(program, location, count, value);}
	inline void ProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1){_detail::ProgramUniform2f(program, location, v0, v1);}
	inline void ProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat * value){_detail::ProgramUniform2fv(program, location, count, value);}
	inline void ProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1){_detail::ProgramUniform2i(program, location, v0, v1);}
	inline void ProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint * value){_detail::ProgramUniform2iv(program, location, count, value);}
	inline void ProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1){_detail::ProgramUniform2ui(program, location, v0, v1);}
	inline void ProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint * value){_detail::ProgramUniform2uiv(program, location, count, value);}
	inline void ProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2){_detail::ProgramUniform3d(program, location, v0, v1, v2);}
	inline void ProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble * value){_detail::ProgramUniform3dv(program, location, count, value);}
	inline void ProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2){_detail::ProgramUniform3f(program, location, v0, v1, v2);}
	inline void ProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat * value){_detail::ProgramUniform3fv(program, location, count, value);}
	inline void ProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2){_detail::ProgramUniform3i(program, location, v0, v1, v2);}
	inline void ProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint * value){_detail::ProgramUniform3iv(program, location, count, value);}
	inline void ProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2){_detail::ProgramUniform3ui(program, location, v0, v1, v2);}
	inline void ProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint * value){_detail::ProgramUniform3uiv(program, location, count, value);}
	inline void ProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3){_detail::ProgramUniform4d(program, location, v0, v1, v2, v3);}
	inline void ProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble * value){_detail::ProgramUniform4dv(program, location, count, value);}
	inline void ProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){_detail::ProgramUniform4f(program, location, v0, v1, v2, v3);}
	inline void ProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat * value){_detail::ProgramUniform4fv(program, location, count, value);}
	inline void ProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3){_detail::ProgramUniform4i(program, location, v0, v1, v2, v3);}
	inline void ProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint * value){_detail::ProgramUniform4iv(program, location, count, value);}
	inline void ProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3){_detail::ProgramUniform4ui(program, location, v0, v1, v2, v3);}
	inline void ProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint * value){_detail::ProgramUniform4uiv(program, location, count, value);}
	inline void ProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix2dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix2fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix2x3dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix2x3fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix2x4dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix2x4fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix3dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix3fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix3x2dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix3x2fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix3x4dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix3x4fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix4dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix4fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix4x2dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix4x2fv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){_detail::ProgramUniformMatrix4x3dv(program, location, count, transpose, value);}
	inline void ProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){_detail::ProgramUniformMatrix4x3fv(program, location, count, transpose, value);}
	inline void ReleaseShaderCompiler(void){_detail::ReleaseShaderCompiler();}
	inline void ScissorArrayv(GLuint first, GLsizei count, const GLint * v){_detail::ScissorArrayv(first, count, v);}
	inline void ScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height){_detail::ScissorIndexed(index, left, bottom, width, height);}
	inline void ScissorIndexedv(GLuint index, const GLint * v){_detail::ScissorIndexedv(index, v);}
	inline void ShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryformat, const void * binary, GLsizei length){_detail::ShaderBinary(count, shaders, binaryformat, binary, length);}
	inline void UseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program){_detail::UseProgramStages(pipeline, stages, program);}
	inline void ValidateProgramPipeline(GLuint pipeline){_detail::ValidateProgramPipeline(pipeline);}
	inline void VertexAttribL1d(GLuint index, GLdouble x){_detail::VertexAttribL1d(index, x);}
	inline void VertexAttribL1dv(GLuint index, const GLdouble * v){_detail::VertexAttribL1dv(index, v);}
	inline void VertexAttribL2d(GLuint index, GLdouble x, GLdouble y){_detail::VertexAttribL2d(index, x, y);}
	inline void VertexAttribL2dv(GLuint index, const GLdouble * v){_detail::VertexAttribL2dv(index, v);}
	inline void VertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z){_detail::VertexAttribL3d(index, x, y, z);}
	inline void VertexAttribL3dv(GLuint index, const GLdouble * v){_detail::VertexAttribL3dv(index, v);}
	inline void VertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w){_detail::VertexAttribL4d(index, x, y, z, w);}
	inline void VertexAttribL4dv(GLuint index, const GLdouble * v){_detail::VertexAttribL4dv(index, v);}
	inline void VertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer){_detail::VertexAttribLPointer(index, size, type, stride, pointer);}
	inline void ViewportArrayv(GLuint first, GLsizei count, const GLfloat * v){_detail::ViewportArrayv(first, count, v);}
	inline void ViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h){_detail::ViewportIndexedf(index, x, y, w, h);}
	inline void ViewportIndexedfv(GLuint index, const GLfloat * v){_detail::ViewportIndexedfv(index, v);}
	
	inline void BindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format){_detail::BindImageTexture(unit, texture, level, layered, layer, access, format);}
	inline void DrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance){_detail::DrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);}
	inline void DrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLuint baseinstance){_detail::DrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);}
	inline void DrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance){_detail::DrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);}
	inline void DrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount){_detail::DrawTransformFeedbackInstanced(mode, id, instancecount);}
	inline void DrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount){_detail::DrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);}
	inline void GetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params){_detail::GetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);}
	inline void GetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params){_detail::GetInternalformativ(target, internalformat, pname, bufSize, params);}
	inline void MemoryBarrier(GLbitfield barriers){_detail::MemoryBarrier(barriers);}
	inline void TexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width){_detail::TexStorage1D(target, levels, internalformat, width);}
	inline void TexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height){_detail::TexStorage2D(target, levels, internalformat, width, height);}
	inline void TexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth){_detail::TexStorage3D(target, levels, internalformat, width, height, depth);}
	
	inline void BindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride){_detail::BindVertexBuffer(bindingindex, buffer, offset, stride);}
	inline void ClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data){_detail::ClearBufferData(target, internalformat, format, type, data);}
	inline void ClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data){_detail::ClearBufferSubData(target, internalformat, offset, size, format, type, data);}
	inline void CopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth){_detail::CopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);}
	inline void DebugMessageCallback(GLDEBUGPROC callback, const void * userParam){_detail::DebugMessageCallback(callback, userParam);}
	inline void DebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled){_detail::DebugMessageControl(source, type, severity, count, ids, enabled);}
	inline void DebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf){_detail::DebugMessageInsert(source, type, id, severity, length, buf);}
	inline void DispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z){_detail::DispatchCompute(num_groups_x, num_groups_y, num_groups_z);}
	inline void DispatchComputeIndirect(GLintptr indirect){_detail::DispatchComputeIndirect(indirect);}
	inline void FramebufferParameteri(GLenum target, GLenum pname, GLint param){_detail::FramebufferParameteri(target, pname, param);}
	inline GLuint GetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog){return _detail::GetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);}
	inline void GetFramebufferParameteriv(GLenum target, GLenum pname, GLint * params){_detail::GetFramebufferParameteriv(target, pname, params);}
	inline void GetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params){_detail::GetInternalformati64v(target, internalformat, pname, bufSize, params);}
	inline void GetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label){_detail::GetObjectLabel(identifier, name, bufSize, length, label);}
	inline void GetObjectPtrLabel(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label){_detail::GetObjectPtrLabel(ptr, bufSize, length, label);}
	inline void GetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params){_detail::GetProgramInterfaceiv(program, programInterface, pname, params);}
	inline GLuint GetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar * name){return _detail::GetProgramResourceIndex(program, programInterface, name);}
	inline GLint GetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar * name){return _detail::GetProgramResourceLocation(program, programInterface, name);}
	inline GLint GetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar * name){return _detail::GetProgramResourceLocationIndex(program, programInterface, name);}
	inline void GetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name){_detail::GetProgramResourceName(program, programInterface, index, bufSize, length, name);}
	inline void GetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params){_detail::GetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);}
	inline void InvalidateBufferData(GLuint buffer){_detail::InvalidateBufferData(buffer);}
	inline void InvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length){_detail::InvalidateBufferSubData(buffer, offset, length);}
	inline void InvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments){_detail::InvalidateFramebuffer(target, numAttachments, attachments);}
	inline void InvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height){_detail::InvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);}
	inline void InvalidateTexImage(GLuint texture, GLint level){_detail::InvalidateTexImage(texture, level);}
	inline void InvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth){_detail::InvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);}
	inline void MultiDrawArraysIndirect(GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride){_detail::MultiDrawArraysIndirect(mode, indirect, drawcount, stride);}
	inline void MultiDrawElementsIndirect(GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride){_detail::MultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);}
	inline void ObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar * label){_detail::ObjectLabel(identifier, name, length, label);}
	inline void ObjectPtrLabel(const void * ptr, GLsizei length, const GLchar * label){_detail::ObjectPtrLabel(ptr, length, label);}
	inline void PopDebugGroup(void){_detail::PopDebugGroup();}
	inline void PushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar * message){_detail::PushDebugGroup(source, id, length, message);}
	inline void ShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding){_detail::ShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);}
	inline void TexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size){_detail::TexBufferRange(target, internalformat, buffer, offset, size);}
	inline void TexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){_detail::TexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);}
	inline void TexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){_detail::TexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);}
	inline void TextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers){_detail::TextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);}
	inline void VertexAttribBinding(GLuint attribindex, GLuint bindingindex){_detail::VertexAttribBinding(attribindex, bindingindex);}
	inline void VertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset){_detail::VertexAttribFormat(attribindex, size, type, normalized, relativeoffset);}
	inline void VertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){_detail::VertexAttribIFormat(attribindex, size, type, relativeoffset);}
	inline void VertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){_detail::VertexAttribLFormat(attribindex, size, type, relativeoffset);}
	inline void VertexBindingDivisor(GLuint bindingindex, GLuint divisor){_detail::VertexBindingDivisor(bindingindex, divisor);}
	
	inline void BindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint * buffers){_detail::BindBuffersBase(target, first, count, buffers);}
	inline void BindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes){_detail::BindBuffersRange(target, first, count, buffers, offsets, sizes);}
	inline void BindImageTextures(GLuint first, GLsizei count, const GLuint * textures){_detail::BindImageTextures(first, count, textures);}
	inline void BindSamplers(GLuint first, GLsizei count, const GLuint * samplers){_detail::BindSamplers(first, count, samplers);}
	inline void BindTextures(GLuint first, GLsizei count, const GLuint * textures){_detail::BindTextures(first, count, textures);}
	inline void BindVertexBuffers(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides){_detail::BindVertexBuffers(first, count, buffers, offsets, strides);}
	inline void BufferStorage(GLenum target, GLsizeiptr size, const void * data, GLbitfield flags){_detail::BufferStorage(target, size, data, flags);}
	inline void ClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void * data){_detail::ClearTexImage(texture, level, format, type, data);}
	inline void ClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * data){_detail::ClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);}
	
	inline void BindTextureUnit(GLuint unit, GLuint texture){_detail::BindTextureUnit(unit, texture);}
	inline void BlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter){_detail::BlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);}
	inline GLenum CheckNamedFramebufferStatus(GLuint framebuffer, GLenum target){return _detail::CheckNamedFramebufferStatus(framebuffer, target);}
	inline void ClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data){_detail::ClearNamedBufferData(buffer, internalformat, format, type, data);}
	inline void ClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data){_detail::ClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);}
	inline void ClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat depth, GLint stencil){_detail::ClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);}
	inline void ClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value){_detail::ClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);}
	inline void ClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value){_detail::ClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);}
	inline void ClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value){_detail::ClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);}
	inline void ClipControl(GLenum origin, GLenum depth){_detail::ClipControl(origin, depth);}
	inline void CompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data){_detail::CompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);}
	inline void CompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data){_detail::CompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);}
	inline void CompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data){_detail::CompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);}
	inline void CopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size){_detail::CopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);}
	inline void CopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width){_detail::CopyTextureSubImage1D(texture, level, xoffset, x, y, width);}
	inline void CopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){_detail::CopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);}
	inline void CopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){_detail::CopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);}
	inline void CreateBuffers(GLsizei n, GLuint * buffers){_detail::CreateBuffers(n, buffers);}
	inline void CreateFramebuffers(GLsizei n, GLuint * framebuffers){_detail::CreateFramebuffers(n, framebuffers);}
	inline void CreateProgramPipelines(GLsizei n, GLuint * pipelines){_detail::CreateProgramPipelines(n, pipelines);}
	inline void CreateQueries(GLenum target, GLsizei n, GLuint * ids){_detail::CreateQueries(target, n, ids);}
	inline void CreateRenderbuffers(GLsizei n, GLuint * renderbuffers){_detail::CreateRenderbuffers(n, renderbuffers);}
	inline void CreateSamplers(GLsizei n, GLuint * samplers){_detail::CreateSamplers(n, samplers);}
	inline void CreateTextures(GLenum target, GLsizei n, GLuint * textures){_detail::CreateTextures(target, n, textures);}
	inline void CreateTransformFeedbacks(GLsizei n, GLuint * ids){_detail::CreateTransformFeedbacks(n, ids);}
	inline void CreateVertexArrays(GLsizei n, GLuint * arrays){_detail::CreateVertexArrays(n, arrays);}
	inline void DisableVertexArrayAttrib(GLuint vaobj, GLuint index){_detail::DisableVertexArrayAttrib(vaobj, index);}
	inline void EnableVertexArrayAttrib(GLuint vaobj, GLuint index){_detail::EnableVertexArrayAttrib(vaobj, index);}
	inline void FlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length){_detail::FlushMappedNamedBufferRange(buffer, offset, length);}
	inline void GenerateTextureMipmap(GLuint texture){_detail::GenerateTextureMipmap(texture);}
	inline void GetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void * pixels){_detail::GetCompressedTextureImage(texture, level, bufSize, pixels);}
	inline void GetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void * pixels){_detail::GetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);}
	inline GLenum GetGraphicsResetStatus(void){return _detail::GetGraphicsResetStatus();}
	inline void GetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 * params){_detail::GetNamedBufferParameteri64v(buffer, pname, params);}
	inline void GetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint * params){_detail::GetNamedBufferParameteriv(buffer, pname, params);}
	inline void GetNamedBufferPointerv(GLuint buffer, GLenum pname, void ** params){_detail::GetNamedBufferPointerv(buffer, pname, params);}
	inline void GetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void * data){_detail::GetNamedBufferSubData(buffer, offset, size, data);}
	inline void GetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params){_detail::GetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);}
	inline void GetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint * param){_detail::GetNamedFramebufferParameteriv(framebuffer, pname, param);}
	inline void GetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint * params){_detail::GetNamedRenderbufferParameteriv(renderbuffer, pname, params);}
	inline void GetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset){_detail::GetQueryBufferObjecti64v(id, buffer, pname, offset);}
	inline void GetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset){_detail::GetQueryBufferObjectiv(id, buffer, pname, offset);}
	inline void GetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset){_detail::GetQueryBufferObjectui64v(id, buffer, pname, offset);}
	inline void GetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset){_detail::GetQueryBufferObjectuiv(id, buffer, pname, offset);}
	inline void GetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels){_detail::GetTextureImage(texture, level, format, type, bufSize, pixels);}
	inline void GetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat * params){_detail::GetTextureLevelParameterfv(texture, level, pname, params);}
	inline void GetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint * params){_detail::GetTextureLevelParameteriv(texture, level, pname, params);}
	inline void GetTextureParameterIiv(GLuint texture, GLenum pname, GLint * params){_detail::GetTextureParameterIiv(texture, pname, params);}
	inline void GetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint * params){_detail::GetTextureParameterIuiv(texture, pname, params);}
	inline void GetTextureParameterfv(GLuint texture, GLenum pname, GLfloat * params){_detail::GetTextureParameterfv(texture, pname, params);}
	inline void GetTextureParameteriv(GLuint texture, GLenum pname, GLint * params){_detail::GetTextureParameteriv(texture, pname, params);}
	inline void GetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void * pixels){_detail::GetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);}
	inline void GetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 * param){_detail::GetTransformFeedbacki64_v(xfb, pname, index, param);}
	inline void GetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint * param){_detail::GetTransformFeedbacki_v(xfb, pname, index, param);}
	inline void GetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint * param){_detail::GetTransformFeedbackiv(xfb, pname, param);}
	inline void GetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param){_detail::GetVertexArrayIndexed64iv(vaobj, index, pname, param);}
	inline void GetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint * param){_detail::GetVertexArrayIndexediv(vaobj, index, pname, param);}
	inline void GetVertexArrayiv(GLuint vaobj, GLenum pname, GLint * param){_detail::GetVertexArrayiv(vaobj, pname, param);}
	inline void GetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void * pixels){_detail::GetnCompressedTexImage(target, lod, bufSize, pixels);}
	inline void GetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels){_detail::GetnTexImage(target, level, format, type, bufSize, pixels);}
	inline void GetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble * params){_detail::GetnUniformdv(program, location, bufSize, params);}
	inline void GetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat * params){_detail::GetnUniformfv(program, location, bufSize, params);}
	inline void GetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint * params){_detail::GetnUniformiv(program, location, bufSize, params);}
	inline void GetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint * params){_detail::GetnUniformuiv(program, location, bufSize, params);}
	inline void InvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments){_detail::InvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);}
	inline void InvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height){_detail::InvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);}
	inline void * MapNamedBuffer(GLuint buffer, GLenum access){return _detail::MapNamedBuffer(buffer, access);}
	inline void * MapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access){return _detail::MapNamedBufferRange(buffer, offset, length, access);}
	inline void MemoryBarrierByRegion(GLbitfield barriers){_detail::MemoryBarrierByRegion(barriers);}
	inline void NamedBufferData(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage){_detail::NamedBufferData(buffer, size, data, usage);}
	inline void NamedBufferStorage(GLuint buffer, GLsizeiptr size, const void * data, GLbitfield flags){_detail::NamedBufferStorage(buffer, size, data, flags);}
	inline void NamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data){_detail::NamedBufferSubData(buffer, offset, size, data);}
	inline void NamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf){_detail::NamedFramebufferDrawBuffer(framebuffer, buf);}
	inline void NamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum * bufs){_detail::NamedFramebufferDrawBuffers(framebuffer, n, bufs);}
	inline void NamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param){_detail::NamedFramebufferParameteri(framebuffer, pname, param);}
	inline void NamedFramebufferReadBuffer(GLuint framebuffer, GLenum src){_detail::NamedFramebufferReadBuffer(framebuffer, src);}
	inline void NamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer){_detail::NamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);}
	inline void NamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level){_detail::NamedFramebufferTexture(framebuffer, attachment, texture, level);}
	inline void NamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer){_detail::NamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);}
	inline void NamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height){_detail::NamedRenderbufferStorage(renderbuffer, internalformat, width, height);}
	inline void NamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height){_detail::NamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);}
	inline void ReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data){_detail::ReadnPixels(x, y, width, height, format, type, bufSize, data);}
	inline void TextureBarrier(void){_detail::TextureBarrier();}
	inline void TextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer){_detail::TextureBuffer(texture, internalformat, buffer);}
	inline void TextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size){_detail::TextureBufferRange(texture, internalformat, buffer, offset, size);}
	inline void TextureParameterIiv(GLuint texture, GLenum pname, const GLint * params){_detail::TextureParameterIiv(texture, pname, params);}
	inline void TextureParameterIuiv(GLuint texture, GLenum pname, const GLuint * params){_detail::TextureParameterIuiv(texture, pname, params);}
	inline void TextureParameterf(GLuint texture, GLenum pname, GLfloat param){_detail::TextureParameterf(texture, pname, param);}
	inline void TextureParameterfv(GLuint texture, GLenum pname, const GLfloat * param){_detail::TextureParameterfv(texture, pname, param);}
	inline void TextureParameteri(GLuint texture, GLenum pname, GLint param){_detail::TextureParameteri(texture, pname, param);}
	inline void TextureParameteriv(GLuint texture, GLenum pname, const GLint * param){_detail::TextureParameteriv(texture, pname, param);}
	inline void TextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width){_detail::TextureStorage1D(texture, levels, internalformat, width);}
	inline void TextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height){_detail::TextureStorage2D(texture, levels, internalformat, width, height);}
	inline void TextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){_detail::TextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);}
	inline void TextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth){_detail::TextureStorage3D(texture, levels, internalformat, width, height, depth);}
	inline void TextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){_detail::TextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);}
	inline void TextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels){_detail::TextureSubImage1D(texture, level, xoffset, width, format, type, pixels);}
	inline void TextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels){_detail::TextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);}
	inline void TextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels){_detail::TextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);}
	inline void TransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer){_detail::TransformFeedbackBufferBase(xfb, index, buffer);}
	inline void TransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size){_detail::TransformFeedbackBufferRange(xfb, index, buffer, offset, size);}
	inline GLboolean UnmapNamedBuffer(GLuint buffer){return _detail::UnmapNamedBuffer(buffer);}
	inline void VertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex){_detail::VertexArrayAttribBinding(vaobj, attribindex, bindingindex);}
	inline void VertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset){_detail::VertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);}
	inline void VertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){_detail::VertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);}
	inline void VertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){_detail::VertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);}
	inline void VertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor){_detail::VertexArrayBindingDivisor(vaobj, bindingindex, divisor);}
	inline void VertexArrayElementBuffer(GLuint vaobj, GLuint buffer){_detail::VertexArrayElementBuffer(vaobj, buffer);}
	inline void VertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride){_detail::VertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);}
	inline void VertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides){_detail::VertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);}
	
	
	namespace sys
	{
		
		exts::LoadTest LoadFunctions();
		
		int GetMinorVersion();
		int GetMajorVersion();
		bool IsVersionGEQ(int majorVersion, int minorVersion);
		
	} //namespace sys
} //namespace gl
#endif //FUNCTION_CPP_GENERATED_HEADEROPENGL_HPP
