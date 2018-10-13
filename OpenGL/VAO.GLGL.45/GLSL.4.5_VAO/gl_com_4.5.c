#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "gl_com_4.5.h"

#if defined(__APPLE__)
#include <dlfcn.h>

static void* AppleGLGetProcAddress (const char *name)
{
	static void* image = NULL;
	
	if (NULL == image)
		image = dlopen("/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL", RTLD_LAZY);

	return (image ? dlsym(image, name) : NULL);
}
#endif /* __APPLE__ */

#if defined(__sgi) || defined (__sun)
#include <dlfcn.h>
#include <stdio.h>

static void* SunGetProcAddress (const GLubyte* name)
{
  static void* h = NULL;
  static void* gpa;

  if (h == NULL)
  {
    if ((h = dlopen(NULL, RTLD_LAZY | RTLD_LOCAL)) == NULL) return NULL;
    gpa = dlsym(h, "glXGetProcAddress");
  }

  if (gpa != NULL)
    return ((void*(*)(const GLubyte*))gpa)(name);
  else
    return dlsym(h, (const char*)name);
}
#endif /* __sgi || __sun */

#if defined(_WIN32)

#ifdef _MSC_VER
#pragma warning(disable: 4055)
#pragma warning(disable: 4054)
#pragma warning(disable: 4996)
#endif

static int TestPointer(const PROC pTest)
{
	ptrdiff_t iTest;
	if(!pTest) return 0;
	iTest = (ptrdiff_t)pTest;
	
	if(iTest == 1 || iTest == 2 || iTest == 3 || iTest == -1) return 0;
	
	return 1;
}

static PROC WinGetProcAddress(const char *name)
{
	HMODULE glMod = NULL;
	PROC pFunc = wglGetProcAddress((LPCSTR)name);
	if(TestPointer(pFunc))
	{
		return pFunc;
	}
	glMod = GetModuleHandleA("OpenGL32.dll");
	return (PROC)GetProcAddress(glMod, (LPCSTR)name);
}
	
#define IntGetProcAddress(name) WinGetProcAddress(name)
#else
	#if defined(__APPLE__)
		#define IntGetProcAddress(name) AppleGLGetProcAddress(name)
	#else
		#if defined(__sgi) || defined(__sun)
			#define IntGetProcAddress(name) SunGetProcAddress(name)
		#else /* GLX */
		    #include <GL/glx.h>

			#define IntGetProcAddress(name) (*glXGetProcAddressARB)((const GLubyte*)name)
		#endif
	#endif
#endif


/* Extension: 1.0*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLACCUMPROC)(GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_Accum(GLenum op, GLfloat value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLALPHAFUNCPROC)(GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_AlphaFunc(GLenum func, GLfloat ref);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBEGINPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_Begin(GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBITMAPPROC)(GLsizei, GLsizei, GLfloat, GLfloat, GLfloat, GLfloat, const GLubyte *);
static void CODEGEN_FUNCPTR Switch_Bitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDFUNCPROC)(GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_BlendFunc(GLenum sfactor, GLenum dfactor);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCALLLISTPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_CallList(GLuint list);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCALLLISTSPROC)(GLsizei, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_CallLists(GLsizei n, GLenum type, const void * lists);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARPROC)(GLbitfield);
static void CODEGEN_FUNCPTR Switch_Clear(GLbitfield mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARACCUMPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_ClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARCOLORPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARDEPTHPROC)(GLdouble);
static void CODEGEN_FUNCPTR Switch_ClearDepth(GLdouble depth);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARINDEXPROC)(GLfloat);
static void CODEGEN_FUNCPTR Switch_ClearIndex(GLfloat c);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARSTENCILPROC)(GLint);
static void CODEGEN_FUNCPTR Switch_ClearStencil(GLint s);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLIPPLANEPROC)(GLenum, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ClipPlane(GLenum plane, const GLdouble * equation);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3BPROC)(GLbyte, GLbyte, GLbyte);
static void CODEGEN_FUNCPTR Switch_Color3b(GLbyte red, GLbyte green, GLbyte blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3BVPROC)(const GLbyte *);
static void CODEGEN_FUNCPTR Switch_Color3bv(const GLbyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3DPROC)(GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Color3d(GLdouble red, GLdouble green, GLdouble blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Color3dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3FPROC)(GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Color3f(GLfloat red, GLfloat green, GLfloat blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Color3fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3IPROC)(GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Color3i(GLint red, GLint green, GLint blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_Color3iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3SPROC)(GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_Color3s(GLshort red, GLshort green, GLshort blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_Color3sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3UBPROC)(GLubyte, GLubyte, GLubyte);
static void CODEGEN_FUNCPTR Switch_Color3ub(GLubyte red, GLubyte green, GLubyte blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3UBVPROC)(const GLubyte *);
static void CODEGEN_FUNCPTR Switch_Color3ubv(const GLubyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3UIPROC)(GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_Color3ui(GLuint red, GLuint green, GLuint blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3UIVPROC)(const GLuint *);
static void CODEGEN_FUNCPTR Switch_Color3uiv(const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3USPROC)(GLushort, GLushort, GLushort);
static void CODEGEN_FUNCPTR Switch_Color3us(GLushort red, GLushort green, GLushort blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR3USVPROC)(const GLushort *);
static void CODEGEN_FUNCPTR Switch_Color3usv(const GLushort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4BPROC)(GLbyte, GLbyte, GLbyte, GLbyte);
static void CODEGEN_FUNCPTR Switch_Color4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4BVPROC)(const GLbyte *);
static void CODEGEN_FUNCPTR Switch_Color4bv(const GLbyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4DPROC)(GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Color4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Color4dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4FPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Color4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Color4fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4IPROC)(GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Color4i(GLint red, GLint green, GLint blue, GLint alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_Color4iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4SPROC)(GLshort, GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_Color4s(GLshort red, GLshort green, GLshort blue, GLshort alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_Color4sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4UBPROC)(GLubyte, GLubyte, GLubyte, GLubyte);
static void CODEGEN_FUNCPTR Switch_Color4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4UBVPROC)(const GLubyte *);
static void CODEGEN_FUNCPTR Switch_Color4ubv(const GLubyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4UIPROC)(GLuint, GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_Color4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4UIVPROC)(const GLuint *);
static void CODEGEN_FUNCPTR Switch_Color4uiv(const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4USPROC)(GLushort, GLushort, GLushort, GLushort);
static void CODEGEN_FUNCPTR Switch_Color4us(GLushort red, GLushort green, GLushort blue, GLushort alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLOR4USVPROC)(const GLushort *);
static void CODEGEN_FUNCPTR Switch_Color4usv(const GLushort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLORMASKPROC)(GLboolean, GLboolean, GLboolean, GLboolean);
static void CODEGEN_FUNCPTR Switch_ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLORMATERIALPROC)(GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_ColorMaterial(GLenum face, GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYPIXELSPROC)(GLint, GLint, GLsizei, GLsizei, GLenum);
static void CODEGEN_FUNCPTR Switch_CopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCULLFACEPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_CullFace(GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETELISTSPROC)(GLuint, GLsizei);
static void CODEGEN_FUNCPTR Switch_DeleteLists(GLuint list, GLsizei range);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDEPTHFUNCPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_DepthFunc(GLenum func);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDEPTHMASKPROC)(GLboolean);
static void CODEGEN_FUNCPTR Switch_DepthMask(GLboolean flag);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDEPTHRANGEPROC)(GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_DepthRange(GLdouble ren_near, GLdouble ren_far);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDISABLEPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_Disable(GLenum cap);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWBUFFERPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_DrawBuffer(GLenum buf);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWPIXELSPROC)(GLsizei, GLsizei, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_DrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEDGEFLAGPROC)(GLboolean);
static void CODEGEN_FUNCPTR Switch_EdgeFlag(GLboolean flag);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEDGEFLAGVPROC)(const GLboolean *);
static void CODEGEN_FUNCPTR Switch_EdgeFlagv(const GLboolean * flag);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENABLEPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_Enable(GLenum cap);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENDPROC)(void);
static void CODEGEN_FUNCPTR Switch_End(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENDLISTPROC)(void);
static void CODEGEN_FUNCPTR Switch_EndList(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEVALCOORD1DPROC)(GLdouble);
static void CODEGEN_FUNCPTR Switch_EvalCoord1d(GLdouble u);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEVALCOORD1DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_EvalCoord1dv(const GLdouble * u);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEVALCOORD1FPROC)(GLfloat);
static void CODEGEN_FUNCPTR Switch_EvalCoord1f(GLfloat u);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEVALCOORD1FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_EvalCoord1fv(const GLfloat * u);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEVALCOORD2DPROC)(GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_EvalCoord2d(GLdouble u, GLdouble v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEVALCOORD2DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_EvalCoord2dv(const GLdouble * u);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEVALCOORD2FPROC)(GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_EvalCoord2f(GLfloat u, GLfloat v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEVALCOORD2FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_EvalCoord2fv(const GLfloat * u);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEVALMESH1PROC)(GLenum, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_EvalMesh1(GLenum mode, GLint i1, GLint i2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEVALMESH2PROC)(GLenum, GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_EvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEVALPOINT1PROC)(GLint);
static void CODEGEN_FUNCPTR Switch_EvalPoint1(GLint i);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEVALPOINT2PROC)(GLint, GLint);
static void CODEGEN_FUNCPTR Switch_EvalPoint2(GLint i, GLint j);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFEEDBACKBUFFERPROC)(GLsizei, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_FeedbackBuffer(GLsizei size, GLenum type, GLfloat * buffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFINISHPROC)(void);
static void CODEGEN_FUNCPTR Switch_Finish(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFLUSHPROC)(void);
static void CODEGEN_FUNCPTR Switch_Flush(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFOGFPROC)(GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_Fogf(GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFOGFVPROC)(GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Fogfv(GLenum pname, const GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFOGIPROC)(GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_Fogi(GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFOGIVPROC)(GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_Fogiv(GLenum pname, const GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRONTFACEPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_FrontFace(GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRUSTUMPROC)(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef GLuint (CODEGEN_FUNCPTR *PFN_PTRC_GLGENLISTSPROC)(GLsizei);
static GLuint CODEGEN_FUNCPTR Switch_GenLists(GLsizei range);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETBOOLEANVPROC)(GLenum, GLboolean *);
static void CODEGEN_FUNCPTR Switch_GetBooleanv(GLenum pname, GLboolean * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETCLIPPLANEPROC)(GLenum, GLdouble *);
static void CODEGEN_FUNCPTR Switch_GetClipPlane(GLenum plane, GLdouble * equation);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETDOUBLEVPROC)(GLenum, GLdouble *);
static void CODEGEN_FUNCPTR Switch_GetDoublev(GLenum pname, GLdouble * data);
typedef GLenum (CODEGEN_FUNCPTR *PFN_PTRC_GLGETERRORPROC)(void);
static GLenum CODEGEN_FUNCPTR Switch_GetError(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETFLOATVPROC)(GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetFloatv(GLenum pname, GLfloat * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETINTEGERVPROC)(GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetIntegerv(GLenum pname, GLint * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETLIGHTFVPROC)(GLenum, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetLightfv(GLenum light, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETLIGHTIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetLightiv(GLenum light, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETMAPDVPROC)(GLenum, GLenum, GLdouble *);
static void CODEGEN_FUNCPTR Switch_GetMapdv(GLenum target, GLenum query, GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETMAPFVPROC)(GLenum, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetMapfv(GLenum target, GLenum query, GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETMAPIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetMapiv(GLenum target, GLenum query, GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETMATERIALFVPROC)(GLenum, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetMaterialfv(GLenum face, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETMATERIALIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetMaterialiv(GLenum face, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPIXELMAPFVPROC)(GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetPixelMapfv(GLenum map, GLfloat * values);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPIXELMAPUIVPROC)(GLenum, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetPixelMapuiv(GLenum map, GLuint * values);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPIXELMAPUSVPROC)(GLenum, GLushort *);
static void CODEGEN_FUNCPTR Switch_GetPixelMapusv(GLenum map, GLushort * values);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPOLYGONSTIPPLEPROC)(GLubyte *);
static void CODEGEN_FUNCPTR Switch_GetPolygonStipple(GLubyte * mask);
typedef const GLubyte * (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSTRINGPROC)(GLenum);
static const GLubyte * CODEGEN_FUNCPTR Switch_GetString(GLenum name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXENVFVPROC)(GLenum, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetTexEnvfv(GLenum target, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXENVIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetTexEnviv(GLenum target, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXGENDVPROC)(GLenum, GLenum, GLdouble *);
static void CODEGEN_FUNCPTR Switch_GetTexGendv(GLenum coord, GLenum pname, GLdouble * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXGENFVPROC)(GLenum, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetTexGenfv(GLenum coord, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXGENIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetTexGeniv(GLenum coord, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXIMAGEPROC)(GLenum, GLint, GLenum, GLenum, void *);
static void CODEGEN_FUNCPTR Switch_GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXLEVELPARAMETERFVPROC)(GLenum, GLint, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXLEVELPARAMETERIVPROC)(GLenum, GLint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXPARAMETERFVPROC)(GLenum, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetTexParameterfv(GLenum target, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXPARAMETERIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetTexParameteriv(GLenum target, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLHINTPROC)(GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_Hint(GLenum target, GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINDEXMASKPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_IndexMask(GLuint mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINDEXDPROC)(GLdouble);
static void CODEGEN_FUNCPTR Switch_Indexd(GLdouble c);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINDEXDVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Indexdv(const GLdouble * c);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINDEXFPROC)(GLfloat);
static void CODEGEN_FUNCPTR Switch_Indexf(GLfloat c);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINDEXFVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Indexfv(const GLfloat * c);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINDEXIPROC)(GLint);
static void CODEGEN_FUNCPTR Switch_Indexi(GLint c);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINDEXIVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_Indexiv(const GLint * c);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINDEXSPROC)(GLshort);
static void CODEGEN_FUNCPTR Switch_Indexs(GLshort c);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINDEXSVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_Indexsv(const GLshort * c);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINITNAMESPROC)(void);
static void CODEGEN_FUNCPTR Switch_InitNames(void);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISENABLEDPROC)(GLenum);
static GLboolean CODEGEN_FUNCPTR Switch_IsEnabled(GLenum cap);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISLISTPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsList(GLuint list);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLIGHTMODELFPROC)(GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_LightModelf(GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLIGHTMODELFVPROC)(GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_LightModelfv(GLenum pname, const GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLIGHTMODELIPROC)(GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_LightModeli(GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLIGHTMODELIVPROC)(GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_LightModeliv(GLenum pname, const GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLIGHTFPROC)(GLenum, GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_Lightf(GLenum light, GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLIGHTFVPROC)(GLenum, GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Lightfv(GLenum light, GLenum pname, const GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLIGHTIPROC)(GLenum, GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_Lighti(GLenum light, GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLIGHTIVPROC)(GLenum, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_Lightiv(GLenum light, GLenum pname, const GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLINESTIPPLEPROC)(GLint, GLushort);
static void CODEGEN_FUNCPTR Switch_LineStipple(GLint factor, GLushort pattern);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLINEWIDTHPROC)(GLfloat);
static void CODEGEN_FUNCPTR Switch_LineWidth(GLfloat width);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLISTBASEPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_ListBase(GLuint base);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLOADIDENTITYPROC)(void);
static void CODEGEN_FUNCPTR Switch_LoadIdentity(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLOADMATRIXDPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_LoadMatrixd(const GLdouble * m);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLOADMATRIXFPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_LoadMatrixf(const GLfloat * m);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLOADNAMEPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_LoadName(GLuint name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLOGICOPPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_LogicOp(GLenum opcode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMAP1DPROC)(GLenum, GLdouble, GLdouble, GLint, GLint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Map1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMAP1FPROC)(GLenum, GLfloat, GLfloat, GLint, GLint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Map1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMAP2DPROC)(GLenum, GLdouble, GLdouble, GLint, GLint, GLdouble, GLdouble, GLint, GLint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Map2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMAP2FPROC)(GLenum, GLfloat, GLfloat, GLint, GLint, GLfloat, GLfloat, GLint, GLint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Map2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMAPGRID1DPROC)(GLint, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_MapGrid1d(GLint un, GLdouble u1, GLdouble u2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMAPGRID1FPROC)(GLint, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_MapGrid1f(GLint un, GLfloat u1, GLfloat u2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMAPGRID2DPROC)(GLint, GLdouble, GLdouble, GLint, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_MapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMAPGRID2FPROC)(GLint, GLfloat, GLfloat, GLint, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_MapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMATERIALFPROC)(GLenum, GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_Materialf(GLenum face, GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMATERIALFVPROC)(GLenum, GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Materialfv(GLenum face, GLenum pname, const GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMATERIALIPROC)(GLenum, GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_Materiali(GLenum face, GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMATERIALIVPROC)(GLenum, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_Materialiv(GLenum face, GLenum pname, const GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMATRIXMODEPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_MatrixMode(GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTMATRIXDPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_MultMatrixd(const GLdouble * m);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTMATRIXFPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_MultMatrixf(const GLfloat * m);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNEWLISTPROC)(GLuint, GLenum);
static void CODEGEN_FUNCPTR Switch_NewList(GLuint list, GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNORMAL3BPROC)(GLbyte, GLbyte, GLbyte);
static void CODEGEN_FUNCPTR Switch_Normal3b(GLbyte nx, GLbyte ny, GLbyte nz);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNORMAL3BVPROC)(const GLbyte *);
static void CODEGEN_FUNCPTR Switch_Normal3bv(const GLbyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNORMAL3DPROC)(GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Normal3d(GLdouble nx, GLdouble ny, GLdouble nz);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNORMAL3DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Normal3dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNORMAL3FPROC)(GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Normal3f(GLfloat nx, GLfloat ny, GLfloat nz);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNORMAL3FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Normal3fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNORMAL3IPROC)(GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Normal3i(GLint nx, GLint ny, GLint nz);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNORMAL3IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_Normal3iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNORMAL3SPROC)(GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_Normal3s(GLshort nx, GLshort ny, GLshort nz);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNORMAL3SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_Normal3sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLORTHOPROC)(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPASSTHROUGHPROC)(GLfloat);
static void CODEGEN_FUNCPTR Switch_PassThrough(GLfloat token);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPIXELMAPFVPROC)(GLenum, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_PixelMapfv(GLenum map, GLsizei mapsize, const GLfloat * values);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPIXELMAPUIVPROC)(GLenum, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_PixelMapuiv(GLenum map, GLsizei mapsize, const GLuint * values);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPIXELMAPUSVPROC)(GLenum, GLsizei, const GLushort *);
static void CODEGEN_FUNCPTR Switch_PixelMapusv(GLenum map, GLsizei mapsize, const GLushort * values);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPIXELSTOREFPROC)(GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_PixelStoref(GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPIXELSTOREIPROC)(GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_PixelStorei(GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPIXELTRANSFERFPROC)(GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_PixelTransferf(GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPIXELTRANSFERIPROC)(GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_PixelTransferi(GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPIXELZOOMPROC)(GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_PixelZoom(GLfloat xfactor, GLfloat yfactor);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOINTSIZEPROC)(GLfloat);
static void CODEGEN_FUNCPTR Switch_PointSize(GLfloat size);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOLYGONMODEPROC)(GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_PolygonMode(GLenum face, GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOLYGONSTIPPLEPROC)(const GLubyte *);
static void CODEGEN_FUNCPTR Switch_PolygonStipple(const GLubyte * mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOPATTRIBPROC)(void);
static void CODEGEN_FUNCPTR Switch_PopAttrib(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOPMATRIXPROC)(void);
static void CODEGEN_FUNCPTR Switch_PopMatrix(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOPNAMEPROC)(void);
static void CODEGEN_FUNCPTR Switch_PopName(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPUSHATTRIBPROC)(GLbitfield);
static void CODEGEN_FUNCPTR Switch_PushAttrib(GLbitfield mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPUSHMATRIXPROC)(void);
static void CODEGEN_FUNCPTR Switch_PushMatrix(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPUSHNAMEPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_PushName(GLuint name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS2DPROC)(GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_RasterPos2d(GLdouble x, GLdouble y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS2DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_RasterPos2dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS2FPROC)(GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_RasterPos2f(GLfloat x, GLfloat y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS2FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_RasterPos2fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS2IPROC)(GLint, GLint);
static void CODEGEN_FUNCPTR Switch_RasterPos2i(GLint x, GLint y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS2IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_RasterPos2iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS2SPROC)(GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_RasterPos2s(GLshort x, GLshort y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS2SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_RasterPos2sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS3DPROC)(GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_RasterPos3d(GLdouble x, GLdouble y, GLdouble z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS3DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_RasterPos3dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS3FPROC)(GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_RasterPos3f(GLfloat x, GLfloat y, GLfloat z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS3FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_RasterPos3fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS3IPROC)(GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_RasterPos3i(GLint x, GLint y, GLint z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS3IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_RasterPos3iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS3SPROC)(GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_RasterPos3s(GLshort x, GLshort y, GLshort z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS3SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_RasterPos3sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS4DPROC)(GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_RasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS4DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_RasterPos4dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS4FPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_RasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS4FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_RasterPos4fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS4IPROC)(GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_RasterPos4i(GLint x, GLint y, GLint z, GLint w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS4IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_RasterPos4iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS4SPROC)(GLshort, GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_RasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRASTERPOS4SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_RasterPos4sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLREADBUFFERPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_ReadBuffer(GLenum src);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLREADPIXELSPROC)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *);
static void CODEGEN_FUNCPTR Switch_ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRECTDPROC)(GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Rectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRECTDVPROC)(const GLdouble *, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Rectdv(const GLdouble * v1, const GLdouble * v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRECTFPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Rectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRECTFVPROC)(const GLfloat *, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Rectfv(const GLfloat * v1, const GLfloat * v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRECTIPROC)(GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Recti(GLint x1, GLint y1, GLint x2, GLint y2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRECTIVPROC)(const GLint *, const GLint *);
static void CODEGEN_FUNCPTR Switch_Rectiv(const GLint * v1, const GLint * v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRECTSPROC)(GLshort, GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_Rects(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRECTSVPROC)(const GLshort *, const GLshort *);
static void CODEGEN_FUNCPTR Switch_Rectsv(const GLshort * v1, const GLshort * v2);
typedef GLint (CODEGEN_FUNCPTR *PFN_PTRC_GLRENDERMODEPROC)(GLenum);
static GLint CODEGEN_FUNCPTR Switch_RenderMode(GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLROTATEDPROC)(GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Rotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLROTATEFPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Rotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSCALEDPROC)(GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Scaled(GLdouble x, GLdouble y, GLdouble z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSCALEFPROC)(GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Scalef(GLfloat x, GLfloat y, GLfloat z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSCISSORPROC)(GLint, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_Scissor(GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSELECTBUFFERPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_SelectBuffer(GLsizei size, GLuint * buffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSHADEMODELPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_ShadeModel(GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSTENCILFUNCPROC)(GLenum, GLint, GLuint);
static void CODEGEN_FUNCPTR Switch_StencilFunc(GLenum func, GLint ref, GLuint mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSTENCILMASKPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_StencilMask(GLuint mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSTENCILOPPROC)(GLenum, GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_StencilOp(GLenum fail, GLenum zfail, GLenum zpass);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD1DPROC)(GLdouble);
static void CODEGEN_FUNCPTR Switch_TexCoord1d(GLdouble s);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD1DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_TexCoord1dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD1FPROC)(GLfloat);
static void CODEGEN_FUNCPTR Switch_TexCoord1f(GLfloat s);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD1FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_TexCoord1fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD1IPROC)(GLint);
static void CODEGEN_FUNCPTR Switch_TexCoord1i(GLint s);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD1IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_TexCoord1iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD1SPROC)(GLshort);
static void CODEGEN_FUNCPTR Switch_TexCoord1s(GLshort s);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD1SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_TexCoord1sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD2DPROC)(GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_TexCoord2d(GLdouble s, GLdouble t);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD2DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_TexCoord2dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD2FPROC)(GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_TexCoord2f(GLfloat s, GLfloat t);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD2FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_TexCoord2fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD2IPROC)(GLint, GLint);
static void CODEGEN_FUNCPTR Switch_TexCoord2i(GLint s, GLint t);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD2IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_TexCoord2iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD2SPROC)(GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_TexCoord2s(GLshort s, GLshort t);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD2SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_TexCoord2sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD3DPROC)(GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_TexCoord3d(GLdouble s, GLdouble t, GLdouble r);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD3DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_TexCoord3dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD3FPROC)(GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_TexCoord3f(GLfloat s, GLfloat t, GLfloat r);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD3FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_TexCoord3fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD3IPROC)(GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_TexCoord3i(GLint s, GLint t, GLint r);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD3IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_TexCoord3iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD3SPROC)(GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_TexCoord3s(GLshort s, GLshort t, GLshort r);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD3SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_TexCoord3sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD4DPROC)(GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_TexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD4DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_TexCoord4dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD4FPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_TexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD4FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_TexCoord4fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD4IPROC)(GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_TexCoord4i(GLint s, GLint t, GLint r, GLint q);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD4IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_TexCoord4iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD4SPROC)(GLshort, GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_TexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORD4SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_TexCoord4sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXENVFPROC)(GLenum, GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_TexEnvf(GLenum target, GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXENVFVPROC)(GLenum, GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_TexEnvfv(GLenum target, GLenum pname, const GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXENVIPROC)(GLenum, GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_TexEnvi(GLenum target, GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXENVIVPROC)(GLenum, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_TexEnviv(GLenum target, GLenum pname, const GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXGENDPROC)(GLenum, GLenum, GLdouble);
static void CODEGEN_FUNCPTR Switch_TexGend(GLenum coord, GLenum pname, GLdouble param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXGENDVPROC)(GLenum, GLenum, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_TexGendv(GLenum coord, GLenum pname, const GLdouble * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXGENFPROC)(GLenum, GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_TexGenf(GLenum coord, GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXGENFVPROC)(GLenum, GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_TexGenfv(GLenum coord, GLenum pname, const GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXGENIPROC)(GLenum, GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_TexGeni(GLenum coord, GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXGENIVPROC)(GLenum, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_TexGeniv(GLenum coord, GLenum pname, const GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXIMAGE1DPROC)(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXIMAGE2DPROC)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXPARAMETERFPROC)(GLenum, GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_TexParameterf(GLenum target, GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXPARAMETERFVPROC)(GLenum, GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_TexParameterfv(GLenum target, GLenum pname, const GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXPARAMETERIPROC)(GLenum, GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_TexParameteri(GLenum target, GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXPARAMETERIVPROC)(GLenum, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_TexParameteriv(GLenum target, GLenum pname, const GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTRANSLATEDPROC)(GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Translated(GLdouble x, GLdouble y, GLdouble z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTRANSLATEFPROC)(GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Translatef(GLfloat x, GLfloat y, GLfloat z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX2DPROC)(GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Vertex2d(GLdouble x, GLdouble y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX2DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Vertex2dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX2FPROC)(GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Vertex2f(GLfloat x, GLfloat y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX2FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Vertex2fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX2IPROC)(GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Vertex2i(GLint x, GLint y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX2IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_Vertex2iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX2SPROC)(GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_Vertex2s(GLshort x, GLshort y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX2SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_Vertex2sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX3DPROC)(GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Vertex3d(GLdouble x, GLdouble y, GLdouble z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX3DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Vertex3dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX3FPROC)(GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Vertex3f(GLfloat x, GLfloat y, GLfloat z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX3FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Vertex3fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX3IPROC)(GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Vertex3i(GLint x, GLint y, GLint z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX3IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_Vertex3iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX3SPROC)(GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_Vertex3s(GLshort x, GLshort y, GLshort z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX3SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_Vertex3sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX4DPROC)(GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Vertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX4DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Vertex4dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX4FPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Vertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX4FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Vertex4fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX4IPROC)(GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Vertex4i(GLint x, GLint y, GLint z, GLint w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX4IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_Vertex4iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX4SPROC)(GLshort, GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_Vertex4s(GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEX4SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_Vertex4sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVIEWPORTPROC)(GLint, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_Viewport(GLint x, GLint y, GLsizei width, GLsizei height);

/* Extension: 1.1*/
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLARETEXTURESRESIDENTPROC)(GLsizei, const GLuint *, GLboolean *);
static GLboolean CODEGEN_FUNCPTR Switch_AreTexturesResident(GLsizei n, const GLuint * textures, GLboolean * residences);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLARRAYELEMENTPROC)(GLint);
static void CODEGEN_FUNCPTR Switch_ArrayElement(GLint i);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDTEXTUREPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_BindTexture(GLenum target, GLuint texture);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLORPOINTERPROC)(GLint, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_ColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYTEXIMAGE1DPROC)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
static void CODEGEN_FUNCPTR Switch_CopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYTEXIMAGE2DPROC)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
static void CODEGEN_FUNCPTR Switch_CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYTEXSUBIMAGE1DPROC)(GLenum, GLint, GLint, GLint, GLint, GLsizei);
static void CODEGEN_FUNCPTR Switch_CopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETETEXTURESPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteTextures(GLsizei n, const GLuint * textures);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDISABLECLIENTSTATEPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_DisableClientState(GLenum ren_array);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWARRAYSPROC)(GLenum, GLint, GLsizei);
static void CODEGEN_FUNCPTR Switch_DrawArrays(GLenum mode, GLint first, GLsizei count);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWELEMENTSPROC)(GLenum, GLsizei, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_DrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLEDGEFLAGPOINTERPROC)(GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_EdgeFlagPointer(GLsizei stride, const void * pointer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENABLECLIENTSTATEPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_EnableClientState(GLenum ren_array);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENTEXTURESPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenTextures(GLsizei n, GLuint * textures);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPOINTERVPROC)(GLenum, void **);
static void CODEGEN_FUNCPTR Switch_GetPointerv(GLenum pname, void ** params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINDEXPOINTERPROC)(GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_IndexPointer(GLenum type, GLsizei stride, const void * pointer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINDEXUBPROC)(GLubyte);
static void CODEGEN_FUNCPTR Switch_Indexub(GLubyte c);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINDEXUBVPROC)(const GLubyte *);
static void CODEGEN_FUNCPTR Switch_Indexubv(const GLubyte * c);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINTERLEAVEDARRAYSPROC)(GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_InterleavedArrays(GLenum format, GLsizei stride, const void * pointer);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISTEXTUREPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsTexture(GLuint texture);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNORMALPOINTERPROC)(GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_NormalPointer(GLenum type, GLsizei stride, const void * pointer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOLYGONOFFSETPROC)(GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_PolygonOffset(GLfloat factor, GLfloat units);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOPCLIENTATTRIBPROC)(void);
static void CODEGEN_FUNCPTR Switch_PopClientAttrib(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPRIORITIZETEXTURESPROC)(GLsizei, const GLuint *, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_PrioritizeTextures(GLsizei n, const GLuint * textures, const GLfloat * priorities);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPUSHCLIENTATTRIBPROC)(GLbitfield);
static void CODEGEN_FUNCPTR Switch_PushClientAttrib(GLbitfield mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXCOORDPOINTERPROC)(GLint, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_TexCoordPointer(GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXSUBIMAGE1DPROC)(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXPOINTERPROC)(GLint, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_VertexPointer(GLint size, GLenum type, GLsizei stride, const void * pointer);

/* Extension: 1.2*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYTEXSUBIMAGE3DPROC)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWRANGEELEMENTSPROC)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXIMAGE3DPROC)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXSUBIMAGE3DPROC)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);

/* Extension: 1.3*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLACTIVETEXTUREPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_ActiveTexture(GLenum texture);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLIENTACTIVETEXTUREPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_ClientActiveTexture(GLenum texture);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXIMAGE1DPROC)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXIMAGE2DPROC)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXIMAGE3DPROC)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETCOMPRESSEDTEXIMAGEPROC)(GLenum, GLint, void *);
static void CODEGEN_FUNCPTR Switch_GetCompressedTexImage(GLenum target, GLint level, void * img);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLOADTRANSPOSEMATRIXDPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_LoadTransposeMatrixd(const GLdouble * m);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLOADTRANSPOSEMATRIXFPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_LoadTransposeMatrixf(const GLfloat * m);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTTRANSPOSEMATRIXDPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_MultTransposeMatrixd(const GLdouble * m);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTTRANSPOSEMATRIXFPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_MultTransposeMatrixf(const GLfloat * m);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD1DPROC)(GLenum, GLdouble);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord1d(GLenum target, GLdouble s);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD1DVPROC)(GLenum, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord1dv(GLenum target, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD1FPROC)(GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord1f(GLenum target, GLfloat s);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD1FVPROC)(GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord1fv(GLenum target, const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD1IPROC)(GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord1i(GLenum target, GLint s);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD1IVPROC)(GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord1iv(GLenum target, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD1SPROC)(GLenum, GLshort);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord1s(GLenum target, GLshort s);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD1SVPROC)(GLenum, const GLshort *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord1sv(GLenum target, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD2DPROC)(GLenum, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord2d(GLenum target, GLdouble s, GLdouble t);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD2DVPROC)(GLenum, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord2dv(GLenum target, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD2FPROC)(GLenum, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord2f(GLenum target, GLfloat s, GLfloat t);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD2FVPROC)(GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord2fv(GLenum target, const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD2IPROC)(GLenum, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord2i(GLenum target, GLint s, GLint t);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD2IVPROC)(GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord2iv(GLenum target, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD2SPROC)(GLenum, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord2s(GLenum target, GLshort s, GLshort t);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD2SVPROC)(GLenum, const GLshort *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord2sv(GLenum target, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD3DPROC)(GLenum, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD3DVPROC)(GLenum, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord3dv(GLenum target, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD3FPROC)(GLenum, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD3FVPROC)(GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord3fv(GLenum target, const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD3IPROC)(GLenum, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD3IVPROC)(GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord3iv(GLenum target, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD3SPROC)(GLenum, GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD3SVPROC)(GLenum, const GLshort *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord3sv(GLenum target, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD4DPROC)(GLenum, GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD4DVPROC)(GLenum, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord4dv(GLenum target, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD4FPROC)(GLenum, GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD4FVPROC)(GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord4fv(GLenum target, const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD4IPROC)(GLenum, GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD4IVPROC)(GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord4iv(GLenum target, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD4SPROC)(GLenum, GLshort, GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTITEXCOORD4SVPROC)(GLenum, const GLshort *);
static void CODEGEN_FUNCPTR Switch_MultiTexCoord4sv(GLenum target, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLECOVERAGEPROC)(GLfloat, GLboolean);
static void CODEGEN_FUNCPTR Switch_SampleCoverage(GLfloat value, GLboolean invert);

/* Extension: 1.4*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDCOLORPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDEQUATIONPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_BlendEquation(GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDFUNCSEPARATEPROC)(GLenum, GLenum, GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFOGCOORDPOINTERPROC)(GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_FogCoordPointer(GLenum type, GLsizei stride, const void * pointer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFOGCOORDDPROC)(GLdouble);
static void CODEGEN_FUNCPTR Switch_FogCoordd(GLdouble coord);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFOGCOORDDVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_FogCoorddv(const GLdouble * coord);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFOGCOORDFPROC)(GLfloat);
static void CODEGEN_FUNCPTR Switch_FogCoordf(GLfloat coord);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFOGCOORDFVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_FogCoordfv(const GLfloat * coord);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTIDRAWARRAYSPROC)(GLenum, const GLint *, const GLsizei *, GLsizei);
static void CODEGEN_FUNCPTR Switch_MultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTIDRAWELEMENTSPROC)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei);
static void CODEGEN_FUNCPTR Switch_MultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOINTPARAMETERFPROC)(GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_PointParameterf(GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOINTPARAMETERFVPROC)(GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_PointParameterfv(GLenum pname, const GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOINTPARAMETERIPROC)(GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_PointParameteri(GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOINTPARAMETERIVPROC)(GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_PointParameteriv(GLenum pname, const GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3BPROC)(GLbyte, GLbyte, GLbyte);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3BVPROC)(const GLbyte *);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3bv(const GLbyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3DPROC)(GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3FPROC)(GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3IPROC)(GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3i(GLint red, GLint green, GLint blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3SPROC)(GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3s(GLshort red, GLshort green, GLshort blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3UBPROC)(GLubyte, GLubyte, GLubyte);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3UBVPROC)(const GLubyte *);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3ubv(const GLubyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3UIPROC)(GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3ui(GLuint red, GLuint green, GLuint blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3UIVPROC)(const GLuint *);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3uiv(const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3USPROC)(GLushort, GLushort, GLushort);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3us(GLushort red, GLushort green, GLushort blue);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLOR3USVPROC)(const GLushort *);
static void CODEGEN_FUNCPTR Switch_SecondaryColor3usv(const GLushort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSECONDARYCOLORPOINTERPROC)(GLint, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_SecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS2DPROC)(GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_WindowPos2d(GLdouble x, GLdouble y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS2DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_WindowPos2dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS2FPROC)(GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_WindowPos2f(GLfloat x, GLfloat y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS2FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_WindowPos2fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS2IPROC)(GLint, GLint);
static void CODEGEN_FUNCPTR Switch_WindowPos2i(GLint x, GLint y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS2IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_WindowPos2iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS2SPROC)(GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_WindowPos2s(GLshort x, GLshort y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS2SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_WindowPos2sv(const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS3DPROC)(GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_WindowPos3d(GLdouble x, GLdouble y, GLdouble z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS3DVPROC)(const GLdouble *);
static void CODEGEN_FUNCPTR Switch_WindowPos3dv(const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS3FPROC)(GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_WindowPos3f(GLfloat x, GLfloat y, GLfloat z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS3FVPROC)(const GLfloat *);
static void CODEGEN_FUNCPTR Switch_WindowPos3fv(const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS3IPROC)(GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_WindowPos3i(GLint x, GLint y, GLint z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS3IVPROC)(const GLint *);
static void CODEGEN_FUNCPTR Switch_WindowPos3iv(const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS3SPROC)(GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_WindowPos3s(GLshort x, GLshort y, GLshort z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWINDOWPOS3SVPROC)(const GLshort *);
static void CODEGEN_FUNCPTR Switch_WindowPos3sv(const GLshort * v);

/* Extension: 1.5*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBEGINQUERYPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_BeginQuery(GLenum target, GLuint id);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDBUFFERPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_BindBuffer(GLenum target, GLuint buffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBUFFERDATAPROC)(GLenum, GLsizeiptr, const void *, GLenum);
static void CODEGEN_FUNCPTR Switch_BufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBUFFERSUBDATAPROC)(GLenum, GLintptr, GLsizeiptr, const void *);
static void CODEGEN_FUNCPTR Switch_BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETEBUFFERSPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteBuffers(GLsizei n, const GLuint * buffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETEQUERIESPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteQueries(GLsizei n, const GLuint * ids);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENDQUERYPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_EndQuery(GLenum target);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENBUFFERSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenBuffers(GLsizei n, GLuint * buffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENQUERIESPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenQueries(GLsizei n, GLuint * ids);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETBUFFERPARAMETERIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetBufferParameteriv(GLenum target, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETBUFFERPOINTERVPROC)(GLenum, GLenum, void **);
static void CODEGEN_FUNCPTR Switch_GetBufferPointerv(GLenum target, GLenum pname, void ** params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETBUFFERSUBDATAPROC)(GLenum, GLintptr, GLsizeiptr, void *);
static void CODEGEN_FUNCPTR Switch_GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYOBJECTIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetQueryObjectiv(GLuint id, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYOBJECTUIVPROC)(GLuint, GLenum, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetQueryiv(GLenum target, GLenum pname, GLint * params);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISBUFFERPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsBuffer(GLuint buffer);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISQUERYPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsQuery(GLuint id);
typedef void * (CODEGEN_FUNCPTR *PFN_PTRC_GLMAPBUFFERPROC)(GLenum, GLenum);
static void * CODEGEN_FUNCPTR Switch_MapBuffer(GLenum target, GLenum access);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLUNMAPBUFFERPROC)(GLenum);
static GLboolean CODEGEN_FUNCPTR Switch_UnmapBuffer(GLenum target);

/* Extension: 2.0*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLATTACHSHADERPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_AttachShader(GLuint program, GLuint shader);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDATTRIBLOCATIONPROC)(GLuint, GLuint, const GLchar *);
static void CODEGEN_FUNCPTR Switch_BindAttribLocation(GLuint program, GLuint index, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDEQUATIONSEPARATEPROC)(GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPILESHADERPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_CompileShader(GLuint shader);
typedef GLuint (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATEPROGRAMPROC)(void);
static GLuint CODEGEN_FUNCPTR Switch_CreateProgram(void);
typedef GLuint (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATESHADERPROC)(GLenum);
static GLuint CODEGEN_FUNCPTR Switch_CreateShader(GLenum type);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETEPROGRAMPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_DeleteProgram(GLuint program);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETESHADERPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_DeleteShader(GLuint shader);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDETACHSHADERPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_DetachShader(GLuint program, GLuint shader);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDISABLEVERTEXATTRIBARRAYPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_DisableVertexAttribArray(GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWBUFFERSPROC)(GLsizei, const GLenum *);
static void CODEGEN_FUNCPTR Switch_DrawBuffers(GLsizei n, const GLenum * bufs);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENABLEVERTEXATTRIBARRAYPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_EnableVertexAttribArray(GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVEATTRIBPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVEUNIFORMPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETATTACHEDSHADERSPROC)(GLuint, GLsizei, GLsizei *, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
typedef GLint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETATTRIBLOCATIONPROC)(GLuint, const GLchar *);
static GLint CODEGEN_FUNCPTR Switch_GetAttribLocation(GLuint program, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMINFOLOGPROC)(GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetProgramiv(GLuint program, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSHADERINFOLOGPROC)(GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSHADERSOURCEPROC)(GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSHADERIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetShaderiv(GLuint shader, GLenum pname, GLint * params);
typedef GLint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMLOCATIONPROC)(GLuint, const GLchar *);
static GLint CODEGEN_FUNCPTR Switch_GetUniformLocation(GLuint program, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMFVPROC)(GLuint, GLint, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetUniformfv(GLuint program, GLint location, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMIVPROC)(GLuint, GLint, GLint *);
static void CODEGEN_FUNCPTR Switch_GetUniformiv(GLuint program, GLint location, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXATTRIBPOINTERVPROC)(GLuint, GLenum, void **);
static void CODEGEN_FUNCPTR Switch_GetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXATTRIBDVPROC)(GLuint, GLenum, GLdouble *);
static void CODEGEN_FUNCPTR Switch_GetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXATTRIBFVPROC)(GLuint, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXATTRIBIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetVertexAttribiv(GLuint index, GLenum pname, GLint * params);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISPROGRAMPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsProgram(GLuint program);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISSHADERPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsShader(GLuint shader);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLLINKPROGRAMPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_LinkProgram(GLuint program);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSHADERSOURCEPROC)(GLuint, GLsizei, const GLchar *const*, const GLint *);
static void CODEGEN_FUNCPTR Switch_ShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSTENCILFUNCSEPARATEPROC)(GLenum, GLenum, GLint, GLuint);
static void CODEGEN_FUNCPTR Switch_StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSTENCILMASKSEPARATEPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_StencilMaskSeparate(GLenum face, GLuint mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSTENCILOPSEPARATEPROC)(GLenum, GLenum, GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1FPROC)(GLint, GLfloat);
static void CODEGEN_FUNCPTR Switch_Uniform1f(GLint location, GLfloat v0);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1FVPROC)(GLint, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Uniform1fv(GLint location, GLsizei count, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1IPROC)(GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Uniform1i(GLint location, GLint v0);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1IVPROC)(GLint, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_Uniform1iv(GLint location, GLsizei count, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2FPROC)(GLint, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Uniform2f(GLint location, GLfloat v0, GLfloat v1);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2FVPROC)(GLint, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Uniform2fv(GLint location, GLsizei count, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2IPROC)(GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Uniform2i(GLint location, GLint v0, GLint v1);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2IVPROC)(GLint, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_Uniform2iv(GLint location, GLsizei count, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3FPROC)(GLint, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3FVPROC)(GLint, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Uniform3fv(GLint location, GLsizei count, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3IPROC)(GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Uniform3i(GLint location, GLint v0, GLint v1, GLint v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3IVPROC)(GLint, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_Uniform3iv(GLint location, GLsizei count, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4FPROC)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4FVPROC)(GLint, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_Uniform4fv(GLint location, GLsizei count, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4IPROC)(GLint, GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4IVPROC)(GLint, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_Uniform4iv(GLint location, GLsizei count, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX2FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX3FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUSEPROGRAMPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_UseProgram(GLuint program);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVALIDATEPROGRAMPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_ValidateProgram(GLuint program);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB1DPROC)(GLuint, GLdouble);
static void CODEGEN_FUNCPTR Switch_VertexAttrib1d(GLuint index, GLdouble x);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB1DVPROC)(GLuint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib1dv(GLuint index, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB1FPROC)(GLuint, GLfloat);
static void CODEGEN_FUNCPTR Switch_VertexAttrib1f(GLuint index, GLfloat x);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB1FVPROC)(GLuint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib1fv(GLuint index, const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB1SPROC)(GLuint, GLshort);
static void CODEGEN_FUNCPTR Switch_VertexAttrib1s(GLuint index, GLshort x);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB1SVPROC)(GLuint, const GLshort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib1sv(GLuint index, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB2DPROC)(GLuint, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_VertexAttrib2d(GLuint index, GLdouble x, GLdouble y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB2DVPROC)(GLuint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib2dv(GLuint index, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB2FPROC)(GLuint, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_VertexAttrib2f(GLuint index, GLfloat x, GLfloat y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB2FVPROC)(GLuint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib2fv(GLuint index, const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB2SPROC)(GLuint, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_VertexAttrib2s(GLuint index, GLshort x, GLshort y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB2SVPROC)(GLuint, const GLshort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib2sv(GLuint index, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB3DPROC)(GLuint, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_VertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB3DVPROC)(GLuint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib3dv(GLuint index, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB3FPROC)(GLuint, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_VertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB3FVPROC)(GLuint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib3fv(GLuint index, const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB3SPROC)(GLuint, GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_VertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB3SVPROC)(GLuint, const GLshort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib3sv(GLuint index, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NBVPROC)(GLuint, const GLbyte *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nbv(GLuint index, const GLbyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NIVPROC)(GLuint, const GLint *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Niv(GLuint index, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NSVPROC)(GLuint, const GLshort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nsv(GLuint index, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NUBPROC)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NUBVPROC)(GLuint, const GLubyte *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nubv(GLuint index, const GLubyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NUIVPROC)(GLuint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nuiv(GLuint index, const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4NUSVPROC)(GLuint, const GLushort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nusv(GLuint index, const GLushort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4BVPROC)(GLuint, const GLbyte *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4bv(GLuint index, const GLbyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4DPROC)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4DVPROC)(GLuint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4dv(GLuint index, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4FPROC)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4FVPROC)(GLuint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4fv(GLuint index, const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4IVPROC)(GLuint, const GLint *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4iv(GLuint index, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4SPROC)(GLuint, GLshort, GLshort, GLshort, GLshort);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4SVPROC)(GLuint, const GLshort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4sv(GLuint index, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4UBVPROC)(GLuint, const GLubyte *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4ubv(GLuint index, const GLubyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4UIVPROC)(GLuint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4uiv(GLuint index, const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIB4USVPROC)(GLuint, const GLushort *);
static void CODEGEN_FUNCPTR Switch_VertexAttrib4usv(GLuint index, const GLushort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBPOINTERPROC)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);

/* Extension: 2.1*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX2X3FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX2X4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX3X2FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX3X4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX4X2FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX4X3FVPROC)(GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);

/* Extension: 3.0*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBEGINCONDITIONALRENDERPROC)(GLuint, GLenum);
static void CODEGEN_FUNCPTR Switch_BeginConditionalRender(GLuint id, GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBEGINTRANSFORMFEEDBACKPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_BeginTransformFeedback(GLenum primitiveMode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDBUFFERBASEPROC)(GLenum, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_BindBufferBase(GLenum target, GLuint index, GLuint buffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDBUFFERRANGEPROC)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
static void CODEGEN_FUNCPTR Switch_BindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDFRAGDATALOCATIONPROC)(GLuint, GLuint, const GLchar *);
static void CODEGEN_FUNCPTR Switch_BindFragDataLocation(GLuint program, GLuint color, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDFRAMEBUFFERPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_BindFramebuffer(GLenum target, GLuint framebuffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDRENDERBUFFERPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_BindRenderbuffer(GLenum target, GLuint renderbuffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDVERTEXARRAYPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_BindVertexArray(GLuint ren_array);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLITFRAMEBUFFERPROC)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
static void CODEGEN_FUNCPTR Switch_BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef GLenum (CODEGEN_FUNCPTR *PFN_PTRC_GLCHECKFRAMEBUFFERSTATUSPROC)(GLenum);
static GLenum CODEGEN_FUNCPTR Switch_CheckFramebufferStatus(GLenum target);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLAMPCOLORPROC)(GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_ClampColor(GLenum target, GLenum clamp);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARBUFFERFIPROC)(GLenum, GLint, GLfloat, GLint);
static void CODEGEN_FUNCPTR Switch_ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARBUFFERFVPROC)(GLenum, GLint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARBUFFERIVPROC)(GLenum, GLint, const GLint *);
static void CODEGEN_FUNCPTR Switch_ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARBUFFERUIVPROC)(GLenum, GLint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOLORMASKIPROC)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean);
static void CODEGEN_FUNCPTR Switch_ColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETEFRAMEBUFFERSPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteFramebuffers(GLsizei n, const GLuint * framebuffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETERENDERBUFFERSPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETEVERTEXARRAYSPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteVertexArrays(GLsizei n, const GLuint * arrays);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDISABLEIPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_Disablei(GLenum target, GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENABLEIPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_Enablei(GLenum target, GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENDCONDITIONALRENDERPROC)(void);
static void CODEGEN_FUNCPTR Switch_EndConditionalRender(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENDTRANSFORMFEEDBACKPROC)(void);
static void CODEGEN_FUNCPTR Switch_EndTransformFeedback(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFLUSHMAPPEDBUFFERRANGEPROC)(GLenum, GLintptr, GLsizeiptr);
static void CODEGEN_FUNCPTR Switch_FlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRAMEBUFFERRENDERBUFFERPROC)(GLenum, GLenum, GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRAMEBUFFERTEXTURE1DPROC)(GLenum, GLenum, GLenum, GLuint, GLint);
static void CODEGEN_FUNCPTR Switch_FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRAMEBUFFERTEXTURE2DPROC)(GLenum, GLenum, GLenum, GLuint, GLint);
static void CODEGEN_FUNCPTR Switch_FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRAMEBUFFERTEXTURE3DPROC)(GLenum, GLenum, GLenum, GLuint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRAMEBUFFERTEXTURELAYERPROC)(GLenum, GLenum, GLuint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENFRAMEBUFFERSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenFramebuffers(GLsizei n, GLuint * framebuffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENRENDERBUFFERSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenRenderbuffers(GLsizei n, GLuint * renderbuffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENVERTEXARRAYSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenVertexArrays(GLsizei n, GLuint * arrays);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENERATEMIPMAPPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_GenerateMipmap(GLenum target);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETBOOLEANI_VPROC)(GLenum, GLuint, GLboolean *);
static void CODEGEN_FUNCPTR Switch_GetBooleani_v(GLenum target, GLuint index, GLboolean * data);
typedef GLint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETFRAGDATALOCATIONPROC)(GLuint, const GLchar *);
static GLint CODEGEN_FUNCPTR Switch_GetFragDataLocation(GLuint program, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum, GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETINTEGERI_VPROC)(GLenum, GLuint, GLint *);
static void CODEGEN_FUNCPTR Switch_GetIntegeri_v(GLenum target, GLuint index, GLint * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETRENDERBUFFERPARAMETERIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params);
typedef const GLubyte * (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSTRINGIPROC)(GLenum, GLuint);
static const GLubyte * CODEGEN_FUNCPTR Switch_GetStringi(GLenum name, GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXPARAMETERIIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetTexParameterIiv(GLenum target, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXPARAMETERIUIVPROC)(GLenum, GLenum, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMUIVPROC)(GLuint, GLint, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetUniformuiv(GLuint program, GLint location, GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXATTRIBIIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetVertexAttribIiv(GLuint index, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXATTRIBIUIVPROC)(GLuint, GLenum, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISENABLEDIPROC)(GLenum, GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsEnabledi(GLenum target, GLuint index);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISFRAMEBUFFERPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsFramebuffer(GLuint framebuffer);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISRENDERBUFFERPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsRenderbuffer(GLuint renderbuffer);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISVERTEXARRAYPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsVertexArray(GLuint ren_array);
typedef void * (CODEGEN_FUNCPTR *PFN_PTRC_GLMAPBUFFERRANGEPROC)(GLenum, GLintptr, GLsizeiptr, GLbitfield);
static void * CODEGEN_FUNCPTR Switch_MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRENDERBUFFERSTORAGEPROC)(GLenum, GLenum, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXPARAMETERIIVPROC)(GLenum, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_TexParameterIiv(GLenum target, GLenum pname, const GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXPARAMETERIUIVPROC)(GLenum, GLenum, const GLuint *);
static void CODEGEN_FUNCPTR Switch_TexParameterIuiv(GLenum target, GLenum pname, const GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTRANSFORMFEEDBACKVARYINGSPROC)(GLuint, GLsizei, const GLchar *const*, GLenum);
static void CODEGEN_FUNCPTR Switch_TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1UIPROC)(GLint, GLuint);
static void CODEGEN_FUNCPTR Switch_Uniform1ui(GLint location, GLuint v0);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1UIVPROC)(GLint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_Uniform1uiv(GLint location, GLsizei count, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2UIPROC)(GLint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_Uniform2ui(GLint location, GLuint v0, GLuint v1);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2UIVPROC)(GLint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_Uniform2uiv(GLint location, GLsizei count, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3UIPROC)(GLint, GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3UIVPROC)(GLint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_Uniform3uiv(GLint location, GLsizei count, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4UIPROC)(GLint, GLuint, GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4UIVPROC)(GLint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_Uniform4uiv(GLint location, GLsizei count, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI1IPROC)(GLuint, GLint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI1i(GLuint index, GLint x);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI1IVPROC)(GLuint, const GLint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI1iv(GLuint index, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI1UIPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI1ui(GLuint index, GLuint x);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI1UIVPROC)(GLuint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI1uiv(GLuint index, const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI2IPROC)(GLuint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI2i(GLuint index, GLint x, GLint y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI2IVPROC)(GLuint, const GLint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI2iv(GLuint index, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI2UIPROC)(GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI2ui(GLuint index, GLuint x, GLuint y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI2UIVPROC)(GLuint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI2uiv(GLuint index, const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI3IPROC)(GLuint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI3i(GLuint index, GLint x, GLint y, GLint z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI3IVPROC)(GLuint, const GLint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI3iv(GLuint index, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI3UIPROC)(GLuint, GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI3UIVPROC)(GLuint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI3uiv(GLuint index, const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4BVPROC)(GLuint, const GLbyte *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4bv(GLuint index, const GLbyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4IPROC)(GLuint, GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4IVPROC)(GLuint, const GLint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4iv(GLuint index, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4SVPROC)(GLuint, const GLshort *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4sv(GLuint index, const GLshort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4UBVPROC)(GLuint, const GLubyte *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4ubv(GLuint index, const GLubyte * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4UIPROC)(GLuint, GLuint, GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4UIVPROC)(GLuint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4uiv(GLuint index, const GLuint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBI4USVPROC)(GLuint, const GLushort *);
static void CODEGEN_FUNCPTR Switch_VertexAttribI4usv(GLuint index, const GLushort * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBIPOINTERPROC)(GLuint, GLint, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);

/* Extension: 3.1*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYBUFFERSUBDATAPROC)(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
static void CODEGEN_FUNCPTR Switch_CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWARRAYSINSTANCEDPROC)(GLenum, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWELEMENTSINSTANCEDPROC)(GLenum, GLsizei, GLenum, const void *, GLsizei);
static void CODEGEN_FUNCPTR Switch_DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVEUNIFORMBLOCKNAMEPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVEUNIFORMBLOCKIVPROC)(GLuint, GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVEUNIFORMNAMEPROC)(GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVEUNIFORMSIVPROC)(GLuint, GLsizei, const GLuint *, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params);
typedef GLuint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMBLOCKINDEXPROC)(GLuint, const GLchar *);
static GLuint CODEGEN_FUNCPTR Switch_GetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMINDICESPROC)(GLuint, GLsizei, const GLchar *const*, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPRIMITIVERESTARTINDEXPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_PrimitiveRestartIndex(GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXBUFFERPROC)(GLenum, GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_TexBuffer(GLenum target, GLenum internalformat, GLuint buffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMBLOCKBINDINGPROC)(GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);

/* Extension: 3.2*/
typedef GLenum (CODEGEN_FUNCPTR *PFN_PTRC_GLCLIENTWAITSYNCPROC)(GLsync, GLbitfield, GLuint64);
static GLenum CODEGEN_FUNCPTR Switch_ClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETESYNCPROC)(GLsync);
static void CODEGEN_FUNCPTR Switch_DeleteSync(GLsync sync);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWELEMENTSBASEVERTEXPROC)(GLenum, GLsizei, GLenum, const void *, GLint);
static void CODEGEN_FUNCPTR Switch_DrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint);
static void CODEGEN_FUNCPTR Switch_DrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint);
static void CODEGEN_FUNCPTR Switch_DrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex);
typedef GLsync (CODEGEN_FUNCPTR *PFN_PTRC_GLFENCESYNCPROC)(GLenum, GLbitfield);
static GLsync CODEGEN_FUNCPTR Switch_FenceSync(GLenum condition, GLbitfield flags);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRAMEBUFFERTEXTUREPROC)(GLenum, GLenum, GLuint, GLint);
static void CODEGEN_FUNCPTR Switch_FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETBUFFERPARAMETERI64VPROC)(GLenum, GLenum, GLint64 *);
static void CODEGEN_FUNCPTR Switch_GetBufferParameteri64v(GLenum target, GLenum pname, GLint64 * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETINTEGER64I_VPROC)(GLenum, GLuint, GLint64 *);
static void CODEGEN_FUNCPTR Switch_GetInteger64i_v(GLenum target, GLuint index, GLint64 * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETINTEGER64VPROC)(GLenum, GLint64 *);
static void CODEGEN_FUNCPTR Switch_GetInteger64v(GLenum pname, GLint64 * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETMULTISAMPLEFVPROC)(GLenum, GLuint, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetMultisamplefv(GLenum pname, GLuint index, GLfloat * val);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSYNCIVPROC)(GLsync, GLenum, GLsizei, GLsizei *, GLint *);
static void CODEGEN_FUNCPTR Switch_GetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISSYNCPROC)(GLsync);
static GLboolean CODEGEN_FUNCPTR Switch_IsSync(GLsync sync);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_MultiDrawElementsBaseVertex(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount, const GLint * basevertex);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROVOKINGVERTEXPROC)(GLenum);
static void CODEGEN_FUNCPTR Switch_ProvokingVertex(GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLEMASKIPROC)(GLuint, GLbitfield);
static void CODEGEN_FUNCPTR Switch_SampleMaski(GLuint maskNumber, GLbitfield mask);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXIMAGE2DMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
static void CODEGEN_FUNCPTR Switch_TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXIMAGE3DMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
static void CODEGEN_FUNCPTR Switch_TexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLWAITSYNCPROC)(GLsync, GLbitfield, GLuint64);
static void CODEGEN_FUNCPTR Switch_WaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout);

/* Extension: 3.3*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDFRAGDATALOCATIONINDEXEDPROC)(GLuint, GLuint, GLuint, const GLchar *);
static void CODEGEN_FUNCPTR Switch_BindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDSAMPLERPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_BindSampler(GLuint unit, GLuint sampler);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETESAMPLERSPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteSamplers(GLsizei count, const GLuint * samplers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENSAMPLERSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenSamplers(GLsizei count, GLuint * samplers);
typedef GLint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETFRAGDATAINDEXPROC)(GLuint, const GLchar *);
static GLint CODEGEN_FUNCPTR Switch_GetFragDataIndex(GLuint program, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYOBJECTI64VPROC)(GLuint, GLenum, GLint64 *);
static void CODEGEN_FUNCPTR Switch_GetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYOBJECTUI64VPROC)(GLuint, GLenum, GLuint64 *);
static void CODEGEN_FUNCPTR Switch_GetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSAMPLERPARAMETERIIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSAMPLERPARAMETERIUIVPROC)(GLuint, GLenum, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSAMPLERPARAMETERFVPROC)(GLuint, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSAMPLERPARAMETERIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISSAMPLERPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsSampler(GLuint sampler);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLQUERYCOUNTERPROC)(GLuint, GLenum);
static void CODEGEN_FUNCPTR Switch_QueryCounter(GLuint id, GLenum target);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLERPARAMETERIIVPROC)(GLuint, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_SamplerParameterIiv(GLuint sampler, GLenum pname, const GLint * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLERPARAMETERIUIVPROC)(GLuint, GLenum, const GLuint *);
static void CODEGEN_FUNCPTR Switch_SamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLERPARAMETERFPROC)(GLuint, GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_SamplerParameterf(GLuint sampler, GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLERPARAMETERFVPROC)(GLuint, GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_SamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLERPARAMETERIPROC)(GLuint, GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_SamplerParameteri(GLuint sampler, GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSAMPLERPARAMETERIVPROC)(GLuint, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_SamplerParameteriv(GLuint sampler, GLenum pname, const GLint * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBDIVISORPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribDivisor(GLuint index, GLuint divisor);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP1UIPROC)(GLuint, GLenum, GLboolean, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP1UIVPROC)(GLuint, GLenum, GLboolean, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP2UIPROC)(GLuint, GLenum, GLboolean, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP2UIVPROC)(GLuint, GLenum, GLboolean, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP3UIPROC)(GLuint, GLenum, GLboolean, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP3UIVPROC)(GLuint, GLenum, GLboolean, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP4UIPROC)(GLuint, GLenum, GLboolean, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBP4UIVPROC)(GLuint, GLenum, GLboolean, const GLuint *);
static void CODEGEN_FUNCPTR Switch_VertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);

/* Extension: 4.0*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBEGINQUERYINDEXEDPROC)(GLenum, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_BeginQueryIndexed(GLenum target, GLuint index, GLuint id);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDTRANSFORMFEEDBACKPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_BindTransformFeedback(GLenum target, GLuint id);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDEQUATIONSEPARATEIPROC)(GLuint, GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_BlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDEQUATIONIPROC)(GLuint, GLenum);
static void CODEGEN_FUNCPTR Switch_BlendEquationi(GLuint buf, GLenum mode);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDFUNCSEPARATEIPROC)(GLuint, GLenum, GLenum, GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_BlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLENDFUNCIPROC)(GLuint, GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_BlendFunci(GLuint buf, GLenum src, GLenum dst);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETETRANSFORMFEEDBACKSPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteTransformFeedbacks(GLsizei n, const GLuint * ids);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWARRAYSINDIRECTPROC)(GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_DrawArraysIndirect(GLenum mode, const void * indirect);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWELEMENTSINDIRECTPROC)(GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_DrawElementsIndirect(GLenum mode, GLenum type, const void * indirect);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWTRANSFORMFEEDBACKPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_DrawTransformFeedback(GLenum mode, GLuint id);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWTRANSFORMFEEDBACKSTREAMPROC)(GLenum, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_DrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENDQUERYINDEXEDPROC)(GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_EndQueryIndexed(GLenum target, GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENTRANSFORMFEEDBACKSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenTransformFeedbacks(GLsizei n, GLuint * ids);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVESUBROUTINENAMEPROC)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVESUBROUTINEUNIFORMNAMEPROC)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVESUBROUTINEUNIFORMIVPROC)(GLuint, GLenum, GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMSTAGEIVPROC)(GLuint, GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYINDEXEDIVPROC)(GLenum, GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params);
typedef GLuint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSUBROUTINEINDEXPROC)(GLuint, GLenum, const GLchar *);
static GLuint CODEGEN_FUNCPTR Switch_GetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar * name);
typedef GLint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSUBROUTINEUNIFORMLOCATIONPROC)(GLuint, GLenum, const GLchar *);
static GLint CODEGEN_FUNCPTR Switch_GetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMSUBROUTINEUIVPROC)(GLenum, GLint, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETUNIFORMDVPROC)(GLuint, GLint, GLdouble *);
static void CODEGEN_FUNCPTR Switch_GetUniformdv(GLuint program, GLint location, GLdouble * params);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISTRANSFORMFEEDBACKPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsTransformFeedback(GLuint id);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMINSAMPLESHADINGPROC)(GLfloat);
static void CODEGEN_FUNCPTR Switch_MinSampleShading(GLfloat value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPATCHPARAMETERFVPROC)(GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_PatchParameterfv(GLenum pname, const GLfloat * values);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPATCHPARAMETERIPROC)(GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_PatchParameteri(GLenum pname, GLint value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPAUSETRANSFORMFEEDBACKPROC)(void);
static void CODEGEN_FUNCPTR Switch_PauseTransformFeedback(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRESUMETRANSFORMFEEDBACKPROC)(void);
static void CODEGEN_FUNCPTR Switch_ResumeTransformFeedback(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1DPROC)(GLint, GLdouble);
static void CODEGEN_FUNCPTR Switch_Uniform1d(GLint location, GLdouble x);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM1DVPROC)(GLint, GLsizei, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Uniform1dv(GLint location, GLsizei count, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2DPROC)(GLint, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Uniform2d(GLint location, GLdouble x, GLdouble y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM2DVPROC)(GLint, GLsizei, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Uniform2dv(GLint location, GLsizei count, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3DPROC)(GLint, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Uniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM3DVPROC)(GLint, GLsizei, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Uniform3dv(GLint location, GLsizei count, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4DPROC)(GLint, GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_Uniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORM4DVPROC)(GLint, GLsizei, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_Uniform4dv(GLint location, GLsizei count, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX2DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX2X3DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX2X4DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX3DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX3X2DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX3X4DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX4DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX4X2DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMMATRIX4X3DVPROC)(GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_UniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUNIFORMSUBROUTINESUIVPROC)(GLenum, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_UniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint * indices);

/* Extension: 4.1*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLACTIVESHADERPROGRAMPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_ActiveShaderProgram(GLuint pipeline, GLuint program);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDPROGRAMPIPELINEPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_BindProgramPipeline(GLuint pipeline);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARDEPTHFPROC)(GLfloat);
static void CODEGEN_FUNCPTR Switch_ClearDepthf(GLfloat d);
typedef GLuint (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATESHADERPROGRAMVPROC)(GLenum, GLsizei, const GLchar *const*);
static GLuint CODEGEN_FUNCPTR Switch_CreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const* strings);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDELETEPROGRAMPIPELINESPROC)(GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_DeleteProgramPipelines(GLsizei n, const GLuint * pipelines);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDEPTHRANGEARRAYVPROC)(GLuint, GLsizei, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_DepthRangeArrayv(GLuint first, GLsizei count, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDEPTHRANGEINDEXEDPROC)(GLuint, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_DepthRangeIndexed(GLuint index, GLdouble n, GLdouble f);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDEPTHRANGEFPROC)(GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_DepthRangef(GLfloat n, GLfloat f);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENPROGRAMPIPELINESPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GenProgramPipelines(GLsizei n, GLuint * pipelines);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETDOUBLEI_VPROC)(GLenum, GLuint, GLdouble *);
static void CODEGEN_FUNCPTR Switch_GetDoublei_v(GLenum target, GLuint index, GLdouble * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETFLOATI_VPROC)(GLenum, GLuint, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetFloati_v(GLenum target, GLuint index, GLfloat * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMBINARYPROC)(GLuint, GLsizei, GLsizei *, GLenum *, void *);
static void CODEGEN_FUNCPTR Switch_GetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, void * binary);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMPIPELINEINFOLOGPROC)(GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMPIPELINEIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETSHADERPRECISIONFORMATPROC)(GLenum, GLenum, GLint *, GLint *);
static void CODEGEN_FUNCPTR Switch_GetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXATTRIBLDVPROC)(GLuint, GLenum, GLdouble *);
static void CODEGEN_FUNCPTR Switch_GetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLISPROGRAMPIPELINEPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_IsProgramPipeline(GLuint pipeline);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMBINARYPROC)(GLuint, GLenum, const void *, GLsizei);
static void CODEGEN_FUNCPTR Switch_ProgramBinary(GLuint program, GLenum binaryFormat, const void * binary, GLsizei length);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMPARAMETERIPROC)(GLuint, GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_ProgramParameteri(GLuint program, GLenum pname, GLint value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM1DPROC)(GLuint, GLint, GLdouble);
static void CODEGEN_FUNCPTR Switch_ProgramUniform1d(GLuint program, GLint location, GLdouble v0);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM1DVPROC)(GLuint, GLint, GLsizei, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM1FPROC)(GLuint, GLint, GLfloat);
static void CODEGEN_FUNCPTR Switch_ProgramUniform1f(GLuint program, GLint location, GLfloat v0);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM1FVPROC)(GLuint, GLint, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM1IPROC)(GLuint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_ProgramUniform1i(GLuint program, GLint location, GLint v0);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM1IVPROC)(GLuint, GLint, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM1UIPROC)(GLuint, GLint, GLuint);
static void CODEGEN_FUNCPTR Switch_ProgramUniform1ui(GLuint program, GLint location, GLuint v0);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM1UIVPROC)(GLuint, GLint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM2DPROC)(GLuint, GLint, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_ProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM2DVPROC)(GLuint, GLint, GLsizei, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM2FPROC)(GLuint, GLint, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_ProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM2FVPROC)(GLuint, GLint, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM2IPROC)(GLuint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_ProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM2IVPROC)(GLuint, GLint, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM2UIPROC)(GLuint, GLint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_ProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM2UIVPROC)(GLuint, GLint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM3DPROC)(GLuint, GLint, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_ProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM3DVPROC)(GLuint, GLint, GLsizei, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM3FPROC)(GLuint, GLint, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_ProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM3FVPROC)(GLuint, GLint, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM3IPROC)(GLuint, GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_ProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM3IVPROC)(GLuint, GLint, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM3UIPROC)(GLuint, GLint, GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_ProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM3UIVPROC)(GLuint, GLint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM4DPROC)(GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_ProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM4DVPROC)(GLuint, GLint, GLsizei, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM4FPROC)(GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_ProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM4FVPROC)(GLuint, GLint, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM4IPROC)(GLuint, GLint, GLint, GLint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_ProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM4IVPROC)(GLuint, GLint, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM4UIPROC)(GLuint, GLint, GLuint, GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_ProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORM4UIVPROC)(GLuint, GLint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_ProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX2DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX2FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX2X3DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX2X3FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX2X4DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX2X4FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX3DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX3FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX3X2DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX3X2FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX3X4DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX3X4FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX4DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX4FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX4X2DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX4X2FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX4X3DVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPROGRAMUNIFORMMATRIX4X3FVPROC)(GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLRELEASESHADERCOMPILERPROC)(void);
static void CODEGEN_FUNCPTR Switch_ReleaseShaderCompiler(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSCISSORARRAYVPROC)(GLuint, GLsizei, const GLint *);
static void CODEGEN_FUNCPTR Switch_ScissorArrayv(GLuint first, GLsizei count, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSCISSORINDEXEDPROC)(GLuint, GLint, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_ScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSCISSORINDEXEDVPROC)(GLuint, const GLint *);
static void CODEGEN_FUNCPTR Switch_ScissorIndexedv(GLuint index, const GLint * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSHADERBINARYPROC)(GLsizei, const GLuint *, GLenum, const void *, GLsizei);
static void CODEGEN_FUNCPTR Switch_ShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryformat, const void * binary, GLsizei length);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLUSEPROGRAMSTAGESPROC)(GLuint, GLbitfield, GLuint);
static void CODEGEN_FUNCPTR Switch_UseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVALIDATEPROGRAMPIPELINEPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_ValidateProgramPipeline(GLuint pipeline);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBL1DPROC)(GLuint, GLdouble);
static void CODEGEN_FUNCPTR Switch_VertexAttribL1d(GLuint index, GLdouble x);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBL1DVPROC)(GLuint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_VertexAttribL1dv(GLuint index, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBL2DPROC)(GLuint, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_VertexAttribL2d(GLuint index, GLdouble x, GLdouble y);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBL2DVPROC)(GLuint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_VertexAttribL2dv(GLuint index, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBL3DPROC)(GLuint, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_VertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBL3DVPROC)(GLuint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_VertexAttribL3dv(GLuint index, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBL4DPROC)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
static void CODEGEN_FUNCPTR Switch_VertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBL4DVPROC)(GLuint, const GLdouble *);
static void CODEGEN_FUNCPTR Switch_VertexAttribL4dv(GLuint index, const GLdouble * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBLPOINTERPROC)(GLuint, GLint, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_VertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVIEWPORTARRAYVPROC)(GLuint, GLsizei, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ViewportArrayv(GLuint first, GLsizei count, const GLfloat * v);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVIEWPORTINDEXEDFPROC)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
static void CODEGEN_FUNCPTR Switch_ViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVIEWPORTINDEXEDFVPROC)(GLuint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ViewportIndexedfv(GLuint index, const GLfloat * v);

/* Extension: 4.2*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDIMAGETEXTUREPROC)(GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_BindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)(GLenum, GLint, GLsizei, GLsizei, GLuint);
static void CODEGEN_FUNCPTR Switch_DrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint);
static void CODEGEN_FUNCPTR Switch_DrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLuint baseinstance);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)(GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint);
static void CODEGEN_FUNCPTR Switch_DrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)(GLenum, GLuint, GLsizei);
static void CODEGEN_FUNCPTR Switch_DrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)(GLenum, GLuint, GLuint, GLsizei);
static void CODEGEN_FUNCPTR Switch_DrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETACTIVEATOMICCOUNTERBUFFERIVPROC)(GLuint, GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETINTERNALFORMATIVPROC)(GLenum, GLenum, GLenum, GLsizei, GLint *);
static void CODEGEN_FUNCPTR Switch_GetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMEMORYBARRIERPROC)(GLbitfield);
static void CODEGEN_FUNCPTR Switch_MemoryBarrier(GLbitfield barriers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXSTORAGE1DPROC)(GLenum, GLsizei, GLenum, GLsizei);
static void CODEGEN_FUNCPTR Switch_TexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXSTORAGE2DPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_TexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXSTORAGE3DPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_TexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);

/* Extension: 4.3*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDVERTEXBUFFERPROC)(GLuint, GLuint, GLintptr, GLsizei);
static void CODEGEN_FUNCPTR Switch_BindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARBUFFERDATAPROC)(GLenum, GLenum, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_ClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARBUFFERSUBDATAPROC)(GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_ClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYIMAGESUBDATAPROC)(GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_CopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDEBUGMESSAGECALLBACKPROC)(GLDEBUGPROC, const void *);
static void CODEGEN_FUNCPTR Switch_DebugMessageCallback(GLDEBUGPROC callback, const void * userParam);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDEBUGMESSAGECONTROLPROC)(GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean);
static void CODEGEN_FUNCPTR Switch_DebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDEBUGMESSAGEINSERTPROC)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *);
static void CODEGEN_FUNCPTR Switch_DebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDISPATCHCOMPUTEPROC)(GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_DispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDISPATCHCOMPUTEINDIRECTPROC)(GLintptr);
static void CODEGEN_FUNCPTR Switch_DispatchComputeIndirect(GLintptr indirect);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFRAMEBUFFERPARAMETERIPROC)(GLenum, GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_FramebufferParameteri(GLenum target, GLenum pname, GLint param);
typedef GLuint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETDEBUGMESSAGELOGPROC)(GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *);
static GLuint CODEGEN_FUNCPTR Switch_GetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETFRAMEBUFFERPARAMETERIVPROC)(GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetFramebufferParameteriv(GLenum target, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETINTERNALFORMATI64VPROC)(GLenum, GLenum, GLenum, GLsizei, GLint64 *);
static void CODEGEN_FUNCPTR Switch_GetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETOBJECTLABELPROC)(GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETOBJECTPTRLABELPROC)(const void *, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetObjectPtrLabel(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMINTERFACEIVPROC)(GLuint, GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params);
typedef GLuint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMRESOURCEINDEXPROC)(GLuint, GLenum, const GLchar *);
static GLuint CODEGEN_FUNCPTR Switch_GetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar * name);
typedef GLint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMRESOURCELOCATIONPROC)(GLuint, GLenum, const GLchar *);
static GLint CODEGEN_FUNCPTR Switch_GetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar * name);
typedef GLint (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMRESOURCELOCATIONINDEXPROC)(GLuint, GLenum, const GLchar *);
static GLint CODEGEN_FUNCPTR Switch_GetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMRESOURCENAMEPROC)(GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
static void CODEGEN_FUNCPTR Switch_GetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETPROGRAMRESOURCEIVPROC)(GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *);
static void CODEGEN_FUNCPTR Switch_GetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINVALIDATEBUFFERDATAPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_InvalidateBufferData(GLuint buffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINVALIDATEBUFFERSUBDATAPROC)(GLuint, GLintptr, GLsizeiptr);
static void CODEGEN_FUNCPTR Switch_InvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINVALIDATEFRAMEBUFFERPROC)(GLenum, GLsizei, const GLenum *);
static void CODEGEN_FUNCPTR Switch_InvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINVALIDATESUBFRAMEBUFFERPROC)(GLenum, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_InvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINVALIDATETEXIMAGEPROC)(GLuint, GLint);
static void CODEGEN_FUNCPTR Switch_InvalidateTexImage(GLuint texture, GLint level);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINVALIDATETEXSUBIMAGEPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_InvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTIDRAWARRAYSINDIRECTPROC)(GLenum, const void *, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_MultiDrawArraysIndirect(GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMULTIDRAWELEMENTSINDIRECTPROC)(GLenum, GLenum, const void *, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_MultiDrawElementsIndirect(GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLOBJECTLABELPROC)(GLenum, GLuint, GLsizei, const GLchar *);
static void CODEGEN_FUNCPTR Switch_ObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar * label);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLOBJECTPTRLABELPROC)(const void *, GLsizei, const GLchar *);
static void CODEGEN_FUNCPTR Switch_ObjectPtrLabel(const void * ptr, GLsizei length, const GLchar * label);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPOPDEBUGGROUPPROC)(void);
static void CODEGEN_FUNCPTR Switch_PopDebugGroup(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLPUSHDEBUGGROUPPROC)(GLenum, GLuint, GLsizei, const GLchar *);
static void CODEGEN_FUNCPTR Switch_PushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar * message);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLSHADERSTORAGEBLOCKBINDINGPROC)(GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_ShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXBUFFERRANGEPROC)(GLenum, GLenum, GLuint, GLintptr, GLsizeiptr);
static void CODEGEN_FUNCPTR Switch_TexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXSTORAGE2DMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
static void CODEGEN_FUNCPTR Switch_TexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXSTORAGE3DMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
static void CODEGEN_FUNCPTR Switch_TexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTUREVIEWPROC)(GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_TextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBBINDINGPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribBinding(GLuint attribindex, GLuint bindingindex);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBFORMATPROC)(GLuint, GLint, GLenum, GLboolean, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBIFORMATPROC)(GLuint, GLint, GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXATTRIBLFORMATPROC)(GLuint, GLint, GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXBINDINGDIVISORPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexBindingDivisor(GLuint bindingindex, GLuint divisor);

/* Extension: 4.4*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDBUFFERSBASEPROC)(GLenum, GLuint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_BindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint * buffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDBUFFERSRANGEPROC)(GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *);
static void CODEGEN_FUNCPTR Switch_BindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDIMAGETEXTURESPROC)(GLuint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_BindImageTextures(GLuint first, GLsizei count, const GLuint * textures);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDSAMPLERSPROC)(GLuint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_BindSamplers(GLuint first, GLsizei count, const GLuint * samplers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDTEXTURESPROC)(GLuint, GLsizei, const GLuint *);
static void CODEGEN_FUNCPTR Switch_BindTextures(GLuint first, GLsizei count, const GLuint * textures);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDVERTEXBUFFERSPROC)(GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);
static void CODEGEN_FUNCPTR Switch_BindVertexBuffers(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBUFFERSTORAGEPROC)(GLenum, GLsizeiptr, const void *, GLbitfield);
static void CODEGEN_FUNCPTR Switch_BufferStorage(GLenum target, GLsizeiptr size, const void * data, GLbitfield flags);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARTEXIMAGEPROC)(GLuint, GLint, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_ClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARTEXSUBIMAGEPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_ClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * data);

/* Extension: 4.5*/
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBINDTEXTUREUNITPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_BindTextureUnit(GLuint unit, GLuint texture);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLBLITNAMEDFRAMEBUFFERPROC)(GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
static void CODEGEN_FUNCPTR Switch_BlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef GLenum (CODEGEN_FUNCPTR *PFN_PTRC_GLCHECKNAMEDFRAMEBUFFERSTATUSPROC)(GLuint, GLenum);
static GLenum CODEGEN_FUNCPTR Switch_CheckNamedFramebufferStatus(GLuint framebuffer, GLenum target);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARNAMEDBUFFERDATAPROC)(GLuint, GLenum, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_ClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARNAMEDBUFFERSUBDATAPROC)(GLuint, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_ClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARNAMEDFRAMEBUFFERFIPROC)(GLuint, GLenum, GLint, const GLfloat, GLint);
static void CODEGEN_FUNCPTR Switch_ClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat depth, GLint stencil);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARNAMEDFRAMEBUFFERFVPROC)(GLuint, GLenum, GLint, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_ClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARNAMEDFRAMEBUFFERIVPROC)(GLuint, GLenum, GLint, const GLint *);
static void CODEGEN_FUNCPTR Switch_ClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLEARNAMEDFRAMEBUFFERUIVPROC)(GLuint, GLenum, GLint, const GLuint *);
static void CODEGEN_FUNCPTR Switch_ClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCLIPCONTROLPROC)(GLenum, GLenum);
static void CODEGEN_FUNCPTR Switch_ClipControl(GLenum origin, GLenum depth);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXTURESUBIMAGE1DPROC)(GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXTURESUBIMAGE2DPROC)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOMPRESSEDTEXTURESUBIMAGE3DPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
static void CODEGEN_FUNCPTR Switch_CompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYNAMEDBUFFERSUBDATAPROC)(GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr);
static void CODEGEN_FUNCPTR Switch_CopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYTEXTURESUBIMAGE1DPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei);
static void CODEGEN_FUNCPTR Switch_CopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYTEXTURESUBIMAGE2DPROC)(GLuint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_CopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCOPYTEXTURESUBIMAGE3DPROC)(GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_CopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATEBUFFERSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_CreateBuffers(GLsizei n, GLuint * buffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATEFRAMEBUFFERSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_CreateFramebuffers(GLsizei n, GLuint * framebuffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATEPROGRAMPIPELINESPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_CreateProgramPipelines(GLsizei n, GLuint * pipelines);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATEQUERIESPROC)(GLenum, GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_CreateQueries(GLenum target, GLsizei n, GLuint * ids);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATERENDERBUFFERSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_CreateRenderbuffers(GLsizei n, GLuint * renderbuffers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATESAMPLERSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_CreateSamplers(GLsizei n, GLuint * samplers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATETEXTURESPROC)(GLenum, GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_CreateTextures(GLenum target, GLsizei n, GLuint * textures);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATETRANSFORMFEEDBACKSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_CreateTransformFeedbacks(GLsizei n, GLuint * ids);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLCREATEVERTEXARRAYSPROC)(GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_CreateVertexArrays(GLsizei n, GLuint * arrays);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLDISABLEVERTEXARRAYATTRIBPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_DisableVertexArrayAttrib(GLuint vaobj, GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLENABLEVERTEXARRAYATTRIBPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_EnableVertexArrayAttrib(GLuint vaobj, GLuint index);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)(GLuint, GLintptr, GLsizeiptr);
static void CODEGEN_FUNCPTR Switch_FlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGENERATETEXTUREMIPMAPPROC)(GLuint);
static void CODEGEN_FUNCPTR Switch_GenerateTextureMipmap(GLuint texture);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETCOMPRESSEDTEXTUREIMAGEPROC)(GLuint, GLint, GLsizei, void *);
static void CODEGEN_FUNCPTR Switch_GetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETCOMPRESSEDTEXTURESUBIMAGEPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, void *);
static void CODEGEN_FUNCPTR Switch_GetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void * pixels);
typedef GLenum (CODEGEN_FUNCPTR *PFN_PTRC_GLGETGRAPHICSRESETSTATUSPROC)(void);
static GLenum CODEGEN_FUNCPTR Switch_GetGraphicsResetStatus(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETNAMEDBUFFERPARAMETERI64VPROC)(GLuint, GLenum, GLint64 *);
static void CODEGEN_FUNCPTR Switch_GetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETNAMEDBUFFERPARAMETERIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETNAMEDBUFFERPOINTERVPROC)(GLuint, GLenum, void **);
static void CODEGEN_FUNCPTR Switch_GetNamedBufferPointerv(GLuint buffer, GLenum pname, void ** params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETNAMEDBUFFERSUBDATAPROC)(GLuint, GLintptr, GLsizeiptr, void *);
static void CODEGEN_FUNCPTR Switch_GetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLuint, GLenum, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETNAMEDRENDERBUFFERPARAMETERIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYBUFFEROBJECTI64VPROC)(GLuint, GLuint, GLenum, GLintptr);
static void CODEGEN_FUNCPTR Switch_GetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYBUFFEROBJECTIVPROC)(GLuint, GLuint, GLenum, GLintptr);
static void CODEGEN_FUNCPTR Switch_GetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYBUFFEROBJECTUI64VPROC)(GLuint, GLuint, GLenum, GLintptr);
static void CODEGEN_FUNCPTR Switch_GetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETQUERYBUFFEROBJECTUIVPROC)(GLuint, GLuint, GLenum, GLintptr);
static void CODEGEN_FUNCPTR Switch_GetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXTUREIMAGEPROC)(GLuint, GLint, GLenum, GLenum, GLsizei, void *);
static void CODEGEN_FUNCPTR Switch_GetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXTURELEVELPARAMETERFVPROC)(GLuint, GLint, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXTURELEVELPARAMETERIVPROC)(GLuint, GLint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXTUREPARAMETERIIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetTextureParameterIiv(GLuint texture, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXTUREPARAMETERIUIVPROC)(GLuint, GLenum, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXTUREPARAMETERFVPROC)(GLuint, GLenum, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetTextureParameterfv(GLuint texture, GLenum pname, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXTUREPARAMETERIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetTextureParameteriv(GLuint texture, GLenum pname, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTEXTURESUBIMAGEPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
static void CODEGEN_FUNCPTR Switch_GetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTRANSFORMFEEDBACKI64_VPROC)(GLuint, GLenum, GLuint, GLint64 *);
static void CODEGEN_FUNCPTR Switch_GetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTRANSFORMFEEDBACKI_VPROC)(GLuint, GLenum, GLuint, GLint *);
static void CODEGEN_FUNCPTR Switch_GetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETTRANSFORMFEEDBACKIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXARRAYINDEXED64IVPROC)(GLuint, GLuint, GLenum, GLint64 *);
static void CODEGEN_FUNCPTR Switch_GetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXARRAYINDEXEDIVPROC)(GLuint, GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETVERTEXARRAYIVPROC)(GLuint, GLenum, GLint *);
static void CODEGEN_FUNCPTR Switch_GetVertexArrayiv(GLuint vaobj, GLenum pname, GLint * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETNCOMPRESSEDTEXIMAGEPROC)(GLenum, GLint, GLsizei, void *);
static void CODEGEN_FUNCPTR Switch_GetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETNTEXIMAGEPROC)(GLenum, GLint, GLenum, GLenum, GLsizei, void *);
static void CODEGEN_FUNCPTR Switch_GetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETNUNIFORMDVPROC)(GLuint, GLint, GLsizei, GLdouble *);
static void CODEGEN_FUNCPTR Switch_GetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETNUNIFORMFVPROC)(GLuint, GLint, GLsizei, GLfloat *);
static void CODEGEN_FUNCPTR Switch_GetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETNUNIFORMIVPROC)(GLuint, GLint, GLsizei, GLint *);
static void CODEGEN_FUNCPTR Switch_GetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLGETNUNIFORMUIVPROC)(GLuint, GLint, GLsizei, GLuint *);
static void CODEGEN_FUNCPTR Switch_GetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINVALIDATENAMEDFRAMEBUFFERDATAPROC)(GLuint, GLsizei, const GLenum *);
static void CODEGEN_FUNCPTR Switch_InvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)(GLuint, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_InvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void * (CODEGEN_FUNCPTR *PFN_PTRC_GLMAPNAMEDBUFFERPROC)(GLuint, GLenum);
static void * CODEGEN_FUNCPTR Switch_MapNamedBuffer(GLuint buffer, GLenum access);
typedef void * (CODEGEN_FUNCPTR *PFN_PTRC_GLMAPNAMEDBUFFERRANGEPROC)(GLuint, GLintptr, GLsizeiptr, GLbitfield);
static void * CODEGEN_FUNCPTR Switch_MapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLMEMORYBARRIERBYREGIONPROC)(GLbitfield);
static void CODEGEN_FUNCPTR Switch_MemoryBarrierByRegion(GLbitfield barriers);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNAMEDBUFFERDATAPROC)(GLuint, GLsizeiptr, const void *, GLenum);
static void CODEGEN_FUNCPTR Switch_NamedBufferData(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNAMEDBUFFERSTORAGEPROC)(GLuint, GLsizeiptr, const void *, GLbitfield);
static void CODEGEN_FUNCPTR Switch_NamedBufferStorage(GLuint buffer, GLsizeiptr size, const void * data, GLbitfield flags);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNAMEDBUFFERSUBDATAPROC)(GLuint, GLintptr, GLsizeiptr, const void *);
static void CODEGEN_FUNCPTR Switch_NamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNAMEDFRAMEBUFFERDRAWBUFFERPROC)(GLuint, GLenum);
static void CODEGEN_FUNCPTR Switch_NamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)(GLuint, GLsizei, const GLenum *);
static void CODEGEN_FUNCPTR Switch_NamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum * bufs);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNAMEDFRAMEBUFFERPARAMETERIPROC)(GLuint, GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_NamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNAMEDFRAMEBUFFERREADBUFFERPROC)(GLuint, GLenum);
static void CODEGEN_FUNCPTR Switch_NamedFramebufferReadBuffer(GLuint framebuffer, GLenum src);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNAMEDFRAMEBUFFERRENDERBUFFERPROC)(GLuint, GLenum, GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_NamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNAMEDFRAMEBUFFERTEXTUREPROC)(GLuint, GLenum, GLuint, GLint);
static void CODEGEN_FUNCPTR Switch_NamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNAMEDFRAMEBUFFERTEXTURELAYERPROC)(GLuint, GLenum, GLuint, GLint, GLint);
static void CODEGEN_FUNCPTR Switch_NamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNAMEDRENDERBUFFERSTORAGEPROC)(GLuint, GLenum, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_NamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_NamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLREADNPIXELSPROC)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
static void CODEGEN_FUNCPTR Switch_ReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTUREBARRIERPROC)(void);
static void CODEGEN_FUNCPTR Switch_TextureBarrier(void);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTUREBUFFERPROC)(GLuint, GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_TextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTUREBUFFERRANGEPROC)(GLuint, GLenum, GLuint, GLintptr, GLsizeiptr);
static void CODEGEN_FUNCPTR Switch_TextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTUREPARAMETERIIVPROC)(GLuint, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_TextureParameterIiv(GLuint texture, GLenum pname, const GLint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTUREPARAMETERIUIVPROC)(GLuint, GLenum, const GLuint *);
static void CODEGEN_FUNCPTR Switch_TextureParameterIuiv(GLuint texture, GLenum pname, const GLuint * params);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTUREPARAMETERFPROC)(GLuint, GLenum, GLfloat);
static void CODEGEN_FUNCPTR Switch_TextureParameterf(GLuint texture, GLenum pname, GLfloat param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTUREPARAMETERFVPROC)(GLuint, GLenum, const GLfloat *);
static void CODEGEN_FUNCPTR Switch_TextureParameterfv(GLuint texture, GLenum pname, const GLfloat * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTUREPARAMETERIPROC)(GLuint, GLenum, GLint);
static void CODEGEN_FUNCPTR Switch_TextureParameteri(GLuint texture, GLenum pname, GLint param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTUREPARAMETERIVPROC)(GLuint, GLenum, const GLint *);
static void CODEGEN_FUNCPTR Switch_TextureParameteriv(GLuint texture, GLenum pname, const GLint * param);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTURESTORAGE1DPROC)(GLuint, GLsizei, GLenum, GLsizei);
static void CODEGEN_FUNCPTR Switch_TextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTURESTORAGE2DPROC)(GLuint, GLsizei, GLenum, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_TextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTURESTORAGE2DMULTISAMPLEPROC)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
static void CODEGEN_FUNCPTR Switch_TextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTURESTORAGE3DPROC)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
static void CODEGEN_FUNCPTR Switch_TextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTURESTORAGE3DMULTISAMPLEPROC)(GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
static void CODEGEN_FUNCPTR Switch_TextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTURESUBIMAGE1DPROC)(GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTURESUBIMAGE2DPROC)(GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTEXTURESUBIMAGE3DPROC)(GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
static void CODEGEN_FUNCPTR Switch_TextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTRANSFORMFEEDBACKBUFFERBASEPROC)(GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_TransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLTRANSFORMFEEDBACKBUFFERRANGEPROC)(GLuint, GLuint, GLuint, GLintptr, GLsizeiptr);
static void CODEGEN_FUNCPTR Switch_TransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
typedef GLboolean (CODEGEN_FUNCPTR *PFN_PTRC_GLUNMAPNAMEDBUFFERPROC)(GLuint);
static GLboolean CODEGEN_FUNCPTR Switch_UnmapNamedBuffer(GLuint buffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXARRAYATTRIBBINDINGPROC)(GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXARRAYATTRIBFORMATPROC)(GLuint, GLuint, GLint, GLenum, GLboolean, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXARRAYATTRIBIFORMATPROC)(GLuint, GLuint, GLint, GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXARRAYATTRIBLFORMATPROC)(GLuint, GLuint, GLint, GLenum, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXARRAYBINDINGDIVISORPROC)(GLuint, GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXARRAYELEMENTBUFFERPROC)(GLuint, GLuint);
static void CODEGEN_FUNCPTR Switch_VertexArrayElementBuffer(GLuint vaobj, GLuint buffer);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXARRAYVERTEXBUFFERPROC)(GLuint, GLuint, GLuint, GLintptr, GLsizei);
static void CODEGEN_FUNCPTR Switch_VertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
typedef void (CODEGEN_FUNCPTR *PFN_PTRC_GLVERTEXARRAYVERTEXBUFFERSPROC)(GLuint, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);
static void CODEGEN_FUNCPTR Switch_VertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides);


/* Extension: 1.0*/
PFN_PTRC_GLACCUMPROC _ptrc_glAccum = Switch_Accum;
PFN_PTRC_GLALPHAFUNCPROC _ptrc_glAlphaFunc = Switch_AlphaFunc;
PFN_PTRC_GLBEGINPROC _ptrc_glBegin = Switch_Begin;
PFN_PTRC_GLBITMAPPROC _ptrc_glBitmap = Switch_Bitmap;
PFN_PTRC_GLBLENDFUNCPROC _ptrc_glBlendFunc = Switch_BlendFunc;
PFN_PTRC_GLCALLLISTPROC _ptrc_glCallList = Switch_CallList;
PFN_PTRC_GLCALLLISTSPROC _ptrc_glCallLists = Switch_CallLists;
PFN_PTRC_GLCLEARPROC _ptrc_glClear = Switch_Clear;
PFN_PTRC_GLCLEARACCUMPROC _ptrc_glClearAccum = Switch_ClearAccum;
PFN_PTRC_GLCLEARCOLORPROC _ptrc_glClearColor = Switch_ClearColor;
PFN_PTRC_GLCLEARDEPTHPROC _ptrc_glClearDepth = Switch_ClearDepth;
PFN_PTRC_GLCLEARINDEXPROC _ptrc_glClearIndex = Switch_ClearIndex;
PFN_PTRC_GLCLEARSTENCILPROC _ptrc_glClearStencil = Switch_ClearStencil;
PFN_PTRC_GLCLIPPLANEPROC _ptrc_glClipPlane = Switch_ClipPlane;
PFN_PTRC_GLCOLOR3BPROC _ptrc_glColor3b = Switch_Color3b;
PFN_PTRC_GLCOLOR3BVPROC _ptrc_glColor3bv = Switch_Color3bv;
PFN_PTRC_GLCOLOR3DPROC _ptrc_glColor3d = Switch_Color3d;
PFN_PTRC_GLCOLOR3DVPROC _ptrc_glColor3dv = Switch_Color3dv;
PFN_PTRC_GLCOLOR3FPROC _ptrc_glColor3f = Switch_Color3f;
PFN_PTRC_GLCOLOR3FVPROC _ptrc_glColor3fv = Switch_Color3fv;
PFN_PTRC_GLCOLOR3IPROC _ptrc_glColor3i = Switch_Color3i;
PFN_PTRC_GLCOLOR3IVPROC _ptrc_glColor3iv = Switch_Color3iv;
PFN_PTRC_GLCOLOR3SPROC _ptrc_glColor3s = Switch_Color3s;
PFN_PTRC_GLCOLOR3SVPROC _ptrc_glColor3sv = Switch_Color3sv;
PFN_PTRC_GLCOLOR3UBPROC _ptrc_glColor3ub = Switch_Color3ub;
PFN_PTRC_GLCOLOR3UBVPROC _ptrc_glColor3ubv = Switch_Color3ubv;
PFN_PTRC_GLCOLOR3UIPROC _ptrc_glColor3ui = Switch_Color3ui;
PFN_PTRC_GLCOLOR3UIVPROC _ptrc_glColor3uiv = Switch_Color3uiv;
PFN_PTRC_GLCOLOR3USPROC _ptrc_glColor3us = Switch_Color3us;
PFN_PTRC_GLCOLOR3USVPROC _ptrc_glColor3usv = Switch_Color3usv;
PFN_PTRC_GLCOLOR4BPROC _ptrc_glColor4b = Switch_Color4b;
PFN_PTRC_GLCOLOR4BVPROC _ptrc_glColor4bv = Switch_Color4bv;
PFN_PTRC_GLCOLOR4DPROC _ptrc_glColor4d = Switch_Color4d;
PFN_PTRC_GLCOLOR4DVPROC _ptrc_glColor4dv = Switch_Color4dv;
PFN_PTRC_GLCOLOR4FPROC _ptrc_glColor4f = Switch_Color4f;
PFN_PTRC_GLCOLOR4FVPROC _ptrc_glColor4fv = Switch_Color4fv;
PFN_PTRC_GLCOLOR4IPROC _ptrc_glColor4i = Switch_Color4i;
PFN_PTRC_GLCOLOR4IVPROC _ptrc_glColor4iv = Switch_Color4iv;
PFN_PTRC_GLCOLOR4SPROC _ptrc_glColor4s = Switch_Color4s;
PFN_PTRC_GLCOLOR4SVPROC _ptrc_glColor4sv = Switch_Color4sv;
PFN_PTRC_GLCOLOR4UBPROC _ptrc_glColor4ub = Switch_Color4ub;
PFN_PTRC_GLCOLOR4UBVPROC _ptrc_glColor4ubv = Switch_Color4ubv;
PFN_PTRC_GLCOLOR4UIPROC _ptrc_glColor4ui = Switch_Color4ui;
PFN_PTRC_GLCOLOR4UIVPROC _ptrc_glColor4uiv = Switch_Color4uiv;
PFN_PTRC_GLCOLOR4USPROC _ptrc_glColor4us = Switch_Color4us;
PFN_PTRC_GLCOLOR4USVPROC _ptrc_glColor4usv = Switch_Color4usv;
PFN_PTRC_GLCOLORMASKPROC _ptrc_glColorMask = Switch_ColorMask;
PFN_PTRC_GLCOLORMATERIALPROC _ptrc_glColorMaterial = Switch_ColorMaterial;
PFN_PTRC_GLCOPYPIXELSPROC _ptrc_glCopyPixels = Switch_CopyPixels;
PFN_PTRC_GLCULLFACEPROC _ptrc_glCullFace = Switch_CullFace;
PFN_PTRC_GLDELETELISTSPROC _ptrc_glDeleteLists = Switch_DeleteLists;
PFN_PTRC_GLDEPTHFUNCPROC _ptrc_glDepthFunc = Switch_DepthFunc;
PFN_PTRC_GLDEPTHMASKPROC _ptrc_glDepthMask = Switch_DepthMask;
PFN_PTRC_GLDEPTHRANGEPROC _ptrc_glDepthRange = Switch_DepthRange;
PFN_PTRC_GLDISABLEPROC _ptrc_glDisable = Switch_Disable;
PFN_PTRC_GLDRAWBUFFERPROC _ptrc_glDrawBuffer = Switch_DrawBuffer;
PFN_PTRC_GLDRAWPIXELSPROC _ptrc_glDrawPixels = Switch_DrawPixels;
PFN_PTRC_GLEDGEFLAGPROC _ptrc_glEdgeFlag = Switch_EdgeFlag;
PFN_PTRC_GLEDGEFLAGVPROC _ptrc_glEdgeFlagv = Switch_EdgeFlagv;
PFN_PTRC_GLENABLEPROC _ptrc_glEnable = Switch_Enable;
PFN_PTRC_GLENDPROC _ptrc_glEnd = Switch_End;
PFN_PTRC_GLENDLISTPROC _ptrc_glEndList = Switch_EndList;
PFN_PTRC_GLEVALCOORD1DPROC _ptrc_glEvalCoord1d = Switch_EvalCoord1d;
PFN_PTRC_GLEVALCOORD1DVPROC _ptrc_glEvalCoord1dv = Switch_EvalCoord1dv;
PFN_PTRC_GLEVALCOORD1FPROC _ptrc_glEvalCoord1f = Switch_EvalCoord1f;
PFN_PTRC_GLEVALCOORD1FVPROC _ptrc_glEvalCoord1fv = Switch_EvalCoord1fv;
PFN_PTRC_GLEVALCOORD2DPROC _ptrc_glEvalCoord2d = Switch_EvalCoord2d;
PFN_PTRC_GLEVALCOORD2DVPROC _ptrc_glEvalCoord2dv = Switch_EvalCoord2dv;
PFN_PTRC_GLEVALCOORD2FPROC _ptrc_glEvalCoord2f = Switch_EvalCoord2f;
PFN_PTRC_GLEVALCOORD2FVPROC _ptrc_glEvalCoord2fv = Switch_EvalCoord2fv;
PFN_PTRC_GLEVALMESH1PROC _ptrc_glEvalMesh1 = Switch_EvalMesh1;
PFN_PTRC_GLEVALMESH2PROC _ptrc_glEvalMesh2 = Switch_EvalMesh2;
PFN_PTRC_GLEVALPOINT1PROC _ptrc_glEvalPoint1 = Switch_EvalPoint1;
PFN_PTRC_GLEVALPOINT2PROC _ptrc_glEvalPoint2 = Switch_EvalPoint2;
PFN_PTRC_GLFEEDBACKBUFFERPROC _ptrc_glFeedbackBuffer = Switch_FeedbackBuffer;
PFN_PTRC_GLFINISHPROC _ptrc_glFinish = Switch_Finish;
PFN_PTRC_GLFLUSHPROC _ptrc_glFlush = Switch_Flush;
PFN_PTRC_GLFOGFPROC _ptrc_glFogf = Switch_Fogf;
PFN_PTRC_GLFOGFVPROC _ptrc_glFogfv = Switch_Fogfv;
PFN_PTRC_GLFOGIPROC _ptrc_glFogi = Switch_Fogi;
PFN_PTRC_GLFOGIVPROC _ptrc_glFogiv = Switch_Fogiv;
PFN_PTRC_GLFRONTFACEPROC _ptrc_glFrontFace = Switch_FrontFace;
PFN_PTRC_GLFRUSTUMPROC _ptrc_glFrustum = Switch_Frustum;
PFN_PTRC_GLGENLISTSPROC _ptrc_glGenLists = Switch_GenLists;
PFN_PTRC_GLGETBOOLEANVPROC _ptrc_glGetBooleanv = Switch_GetBooleanv;
PFN_PTRC_GLGETCLIPPLANEPROC _ptrc_glGetClipPlane = Switch_GetClipPlane;
PFN_PTRC_GLGETDOUBLEVPROC _ptrc_glGetDoublev = Switch_GetDoublev;
PFN_PTRC_GLGETERRORPROC _ptrc_glGetError = Switch_GetError;
PFN_PTRC_GLGETFLOATVPROC _ptrc_glGetFloatv = Switch_GetFloatv;
PFN_PTRC_GLGETINTEGERVPROC _ptrc_glGetIntegerv = Switch_GetIntegerv;
PFN_PTRC_GLGETLIGHTFVPROC _ptrc_glGetLightfv = Switch_GetLightfv;
PFN_PTRC_GLGETLIGHTIVPROC _ptrc_glGetLightiv = Switch_GetLightiv;
PFN_PTRC_GLGETMAPDVPROC _ptrc_glGetMapdv = Switch_GetMapdv;
PFN_PTRC_GLGETMAPFVPROC _ptrc_glGetMapfv = Switch_GetMapfv;
PFN_PTRC_GLGETMAPIVPROC _ptrc_glGetMapiv = Switch_GetMapiv;
PFN_PTRC_GLGETMATERIALFVPROC _ptrc_glGetMaterialfv = Switch_GetMaterialfv;
PFN_PTRC_GLGETMATERIALIVPROC _ptrc_glGetMaterialiv = Switch_GetMaterialiv;
PFN_PTRC_GLGETPIXELMAPFVPROC _ptrc_glGetPixelMapfv = Switch_GetPixelMapfv;
PFN_PTRC_GLGETPIXELMAPUIVPROC _ptrc_glGetPixelMapuiv = Switch_GetPixelMapuiv;
PFN_PTRC_GLGETPIXELMAPUSVPROC _ptrc_glGetPixelMapusv = Switch_GetPixelMapusv;
PFN_PTRC_GLGETPOLYGONSTIPPLEPROC _ptrc_glGetPolygonStipple = Switch_GetPolygonStipple;
PFN_PTRC_GLGETSTRINGPROC _ptrc_glGetString = Switch_GetString;
PFN_PTRC_GLGETTEXENVFVPROC _ptrc_glGetTexEnvfv = Switch_GetTexEnvfv;
PFN_PTRC_GLGETTEXENVIVPROC _ptrc_glGetTexEnviv = Switch_GetTexEnviv;
PFN_PTRC_GLGETTEXGENDVPROC _ptrc_glGetTexGendv = Switch_GetTexGendv;
PFN_PTRC_GLGETTEXGENFVPROC _ptrc_glGetTexGenfv = Switch_GetTexGenfv;
PFN_PTRC_GLGETTEXGENIVPROC _ptrc_glGetTexGeniv = Switch_GetTexGeniv;
PFN_PTRC_GLGETTEXIMAGEPROC _ptrc_glGetTexImage = Switch_GetTexImage;
PFN_PTRC_GLGETTEXLEVELPARAMETERFVPROC _ptrc_glGetTexLevelParameterfv = Switch_GetTexLevelParameterfv;
PFN_PTRC_GLGETTEXLEVELPARAMETERIVPROC _ptrc_glGetTexLevelParameteriv = Switch_GetTexLevelParameteriv;
PFN_PTRC_GLGETTEXPARAMETERFVPROC _ptrc_glGetTexParameterfv = Switch_GetTexParameterfv;
PFN_PTRC_GLGETTEXPARAMETERIVPROC _ptrc_glGetTexParameteriv = Switch_GetTexParameteriv;
PFN_PTRC_GLHINTPROC _ptrc_glHint = Switch_Hint;
PFN_PTRC_GLINDEXMASKPROC _ptrc_glIndexMask = Switch_IndexMask;
PFN_PTRC_GLINDEXDPROC _ptrc_glIndexd = Switch_Indexd;
PFN_PTRC_GLINDEXDVPROC _ptrc_glIndexdv = Switch_Indexdv;
PFN_PTRC_GLINDEXFPROC _ptrc_glIndexf = Switch_Indexf;
PFN_PTRC_GLINDEXFVPROC _ptrc_glIndexfv = Switch_Indexfv;
PFN_PTRC_GLINDEXIPROC _ptrc_glIndexi = Switch_Indexi;
PFN_PTRC_GLINDEXIVPROC _ptrc_glIndexiv = Switch_Indexiv;
PFN_PTRC_GLINDEXSPROC _ptrc_glIndexs = Switch_Indexs;
PFN_PTRC_GLINDEXSVPROC _ptrc_glIndexsv = Switch_Indexsv;
PFN_PTRC_GLINITNAMESPROC _ptrc_glInitNames = Switch_InitNames;
PFN_PTRC_GLISENABLEDPROC _ptrc_glIsEnabled = Switch_IsEnabled;
PFN_PTRC_GLISLISTPROC _ptrc_glIsList = Switch_IsList;
PFN_PTRC_GLLIGHTMODELFPROC _ptrc_glLightModelf = Switch_LightModelf;
PFN_PTRC_GLLIGHTMODELFVPROC _ptrc_glLightModelfv = Switch_LightModelfv;
PFN_PTRC_GLLIGHTMODELIPROC _ptrc_glLightModeli = Switch_LightModeli;
PFN_PTRC_GLLIGHTMODELIVPROC _ptrc_glLightModeliv = Switch_LightModeliv;
PFN_PTRC_GLLIGHTFPROC _ptrc_glLightf = Switch_Lightf;
PFN_PTRC_GLLIGHTFVPROC _ptrc_glLightfv = Switch_Lightfv;
PFN_PTRC_GLLIGHTIPROC _ptrc_glLighti = Switch_Lighti;
PFN_PTRC_GLLIGHTIVPROC _ptrc_glLightiv = Switch_Lightiv;
PFN_PTRC_GLLINESTIPPLEPROC _ptrc_glLineStipple = Switch_LineStipple;
PFN_PTRC_GLLINEWIDTHPROC _ptrc_glLineWidth = Switch_LineWidth;
PFN_PTRC_GLLISTBASEPROC _ptrc_glListBase = Switch_ListBase;
PFN_PTRC_GLLOADIDENTITYPROC _ptrc_glLoadIdentity = Switch_LoadIdentity;
PFN_PTRC_GLLOADMATRIXDPROC _ptrc_glLoadMatrixd = Switch_LoadMatrixd;
PFN_PTRC_GLLOADMATRIXFPROC _ptrc_glLoadMatrixf = Switch_LoadMatrixf;
PFN_PTRC_GLLOADNAMEPROC _ptrc_glLoadName = Switch_LoadName;
PFN_PTRC_GLLOGICOPPROC _ptrc_glLogicOp = Switch_LogicOp;
PFN_PTRC_GLMAP1DPROC _ptrc_glMap1d = Switch_Map1d;
PFN_PTRC_GLMAP1FPROC _ptrc_glMap1f = Switch_Map1f;
PFN_PTRC_GLMAP2DPROC _ptrc_glMap2d = Switch_Map2d;
PFN_PTRC_GLMAP2FPROC _ptrc_glMap2f = Switch_Map2f;
PFN_PTRC_GLMAPGRID1DPROC _ptrc_glMapGrid1d = Switch_MapGrid1d;
PFN_PTRC_GLMAPGRID1FPROC _ptrc_glMapGrid1f = Switch_MapGrid1f;
PFN_PTRC_GLMAPGRID2DPROC _ptrc_glMapGrid2d = Switch_MapGrid2d;
PFN_PTRC_GLMAPGRID2FPROC _ptrc_glMapGrid2f = Switch_MapGrid2f;
PFN_PTRC_GLMATERIALFPROC _ptrc_glMaterialf = Switch_Materialf;
PFN_PTRC_GLMATERIALFVPROC _ptrc_glMaterialfv = Switch_Materialfv;
PFN_PTRC_GLMATERIALIPROC _ptrc_glMateriali = Switch_Materiali;
PFN_PTRC_GLMATERIALIVPROC _ptrc_glMaterialiv = Switch_Materialiv;
PFN_PTRC_GLMATRIXMODEPROC _ptrc_glMatrixMode = Switch_MatrixMode;
PFN_PTRC_GLMULTMATRIXDPROC _ptrc_glMultMatrixd = Switch_MultMatrixd;
PFN_PTRC_GLMULTMATRIXFPROC _ptrc_glMultMatrixf = Switch_MultMatrixf;
PFN_PTRC_GLNEWLISTPROC _ptrc_glNewList = Switch_NewList;
PFN_PTRC_GLNORMAL3BPROC _ptrc_glNormal3b = Switch_Normal3b;
PFN_PTRC_GLNORMAL3BVPROC _ptrc_glNormal3bv = Switch_Normal3bv;
PFN_PTRC_GLNORMAL3DPROC _ptrc_glNormal3d = Switch_Normal3d;
PFN_PTRC_GLNORMAL3DVPROC _ptrc_glNormal3dv = Switch_Normal3dv;
PFN_PTRC_GLNORMAL3FPROC _ptrc_glNormal3f = Switch_Normal3f;
PFN_PTRC_GLNORMAL3FVPROC _ptrc_glNormal3fv = Switch_Normal3fv;
PFN_PTRC_GLNORMAL3IPROC _ptrc_glNormal3i = Switch_Normal3i;
PFN_PTRC_GLNORMAL3IVPROC _ptrc_glNormal3iv = Switch_Normal3iv;
PFN_PTRC_GLNORMAL3SPROC _ptrc_glNormal3s = Switch_Normal3s;
PFN_PTRC_GLNORMAL3SVPROC _ptrc_glNormal3sv = Switch_Normal3sv;
PFN_PTRC_GLORTHOPROC _ptrc_glOrtho = Switch_Ortho;
PFN_PTRC_GLPASSTHROUGHPROC _ptrc_glPassThrough = Switch_PassThrough;
PFN_PTRC_GLPIXELMAPFVPROC _ptrc_glPixelMapfv = Switch_PixelMapfv;
PFN_PTRC_GLPIXELMAPUIVPROC _ptrc_glPixelMapuiv = Switch_PixelMapuiv;
PFN_PTRC_GLPIXELMAPUSVPROC _ptrc_glPixelMapusv = Switch_PixelMapusv;
PFN_PTRC_GLPIXELSTOREFPROC _ptrc_glPixelStoref = Switch_PixelStoref;
PFN_PTRC_GLPIXELSTOREIPROC _ptrc_glPixelStorei = Switch_PixelStorei;
PFN_PTRC_GLPIXELTRANSFERFPROC _ptrc_glPixelTransferf = Switch_PixelTransferf;
PFN_PTRC_GLPIXELTRANSFERIPROC _ptrc_glPixelTransferi = Switch_PixelTransferi;
PFN_PTRC_GLPIXELZOOMPROC _ptrc_glPixelZoom = Switch_PixelZoom;
PFN_PTRC_GLPOINTSIZEPROC _ptrc_glPointSize = Switch_PointSize;
PFN_PTRC_GLPOLYGONMODEPROC _ptrc_glPolygonMode = Switch_PolygonMode;
PFN_PTRC_GLPOLYGONSTIPPLEPROC _ptrc_glPolygonStipple = Switch_PolygonStipple;
PFN_PTRC_GLPOPATTRIBPROC _ptrc_glPopAttrib = Switch_PopAttrib;
PFN_PTRC_GLPOPMATRIXPROC _ptrc_glPopMatrix = Switch_PopMatrix;
PFN_PTRC_GLPOPNAMEPROC _ptrc_glPopName = Switch_PopName;
PFN_PTRC_GLPUSHATTRIBPROC _ptrc_glPushAttrib = Switch_PushAttrib;
PFN_PTRC_GLPUSHMATRIXPROC _ptrc_glPushMatrix = Switch_PushMatrix;
PFN_PTRC_GLPUSHNAMEPROC _ptrc_glPushName = Switch_PushName;
PFN_PTRC_GLRASTERPOS2DPROC _ptrc_glRasterPos2d = Switch_RasterPos2d;
PFN_PTRC_GLRASTERPOS2DVPROC _ptrc_glRasterPos2dv = Switch_RasterPos2dv;
PFN_PTRC_GLRASTERPOS2FPROC _ptrc_glRasterPos2f = Switch_RasterPos2f;
PFN_PTRC_GLRASTERPOS2FVPROC _ptrc_glRasterPos2fv = Switch_RasterPos2fv;
PFN_PTRC_GLRASTERPOS2IPROC _ptrc_glRasterPos2i = Switch_RasterPos2i;
PFN_PTRC_GLRASTERPOS2IVPROC _ptrc_glRasterPos2iv = Switch_RasterPos2iv;
PFN_PTRC_GLRASTERPOS2SPROC _ptrc_glRasterPos2s = Switch_RasterPos2s;
PFN_PTRC_GLRASTERPOS2SVPROC _ptrc_glRasterPos2sv = Switch_RasterPos2sv;
PFN_PTRC_GLRASTERPOS3DPROC _ptrc_glRasterPos3d = Switch_RasterPos3d;
PFN_PTRC_GLRASTERPOS3DVPROC _ptrc_glRasterPos3dv = Switch_RasterPos3dv;
PFN_PTRC_GLRASTERPOS3FPROC _ptrc_glRasterPos3f = Switch_RasterPos3f;
PFN_PTRC_GLRASTERPOS3FVPROC _ptrc_glRasterPos3fv = Switch_RasterPos3fv;
PFN_PTRC_GLRASTERPOS3IPROC _ptrc_glRasterPos3i = Switch_RasterPos3i;
PFN_PTRC_GLRASTERPOS3IVPROC _ptrc_glRasterPos3iv = Switch_RasterPos3iv;
PFN_PTRC_GLRASTERPOS3SPROC _ptrc_glRasterPos3s = Switch_RasterPos3s;
PFN_PTRC_GLRASTERPOS3SVPROC _ptrc_glRasterPos3sv = Switch_RasterPos3sv;
PFN_PTRC_GLRASTERPOS4DPROC _ptrc_glRasterPos4d = Switch_RasterPos4d;
PFN_PTRC_GLRASTERPOS4DVPROC _ptrc_glRasterPos4dv = Switch_RasterPos4dv;
PFN_PTRC_GLRASTERPOS4FPROC _ptrc_glRasterPos4f = Switch_RasterPos4f;
PFN_PTRC_GLRASTERPOS4FVPROC _ptrc_glRasterPos4fv = Switch_RasterPos4fv;
PFN_PTRC_GLRASTERPOS4IPROC _ptrc_glRasterPos4i = Switch_RasterPos4i;
PFN_PTRC_GLRASTERPOS4IVPROC _ptrc_glRasterPos4iv = Switch_RasterPos4iv;
PFN_PTRC_GLRASTERPOS4SPROC _ptrc_glRasterPos4s = Switch_RasterPos4s;
PFN_PTRC_GLRASTERPOS4SVPROC _ptrc_glRasterPos4sv = Switch_RasterPos4sv;
PFN_PTRC_GLREADBUFFERPROC _ptrc_glReadBuffer = Switch_ReadBuffer;
PFN_PTRC_GLREADPIXELSPROC _ptrc_glReadPixels = Switch_ReadPixels;
PFN_PTRC_GLRECTDPROC _ptrc_glRectd = Switch_Rectd;
PFN_PTRC_GLRECTDVPROC _ptrc_glRectdv = Switch_Rectdv;
PFN_PTRC_GLRECTFPROC _ptrc_glRectf = Switch_Rectf;
PFN_PTRC_GLRECTFVPROC _ptrc_glRectfv = Switch_Rectfv;
PFN_PTRC_GLRECTIPROC _ptrc_glRecti = Switch_Recti;
PFN_PTRC_GLRECTIVPROC _ptrc_glRectiv = Switch_Rectiv;
PFN_PTRC_GLRECTSPROC _ptrc_glRects = Switch_Rects;
PFN_PTRC_GLRECTSVPROC _ptrc_glRectsv = Switch_Rectsv;
PFN_PTRC_GLRENDERMODEPROC _ptrc_glRenderMode = Switch_RenderMode;
PFN_PTRC_GLROTATEDPROC _ptrc_glRotated = Switch_Rotated;
PFN_PTRC_GLROTATEFPROC _ptrc_glRotatef = Switch_Rotatef;
PFN_PTRC_GLSCALEDPROC _ptrc_glScaled = Switch_Scaled;
PFN_PTRC_GLSCALEFPROC _ptrc_glScalef = Switch_Scalef;
PFN_PTRC_GLSCISSORPROC _ptrc_glScissor = Switch_Scissor;
PFN_PTRC_GLSELECTBUFFERPROC _ptrc_glSelectBuffer = Switch_SelectBuffer;
PFN_PTRC_GLSHADEMODELPROC _ptrc_glShadeModel = Switch_ShadeModel;
PFN_PTRC_GLSTENCILFUNCPROC _ptrc_glStencilFunc = Switch_StencilFunc;
PFN_PTRC_GLSTENCILMASKPROC _ptrc_glStencilMask = Switch_StencilMask;
PFN_PTRC_GLSTENCILOPPROC _ptrc_glStencilOp = Switch_StencilOp;
PFN_PTRC_GLTEXCOORD1DPROC _ptrc_glTexCoord1d = Switch_TexCoord1d;
PFN_PTRC_GLTEXCOORD1DVPROC _ptrc_glTexCoord1dv = Switch_TexCoord1dv;
PFN_PTRC_GLTEXCOORD1FPROC _ptrc_glTexCoord1f = Switch_TexCoord1f;
PFN_PTRC_GLTEXCOORD1FVPROC _ptrc_glTexCoord1fv = Switch_TexCoord1fv;
PFN_PTRC_GLTEXCOORD1IPROC _ptrc_glTexCoord1i = Switch_TexCoord1i;
PFN_PTRC_GLTEXCOORD1IVPROC _ptrc_glTexCoord1iv = Switch_TexCoord1iv;
PFN_PTRC_GLTEXCOORD1SPROC _ptrc_glTexCoord1s = Switch_TexCoord1s;
PFN_PTRC_GLTEXCOORD1SVPROC _ptrc_glTexCoord1sv = Switch_TexCoord1sv;
PFN_PTRC_GLTEXCOORD2DPROC _ptrc_glTexCoord2d = Switch_TexCoord2d;
PFN_PTRC_GLTEXCOORD2DVPROC _ptrc_glTexCoord2dv = Switch_TexCoord2dv;
PFN_PTRC_GLTEXCOORD2FPROC _ptrc_glTexCoord2f = Switch_TexCoord2f;
PFN_PTRC_GLTEXCOORD2FVPROC _ptrc_glTexCoord2fv = Switch_TexCoord2fv;
PFN_PTRC_GLTEXCOORD2IPROC _ptrc_glTexCoord2i = Switch_TexCoord2i;
PFN_PTRC_GLTEXCOORD2IVPROC _ptrc_glTexCoord2iv = Switch_TexCoord2iv;
PFN_PTRC_GLTEXCOORD2SPROC _ptrc_glTexCoord2s = Switch_TexCoord2s;
PFN_PTRC_GLTEXCOORD2SVPROC _ptrc_glTexCoord2sv = Switch_TexCoord2sv;
PFN_PTRC_GLTEXCOORD3DPROC _ptrc_glTexCoord3d = Switch_TexCoord3d;
PFN_PTRC_GLTEXCOORD3DVPROC _ptrc_glTexCoord3dv = Switch_TexCoord3dv;
PFN_PTRC_GLTEXCOORD3FPROC _ptrc_glTexCoord3f = Switch_TexCoord3f;
PFN_PTRC_GLTEXCOORD3FVPROC _ptrc_glTexCoord3fv = Switch_TexCoord3fv;
PFN_PTRC_GLTEXCOORD3IPROC _ptrc_glTexCoord3i = Switch_TexCoord3i;
PFN_PTRC_GLTEXCOORD3IVPROC _ptrc_glTexCoord3iv = Switch_TexCoord3iv;
PFN_PTRC_GLTEXCOORD3SPROC _ptrc_glTexCoord3s = Switch_TexCoord3s;
PFN_PTRC_GLTEXCOORD3SVPROC _ptrc_glTexCoord3sv = Switch_TexCoord3sv;
PFN_PTRC_GLTEXCOORD4DPROC _ptrc_glTexCoord4d = Switch_TexCoord4d;
PFN_PTRC_GLTEXCOORD4DVPROC _ptrc_glTexCoord4dv = Switch_TexCoord4dv;
PFN_PTRC_GLTEXCOORD4FPROC _ptrc_glTexCoord4f = Switch_TexCoord4f;
PFN_PTRC_GLTEXCOORD4FVPROC _ptrc_glTexCoord4fv = Switch_TexCoord4fv;
PFN_PTRC_GLTEXCOORD4IPROC _ptrc_glTexCoord4i = Switch_TexCoord4i;
PFN_PTRC_GLTEXCOORD4IVPROC _ptrc_glTexCoord4iv = Switch_TexCoord4iv;
PFN_PTRC_GLTEXCOORD4SPROC _ptrc_glTexCoord4s = Switch_TexCoord4s;
PFN_PTRC_GLTEXCOORD4SVPROC _ptrc_glTexCoord4sv = Switch_TexCoord4sv;
PFN_PTRC_GLTEXENVFPROC _ptrc_glTexEnvf = Switch_TexEnvf;
PFN_PTRC_GLTEXENVFVPROC _ptrc_glTexEnvfv = Switch_TexEnvfv;
PFN_PTRC_GLTEXENVIPROC _ptrc_glTexEnvi = Switch_TexEnvi;
PFN_PTRC_GLTEXENVIVPROC _ptrc_glTexEnviv = Switch_TexEnviv;
PFN_PTRC_GLTEXGENDPROC _ptrc_glTexGend = Switch_TexGend;
PFN_PTRC_GLTEXGENDVPROC _ptrc_glTexGendv = Switch_TexGendv;
PFN_PTRC_GLTEXGENFPROC _ptrc_glTexGenf = Switch_TexGenf;
PFN_PTRC_GLTEXGENFVPROC _ptrc_glTexGenfv = Switch_TexGenfv;
PFN_PTRC_GLTEXGENIPROC _ptrc_glTexGeni = Switch_TexGeni;
PFN_PTRC_GLTEXGENIVPROC _ptrc_glTexGeniv = Switch_TexGeniv;
PFN_PTRC_GLTEXIMAGE1DPROC _ptrc_glTexImage1D = Switch_TexImage1D;
PFN_PTRC_GLTEXIMAGE2DPROC _ptrc_glTexImage2D = Switch_TexImage2D;
PFN_PTRC_GLTEXPARAMETERFPROC _ptrc_glTexParameterf = Switch_TexParameterf;
PFN_PTRC_GLTEXPARAMETERFVPROC _ptrc_glTexParameterfv = Switch_TexParameterfv;
PFN_PTRC_GLTEXPARAMETERIPROC _ptrc_glTexParameteri = Switch_TexParameteri;
PFN_PTRC_GLTEXPARAMETERIVPROC _ptrc_glTexParameteriv = Switch_TexParameteriv;
PFN_PTRC_GLTRANSLATEDPROC _ptrc_glTranslated = Switch_Translated;
PFN_PTRC_GLTRANSLATEFPROC _ptrc_glTranslatef = Switch_Translatef;
PFN_PTRC_GLVERTEX2DPROC _ptrc_glVertex2d = Switch_Vertex2d;
PFN_PTRC_GLVERTEX2DVPROC _ptrc_glVertex2dv = Switch_Vertex2dv;
PFN_PTRC_GLVERTEX2FPROC _ptrc_glVertex2f = Switch_Vertex2f;
PFN_PTRC_GLVERTEX2FVPROC _ptrc_glVertex2fv = Switch_Vertex2fv;
PFN_PTRC_GLVERTEX2IPROC _ptrc_glVertex2i = Switch_Vertex2i;
PFN_PTRC_GLVERTEX2IVPROC _ptrc_glVertex2iv = Switch_Vertex2iv;
PFN_PTRC_GLVERTEX2SPROC _ptrc_glVertex2s = Switch_Vertex2s;
PFN_PTRC_GLVERTEX2SVPROC _ptrc_glVertex2sv = Switch_Vertex2sv;
PFN_PTRC_GLVERTEX3DPROC _ptrc_glVertex3d = Switch_Vertex3d;
PFN_PTRC_GLVERTEX3DVPROC _ptrc_glVertex3dv = Switch_Vertex3dv;
PFN_PTRC_GLVERTEX3FPROC _ptrc_glVertex3f = Switch_Vertex3f;
PFN_PTRC_GLVERTEX3FVPROC _ptrc_glVertex3fv = Switch_Vertex3fv;
PFN_PTRC_GLVERTEX3IPROC _ptrc_glVertex3i = Switch_Vertex3i;
PFN_PTRC_GLVERTEX3IVPROC _ptrc_glVertex3iv = Switch_Vertex3iv;
PFN_PTRC_GLVERTEX3SPROC _ptrc_glVertex3s = Switch_Vertex3s;
PFN_PTRC_GLVERTEX3SVPROC _ptrc_glVertex3sv = Switch_Vertex3sv;
PFN_PTRC_GLVERTEX4DPROC _ptrc_glVertex4d = Switch_Vertex4d;
PFN_PTRC_GLVERTEX4DVPROC _ptrc_glVertex4dv = Switch_Vertex4dv;
PFN_PTRC_GLVERTEX4FPROC _ptrc_glVertex4f = Switch_Vertex4f;
PFN_PTRC_GLVERTEX4FVPROC _ptrc_glVertex4fv = Switch_Vertex4fv;
PFN_PTRC_GLVERTEX4IPROC _ptrc_glVertex4i = Switch_Vertex4i;
PFN_PTRC_GLVERTEX4IVPROC _ptrc_glVertex4iv = Switch_Vertex4iv;
PFN_PTRC_GLVERTEX4SPROC _ptrc_glVertex4s = Switch_Vertex4s;
PFN_PTRC_GLVERTEX4SVPROC _ptrc_glVertex4sv = Switch_Vertex4sv;
PFN_PTRC_GLVIEWPORTPROC _ptrc_glViewport = Switch_Viewport;

/* Extension: 1.1*/
PFN_PTRC_GLARETEXTURESRESIDENTPROC _ptrc_glAreTexturesResident = Switch_AreTexturesResident;
PFN_PTRC_GLARRAYELEMENTPROC _ptrc_glArrayElement = Switch_ArrayElement;
PFN_PTRC_GLBINDTEXTUREPROC _ptrc_glBindTexture = Switch_BindTexture;
PFN_PTRC_GLCOLORPOINTERPROC _ptrc_glColorPointer = Switch_ColorPointer;
PFN_PTRC_GLCOPYTEXIMAGE1DPROC _ptrc_glCopyTexImage1D = Switch_CopyTexImage1D;
PFN_PTRC_GLCOPYTEXIMAGE2DPROC _ptrc_glCopyTexImage2D = Switch_CopyTexImage2D;
PFN_PTRC_GLCOPYTEXSUBIMAGE1DPROC _ptrc_glCopyTexSubImage1D = Switch_CopyTexSubImage1D;
PFN_PTRC_GLCOPYTEXSUBIMAGE2DPROC _ptrc_glCopyTexSubImage2D = Switch_CopyTexSubImage2D;
PFN_PTRC_GLDELETETEXTURESPROC _ptrc_glDeleteTextures = Switch_DeleteTextures;
PFN_PTRC_GLDISABLECLIENTSTATEPROC _ptrc_glDisableClientState = Switch_DisableClientState;
PFN_PTRC_GLDRAWARRAYSPROC _ptrc_glDrawArrays = Switch_DrawArrays;
PFN_PTRC_GLDRAWELEMENTSPROC _ptrc_glDrawElements = Switch_DrawElements;
PFN_PTRC_GLEDGEFLAGPOINTERPROC _ptrc_glEdgeFlagPointer = Switch_EdgeFlagPointer;
PFN_PTRC_GLENABLECLIENTSTATEPROC _ptrc_glEnableClientState = Switch_EnableClientState;
PFN_PTRC_GLGENTEXTURESPROC _ptrc_glGenTextures = Switch_GenTextures;
PFN_PTRC_GLGETPOINTERVPROC _ptrc_glGetPointerv = Switch_GetPointerv;
PFN_PTRC_GLINDEXPOINTERPROC _ptrc_glIndexPointer = Switch_IndexPointer;
PFN_PTRC_GLINDEXUBPROC _ptrc_glIndexub = Switch_Indexub;
PFN_PTRC_GLINDEXUBVPROC _ptrc_glIndexubv = Switch_Indexubv;
PFN_PTRC_GLINTERLEAVEDARRAYSPROC _ptrc_glInterleavedArrays = Switch_InterleavedArrays;
PFN_PTRC_GLISTEXTUREPROC _ptrc_glIsTexture = Switch_IsTexture;
PFN_PTRC_GLNORMALPOINTERPROC _ptrc_glNormalPointer = Switch_NormalPointer;
PFN_PTRC_GLPOLYGONOFFSETPROC _ptrc_glPolygonOffset = Switch_PolygonOffset;
PFN_PTRC_GLPOPCLIENTATTRIBPROC _ptrc_glPopClientAttrib = Switch_PopClientAttrib;
PFN_PTRC_GLPRIORITIZETEXTURESPROC _ptrc_glPrioritizeTextures = Switch_PrioritizeTextures;
PFN_PTRC_GLPUSHCLIENTATTRIBPROC _ptrc_glPushClientAttrib = Switch_PushClientAttrib;
PFN_PTRC_GLTEXCOORDPOINTERPROC _ptrc_glTexCoordPointer = Switch_TexCoordPointer;
PFN_PTRC_GLTEXSUBIMAGE1DPROC _ptrc_glTexSubImage1D = Switch_TexSubImage1D;
PFN_PTRC_GLTEXSUBIMAGE2DPROC _ptrc_glTexSubImage2D = Switch_TexSubImage2D;
PFN_PTRC_GLVERTEXPOINTERPROC _ptrc_glVertexPointer = Switch_VertexPointer;

/* Extension: 1.2*/
PFN_PTRC_GLCOPYTEXSUBIMAGE3DPROC _ptrc_glCopyTexSubImage3D = Switch_CopyTexSubImage3D;
PFN_PTRC_GLDRAWRANGEELEMENTSPROC _ptrc_glDrawRangeElements = Switch_DrawRangeElements;
PFN_PTRC_GLTEXIMAGE3DPROC _ptrc_glTexImage3D = Switch_TexImage3D;
PFN_PTRC_GLTEXSUBIMAGE3DPROC _ptrc_glTexSubImage3D = Switch_TexSubImage3D;

/* Extension: 1.3*/
PFN_PTRC_GLACTIVETEXTUREPROC _ptrc_glActiveTexture = Switch_ActiveTexture;
PFN_PTRC_GLCLIENTACTIVETEXTUREPROC _ptrc_glClientActiveTexture = Switch_ClientActiveTexture;
PFN_PTRC_GLCOMPRESSEDTEXIMAGE1DPROC _ptrc_glCompressedTexImage1D = Switch_CompressedTexImage1D;
PFN_PTRC_GLCOMPRESSEDTEXIMAGE2DPROC _ptrc_glCompressedTexImage2D = Switch_CompressedTexImage2D;
PFN_PTRC_GLCOMPRESSEDTEXIMAGE3DPROC _ptrc_glCompressedTexImage3D = Switch_CompressedTexImage3D;
PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE1DPROC _ptrc_glCompressedTexSubImage1D = Switch_CompressedTexSubImage1D;
PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE2DPROC _ptrc_glCompressedTexSubImage2D = Switch_CompressedTexSubImage2D;
PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE3DPROC _ptrc_glCompressedTexSubImage3D = Switch_CompressedTexSubImage3D;
PFN_PTRC_GLGETCOMPRESSEDTEXIMAGEPROC _ptrc_glGetCompressedTexImage = Switch_GetCompressedTexImage;
PFN_PTRC_GLLOADTRANSPOSEMATRIXDPROC _ptrc_glLoadTransposeMatrixd = Switch_LoadTransposeMatrixd;
PFN_PTRC_GLLOADTRANSPOSEMATRIXFPROC _ptrc_glLoadTransposeMatrixf = Switch_LoadTransposeMatrixf;
PFN_PTRC_GLMULTTRANSPOSEMATRIXDPROC _ptrc_glMultTransposeMatrixd = Switch_MultTransposeMatrixd;
PFN_PTRC_GLMULTTRANSPOSEMATRIXFPROC _ptrc_glMultTransposeMatrixf = Switch_MultTransposeMatrixf;
PFN_PTRC_GLMULTITEXCOORD1DPROC _ptrc_glMultiTexCoord1d = Switch_MultiTexCoord1d;
PFN_PTRC_GLMULTITEXCOORD1DVPROC _ptrc_glMultiTexCoord1dv = Switch_MultiTexCoord1dv;
PFN_PTRC_GLMULTITEXCOORD1FPROC _ptrc_glMultiTexCoord1f = Switch_MultiTexCoord1f;
PFN_PTRC_GLMULTITEXCOORD1FVPROC _ptrc_glMultiTexCoord1fv = Switch_MultiTexCoord1fv;
PFN_PTRC_GLMULTITEXCOORD1IPROC _ptrc_glMultiTexCoord1i = Switch_MultiTexCoord1i;
PFN_PTRC_GLMULTITEXCOORD1IVPROC _ptrc_glMultiTexCoord1iv = Switch_MultiTexCoord1iv;
PFN_PTRC_GLMULTITEXCOORD1SPROC _ptrc_glMultiTexCoord1s = Switch_MultiTexCoord1s;
PFN_PTRC_GLMULTITEXCOORD1SVPROC _ptrc_glMultiTexCoord1sv = Switch_MultiTexCoord1sv;
PFN_PTRC_GLMULTITEXCOORD2DPROC _ptrc_glMultiTexCoord2d = Switch_MultiTexCoord2d;
PFN_PTRC_GLMULTITEXCOORD2DVPROC _ptrc_glMultiTexCoord2dv = Switch_MultiTexCoord2dv;
PFN_PTRC_GLMULTITEXCOORD2FPROC _ptrc_glMultiTexCoord2f = Switch_MultiTexCoord2f;
PFN_PTRC_GLMULTITEXCOORD2FVPROC _ptrc_glMultiTexCoord2fv = Switch_MultiTexCoord2fv;
PFN_PTRC_GLMULTITEXCOORD2IPROC _ptrc_glMultiTexCoord2i = Switch_MultiTexCoord2i;
PFN_PTRC_GLMULTITEXCOORD2IVPROC _ptrc_glMultiTexCoord2iv = Switch_MultiTexCoord2iv;
PFN_PTRC_GLMULTITEXCOORD2SPROC _ptrc_glMultiTexCoord2s = Switch_MultiTexCoord2s;
PFN_PTRC_GLMULTITEXCOORD2SVPROC _ptrc_glMultiTexCoord2sv = Switch_MultiTexCoord2sv;
PFN_PTRC_GLMULTITEXCOORD3DPROC _ptrc_glMultiTexCoord3d = Switch_MultiTexCoord3d;
PFN_PTRC_GLMULTITEXCOORD3DVPROC _ptrc_glMultiTexCoord3dv = Switch_MultiTexCoord3dv;
PFN_PTRC_GLMULTITEXCOORD3FPROC _ptrc_glMultiTexCoord3f = Switch_MultiTexCoord3f;
PFN_PTRC_GLMULTITEXCOORD3FVPROC _ptrc_glMultiTexCoord3fv = Switch_MultiTexCoord3fv;
PFN_PTRC_GLMULTITEXCOORD3IPROC _ptrc_glMultiTexCoord3i = Switch_MultiTexCoord3i;
PFN_PTRC_GLMULTITEXCOORD3IVPROC _ptrc_glMultiTexCoord3iv = Switch_MultiTexCoord3iv;
PFN_PTRC_GLMULTITEXCOORD3SPROC _ptrc_glMultiTexCoord3s = Switch_MultiTexCoord3s;
PFN_PTRC_GLMULTITEXCOORD3SVPROC _ptrc_glMultiTexCoord3sv = Switch_MultiTexCoord3sv;
PFN_PTRC_GLMULTITEXCOORD4DPROC _ptrc_glMultiTexCoord4d = Switch_MultiTexCoord4d;
PFN_PTRC_GLMULTITEXCOORD4DVPROC _ptrc_glMultiTexCoord4dv = Switch_MultiTexCoord4dv;
PFN_PTRC_GLMULTITEXCOORD4FPROC _ptrc_glMultiTexCoord4f = Switch_MultiTexCoord4f;
PFN_PTRC_GLMULTITEXCOORD4FVPROC _ptrc_glMultiTexCoord4fv = Switch_MultiTexCoord4fv;
PFN_PTRC_GLMULTITEXCOORD4IPROC _ptrc_glMultiTexCoord4i = Switch_MultiTexCoord4i;
PFN_PTRC_GLMULTITEXCOORD4IVPROC _ptrc_glMultiTexCoord4iv = Switch_MultiTexCoord4iv;
PFN_PTRC_GLMULTITEXCOORD4SPROC _ptrc_glMultiTexCoord4s = Switch_MultiTexCoord4s;
PFN_PTRC_GLMULTITEXCOORD4SVPROC _ptrc_glMultiTexCoord4sv = Switch_MultiTexCoord4sv;
PFN_PTRC_GLSAMPLECOVERAGEPROC _ptrc_glSampleCoverage = Switch_SampleCoverage;

/* Extension: 1.4*/
PFN_PTRC_GLBLENDCOLORPROC _ptrc_glBlendColor = Switch_BlendColor;
PFN_PTRC_GLBLENDEQUATIONPROC _ptrc_glBlendEquation = Switch_BlendEquation;
PFN_PTRC_GLBLENDFUNCSEPARATEPROC _ptrc_glBlendFuncSeparate = Switch_BlendFuncSeparate;
PFN_PTRC_GLFOGCOORDPOINTERPROC _ptrc_glFogCoordPointer = Switch_FogCoordPointer;
PFN_PTRC_GLFOGCOORDDPROC _ptrc_glFogCoordd = Switch_FogCoordd;
PFN_PTRC_GLFOGCOORDDVPROC _ptrc_glFogCoorddv = Switch_FogCoorddv;
PFN_PTRC_GLFOGCOORDFPROC _ptrc_glFogCoordf = Switch_FogCoordf;
PFN_PTRC_GLFOGCOORDFVPROC _ptrc_glFogCoordfv = Switch_FogCoordfv;
PFN_PTRC_GLMULTIDRAWARRAYSPROC _ptrc_glMultiDrawArrays = Switch_MultiDrawArrays;
PFN_PTRC_GLMULTIDRAWELEMENTSPROC _ptrc_glMultiDrawElements = Switch_MultiDrawElements;
PFN_PTRC_GLPOINTPARAMETERFPROC _ptrc_glPointParameterf = Switch_PointParameterf;
PFN_PTRC_GLPOINTPARAMETERFVPROC _ptrc_glPointParameterfv = Switch_PointParameterfv;
PFN_PTRC_GLPOINTPARAMETERIPROC _ptrc_glPointParameteri = Switch_PointParameteri;
PFN_PTRC_GLPOINTPARAMETERIVPROC _ptrc_glPointParameteriv = Switch_PointParameteriv;
PFN_PTRC_GLSECONDARYCOLOR3BPROC _ptrc_glSecondaryColor3b = Switch_SecondaryColor3b;
PFN_PTRC_GLSECONDARYCOLOR3BVPROC _ptrc_glSecondaryColor3bv = Switch_SecondaryColor3bv;
PFN_PTRC_GLSECONDARYCOLOR3DPROC _ptrc_glSecondaryColor3d = Switch_SecondaryColor3d;
PFN_PTRC_GLSECONDARYCOLOR3DVPROC _ptrc_glSecondaryColor3dv = Switch_SecondaryColor3dv;
PFN_PTRC_GLSECONDARYCOLOR3FPROC _ptrc_glSecondaryColor3f = Switch_SecondaryColor3f;
PFN_PTRC_GLSECONDARYCOLOR3FVPROC _ptrc_glSecondaryColor3fv = Switch_SecondaryColor3fv;
PFN_PTRC_GLSECONDARYCOLOR3IPROC _ptrc_glSecondaryColor3i = Switch_SecondaryColor3i;
PFN_PTRC_GLSECONDARYCOLOR3IVPROC _ptrc_glSecondaryColor3iv = Switch_SecondaryColor3iv;
PFN_PTRC_GLSECONDARYCOLOR3SPROC _ptrc_glSecondaryColor3s = Switch_SecondaryColor3s;
PFN_PTRC_GLSECONDARYCOLOR3SVPROC _ptrc_glSecondaryColor3sv = Switch_SecondaryColor3sv;
PFN_PTRC_GLSECONDARYCOLOR3UBPROC _ptrc_glSecondaryColor3ub = Switch_SecondaryColor3ub;
PFN_PTRC_GLSECONDARYCOLOR3UBVPROC _ptrc_glSecondaryColor3ubv = Switch_SecondaryColor3ubv;
PFN_PTRC_GLSECONDARYCOLOR3UIPROC _ptrc_glSecondaryColor3ui = Switch_SecondaryColor3ui;
PFN_PTRC_GLSECONDARYCOLOR3UIVPROC _ptrc_glSecondaryColor3uiv = Switch_SecondaryColor3uiv;
PFN_PTRC_GLSECONDARYCOLOR3USPROC _ptrc_glSecondaryColor3us = Switch_SecondaryColor3us;
PFN_PTRC_GLSECONDARYCOLOR3USVPROC _ptrc_glSecondaryColor3usv = Switch_SecondaryColor3usv;
PFN_PTRC_GLSECONDARYCOLORPOINTERPROC _ptrc_glSecondaryColorPointer = Switch_SecondaryColorPointer;
PFN_PTRC_GLWINDOWPOS2DPROC _ptrc_glWindowPos2d = Switch_WindowPos2d;
PFN_PTRC_GLWINDOWPOS2DVPROC _ptrc_glWindowPos2dv = Switch_WindowPos2dv;
PFN_PTRC_GLWINDOWPOS2FPROC _ptrc_glWindowPos2f = Switch_WindowPos2f;
PFN_PTRC_GLWINDOWPOS2FVPROC _ptrc_glWindowPos2fv = Switch_WindowPos2fv;
PFN_PTRC_GLWINDOWPOS2IPROC _ptrc_glWindowPos2i = Switch_WindowPos2i;
PFN_PTRC_GLWINDOWPOS2IVPROC _ptrc_glWindowPos2iv = Switch_WindowPos2iv;
PFN_PTRC_GLWINDOWPOS2SPROC _ptrc_glWindowPos2s = Switch_WindowPos2s;
PFN_PTRC_GLWINDOWPOS2SVPROC _ptrc_glWindowPos2sv = Switch_WindowPos2sv;
PFN_PTRC_GLWINDOWPOS3DPROC _ptrc_glWindowPos3d = Switch_WindowPos3d;
PFN_PTRC_GLWINDOWPOS3DVPROC _ptrc_glWindowPos3dv = Switch_WindowPos3dv;
PFN_PTRC_GLWINDOWPOS3FPROC _ptrc_glWindowPos3f = Switch_WindowPos3f;
PFN_PTRC_GLWINDOWPOS3FVPROC _ptrc_glWindowPos3fv = Switch_WindowPos3fv;
PFN_PTRC_GLWINDOWPOS3IPROC _ptrc_glWindowPos3i = Switch_WindowPos3i;
PFN_PTRC_GLWINDOWPOS3IVPROC _ptrc_glWindowPos3iv = Switch_WindowPos3iv;
PFN_PTRC_GLWINDOWPOS3SPROC _ptrc_glWindowPos3s = Switch_WindowPos3s;
PFN_PTRC_GLWINDOWPOS3SVPROC _ptrc_glWindowPos3sv = Switch_WindowPos3sv;

/* Extension: 1.5*/
PFN_PTRC_GLBEGINQUERYPROC _ptrc_glBeginQuery = Switch_BeginQuery;
PFN_PTRC_GLBINDBUFFERPROC _ptrc_glBindBuffer = Switch_BindBuffer;
PFN_PTRC_GLBUFFERDATAPROC _ptrc_glBufferData = Switch_BufferData;
PFN_PTRC_GLBUFFERSUBDATAPROC _ptrc_glBufferSubData = Switch_BufferSubData;
PFN_PTRC_GLDELETEBUFFERSPROC _ptrc_glDeleteBuffers = Switch_DeleteBuffers;
PFN_PTRC_GLDELETEQUERIESPROC _ptrc_glDeleteQueries = Switch_DeleteQueries;
PFN_PTRC_GLENDQUERYPROC _ptrc_glEndQuery = Switch_EndQuery;
PFN_PTRC_GLGENBUFFERSPROC _ptrc_glGenBuffers = Switch_GenBuffers;
PFN_PTRC_GLGENQUERIESPROC _ptrc_glGenQueries = Switch_GenQueries;
PFN_PTRC_GLGETBUFFERPARAMETERIVPROC _ptrc_glGetBufferParameteriv = Switch_GetBufferParameteriv;
PFN_PTRC_GLGETBUFFERPOINTERVPROC _ptrc_glGetBufferPointerv = Switch_GetBufferPointerv;
PFN_PTRC_GLGETBUFFERSUBDATAPROC _ptrc_glGetBufferSubData = Switch_GetBufferSubData;
PFN_PTRC_GLGETQUERYOBJECTIVPROC _ptrc_glGetQueryObjectiv = Switch_GetQueryObjectiv;
PFN_PTRC_GLGETQUERYOBJECTUIVPROC _ptrc_glGetQueryObjectuiv = Switch_GetQueryObjectuiv;
PFN_PTRC_GLGETQUERYIVPROC _ptrc_glGetQueryiv = Switch_GetQueryiv;
PFN_PTRC_GLISBUFFERPROC _ptrc_glIsBuffer = Switch_IsBuffer;
PFN_PTRC_GLISQUERYPROC _ptrc_glIsQuery = Switch_IsQuery;
PFN_PTRC_GLMAPBUFFERPROC _ptrc_glMapBuffer = Switch_MapBuffer;
PFN_PTRC_GLUNMAPBUFFERPROC _ptrc_glUnmapBuffer = Switch_UnmapBuffer;

/* Extension: 2.0*/
PFN_PTRC_GLATTACHSHADERPROC _ptrc_glAttachShader = Switch_AttachShader;
PFN_PTRC_GLBINDATTRIBLOCATIONPROC _ptrc_glBindAttribLocation = Switch_BindAttribLocation;
PFN_PTRC_GLBLENDEQUATIONSEPARATEPROC _ptrc_glBlendEquationSeparate = Switch_BlendEquationSeparate;
PFN_PTRC_GLCOMPILESHADERPROC _ptrc_glCompileShader = Switch_CompileShader;
PFN_PTRC_GLCREATEPROGRAMPROC _ptrc_glCreateProgram = Switch_CreateProgram;
PFN_PTRC_GLCREATESHADERPROC _ptrc_glCreateShader = Switch_CreateShader;
PFN_PTRC_GLDELETEPROGRAMPROC _ptrc_glDeleteProgram = Switch_DeleteProgram;
PFN_PTRC_GLDELETESHADERPROC _ptrc_glDeleteShader = Switch_DeleteShader;
PFN_PTRC_GLDETACHSHADERPROC _ptrc_glDetachShader = Switch_DetachShader;
PFN_PTRC_GLDISABLEVERTEXATTRIBARRAYPROC _ptrc_glDisableVertexAttribArray = Switch_DisableVertexAttribArray;
PFN_PTRC_GLDRAWBUFFERSPROC _ptrc_glDrawBuffers = Switch_DrawBuffers;
PFN_PTRC_GLENABLEVERTEXATTRIBARRAYPROC _ptrc_glEnableVertexAttribArray = Switch_EnableVertexAttribArray;
PFN_PTRC_GLGETACTIVEATTRIBPROC _ptrc_glGetActiveAttrib = Switch_GetActiveAttrib;
PFN_PTRC_GLGETACTIVEUNIFORMPROC _ptrc_glGetActiveUniform = Switch_GetActiveUniform;
PFN_PTRC_GLGETATTACHEDSHADERSPROC _ptrc_glGetAttachedShaders = Switch_GetAttachedShaders;
PFN_PTRC_GLGETATTRIBLOCATIONPROC _ptrc_glGetAttribLocation = Switch_GetAttribLocation;
PFN_PTRC_GLGETPROGRAMINFOLOGPROC _ptrc_glGetProgramInfoLog = Switch_GetProgramInfoLog;
PFN_PTRC_GLGETPROGRAMIVPROC _ptrc_glGetProgramiv = Switch_GetProgramiv;
PFN_PTRC_GLGETSHADERINFOLOGPROC _ptrc_glGetShaderInfoLog = Switch_GetShaderInfoLog;
PFN_PTRC_GLGETSHADERSOURCEPROC _ptrc_glGetShaderSource = Switch_GetShaderSource;
PFN_PTRC_GLGETSHADERIVPROC _ptrc_glGetShaderiv = Switch_GetShaderiv;
PFN_PTRC_GLGETUNIFORMLOCATIONPROC _ptrc_glGetUniformLocation = Switch_GetUniformLocation;
PFN_PTRC_GLGETUNIFORMFVPROC _ptrc_glGetUniformfv = Switch_GetUniformfv;
PFN_PTRC_GLGETUNIFORMIVPROC _ptrc_glGetUniformiv = Switch_GetUniformiv;
PFN_PTRC_GLGETVERTEXATTRIBPOINTERVPROC _ptrc_glGetVertexAttribPointerv = Switch_GetVertexAttribPointerv;
PFN_PTRC_GLGETVERTEXATTRIBDVPROC _ptrc_glGetVertexAttribdv = Switch_GetVertexAttribdv;
PFN_PTRC_GLGETVERTEXATTRIBFVPROC _ptrc_glGetVertexAttribfv = Switch_GetVertexAttribfv;
PFN_PTRC_GLGETVERTEXATTRIBIVPROC _ptrc_glGetVertexAttribiv = Switch_GetVertexAttribiv;
PFN_PTRC_GLISPROGRAMPROC _ptrc_glIsProgram = Switch_IsProgram;
PFN_PTRC_GLISSHADERPROC _ptrc_glIsShader = Switch_IsShader;
PFN_PTRC_GLLINKPROGRAMPROC _ptrc_glLinkProgram = Switch_LinkProgram;
PFN_PTRC_GLSHADERSOURCEPROC _ptrc_glShaderSource = Switch_ShaderSource;
PFN_PTRC_GLSTENCILFUNCSEPARATEPROC _ptrc_glStencilFuncSeparate = Switch_StencilFuncSeparate;
PFN_PTRC_GLSTENCILMASKSEPARATEPROC _ptrc_glStencilMaskSeparate = Switch_StencilMaskSeparate;
PFN_PTRC_GLSTENCILOPSEPARATEPROC _ptrc_glStencilOpSeparate = Switch_StencilOpSeparate;
PFN_PTRC_GLUNIFORM1FPROC _ptrc_glUniform1f = Switch_Uniform1f;
PFN_PTRC_GLUNIFORM1FVPROC _ptrc_glUniform1fv = Switch_Uniform1fv;
PFN_PTRC_GLUNIFORM1IPROC _ptrc_glUniform1i = Switch_Uniform1i;
PFN_PTRC_GLUNIFORM1IVPROC _ptrc_glUniform1iv = Switch_Uniform1iv;
PFN_PTRC_GLUNIFORM2FPROC _ptrc_glUniform2f = Switch_Uniform2f;
PFN_PTRC_GLUNIFORM2FVPROC _ptrc_glUniform2fv = Switch_Uniform2fv;
PFN_PTRC_GLUNIFORM2IPROC _ptrc_glUniform2i = Switch_Uniform2i;
PFN_PTRC_GLUNIFORM2IVPROC _ptrc_glUniform2iv = Switch_Uniform2iv;
PFN_PTRC_GLUNIFORM3FPROC _ptrc_glUniform3f = Switch_Uniform3f;
PFN_PTRC_GLUNIFORM3FVPROC _ptrc_glUniform3fv = Switch_Uniform3fv;
PFN_PTRC_GLUNIFORM3IPROC _ptrc_glUniform3i = Switch_Uniform3i;
PFN_PTRC_GLUNIFORM3IVPROC _ptrc_glUniform3iv = Switch_Uniform3iv;
PFN_PTRC_GLUNIFORM4FPROC _ptrc_glUniform4f = Switch_Uniform4f;
PFN_PTRC_GLUNIFORM4FVPROC _ptrc_glUniform4fv = Switch_Uniform4fv;
PFN_PTRC_GLUNIFORM4IPROC _ptrc_glUniform4i = Switch_Uniform4i;
PFN_PTRC_GLUNIFORM4IVPROC _ptrc_glUniform4iv = Switch_Uniform4iv;
PFN_PTRC_GLUNIFORMMATRIX2FVPROC _ptrc_glUniformMatrix2fv = Switch_UniformMatrix2fv;
PFN_PTRC_GLUNIFORMMATRIX3FVPROC _ptrc_glUniformMatrix3fv = Switch_UniformMatrix3fv;
PFN_PTRC_GLUNIFORMMATRIX4FVPROC _ptrc_glUniformMatrix4fv = Switch_UniformMatrix4fv;
PFN_PTRC_GLUSEPROGRAMPROC _ptrc_glUseProgram = Switch_UseProgram;
PFN_PTRC_GLVALIDATEPROGRAMPROC _ptrc_glValidateProgram = Switch_ValidateProgram;
PFN_PTRC_GLVERTEXATTRIB1DPROC _ptrc_glVertexAttrib1d = Switch_VertexAttrib1d;
PFN_PTRC_GLVERTEXATTRIB1DVPROC _ptrc_glVertexAttrib1dv = Switch_VertexAttrib1dv;
PFN_PTRC_GLVERTEXATTRIB1FPROC _ptrc_glVertexAttrib1f = Switch_VertexAttrib1f;
PFN_PTRC_GLVERTEXATTRIB1FVPROC _ptrc_glVertexAttrib1fv = Switch_VertexAttrib1fv;
PFN_PTRC_GLVERTEXATTRIB1SPROC _ptrc_glVertexAttrib1s = Switch_VertexAttrib1s;
PFN_PTRC_GLVERTEXATTRIB1SVPROC _ptrc_glVertexAttrib1sv = Switch_VertexAttrib1sv;
PFN_PTRC_GLVERTEXATTRIB2DPROC _ptrc_glVertexAttrib2d = Switch_VertexAttrib2d;
PFN_PTRC_GLVERTEXATTRIB2DVPROC _ptrc_glVertexAttrib2dv = Switch_VertexAttrib2dv;
PFN_PTRC_GLVERTEXATTRIB2FPROC _ptrc_glVertexAttrib2f = Switch_VertexAttrib2f;
PFN_PTRC_GLVERTEXATTRIB2FVPROC _ptrc_glVertexAttrib2fv = Switch_VertexAttrib2fv;
PFN_PTRC_GLVERTEXATTRIB2SPROC _ptrc_glVertexAttrib2s = Switch_VertexAttrib2s;
PFN_PTRC_GLVERTEXATTRIB2SVPROC _ptrc_glVertexAttrib2sv = Switch_VertexAttrib2sv;
PFN_PTRC_GLVERTEXATTRIB3DPROC _ptrc_glVertexAttrib3d = Switch_VertexAttrib3d;
PFN_PTRC_GLVERTEXATTRIB3DVPROC _ptrc_glVertexAttrib3dv = Switch_VertexAttrib3dv;
PFN_PTRC_GLVERTEXATTRIB3FPROC _ptrc_glVertexAttrib3f = Switch_VertexAttrib3f;
PFN_PTRC_GLVERTEXATTRIB3FVPROC _ptrc_glVertexAttrib3fv = Switch_VertexAttrib3fv;
PFN_PTRC_GLVERTEXATTRIB3SPROC _ptrc_glVertexAttrib3s = Switch_VertexAttrib3s;
PFN_PTRC_GLVERTEXATTRIB3SVPROC _ptrc_glVertexAttrib3sv = Switch_VertexAttrib3sv;
PFN_PTRC_GLVERTEXATTRIB4NBVPROC _ptrc_glVertexAttrib4Nbv = Switch_VertexAttrib4Nbv;
PFN_PTRC_GLVERTEXATTRIB4NIVPROC _ptrc_glVertexAttrib4Niv = Switch_VertexAttrib4Niv;
PFN_PTRC_GLVERTEXATTRIB4NSVPROC _ptrc_glVertexAttrib4Nsv = Switch_VertexAttrib4Nsv;
PFN_PTRC_GLVERTEXATTRIB4NUBPROC _ptrc_glVertexAttrib4Nub = Switch_VertexAttrib4Nub;
PFN_PTRC_GLVERTEXATTRIB4NUBVPROC _ptrc_glVertexAttrib4Nubv = Switch_VertexAttrib4Nubv;
PFN_PTRC_GLVERTEXATTRIB4NUIVPROC _ptrc_glVertexAttrib4Nuiv = Switch_VertexAttrib4Nuiv;
PFN_PTRC_GLVERTEXATTRIB4NUSVPROC _ptrc_glVertexAttrib4Nusv = Switch_VertexAttrib4Nusv;
PFN_PTRC_GLVERTEXATTRIB4BVPROC _ptrc_glVertexAttrib4bv = Switch_VertexAttrib4bv;
PFN_PTRC_GLVERTEXATTRIB4DPROC _ptrc_glVertexAttrib4d = Switch_VertexAttrib4d;
PFN_PTRC_GLVERTEXATTRIB4DVPROC _ptrc_glVertexAttrib4dv = Switch_VertexAttrib4dv;
PFN_PTRC_GLVERTEXATTRIB4FPROC _ptrc_glVertexAttrib4f = Switch_VertexAttrib4f;
PFN_PTRC_GLVERTEXATTRIB4FVPROC _ptrc_glVertexAttrib4fv = Switch_VertexAttrib4fv;
PFN_PTRC_GLVERTEXATTRIB4IVPROC _ptrc_glVertexAttrib4iv = Switch_VertexAttrib4iv;
PFN_PTRC_GLVERTEXATTRIB4SPROC _ptrc_glVertexAttrib4s = Switch_VertexAttrib4s;
PFN_PTRC_GLVERTEXATTRIB4SVPROC _ptrc_glVertexAttrib4sv = Switch_VertexAttrib4sv;
PFN_PTRC_GLVERTEXATTRIB4UBVPROC _ptrc_glVertexAttrib4ubv = Switch_VertexAttrib4ubv;
PFN_PTRC_GLVERTEXATTRIB4UIVPROC _ptrc_glVertexAttrib4uiv = Switch_VertexAttrib4uiv;
PFN_PTRC_GLVERTEXATTRIB4USVPROC _ptrc_glVertexAttrib4usv = Switch_VertexAttrib4usv;
PFN_PTRC_GLVERTEXATTRIBPOINTERPROC _ptrc_glVertexAttribPointer = Switch_VertexAttribPointer;

/* Extension: 2.1*/
PFN_PTRC_GLUNIFORMMATRIX2X3FVPROC _ptrc_glUniformMatrix2x3fv = Switch_UniformMatrix2x3fv;
PFN_PTRC_GLUNIFORMMATRIX2X4FVPROC _ptrc_glUniformMatrix2x4fv = Switch_UniformMatrix2x4fv;
PFN_PTRC_GLUNIFORMMATRIX3X2FVPROC _ptrc_glUniformMatrix3x2fv = Switch_UniformMatrix3x2fv;
PFN_PTRC_GLUNIFORMMATRIX3X4FVPROC _ptrc_glUniformMatrix3x4fv = Switch_UniformMatrix3x4fv;
PFN_PTRC_GLUNIFORMMATRIX4X2FVPROC _ptrc_glUniformMatrix4x2fv = Switch_UniformMatrix4x2fv;
PFN_PTRC_GLUNIFORMMATRIX4X3FVPROC _ptrc_glUniformMatrix4x3fv = Switch_UniformMatrix4x3fv;

/* Extension: 3.0*/
PFN_PTRC_GLBEGINCONDITIONALRENDERPROC _ptrc_glBeginConditionalRender = Switch_BeginConditionalRender;
PFN_PTRC_GLBEGINTRANSFORMFEEDBACKPROC _ptrc_glBeginTransformFeedback = Switch_BeginTransformFeedback;
PFN_PTRC_GLBINDBUFFERBASEPROC _ptrc_glBindBufferBase = Switch_BindBufferBase;
PFN_PTRC_GLBINDBUFFERRANGEPROC _ptrc_glBindBufferRange = Switch_BindBufferRange;
PFN_PTRC_GLBINDFRAGDATALOCATIONPROC _ptrc_glBindFragDataLocation = Switch_BindFragDataLocation;
PFN_PTRC_GLBINDFRAMEBUFFERPROC _ptrc_glBindFramebuffer = Switch_BindFramebuffer;
PFN_PTRC_GLBINDRENDERBUFFERPROC _ptrc_glBindRenderbuffer = Switch_BindRenderbuffer;
PFN_PTRC_GLBINDVERTEXARRAYPROC _ptrc_glBindVertexArray = Switch_BindVertexArray;
PFN_PTRC_GLBLITFRAMEBUFFERPROC _ptrc_glBlitFramebuffer = Switch_BlitFramebuffer;
PFN_PTRC_GLCHECKFRAMEBUFFERSTATUSPROC _ptrc_glCheckFramebufferStatus = Switch_CheckFramebufferStatus;
PFN_PTRC_GLCLAMPCOLORPROC _ptrc_glClampColor = Switch_ClampColor;
PFN_PTRC_GLCLEARBUFFERFIPROC _ptrc_glClearBufferfi = Switch_ClearBufferfi;
PFN_PTRC_GLCLEARBUFFERFVPROC _ptrc_glClearBufferfv = Switch_ClearBufferfv;
PFN_PTRC_GLCLEARBUFFERIVPROC _ptrc_glClearBufferiv = Switch_ClearBufferiv;
PFN_PTRC_GLCLEARBUFFERUIVPROC _ptrc_glClearBufferuiv = Switch_ClearBufferuiv;
PFN_PTRC_GLCOLORMASKIPROC _ptrc_glColorMaski = Switch_ColorMaski;
PFN_PTRC_GLDELETEFRAMEBUFFERSPROC _ptrc_glDeleteFramebuffers = Switch_DeleteFramebuffers;
PFN_PTRC_GLDELETERENDERBUFFERSPROC _ptrc_glDeleteRenderbuffers = Switch_DeleteRenderbuffers;
PFN_PTRC_GLDELETEVERTEXARRAYSPROC _ptrc_glDeleteVertexArrays = Switch_DeleteVertexArrays;
PFN_PTRC_GLDISABLEIPROC _ptrc_glDisablei = Switch_Disablei;
PFN_PTRC_GLENABLEIPROC _ptrc_glEnablei = Switch_Enablei;
PFN_PTRC_GLENDCONDITIONALRENDERPROC _ptrc_glEndConditionalRender = Switch_EndConditionalRender;
PFN_PTRC_GLENDTRANSFORMFEEDBACKPROC _ptrc_glEndTransformFeedback = Switch_EndTransformFeedback;
PFN_PTRC_GLFLUSHMAPPEDBUFFERRANGEPROC _ptrc_glFlushMappedBufferRange = Switch_FlushMappedBufferRange;
PFN_PTRC_GLFRAMEBUFFERRENDERBUFFERPROC _ptrc_glFramebufferRenderbuffer = Switch_FramebufferRenderbuffer;
PFN_PTRC_GLFRAMEBUFFERTEXTURE1DPROC _ptrc_glFramebufferTexture1D = Switch_FramebufferTexture1D;
PFN_PTRC_GLFRAMEBUFFERTEXTURE2DPROC _ptrc_glFramebufferTexture2D = Switch_FramebufferTexture2D;
PFN_PTRC_GLFRAMEBUFFERTEXTURE3DPROC _ptrc_glFramebufferTexture3D = Switch_FramebufferTexture3D;
PFN_PTRC_GLFRAMEBUFFERTEXTURELAYERPROC _ptrc_glFramebufferTextureLayer = Switch_FramebufferTextureLayer;
PFN_PTRC_GLGENFRAMEBUFFERSPROC _ptrc_glGenFramebuffers = Switch_GenFramebuffers;
PFN_PTRC_GLGENRENDERBUFFERSPROC _ptrc_glGenRenderbuffers = Switch_GenRenderbuffers;
PFN_PTRC_GLGENVERTEXARRAYSPROC _ptrc_glGenVertexArrays = Switch_GenVertexArrays;
PFN_PTRC_GLGENERATEMIPMAPPROC _ptrc_glGenerateMipmap = Switch_GenerateMipmap;
PFN_PTRC_GLGETBOOLEANI_VPROC _ptrc_glGetBooleani_v = Switch_GetBooleani_v;
PFN_PTRC_GLGETFRAGDATALOCATIONPROC _ptrc_glGetFragDataLocation = Switch_GetFragDataLocation;
PFN_PTRC_GLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC _ptrc_glGetFramebufferAttachmentParameteriv = Switch_GetFramebufferAttachmentParameteriv;
PFN_PTRC_GLGETINTEGERI_VPROC _ptrc_glGetIntegeri_v = Switch_GetIntegeri_v;
PFN_PTRC_GLGETRENDERBUFFERPARAMETERIVPROC _ptrc_glGetRenderbufferParameteriv = Switch_GetRenderbufferParameteriv;
PFN_PTRC_GLGETSTRINGIPROC _ptrc_glGetStringi = Switch_GetStringi;
PFN_PTRC_GLGETTEXPARAMETERIIVPROC _ptrc_glGetTexParameterIiv = Switch_GetTexParameterIiv;
PFN_PTRC_GLGETTEXPARAMETERIUIVPROC _ptrc_glGetTexParameterIuiv = Switch_GetTexParameterIuiv;
PFN_PTRC_GLGETTRANSFORMFEEDBACKVARYINGPROC _ptrc_glGetTransformFeedbackVarying = Switch_GetTransformFeedbackVarying;
PFN_PTRC_GLGETUNIFORMUIVPROC _ptrc_glGetUniformuiv = Switch_GetUniformuiv;
PFN_PTRC_GLGETVERTEXATTRIBIIVPROC _ptrc_glGetVertexAttribIiv = Switch_GetVertexAttribIiv;
PFN_PTRC_GLGETVERTEXATTRIBIUIVPROC _ptrc_glGetVertexAttribIuiv = Switch_GetVertexAttribIuiv;
PFN_PTRC_GLISENABLEDIPROC _ptrc_glIsEnabledi = Switch_IsEnabledi;
PFN_PTRC_GLISFRAMEBUFFERPROC _ptrc_glIsFramebuffer = Switch_IsFramebuffer;
PFN_PTRC_GLISRENDERBUFFERPROC _ptrc_glIsRenderbuffer = Switch_IsRenderbuffer;
PFN_PTRC_GLISVERTEXARRAYPROC _ptrc_glIsVertexArray = Switch_IsVertexArray;
PFN_PTRC_GLMAPBUFFERRANGEPROC _ptrc_glMapBufferRange = Switch_MapBufferRange;
PFN_PTRC_GLRENDERBUFFERSTORAGEPROC _ptrc_glRenderbufferStorage = Switch_RenderbufferStorage;
PFN_PTRC_GLRENDERBUFFERSTORAGEMULTISAMPLEPROC _ptrc_glRenderbufferStorageMultisample = Switch_RenderbufferStorageMultisample;
PFN_PTRC_GLTEXPARAMETERIIVPROC _ptrc_glTexParameterIiv = Switch_TexParameterIiv;
PFN_PTRC_GLTEXPARAMETERIUIVPROC _ptrc_glTexParameterIuiv = Switch_TexParameterIuiv;
PFN_PTRC_GLTRANSFORMFEEDBACKVARYINGSPROC _ptrc_glTransformFeedbackVaryings = Switch_TransformFeedbackVaryings;
PFN_PTRC_GLUNIFORM1UIPROC _ptrc_glUniform1ui = Switch_Uniform1ui;
PFN_PTRC_GLUNIFORM1UIVPROC _ptrc_glUniform1uiv = Switch_Uniform1uiv;
PFN_PTRC_GLUNIFORM2UIPROC _ptrc_glUniform2ui = Switch_Uniform2ui;
PFN_PTRC_GLUNIFORM2UIVPROC _ptrc_glUniform2uiv = Switch_Uniform2uiv;
PFN_PTRC_GLUNIFORM3UIPROC _ptrc_glUniform3ui = Switch_Uniform3ui;
PFN_PTRC_GLUNIFORM3UIVPROC _ptrc_glUniform3uiv = Switch_Uniform3uiv;
PFN_PTRC_GLUNIFORM4UIPROC _ptrc_glUniform4ui = Switch_Uniform4ui;
PFN_PTRC_GLUNIFORM4UIVPROC _ptrc_glUniform4uiv = Switch_Uniform4uiv;
PFN_PTRC_GLVERTEXATTRIBI1IPROC _ptrc_glVertexAttribI1i = Switch_VertexAttribI1i;
PFN_PTRC_GLVERTEXATTRIBI1IVPROC _ptrc_glVertexAttribI1iv = Switch_VertexAttribI1iv;
PFN_PTRC_GLVERTEXATTRIBI1UIPROC _ptrc_glVertexAttribI1ui = Switch_VertexAttribI1ui;
PFN_PTRC_GLVERTEXATTRIBI1UIVPROC _ptrc_glVertexAttribI1uiv = Switch_VertexAttribI1uiv;
PFN_PTRC_GLVERTEXATTRIBI2IPROC _ptrc_glVertexAttribI2i = Switch_VertexAttribI2i;
PFN_PTRC_GLVERTEXATTRIBI2IVPROC _ptrc_glVertexAttribI2iv = Switch_VertexAttribI2iv;
PFN_PTRC_GLVERTEXATTRIBI2UIPROC _ptrc_glVertexAttribI2ui = Switch_VertexAttribI2ui;
PFN_PTRC_GLVERTEXATTRIBI2UIVPROC _ptrc_glVertexAttribI2uiv = Switch_VertexAttribI2uiv;
PFN_PTRC_GLVERTEXATTRIBI3IPROC _ptrc_glVertexAttribI3i = Switch_VertexAttribI3i;
PFN_PTRC_GLVERTEXATTRIBI3IVPROC _ptrc_glVertexAttribI3iv = Switch_VertexAttribI3iv;
PFN_PTRC_GLVERTEXATTRIBI3UIPROC _ptrc_glVertexAttribI3ui = Switch_VertexAttribI3ui;
PFN_PTRC_GLVERTEXATTRIBI3UIVPROC _ptrc_glVertexAttribI3uiv = Switch_VertexAttribI3uiv;
PFN_PTRC_GLVERTEXATTRIBI4BVPROC _ptrc_glVertexAttribI4bv = Switch_VertexAttribI4bv;
PFN_PTRC_GLVERTEXATTRIBI4IPROC _ptrc_glVertexAttribI4i = Switch_VertexAttribI4i;
PFN_PTRC_GLVERTEXATTRIBI4IVPROC _ptrc_glVertexAttribI4iv = Switch_VertexAttribI4iv;
PFN_PTRC_GLVERTEXATTRIBI4SVPROC _ptrc_glVertexAttribI4sv = Switch_VertexAttribI4sv;
PFN_PTRC_GLVERTEXATTRIBI4UBVPROC _ptrc_glVertexAttribI4ubv = Switch_VertexAttribI4ubv;
PFN_PTRC_GLVERTEXATTRIBI4UIPROC _ptrc_glVertexAttribI4ui = Switch_VertexAttribI4ui;
PFN_PTRC_GLVERTEXATTRIBI4UIVPROC _ptrc_glVertexAttribI4uiv = Switch_VertexAttribI4uiv;
PFN_PTRC_GLVERTEXATTRIBI4USVPROC _ptrc_glVertexAttribI4usv = Switch_VertexAttribI4usv;
PFN_PTRC_GLVERTEXATTRIBIPOINTERPROC _ptrc_glVertexAttribIPointer = Switch_VertexAttribIPointer;

/* Extension: 3.1*/
PFN_PTRC_GLCOPYBUFFERSUBDATAPROC _ptrc_glCopyBufferSubData = Switch_CopyBufferSubData;
PFN_PTRC_GLDRAWARRAYSINSTANCEDPROC _ptrc_glDrawArraysInstanced = Switch_DrawArraysInstanced;
PFN_PTRC_GLDRAWELEMENTSINSTANCEDPROC _ptrc_glDrawElementsInstanced = Switch_DrawElementsInstanced;
PFN_PTRC_GLGETACTIVEUNIFORMBLOCKNAMEPROC _ptrc_glGetActiveUniformBlockName = Switch_GetActiveUniformBlockName;
PFN_PTRC_GLGETACTIVEUNIFORMBLOCKIVPROC _ptrc_glGetActiveUniformBlockiv = Switch_GetActiveUniformBlockiv;
PFN_PTRC_GLGETACTIVEUNIFORMNAMEPROC _ptrc_glGetActiveUniformName = Switch_GetActiveUniformName;
PFN_PTRC_GLGETACTIVEUNIFORMSIVPROC _ptrc_glGetActiveUniformsiv = Switch_GetActiveUniformsiv;
PFN_PTRC_GLGETUNIFORMBLOCKINDEXPROC _ptrc_glGetUniformBlockIndex = Switch_GetUniformBlockIndex;
PFN_PTRC_GLGETUNIFORMINDICESPROC _ptrc_glGetUniformIndices = Switch_GetUniformIndices;
PFN_PTRC_GLPRIMITIVERESTARTINDEXPROC _ptrc_glPrimitiveRestartIndex = Switch_PrimitiveRestartIndex;
PFN_PTRC_GLTEXBUFFERPROC _ptrc_glTexBuffer = Switch_TexBuffer;
PFN_PTRC_GLUNIFORMBLOCKBINDINGPROC _ptrc_glUniformBlockBinding = Switch_UniformBlockBinding;

/* Extension: 3.2*/
PFN_PTRC_GLCLIENTWAITSYNCPROC _ptrc_glClientWaitSync = Switch_ClientWaitSync;
PFN_PTRC_GLDELETESYNCPROC _ptrc_glDeleteSync = Switch_DeleteSync;
PFN_PTRC_GLDRAWELEMENTSBASEVERTEXPROC _ptrc_glDrawElementsBaseVertex = Switch_DrawElementsBaseVertex;
PFN_PTRC_GLDRAWELEMENTSINSTANCEDBASEVERTEXPROC _ptrc_glDrawElementsInstancedBaseVertex = Switch_DrawElementsInstancedBaseVertex;
PFN_PTRC_GLDRAWRANGEELEMENTSBASEVERTEXPROC _ptrc_glDrawRangeElementsBaseVertex = Switch_DrawRangeElementsBaseVertex;
PFN_PTRC_GLFENCESYNCPROC _ptrc_glFenceSync = Switch_FenceSync;
PFN_PTRC_GLFRAMEBUFFERTEXTUREPROC _ptrc_glFramebufferTexture = Switch_FramebufferTexture;
PFN_PTRC_GLGETBUFFERPARAMETERI64VPROC _ptrc_glGetBufferParameteri64v = Switch_GetBufferParameteri64v;
PFN_PTRC_GLGETINTEGER64I_VPROC _ptrc_glGetInteger64i_v = Switch_GetInteger64i_v;
PFN_PTRC_GLGETINTEGER64VPROC _ptrc_glGetInteger64v = Switch_GetInteger64v;
PFN_PTRC_GLGETMULTISAMPLEFVPROC _ptrc_glGetMultisamplefv = Switch_GetMultisamplefv;
PFN_PTRC_GLGETSYNCIVPROC _ptrc_glGetSynciv = Switch_GetSynciv;
PFN_PTRC_GLISSYNCPROC _ptrc_glIsSync = Switch_IsSync;
PFN_PTRC_GLMULTIDRAWELEMENTSBASEVERTEXPROC _ptrc_glMultiDrawElementsBaseVertex = Switch_MultiDrawElementsBaseVertex;
PFN_PTRC_GLPROVOKINGVERTEXPROC _ptrc_glProvokingVertex = Switch_ProvokingVertex;
PFN_PTRC_GLSAMPLEMASKIPROC _ptrc_glSampleMaski = Switch_SampleMaski;
PFN_PTRC_GLTEXIMAGE2DMULTISAMPLEPROC _ptrc_glTexImage2DMultisample = Switch_TexImage2DMultisample;
PFN_PTRC_GLTEXIMAGE3DMULTISAMPLEPROC _ptrc_glTexImage3DMultisample = Switch_TexImage3DMultisample;
PFN_PTRC_GLWAITSYNCPROC _ptrc_glWaitSync = Switch_WaitSync;

/* Extension: 3.3*/
PFN_PTRC_GLBINDFRAGDATALOCATIONINDEXEDPROC _ptrc_glBindFragDataLocationIndexed = Switch_BindFragDataLocationIndexed;
PFN_PTRC_GLBINDSAMPLERPROC _ptrc_glBindSampler = Switch_BindSampler;
PFN_PTRC_GLDELETESAMPLERSPROC _ptrc_glDeleteSamplers = Switch_DeleteSamplers;
PFN_PTRC_GLGENSAMPLERSPROC _ptrc_glGenSamplers = Switch_GenSamplers;
PFN_PTRC_GLGETFRAGDATAINDEXPROC _ptrc_glGetFragDataIndex = Switch_GetFragDataIndex;
PFN_PTRC_GLGETQUERYOBJECTI64VPROC _ptrc_glGetQueryObjecti64v = Switch_GetQueryObjecti64v;
PFN_PTRC_GLGETQUERYOBJECTUI64VPROC _ptrc_glGetQueryObjectui64v = Switch_GetQueryObjectui64v;
PFN_PTRC_GLGETSAMPLERPARAMETERIIVPROC _ptrc_glGetSamplerParameterIiv = Switch_GetSamplerParameterIiv;
PFN_PTRC_GLGETSAMPLERPARAMETERIUIVPROC _ptrc_glGetSamplerParameterIuiv = Switch_GetSamplerParameterIuiv;
PFN_PTRC_GLGETSAMPLERPARAMETERFVPROC _ptrc_glGetSamplerParameterfv = Switch_GetSamplerParameterfv;
PFN_PTRC_GLGETSAMPLERPARAMETERIVPROC _ptrc_glGetSamplerParameteriv = Switch_GetSamplerParameteriv;
PFN_PTRC_GLISSAMPLERPROC _ptrc_glIsSampler = Switch_IsSampler;
PFN_PTRC_GLQUERYCOUNTERPROC _ptrc_glQueryCounter = Switch_QueryCounter;
PFN_PTRC_GLSAMPLERPARAMETERIIVPROC _ptrc_glSamplerParameterIiv = Switch_SamplerParameterIiv;
PFN_PTRC_GLSAMPLERPARAMETERIUIVPROC _ptrc_glSamplerParameterIuiv = Switch_SamplerParameterIuiv;
PFN_PTRC_GLSAMPLERPARAMETERFPROC _ptrc_glSamplerParameterf = Switch_SamplerParameterf;
PFN_PTRC_GLSAMPLERPARAMETERFVPROC _ptrc_glSamplerParameterfv = Switch_SamplerParameterfv;
PFN_PTRC_GLSAMPLERPARAMETERIPROC _ptrc_glSamplerParameteri = Switch_SamplerParameteri;
PFN_PTRC_GLSAMPLERPARAMETERIVPROC _ptrc_glSamplerParameteriv = Switch_SamplerParameteriv;
PFN_PTRC_GLVERTEXATTRIBDIVISORPROC _ptrc_glVertexAttribDivisor = Switch_VertexAttribDivisor;
PFN_PTRC_GLVERTEXATTRIBP1UIPROC _ptrc_glVertexAttribP1ui = Switch_VertexAttribP1ui;
PFN_PTRC_GLVERTEXATTRIBP1UIVPROC _ptrc_glVertexAttribP1uiv = Switch_VertexAttribP1uiv;
PFN_PTRC_GLVERTEXATTRIBP2UIPROC _ptrc_glVertexAttribP2ui = Switch_VertexAttribP2ui;
PFN_PTRC_GLVERTEXATTRIBP2UIVPROC _ptrc_glVertexAttribP2uiv = Switch_VertexAttribP2uiv;
PFN_PTRC_GLVERTEXATTRIBP3UIPROC _ptrc_glVertexAttribP3ui = Switch_VertexAttribP3ui;
PFN_PTRC_GLVERTEXATTRIBP3UIVPROC _ptrc_glVertexAttribP3uiv = Switch_VertexAttribP3uiv;
PFN_PTRC_GLVERTEXATTRIBP4UIPROC _ptrc_glVertexAttribP4ui = Switch_VertexAttribP4ui;
PFN_PTRC_GLVERTEXATTRIBP4UIVPROC _ptrc_glVertexAttribP4uiv = Switch_VertexAttribP4uiv;

/* Extension: 4.0*/
PFN_PTRC_GLBEGINQUERYINDEXEDPROC _ptrc_glBeginQueryIndexed = Switch_BeginQueryIndexed;
PFN_PTRC_GLBINDTRANSFORMFEEDBACKPROC _ptrc_glBindTransformFeedback = Switch_BindTransformFeedback;
PFN_PTRC_GLBLENDEQUATIONSEPARATEIPROC _ptrc_glBlendEquationSeparatei = Switch_BlendEquationSeparatei;
PFN_PTRC_GLBLENDEQUATIONIPROC _ptrc_glBlendEquationi = Switch_BlendEquationi;
PFN_PTRC_GLBLENDFUNCSEPARATEIPROC _ptrc_glBlendFuncSeparatei = Switch_BlendFuncSeparatei;
PFN_PTRC_GLBLENDFUNCIPROC _ptrc_glBlendFunci = Switch_BlendFunci;
PFN_PTRC_GLDELETETRANSFORMFEEDBACKSPROC _ptrc_glDeleteTransformFeedbacks = Switch_DeleteTransformFeedbacks;
PFN_PTRC_GLDRAWARRAYSINDIRECTPROC _ptrc_glDrawArraysIndirect = Switch_DrawArraysIndirect;
PFN_PTRC_GLDRAWELEMENTSINDIRECTPROC _ptrc_glDrawElementsIndirect = Switch_DrawElementsIndirect;
PFN_PTRC_GLDRAWTRANSFORMFEEDBACKPROC _ptrc_glDrawTransformFeedback = Switch_DrawTransformFeedback;
PFN_PTRC_GLDRAWTRANSFORMFEEDBACKSTREAMPROC _ptrc_glDrawTransformFeedbackStream = Switch_DrawTransformFeedbackStream;
PFN_PTRC_GLENDQUERYINDEXEDPROC _ptrc_glEndQueryIndexed = Switch_EndQueryIndexed;
PFN_PTRC_GLGENTRANSFORMFEEDBACKSPROC _ptrc_glGenTransformFeedbacks = Switch_GenTransformFeedbacks;
PFN_PTRC_GLGETACTIVESUBROUTINENAMEPROC _ptrc_glGetActiveSubroutineName = Switch_GetActiveSubroutineName;
PFN_PTRC_GLGETACTIVESUBROUTINEUNIFORMNAMEPROC _ptrc_glGetActiveSubroutineUniformName = Switch_GetActiveSubroutineUniformName;
PFN_PTRC_GLGETACTIVESUBROUTINEUNIFORMIVPROC _ptrc_glGetActiveSubroutineUniformiv = Switch_GetActiveSubroutineUniformiv;
PFN_PTRC_GLGETPROGRAMSTAGEIVPROC _ptrc_glGetProgramStageiv = Switch_GetProgramStageiv;
PFN_PTRC_GLGETQUERYINDEXEDIVPROC _ptrc_glGetQueryIndexediv = Switch_GetQueryIndexediv;
PFN_PTRC_GLGETSUBROUTINEINDEXPROC _ptrc_glGetSubroutineIndex = Switch_GetSubroutineIndex;
PFN_PTRC_GLGETSUBROUTINEUNIFORMLOCATIONPROC _ptrc_glGetSubroutineUniformLocation = Switch_GetSubroutineUniformLocation;
PFN_PTRC_GLGETUNIFORMSUBROUTINEUIVPROC _ptrc_glGetUniformSubroutineuiv = Switch_GetUniformSubroutineuiv;
PFN_PTRC_GLGETUNIFORMDVPROC _ptrc_glGetUniformdv = Switch_GetUniformdv;
PFN_PTRC_GLISTRANSFORMFEEDBACKPROC _ptrc_glIsTransformFeedback = Switch_IsTransformFeedback;
PFN_PTRC_GLMINSAMPLESHADINGPROC _ptrc_glMinSampleShading = Switch_MinSampleShading;
PFN_PTRC_GLPATCHPARAMETERFVPROC _ptrc_glPatchParameterfv = Switch_PatchParameterfv;
PFN_PTRC_GLPATCHPARAMETERIPROC _ptrc_glPatchParameteri = Switch_PatchParameteri;
PFN_PTRC_GLPAUSETRANSFORMFEEDBACKPROC _ptrc_glPauseTransformFeedback = Switch_PauseTransformFeedback;
PFN_PTRC_GLRESUMETRANSFORMFEEDBACKPROC _ptrc_glResumeTransformFeedback = Switch_ResumeTransformFeedback;
PFN_PTRC_GLUNIFORM1DPROC _ptrc_glUniform1d = Switch_Uniform1d;
PFN_PTRC_GLUNIFORM1DVPROC _ptrc_glUniform1dv = Switch_Uniform1dv;
PFN_PTRC_GLUNIFORM2DPROC _ptrc_glUniform2d = Switch_Uniform2d;
PFN_PTRC_GLUNIFORM2DVPROC _ptrc_glUniform2dv = Switch_Uniform2dv;
PFN_PTRC_GLUNIFORM3DPROC _ptrc_glUniform3d = Switch_Uniform3d;
PFN_PTRC_GLUNIFORM3DVPROC _ptrc_glUniform3dv = Switch_Uniform3dv;
PFN_PTRC_GLUNIFORM4DPROC _ptrc_glUniform4d = Switch_Uniform4d;
PFN_PTRC_GLUNIFORM4DVPROC _ptrc_glUniform4dv = Switch_Uniform4dv;
PFN_PTRC_GLUNIFORMMATRIX2DVPROC _ptrc_glUniformMatrix2dv = Switch_UniformMatrix2dv;
PFN_PTRC_GLUNIFORMMATRIX2X3DVPROC _ptrc_glUniformMatrix2x3dv = Switch_UniformMatrix2x3dv;
PFN_PTRC_GLUNIFORMMATRIX2X4DVPROC _ptrc_glUniformMatrix2x4dv = Switch_UniformMatrix2x4dv;
PFN_PTRC_GLUNIFORMMATRIX3DVPROC _ptrc_glUniformMatrix3dv = Switch_UniformMatrix3dv;
PFN_PTRC_GLUNIFORMMATRIX3X2DVPROC _ptrc_glUniformMatrix3x2dv = Switch_UniformMatrix3x2dv;
PFN_PTRC_GLUNIFORMMATRIX3X4DVPROC _ptrc_glUniformMatrix3x4dv = Switch_UniformMatrix3x4dv;
PFN_PTRC_GLUNIFORMMATRIX4DVPROC _ptrc_glUniformMatrix4dv = Switch_UniformMatrix4dv;
PFN_PTRC_GLUNIFORMMATRIX4X2DVPROC _ptrc_glUniformMatrix4x2dv = Switch_UniformMatrix4x2dv;
PFN_PTRC_GLUNIFORMMATRIX4X3DVPROC _ptrc_glUniformMatrix4x3dv = Switch_UniformMatrix4x3dv;
PFN_PTRC_GLUNIFORMSUBROUTINESUIVPROC _ptrc_glUniformSubroutinesuiv = Switch_UniformSubroutinesuiv;

/* Extension: 4.1*/
PFN_PTRC_GLACTIVESHADERPROGRAMPROC _ptrc_glActiveShaderProgram = Switch_ActiveShaderProgram;
PFN_PTRC_GLBINDPROGRAMPIPELINEPROC _ptrc_glBindProgramPipeline = Switch_BindProgramPipeline;
PFN_PTRC_GLCLEARDEPTHFPROC _ptrc_glClearDepthf = Switch_ClearDepthf;
PFN_PTRC_GLCREATESHADERPROGRAMVPROC _ptrc_glCreateShaderProgramv = Switch_CreateShaderProgramv;
PFN_PTRC_GLDELETEPROGRAMPIPELINESPROC _ptrc_glDeleteProgramPipelines = Switch_DeleteProgramPipelines;
PFN_PTRC_GLDEPTHRANGEARRAYVPROC _ptrc_glDepthRangeArrayv = Switch_DepthRangeArrayv;
PFN_PTRC_GLDEPTHRANGEINDEXEDPROC _ptrc_glDepthRangeIndexed = Switch_DepthRangeIndexed;
PFN_PTRC_GLDEPTHRANGEFPROC _ptrc_glDepthRangef = Switch_DepthRangef;
PFN_PTRC_GLGENPROGRAMPIPELINESPROC _ptrc_glGenProgramPipelines = Switch_GenProgramPipelines;
PFN_PTRC_GLGETDOUBLEI_VPROC _ptrc_glGetDoublei_v = Switch_GetDoublei_v;
PFN_PTRC_GLGETFLOATI_VPROC _ptrc_glGetFloati_v = Switch_GetFloati_v;
PFN_PTRC_GLGETPROGRAMBINARYPROC _ptrc_glGetProgramBinary = Switch_GetProgramBinary;
PFN_PTRC_GLGETPROGRAMPIPELINEINFOLOGPROC _ptrc_glGetProgramPipelineInfoLog = Switch_GetProgramPipelineInfoLog;
PFN_PTRC_GLGETPROGRAMPIPELINEIVPROC _ptrc_glGetProgramPipelineiv = Switch_GetProgramPipelineiv;
PFN_PTRC_GLGETSHADERPRECISIONFORMATPROC _ptrc_glGetShaderPrecisionFormat = Switch_GetShaderPrecisionFormat;
PFN_PTRC_GLGETVERTEXATTRIBLDVPROC _ptrc_glGetVertexAttribLdv = Switch_GetVertexAttribLdv;
PFN_PTRC_GLISPROGRAMPIPELINEPROC _ptrc_glIsProgramPipeline = Switch_IsProgramPipeline;
PFN_PTRC_GLPROGRAMBINARYPROC _ptrc_glProgramBinary = Switch_ProgramBinary;
PFN_PTRC_GLPROGRAMPARAMETERIPROC _ptrc_glProgramParameteri = Switch_ProgramParameteri;
PFN_PTRC_GLPROGRAMUNIFORM1DPROC _ptrc_glProgramUniform1d = Switch_ProgramUniform1d;
PFN_PTRC_GLPROGRAMUNIFORM1DVPROC _ptrc_glProgramUniform1dv = Switch_ProgramUniform1dv;
PFN_PTRC_GLPROGRAMUNIFORM1FPROC _ptrc_glProgramUniform1f = Switch_ProgramUniform1f;
PFN_PTRC_GLPROGRAMUNIFORM1FVPROC _ptrc_glProgramUniform1fv = Switch_ProgramUniform1fv;
PFN_PTRC_GLPROGRAMUNIFORM1IPROC _ptrc_glProgramUniform1i = Switch_ProgramUniform1i;
PFN_PTRC_GLPROGRAMUNIFORM1IVPROC _ptrc_glProgramUniform1iv = Switch_ProgramUniform1iv;
PFN_PTRC_GLPROGRAMUNIFORM1UIPROC _ptrc_glProgramUniform1ui = Switch_ProgramUniform1ui;
PFN_PTRC_GLPROGRAMUNIFORM1UIVPROC _ptrc_glProgramUniform1uiv = Switch_ProgramUniform1uiv;
PFN_PTRC_GLPROGRAMUNIFORM2DPROC _ptrc_glProgramUniform2d = Switch_ProgramUniform2d;
PFN_PTRC_GLPROGRAMUNIFORM2DVPROC _ptrc_glProgramUniform2dv = Switch_ProgramUniform2dv;
PFN_PTRC_GLPROGRAMUNIFORM2FPROC _ptrc_glProgramUniform2f = Switch_ProgramUniform2f;
PFN_PTRC_GLPROGRAMUNIFORM2FVPROC _ptrc_glProgramUniform2fv = Switch_ProgramUniform2fv;
PFN_PTRC_GLPROGRAMUNIFORM2IPROC _ptrc_glProgramUniform2i = Switch_ProgramUniform2i;
PFN_PTRC_GLPROGRAMUNIFORM2IVPROC _ptrc_glProgramUniform2iv = Switch_ProgramUniform2iv;
PFN_PTRC_GLPROGRAMUNIFORM2UIPROC _ptrc_glProgramUniform2ui = Switch_ProgramUniform2ui;
PFN_PTRC_GLPROGRAMUNIFORM2UIVPROC _ptrc_glProgramUniform2uiv = Switch_ProgramUniform2uiv;
PFN_PTRC_GLPROGRAMUNIFORM3DPROC _ptrc_glProgramUniform3d = Switch_ProgramUniform3d;
PFN_PTRC_GLPROGRAMUNIFORM3DVPROC _ptrc_glProgramUniform3dv = Switch_ProgramUniform3dv;
PFN_PTRC_GLPROGRAMUNIFORM3FPROC _ptrc_glProgramUniform3f = Switch_ProgramUniform3f;
PFN_PTRC_GLPROGRAMUNIFORM3FVPROC _ptrc_glProgramUniform3fv = Switch_ProgramUniform3fv;
PFN_PTRC_GLPROGRAMUNIFORM3IPROC _ptrc_glProgramUniform3i = Switch_ProgramUniform3i;
PFN_PTRC_GLPROGRAMUNIFORM3IVPROC _ptrc_glProgramUniform3iv = Switch_ProgramUniform3iv;
PFN_PTRC_GLPROGRAMUNIFORM3UIPROC _ptrc_glProgramUniform3ui = Switch_ProgramUniform3ui;
PFN_PTRC_GLPROGRAMUNIFORM3UIVPROC _ptrc_glProgramUniform3uiv = Switch_ProgramUniform3uiv;
PFN_PTRC_GLPROGRAMUNIFORM4DPROC _ptrc_glProgramUniform4d = Switch_ProgramUniform4d;
PFN_PTRC_GLPROGRAMUNIFORM4DVPROC _ptrc_glProgramUniform4dv = Switch_ProgramUniform4dv;
PFN_PTRC_GLPROGRAMUNIFORM4FPROC _ptrc_glProgramUniform4f = Switch_ProgramUniform4f;
PFN_PTRC_GLPROGRAMUNIFORM4FVPROC _ptrc_glProgramUniform4fv = Switch_ProgramUniform4fv;
PFN_PTRC_GLPROGRAMUNIFORM4IPROC _ptrc_glProgramUniform4i = Switch_ProgramUniform4i;
PFN_PTRC_GLPROGRAMUNIFORM4IVPROC _ptrc_glProgramUniform4iv = Switch_ProgramUniform4iv;
PFN_PTRC_GLPROGRAMUNIFORM4UIPROC _ptrc_glProgramUniform4ui = Switch_ProgramUniform4ui;
PFN_PTRC_GLPROGRAMUNIFORM4UIVPROC _ptrc_glProgramUniform4uiv = Switch_ProgramUniform4uiv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX2DVPROC _ptrc_glProgramUniformMatrix2dv = Switch_ProgramUniformMatrix2dv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX2FVPROC _ptrc_glProgramUniformMatrix2fv = Switch_ProgramUniformMatrix2fv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX2X3DVPROC _ptrc_glProgramUniformMatrix2x3dv = Switch_ProgramUniformMatrix2x3dv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX2X3FVPROC _ptrc_glProgramUniformMatrix2x3fv = Switch_ProgramUniformMatrix2x3fv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX2X4DVPROC _ptrc_glProgramUniformMatrix2x4dv = Switch_ProgramUniformMatrix2x4dv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX2X4FVPROC _ptrc_glProgramUniformMatrix2x4fv = Switch_ProgramUniformMatrix2x4fv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX3DVPROC _ptrc_glProgramUniformMatrix3dv = Switch_ProgramUniformMatrix3dv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX3FVPROC _ptrc_glProgramUniformMatrix3fv = Switch_ProgramUniformMatrix3fv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX3X2DVPROC _ptrc_glProgramUniformMatrix3x2dv = Switch_ProgramUniformMatrix3x2dv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX3X2FVPROC _ptrc_glProgramUniformMatrix3x2fv = Switch_ProgramUniformMatrix3x2fv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX3X4DVPROC _ptrc_glProgramUniformMatrix3x4dv = Switch_ProgramUniformMatrix3x4dv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX3X4FVPROC _ptrc_glProgramUniformMatrix3x4fv = Switch_ProgramUniformMatrix3x4fv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX4DVPROC _ptrc_glProgramUniformMatrix4dv = Switch_ProgramUniformMatrix4dv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX4FVPROC _ptrc_glProgramUniformMatrix4fv = Switch_ProgramUniformMatrix4fv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX4X2DVPROC _ptrc_glProgramUniformMatrix4x2dv = Switch_ProgramUniformMatrix4x2dv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX4X2FVPROC _ptrc_glProgramUniformMatrix4x2fv = Switch_ProgramUniformMatrix4x2fv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX4X3DVPROC _ptrc_glProgramUniformMatrix4x3dv = Switch_ProgramUniformMatrix4x3dv;
PFN_PTRC_GLPROGRAMUNIFORMMATRIX4X3FVPROC _ptrc_glProgramUniformMatrix4x3fv = Switch_ProgramUniformMatrix4x3fv;
PFN_PTRC_GLRELEASESHADERCOMPILERPROC _ptrc_glReleaseShaderCompiler = Switch_ReleaseShaderCompiler;
PFN_PTRC_GLSCISSORARRAYVPROC _ptrc_glScissorArrayv = Switch_ScissorArrayv;
PFN_PTRC_GLSCISSORINDEXEDPROC _ptrc_glScissorIndexed = Switch_ScissorIndexed;
PFN_PTRC_GLSCISSORINDEXEDVPROC _ptrc_glScissorIndexedv = Switch_ScissorIndexedv;
PFN_PTRC_GLSHADERBINARYPROC _ptrc_glShaderBinary = Switch_ShaderBinary;
PFN_PTRC_GLUSEPROGRAMSTAGESPROC _ptrc_glUseProgramStages = Switch_UseProgramStages;
PFN_PTRC_GLVALIDATEPROGRAMPIPELINEPROC _ptrc_glValidateProgramPipeline = Switch_ValidateProgramPipeline;
PFN_PTRC_GLVERTEXATTRIBL1DPROC _ptrc_glVertexAttribL1d = Switch_VertexAttribL1d;
PFN_PTRC_GLVERTEXATTRIBL1DVPROC _ptrc_glVertexAttribL1dv = Switch_VertexAttribL1dv;
PFN_PTRC_GLVERTEXATTRIBL2DPROC _ptrc_glVertexAttribL2d = Switch_VertexAttribL2d;
PFN_PTRC_GLVERTEXATTRIBL2DVPROC _ptrc_glVertexAttribL2dv = Switch_VertexAttribL2dv;
PFN_PTRC_GLVERTEXATTRIBL3DPROC _ptrc_glVertexAttribL3d = Switch_VertexAttribL3d;
PFN_PTRC_GLVERTEXATTRIBL3DVPROC _ptrc_glVertexAttribL3dv = Switch_VertexAttribL3dv;
PFN_PTRC_GLVERTEXATTRIBL4DPROC _ptrc_glVertexAttribL4d = Switch_VertexAttribL4d;
PFN_PTRC_GLVERTEXATTRIBL4DVPROC _ptrc_glVertexAttribL4dv = Switch_VertexAttribL4dv;
PFN_PTRC_GLVERTEXATTRIBLPOINTERPROC _ptrc_glVertexAttribLPointer = Switch_VertexAttribLPointer;
PFN_PTRC_GLVIEWPORTARRAYVPROC _ptrc_glViewportArrayv = Switch_ViewportArrayv;
PFN_PTRC_GLVIEWPORTINDEXEDFPROC _ptrc_glViewportIndexedf = Switch_ViewportIndexedf;
PFN_PTRC_GLVIEWPORTINDEXEDFVPROC _ptrc_glViewportIndexedfv = Switch_ViewportIndexedfv;

/* Extension: 4.2*/
PFN_PTRC_GLBINDIMAGETEXTUREPROC _ptrc_glBindImageTexture = Switch_BindImageTexture;
PFN_PTRC_GLDRAWARRAYSINSTANCEDBASEINSTANCEPROC _ptrc_glDrawArraysInstancedBaseInstance = Switch_DrawArraysInstancedBaseInstance;
PFN_PTRC_GLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC _ptrc_glDrawElementsInstancedBaseInstance = Switch_DrawElementsInstancedBaseInstance;
PFN_PTRC_GLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC _ptrc_glDrawElementsInstancedBaseVertexBaseInstance = Switch_DrawElementsInstancedBaseVertexBaseInstance;
PFN_PTRC_GLDRAWTRANSFORMFEEDBACKINSTANCEDPROC _ptrc_glDrawTransformFeedbackInstanced = Switch_DrawTransformFeedbackInstanced;
PFN_PTRC_GLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC _ptrc_glDrawTransformFeedbackStreamInstanced = Switch_DrawTransformFeedbackStreamInstanced;
PFN_PTRC_GLGETACTIVEATOMICCOUNTERBUFFERIVPROC _ptrc_glGetActiveAtomicCounterBufferiv = Switch_GetActiveAtomicCounterBufferiv;
PFN_PTRC_GLGETINTERNALFORMATIVPROC _ptrc_glGetInternalformativ = Switch_GetInternalformativ;
PFN_PTRC_GLMEMORYBARRIERPROC _ptrc_glMemoryBarrier = Switch_MemoryBarrier;
PFN_PTRC_GLTEXSTORAGE1DPROC _ptrc_glTexStorage1D = Switch_TexStorage1D;
PFN_PTRC_GLTEXSTORAGE2DPROC _ptrc_glTexStorage2D = Switch_TexStorage2D;
PFN_PTRC_GLTEXSTORAGE3DPROC _ptrc_glTexStorage3D = Switch_TexStorage3D;

/* Extension: 4.3*/
PFN_PTRC_GLBINDVERTEXBUFFERPROC _ptrc_glBindVertexBuffer = Switch_BindVertexBuffer;
PFN_PTRC_GLCLEARBUFFERDATAPROC _ptrc_glClearBufferData = Switch_ClearBufferData;
PFN_PTRC_GLCLEARBUFFERSUBDATAPROC _ptrc_glClearBufferSubData = Switch_ClearBufferSubData;
PFN_PTRC_GLCOPYIMAGESUBDATAPROC _ptrc_glCopyImageSubData = Switch_CopyImageSubData;
PFN_PTRC_GLDEBUGMESSAGECALLBACKPROC _ptrc_glDebugMessageCallback = Switch_DebugMessageCallback;
PFN_PTRC_GLDEBUGMESSAGECONTROLPROC _ptrc_glDebugMessageControl = Switch_DebugMessageControl;
PFN_PTRC_GLDEBUGMESSAGEINSERTPROC _ptrc_glDebugMessageInsert = Switch_DebugMessageInsert;
PFN_PTRC_GLDISPATCHCOMPUTEPROC _ptrc_glDispatchCompute = Switch_DispatchCompute;
PFN_PTRC_GLDISPATCHCOMPUTEINDIRECTPROC _ptrc_glDispatchComputeIndirect = Switch_DispatchComputeIndirect;
PFN_PTRC_GLFRAMEBUFFERPARAMETERIPROC _ptrc_glFramebufferParameteri = Switch_FramebufferParameteri;
PFN_PTRC_GLGETDEBUGMESSAGELOGPROC _ptrc_glGetDebugMessageLog = Switch_GetDebugMessageLog;
PFN_PTRC_GLGETFRAMEBUFFERPARAMETERIVPROC _ptrc_glGetFramebufferParameteriv = Switch_GetFramebufferParameteriv;
PFN_PTRC_GLGETINTERNALFORMATI64VPROC _ptrc_glGetInternalformati64v = Switch_GetInternalformati64v;
PFN_PTRC_GLGETOBJECTLABELPROC _ptrc_glGetObjectLabel = Switch_GetObjectLabel;
PFN_PTRC_GLGETOBJECTPTRLABELPROC _ptrc_glGetObjectPtrLabel = Switch_GetObjectPtrLabel;
PFN_PTRC_GLGETPROGRAMINTERFACEIVPROC _ptrc_glGetProgramInterfaceiv = Switch_GetProgramInterfaceiv;
PFN_PTRC_GLGETPROGRAMRESOURCEINDEXPROC _ptrc_glGetProgramResourceIndex = Switch_GetProgramResourceIndex;
PFN_PTRC_GLGETPROGRAMRESOURCELOCATIONPROC _ptrc_glGetProgramResourceLocation = Switch_GetProgramResourceLocation;
PFN_PTRC_GLGETPROGRAMRESOURCELOCATIONINDEXPROC _ptrc_glGetProgramResourceLocationIndex = Switch_GetProgramResourceLocationIndex;
PFN_PTRC_GLGETPROGRAMRESOURCENAMEPROC _ptrc_glGetProgramResourceName = Switch_GetProgramResourceName;
PFN_PTRC_GLGETPROGRAMRESOURCEIVPROC _ptrc_glGetProgramResourceiv = Switch_GetProgramResourceiv;
PFN_PTRC_GLINVALIDATEBUFFERDATAPROC _ptrc_glInvalidateBufferData = Switch_InvalidateBufferData;
PFN_PTRC_GLINVALIDATEBUFFERSUBDATAPROC _ptrc_glInvalidateBufferSubData = Switch_InvalidateBufferSubData;
PFN_PTRC_GLINVALIDATEFRAMEBUFFERPROC _ptrc_glInvalidateFramebuffer = Switch_InvalidateFramebuffer;
PFN_PTRC_GLINVALIDATESUBFRAMEBUFFERPROC _ptrc_glInvalidateSubFramebuffer = Switch_InvalidateSubFramebuffer;
PFN_PTRC_GLINVALIDATETEXIMAGEPROC _ptrc_glInvalidateTexImage = Switch_InvalidateTexImage;
PFN_PTRC_GLINVALIDATETEXSUBIMAGEPROC _ptrc_glInvalidateTexSubImage = Switch_InvalidateTexSubImage;
PFN_PTRC_GLMULTIDRAWARRAYSINDIRECTPROC _ptrc_glMultiDrawArraysIndirect = Switch_MultiDrawArraysIndirect;
PFN_PTRC_GLMULTIDRAWELEMENTSINDIRECTPROC _ptrc_glMultiDrawElementsIndirect = Switch_MultiDrawElementsIndirect;
PFN_PTRC_GLOBJECTLABELPROC _ptrc_glObjectLabel = Switch_ObjectLabel;
PFN_PTRC_GLOBJECTPTRLABELPROC _ptrc_glObjectPtrLabel = Switch_ObjectPtrLabel;
PFN_PTRC_GLPOPDEBUGGROUPPROC _ptrc_glPopDebugGroup = Switch_PopDebugGroup;
PFN_PTRC_GLPUSHDEBUGGROUPPROC _ptrc_glPushDebugGroup = Switch_PushDebugGroup;
PFN_PTRC_GLSHADERSTORAGEBLOCKBINDINGPROC _ptrc_glShaderStorageBlockBinding = Switch_ShaderStorageBlockBinding;
PFN_PTRC_GLTEXBUFFERRANGEPROC _ptrc_glTexBufferRange = Switch_TexBufferRange;
PFN_PTRC_GLTEXSTORAGE2DMULTISAMPLEPROC _ptrc_glTexStorage2DMultisample = Switch_TexStorage2DMultisample;
PFN_PTRC_GLTEXSTORAGE3DMULTISAMPLEPROC _ptrc_glTexStorage3DMultisample = Switch_TexStorage3DMultisample;
PFN_PTRC_GLTEXTUREVIEWPROC _ptrc_glTextureView = Switch_TextureView;
PFN_PTRC_GLVERTEXATTRIBBINDINGPROC _ptrc_glVertexAttribBinding = Switch_VertexAttribBinding;
PFN_PTRC_GLVERTEXATTRIBFORMATPROC _ptrc_glVertexAttribFormat = Switch_VertexAttribFormat;
PFN_PTRC_GLVERTEXATTRIBIFORMATPROC _ptrc_glVertexAttribIFormat = Switch_VertexAttribIFormat;
PFN_PTRC_GLVERTEXATTRIBLFORMATPROC _ptrc_glVertexAttribLFormat = Switch_VertexAttribLFormat;
PFN_PTRC_GLVERTEXBINDINGDIVISORPROC _ptrc_glVertexBindingDivisor = Switch_VertexBindingDivisor;

/* Extension: 4.4*/
PFN_PTRC_GLBINDBUFFERSBASEPROC _ptrc_glBindBuffersBase = Switch_BindBuffersBase;
PFN_PTRC_GLBINDBUFFERSRANGEPROC _ptrc_glBindBuffersRange = Switch_BindBuffersRange;
PFN_PTRC_GLBINDIMAGETEXTURESPROC _ptrc_glBindImageTextures = Switch_BindImageTextures;
PFN_PTRC_GLBINDSAMPLERSPROC _ptrc_glBindSamplers = Switch_BindSamplers;
PFN_PTRC_GLBINDTEXTURESPROC _ptrc_glBindTextures = Switch_BindTextures;
PFN_PTRC_GLBINDVERTEXBUFFERSPROC _ptrc_glBindVertexBuffers = Switch_BindVertexBuffers;
PFN_PTRC_GLBUFFERSTORAGEPROC _ptrc_glBufferStorage = Switch_BufferStorage;
PFN_PTRC_GLCLEARTEXIMAGEPROC _ptrc_glClearTexImage = Switch_ClearTexImage;
PFN_PTRC_GLCLEARTEXSUBIMAGEPROC _ptrc_glClearTexSubImage = Switch_ClearTexSubImage;

/* Extension: 4.5*/
PFN_PTRC_GLBINDTEXTUREUNITPROC _ptrc_glBindTextureUnit = Switch_BindTextureUnit;
PFN_PTRC_GLBLITNAMEDFRAMEBUFFERPROC _ptrc_glBlitNamedFramebuffer = Switch_BlitNamedFramebuffer;
PFN_PTRC_GLCHECKNAMEDFRAMEBUFFERSTATUSPROC _ptrc_glCheckNamedFramebufferStatus = Switch_CheckNamedFramebufferStatus;
PFN_PTRC_GLCLEARNAMEDBUFFERDATAPROC _ptrc_glClearNamedBufferData = Switch_ClearNamedBufferData;
PFN_PTRC_GLCLEARNAMEDBUFFERSUBDATAPROC _ptrc_glClearNamedBufferSubData = Switch_ClearNamedBufferSubData;
PFN_PTRC_GLCLEARNAMEDFRAMEBUFFERFIPROC _ptrc_glClearNamedFramebufferfi = Switch_ClearNamedFramebufferfi;
PFN_PTRC_GLCLEARNAMEDFRAMEBUFFERFVPROC _ptrc_glClearNamedFramebufferfv = Switch_ClearNamedFramebufferfv;
PFN_PTRC_GLCLEARNAMEDFRAMEBUFFERIVPROC _ptrc_glClearNamedFramebufferiv = Switch_ClearNamedFramebufferiv;
PFN_PTRC_GLCLEARNAMEDFRAMEBUFFERUIVPROC _ptrc_glClearNamedFramebufferuiv = Switch_ClearNamedFramebufferuiv;
PFN_PTRC_GLCLIPCONTROLPROC _ptrc_glClipControl = Switch_ClipControl;
PFN_PTRC_GLCOMPRESSEDTEXTURESUBIMAGE1DPROC _ptrc_glCompressedTextureSubImage1D = Switch_CompressedTextureSubImage1D;
PFN_PTRC_GLCOMPRESSEDTEXTURESUBIMAGE2DPROC _ptrc_glCompressedTextureSubImage2D = Switch_CompressedTextureSubImage2D;
PFN_PTRC_GLCOMPRESSEDTEXTURESUBIMAGE3DPROC _ptrc_glCompressedTextureSubImage3D = Switch_CompressedTextureSubImage3D;
PFN_PTRC_GLCOPYNAMEDBUFFERSUBDATAPROC _ptrc_glCopyNamedBufferSubData = Switch_CopyNamedBufferSubData;
PFN_PTRC_GLCOPYTEXTURESUBIMAGE1DPROC _ptrc_glCopyTextureSubImage1D = Switch_CopyTextureSubImage1D;
PFN_PTRC_GLCOPYTEXTURESUBIMAGE2DPROC _ptrc_glCopyTextureSubImage2D = Switch_CopyTextureSubImage2D;
PFN_PTRC_GLCOPYTEXTURESUBIMAGE3DPROC _ptrc_glCopyTextureSubImage3D = Switch_CopyTextureSubImage3D;
PFN_PTRC_GLCREATEBUFFERSPROC _ptrc_glCreateBuffers = Switch_CreateBuffers;
PFN_PTRC_GLCREATEFRAMEBUFFERSPROC _ptrc_glCreateFramebuffers = Switch_CreateFramebuffers;
PFN_PTRC_GLCREATEPROGRAMPIPELINESPROC _ptrc_glCreateProgramPipelines = Switch_CreateProgramPipelines;
PFN_PTRC_GLCREATEQUERIESPROC _ptrc_glCreateQueries = Switch_CreateQueries;
PFN_PTRC_GLCREATERENDERBUFFERSPROC _ptrc_glCreateRenderbuffers = Switch_CreateRenderbuffers;
PFN_PTRC_GLCREATESAMPLERSPROC _ptrc_glCreateSamplers = Switch_CreateSamplers;
PFN_PTRC_GLCREATETEXTURESPROC _ptrc_glCreateTextures = Switch_CreateTextures;
PFN_PTRC_GLCREATETRANSFORMFEEDBACKSPROC _ptrc_glCreateTransformFeedbacks = Switch_CreateTransformFeedbacks;
PFN_PTRC_GLCREATEVERTEXARRAYSPROC _ptrc_glCreateVertexArrays = Switch_CreateVertexArrays;
PFN_PTRC_GLDISABLEVERTEXARRAYATTRIBPROC _ptrc_glDisableVertexArrayAttrib = Switch_DisableVertexArrayAttrib;
PFN_PTRC_GLENABLEVERTEXARRAYATTRIBPROC _ptrc_glEnableVertexArrayAttrib = Switch_EnableVertexArrayAttrib;
PFN_PTRC_GLFLUSHMAPPEDNAMEDBUFFERRANGEPROC _ptrc_glFlushMappedNamedBufferRange = Switch_FlushMappedNamedBufferRange;
PFN_PTRC_GLGENERATETEXTUREMIPMAPPROC _ptrc_glGenerateTextureMipmap = Switch_GenerateTextureMipmap;
PFN_PTRC_GLGETCOMPRESSEDTEXTUREIMAGEPROC _ptrc_glGetCompressedTextureImage = Switch_GetCompressedTextureImage;
PFN_PTRC_GLGETCOMPRESSEDTEXTURESUBIMAGEPROC _ptrc_glGetCompressedTextureSubImage = Switch_GetCompressedTextureSubImage;
PFN_PTRC_GLGETGRAPHICSRESETSTATUSPROC _ptrc_glGetGraphicsResetStatus = Switch_GetGraphicsResetStatus;
PFN_PTRC_GLGETNAMEDBUFFERPARAMETERI64VPROC _ptrc_glGetNamedBufferParameteri64v = Switch_GetNamedBufferParameteri64v;
PFN_PTRC_GLGETNAMEDBUFFERPARAMETERIVPROC _ptrc_glGetNamedBufferParameteriv = Switch_GetNamedBufferParameteriv;
PFN_PTRC_GLGETNAMEDBUFFERPOINTERVPROC _ptrc_glGetNamedBufferPointerv = Switch_GetNamedBufferPointerv;
PFN_PTRC_GLGETNAMEDBUFFERSUBDATAPROC _ptrc_glGetNamedBufferSubData = Switch_GetNamedBufferSubData;
PFN_PTRC_GLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC _ptrc_glGetNamedFramebufferAttachmentParameteriv = Switch_GetNamedFramebufferAttachmentParameteriv;
PFN_PTRC_GLGETNAMEDFRAMEBUFFERPARAMETERIVPROC _ptrc_glGetNamedFramebufferParameteriv = Switch_GetNamedFramebufferParameteriv;
PFN_PTRC_GLGETNAMEDRENDERBUFFERPARAMETERIVPROC _ptrc_glGetNamedRenderbufferParameteriv = Switch_GetNamedRenderbufferParameteriv;
PFN_PTRC_GLGETQUERYBUFFEROBJECTI64VPROC _ptrc_glGetQueryBufferObjecti64v = Switch_GetQueryBufferObjecti64v;
PFN_PTRC_GLGETQUERYBUFFEROBJECTIVPROC _ptrc_glGetQueryBufferObjectiv = Switch_GetQueryBufferObjectiv;
PFN_PTRC_GLGETQUERYBUFFEROBJECTUI64VPROC _ptrc_glGetQueryBufferObjectui64v = Switch_GetQueryBufferObjectui64v;
PFN_PTRC_GLGETQUERYBUFFEROBJECTUIVPROC _ptrc_glGetQueryBufferObjectuiv = Switch_GetQueryBufferObjectuiv;
PFN_PTRC_GLGETTEXTUREIMAGEPROC _ptrc_glGetTextureImage = Switch_GetTextureImage;
PFN_PTRC_GLGETTEXTURELEVELPARAMETERFVPROC _ptrc_glGetTextureLevelParameterfv = Switch_GetTextureLevelParameterfv;
PFN_PTRC_GLGETTEXTURELEVELPARAMETERIVPROC _ptrc_glGetTextureLevelParameteriv = Switch_GetTextureLevelParameteriv;
PFN_PTRC_GLGETTEXTUREPARAMETERIIVPROC _ptrc_glGetTextureParameterIiv = Switch_GetTextureParameterIiv;
PFN_PTRC_GLGETTEXTUREPARAMETERIUIVPROC _ptrc_glGetTextureParameterIuiv = Switch_GetTextureParameterIuiv;
PFN_PTRC_GLGETTEXTUREPARAMETERFVPROC _ptrc_glGetTextureParameterfv = Switch_GetTextureParameterfv;
PFN_PTRC_GLGETTEXTUREPARAMETERIVPROC _ptrc_glGetTextureParameteriv = Switch_GetTextureParameteriv;
PFN_PTRC_GLGETTEXTURESUBIMAGEPROC _ptrc_glGetTextureSubImage = Switch_GetTextureSubImage;
PFN_PTRC_GLGETTRANSFORMFEEDBACKI64_VPROC _ptrc_glGetTransformFeedbacki64_v = Switch_GetTransformFeedbacki64_v;
PFN_PTRC_GLGETTRANSFORMFEEDBACKI_VPROC _ptrc_glGetTransformFeedbacki_v = Switch_GetTransformFeedbacki_v;
PFN_PTRC_GLGETTRANSFORMFEEDBACKIVPROC _ptrc_glGetTransformFeedbackiv = Switch_GetTransformFeedbackiv;
PFN_PTRC_GLGETVERTEXARRAYINDEXED64IVPROC _ptrc_glGetVertexArrayIndexed64iv = Switch_GetVertexArrayIndexed64iv;
PFN_PTRC_GLGETVERTEXARRAYINDEXEDIVPROC _ptrc_glGetVertexArrayIndexediv = Switch_GetVertexArrayIndexediv;
PFN_PTRC_GLGETVERTEXARRAYIVPROC _ptrc_glGetVertexArrayiv = Switch_GetVertexArrayiv;
PFN_PTRC_GLGETNCOMPRESSEDTEXIMAGEPROC _ptrc_glGetnCompressedTexImage = Switch_GetnCompressedTexImage;
PFN_PTRC_GLGETNTEXIMAGEPROC _ptrc_glGetnTexImage = Switch_GetnTexImage;
PFN_PTRC_GLGETNUNIFORMDVPROC _ptrc_glGetnUniformdv = Switch_GetnUniformdv;
PFN_PTRC_GLGETNUNIFORMFVPROC _ptrc_glGetnUniformfv = Switch_GetnUniformfv;
PFN_PTRC_GLGETNUNIFORMIVPROC _ptrc_glGetnUniformiv = Switch_GetnUniformiv;
PFN_PTRC_GLGETNUNIFORMUIVPROC _ptrc_glGetnUniformuiv = Switch_GetnUniformuiv;
PFN_PTRC_GLINVALIDATENAMEDFRAMEBUFFERDATAPROC _ptrc_glInvalidateNamedFramebufferData = Switch_InvalidateNamedFramebufferData;
PFN_PTRC_GLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC _ptrc_glInvalidateNamedFramebufferSubData = Switch_InvalidateNamedFramebufferSubData;
PFN_PTRC_GLMAPNAMEDBUFFERPROC _ptrc_glMapNamedBuffer = Switch_MapNamedBuffer;
PFN_PTRC_GLMAPNAMEDBUFFERRANGEPROC _ptrc_glMapNamedBufferRange = Switch_MapNamedBufferRange;
PFN_PTRC_GLMEMORYBARRIERBYREGIONPROC _ptrc_glMemoryBarrierByRegion = Switch_MemoryBarrierByRegion;
PFN_PTRC_GLNAMEDBUFFERDATAPROC _ptrc_glNamedBufferData = Switch_NamedBufferData;
PFN_PTRC_GLNAMEDBUFFERSTORAGEPROC _ptrc_glNamedBufferStorage = Switch_NamedBufferStorage;
PFN_PTRC_GLNAMEDBUFFERSUBDATAPROC _ptrc_glNamedBufferSubData = Switch_NamedBufferSubData;
PFN_PTRC_GLNAMEDFRAMEBUFFERDRAWBUFFERPROC _ptrc_glNamedFramebufferDrawBuffer = Switch_NamedFramebufferDrawBuffer;
PFN_PTRC_GLNAMEDFRAMEBUFFERDRAWBUFFERSPROC _ptrc_glNamedFramebufferDrawBuffers = Switch_NamedFramebufferDrawBuffers;
PFN_PTRC_GLNAMEDFRAMEBUFFERPARAMETERIPROC _ptrc_glNamedFramebufferParameteri = Switch_NamedFramebufferParameteri;
PFN_PTRC_GLNAMEDFRAMEBUFFERREADBUFFERPROC _ptrc_glNamedFramebufferReadBuffer = Switch_NamedFramebufferReadBuffer;
PFN_PTRC_GLNAMEDFRAMEBUFFERRENDERBUFFERPROC _ptrc_glNamedFramebufferRenderbuffer = Switch_NamedFramebufferRenderbuffer;
PFN_PTRC_GLNAMEDFRAMEBUFFERTEXTUREPROC _ptrc_glNamedFramebufferTexture = Switch_NamedFramebufferTexture;
PFN_PTRC_GLNAMEDFRAMEBUFFERTEXTURELAYERPROC _ptrc_glNamedFramebufferTextureLayer = Switch_NamedFramebufferTextureLayer;
PFN_PTRC_GLNAMEDRENDERBUFFERSTORAGEPROC _ptrc_glNamedRenderbufferStorage = Switch_NamedRenderbufferStorage;
PFN_PTRC_GLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC _ptrc_glNamedRenderbufferStorageMultisample = Switch_NamedRenderbufferStorageMultisample;
PFN_PTRC_GLREADNPIXELSPROC _ptrc_glReadnPixels = Switch_ReadnPixels;
PFN_PTRC_GLTEXTUREBARRIERPROC _ptrc_glTextureBarrier = Switch_TextureBarrier;
PFN_PTRC_GLTEXTUREBUFFERPROC _ptrc_glTextureBuffer = Switch_TextureBuffer;
PFN_PTRC_GLTEXTUREBUFFERRANGEPROC _ptrc_glTextureBufferRange = Switch_TextureBufferRange;
PFN_PTRC_GLTEXTUREPARAMETERIIVPROC _ptrc_glTextureParameterIiv = Switch_TextureParameterIiv;
PFN_PTRC_GLTEXTUREPARAMETERIUIVPROC _ptrc_glTextureParameterIuiv = Switch_TextureParameterIuiv;
PFN_PTRC_GLTEXTUREPARAMETERFPROC _ptrc_glTextureParameterf = Switch_TextureParameterf;
PFN_PTRC_GLTEXTUREPARAMETERFVPROC _ptrc_glTextureParameterfv = Switch_TextureParameterfv;
PFN_PTRC_GLTEXTUREPARAMETERIPROC _ptrc_glTextureParameteri = Switch_TextureParameteri;
PFN_PTRC_GLTEXTUREPARAMETERIVPROC _ptrc_glTextureParameteriv = Switch_TextureParameteriv;
PFN_PTRC_GLTEXTURESTORAGE1DPROC _ptrc_glTextureStorage1D = Switch_TextureStorage1D;
PFN_PTRC_GLTEXTURESTORAGE2DPROC _ptrc_glTextureStorage2D = Switch_TextureStorage2D;
PFN_PTRC_GLTEXTURESTORAGE2DMULTISAMPLEPROC _ptrc_glTextureStorage2DMultisample = Switch_TextureStorage2DMultisample;
PFN_PTRC_GLTEXTURESTORAGE3DPROC _ptrc_glTextureStorage3D = Switch_TextureStorage3D;
PFN_PTRC_GLTEXTURESTORAGE3DMULTISAMPLEPROC _ptrc_glTextureStorage3DMultisample = Switch_TextureStorage3DMultisample;
PFN_PTRC_GLTEXTURESUBIMAGE1DPROC _ptrc_glTextureSubImage1D = Switch_TextureSubImage1D;
PFN_PTRC_GLTEXTURESUBIMAGE2DPROC _ptrc_glTextureSubImage2D = Switch_TextureSubImage2D;
PFN_PTRC_GLTEXTURESUBIMAGE3DPROC _ptrc_glTextureSubImage3D = Switch_TextureSubImage3D;
PFN_PTRC_GLTRANSFORMFEEDBACKBUFFERBASEPROC _ptrc_glTransformFeedbackBufferBase = Switch_TransformFeedbackBufferBase;
PFN_PTRC_GLTRANSFORMFEEDBACKBUFFERRANGEPROC _ptrc_glTransformFeedbackBufferRange = Switch_TransformFeedbackBufferRange;
PFN_PTRC_GLUNMAPNAMEDBUFFERPROC _ptrc_glUnmapNamedBuffer = Switch_UnmapNamedBuffer;
PFN_PTRC_GLVERTEXARRAYATTRIBBINDINGPROC _ptrc_glVertexArrayAttribBinding = Switch_VertexArrayAttribBinding;
PFN_PTRC_GLVERTEXARRAYATTRIBFORMATPROC _ptrc_glVertexArrayAttribFormat = Switch_VertexArrayAttribFormat;
PFN_PTRC_GLVERTEXARRAYATTRIBIFORMATPROC _ptrc_glVertexArrayAttribIFormat = Switch_VertexArrayAttribIFormat;
PFN_PTRC_GLVERTEXARRAYATTRIBLFORMATPROC _ptrc_glVertexArrayAttribLFormat = Switch_VertexArrayAttribLFormat;
PFN_PTRC_GLVERTEXARRAYBINDINGDIVISORPROC _ptrc_glVertexArrayBindingDivisor = Switch_VertexArrayBindingDivisor;
PFN_PTRC_GLVERTEXARRAYELEMENTBUFFERPROC _ptrc_glVertexArrayElementBuffer = Switch_VertexArrayElementBuffer;
PFN_PTRC_GLVERTEXARRAYVERTEXBUFFERPROC _ptrc_glVertexArrayVertexBuffer = Switch_VertexArrayVertexBuffer;
PFN_PTRC_GLVERTEXARRAYVERTEXBUFFERSPROC _ptrc_glVertexArrayVertexBuffers = Switch_VertexArrayVertexBuffers;


/* Extension: 1.0*/
static void CODEGEN_FUNCPTR Switch_Accum(GLenum op, GLfloat value)
{
	_ptrc_glAccum = (PFN_PTRC_GLACCUMPROC)IntGetProcAddress("glAccum");
	_ptrc_glAccum(op, value);
}

static void CODEGEN_FUNCPTR Switch_AlphaFunc(GLenum func, GLfloat ref)
{
	_ptrc_glAlphaFunc = (PFN_PTRC_GLALPHAFUNCPROC)IntGetProcAddress("glAlphaFunc");
	_ptrc_glAlphaFunc(func, ref);
}

static void CODEGEN_FUNCPTR Switch_Begin(GLenum mode)
{
	_ptrc_glBegin = (PFN_PTRC_GLBEGINPROC)IntGetProcAddress("glBegin");
	_ptrc_glBegin(mode);
}

static void CODEGEN_FUNCPTR Switch_Bitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap)
{
	_ptrc_glBitmap = (PFN_PTRC_GLBITMAPPROC)IntGetProcAddress("glBitmap");
	_ptrc_glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap);
}

static void CODEGEN_FUNCPTR Switch_BlendFunc(GLenum sfactor, GLenum dfactor)
{
	_ptrc_glBlendFunc = (PFN_PTRC_GLBLENDFUNCPROC)IntGetProcAddress("glBlendFunc");
	_ptrc_glBlendFunc(sfactor, dfactor);
}

static void CODEGEN_FUNCPTR Switch_CallList(GLuint list)
{
	_ptrc_glCallList = (PFN_PTRC_GLCALLLISTPROC)IntGetProcAddress("glCallList");
	_ptrc_glCallList(list);
}

static void CODEGEN_FUNCPTR Switch_CallLists(GLsizei n, GLenum type, const void * lists)
{
	_ptrc_glCallLists = (PFN_PTRC_GLCALLLISTSPROC)IntGetProcAddress("glCallLists");
	_ptrc_glCallLists(n, type, lists);
}

static void CODEGEN_FUNCPTR Switch_Clear(GLbitfield mask)
{
	_ptrc_glClear = (PFN_PTRC_GLCLEARPROC)IntGetProcAddress("glClear");
	_ptrc_glClear(mask);
}

static void CODEGEN_FUNCPTR Switch_ClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	_ptrc_glClearAccum = (PFN_PTRC_GLCLEARACCUMPROC)IntGetProcAddress("glClearAccum");
	_ptrc_glClearAccum(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	_ptrc_glClearColor = (PFN_PTRC_GLCLEARCOLORPROC)IntGetProcAddress("glClearColor");
	_ptrc_glClearColor(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_ClearDepth(GLdouble depth)
{
	_ptrc_glClearDepth = (PFN_PTRC_GLCLEARDEPTHPROC)IntGetProcAddress("glClearDepth");
	_ptrc_glClearDepth(depth);
}

static void CODEGEN_FUNCPTR Switch_ClearIndex(GLfloat c)
{
	_ptrc_glClearIndex = (PFN_PTRC_GLCLEARINDEXPROC)IntGetProcAddress("glClearIndex");
	_ptrc_glClearIndex(c);
}

static void CODEGEN_FUNCPTR Switch_ClearStencil(GLint s)
{
	_ptrc_glClearStencil = (PFN_PTRC_GLCLEARSTENCILPROC)IntGetProcAddress("glClearStencil");
	_ptrc_glClearStencil(s);
}

static void CODEGEN_FUNCPTR Switch_ClipPlane(GLenum plane, const GLdouble * equation)
{
	_ptrc_glClipPlane = (PFN_PTRC_GLCLIPPLANEPROC)IntGetProcAddress("glClipPlane");
	_ptrc_glClipPlane(plane, equation);
}

static void CODEGEN_FUNCPTR Switch_Color3b(GLbyte red, GLbyte green, GLbyte blue)
{
	_ptrc_glColor3b = (PFN_PTRC_GLCOLOR3BPROC)IntGetProcAddress("glColor3b");
	_ptrc_glColor3b(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_Color3bv(const GLbyte * v)
{
	_ptrc_glColor3bv = (PFN_PTRC_GLCOLOR3BVPROC)IntGetProcAddress("glColor3bv");
	_ptrc_glColor3bv(v);
}

static void CODEGEN_FUNCPTR Switch_Color3d(GLdouble red, GLdouble green, GLdouble blue)
{
	_ptrc_glColor3d = (PFN_PTRC_GLCOLOR3DPROC)IntGetProcAddress("glColor3d");
	_ptrc_glColor3d(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_Color3dv(const GLdouble * v)
{
	_ptrc_glColor3dv = (PFN_PTRC_GLCOLOR3DVPROC)IntGetProcAddress("glColor3dv");
	_ptrc_glColor3dv(v);
}

static void CODEGEN_FUNCPTR Switch_Color3f(GLfloat red, GLfloat green, GLfloat blue)
{
	_ptrc_glColor3f = (PFN_PTRC_GLCOLOR3FPROC)IntGetProcAddress("glColor3f");
	_ptrc_glColor3f(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_Color3fv(const GLfloat * v)
{
	_ptrc_glColor3fv = (PFN_PTRC_GLCOLOR3FVPROC)IntGetProcAddress("glColor3fv");
	_ptrc_glColor3fv(v);
}

static void CODEGEN_FUNCPTR Switch_Color3i(GLint red, GLint green, GLint blue)
{
	_ptrc_glColor3i = (PFN_PTRC_GLCOLOR3IPROC)IntGetProcAddress("glColor3i");
	_ptrc_glColor3i(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_Color3iv(const GLint * v)
{
	_ptrc_glColor3iv = (PFN_PTRC_GLCOLOR3IVPROC)IntGetProcAddress("glColor3iv");
	_ptrc_glColor3iv(v);
}

static void CODEGEN_FUNCPTR Switch_Color3s(GLshort red, GLshort green, GLshort blue)
{
	_ptrc_glColor3s = (PFN_PTRC_GLCOLOR3SPROC)IntGetProcAddress("glColor3s");
	_ptrc_glColor3s(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_Color3sv(const GLshort * v)
{
	_ptrc_glColor3sv = (PFN_PTRC_GLCOLOR3SVPROC)IntGetProcAddress("glColor3sv");
	_ptrc_glColor3sv(v);
}

static void CODEGEN_FUNCPTR Switch_Color3ub(GLubyte red, GLubyte green, GLubyte blue)
{
	_ptrc_glColor3ub = (PFN_PTRC_GLCOLOR3UBPROC)IntGetProcAddress("glColor3ub");
	_ptrc_glColor3ub(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_Color3ubv(const GLubyte * v)
{
	_ptrc_glColor3ubv = (PFN_PTRC_GLCOLOR3UBVPROC)IntGetProcAddress("glColor3ubv");
	_ptrc_glColor3ubv(v);
}

static void CODEGEN_FUNCPTR Switch_Color3ui(GLuint red, GLuint green, GLuint blue)
{
	_ptrc_glColor3ui = (PFN_PTRC_GLCOLOR3UIPROC)IntGetProcAddress("glColor3ui");
	_ptrc_glColor3ui(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_Color3uiv(const GLuint * v)
{
	_ptrc_glColor3uiv = (PFN_PTRC_GLCOLOR3UIVPROC)IntGetProcAddress("glColor3uiv");
	_ptrc_glColor3uiv(v);
}

static void CODEGEN_FUNCPTR Switch_Color3us(GLushort red, GLushort green, GLushort blue)
{
	_ptrc_glColor3us = (PFN_PTRC_GLCOLOR3USPROC)IntGetProcAddress("glColor3us");
	_ptrc_glColor3us(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_Color3usv(const GLushort * v)
{
	_ptrc_glColor3usv = (PFN_PTRC_GLCOLOR3USVPROC)IntGetProcAddress("glColor3usv");
	_ptrc_glColor3usv(v);
}

static void CODEGEN_FUNCPTR Switch_Color4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha)
{
	_ptrc_glColor4b = (PFN_PTRC_GLCOLOR4BPROC)IntGetProcAddress("glColor4b");
	_ptrc_glColor4b(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_Color4bv(const GLbyte * v)
{
	_ptrc_glColor4bv = (PFN_PTRC_GLCOLOR4BVPROC)IntGetProcAddress("glColor4bv");
	_ptrc_glColor4bv(v);
}

static void CODEGEN_FUNCPTR Switch_Color4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha)
{
	_ptrc_glColor4d = (PFN_PTRC_GLCOLOR4DPROC)IntGetProcAddress("glColor4d");
	_ptrc_glColor4d(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_Color4dv(const GLdouble * v)
{
	_ptrc_glColor4dv = (PFN_PTRC_GLCOLOR4DVPROC)IntGetProcAddress("glColor4dv");
	_ptrc_glColor4dv(v);
}

static void CODEGEN_FUNCPTR Switch_Color4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	_ptrc_glColor4f = (PFN_PTRC_GLCOLOR4FPROC)IntGetProcAddress("glColor4f");
	_ptrc_glColor4f(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_Color4fv(const GLfloat * v)
{
	_ptrc_glColor4fv = (PFN_PTRC_GLCOLOR4FVPROC)IntGetProcAddress("glColor4fv");
	_ptrc_glColor4fv(v);
}

static void CODEGEN_FUNCPTR Switch_Color4i(GLint red, GLint green, GLint blue, GLint alpha)
{
	_ptrc_glColor4i = (PFN_PTRC_GLCOLOR4IPROC)IntGetProcAddress("glColor4i");
	_ptrc_glColor4i(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_Color4iv(const GLint * v)
{
	_ptrc_glColor4iv = (PFN_PTRC_GLCOLOR4IVPROC)IntGetProcAddress("glColor4iv");
	_ptrc_glColor4iv(v);
}

static void CODEGEN_FUNCPTR Switch_Color4s(GLshort red, GLshort green, GLshort blue, GLshort alpha)
{
	_ptrc_glColor4s = (PFN_PTRC_GLCOLOR4SPROC)IntGetProcAddress("glColor4s");
	_ptrc_glColor4s(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_Color4sv(const GLshort * v)
{
	_ptrc_glColor4sv = (PFN_PTRC_GLCOLOR4SVPROC)IntGetProcAddress("glColor4sv");
	_ptrc_glColor4sv(v);
}

static void CODEGEN_FUNCPTR Switch_Color4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
	_ptrc_glColor4ub = (PFN_PTRC_GLCOLOR4UBPROC)IntGetProcAddress("glColor4ub");
	_ptrc_glColor4ub(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_Color4ubv(const GLubyte * v)
{
	_ptrc_glColor4ubv = (PFN_PTRC_GLCOLOR4UBVPROC)IntGetProcAddress("glColor4ubv");
	_ptrc_glColor4ubv(v);
}

static void CODEGEN_FUNCPTR Switch_Color4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha)
{
	_ptrc_glColor4ui = (PFN_PTRC_GLCOLOR4UIPROC)IntGetProcAddress("glColor4ui");
	_ptrc_glColor4ui(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_Color4uiv(const GLuint * v)
{
	_ptrc_glColor4uiv = (PFN_PTRC_GLCOLOR4UIVPROC)IntGetProcAddress("glColor4uiv");
	_ptrc_glColor4uiv(v);
}

static void CODEGEN_FUNCPTR Switch_Color4us(GLushort red, GLushort green, GLushort blue, GLushort alpha)
{
	_ptrc_glColor4us = (PFN_PTRC_GLCOLOR4USPROC)IntGetProcAddress("glColor4us");
	_ptrc_glColor4us(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_Color4usv(const GLushort * v)
{
	_ptrc_glColor4usv = (PFN_PTRC_GLCOLOR4USVPROC)IntGetProcAddress("glColor4usv");
	_ptrc_glColor4usv(v);
}

static void CODEGEN_FUNCPTR Switch_ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	_ptrc_glColorMask = (PFN_PTRC_GLCOLORMASKPROC)IntGetProcAddress("glColorMask");
	_ptrc_glColorMask(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_ColorMaterial(GLenum face, GLenum mode)
{
	_ptrc_glColorMaterial = (PFN_PTRC_GLCOLORMATERIALPROC)IntGetProcAddress("glColorMaterial");
	_ptrc_glColorMaterial(face, mode);
}

static void CODEGEN_FUNCPTR Switch_CopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type)
{
	_ptrc_glCopyPixels = (PFN_PTRC_GLCOPYPIXELSPROC)IntGetProcAddress("glCopyPixels");
	_ptrc_glCopyPixels(x, y, width, height, type);
}

static void CODEGEN_FUNCPTR Switch_CullFace(GLenum mode)
{
	_ptrc_glCullFace = (PFN_PTRC_GLCULLFACEPROC)IntGetProcAddress("glCullFace");
	_ptrc_glCullFace(mode);
}

static void CODEGEN_FUNCPTR Switch_DeleteLists(GLuint list, GLsizei range)
{
	_ptrc_glDeleteLists = (PFN_PTRC_GLDELETELISTSPROC)IntGetProcAddress("glDeleteLists");
	_ptrc_glDeleteLists(list, range);
}

static void CODEGEN_FUNCPTR Switch_DepthFunc(GLenum func)
{
	_ptrc_glDepthFunc = (PFN_PTRC_GLDEPTHFUNCPROC)IntGetProcAddress("glDepthFunc");
	_ptrc_glDepthFunc(func);
}

static void CODEGEN_FUNCPTR Switch_DepthMask(GLboolean flag)
{
	_ptrc_glDepthMask = (PFN_PTRC_GLDEPTHMASKPROC)IntGetProcAddress("glDepthMask");
	_ptrc_glDepthMask(flag);
}

static void CODEGEN_FUNCPTR Switch_DepthRange(GLdouble ren_near, GLdouble ren_far)
{
	_ptrc_glDepthRange = (PFN_PTRC_GLDEPTHRANGEPROC)IntGetProcAddress("glDepthRange");
	_ptrc_glDepthRange(ren_near, ren_far);
}

static void CODEGEN_FUNCPTR Switch_Disable(GLenum cap)
{
	_ptrc_glDisable = (PFN_PTRC_GLDISABLEPROC)IntGetProcAddress("glDisable");
	_ptrc_glDisable(cap);
}

static void CODEGEN_FUNCPTR Switch_DrawBuffer(GLenum buf)
{
	_ptrc_glDrawBuffer = (PFN_PTRC_GLDRAWBUFFERPROC)IntGetProcAddress("glDrawBuffer");
	_ptrc_glDrawBuffer(buf);
}

static void CODEGEN_FUNCPTR Switch_DrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
{
	_ptrc_glDrawPixels = (PFN_PTRC_GLDRAWPIXELSPROC)IntGetProcAddress("glDrawPixels");
	_ptrc_glDrawPixels(width, height, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_EdgeFlag(GLboolean flag)
{
	_ptrc_glEdgeFlag = (PFN_PTRC_GLEDGEFLAGPROC)IntGetProcAddress("glEdgeFlag");
	_ptrc_glEdgeFlag(flag);
}

static void CODEGEN_FUNCPTR Switch_EdgeFlagv(const GLboolean * flag)
{
	_ptrc_glEdgeFlagv = (PFN_PTRC_GLEDGEFLAGVPROC)IntGetProcAddress("glEdgeFlagv");
	_ptrc_glEdgeFlagv(flag);
}

static void CODEGEN_FUNCPTR Switch_Enable(GLenum cap)
{
	_ptrc_glEnable = (PFN_PTRC_GLENABLEPROC)IntGetProcAddress("glEnable");
	_ptrc_glEnable(cap);
}

static void CODEGEN_FUNCPTR Switch_End(void)
{
	_ptrc_glEnd = (PFN_PTRC_GLENDPROC)IntGetProcAddress("glEnd");
	_ptrc_glEnd();
}

static void CODEGEN_FUNCPTR Switch_EndList(void)
{
	_ptrc_glEndList = (PFN_PTRC_GLENDLISTPROC)IntGetProcAddress("glEndList");
	_ptrc_glEndList();
}

static void CODEGEN_FUNCPTR Switch_EvalCoord1d(GLdouble u)
{
	_ptrc_glEvalCoord1d = (PFN_PTRC_GLEVALCOORD1DPROC)IntGetProcAddress("glEvalCoord1d");
	_ptrc_glEvalCoord1d(u);
}

static void CODEGEN_FUNCPTR Switch_EvalCoord1dv(const GLdouble * u)
{
	_ptrc_glEvalCoord1dv = (PFN_PTRC_GLEVALCOORD1DVPROC)IntGetProcAddress("glEvalCoord1dv");
	_ptrc_glEvalCoord1dv(u);
}

static void CODEGEN_FUNCPTR Switch_EvalCoord1f(GLfloat u)
{
	_ptrc_glEvalCoord1f = (PFN_PTRC_GLEVALCOORD1FPROC)IntGetProcAddress("glEvalCoord1f");
	_ptrc_glEvalCoord1f(u);
}

static void CODEGEN_FUNCPTR Switch_EvalCoord1fv(const GLfloat * u)
{
	_ptrc_glEvalCoord1fv = (PFN_PTRC_GLEVALCOORD1FVPROC)IntGetProcAddress("glEvalCoord1fv");
	_ptrc_glEvalCoord1fv(u);
}

static void CODEGEN_FUNCPTR Switch_EvalCoord2d(GLdouble u, GLdouble v)
{
	_ptrc_glEvalCoord2d = (PFN_PTRC_GLEVALCOORD2DPROC)IntGetProcAddress("glEvalCoord2d");
	_ptrc_glEvalCoord2d(u, v);
}

static void CODEGEN_FUNCPTR Switch_EvalCoord2dv(const GLdouble * u)
{
	_ptrc_glEvalCoord2dv = (PFN_PTRC_GLEVALCOORD2DVPROC)IntGetProcAddress("glEvalCoord2dv");
	_ptrc_glEvalCoord2dv(u);
}

static void CODEGEN_FUNCPTR Switch_EvalCoord2f(GLfloat u, GLfloat v)
{
	_ptrc_glEvalCoord2f = (PFN_PTRC_GLEVALCOORD2FPROC)IntGetProcAddress("glEvalCoord2f");
	_ptrc_glEvalCoord2f(u, v);
}

static void CODEGEN_FUNCPTR Switch_EvalCoord2fv(const GLfloat * u)
{
	_ptrc_glEvalCoord2fv = (PFN_PTRC_GLEVALCOORD2FVPROC)IntGetProcAddress("glEvalCoord2fv");
	_ptrc_glEvalCoord2fv(u);
}

static void CODEGEN_FUNCPTR Switch_EvalMesh1(GLenum mode, GLint i1, GLint i2)
{
	_ptrc_glEvalMesh1 = (PFN_PTRC_GLEVALMESH1PROC)IntGetProcAddress("glEvalMesh1");
	_ptrc_glEvalMesh1(mode, i1, i2);
}

static void CODEGEN_FUNCPTR Switch_EvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2)
{
	_ptrc_glEvalMesh2 = (PFN_PTRC_GLEVALMESH2PROC)IntGetProcAddress("glEvalMesh2");
	_ptrc_glEvalMesh2(mode, i1, i2, j1, j2);
}

static void CODEGEN_FUNCPTR Switch_EvalPoint1(GLint i)
{
	_ptrc_glEvalPoint1 = (PFN_PTRC_GLEVALPOINT1PROC)IntGetProcAddress("glEvalPoint1");
	_ptrc_glEvalPoint1(i);
}

static void CODEGEN_FUNCPTR Switch_EvalPoint2(GLint i, GLint j)
{
	_ptrc_glEvalPoint2 = (PFN_PTRC_GLEVALPOINT2PROC)IntGetProcAddress("glEvalPoint2");
	_ptrc_glEvalPoint2(i, j);
}

static void CODEGEN_FUNCPTR Switch_FeedbackBuffer(GLsizei size, GLenum type, GLfloat * buffer)
{
	_ptrc_glFeedbackBuffer = (PFN_PTRC_GLFEEDBACKBUFFERPROC)IntGetProcAddress("glFeedbackBuffer");
	_ptrc_glFeedbackBuffer(size, type, buffer);
}

static void CODEGEN_FUNCPTR Switch_Finish(void)
{
	_ptrc_glFinish = (PFN_PTRC_GLFINISHPROC)IntGetProcAddress("glFinish");
	_ptrc_glFinish();
}

static void CODEGEN_FUNCPTR Switch_Flush(void)
{
	_ptrc_glFlush = (PFN_PTRC_GLFLUSHPROC)IntGetProcAddress("glFlush");
	_ptrc_glFlush();
}

static void CODEGEN_FUNCPTR Switch_Fogf(GLenum pname, GLfloat param)
{
	_ptrc_glFogf = (PFN_PTRC_GLFOGFPROC)IntGetProcAddress("glFogf");
	_ptrc_glFogf(pname, param);
}

static void CODEGEN_FUNCPTR Switch_Fogfv(GLenum pname, const GLfloat * params)
{
	_ptrc_glFogfv = (PFN_PTRC_GLFOGFVPROC)IntGetProcAddress("glFogfv");
	_ptrc_glFogfv(pname, params);
}

static void CODEGEN_FUNCPTR Switch_Fogi(GLenum pname, GLint param)
{
	_ptrc_glFogi = (PFN_PTRC_GLFOGIPROC)IntGetProcAddress("glFogi");
	_ptrc_glFogi(pname, param);
}

static void CODEGEN_FUNCPTR Switch_Fogiv(GLenum pname, const GLint * params)
{
	_ptrc_glFogiv = (PFN_PTRC_GLFOGIVPROC)IntGetProcAddress("glFogiv");
	_ptrc_glFogiv(pname, params);
}

static void CODEGEN_FUNCPTR Switch_FrontFace(GLenum mode)
{
	_ptrc_glFrontFace = (PFN_PTRC_GLFRONTFACEPROC)IntGetProcAddress("glFrontFace");
	_ptrc_glFrontFace(mode);
}

static void CODEGEN_FUNCPTR Switch_Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
	_ptrc_glFrustum = (PFN_PTRC_GLFRUSTUMPROC)IntGetProcAddress("glFrustum");
	_ptrc_glFrustum(left, right, bottom, top, zNear, zFar);
}

static GLuint CODEGEN_FUNCPTR Switch_GenLists(GLsizei range)
{
	_ptrc_glGenLists = (PFN_PTRC_GLGENLISTSPROC)IntGetProcAddress("glGenLists");
	return _ptrc_glGenLists(range);
}

static void CODEGEN_FUNCPTR Switch_GetBooleanv(GLenum pname, GLboolean * data)
{
	_ptrc_glGetBooleanv = (PFN_PTRC_GLGETBOOLEANVPROC)IntGetProcAddress("glGetBooleanv");
	_ptrc_glGetBooleanv(pname, data);
}

static void CODEGEN_FUNCPTR Switch_GetClipPlane(GLenum plane, GLdouble * equation)
{
	_ptrc_glGetClipPlane = (PFN_PTRC_GLGETCLIPPLANEPROC)IntGetProcAddress("glGetClipPlane");
	_ptrc_glGetClipPlane(plane, equation);
}

static void CODEGEN_FUNCPTR Switch_GetDoublev(GLenum pname, GLdouble * data)
{
	_ptrc_glGetDoublev = (PFN_PTRC_GLGETDOUBLEVPROC)IntGetProcAddress("glGetDoublev");
	_ptrc_glGetDoublev(pname, data);
}

static GLenum CODEGEN_FUNCPTR Switch_GetError(void)
{
	_ptrc_glGetError = (PFN_PTRC_GLGETERRORPROC)IntGetProcAddress("glGetError");
	return _ptrc_glGetError();
}

static void CODEGEN_FUNCPTR Switch_GetFloatv(GLenum pname, GLfloat * data)
{
	_ptrc_glGetFloatv = (PFN_PTRC_GLGETFLOATVPROC)IntGetProcAddress("glGetFloatv");
	_ptrc_glGetFloatv(pname, data);
}

static void CODEGEN_FUNCPTR Switch_GetIntegerv(GLenum pname, GLint * data)
{
	_ptrc_glGetIntegerv = (PFN_PTRC_GLGETINTEGERVPROC)IntGetProcAddress("glGetIntegerv");
	_ptrc_glGetIntegerv(pname, data);
}

static void CODEGEN_FUNCPTR Switch_GetLightfv(GLenum light, GLenum pname, GLfloat * params)
{
	_ptrc_glGetLightfv = (PFN_PTRC_GLGETLIGHTFVPROC)IntGetProcAddress("glGetLightfv");
	_ptrc_glGetLightfv(light, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetLightiv(GLenum light, GLenum pname, GLint * params)
{
	_ptrc_glGetLightiv = (PFN_PTRC_GLGETLIGHTIVPROC)IntGetProcAddress("glGetLightiv");
	_ptrc_glGetLightiv(light, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetMapdv(GLenum target, GLenum query, GLdouble * v)
{
	_ptrc_glGetMapdv = (PFN_PTRC_GLGETMAPDVPROC)IntGetProcAddress("glGetMapdv");
	_ptrc_glGetMapdv(target, query, v);
}

static void CODEGEN_FUNCPTR Switch_GetMapfv(GLenum target, GLenum query, GLfloat * v)
{
	_ptrc_glGetMapfv = (PFN_PTRC_GLGETMAPFVPROC)IntGetProcAddress("glGetMapfv");
	_ptrc_glGetMapfv(target, query, v);
}

static void CODEGEN_FUNCPTR Switch_GetMapiv(GLenum target, GLenum query, GLint * v)
{
	_ptrc_glGetMapiv = (PFN_PTRC_GLGETMAPIVPROC)IntGetProcAddress("glGetMapiv");
	_ptrc_glGetMapiv(target, query, v);
}

static void CODEGEN_FUNCPTR Switch_GetMaterialfv(GLenum face, GLenum pname, GLfloat * params)
{
	_ptrc_glGetMaterialfv = (PFN_PTRC_GLGETMATERIALFVPROC)IntGetProcAddress("glGetMaterialfv");
	_ptrc_glGetMaterialfv(face, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetMaterialiv(GLenum face, GLenum pname, GLint * params)
{
	_ptrc_glGetMaterialiv = (PFN_PTRC_GLGETMATERIALIVPROC)IntGetProcAddress("glGetMaterialiv");
	_ptrc_glGetMaterialiv(face, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetPixelMapfv(GLenum map, GLfloat * values)
{
	_ptrc_glGetPixelMapfv = (PFN_PTRC_GLGETPIXELMAPFVPROC)IntGetProcAddress("glGetPixelMapfv");
	_ptrc_glGetPixelMapfv(map, values);
}

static void CODEGEN_FUNCPTR Switch_GetPixelMapuiv(GLenum map, GLuint * values)
{
	_ptrc_glGetPixelMapuiv = (PFN_PTRC_GLGETPIXELMAPUIVPROC)IntGetProcAddress("glGetPixelMapuiv");
	_ptrc_glGetPixelMapuiv(map, values);
}

static void CODEGEN_FUNCPTR Switch_GetPixelMapusv(GLenum map, GLushort * values)
{
	_ptrc_glGetPixelMapusv = (PFN_PTRC_GLGETPIXELMAPUSVPROC)IntGetProcAddress("glGetPixelMapusv");
	_ptrc_glGetPixelMapusv(map, values);
}

static void CODEGEN_FUNCPTR Switch_GetPolygonStipple(GLubyte * mask)
{
	_ptrc_glGetPolygonStipple = (PFN_PTRC_GLGETPOLYGONSTIPPLEPROC)IntGetProcAddress("glGetPolygonStipple");
	_ptrc_glGetPolygonStipple(mask);
}

static const GLubyte * CODEGEN_FUNCPTR Switch_GetString(GLenum name)
{
	_ptrc_glGetString = (PFN_PTRC_GLGETSTRINGPROC)IntGetProcAddress("glGetString");
	return _ptrc_glGetString(name);
}

static void CODEGEN_FUNCPTR Switch_GetTexEnvfv(GLenum target, GLenum pname, GLfloat * params)
{
	_ptrc_glGetTexEnvfv = (PFN_PTRC_GLGETTEXENVFVPROC)IntGetProcAddress("glGetTexEnvfv");
	_ptrc_glGetTexEnvfv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTexEnviv(GLenum target, GLenum pname, GLint * params)
{
	_ptrc_glGetTexEnviv = (PFN_PTRC_GLGETTEXENVIVPROC)IntGetProcAddress("glGetTexEnviv");
	_ptrc_glGetTexEnviv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTexGendv(GLenum coord, GLenum pname, GLdouble * params)
{
	_ptrc_glGetTexGendv = (PFN_PTRC_GLGETTEXGENDVPROC)IntGetProcAddress("glGetTexGendv");
	_ptrc_glGetTexGendv(coord, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTexGenfv(GLenum coord, GLenum pname, GLfloat * params)
{
	_ptrc_glGetTexGenfv = (PFN_PTRC_GLGETTEXGENFVPROC)IntGetProcAddress("glGetTexGenfv");
	_ptrc_glGetTexGenfv(coord, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTexGeniv(GLenum coord, GLenum pname, GLint * params)
{
	_ptrc_glGetTexGeniv = (PFN_PTRC_GLGETTEXGENIVPROC)IntGetProcAddress("glGetTexGeniv");
	_ptrc_glGetTexGeniv(coord, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels)
{
	_ptrc_glGetTexImage = (PFN_PTRC_GLGETTEXIMAGEPROC)IntGetProcAddress("glGetTexImage");
	_ptrc_glGetTexImage(target, level, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_GetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params)
{
	_ptrc_glGetTexLevelParameterfv = (PFN_PTRC_GLGETTEXLEVELPARAMETERFVPROC)IntGetProcAddress("glGetTexLevelParameterfv");
	_ptrc_glGetTexLevelParameterfv(target, level, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params)
{
	_ptrc_glGetTexLevelParameteriv = (PFN_PTRC_GLGETTEXLEVELPARAMETERIVPROC)IntGetProcAddress("glGetTexLevelParameteriv");
	_ptrc_glGetTexLevelParameteriv(target, level, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTexParameterfv(GLenum target, GLenum pname, GLfloat * params)
{
	_ptrc_glGetTexParameterfv = (PFN_PTRC_GLGETTEXPARAMETERFVPROC)IntGetProcAddress("glGetTexParameterfv");
	_ptrc_glGetTexParameterfv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTexParameteriv(GLenum target, GLenum pname, GLint * params)
{
	_ptrc_glGetTexParameteriv = (PFN_PTRC_GLGETTEXPARAMETERIVPROC)IntGetProcAddress("glGetTexParameteriv");
	_ptrc_glGetTexParameteriv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_Hint(GLenum target, GLenum mode)
{
	_ptrc_glHint = (PFN_PTRC_GLHINTPROC)IntGetProcAddress("glHint");
	_ptrc_glHint(target, mode);
}

static void CODEGEN_FUNCPTR Switch_IndexMask(GLuint mask)
{
	_ptrc_glIndexMask = (PFN_PTRC_GLINDEXMASKPROC)IntGetProcAddress("glIndexMask");
	_ptrc_glIndexMask(mask);
}

static void CODEGEN_FUNCPTR Switch_Indexd(GLdouble c)
{
	_ptrc_glIndexd = (PFN_PTRC_GLINDEXDPROC)IntGetProcAddress("glIndexd");
	_ptrc_glIndexd(c);
}

static void CODEGEN_FUNCPTR Switch_Indexdv(const GLdouble * c)
{
	_ptrc_glIndexdv = (PFN_PTRC_GLINDEXDVPROC)IntGetProcAddress("glIndexdv");
	_ptrc_glIndexdv(c);
}

static void CODEGEN_FUNCPTR Switch_Indexf(GLfloat c)
{
	_ptrc_glIndexf = (PFN_PTRC_GLINDEXFPROC)IntGetProcAddress("glIndexf");
	_ptrc_glIndexf(c);
}

static void CODEGEN_FUNCPTR Switch_Indexfv(const GLfloat * c)
{
	_ptrc_glIndexfv = (PFN_PTRC_GLINDEXFVPROC)IntGetProcAddress("glIndexfv");
	_ptrc_glIndexfv(c);
}

static void CODEGEN_FUNCPTR Switch_Indexi(GLint c)
{
	_ptrc_glIndexi = (PFN_PTRC_GLINDEXIPROC)IntGetProcAddress("glIndexi");
	_ptrc_glIndexi(c);
}

static void CODEGEN_FUNCPTR Switch_Indexiv(const GLint * c)
{
	_ptrc_glIndexiv = (PFN_PTRC_GLINDEXIVPROC)IntGetProcAddress("glIndexiv");
	_ptrc_glIndexiv(c);
}

static void CODEGEN_FUNCPTR Switch_Indexs(GLshort c)
{
	_ptrc_glIndexs = (PFN_PTRC_GLINDEXSPROC)IntGetProcAddress("glIndexs");
	_ptrc_glIndexs(c);
}

static void CODEGEN_FUNCPTR Switch_Indexsv(const GLshort * c)
{
	_ptrc_glIndexsv = (PFN_PTRC_GLINDEXSVPROC)IntGetProcAddress("glIndexsv");
	_ptrc_glIndexsv(c);
}

static void CODEGEN_FUNCPTR Switch_InitNames(void)
{
	_ptrc_glInitNames = (PFN_PTRC_GLINITNAMESPROC)IntGetProcAddress("glInitNames");
	_ptrc_glInitNames();
}

static GLboolean CODEGEN_FUNCPTR Switch_IsEnabled(GLenum cap)
{
	_ptrc_glIsEnabled = (PFN_PTRC_GLISENABLEDPROC)IntGetProcAddress("glIsEnabled");
	return _ptrc_glIsEnabled(cap);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsList(GLuint list)
{
	_ptrc_glIsList = (PFN_PTRC_GLISLISTPROC)IntGetProcAddress("glIsList");
	return _ptrc_glIsList(list);
}

static void CODEGEN_FUNCPTR Switch_LightModelf(GLenum pname, GLfloat param)
{
	_ptrc_glLightModelf = (PFN_PTRC_GLLIGHTMODELFPROC)IntGetProcAddress("glLightModelf");
	_ptrc_glLightModelf(pname, param);
}

static void CODEGEN_FUNCPTR Switch_LightModelfv(GLenum pname, const GLfloat * params)
{
	_ptrc_glLightModelfv = (PFN_PTRC_GLLIGHTMODELFVPROC)IntGetProcAddress("glLightModelfv");
	_ptrc_glLightModelfv(pname, params);
}

static void CODEGEN_FUNCPTR Switch_LightModeli(GLenum pname, GLint param)
{
	_ptrc_glLightModeli = (PFN_PTRC_GLLIGHTMODELIPROC)IntGetProcAddress("glLightModeli");
	_ptrc_glLightModeli(pname, param);
}

static void CODEGEN_FUNCPTR Switch_LightModeliv(GLenum pname, const GLint * params)
{
	_ptrc_glLightModeliv = (PFN_PTRC_GLLIGHTMODELIVPROC)IntGetProcAddress("glLightModeliv");
	_ptrc_glLightModeliv(pname, params);
}

static void CODEGEN_FUNCPTR Switch_Lightf(GLenum light, GLenum pname, GLfloat param)
{
	_ptrc_glLightf = (PFN_PTRC_GLLIGHTFPROC)IntGetProcAddress("glLightf");
	_ptrc_glLightf(light, pname, param);
}

static void CODEGEN_FUNCPTR Switch_Lightfv(GLenum light, GLenum pname, const GLfloat * params)
{
	_ptrc_glLightfv = (PFN_PTRC_GLLIGHTFVPROC)IntGetProcAddress("glLightfv");
	_ptrc_glLightfv(light, pname, params);
}

static void CODEGEN_FUNCPTR Switch_Lighti(GLenum light, GLenum pname, GLint param)
{
	_ptrc_glLighti = (PFN_PTRC_GLLIGHTIPROC)IntGetProcAddress("glLighti");
	_ptrc_glLighti(light, pname, param);
}

static void CODEGEN_FUNCPTR Switch_Lightiv(GLenum light, GLenum pname, const GLint * params)
{
	_ptrc_glLightiv = (PFN_PTRC_GLLIGHTIVPROC)IntGetProcAddress("glLightiv");
	_ptrc_glLightiv(light, pname, params);
}

static void CODEGEN_FUNCPTR Switch_LineStipple(GLint factor, GLushort pattern)
{
	_ptrc_glLineStipple = (PFN_PTRC_GLLINESTIPPLEPROC)IntGetProcAddress("glLineStipple");
	_ptrc_glLineStipple(factor, pattern);
}

static void CODEGEN_FUNCPTR Switch_LineWidth(GLfloat width)
{
	_ptrc_glLineWidth = (PFN_PTRC_GLLINEWIDTHPROC)IntGetProcAddress("glLineWidth");
	_ptrc_glLineWidth(width);
}

static void CODEGEN_FUNCPTR Switch_ListBase(GLuint base)
{
	_ptrc_glListBase = (PFN_PTRC_GLLISTBASEPROC)IntGetProcAddress("glListBase");
	_ptrc_glListBase(base);
}

static void CODEGEN_FUNCPTR Switch_LoadIdentity(void)
{
	_ptrc_glLoadIdentity = (PFN_PTRC_GLLOADIDENTITYPROC)IntGetProcAddress("glLoadIdentity");
	_ptrc_glLoadIdentity();
}

static void CODEGEN_FUNCPTR Switch_LoadMatrixd(const GLdouble * m)
{
	_ptrc_glLoadMatrixd = (PFN_PTRC_GLLOADMATRIXDPROC)IntGetProcAddress("glLoadMatrixd");
	_ptrc_glLoadMatrixd(m);
}

static void CODEGEN_FUNCPTR Switch_LoadMatrixf(const GLfloat * m)
{
	_ptrc_glLoadMatrixf = (PFN_PTRC_GLLOADMATRIXFPROC)IntGetProcAddress("glLoadMatrixf");
	_ptrc_glLoadMatrixf(m);
}

static void CODEGEN_FUNCPTR Switch_LoadName(GLuint name)
{
	_ptrc_glLoadName = (PFN_PTRC_GLLOADNAMEPROC)IntGetProcAddress("glLoadName");
	_ptrc_glLoadName(name);
}

static void CODEGEN_FUNCPTR Switch_LogicOp(GLenum opcode)
{
	_ptrc_glLogicOp = (PFN_PTRC_GLLOGICOPPROC)IntGetProcAddress("glLogicOp");
	_ptrc_glLogicOp(opcode);
}

static void CODEGEN_FUNCPTR Switch_Map1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points)
{
	_ptrc_glMap1d = (PFN_PTRC_GLMAP1DPROC)IntGetProcAddress("glMap1d");
	_ptrc_glMap1d(target, u1, u2, stride, order, points);
}

static void CODEGEN_FUNCPTR Switch_Map1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points)
{
	_ptrc_glMap1f = (PFN_PTRC_GLMAP1FPROC)IntGetProcAddress("glMap1f");
	_ptrc_glMap1f(target, u1, u2, stride, order, points);
}

static void CODEGEN_FUNCPTR Switch_Map2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points)
{
	_ptrc_glMap2d = (PFN_PTRC_GLMAP2DPROC)IntGetProcAddress("glMap2d");
	_ptrc_glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

static void CODEGEN_FUNCPTR Switch_Map2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points)
{
	_ptrc_glMap2f = (PFN_PTRC_GLMAP2FPROC)IntGetProcAddress("glMap2f");
	_ptrc_glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

static void CODEGEN_FUNCPTR Switch_MapGrid1d(GLint un, GLdouble u1, GLdouble u2)
{
	_ptrc_glMapGrid1d = (PFN_PTRC_GLMAPGRID1DPROC)IntGetProcAddress("glMapGrid1d");
	_ptrc_glMapGrid1d(un, u1, u2);
}

static void CODEGEN_FUNCPTR Switch_MapGrid1f(GLint un, GLfloat u1, GLfloat u2)
{
	_ptrc_glMapGrid1f = (PFN_PTRC_GLMAPGRID1FPROC)IntGetProcAddress("glMapGrid1f");
	_ptrc_glMapGrid1f(un, u1, u2);
}

static void CODEGEN_FUNCPTR Switch_MapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2)
{
	_ptrc_glMapGrid2d = (PFN_PTRC_GLMAPGRID2DPROC)IntGetProcAddress("glMapGrid2d");
	_ptrc_glMapGrid2d(un, u1, u2, vn, v1, v2);
}

static void CODEGEN_FUNCPTR Switch_MapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2)
{
	_ptrc_glMapGrid2f = (PFN_PTRC_GLMAPGRID2FPROC)IntGetProcAddress("glMapGrid2f");
	_ptrc_glMapGrid2f(un, u1, u2, vn, v1, v2);
}

static void CODEGEN_FUNCPTR Switch_Materialf(GLenum face, GLenum pname, GLfloat param)
{
	_ptrc_glMaterialf = (PFN_PTRC_GLMATERIALFPROC)IntGetProcAddress("glMaterialf");
	_ptrc_glMaterialf(face, pname, param);
}

static void CODEGEN_FUNCPTR Switch_Materialfv(GLenum face, GLenum pname, const GLfloat * params)
{
	_ptrc_glMaterialfv = (PFN_PTRC_GLMATERIALFVPROC)IntGetProcAddress("glMaterialfv");
	_ptrc_glMaterialfv(face, pname, params);
}

static void CODEGEN_FUNCPTR Switch_Materiali(GLenum face, GLenum pname, GLint param)
{
	_ptrc_glMateriali = (PFN_PTRC_GLMATERIALIPROC)IntGetProcAddress("glMateriali");
	_ptrc_glMateriali(face, pname, param);
}

static void CODEGEN_FUNCPTR Switch_Materialiv(GLenum face, GLenum pname, const GLint * params)
{
	_ptrc_glMaterialiv = (PFN_PTRC_GLMATERIALIVPROC)IntGetProcAddress("glMaterialiv");
	_ptrc_glMaterialiv(face, pname, params);
}

static void CODEGEN_FUNCPTR Switch_MatrixMode(GLenum mode)
{
	_ptrc_glMatrixMode = (PFN_PTRC_GLMATRIXMODEPROC)IntGetProcAddress("glMatrixMode");
	_ptrc_glMatrixMode(mode);
}

static void CODEGEN_FUNCPTR Switch_MultMatrixd(const GLdouble * m)
{
	_ptrc_glMultMatrixd = (PFN_PTRC_GLMULTMATRIXDPROC)IntGetProcAddress("glMultMatrixd");
	_ptrc_glMultMatrixd(m);
}

static void CODEGEN_FUNCPTR Switch_MultMatrixf(const GLfloat * m)
{
	_ptrc_glMultMatrixf = (PFN_PTRC_GLMULTMATRIXFPROC)IntGetProcAddress("glMultMatrixf");
	_ptrc_glMultMatrixf(m);
}

static void CODEGEN_FUNCPTR Switch_NewList(GLuint list, GLenum mode)
{
	_ptrc_glNewList = (PFN_PTRC_GLNEWLISTPROC)IntGetProcAddress("glNewList");
	_ptrc_glNewList(list, mode);
}

static void CODEGEN_FUNCPTR Switch_Normal3b(GLbyte nx, GLbyte ny, GLbyte nz)
{
	_ptrc_glNormal3b = (PFN_PTRC_GLNORMAL3BPROC)IntGetProcAddress("glNormal3b");
	_ptrc_glNormal3b(nx, ny, nz);
}

static void CODEGEN_FUNCPTR Switch_Normal3bv(const GLbyte * v)
{
	_ptrc_glNormal3bv = (PFN_PTRC_GLNORMAL3BVPROC)IntGetProcAddress("glNormal3bv");
	_ptrc_glNormal3bv(v);
}

static void CODEGEN_FUNCPTR Switch_Normal3d(GLdouble nx, GLdouble ny, GLdouble nz)
{
	_ptrc_glNormal3d = (PFN_PTRC_GLNORMAL3DPROC)IntGetProcAddress("glNormal3d");
	_ptrc_glNormal3d(nx, ny, nz);
}

static void CODEGEN_FUNCPTR Switch_Normal3dv(const GLdouble * v)
{
	_ptrc_glNormal3dv = (PFN_PTRC_GLNORMAL3DVPROC)IntGetProcAddress("glNormal3dv");
	_ptrc_glNormal3dv(v);
}

static void CODEGEN_FUNCPTR Switch_Normal3f(GLfloat nx, GLfloat ny, GLfloat nz)
{
	_ptrc_glNormal3f = (PFN_PTRC_GLNORMAL3FPROC)IntGetProcAddress("glNormal3f");
	_ptrc_glNormal3f(nx, ny, nz);
}

static void CODEGEN_FUNCPTR Switch_Normal3fv(const GLfloat * v)
{
	_ptrc_glNormal3fv = (PFN_PTRC_GLNORMAL3FVPROC)IntGetProcAddress("glNormal3fv");
	_ptrc_glNormal3fv(v);
}

static void CODEGEN_FUNCPTR Switch_Normal3i(GLint nx, GLint ny, GLint nz)
{
	_ptrc_glNormal3i = (PFN_PTRC_GLNORMAL3IPROC)IntGetProcAddress("glNormal3i");
	_ptrc_glNormal3i(nx, ny, nz);
}

static void CODEGEN_FUNCPTR Switch_Normal3iv(const GLint * v)
{
	_ptrc_glNormal3iv = (PFN_PTRC_GLNORMAL3IVPROC)IntGetProcAddress("glNormal3iv");
	_ptrc_glNormal3iv(v);
}

static void CODEGEN_FUNCPTR Switch_Normal3s(GLshort nx, GLshort ny, GLshort nz)
{
	_ptrc_glNormal3s = (PFN_PTRC_GLNORMAL3SPROC)IntGetProcAddress("glNormal3s");
	_ptrc_glNormal3s(nx, ny, nz);
}

static void CODEGEN_FUNCPTR Switch_Normal3sv(const GLshort * v)
{
	_ptrc_glNormal3sv = (PFN_PTRC_GLNORMAL3SVPROC)IntGetProcAddress("glNormal3sv");
	_ptrc_glNormal3sv(v);
}

static void CODEGEN_FUNCPTR Switch_Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
	_ptrc_glOrtho = (PFN_PTRC_GLORTHOPROC)IntGetProcAddress("glOrtho");
	_ptrc_glOrtho(left, right, bottom, top, zNear, zFar);
}

static void CODEGEN_FUNCPTR Switch_PassThrough(GLfloat token)
{
	_ptrc_glPassThrough = (PFN_PTRC_GLPASSTHROUGHPROC)IntGetProcAddress("glPassThrough");
	_ptrc_glPassThrough(token);
}

static void CODEGEN_FUNCPTR Switch_PixelMapfv(GLenum map, GLsizei mapsize, const GLfloat * values)
{
	_ptrc_glPixelMapfv = (PFN_PTRC_GLPIXELMAPFVPROC)IntGetProcAddress("glPixelMapfv");
	_ptrc_glPixelMapfv(map, mapsize, values);
}

static void CODEGEN_FUNCPTR Switch_PixelMapuiv(GLenum map, GLsizei mapsize, const GLuint * values)
{
	_ptrc_glPixelMapuiv = (PFN_PTRC_GLPIXELMAPUIVPROC)IntGetProcAddress("glPixelMapuiv");
	_ptrc_glPixelMapuiv(map, mapsize, values);
}

static void CODEGEN_FUNCPTR Switch_PixelMapusv(GLenum map, GLsizei mapsize, const GLushort * values)
{
	_ptrc_glPixelMapusv = (PFN_PTRC_GLPIXELMAPUSVPROC)IntGetProcAddress("glPixelMapusv");
	_ptrc_glPixelMapusv(map, mapsize, values);
}

static void CODEGEN_FUNCPTR Switch_PixelStoref(GLenum pname, GLfloat param)
{
	_ptrc_glPixelStoref = (PFN_PTRC_GLPIXELSTOREFPROC)IntGetProcAddress("glPixelStoref");
	_ptrc_glPixelStoref(pname, param);
}

static void CODEGEN_FUNCPTR Switch_PixelStorei(GLenum pname, GLint param)
{
	_ptrc_glPixelStorei = (PFN_PTRC_GLPIXELSTOREIPROC)IntGetProcAddress("glPixelStorei");
	_ptrc_glPixelStorei(pname, param);
}

static void CODEGEN_FUNCPTR Switch_PixelTransferf(GLenum pname, GLfloat param)
{
	_ptrc_glPixelTransferf = (PFN_PTRC_GLPIXELTRANSFERFPROC)IntGetProcAddress("glPixelTransferf");
	_ptrc_glPixelTransferf(pname, param);
}

static void CODEGEN_FUNCPTR Switch_PixelTransferi(GLenum pname, GLint param)
{
	_ptrc_glPixelTransferi = (PFN_PTRC_GLPIXELTRANSFERIPROC)IntGetProcAddress("glPixelTransferi");
	_ptrc_glPixelTransferi(pname, param);
}

static void CODEGEN_FUNCPTR Switch_PixelZoom(GLfloat xfactor, GLfloat yfactor)
{
	_ptrc_glPixelZoom = (PFN_PTRC_GLPIXELZOOMPROC)IntGetProcAddress("glPixelZoom");
	_ptrc_glPixelZoom(xfactor, yfactor);
}

static void CODEGEN_FUNCPTR Switch_PointSize(GLfloat size)
{
	_ptrc_glPointSize = (PFN_PTRC_GLPOINTSIZEPROC)IntGetProcAddress("glPointSize");
	_ptrc_glPointSize(size);
}

static void CODEGEN_FUNCPTR Switch_PolygonMode(GLenum face, GLenum mode)
{
	_ptrc_glPolygonMode = (PFN_PTRC_GLPOLYGONMODEPROC)IntGetProcAddress("glPolygonMode");
	_ptrc_glPolygonMode(face, mode);
}

static void CODEGEN_FUNCPTR Switch_PolygonStipple(const GLubyte * mask)
{
	_ptrc_glPolygonStipple = (PFN_PTRC_GLPOLYGONSTIPPLEPROC)IntGetProcAddress("glPolygonStipple");
	_ptrc_glPolygonStipple(mask);
}

static void CODEGEN_FUNCPTR Switch_PopAttrib(void)
{
	_ptrc_glPopAttrib = (PFN_PTRC_GLPOPATTRIBPROC)IntGetProcAddress("glPopAttrib");
	_ptrc_glPopAttrib();
}

static void CODEGEN_FUNCPTR Switch_PopMatrix(void)
{
	_ptrc_glPopMatrix = (PFN_PTRC_GLPOPMATRIXPROC)IntGetProcAddress("glPopMatrix");
	_ptrc_glPopMatrix();
}

static void CODEGEN_FUNCPTR Switch_PopName(void)
{
	_ptrc_glPopName = (PFN_PTRC_GLPOPNAMEPROC)IntGetProcAddress("glPopName");
	_ptrc_glPopName();
}

static void CODEGEN_FUNCPTR Switch_PushAttrib(GLbitfield mask)
{
	_ptrc_glPushAttrib = (PFN_PTRC_GLPUSHATTRIBPROC)IntGetProcAddress("glPushAttrib");
	_ptrc_glPushAttrib(mask);
}

static void CODEGEN_FUNCPTR Switch_PushMatrix(void)
{
	_ptrc_glPushMatrix = (PFN_PTRC_GLPUSHMATRIXPROC)IntGetProcAddress("glPushMatrix");
	_ptrc_glPushMatrix();
}

static void CODEGEN_FUNCPTR Switch_PushName(GLuint name)
{
	_ptrc_glPushName = (PFN_PTRC_GLPUSHNAMEPROC)IntGetProcAddress("glPushName");
	_ptrc_glPushName(name);
}

static void CODEGEN_FUNCPTR Switch_RasterPos2d(GLdouble x, GLdouble y)
{
	_ptrc_glRasterPos2d = (PFN_PTRC_GLRASTERPOS2DPROC)IntGetProcAddress("glRasterPos2d");
	_ptrc_glRasterPos2d(x, y);
}

static void CODEGEN_FUNCPTR Switch_RasterPos2dv(const GLdouble * v)
{
	_ptrc_glRasterPos2dv = (PFN_PTRC_GLRASTERPOS2DVPROC)IntGetProcAddress("glRasterPos2dv");
	_ptrc_glRasterPos2dv(v);
}

static void CODEGEN_FUNCPTR Switch_RasterPos2f(GLfloat x, GLfloat y)
{
	_ptrc_glRasterPos2f = (PFN_PTRC_GLRASTERPOS2FPROC)IntGetProcAddress("glRasterPos2f");
	_ptrc_glRasterPos2f(x, y);
}

static void CODEGEN_FUNCPTR Switch_RasterPos2fv(const GLfloat * v)
{
	_ptrc_glRasterPos2fv = (PFN_PTRC_GLRASTERPOS2FVPROC)IntGetProcAddress("glRasterPos2fv");
	_ptrc_glRasterPos2fv(v);
}

static void CODEGEN_FUNCPTR Switch_RasterPos2i(GLint x, GLint y)
{
	_ptrc_glRasterPos2i = (PFN_PTRC_GLRASTERPOS2IPROC)IntGetProcAddress("glRasterPos2i");
	_ptrc_glRasterPos2i(x, y);
}

static void CODEGEN_FUNCPTR Switch_RasterPos2iv(const GLint * v)
{
	_ptrc_glRasterPos2iv = (PFN_PTRC_GLRASTERPOS2IVPROC)IntGetProcAddress("glRasterPos2iv");
	_ptrc_glRasterPos2iv(v);
}

static void CODEGEN_FUNCPTR Switch_RasterPos2s(GLshort x, GLshort y)
{
	_ptrc_glRasterPos2s = (PFN_PTRC_GLRASTERPOS2SPROC)IntGetProcAddress("glRasterPos2s");
	_ptrc_glRasterPos2s(x, y);
}

static void CODEGEN_FUNCPTR Switch_RasterPos2sv(const GLshort * v)
{
	_ptrc_glRasterPos2sv = (PFN_PTRC_GLRASTERPOS2SVPROC)IntGetProcAddress("glRasterPos2sv");
	_ptrc_glRasterPos2sv(v);
}

static void CODEGEN_FUNCPTR Switch_RasterPos3d(GLdouble x, GLdouble y, GLdouble z)
{
	_ptrc_glRasterPos3d = (PFN_PTRC_GLRASTERPOS3DPROC)IntGetProcAddress("glRasterPos3d");
	_ptrc_glRasterPos3d(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_RasterPos3dv(const GLdouble * v)
{
	_ptrc_glRasterPos3dv = (PFN_PTRC_GLRASTERPOS3DVPROC)IntGetProcAddress("glRasterPos3dv");
	_ptrc_glRasterPos3dv(v);
}

static void CODEGEN_FUNCPTR Switch_RasterPos3f(GLfloat x, GLfloat y, GLfloat z)
{
	_ptrc_glRasterPos3f = (PFN_PTRC_GLRASTERPOS3FPROC)IntGetProcAddress("glRasterPos3f");
	_ptrc_glRasterPos3f(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_RasterPos3fv(const GLfloat * v)
{
	_ptrc_glRasterPos3fv = (PFN_PTRC_GLRASTERPOS3FVPROC)IntGetProcAddress("glRasterPos3fv");
	_ptrc_glRasterPos3fv(v);
}

static void CODEGEN_FUNCPTR Switch_RasterPos3i(GLint x, GLint y, GLint z)
{
	_ptrc_glRasterPos3i = (PFN_PTRC_GLRASTERPOS3IPROC)IntGetProcAddress("glRasterPos3i");
	_ptrc_glRasterPos3i(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_RasterPos3iv(const GLint * v)
{
	_ptrc_glRasterPos3iv = (PFN_PTRC_GLRASTERPOS3IVPROC)IntGetProcAddress("glRasterPos3iv");
	_ptrc_glRasterPos3iv(v);
}

static void CODEGEN_FUNCPTR Switch_RasterPos3s(GLshort x, GLshort y, GLshort z)
{
	_ptrc_glRasterPos3s = (PFN_PTRC_GLRASTERPOS3SPROC)IntGetProcAddress("glRasterPos3s");
	_ptrc_glRasterPos3s(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_RasterPos3sv(const GLshort * v)
{
	_ptrc_glRasterPos3sv = (PFN_PTRC_GLRASTERPOS3SVPROC)IntGetProcAddress("glRasterPos3sv");
	_ptrc_glRasterPos3sv(v);
}

static void CODEGEN_FUNCPTR Switch_RasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	_ptrc_glRasterPos4d = (PFN_PTRC_GLRASTERPOS4DPROC)IntGetProcAddress("glRasterPos4d");
	_ptrc_glRasterPos4d(x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_RasterPos4dv(const GLdouble * v)
{
	_ptrc_glRasterPos4dv = (PFN_PTRC_GLRASTERPOS4DVPROC)IntGetProcAddress("glRasterPos4dv");
	_ptrc_glRasterPos4dv(v);
}

static void CODEGEN_FUNCPTR Switch_RasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_ptrc_glRasterPos4f = (PFN_PTRC_GLRASTERPOS4FPROC)IntGetProcAddress("glRasterPos4f");
	_ptrc_glRasterPos4f(x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_RasterPos4fv(const GLfloat * v)
{
	_ptrc_glRasterPos4fv = (PFN_PTRC_GLRASTERPOS4FVPROC)IntGetProcAddress("glRasterPos4fv");
	_ptrc_glRasterPos4fv(v);
}

static void CODEGEN_FUNCPTR Switch_RasterPos4i(GLint x, GLint y, GLint z, GLint w)
{
	_ptrc_glRasterPos4i = (PFN_PTRC_GLRASTERPOS4IPROC)IntGetProcAddress("glRasterPos4i");
	_ptrc_glRasterPos4i(x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_RasterPos4iv(const GLint * v)
{
	_ptrc_glRasterPos4iv = (PFN_PTRC_GLRASTERPOS4IVPROC)IntGetProcAddress("glRasterPos4iv");
	_ptrc_glRasterPos4iv(v);
}

static void CODEGEN_FUNCPTR Switch_RasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w)
{
	_ptrc_glRasterPos4s = (PFN_PTRC_GLRASTERPOS4SPROC)IntGetProcAddress("glRasterPos4s");
	_ptrc_glRasterPos4s(x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_RasterPos4sv(const GLshort * v)
{
	_ptrc_glRasterPos4sv = (PFN_PTRC_GLRASTERPOS4SVPROC)IntGetProcAddress("glRasterPos4sv");
	_ptrc_glRasterPos4sv(v);
}

static void CODEGEN_FUNCPTR Switch_ReadBuffer(GLenum src)
{
	_ptrc_glReadBuffer = (PFN_PTRC_GLREADBUFFERPROC)IntGetProcAddress("glReadBuffer");
	_ptrc_glReadBuffer(src);
}

static void CODEGEN_FUNCPTR Switch_ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels)
{
	_ptrc_glReadPixels = (PFN_PTRC_GLREADPIXELSPROC)IntGetProcAddress("glReadPixels");
	_ptrc_glReadPixels(x, y, width, height, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_Rectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
	_ptrc_glRectd = (PFN_PTRC_GLRECTDPROC)IntGetProcAddress("glRectd");
	_ptrc_glRectd(x1, y1, x2, y2);
}

static void CODEGEN_FUNCPTR Switch_Rectdv(const GLdouble * v1, const GLdouble * v2)
{
	_ptrc_glRectdv = (PFN_PTRC_GLRECTDVPROC)IntGetProcAddress("glRectdv");
	_ptrc_glRectdv(v1, v2);
}

static void CODEGEN_FUNCPTR Switch_Rectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	_ptrc_glRectf = (PFN_PTRC_GLRECTFPROC)IntGetProcAddress("glRectf");
	_ptrc_glRectf(x1, y1, x2, y2);
}

static void CODEGEN_FUNCPTR Switch_Rectfv(const GLfloat * v1, const GLfloat * v2)
{
	_ptrc_glRectfv = (PFN_PTRC_GLRECTFVPROC)IntGetProcAddress("glRectfv");
	_ptrc_glRectfv(v1, v2);
}

static void CODEGEN_FUNCPTR Switch_Recti(GLint x1, GLint y1, GLint x2, GLint y2)
{
	_ptrc_glRecti = (PFN_PTRC_GLRECTIPROC)IntGetProcAddress("glRecti");
	_ptrc_glRecti(x1, y1, x2, y2);
}

static void CODEGEN_FUNCPTR Switch_Rectiv(const GLint * v1, const GLint * v2)
{
	_ptrc_glRectiv = (PFN_PTRC_GLRECTIVPROC)IntGetProcAddress("glRectiv");
	_ptrc_glRectiv(v1, v2);
}

static void CODEGEN_FUNCPTR Switch_Rects(GLshort x1, GLshort y1, GLshort x2, GLshort y2)
{
	_ptrc_glRects = (PFN_PTRC_GLRECTSPROC)IntGetProcAddress("glRects");
	_ptrc_glRects(x1, y1, x2, y2);
}

static void CODEGEN_FUNCPTR Switch_Rectsv(const GLshort * v1, const GLshort * v2)
{
	_ptrc_glRectsv = (PFN_PTRC_GLRECTSVPROC)IntGetProcAddress("glRectsv");
	_ptrc_glRectsv(v1, v2);
}

static GLint CODEGEN_FUNCPTR Switch_RenderMode(GLenum mode)
{
	_ptrc_glRenderMode = (PFN_PTRC_GLRENDERMODEPROC)IntGetProcAddress("glRenderMode");
	return _ptrc_glRenderMode(mode);
}

static void CODEGEN_FUNCPTR Switch_Rotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
	_ptrc_glRotated = (PFN_PTRC_GLROTATEDPROC)IntGetProcAddress("glRotated");
	_ptrc_glRotated(angle, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_Rotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	_ptrc_glRotatef = (PFN_PTRC_GLROTATEFPROC)IntGetProcAddress("glRotatef");
	_ptrc_glRotatef(angle, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_Scaled(GLdouble x, GLdouble y, GLdouble z)
{
	_ptrc_glScaled = (PFN_PTRC_GLSCALEDPROC)IntGetProcAddress("glScaled");
	_ptrc_glScaled(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_Scalef(GLfloat x, GLfloat y, GLfloat z)
{
	_ptrc_glScalef = (PFN_PTRC_GLSCALEFPROC)IntGetProcAddress("glScalef");
	_ptrc_glScalef(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_Scissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	_ptrc_glScissor = (PFN_PTRC_GLSCISSORPROC)IntGetProcAddress("glScissor");
	_ptrc_glScissor(x, y, width, height);
}

static void CODEGEN_FUNCPTR Switch_SelectBuffer(GLsizei size, GLuint * buffer)
{
	_ptrc_glSelectBuffer = (PFN_PTRC_GLSELECTBUFFERPROC)IntGetProcAddress("glSelectBuffer");
	_ptrc_glSelectBuffer(size, buffer);
}

static void CODEGEN_FUNCPTR Switch_ShadeModel(GLenum mode)
{
	_ptrc_glShadeModel = (PFN_PTRC_GLSHADEMODELPROC)IntGetProcAddress("glShadeModel");
	_ptrc_glShadeModel(mode);
}

static void CODEGEN_FUNCPTR Switch_StencilFunc(GLenum func, GLint ref, GLuint mask)
{
	_ptrc_glStencilFunc = (PFN_PTRC_GLSTENCILFUNCPROC)IntGetProcAddress("glStencilFunc");
	_ptrc_glStencilFunc(func, ref, mask);
}

static void CODEGEN_FUNCPTR Switch_StencilMask(GLuint mask)
{
	_ptrc_glStencilMask = (PFN_PTRC_GLSTENCILMASKPROC)IntGetProcAddress("glStencilMask");
	_ptrc_glStencilMask(mask);
}

static void CODEGEN_FUNCPTR Switch_StencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	_ptrc_glStencilOp = (PFN_PTRC_GLSTENCILOPPROC)IntGetProcAddress("glStencilOp");
	_ptrc_glStencilOp(fail, zfail, zpass);
}

static void CODEGEN_FUNCPTR Switch_TexCoord1d(GLdouble s)
{
	_ptrc_glTexCoord1d = (PFN_PTRC_GLTEXCOORD1DPROC)IntGetProcAddress("glTexCoord1d");
	_ptrc_glTexCoord1d(s);
}

static void CODEGEN_FUNCPTR Switch_TexCoord1dv(const GLdouble * v)
{
	_ptrc_glTexCoord1dv = (PFN_PTRC_GLTEXCOORD1DVPROC)IntGetProcAddress("glTexCoord1dv");
	_ptrc_glTexCoord1dv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord1f(GLfloat s)
{
	_ptrc_glTexCoord1f = (PFN_PTRC_GLTEXCOORD1FPROC)IntGetProcAddress("glTexCoord1f");
	_ptrc_glTexCoord1f(s);
}

static void CODEGEN_FUNCPTR Switch_TexCoord1fv(const GLfloat * v)
{
	_ptrc_glTexCoord1fv = (PFN_PTRC_GLTEXCOORD1FVPROC)IntGetProcAddress("glTexCoord1fv");
	_ptrc_glTexCoord1fv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord1i(GLint s)
{
	_ptrc_glTexCoord1i = (PFN_PTRC_GLTEXCOORD1IPROC)IntGetProcAddress("glTexCoord1i");
	_ptrc_glTexCoord1i(s);
}

static void CODEGEN_FUNCPTR Switch_TexCoord1iv(const GLint * v)
{
	_ptrc_glTexCoord1iv = (PFN_PTRC_GLTEXCOORD1IVPROC)IntGetProcAddress("glTexCoord1iv");
	_ptrc_glTexCoord1iv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord1s(GLshort s)
{
	_ptrc_glTexCoord1s = (PFN_PTRC_GLTEXCOORD1SPROC)IntGetProcAddress("glTexCoord1s");
	_ptrc_glTexCoord1s(s);
}

static void CODEGEN_FUNCPTR Switch_TexCoord1sv(const GLshort * v)
{
	_ptrc_glTexCoord1sv = (PFN_PTRC_GLTEXCOORD1SVPROC)IntGetProcAddress("glTexCoord1sv");
	_ptrc_glTexCoord1sv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord2d(GLdouble s, GLdouble t)
{
	_ptrc_glTexCoord2d = (PFN_PTRC_GLTEXCOORD2DPROC)IntGetProcAddress("glTexCoord2d");
	_ptrc_glTexCoord2d(s, t);
}

static void CODEGEN_FUNCPTR Switch_TexCoord2dv(const GLdouble * v)
{
	_ptrc_glTexCoord2dv = (PFN_PTRC_GLTEXCOORD2DVPROC)IntGetProcAddress("glTexCoord2dv");
	_ptrc_glTexCoord2dv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord2f(GLfloat s, GLfloat t)
{
	_ptrc_glTexCoord2f = (PFN_PTRC_GLTEXCOORD2FPROC)IntGetProcAddress("glTexCoord2f");
	_ptrc_glTexCoord2f(s, t);
}

static void CODEGEN_FUNCPTR Switch_TexCoord2fv(const GLfloat * v)
{
	_ptrc_glTexCoord2fv = (PFN_PTRC_GLTEXCOORD2FVPROC)IntGetProcAddress("glTexCoord2fv");
	_ptrc_glTexCoord2fv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord2i(GLint s, GLint t)
{
	_ptrc_glTexCoord2i = (PFN_PTRC_GLTEXCOORD2IPROC)IntGetProcAddress("glTexCoord2i");
	_ptrc_glTexCoord2i(s, t);
}

static void CODEGEN_FUNCPTR Switch_TexCoord2iv(const GLint * v)
{
	_ptrc_glTexCoord2iv = (PFN_PTRC_GLTEXCOORD2IVPROC)IntGetProcAddress("glTexCoord2iv");
	_ptrc_glTexCoord2iv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord2s(GLshort s, GLshort t)
{
	_ptrc_glTexCoord2s = (PFN_PTRC_GLTEXCOORD2SPROC)IntGetProcAddress("glTexCoord2s");
	_ptrc_glTexCoord2s(s, t);
}

static void CODEGEN_FUNCPTR Switch_TexCoord2sv(const GLshort * v)
{
	_ptrc_glTexCoord2sv = (PFN_PTRC_GLTEXCOORD2SVPROC)IntGetProcAddress("glTexCoord2sv");
	_ptrc_glTexCoord2sv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord3d(GLdouble s, GLdouble t, GLdouble r)
{
	_ptrc_glTexCoord3d = (PFN_PTRC_GLTEXCOORD3DPROC)IntGetProcAddress("glTexCoord3d");
	_ptrc_glTexCoord3d(s, t, r);
}

static void CODEGEN_FUNCPTR Switch_TexCoord3dv(const GLdouble * v)
{
	_ptrc_glTexCoord3dv = (PFN_PTRC_GLTEXCOORD3DVPROC)IntGetProcAddress("glTexCoord3dv");
	_ptrc_glTexCoord3dv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord3f(GLfloat s, GLfloat t, GLfloat r)
{
	_ptrc_glTexCoord3f = (PFN_PTRC_GLTEXCOORD3FPROC)IntGetProcAddress("glTexCoord3f");
	_ptrc_glTexCoord3f(s, t, r);
}

static void CODEGEN_FUNCPTR Switch_TexCoord3fv(const GLfloat * v)
{
	_ptrc_glTexCoord3fv = (PFN_PTRC_GLTEXCOORD3FVPROC)IntGetProcAddress("glTexCoord3fv");
	_ptrc_glTexCoord3fv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord3i(GLint s, GLint t, GLint r)
{
	_ptrc_glTexCoord3i = (PFN_PTRC_GLTEXCOORD3IPROC)IntGetProcAddress("glTexCoord3i");
	_ptrc_glTexCoord3i(s, t, r);
}

static void CODEGEN_FUNCPTR Switch_TexCoord3iv(const GLint * v)
{
	_ptrc_glTexCoord3iv = (PFN_PTRC_GLTEXCOORD3IVPROC)IntGetProcAddress("glTexCoord3iv");
	_ptrc_glTexCoord3iv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord3s(GLshort s, GLshort t, GLshort r)
{
	_ptrc_glTexCoord3s = (PFN_PTRC_GLTEXCOORD3SPROC)IntGetProcAddress("glTexCoord3s");
	_ptrc_glTexCoord3s(s, t, r);
}

static void CODEGEN_FUNCPTR Switch_TexCoord3sv(const GLshort * v)
{
	_ptrc_glTexCoord3sv = (PFN_PTRC_GLTEXCOORD3SVPROC)IntGetProcAddress("glTexCoord3sv");
	_ptrc_glTexCoord3sv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
	_ptrc_glTexCoord4d = (PFN_PTRC_GLTEXCOORD4DPROC)IntGetProcAddress("glTexCoord4d");
	_ptrc_glTexCoord4d(s, t, r, q);
}

static void CODEGEN_FUNCPTR Switch_TexCoord4dv(const GLdouble * v)
{
	_ptrc_glTexCoord4dv = (PFN_PTRC_GLTEXCOORD4DVPROC)IntGetProcAddress("glTexCoord4dv");
	_ptrc_glTexCoord4dv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
	_ptrc_glTexCoord4f = (PFN_PTRC_GLTEXCOORD4FPROC)IntGetProcAddress("glTexCoord4f");
	_ptrc_glTexCoord4f(s, t, r, q);
}

static void CODEGEN_FUNCPTR Switch_TexCoord4fv(const GLfloat * v)
{
	_ptrc_glTexCoord4fv = (PFN_PTRC_GLTEXCOORD4FVPROC)IntGetProcAddress("glTexCoord4fv");
	_ptrc_glTexCoord4fv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord4i(GLint s, GLint t, GLint r, GLint q)
{
	_ptrc_glTexCoord4i = (PFN_PTRC_GLTEXCOORD4IPROC)IntGetProcAddress("glTexCoord4i");
	_ptrc_glTexCoord4i(s, t, r, q);
}

static void CODEGEN_FUNCPTR Switch_TexCoord4iv(const GLint * v)
{
	_ptrc_glTexCoord4iv = (PFN_PTRC_GLTEXCOORD4IVPROC)IntGetProcAddress("glTexCoord4iv");
	_ptrc_glTexCoord4iv(v);
}

static void CODEGEN_FUNCPTR Switch_TexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q)
{
	_ptrc_glTexCoord4s = (PFN_PTRC_GLTEXCOORD4SPROC)IntGetProcAddress("glTexCoord4s");
	_ptrc_glTexCoord4s(s, t, r, q);
}

static void CODEGEN_FUNCPTR Switch_TexCoord4sv(const GLshort * v)
{
	_ptrc_glTexCoord4sv = (PFN_PTRC_GLTEXCOORD4SVPROC)IntGetProcAddress("glTexCoord4sv");
	_ptrc_glTexCoord4sv(v);
}

static void CODEGEN_FUNCPTR Switch_TexEnvf(GLenum target, GLenum pname, GLfloat param)
{
	_ptrc_glTexEnvf = (PFN_PTRC_GLTEXENVFPROC)IntGetProcAddress("glTexEnvf");
	_ptrc_glTexEnvf(target, pname, param);
}

static void CODEGEN_FUNCPTR Switch_TexEnvfv(GLenum target, GLenum pname, const GLfloat * params)
{
	_ptrc_glTexEnvfv = (PFN_PTRC_GLTEXENVFVPROC)IntGetProcAddress("glTexEnvfv");
	_ptrc_glTexEnvfv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_TexEnvi(GLenum target, GLenum pname, GLint param)
{
	_ptrc_glTexEnvi = (PFN_PTRC_GLTEXENVIPROC)IntGetProcAddress("glTexEnvi");
	_ptrc_glTexEnvi(target, pname, param);
}

static void CODEGEN_FUNCPTR Switch_TexEnviv(GLenum target, GLenum pname, const GLint * params)
{
	_ptrc_glTexEnviv = (PFN_PTRC_GLTEXENVIVPROC)IntGetProcAddress("glTexEnviv");
	_ptrc_glTexEnviv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_TexGend(GLenum coord, GLenum pname, GLdouble param)
{
	_ptrc_glTexGend = (PFN_PTRC_GLTEXGENDPROC)IntGetProcAddress("glTexGend");
	_ptrc_glTexGend(coord, pname, param);
}

static void CODEGEN_FUNCPTR Switch_TexGendv(GLenum coord, GLenum pname, const GLdouble * params)
{
	_ptrc_glTexGendv = (PFN_PTRC_GLTEXGENDVPROC)IntGetProcAddress("glTexGendv");
	_ptrc_glTexGendv(coord, pname, params);
}

static void CODEGEN_FUNCPTR Switch_TexGenf(GLenum coord, GLenum pname, GLfloat param)
{
	_ptrc_glTexGenf = (PFN_PTRC_GLTEXGENFPROC)IntGetProcAddress("glTexGenf");
	_ptrc_glTexGenf(coord, pname, param);
}

static void CODEGEN_FUNCPTR Switch_TexGenfv(GLenum coord, GLenum pname, const GLfloat * params)
{
	_ptrc_glTexGenfv = (PFN_PTRC_GLTEXGENFVPROC)IntGetProcAddress("glTexGenfv");
	_ptrc_glTexGenfv(coord, pname, params);
}

static void CODEGEN_FUNCPTR Switch_TexGeni(GLenum coord, GLenum pname, GLint param)
{
	_ptrc_glTexGeni = (PFN_PTRC_GLTEXGENIPROC)IntGetProcAddress("glTexGeni");
	_ptrc_glTexGeni(coord, pname, param);
}

static void CODEGEN_FUNCPTR Switch_TexGeniv(GLenum coord, GLenum pname, const GLint * params)
{
	_ptrc_glTexGeniv = (PFN_PTRC_GLTEXGENIVPROC)IntGetProcAddress("glTexGeniv");
	_ptrc_glTexGeniv(coord, pname, params);
}

static void CODEGEN_FUNCPTR Switch_TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels)
{
	_ptrc_glTexImage1D = (PFN_PTRC_GLTEXIMAGE1DPROC)IntGetProcAddress("glTexImage1D");
	_ptrc_glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels)
{
	_ptrc_glTexImage2D = (PFN_PTRC_GLTEXIMAGE2DPROC)IntGetProcAddress("glTexImage2D");
	_ptrc_glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_TexParameterf(GLenum target, GLenum pname, GLfloat param)
{
	_ptrc_glTexParameterf = (PFN_PTRC_GLTEXPARAMETERFPROC)IntGetProcAddress("glTexParameterf");
	_ptrc_glTexParameterf(target, pname, param);
}

static void CODEGEN_FUNCPTR Switch_TexParameterfv(GLenum target, GLenum pname, const GLfloat * params)
{
	_ptrc_glTexParameterfv = (PFN_PTRC_GLTEXPARAMETERFVPROC)IntGetProcAddress("glTexParameterfv");
	_ptrc_glTexParameterfv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_TexParameteri(GLenum target, GLenum pname, GLint param)
{
	_ptrc_glTexParameteri = (PFN_PTRC_GLTEXPARAMETERIPROC)IntGetProcAddress("glTexParameteri");
	_ptrc_glTexParameteri(target, pname, param);
}

static void CODEGEN_FUNCPTR Switch_TexParameteriv(GLenum target, GLenum pname, const GLint * params)
{
	_ptrc_glTexParameteriv = (PFN_PTRC_GLTEXPARAMETERIVPROC)IntGetProcAddress("glTexParameteriv");
	_ptrc_glTexParameteriv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_Translated(GLdouble x, GLdouble y, GLdouble z)
{
	_ptrc_glTranslated = (PFN_PTRC_GLTRANSLATEDPROC)IntGetProcAddress("glTranslated");
	_ptrc_glTranslated(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_Translatef(GLfloat x, GLfloat y, GLfloat z)
{
	_ptrc_glTranslatef = (PFN_PTRC_GLTRANSLATEFPROC)IntGetProcAddress("glTranslatef");
	_ptrc_glTranslatef(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_Vertex2d(GLdouble x, GLdouble y)
{
	_ptrc_glVertex2d = (PFN_PTRC_GLVERTEX2DPROC)IntGetProcAddress("glVertex2d");
	_ptrc_glVertex2d(x, y);
}

static void CODEGEN_FUNCPTR Switch_Vertex2dv(const GLdouble * v)
{
	_ptrc_glVertex2dv = (PFN_PTRC_GLVERTEX2DVPROC)IntGetProcAddress("glVertex2dv");
	_ptrc_glVertex2dv(v);
}

static void CODEGEN_FUNCPTR Switch_Vertex2f(GLfloat x, GLfloat y)
{
	_ptrc_glVertex2f = (PFN_PTRC_GLVERTEX2FPROC)IntGetProcAddress("glVertex2f");
	_ptrc_glVertex2f(x, y);
}

static void CODEGEN_FUNCPTR Switch_Vertex2fv(const GLfloat * v)
{
	_ptrc_glVertex2fv = (PFN_PTRC_GLVERTEX2FVPROC)IntGetProcAddress("glVertex2fv");
	_ptrc_glVertex2fv(v);
}

static void CODEGEN_FUNCPTR Switch_Vertex2i(GLint x, GLint y)
{
	_ptrc_glVertex2i = (PFN_PTRC_GLVERTEX2IPROC)IntGetProcAddress("glVertex2i");
	_ptrc_glVertex2i(x, y);
}

static void CODEGEN_FUNCPTR Switch_Vertex2iv(const GLint * v)
{
	_ptrc_glVertex2iv = (PFN_PTRC_GLVERTEX2IVPROC)IntGetProcAddress("glVertex2iv");
	_ptrc_glVertex2iv(v);
}

static void CODEGEN_FUNCPTR Switch_Vertex2s(GLshort x, GLshort y)
{
	_ptrc_glVertex2s = (PFN_PTRC_GLVERTEX2SPROC)IntGetProcAddress("glVertex2s");
	_ptrc_glVertex2s(x, y);
}

static void CODEGEN_FUNCPTR Switch_Vertex2sv(const GLshort * v)
{
	_ptrc_glVertex2sv = (PFN_PTRC_GLVERTEX2SVPROC)IntGetProcAddress("glVertex2sv");
	_ptrc_glVertex2sv(v);
}

static void CODEGEN_FUNCPTR Switch_Vertex3d(GLdouble x, GLdouble y, GLdouble z)
{
	_ptrc_glVertex3d = (PFN_PTRC_GLVERTEX3DPROC)IntGetProcAddress("glVertex3d");
	_ptrc_glVertex3d(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_Vertex3dv(const GLdouble * v)
{
	_ptrc_glVertex3dv = (PFN_PTRC_GLVERTEX3DVPROC)IntGetProcAddress("glVertex3dv");
	_ptrc_glVertex3dv(v);
}

static void CODEGEN_FUNCPTR Switch_Vertex3f(GLfloat x, GLfloat y, GLfloat z)
{
	_ptrc_glVertex3f = (PFN_PTRC_GLVERTEX3FPROC)IntGetProcAddress("glVertex3f");
	_ptrc_glVertex3f(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_Vertex3fv(const GLfloat * v)
{
	_ptrc_glVertex3fv = (PFN_PTRC_GLVERTEX3FVPROC)IntGetProcAddress("glVertex3fv");
	_ptrc_glVertex3fv(v);
}

static void CODEGEN_FUNCPTR Switch_Vertex3i(GLint x, GLint y, GLint z)
{
	_ptrc_glVertex3i = (PFN_PTRC_GLVERTEX3IPROC)IntGetProcAddress("glVertex3i");
	_ptrc_glVertex3i(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_Vertex3iv(const GLint * v)
{
	_ptrc_glVertex3iv = (PFN_PTRC_GLVERTEX3IVPROC)IntGetProcAddress("glVertex3iv");
	_ptrc_glVertex3iv(v);
}

static void CODEGEN_FUNCPTR Switch_Vertex3s(GLshort x, GLshort y, GLshort z)
{
	_ptrc_glVertex3s = (PFN_PTRC_GLVERTEX3SPROC)IntGetProcAddress("glVertex3s");
	_ptrc_glVertex3s(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_Vertex3sv(const GLshort * v)
{
	_ptrc_glVertex3sv = (PFN_PTRC_GLVERTEX3SVPROC)IntGetProcAddress("glVertex3sv");
	_ptrc_glVertex3sv(v);
}

static void CODEGEN_FUNCPTR Switch_Vertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	_ptrc_glVertex4d = (PFN_PTRC_GLVERTEX4DPROC)IntGetProcAddress("glVertex4d");
	_ptrc_glVertex4d(x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_Vertex4dv(const GLdouble * v)
{
	_ptrc_glVertex4dv = (PFN_PTRC_GLVERTEX4DVPROC)IntGetProcAddress("glVertex4dv");
	_ptrc_glVertex4dv(v);
}

static void CODEGEN_FUNCPTR Switch_Vertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_ptrc_glVertex4f = (PFN_PTRC_GLVERTEX4FPROC)IntGetProcAddress("glVertex4f");
	_ptrc_glVertex4f(x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_Vertex4fv(const GLfloat * v)
{
	_ptrc_glVertex4fv = (PFN_PTRC_GLVERTEX4FVPROC)IntGetProcAddress("glVertex4fv");
	_ptrc_glVertex4fv(v);
}

static void CODEGEN_FUNCPTR Switch_Vertex4i(GLint x, GLint y, GLint z, GLint w)
{
	_ptrc_glVertex4i = (PFN_PTRC_GLVERTEX4IPROC)IntGetProcAddress("glVertex4i");
	_ptrc_glVertex4i(x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_Vertex4iv(const GLint * v)
{
	_ptrc_glVertex4iv = (PFN_PTRC_GLVERTEX4IVPROC)IntGetProcAddress("glVertex4iv");
	_ptrc_glVertex4iv(v);
}

static void CODEGEN_FUNCPTR Switch_Vertex4s(GLshort x, GLshort y, GLshort z, GLshort w)
{
	_ptrc_glVertex4s = (PFN_PTRC_GLVERTEX4SPROC)IntGetProcAddress("glVertex4s");
	_ptrc_glVertex4s(x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_Vertex4sv(const GLshort * v)
{
	_ptrc_glVertex4sv = (PFN_PTRC_GLVERTEX4SVPROC)IntGetProcAddress("glVertex4sv");
	_ptrc_glVertex4sv(v);
}

static void CODEGEN_FUNCPTR Switch_Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	_ptrc_glViewport = (PFN_PTRC_GLVIEWPORTPROC)IntGetProcAddress("glViewport");
	_ptrc_glViewport(x, y, width, height);
}


/* Extension: 1.1*/
static GLboolean CODEGEN_FUNCPTR Switch_AreTexturesResident(GLsizei n, const GLuint * textures, GLboolean * residences)
{
	_ptrc_glAreTexturesResident = (PFN_PTRC_GLARETEXTURESRESIDENTPROC)IntGetProcAddress("glAreTexturesResident");
	return _ptrc_glAreTexturesResident(n, textures, residences);
}

static void CODEGEN_FUNCPTR Switch_ArrayElement(GLint i)
{
	_ptrc_glArrayElement = (PFN_PTRC_GLARRAYELEMENTPROC)IntGetProcAddress("glArrayElement");
	_ptrc_glArrayElement(i);
}

static void CODEGEN_FUNCPTR Switch_BindTexture(GLenum target, GLuint texture)
{
	_ptrc_glBindTexture = (PFN_PTRC_GLBINDTEXTUREPROC)IntGetProcAddress("glBindTexture");
	_ptrc_glBindTexture(target, texture);
}

static void CODEGEN_FUNCPTR Switch_ColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
	_ptrc_glColorPointer = (PFN_PTRC_GLCOLORPOINTERPROC)IntGetProcAddress("glColorPointer");
	_ptrc_glColorPointer(size, type, stride, pointer);
}

static void CODEGEN_FUNCPTR Switch_CopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
	_ptrc_glCopyTexImage1D = (PFN_PTRC_GLCOPYTEXIMAGE1DPROC)IntGetProcAddress("glCopyTexImage1D");
	_ptrc_glCopyTexImage1D(target, level, internalformat, x, y, width, border);
}

static void CODEGEN_FUNCPTR Switch_CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	_ptrc_glCopyTexImage2D = (PFN_PTRC_GLCOPYTEXIMAGE2DPROC)IntGetProcAddress("glCopyTexImage2D");
	_ptrc_glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

static void CODEGEN_FUNCPTR Switch_CopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
	_ptrc_glCopyTexSubImage1D = (PFN_PTRC_GLCOPYTEXSUBIMAGE1DPROC)IntGetProcAddress("glCopyTexSubImage1D");
	_ptrc_glCopyTexSubImage1D(target, level, xoffset, x, y, width);
}

static void CODEGEN_FUNCPTR Switch_CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_ptrc_glCopyTexSubImage2D = (PFN_PTRC_GLCOPYTEXSUBIMAGE2DPROC)IntGetProcAddress("glCopyTexSubImage2D");
	_ptrc_glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

static void CODEGEN_FUNCPTR Switch_DeleteTextures(GLsizei n, const GLuint * textures)
{
	_ptrc_glDeleteTextures = (PFN_PTRC_GLDELETETEXTURESPROC)IntGetProcAddress("glDeleteTextures");
	_ptrc_glDeleteTextures(n, textures);
}

static void CODEGEN_FUNCPTR Switch_DisableClientState(GLenum ren_array)
{
	_ptrc_glDisableClientState = (PFN_PTRC_GLDISABLECLIENTSTATEPROC)IntGetProcAddress("glDisableClientState");
	_ptrc_glDisableClientState(ren_array);
}

static void CODEGEN_FUNCPTR Switch_DrawArrays(GLenum mode, GLint first, GLsizei count)
{
	_ptrc_glDrawArrays = (PFN_PTRC_GLDRAWARRAYSPROC)IntGetProcAddress("glDrawArrays");
	_ptrc_glDrawArrays(mode, first, count);
}

static void CODEGEN_FUNCPTR Switch_DrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices)
{
	_ptrc_glDrawElements = (PFN_PTRC_GLDRAWELEMENTSPROC)IntGetProcAddress("glDrawElements");
	_ptrc_glDrawElements(mode, count, type, indices);
}

static void CODEGEN_FUNCPTR Switch_EdgeFlagPointer(GLsizei stride, const void * pointer)
{
	_ptrc_glEdgeFlagPointer = (PFN_PTRC_GLEDGEFLAGPOINTERPROC)IntGetProcAddress("glEdgeFlagPointer");
	_ptrc_glEdgeFlagPointer(stride, pointer);
}

static void CODEGEN_FUNCPTR Switch_EnableClientState(GLenum ren_array)
{
	_ptrc_glEnableClientState = (PFN_PTRC_GLENABLECLIENTSTATEPROC)IntGetProcAddress("glEnableClientState");
	_ptrc_glEnableClientState(ren_array);
}

static void CODEGEN_FUNCPTR Switch_GenTextures(GLsizei n, GLuint * textures)
{
	_ptrc_glGenTextures = (PFN_PTRC_GLGENTEXTURESPROC)IntGetProcAddress("glGenTextures");
	_ptrc_glGenTextures(n, textures);
}

static void CODEGEN_FUNCPTR Switch_GetPointerv(GLenum pname, void ** params)
{
	_ptrc_glGetPointerv = (PFN_PTRC_GLGETPOINTERVPROC)IntGetProcAddress("glGetPointerv");
	_ptrc_glGetPointerv(pname, params);
}

static void CODEGEN_FUNCPTR Switch_IndexPointer(GLenum type, GLsizei stride, const void * pointer)
{
	_ptrc_glIndexPointer = (PFN_PTRC_GLINDEXPOINTERPROC)IntGetProcAddress("glIndexPointer");
	_ptrc_glIndexPointer(type, stride, pointer);
}

static void CODEGEN_FUNCPTR Switch_Indexub(GLubyte c)
{
	_ptrc_glIndexub = (PFN_PTRC_GLINDEXUBPROC)IntGetProcAddress("glIndexub");
	_ptrc_glIndexub(c);
}

static void CODEGEN_FUNCPTR Switch_Indexubv(const GLubyte * c)
{
	_ptrc_glIndexubv = (PFN_PTRC_GLINDEXUBVPROC)IntGetProcAddress("glIndexubv");
	_ptrc_glIndexubv(c);
}

static void CODEGEN_FUNCPTR Switch_InterleavedArrays(GLenum format, GLsizei stride, const void * pointer)
{
	_ptrc_glInterleavedArrays = (PFN_PTRC_GLINTERLEAVEDARRAYSPROC)IntGetProcAddress("glInterleavedArrays");
	_ptrc_glInterleavedArrays(format, stride, pointer);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsTexture(GLuint texture)
{
	_ptrc_glIsTexture = (PFN_PTRC_GLISTEXTUREPROC)IntGetProcAddress("glIsTexture");
	return _ptrc_glIsTexture(texture);
}

static void CODEGEN_FUNCPTR Switch_NormalPointer(GLenum type, GLsizei stride, const void * pointer)
{
	_ptrc_glNormalPointer = (PFN_PTRC_GLNORMALPOINTERPROC)IntGetProcAddress("glNormalPointer");
	_ptrc_glNormalPointer(type, stride, pointer);
}

static void CODEGEN_FUNCPTR Switch_PolygonOffset(GLfloat factor, GLfloat units)
{
	_ptrc_glPolygonOffset = (PFN_PTRC_GLPOLYGONOFFSETPROC)IntGetProcAddress("glPolygonOffset");
	_ptrc_glPolygonOffset(factor, units);
}

static void CODEGEN_FUNCPTR Switch_PopClientAttrib(void)
{
	_ptrc_glPopClientAttrib = (PFN_PTRC_GLPOPCLIENTATTRIBPROC)IntGetProcAddress("glPopClientAttrib");
	_ptrc_glPopClientAttrib();
}

static void CODEGEN_FUNCPTR Switch_PrioritizeTextures(GLsizei n, const GLuint * textures, const GLfloat * priorities)
{
	_ptrc_glPrioritizeTextures = (PFN_PTRC_GLPRIORITIZETEXTURESPROC)IntGetProcAddress("glPrioritizeTextures");
	_ptrc_glPrioritizeTextures(n, textures, priorities);
}

static void CODEGEN_FUNCPTR Switch_PushClientAttrib(GLbitfield mask)
{
	_ptrc_glPushClientAttrib = (PFN_PTRC_GLPUSHCLIENTATTRIBPROC)IntGetProcAddress("glPushClientAttrib");
	_ptrc_glPushClientAttrib(mask);
}

static void CODEGEN_FUNCPTR Switch_TexCoordPointer(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
	_ptrc_glTexCoordPointer = (PFN_PTRC_GLTEXCOORDPOINTERPROC)IntGetProcAddress("glTexCoordPointer");
	_ptrc_glTexCoordPointer(size, type, stride, pointer);
}

static void CODEGEN_FUNCPTR Switch_TexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
{
	_ptrc_glTexSubImage1D = (PFN_PTRC_GLTEXSUBIMAGE1DPROC)IntGetProcAddress("glTexSubImage1D");
	_ptrc_glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
{
	_ptrc_glTexSubImage2D = (PFN_PTRC_GLTEXSUBIMAGE2DPROC)IntGetProcAddress("glTexSubImage2D");
	_ptrc_glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_VertexPointer(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
	_ptrc_glVertexPointer = (PFN_PTRC_GLVERTEXPOINTERPROC)IntGetProcAddress("glVertexPointer");
	_ptrc_glVertexPointer(size, type, stride, pointer);
}


/* Extension: 1.2*/
static void CODEGEN_FUNCPTR Switch_CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_ptrc_glCopyTexSubImage3D = (PFN_PTRC_GLCOPYTEXSUBIMAGE3DPROC)IntGetProcAddress("glCopyTexSubImage3D");
	_ptrc_glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

static void CODEGEN_FUNCPTR Switch_DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices)
{
	_ptrc_glDrawRangeElements = (PFN_PTRC_GLDRAWRANGEELEMENTSPROC)IntGetProcAddress("glDrawRangeElements");
	_ptrc_glDrawRangeElements(mode, start, end, count, type, indices);
}

static void CODEGEN_FUNCPTR Switch_TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels)
{
	_ptrc_glTexImage3D = (PFN_PTRC_GLTEXIMAGE3DPROC)IntGetProcAddress("glTexImage3D");
	_ptrc_glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels)
{
	_ptrc_glTexSubImage3D = (PFN_PTRC_GLTEXSUBIMAGE3DPROC)IntGetProcAddress("glTexSubImage3D");
	_ptrc_glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}


/* Extension: 1.3*/
static void CODEGEN_FUNCPTR Switch_ActiveTexture(GLenum texture)
{
	_ptrc_glActiveTexture = (PFN_PTRC_GLACTIVETEXTUREPROC)IntGetProcAddress("glActiveTexture");
	_ptrc_glActiveTexture(texture);
}

static void CODEGEN_FUNCPTR Switch_ClientActiveTexture(GLenum texture)
{
	_ptrc_glClientActiveTexture = (PFN_PTRC_GLCLIENTACTIVETEXTUREPROC)IntGetProcAddress("glClientActiveTexture");
	_ptrc_glClientActiveTexture(texture);
}

static void CODEGEN_FUNCPTR Switch_CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data)
{
	_ptrc_glCompressedTexImage1D = (PFN_PTRC_GLCOMPRESSEDTEXIMAGE1DPROC)IntGetProcAddress("glCompressedTexImage1D");
	_ptrc_glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data)
{
	_ptrc_glCompressedTexImage2D = (PFN_PTRC_GLCOMPRESSEDTEXIMAGE2DPROC)IntGetProcAddress("glCompressedTexImage2D");
	_ptrc_glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data)
{
	_ptrc_glCompressedTexImage3D = (PFN_PTRC_GLCOMPRESSEDTEXIMAGE3DPROC)IntGetProcAddress("glCompressedTexImage3D");
	_ptrc_glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
{
	_ptrc_glCompressedTexSubImage1D = (PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE1DPROC)IntGetProcAddress("glCompressedTexSubImage1D");
	_ptrc_glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
{
	_ptrc_glCompressedTexSubImage2D = (PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE2DPROC)IntGetProcAddress("glCompressedTexSubImage2D");
	_ptrc_glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_CompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data)
{
	_ptrc_glCompressedTexSubImage3D = (PFN_PTRC_GLCOMPRESSEDTEXSUBIMAGE3DPROC)IntGetProcAddress("glCompressedTexSubImage3D");
	_ptrc_glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_GetCompressedTexImage(GLenum target, GLint level, void * img)
{
	_ptrc_glGetCompressedTexImage = (PFN_PTRC_GLGETCOMPRESSEDTEXIMAGEPROC)IntGetProcAddress("glGetCompressedTexImage");
	_ptrc_glGetCompressedTexImage(target, level, img);
}

static void CODEGEN_FUNCPTR Switch_LoadTransposeMatrixd(const GLdouble * m)
{
	_ptrc_glLoadTransposeMatrixd = (PFN_PTRC_GLLOADTRANSPOSEMATRIXDPROC)IntGetProcAddress("glLoadTransposeMatrixd");
	_ptrc_glLoadTransposeMatrixd(m);
}

static void CODEGEN_FUNCPTR Switch_LoadTransposeMatrixf(const GLfloat * m)
{
	_ptrc_glLoadTransposeMatrixf = (PFN_PTRC_GLLOADTRANSPOSEMATRIXFPROC)IntGetProcAddress("glLoadTransposeMatrixf");
	_ptrc_glLoadTransposeMatrixf(m);
}

static void CODEGEN_FUNCPTR Switch_MultTransposeMatrixd(const GLdouble * m)
{
	_ptrc_glMultTransposeMatrixd = (PFN_PTRC_GLMULTTRANSPOSEMATRIXDPROC)IntGetProcAddress("glMultTransposeMatrixd");
	_ptrc_glMultTransposeMatrixd(m);
}

static void CODEGEN_FUNCPTR Switch_MultTransposeMatrixf(const GLfloat * m)
{
	_ptrc_glMultTransposeMatrixf = (PFN_PTRC_GLMULTTRANSPOSEMATRIXFPROC)IntGetProcAddress("glMultTransposeMatrixf");
	_ptrc_glMultTransposeMatrixf(m);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord1d(GLenum target, GLdouble s)
{
	_ptrc_glMultiTexCoord1d = (PFN_PTRC_GLMULTITEXCOORD1DPROC)IntGetProcAddress("glMultiTexCoord1d");
	_ptrc_glMultiTexCoord1d(target, s);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord1dv(GLenum target, const GLdouble * v)
{
	_ptrc_glMultiTexCoord1dv = (PFN_PTRC_GLMULTITEXCOORD1DVPROC)IntGetProcAddress("glMultiTexCoord1dv");
	_ptrc_glMultiTexCoord1dv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord1f(GLenum target, GLfloat s)
{
	_ptrc_glMultiTexCoord1f = (PFN_PTRC_GLMULTITEXCOORD1FPROC)IntGetProcAddress("glMultiTexCoord1f");
	_ptrc_glMultiTexCoord1f(target, s);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord1fv(GLenum target, const GLfloat * v)
{
	_ptrc_glMultiTexCoord1fv = (PFN_PTRC_GLMULTITEXCOORD1FVPROC)IntGetProcAddress("glMultiTexCoord1fv");
	_ptrc_glMultiTexCoord1fv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord1i(GLenum target, GLint s)
{
	_ptrc_glMultiTexCoord1i = (PFN_PTRC_GLMULTITEXCOORD1IPROC)IntGetProcAddress("glMultiTexCoord1i");
	_ptrc_glMultiTexCoord1i(target, s);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord1iv(GLenum target, const GLint * v)
{
	_ptrc_glMultiTexCoord1iv = (PFN_PTRC_GLMULTITEXCOORD1IVPROC)IntGetProcAddress("glMultiTexCoord1iv");
	_ptrc_glMultiTexCoord1iv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord1s(GLenum target, GLshort s)
{
	_ptrc_glMultiTexCoord1s = (PFN_PTRC_GLMULTITEXCOORD1SPROC)IntGetProcAddress("glMultiTexCoord1s");
	_ptrc_glMultiTexCoord1s(target, s);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord1sv(GLenum target, const GLshort * v)
{
	_ptrc_glMultiTexCoord1sv = (PFN_PTRC_GLMULTITEXCOORD1SVPROC)IntGetProcAddress("glMultiTexCoord1sv");
	_ptrc_glMultiTexCoord1sv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord2d(GLenum target, GLdouble s, GLdouble t)
{
	_ptrc_glMultiTexCoord2d = (PFN_PTRC_GLMULTITEXCOORD2DPROC)IntGetProcAddress("glMultiTexCoord2d");
	_ptrc_glMultiTexCoord2d(target, s, t);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord2dv(GLenum target, const GLdouble * v)
{
	_ptrc_glMultiTexCoord2dv = (PFN_PTRC_GLMULTITEXCOORD2DVPROC)IntGetProcAddress("glMultiTexCoord2dv");
	_ptrc_glMultiTexCoord2dv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord2f(GLenum target, GLfloat s, GLfloat t)
{
	_ptrc_glMultiTexCoord2f = (PFN_PTRC_GLMULTITEXCOORD2FPROC)IntGetProcAddress("glMultiTexCoord2f");
	_ptrc_glMultiTexCoord2f(target, s, t);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord2fv(GLenum target, const GLfloat * v)
{
	_ptrc_glMultiTexCoord2fv = (PFN_PTRC_GLMULTITEXCOORD2FVPROC)IntGetProcAddress("glMultiTexCoord2fv");
	_ptrc_glMultiTexCoord2fv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord2i(GLenum target, GLint s, GLint t)
{
	_ptrc_glMultiTexCoord2i = (PFN_PTRC_GLMULTITEXCOORD2IPROC)IntGetProcAddress("glMultiTexCoord2i");
	_ptrc_glMultiTexCoord2i(target, s, t);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord2iv(GLenum target, const GLint * v)
{
	_ptrc_glMultiTexCoord2iv = (PFN_PTRC_GLMULTITEXCOORD2IVPROC)IntGetProcAddress("glMultiTexCoord2iv");
	_ptrc_glMultiTexCoord2iv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord2s(GLenum target, GLshort s, GLshort t)
{
	_ptrc_glMultiTexCoord2s = (PFN_PTRC_GLMULTITEXCOORD2SPROC)IntGetProcAddress("glMultiTexCoord2s");
	_ptrc_glMultiTexCoord2s(target, s, t);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord2sv(GLenum target, const GLshort * v)
{
	_ptrc_glMultiTexCoord2sv = (PFN_PTRC_GLMULTITEXCOORD2SVPROC)IntGetProcAddress("glMultiTexCoord2sv");
	_ptrc_glMultiTexCoord2sv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r)
{
	_ptrc_glMultiTexCoord3d = (PFN_PTRC_GLMULTITEXCOORD3DPROC)IntGetProcAddress("glMultiTexCoord3d");
	_ptrc_glMultiTexCoord3d(target, s, t, r);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord3dv(GLenum target, const GLdouble * v)
{
	_ptrc_glMultiTexCoord3dv = (PFN_PTRC_GLMULTITEXCOORD3DVPROC)IntGetProcAddress("glMultiTexCoord3dv");
	_ptrc_glMultiTexCoord3dv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r)
{
	_ptrc_glMultiTexCoord3f = (PFN_PTRC_GLMULTITEXCOORD3FPROC)IntGetProcAddress("glMultiTexCoord3f");
	_ptrc_glMultiTexCoord3f(target, s, t, r);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord3fv(GLenum target, const GLfloat * v)
{
	_ptrc_glMultiTexCoord3fv = (PFN_PTRC_GLMULTITEXCOORD3FVPROC)IntGetProcAddress("glMultiTexCoord3fv");
	_ptrc_glMultiTexCoord3fv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r)
{
	_ptrc_glMultiTexCoord3i = (PFN_PTRC_GLMULTITEXCOORD3IPROC)IntGetProcAddress("glMultiTexCoord3i");
	_ptrc_glMultiTexCoord3i(target, s, t, r);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord3iv(GLenum target, const GLint * v)
{
	_ptrc_glMultiTexCoord3iv = (PFN_PTRC_GLMULTITEXCOORD3IVPROC)IntGetProcAddress("glMultiTexCoord3iv");
	_ptrc_glMultiTexCoord3iv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r)
{
	_ptrc_glMultiTexCoord3s = (PFN_PTRC_GLMULTITEXCOORD3SPROC)IntGetProcAddress("glMultiTexCoord3s");
	_ptrc_glMultiTexCoord3s(target, s, t, r);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord3sv(GLenum target, const GLshort * v)
{
	_ptrc_glMultiTexCoord3sv = (PFN_PTRC_GLMULTITEXCOORD3SVPROC)IntGetProcAddress("glMultiTexCoord3sv");
	_ptrc_glMultiTexCoord3sv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
	_ptrc_glMultiTexCoord4d = (PFN_PTRC_GLMULTITEXCOORD4DPROC)IntGetProcAddress("glMultiTexCoord4d");
	_ptrc_glMultiTexCoord4d(target, s, t, r, q);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord4dv(GLenum target, const GLdouble * v)
{
	_ptrc_glMultiTexCoord4dv = (PFN_PTRC_GLMULTITEXCOORD4DVPROC)IntGetProcAddress("glMultiTexCoord4dv");
	_ptrc_glMultiTexCoord4dv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
	_ptrc_glMultiTexCoord4f = (PFN_PTRC_GLMULTITEXCOORD4FPROC)IntGetProcAddress("glMultiTexCoord4f");
	_ptrc_glMultiTexCoord4f(target, s, t, r, q);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord4fv(GLenum target, const GLfloat * v)
{
	_ptrc_glMultiTexCoord4fv = (PFN_PTRC_GLMULTITEXCOORD4FVPROC)IntGetProcAddress("glMultiTexCoord4fv");
	_ptrc_glMultiTexCoord4fv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q)
{
	_ptrc_glMultiTexCoord4i = (PFN_PTRC_GLMULTITEXCOORD4IPROC)IntGetProcAddress("glMultiTexCoord4i");
	_ptrc_glMultiTexCoord4i(target, s, t, r, q);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord4iv(GLenum target, const GLint * v)
{
	_ptrc_glMultiTexCoord4iv = (PFN_PTRC_GLMULTITEXCOORD4IVPROC)IntGetProcAddress("glMultiTexCoord4iv");
	_ptrc_glMultiTexCoord4iv(target, v);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)
{
	_ptrc_glMultiTexCoord4s = (PFN_PTRC_GLMULTITEXCOORD4SPROC)IntGetProcAddress("glMultiTexCoord4s");
	_ptrc_glMultiTexCoord4s(target, s, t, r, q);
}

static void CODEGEN_FUNCPTR Switch_MultiTexCoord4sv(GLenum target, const GLshort * v)
{
	_ptrc_glMultiTexCoord4sv = (PFN_PTRC_GLMULTITEXCOORD4SVPROC)IntGetProcAddress("glMultiTexCoord4sv");
	_ptrc_glMultiTexCoord4sv(target, v);
}

static void CODEGEN_FUNCPTR Switch_SampleCoverage(GLfloat value, GLboolean invert)
{
	_ptrc_glSampleCoverage = (PFN_PTRC_GLSAMPLECOVERAGEPROC)IntGetProcAddress("glSampleCoverage");
	_ptrc_glSampleCoverage(value, invert);
}


/* Extension: 1.4*/
static void CODEGEN_FUNCPTR Switch_BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	_ptrc_glBlendColor = (PFN_PTRC_GLBLENDCOLORPROC)IntGetProcAddress("glBlendColor");
	_ptrc_glBlendColor(red, green, blue, alpha);
}

static void CODEGEN_FUNCPTR Switch_BlendEquation(GLenum mode)
{
	_ptrc_glBlendEquation = (PFN_PTRC_GLBLENDEQUATIONPROC)IntGetProcAddress("glBlendEquation");
	_ptrc_glBlendEquation(mode);
}

static void CODEGEN_FUNCPTR Switch_BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
	_ptrc_glBlendFuncSeparate = (PFN_PTRC_GLBLENDFUNCSEPARATEPROC)IntGetProcAddress("glBlendFuncSeparate");
	_ptrc_glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

static void CODEGEN_FUNCPTR Switch_FogCoordPointer(GLenum type, GLsizei stride, const void * pointer)
{
	_ptrc_glFogCoordPointer = (PFN_PTRC_GLFOGCOORDPOINTERPROC)IntGetProcAddress("glFogCoordPointer");
	_ptrc_glFogCoordPointer(type, stride, pointer);
}

static void CODEGEN_FUNCPTR Switch_FogCoordd(GLdouble coord)
{
	_ptrc_glFogCoordd = (PFN_PTRC_GLFOGCOORDDPROC)IntGetProcAddress("glFogCoordd");
	_ptrc_glFogCoordd(coord);
}

static void CODEGEN_FUNCPTR Switch_FogCoorddv(const GLdouble * coord)
{
	_ptrc_glFogCoorddv = (PFN_PTRC_GLFOGCOORDDVPROC)IntGetProcAddress("glFogCoorddv");
	_ptrc_glFogCoorddv(coord);
}

static void CODEGEN_FUNCPTR Switch_FogCoordf(GLfloat coord)
{
	_ptrc_glFogCoordf = (PFN_PTRC_GLFOGCOORDFPROC)IntGetProcAddress("glFogCoordf");
	_ptrc_glFogCoordf(coord);
}

static void CODEGEN_FUNCPTR Switch_FogCoordfv(const GLfloat * coord)
{
	_ptrc_glFogCoordfv = (PFN_PTRC_GLFOGCOORDFVPROC)IntGetProcAddress("glFogCoordfv");
	_ptrc_glFogCoordfv(coord);
}

static void CODEGEN_FUNCPTR Switch_MultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount)
{
	_ptrc_glMultiDrawArrays = (PFN_PTRC_GLMULTIDRAWARRAYSPROC)IntGetProcAddress("glMultiDrawArrays");
	_ptrc_glMultiDrawArrays(mode, first, count, drawcount);
}

static void CODEGEN_FUNCPTR Switch_MultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount)
{
	_ptrc_glMultiDrawElements = (PFN_PTRC_GLMULTIDRAWELEMENTSPROC)IntGetProcAddress("glMultiDrawElements");
	_ptrc_glMultiDrawElements(mode, count, type, indices, drawcount);
}

static void CODEGEN_FUNCPTR Switch_PointParameterf(GLenum pname, GLfloat param)
{
	_ptrc_glPointParameterf = (PFN_PTRC_GLPOINTPARAMETERFPROC)IntGetProcAddress("glPointParameterf");
	_ptrc_glPointParameterf(pname, param);
}

static void CODEGEN_FUNCPTR Switch_PointParameterfv(GLenum pname, const GLfloat * params)
{
	_ptrc_glPointParameterfv = (PFN_PTRC_GLPOINTPARAMETERFVPROC)IntGetProcAddress("glPointParameterfv");
	_ptrc_glPointParameterfv(pname, params);
}

static void CODEGEN_FUNCPTR Switch_PointParameteri(GLenum pname, GLint param)
{
	_ptrc_glPointParameteri = (PFN_PTRC_GLPOINTPARAMETERIPROC)IntGetProcAddress("glPointParameteri");
	_ptrc_glPointParameteri(pname, param);
}

static void CODEGEN_FUNCPTR Switch_PointParameteriv(GLenum pname, const GLint * params)
{
	_ptrc_glPointParameteriv = (PFN_PTRC_GLPOINTPARAMETERIVPROC)IntGetProcAddress("glPointParameteriv");
	_ptrc_glPointParameteriv(pname, params);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue)
{
	_ptrc_glSecondaryColor3b = (PFN_PTRC_GLSECONDARYCOLOR3BPROC)IntGetProcAddress("glSecondaryColor3b");
	_ptrc_glSecondaryColor3b(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3bv(const GLbyte * v)
{
	_ptrc_glSecondaryColor3bv = (PFN_PTRC_GLSECONDARYCOLOR3BVPROC)IntGetProcAddress("glSecondaryColor3bv");
	_ptrc_glSecondaryColor3bv(v);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue)
{
	_ptrc_glSecondaryColor3d = (PFN_PTRC_GLSECONDARYCOLOR3DPROC)IntGetProcAddress("glSecondaryColor3d");
	_ptrc_glSecondaryColor3d(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3dv(const GLdouble * v)
{
	_ptrc_glSecondaryColor3dv = (PFN_PTRC_GLSECONDARYCOLOR3DVPROC)IntGetProcAddress("glSecondaryColor3dv");
	_ptrc_glSecondaryColor3dv(v);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue)
{
	_ptrc_glSecondaryColor3f = (PFN_PTRC_GLSECONDARYCOLOR3FPROC)IntGetProcAddress("glSecondaryColor3f");
	_ptrc_glSecondaryColor3f(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3fv(const GLfloat * v)
{
	_ptrc_glSecondaryColor3fv = (PFN_PTRC_GLSECONDARYCOLOR3FVPROC)IntGetProcAddress("glSecondaryColor3fv");
	_ptrc_glSecondaryColor3fv(v);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3i(GLint red, GLint green, GLint blue)
{
	_ptrc_glSecondaryColor3i = (PFN_PTRC_GLSECONDARYCOLOR3IPROC)IntGetProcAddress("glSecondaryColor3i");
	_ptrc_glSecondaryColor3i(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3iv(const GLint * v)
{
	_ptrc_glSecondaryColor3iv = (PFN_PTRC_GLSECONDARYCOLOR3IVPROC)IntGetProcAddress("glSecondaryColor3iv");
	_ptrc_glSecondaryColor3iv(v);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3s(GLshort red, GLshort green, GLshort blue)
{
	_ptrc_glSecondaryColor3s = (PFN_PTRC_GLSECONDARYCOLOR3SPROC)IntGetProcAddress("glSecondaryColor3s");
	_ptrc_glSecondaryColor3s(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3sv(const GLshort * v)
{
	_ptrc_glSecondaryColor3sv = (PFN_PTRC_GLSECONDARYCOLOR3SVPROC)IntGetProcAddress("glSecondaryColor3sv");
	_ptrc_glSecondaryColor3sv(v);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue)
{
	_ptrc_glSecondaryColor3ub = (PFN_PTRC_GLSECONDARYCOLOR3UBPROC)IntGetProcAddress("glSecondaryColor3ub");
	_ptrc_glSecondaryColor3ub(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3ubv(const GLubyte * v)
{
	_ptrc_glSecondaryColor3ubv = (PFN_PTRC_GLSECONDARYCOLOR3UBVPROC)IntGetProcAddress("glSecondaryColor3ubv");
	_ptrc_glSecondaryColor3ubv(v);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3ui(GLuint red, GLuint green, GLuint blue)
{
	_ptrc_glSecondaryColor3ui = (PFN_PTRC_GLSECONDARYCOLOR3UIPROC)IntGetProcAddress("glSecondaryColor3ui");
	_ptrc_glSecondaryColor3ui(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3uiv(const GLuint * v)
{
	_ptrc_glSecondaryColor3uiv = (PFN_PTRC_GLSECONDARYCOLOR3UIVPROC)IntGetProcAddress("glSecondaryColor3uiv");
	_ptrc_glSecondaryColor3uiv(v);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3us(GLushort red, GLushort green, GLushort blue)
{
	_ptrc_glSecondaryColor3us = (PFN_PTRC_GLSECONDARYCOLOR3USPROC)IntGetProcAddress("glSecondaryColor3us");
	_ptrc_glSecondaryColor3us(red, green, blue);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColor3usv(const GLushort * v)
{
	_ptrc_glSecondaryColor3usv = (PFN_PTRC_GLSECONDARYCOLOR3USVPROC)IntGetProcAddress("glSecondaryColor3usv");
	_ptrc_glSecondaryColor3usv(v);
}

static void CODEGEN_FUNCPTR Switch_SecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
	_ptrc_glSecondaryColorPointer = (PFN_PTRC_GLSECONDARYCOLORPOINTERPROC)IntGetProcAddress("glSecondaryColorPointer");
	_ptrc_glSecondaryColorPointer(size, type, stride, pointer);
}

static void CODEGEN_FUNCPTR Switch_WindowPos2d(GLdouble x, GLdouble y)
{
	_ptrc_glWindowPos2d = (PFN_PTRC_GLWINDOWPOS2DPROC)IntGetProcAddress("glWindowPos2d");
	_ptrc_glWindowPos2d(x, y);
}

static void CODEGEN_FUNCPTR Switch_WindowPos2dv(const GLdouble * v)
{
	_ptrc_glWindowPos2dv = (PFN_PTRC_GLWINDOWPOS2DVPROC)IntGetProcAddress("glWindowPos2dv");
	_ptrc_glWindowPos2dv(v);
}

static void CODEGEN_FUNCPTR Switch_WindowPos2f(GLfloat x, GLfloat y)
{
	_ptrc_glWindowPos2f = (PFN_PTRC_GLWINDOWPOS2FPROC)IntGetProcAddress("glWindowPos2f");
	_ptrc_glWindowPos2f(x, y);
}

static void CODEGEN_FUNCPTR Switch_WindowPos2fv(const GLfloat * v)
{
	_ptrc_glWindowPos2fv = (PFN_PTRC_GLWINDOWPOS2FVPROC)IntGetProcAddress("glWindowPos2fv");
	_ptrc_glWindowPos2fv(v);
}

static void CODEGEN_FUNCPTR Switch_WindowPos2i(GLint x, GLint y)
{
	_ptrc_glWindowPos2i = (PFN_PTRC_GLWINDOWPOS2IPROC)IntGetProcAddress("glWindowPos2i");
	_ptrc_glWindowPos2i(x, y);
}

static void CODEGEN_FUNCPTR Switch_WindowPos2iv(const GLint * v)
{
	_ptrc_glWindowPos2iv = (PFN_PTRC_GLWINDOWPOS2IVPROC)IntGetProcAddress("glWindowPos2iv");
	_ptrc_glWindowPos2iv(v);
}

static void CODEGEN_FUNCPTR Switch_WindowPos2s(GLshort x, GLshort y)
{
	_ptrc_glWindowPos2s = (PFN_PTRC_GLWINDOWPOS2SPROC)IntGetProcAddress("glWindowPos2s");
	_ptrc_glWindowPos2s(x, y);
}

static void CODEGEN_FUNCPTR Switch_WindowPos2sv(const GLshort * v)
{
	_ptrc_glWindowPos2sv = (PFN_PTRC_GLWINDOWPOS2SVPROC)IntGetProcAddress("glWindowPos2sv");
	_ptrc_glWindowPos2sv(v);
}

static void CODEGEN_FUNCPTR Switch_WindowPos3d(GLdouble x, GLdouble y, GLdouble z)
{
	_ptrc_glWindowPos3d = (PFN_PTRC_GLWINDOWPOS3DPROC)IntGetProcAddress("glWindowPos3d");
	_ptrc_glWindowPos3d(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_WindowPos3dv(const GLdouble * v)
{
	_ptrc_glWindowPos3dv = (PFN_PTRC_GLWINDOWPOS3DVPROC)IntGetProcAddress("glWindowPos3dv");
	_ptrc_glWindowPos3dv(v);
}

static void CODEGEN_FUNCPTR Switch_WindowPos3f(GLfloat x, GLfloat y, GLfloat z)
{
	_ptrc_glWindowPos3f = (PFN_PTRC_GLWINDOWPOS3FPROC)IntGetProcAddress("glWindowPos3f");
	_ptrc_glWindowPos3f(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_WindowPos3fv(const GLfloat * v)
{
	_ptrc_glWindowPos3fv = (PFN_PTRC_GLWINDOWPOS3FVPROC)IntGetProcAddress("glWindowPos3fv");
	_ptrc_glWindowPos3fv(v);
}

static void CODEGEN_FUNCPTR Switch_WindowPos3i(GLint x, GLint y, GLint z)
{
	_ptrc_glWindowPos3i = (PFN_PTRC_GLWINDOWPOS3IPROC)IntGetProcAddress("glWindowPos3i");
	_ptrc_glWindowPos3i(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_WindowPos3iv(const GLint * v)
{
	_ptrc_glWindowPos3iv = (PFN_PTRC_GLWINDOWPOS3IVPROC)IntGetProcAddress("glWindowPos3iv");
	_ptrc_glWindowPos3iv(v);
}

static void CODEGEN_FUNCPTR Switch_WindowPos3s(GLshort x, GLshort y, GLshort z)
{
	_ptrc_glWindowPos3s = (PFN_PTRC_GLWINDOWPOS3SPROC)IntGetProcAddress("glWindowPos3s");
	_ptrc_glWindowPos3s(x, y, z);
}

static void CODEGEN_FUNCPTR Switch_WindowPos3sv(const GLshort * v)
{
	_ptrc_glWindowPos3sv = (PFN_PTRC_GLWINDOWPOS3SVPROC)IntGetProcAddress("glWindowPos3sv");
	_ptrc_glWindowPos3sv(v);
}


/* Extension: 1.5*/
static void CODEGEN_FUNCPTR Switch_BeginQuery(GLenum target, GLuint id)
{
	_ptrc_glBeginQuery = (PFN_PTRC_GLBEGINQUERYPROC)IntGetProcAddress("glBeginQuery");
	_ptrc_glBeginQuery(target, id);
}

static void CODEGEN_FUNCPTR Switch_BindBuffer(GLenum target, GLuint buffer)
{
	_ptrc_glBindBuffer = (PFN_PTRC_GLBINDBUFFERPROC)IntGetProcAddress("glBindBuffer");
	_ptrc_glBindBuffer(target, buffer);
}

static void CODEGEN_FUNCPTR Switch_BufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage)
{
	_ptrc_glBufferData = (PFN_PTRC_GLBUFFERDATAPROC)IntGetProcAddress("glBufferData");
	_ptrc_glBufferData(target, size, data, usage);
}

static void CODEGEN_FUNCPTR Switch_BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data)
{
	_ptrc_glBufferSubData = (PFN_PTRC_GLBUFFERSUBDATAPROC)IntGetProcAddress("glBufferSubData");
	_ptrc_glBufferSubData(target, offset, size, data);
}

static void CODEGEN_FUNCPTR Switch_DeleteBuffers(GLsizei n, const GLuint * buffers)
{
	_ptrc_glDeleteBuffers = (PFN_PTRC_GLDELETEBUFFERSPROC)IntGetProcAddress("glDeleteBuffers");
	_ptrc_glDeleteBuffers(n, buffers);
}

static void CODEGEN_FUNCPTR Switch_DeleteQueries(GLsizei n, const GLuint * ids)
{
	_ptrc_glDeleteQueries = (PFN_PTRC_GLDELETEQUERIESPROC)IntGetProcAddress("glDeleteQueries");
	_ptrc_glDeleteQueries(n, ids);
}

static void CODEGEN_FUNCPTR Switch_EndQuery(GLenum target)
{
	_ptrc_glEndQuery = (PFN_PTRC_GLENDQUERYPROC)IntGetProcAddress("glEndQuery");
	_ptrc_glEndQuery(target);
}

static void CODEGEN_FUNCPTR Switch_GenBuffers(GLsizei n, GLuint * buffers)
{
	_ptrc_glGenBuffers = (PFN_PTRC_GLGENBUFFERSPROC)IntGetProcAddress("glGenBuffers");
	_ptrc_glGenBuffers(n, buffers);
}

static void CODEGEN_FUNCPTR Switch_GenQueries(GLsizei n, GLuint * ids)
{
	_ptrc_glGenQueries = (PFN_PTRC_GLGENQUERIESPROC)IntGetProcAddress("glGenQueries");
	_ptrc_glGenQueries(n, ids);
}

static void CODEGEN_FUNCPTR Switch_GetBufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
	_ptrc_glGetBufferParameteriv = (PFN_PTRC_GLGETBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetBufferParameteriv");
	_ptrc_glGetBufferParameteriv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetBufferPointerv(GLenum target, GLenum pname, void ** params)
{
	_ptrc_glGetBufferPointerv = (PFN_PTRC_GLGETBUFFERPOINTERVPROC)IntGetProcAddress("glGetBufferPointerv");
	_ptrc_glGetBufferPointerv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data)
{
	_ptrc_glGetBufferSubData = (PFN_PTRC_GLGETBUFFERSUBDATAPROC)IntGetProcAddress("glGetBufferSubData");
	_ptrc_glGetBufferSubData(target, offset, size, data);
}

static void CODEGEN_FUNCPTR Switch_GetQueryObjectiv(GLuint id, GLenum pname, GLint * params)
{
	_ptrc_glGetQueryObjectiv = (PFN_PTRC_GLGETQUERYOBJECTIVPROC)IntGetProcAddress("glGetQueryObjectiv");
	_ptrc_glGetQueryObjectiv(id, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params)
{
	_ptrc_glGetQueryObjectuiv = (PFN_PTRC_GLGETQUERYOBJECTUIVPROC)IntGetProcAddress("glGetQueryObjectuiv");
	_ptrc_glGetQueryObjectuiv(id, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetQueryiv(GLenum target, GLenum pname, GLint * params)
{
	_ptrc_glGetQueryiv = (PFN_PTRC_GLGETQUERYIVPROC)IntGetProcAddress("glGetQueryiv");
	_ptrc_glGetQueryiv(target, pname, params);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsBuffer(GLuint buffer)
{
	_ptrc_glIsBuffer = (PFN_PTRC_GLISBUFFERPROC)IntGetProcAddress("glIsBuffer");
	return _ptrc_glIsBuffer(buffer);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsQuery(GLuint id)
{
	_ptrc_glIsQuery = (PFN_PTRC_GLISQUERYPROC)IntGetProcAddress("glIsQuery");
	return _ptrc_glIsQuery(id);
}

static void * CODEGEN_FUNCPTR Switch_MapBuffer(GLenum target, GLenum access)
{
	_ptrc_glMapBuffer = (PFN_PTRC_GLMAPBUFFERPROC)IntGetProcAddress("glMapBuffer");
	return _ptrc_glMapBuffer(target, access);
}

static GLboolean CODEGEN_FUNCPTR Switch_UnmapBuffer(GLenum target)
{
	_ptrc_glUnmapBuffer = (PFN_PTRC_GLUNMAPBUFFERPROC)IntGetProcAddress("glUnmapBuffer");
	return _ptrc_glUnmapBuffer(target);
}


/* Extension: 2.0*/
static void CODEGEN_FUNCPTR Switch_AttachShader(GLuint program, GLuint shader)
{
	_ptrc_glAttachShader = (PFN_PTRC_GLATTACHSHADERPROC)IntGetProcAddress("glAttachShader");
	_ptrc_glAttachShader(program, shader);
}

static void CODEGEN_FUNCPTR Switch_BindAttribLocation(GLuint program, GLuint index, const GLchar * name)
{
	_ptrc_glBindAttribLocation = (PFN_PTRC_GLBINDATTRIBLOCATIONPROC)IntGetProcAddress("glBindAttribLocation");
	_ptrc_glBindAttribLocation(program, index, name);
}

static void CODEGEN_FUNCPTR Switch_BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	_ptrc_glBlendEquationSeparate = (PFN_PTRC_GLBLENDEQUATIONSEPARATEPROC)IntGetProcAddress("glBlendEquationSeparate");
	_ptrc_glBlendEquationSeparate(modeRGB, modeAlpha);
}

static void CODEGEN_FUNCPTR Switch_CompileShader(GLuint shader)
{
	_ptrc_glCompileShader = (PFN_PTRC_GLCOMPILESHADERPROC)IntGetProcAddress("glCompileShader");
	_ptrc_glCompileShader(shader);
}

static GLuint CODEGEN_FUNCPTR Switch_CreateProgram(void)
{
	_ptrc_glCreateProgram = (PFN_PTRC_GLCREATEPROGRAMPROC)IntGetProcAddress("glCreateProgram");
	return _ptrc_glCreateProgram();
}

static GLuint CODEGEN_FUNCPTR Switch_CreateShader(GLenum type)
{
	_ptrc_glCreateShader = (PFN_PTRC_GLCREATESHADERPROC)IntGetProcAddress("glCreateShader");
	return _ptrc_glCreateShader(type);
}

static void CODEGEN_FUNCPTR Switch_DeleteProgram(GLuint program)
{
	_ptrc_glDeleteProgram = (PFN_PTRC_GLDELETEPROGRAMPROC)IntGetProcAddress("glDeleteProgram");
	_ptrc_glDeleteProgram(program);
}

static void CODEGEN_FUNCPTR Switch_DeleteShader(GLuint shader)
{
	_ptrc_glDeleteShader = (PFN_PTRC_GLDELETESHADERPROC)IntGetProcAddress("glDeleteShader");
	_ptrc_glDeleteShader(shader);
}

static void CODEGEN_FUNCPTR Switch_DetachShader(GLuint program, GLuint shader)
{
	_ptrc_glDetachShader = (PFN_PTRC_GLDETACHSHADERPROC)IntGetProcAddress("glDetachShader");
	_ptrc_glDetachShader(program, shader);
}

static void CODEGEN_FUNCPTR Switch_DisableVertexAttribArray(GLuint index)
{
	_ptrc_glDisableVertexAttribArray = (PFN_PTRC_GLDISABLEVERTEXATTRIBARRAYPROC)IntGetProcAddress("glDisableVertexAttribArray");
	_ptrc_glDisableVertexAttribArray(index);
}

static void CODEGEN_FUNCPTR Switch_DrawBuffers(GLsizei n, const GLenum * bufs)
{
	_ptrc_glDrawBuffers = (PFN_PTRC_GLDRAWBUFFERSPROC)IntGetProcAddress("glDrawBuffers");
	_ptrc_glDrawBuffers(n, bufs);
}

static void CODEGEN_FUNCPTR Switch_EnableVertexAttribArray(GLuint index)
{
	_ptrc_glEnableVertexAttribArray = (PFN_PTRC_GLENABLEVERTEXATTRIBARRAYPROC)IntGetProcAddress("glEnableVertexAttribArray");
	_ptrc_glEnableVertexAttribArray(index);
}

static void CODEGEN_FUNCPTR Switch_GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
	_ptrc_glGetActiveAttrib = (PFN_PTRC_GLGETACTIVEATTRIBPROC)IntGetProcAddress("glGetActiveAttrib");
	_ptrc_glGetActiveAttrib(program, index, bufSize, length, size, type, name);
}

static void CODEGEN_FUNCPTR Switch_GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
	_ptrc_glGetActiveUniform = (PFN_PTRC_GLGETACTIVEUNIFORMPROC)IntGetProcAddress("glGetActiveUniform");
	_ptrc_glGetActiveUniform(program, index, bufSize, length, size, type, name);
}

static void CODEGEN_FUNCPTR Switch_GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders)
{
	_ptrc_glGetAttachedShaders = (PFN_PTRC_GLGETATTACHEDSHADERSPROC)IntGetProcAddress("glGetAttachedShaders");
	_ptrc_glGetAttachedShaders(program, maxCount, count, shaders);
}

static GLint CODEGEN_FUNCPTR Switch_GetAttribLocation(GLuint program, const GLchar * name)
{
	_ptrc_glGetAttribLocation = (PFN_PTRC_GLGETATTRIBLOCATIONPROC)IntGetProcAddress("glGetAttribLocation");
	return _ptrc_glGetAttribLocation(program, name);
}

static void CODEGEN_FUNCPTR Switch_GetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
	_ptrc_glGetProgramInfoLog = (PFN_PTRC_GLGETPROGRAMINFOLOGPROC)IntGetProcAddress("glGetProgramInfoLog");
	_ptrc_glGetProgramInfoLog(program, bufSize, length, infoLog);
}

static void CODEGEN_FUNCPTR Switch_GetProgramiv(GLuint program, GLenum pname, GLint * params)
{
	_ptrc_glGetProgramiv = (PFN_PTRC_GLGETPROGRAMIVPROC)IntGetProcAddress("glGetProgramiv");
	_ptrc_glGetProgramiv(program, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
	_ptrc_glGetShaderInfoLog = (PFN_PTRC_GLGETSHADERINFOLOGPROC)IntGetProcAddress("glGetShaderInfoLog");
	_ptrc_glGetShaderInfoLog(shader, bufSize, length, infoLog);
}

static void CODEGEN_FUNCPTR Switch_GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source)
{
	_ptrc_glGetShaderSource = (PFN_PTRC_GLGETSHADERSOURCEPROC)IntGetProcAddress("glGetShaderSource");
	_ptrc_glGetShaderSource(shader, bufSize, length, source);
}

static void CODEGEN_FUNCPTR Switch_GetShaderiv(GLuint shader, GLenum pname, GLint * params)
{
	_ptrc_glGetShaderiv = (PFN_PTRC_GLGETSHADERIVPROC)IntGetProcAddress("glGetShaderiv");
	_ptrc_glGetShaderiv(shader, pname, params);
}

static GLint CODEGEN_FUNCPTR Switch_GetUniformLocation(GLuint program, const GLchar * name)
{
	_ptrc_glGetUniformLocation = (PFN_PTRC_GLGETUNIFORMLOCATIONPROC)IntGetProcAddress("glGetUniformLocation");
	return _ptrc_glGetUniformLocation(program, name);
}

static void CODEGEN_FUNCPTR Switch_GetUniformfv(GLuint program, GLint location, GLfloat * params)
{
	_ptrc_glGetUniformfv = (PFN_PTRC_GLGETUNIFORMFVPROC)IntGetProcAddress("glGetUniformfv");
	_ptrc_glGetUniformfv(program, location, params);
}

static void CODEGEN_FUNCPTR Switch_GetUniformiv(GLuint program, GLint location, GLint * params)
{
	_ptrc_glGetUniformiv = (PFN_PTRC_GLGETUNIFORMIVPROC)IntGetProcAddress("glGetUniformiv");
	_ptrc_glGetUniformiv(program, location, params);
}

static void CODEGEN_FUNCPTR Switch_GetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer)
{
	_ptrc_glGetVertexAttribPointerv = (PFN_PTRC_GLGETVERTEXATTRIBPOINTERVPROC)IntGetProcAddress("glGetVertexAttribPointerv");
	_ptrc_glGetVertexAttribPointerv(index, pname, pointer);
}

static void CODEGEN_FUNCPTR Switch_GetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params)
{
	_ptrc_glGetVertexAttribdv = (PFN_PTRC_GLGETVERTEXATTRIBDVPROC)IntGetProcAddress("glGetVertexAttribdv");
	_ptrc_glGetVertexAttribdv(index, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params)
{
	_ptrc_glGetVertexAttribfv = (PFN_PTRC_GLGETVERTEXATTRIBFVPROC)IntGetProcAddress("glGetVertexAttribfv");
	_ptrc_glGetVertexAttribfv(index, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetVertexAttribiv(GLuint index, GLenum pname, GLint * params)
{
	_ptrc_glGetVertexAttribiv = (PFN_PTRC_GLGETVERTEXATTRIBIVPROC)IntGetProcAddress("glGetVertexAttribiv");
	_ptrc_glGetVertexAttribiv(index, pname, params);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsProgram(GLuint program)
{
	_ptrc_glIsProgram = (PFN_PTRC_GLISPROGRAMPROC)IntGetProcAddress("glIsProgram");
	return _ptrc_glIsProgram(program);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsShader(GLuint shader)
{
	_ptrc_glIsShader = (PFN_PTRC_GLISSHADERPROC)IntGetProcAddress("glIsShader");
	return _ptrc_glIsShader(shader);
}

static void CODEGEN_FUNCPTR Switch_LinkProgram(GLuint program)
{
	_ptrc_glLinkProgram = (PFN_PTRC_GLLINKPROGRAMPROC)IntGetProcAddress("glLinkProgram");
	_ptrc_glLinkProgram(program);
}

static void CODEGEN_FUNCPTR Switch_ShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length)
{
	_ptrc_glShaderSource = (PFN_PTRC_GLSHADERSOURCEPROC)IntGetProcAddress("glShaderSource");
	_ptrc_glShaderSource(shader, count, string, length);
}

static void CODEGEN_FUNCPTR Switch_StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	_ptrc_glStencilFuncSeparate = (PFN_PTRC_GLSTENCILFUNCSEPARATEPROC)IntGetProcAddress("glStencilFuncSeparate");
	_ptrc_glStencilFuncSeparate(face, func, ref, mask);
}

static void CODEGEN_FUNCPTR Switch_StencilMaskSeparate(GLenum face, GLuint mask)
{
	_ptrc_glStencilMaskSeparate = (PFN_PTRC_GLSTENCILMASKSEPARATEPROC)IntGetProcAddress("glStencilMaskSeparate");
	_ptrc_glStencilMaskSeparate(face, mask);
}

static void CODEGEN_FUNCPTR Switch_StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
	_ptrc_glStencilOpSeparate = (PFN_PTRC_GLSTENCILOPSEPARATEPROC)IntGetProcAddress("glStencilOpSeparate");
	_ptrc_glStencilOpSeparate(face, sfail, dpfail, dppass);
}

static void CODEGEN_FUNCPTR Switch_Uniform1f(GLint location, GLfloat v0)
{
	_ptrc_glUniform1f = (PFN_PTRC_GLUNIFORM1FPROC)IntGetProcAddress("glUniform1f");
	_ptrc_glUniform1f(location, v0);
}

static void CODEGEN_FUNCPTR Switch_Uniform1fv(GLint location, GLsizei count, const GLfloat * value)
{
	_ptrc_glUniform1fv = (PFN_PTRC_GLUNIFORM1FVPROC)IntGetProcAddress("glUniform1fv");
	_ptrc_glUniform1fv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform1i(GLint location, GLint v0)
{
	_ptrc_glUniform1i = (PFN_PTRC_GLUNIFORM1IPROC)IntGetProcAddress("glUniform1i");
	_ptrc_glUniform1i(location, v0);
}

static void CODEGEN_FUNCPTR Switch_Uniform1iv(GLint location, GLsizei count, const GLint * value)
{
	_ptrc_glUniform1iv = (PFN_PTRC_GLUNIFORM1IVPROC)IntGetProcAddress("glUniform1iv");
	_ptrc_glUniform1iv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform2f(GLint location, GLfloat v0, GLfloat v1)
{
	_ptrc_glUniform2f = (PFN_PTRC_GLUNIFORM2FPROC)IntGetProcAddress("glUniform2f");
	_ptrc_glUniform2f(location, v0, v1);
}

static void CODEGEN_FUNCPTR Switch_Uniform2fv(GLint location, GLsizei count, const GLfloat * value)
{
	_ptrc_glUniform2fv = (PFN_PTRC_GLUNIFORM2FVPROC)IntGetProcAddress("glUniform2fv");
	_ptrc_glUniform2fv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform2i(GLint location, GLint v0, GLint v1)
{
	_ptrc_glUniform2i = (PFN_PTRC_GLUNIFORM2IPROC)IntGetProcAddress("glUniform2i");
	_ptrc_glUniform2i(location, v0, v1);
}

static void CODEGEN_FUNCPTR Switch_Uniform2iv(GLint location, GLsizei count, const GLint * value)
{
	_ptrc_glUniform2iv = (PFN_PTRC_GLUNIFORM2IVPROC)IntGetProcAddress("glUniform2iv");
	_ptrc_glUniform2iv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	_ptrc_glUniform3f = (PFN_PTRC_GLUNIFORM3FPROC)IntGetProcAddress("glUniform3f");
	_ptrc_glUniform3f(location, v0, v1, v2);
}

static void CODEGEN_FUNCPTR Switch_Uniform3fv(GLint location, GLsizei count, const GLfloat * value)
{
	_ptrc_glUniform3fv = (PFN_PTRC_GLUNIFORM3FVPROC)IntGetProcAddress("glUniform3fv");
	_ptrc_glUniform3fv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
	_ptrc_glUniform3i = (PFN_PTRC_GLUNIFORM3IPROC)IntGetProcAddress("glUniform3i");
	_ptrc_glUniform3i(location, v0, v1, v2);
}

static void CODEGEN_FUNCPTR Switch_Uniform3iv(GLint location, GLsizei count, const GLint * value)
{
	_ptrc_glUniform3iv = (PFN_PTRC_GLUNIFORM3IVPROC)IntGetProcAddress("glUniform3iv");
	_ptrc_glUniform3iv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	_ptrc_glUniform4f = (PFN_PTRC_GLUNIFORM4FPROC)IntGetProcAddress("glUniform4f");
	_ptrc_glUniform4f(location, v0, v1, v2, v3);
}

static void CODEGEN_FUNCPTR Switch_Uniform4fv(GLint location, GLsizei count, const GLfloat * value)
{
	_ptrc_glUniform4fv = (PFN_PTRC_GLUNIFORM4FVPROC)IntGetProcAddress("glUniform4fv");
	_ptrc_glUniform4fv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	_ptrc_glUniform4i = (PFN_PTRC_GLUNIFORM4IPROC)IntGetProcAddress("glUniform4i");
	_ptrc_glUniform4i(location, v0, v1, v2, v3);
}

static void CODEGEN_FUNCPTR Switch_Uniform4iv(GLint location, GLsizei count, const GLint * value)
{
	_ptrc_glUniform4iv = (PFN_PTRC_GLUNIFORM4IVPROC)IntGetProcAddress("glUniform4iv");
	_ptrc_glUniform4iv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glUniformMatrix2fv = (PFN_PTRC_GLUNIFORMMATRIX2FVPROC)IntGetProcAddress("glUniformMatrix2fv");
	_ptrc_glUniformMatrix2fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glUniformMatrix3fv = (PFN_PTRC_GLUNIFORMMATRIX3FVPROC)IntGetProcAddress("glUniformMatrix3fv");
	_ptrc_glUniformMatrix3fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glUniformMatrix4fv = (PFN_PTRC_GLUNIFORMMATRIX4FVPROC)IntGetProcAddress("glUniformMatrix4fv");
	_ptrc_glUniformMatrix4fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UseProgram(GLuint program)
{
	_ptrc_glUseProgram = (PFN_PTRC_GLUSEPROGRAMPROC)IntGetProcAddress("glUseProgram");
	_ptrc_glUseProgram(program);
}

static void CODEGEN_FUNCPTR Switch_ValidateProgram(GLuint program)
{
	_ptrc_glValidateProgram = (PFN_PTRC_GLVALIDATEPROGRAMPROC)IntGetProcAddress("glValidateProgram");
	_ptrc_glValidateProgram(program);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib1d(GLuint index, GLdouble x)
{
	_ptrc_glVertexAttrib1d = (PFN_PTRC_GLVERTEXATTRIB1DPROC)IntGetProcAddress("glVertexAttrib1d");
	_ptrc_glVertexAttrib1d(index, x);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib1dv(GLuint index, const GLdouble * v)
{
	_ptrc_glVertexAttrib1dv = (PFN_PTRC_GLVERTEXATTRIB1DVPROC)IntGetProcAddress("glVertexAttrib1dv");
	_ptrc_glVertexAttrib1dv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib1f(GLuint index, GLfloat x)
{
	_ptrc_glVertexAttrib1f = (PFN_PTRC_GLVERTEXATTRIB1FPROC)IntGetProcAddress("glVertexAttrib1f");
	_ptrc_glVertexAttrib1f(index, x);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib1fv(GLuint index, const GLfloat * v)
{
	_ptrc_glVertexAttrib1fv = (PFN_PTRC_GLVERTEXATTRIB1FVPROC)IntGetProcAddress("glVertexAttrib1fv");
	_ptrc_glVertexAttrib1fv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib1s(GLuint index, GLshort x)
{
	_ptrc_glVertexAttrib1s = (PFN_PTRC_GLVERTEXATTRIB1SPROC)IntGetProcAddress("glVertexAttrib1s");
	_ptrc_glVertexAttrib1s(index, x);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib1sv(GLuint index, const GLshort * v)
{
	_ptrc_glVertexAttrib1sv = (PFN_PTRC_GLVERTEXATTRIB1SVPROC)IntGetProcAddress("glVertexAttrib1sv");
	_ptrc_glVertexAttrib1sv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib2d(GLuint index, GLdouble x, GLdouble y)
{
	_ptrc_glVertexAttrib2d = (PFN_PTRC_GLVERTEXATTRIB2DPROC)IntGetProcAddress("glVertexAttrib2d");
	_ptrc_glVertexAttrib2d(index, x, y);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib2dv(GLuint index, const GLdouble * v)
{
	_ptrc_glVertexAttrib2dv = (PFN_PTRC_GLVERTEXATTRIB2DVPROC)IntGetProcAddress("glVertexAttrib2dv");
	_ptrc_glVertexAttrib2dv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
{
	_ptrc_glVertexAttrib2f = (PFN_PTRC_GLVERTEXATTRIB2FPROC)IntGetProcAddress("glVertexAttrib2f");
	_ptrc_glVertexAttrib2f(index, x, y);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib2fv(GLuint index, const GLfloat * v)
{
	_ptrc_glVertexAttrib2fv = (PFN_PTRC_GLVERTEXATTRIB2FVPROC)IntGetProcAddress("glVertexAttrib2fv");
	_ptrc_glVertexAttrib2fv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib2s(GLuint index, GLshort x, GLshort y)
{
	_ptrc_glVertexAttrib2s = (PFN_PTRC_GLVERTEXATTRIB2SPROC)IntGetProcAddress("glVertexAttrib2s");
	_ptrc_glVertexAttrib2s(index, x, y);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib2sv(GLuint index, const GLshort * v)
{
	_ptrc_glVertexAttrib2sv = (PFN_PTRC_GLVERTEXATTRIB2SVPROC)IntGetProcAddress("glVertexAttrib2sv");
	_ptrc_glVertexAttrib2sv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
	_ptrc_glVertexAttrib3d = (PFN_PTRC_GLVERTEXATTRIB3DPROC)IntGetProcAddress("glVertexAttrib3d");
	_ptrc_glVertexAttrib3d(index, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib3dv(GLuint index, const GLdouble * v)
{
	_ptrc_glVertexAttrib3dv = (PFN_PTRC_GLVERTEXATTRIB3DVPROC)IntGetProcAddress("glVertexAttrib3dv");
	_ptrc_glVertexAttrib3dv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
	_ptrc_glVertexAttrib3f = (PFN_PTRC_GLVERTEXATTRIB3FPROC)IntGetProcAddress("glVertexAttrib3f");
	_ptrc_glVertexAttrib3f(index, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib3fv(GLuint index, const GLfloat * v)
{
	_ptrc_glVertexAttrib3fv = (PFN_PTRC_GLVERTEXATTRIB3FVPROC)IntGetProcAddress("glVertexAttrib3fv");
	_ptrc_glVertexAttrib3fv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z)
{
	_ptrc_glVertexAttrib3s = (PFN_PTRC_GLVERTEXATTRIB3SPROC)IntGetProcAddress("glVertexAttrib3s");
	_ptrc_glVertexAttrib3s(index, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib3sv(GLuint index, const GLshort * v)
{
	_ptrc_glVertexAttrib3sv = (PFN_PTRC_GLVERTEXATTRIB3SVPROC)IntGetProcAddress("glVertexAttrib3sv");
	_ptrc_glVertexAttrib3sv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nbv(GLuint index, const GLbyte * v)
{
	_ptrc_glVertexAttrib4Nbv = (PFN_PTRC_GLVERTEXATTRIB4NBVPROC)IntGetProcAddress("glVertexAttrib4Nbv");
	_ptrc_glVertexAttrib4Nbv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Niv(GLuint index, const GLint * v)
{
	_ptrc_glVertexAttrib4Niv = (PFN_PTRC_GLVERTEXATTRIB4NIVPROC)IntGetProcAddress("glVertexAttrib4Niv");
	_ptrc_glVertexAttrib4Niv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nsv(GLuint index, const GLshort * v)
{
	_ptrc_glVertexAttrib4Nsv = (PFN_PTRC_GLVERTEXATTRIB4NSVPROC)IntGetProcAddress("glVertexAttrib4Nsv");
	_ptrc_glVertexAttrib4Nsv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	_ptrc_glVertexAttrib4Nub = (PFN_PTRC_GLVERTEXATTRIB4NUBPROC)IntGetProcAddress("glVertexAttrib4Nub");
	_ptrc_glVertexAttrib4Nub(index, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nubv(GLuint index, const GLubyte * v)
{
	_ptrc_glVertexAttrib4Nubv = (PFN_PTRC_GLVERTEXATTRIB4NUBVPROC)IntGetProcAddress("glVertexAttrib4Nubv");
	_ptrc_glVertexAttrib4Nubv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nuiv(GLuint index, const GLuint * v)
{
	_ptrc_glVertexAttrib4Nuiv = (PFN_PTRC_GLVERTEXATTRIB4NUIVPROC)IntGetProcAddress("glVertexAttrib4Nuiv");
	_ptrc_glVertexAttrib4Nuiv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4Nusv(GLuint index, const GLushort * v)
{
	_ptrc_glVertexAttrib4Nusv = (PFN_PTRC_GLVERTEXATTRIB4NUSVPROC)IntGetProcAddress("glVertexAttrib4Nusv");
	_ptrc_glVertexAttrib4Nusv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4bv(GLuint index, const GLbyte * v)
{
	_ptrc_glVertexAttrib4bv = (PFN_PTRC_GLVERTEXATTRIB4BVPROC)IntGetProcAddress("glVertexAttrib4bv");
	_ptrc_glVertexAttrib4bv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	_ptrc_glVertexAttrib4d = (PFN_PTRC_GLVERTEXATTRIB4DPROC)IntGetProcAddress("glVertexAttrib4d");
	_ptrc_glVertexAttrib4d(index, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4dv(GLuint index, const GLdouble * v)
{
	_ptrc_glVertexAttrib4dv = (PFN_PTRC_GLVERTEXATTRIB4DVPROC)IntGetProcAddress("glVertexAttrib4dv");
	_ptrc_glVertexAttrib4dv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_ptrc_glVertexAttrib4f = (PFN_PTRC_GLVERTEXATTRIB4FPROC)IntGetProcAddress("glVertexAttrib4f");
	_ptrc_glVertexAttrib4f(index, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4fv(GLuint index, const GLfloat * v)
{
	_ptrc_glVertexAttrib4fv = (PFN_PTRC_GLVERTEXATTRIB4FVPROC)IntGetProcAddress("glVertexAttrib4fv");
	_ptrc_glVertexAttrib4fv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4iv(GLuint index, const GLint * v)
{
	_ptrc_glVertexAttrib4iv = (PFN_PTRC_GLVERTEXATTRIB4IVPROC)IntGetProcAddress("glVertexAttrib4iv");
	_ptrc_glVertexAttrib4iv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
	_ptrc_glVertexAttrib4s = (PFN_PTRC_GLVERTEXATTRIB4SPROC)IntGetProcAddress("glVertexAttrib4s");
	_ptrc_glVertexAttrib4s(index, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4sv(GLuint index, const GLshort * v)
{
	_ptrc_glVertexAttrib4sv = (PFN_PTRC_GLVERTEXATTRIB4SVPROC)IntGetProcAddress("glVertexAttrib4sv");
	_ptrc_glVertexAttrib4sv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4ubv(GLuint index, const GLubyte * v)
{
	_ptrc_glVertexAttrib4ubv = (PFN_PTRC_GLVERTEXATTRIB4UBVPROC)IntGetProcAddress("glVertexAttrib4ubv");
	_ptrc_glVertexAttrib4ubv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4uiv(GLuint index, const GLuint * v)
{
	_ptrc_glVertexAttrib4uiv = (PFN_PTRC_GLVERTEXATTRIB4UIVPROC)IntGetProcAddress("glVertexAttrib4uiv");
	_ptrc_glVertexAttrib4uiv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttrib4usv(GLuint index, const GLushort * v)
{
	_ptrc_glVertexAttrib4usv = (PFN_PTRC_GLVERTEXATTRIB4USVPROC)IntGetProcAddress("glVertexAttrib4usv");
	_ptrc_glVertexAttrib4usv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer)
{
	_ptrc_glVertexAttribPointer = (PFN_PTRC_GLVERTEXATTRIBPOINTERPROC)IntGetProcAddress("glVertexAttribPointer");
	_ptrc_glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}


/* Extension: 2.1*/
static void CODEGEN_FUNCPTR Switch_UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glUniformMatrix2x3fv = (PFN_PTRC_GLUNIFORMMATRIX2X3FVPROC)IntGetProcAddress("glUniformMatrix2x3fv");
	_ptrc_glUniformMatrix2x3fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glUniformMatrix2x4fv = (PFN_PTRC_GLUNIFORMMATRIX2X4FVPROC)IntGetProcAddress("glUniformMatrix2x4fv");
	_ptrc_glUniformMatrix2x4fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glUniformMatrix3x2fv = (PFN_PTRC_GLUNIFORMMATRIX3X2FVPROC)IntGetProcAddress("glUniformMatrix3x2fv");
	_ptrc_glUniformMatrix3x2fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glUniformMatrix3x4fv = (PFN_PTRC_GLUNIFORMMATRIX3X4FVPROC)IntGetProcAddress("glUniformMatrix3x4fv");
	_ptrc_glUniformMatrix3x4fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glUniformMatrix4x2fv = (PFN_PTRC_GLUNIFORMMATRIX4X2FVPROC)IntGetProcAddress("glUniformMatrix4x2fv");
	_ptrc_glUniformMatrix4x2fv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glUniformMatrix4x3fv = (PFN_PTRC_GLUNIFORMMATRIX4X3FVPROC)IntGetProcAddress("glUniformMatrix4x3fv");
	_ptrc_glUniformMatrix4x3fv(location, count, transpose, value);
}


/* Extension: 3.0*/
static void CODEGEN_FUNCPTR Switch_BeginConditionalRender(GLuint id, GLenum mode)
{
	_ptrc_glBeginConditionalRender = (PFN_PTRC_GLBEGINCONDITIONALRENDERPROC)IntGetProcAddress("glBeginConditionalRender");
	_ptrc_glBeginConditionalRender(id, mode);
}

static void CODEGEN_FUNCPTR Switch_BeginTransformFeedback(GLenum primitiveMode)
{
	_ptrc_glBeginTransformFeedback = (PFN_PTRC_GLBEGINTRANSFORMFEEDBACKPROC)IntGetProcAddress("glBeginTransformFeedback");
	_ptrc_glBeginTransformFeedback(primitiveMode);
}

static void CODEGEN_FUNCPTR Switch_BindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
	_ptrc_glBindBufferBase = (PFN_PTRC_GLBINDBUFFERBASEPROC)IntGetProcAddress("glBindBufferBase");
	_ptrc_glBindBufferBase(target, index, buffer);
}

static void CODEGEN_FUNCPTR Switch_BindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	_ptrc_glBindBufferRange = (PFN_PTRC_GLBINDBUFFERRANGEPROC)IntGetProcAddress("glBindBufferRange");
	_ptrc_glBindBufferRange(target, index, buffer, offset, size);
}

static void CODEGEN_FUNCPTR Switch_BindFragDataLocation(GLuint program, GLuint color, const GLchar * name)
{
	_ptrc_glBindFragDataLocation = (PFN_PTRC_GLBINDFRAGDATALOCATIONPROC)IntGetProcAddress("glBindFragDataLocation");
	_ptrc_glBindFragDataLocation(program, color, name);
}

static void CODEGEN_FUNCPTR Switch_BindFramebuffer(GLenum target, GLuint framebuffer)
{
	_ptrc_glBindFramebuffer = (PFN_PTRC_GLBINDFRAMEBUFFERPROC)IntGetProcAddress("glBindFramebuffer");
	_ptrc_glBindFramebuffer(target, framebuffer);
}

static void CODEGEN_FUNCPTR Switch_BindRenderbuffer(GLenum target, GLuint renderbuffer)
{
	_ptrc_glBindRenderbuffer = (PFN_PTRC_GLBINDRENDERBUFFERPROC)IntGetProcAddress("glBindRenderbuffer");
	_ptrc_glBindRenderbuffer(target, renderbuffer);
}

static void CODEGEN_FUNCPTR Switch_BindVertexArray(GLuint ren_array)
{
	_ptrc_glBindVertexArray = (PFN_PTRC_GLBINDVERTEXARRAYPROC)IntGetProcAddress("glBindVertexArray");
	_ptrc_glBindVertexArray(ren_array);
}

static void CODEGEN_FUNCPTR Switch_BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
	_ptrc_glBlitFramebuffer = (PFN_PTRC_GLBLITFRAMEBUFFERPROC)IntGetProcAddress("glBlitFramebuffer");
	_ptrc_glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

static GLenum CODEGEN_FUNCPTR Switch_CheckFramebufferStatus(GLenum target)
{
	_ptrc_glCheckFramebufferStatus = (PFN_PTRC_GLCHECKFRAMEBUFFERSTATUSPROC)IntGetProcAddress("glCheckFramebufferStatus");
	return _ptrc_glCheckFramebufferStatus(target);
}

static void CODEGEN_FUNCPTR Switch_ClampColor(GLenum target, GLenum clamp)
{
	_ptrc_glClampColor = (PFN_PTRC_GLCLAMPCOLORPROC)IntGetProcAddress("glClampColor");
	_ptrc_glClampColor(target, clamp);
}

static void CODEGEN_FUNCPTR Switch_ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
	_ptrc_glClearBufferfi = (PFN_PTRC_GLCLEARBUFFERFIPROC)IntGetProcAddress("glClearBufferfi");
	_ptrc_glClearBufferfi(buffer, drawbuffer, depth, stencil);
}

static void CODEGEN_FUNCPTR Switch_ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value)
{
	_ptrc_glClearBufferfv = (PFN_PTRC_GLCLEARBUFFERFVPROC)IntGetProcAddress("glClearBufferfv");
	_ptrc_glClearBufferfv(buffer, drawbuffer, value);
}

static void CODEGEN_FUNCPTR Switch_ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value)
{
	_ptrc_glClearBufferiv = (PFN_PTRC_GLCLEARBUFFERIVPROC)IntGetProcAddress("glClearBufferiv");
	_ptrc_glClearBufferiv(buffer, drawbuffer, value);
}

static void CODEGEN_FUNCPTR Switch_ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value)
{
	_ptrc_glClearBufferuiv = (PFN_PTRC_GLCLEARBUFFERUIVPROC)IntGetProcAddress("glClearBufferuiv");
	_ptrc_glClearBufferuiv(buffer, drawbuffer, value);
}

static void CODEGEN_FUNCPTR Switch_ColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
	_ptrc_glColorMaski = (PFN_PTRC_GLCOLORMASKIPROC)IntGetProcAddress("glColorMaski");
	_ptrc_glColorMaski(index, r, g, b, a);
}

static void CODEGEN_FUNCPTR Switch_DeleteFramebuffers(GLsizei n, const GLuint * framebuffers)
{
	_ptrc_glDeleteFramebuffers = (PFN_PTRC_GLDELETEFRAMEBUFFERSPROC)IntGetProcAddress("glDeleteFramebuffers");
	_ptrc_glDeleteFramebuffers(n, framebuffers);
}

static void CODEGEN_FUNCPTR Switch_DeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers)
{
	_ptrc_glDeleteRenderbuffers = (PFN_PTRC_GLDELETERENDERBUFFERSPROC)IntGetProcAddress("glDeleteRenderbuffers");
	_ptrc_glDeleteRenderbuffers(n, renderbuffers);
}

static void CODEGEN_FUNCPTR Switch_DeleteVertexArrays(GLsizei n, const GLuint * arrays)
{
	_ptrc_glDeleteVertexArrays = (PFN_PTRC_GLDELETEVERTEXARRAYSPROC)IntGetProcAddress("glDeleteVertexArrays");
	_ptrc_glDeleteVertexArrays(n, arrays);
}

static void CODEGEN_FUNCPTR Switch_Disablei(GLenum target, GLuint index)
{
	_ptrc_glDisablei = (PFN_PTRC_GLDISABLEIPROC)IntGetProcAddress("glDisablei");
	_ptrc_glDisablei(target, index);
}

static void CODEGEN_FUNCPTR Switch_Enablei(GLenum target, GLuint index)
{
	_ptrc_glEnablei = (PFN_PTRC_GLENABLEIPROC)IntGetProcAddress("glEnablei");
	_ptrc_glEnablei(target, index);
}

static void CODEGEN_FUNCPTR Switch_EndConditionalRender(void)
{
	_ptrc_glEndConditionalRender = (PFN_PTRC_GLENDCONDITIONALRENDERPROC)IntGetProcAddress("glEndConditionalRender");
	_ptrc_glEndConditionalRender();
}

static void CODEGEN_FUNCPTR Switch_EndTransformFeedback(void)
{
	_ptrc_glEndTransformFeedback = (PFN_PTRC_GLENDTRANSFORMFEEDBACKPROC)IntGetProcAddress("glEndTransformFeedback");
	_ptrc_glEndTransformFeedback();
}

static void CODEGEN_FUNCPTR Switch_FlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
{
	_ptrc_glFlushMappedBufferRange = (PFN_PTRC_GLFLUSHMAPPEDBUFFERRANGEPROC)IntGetProcAddress("glFlushMappedBufferRange");
	_ptrc_glFlushMappedBufferRange(target, offset, length);
}

static void CODEGEN_FUNCPTR Switch_FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	_ptrc_glFramebufferRenderbuffer = (PFN_PTRC_GLFRAMEBUFFERRENDERBUFFERPROC)IntGetProcAddress("glFramebufferRenderbuffer");
	_ptrc_glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

static void CODEGEN_FUNCPTR Switch_FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	_ptrc_glFramebufferTexture1D = (PFN_PTRC_GLFRAMEBUFFERTEXTURE1DPROC)IntGetProcAddress("glFramebufferTexture1D");
	_ptrc_glFramebufferTexture1D(target, attachment, textarget, texture, level);
}

static void CODEGEN_FUNCPTR Switch_FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	_ptrc_glFramebufferTexture2D = (PFN_PTRC_GLFRAMEBUFFERTEXTURE2DPROC)IntGetProcAddress("glFramebufferTexture2D");
	_ptrc_glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

static void CODEGEN_FUNCPTR Switch_FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
	_ptrc_glFramebufferTexture3D = (PFN_PTRC_GLFRAMEBUFFERTEXTURE3DPROC)IntGetProcAddress("glFramebufferTexture3D");
	_ptrc_glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
}

static void CODEGEN_FUNCPTR Switch_FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
	_ptrc_glFramebufferTextureLayer = (PFN_PTRC_GLFRAMEBUFFERTEXTURELAYERPROC)IntGetProcAddress("glFramebufferTextureLayer");
	_ptrc_glFramebufferTextureLayer(target, attachment, texture, level, layer);
}

static void CODEGEN_FUNCPTR Switch_GenFramebuffers(GLsizei n, GLuint * framebuffers)
{
	_ptrc_glGenFramebuffers = (PFN_PTRC_GLGENFRAMEBUFFERSPROC)IntGetProcAddress("glGenFramebuffers");
	_ptrc_glGenFramebuffers(n, framebuffers);
}

static void CODEGEN_FUNCPTR Switch_GenRenderbuffers(GLsizei n, GLuint * renderbuffers)
{
	_ptrc_glGenRenderbuffers = (PFN_PTRC_GLGENRENDERBUFFERSPROC)IntGetProcAddress("glGenRenderbuffers");
	_ptrc_glGenRenderbuffers(n, renderbuffers);
}

static void CODEGEN_FUNCPTR Switch_GenVertexArrays(GLsizei n, GLuint * arrays)
{
	_ptrc_glGenVertexArrays = (PFN_PTRC_GLGENVERTEXARRAYSPROC)IntGetProcAddress("glGenVertexArrays");
	_ptrc_glGenVertexArrays(n, arrays);
}

static void CODEGEN_FUNCPTR Switch_GenerateMipmap(GLenum target)
{
	_ptrc_glGenerateMipmap = (PFN_PTRC_GLGENERATEMIPMAPPROC)IntGetProcAddress("glGenerateMipmap");
	_ptrc_glGenerateMipmap(target);
}

static void CODEGEN_FUNCPTR Switch_GetBooleani_v(GLenum target, GLuint index, GLboolean * data)
{
	_ptrc_glGetBooleani_v = (PFN_PTRC_GLGETBOOLEANI_VPROC)IntGetProcAddress("glGetBooleani_v");
	_ptrc_glGetBooleani_v(target, index, data);
}

static GLint CODEGEN_FUNCPTR Switch_GetFragDataLocation(GLuint program, const GLchar * name)
{
	_ptrc_glGetFragDataLocation = (PFN_PTRC_GLGETFRAGDATALOCATIONPROC)IntGetProcAddress("glGetFragDataLocation");
	return _ptrc_glGetFragDataLocation(program, name);
}

static void CODEGEN_FUNCPTR Switch_GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params)
{
	_ptrc_glGetFramebufferAttachmentParameteriv = (PFN_PTRC_GLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)IntGetProcAddress("glGetFramebufferAttachmentParameteriv");
	_ptrc_glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetIntegeri_v(GLenum target, GLuint index, GLint * data)
{
	_ptrc_glGetIntegeri_v = (PFN_PTRC_GLGETINTEGERI_VPROC)IntGetProcAddress("glGetIntegeri_v");
	_ptrc_glGetIntegeri_v(target, index, data);
}

static void CODEGEN_FUNCPTR Switch_GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
	_ptrc_glGetRenderbufferParameteriv = (PFN_PTRC_GLGETRENDERBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetRenderbufferParameteriv");
	_ptrc_glGetRenderbufferParameteriv(target, pname, params);
}

static const GLubyte * CODEGEN_FUNCPTR Switch_GetStringi(GLenum name, GLuint index)
{
	_ptrc_glGetStringi = (PFN_PTRC_GLGETSTRINGIPROC)IntGetProcAddress("glGetStringi");
	return _ptrc_glGetStringi(name, index);
}

static void CODEGEN_FUNCPTR Switch_GetTexParameterIiv(GLenum target, GLenum pname, GLint * params)
{
	_ptrc_glGetTexParameterIiv = (PFN_PTRC_GLGETTEXPARAMETERIIVPROC)IntGetProcAddress("glGetTexParameterIiv");
	_ptrc_glGetTexParameterIiv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params)
{
	_ptrc_glGetTexParameterIuiv = (PFN_PTRC_GLGETTEXPARAMETERIUIVPROC)IntGetProcAddress("glGetTexParameterIuiv");
	_ptrc_glGetTexParameterIuiv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name)
{
	_ptrc_glGetTransformFeedbackVarying = (PFN_PTRC_GLGETTRANSFORMFEEDBACKVARYINGPROC)IntGetProcAddress("glGetTransformFeedbackVarying");
	_ptrc_glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
}

static void CODEGEN_FUNCPTR Switch_GetUniformuiv(GLuint program, GLint location, GLuint * params)
{
	_ptrc_glGetUniformuiv = (PFN_PTRC_GLGETUNIFORMUIVPROC)IntGetProcAddress("glGetUniformuiv");
	_ptrc_glGetUniformuiv(program, location, params);
}

static void CODEGEN_FUNCPTR Switch_GetVertexAttribIiv(GLuint index, GLenum pname, GLint * params)
{
	_ptrc_glGetVertexAttribIiv = (PFN_PTRC_GLGETVERTEXATTRIBIIVPROC)IntGetProcAddress("glGetVertexAttribIiv");
	_ptrc_glGetVertexAttribIiv(index, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params)
{
	_ptrc_glGetVertexAttribIuiv = (PFN_PTRC_GLGETVERTEXATTRIBIUIVPROC)IntGetProcAddress("glGetVertexAttribIuiv");
	_ptrc_glGetVertexAttribIuiv(index, pname, params);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsEnabledi(GLenum target, GLuint index)
{
	_ptrc_glIsEnabledi = (PFN_PTRC_GLISENABLEDIPROC)IntGetProcAddress("glIsEnabledi");
	return _ptrc_glIsEnabledi(target, index);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsFramebuffer(GLuint framebuffer)
{
	_ptrc_glIsFramebuffer = (PFN_PTRC_GLISFRAMEBUFFERPROC)IntGetProcAddress("glIsFramebuffer");
	return _ptrc_glIsFramebuffer(framebuffer);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsRenderbuffer(GLuint renderbuffer)
{
	_ptrc_glIsRenderbuffer = (PFN_PTRC_GLISRENDERBUFFERPROC)IntGetProcAddress("glIsRenderbuffer");
	return _ptrc_glIsRenderbuffer(renderbuffer);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsVertexArray(GLuint ren_array)
{
	_ptrc_glIsVertexArray = (PFN_PTRC_GLISVERTEXARRAYPROC)IntGetProcAddress("glIsVertexArray");
	return _ptrc_glIsVertexArray(ren_array);
}

static void * CODEGEN_FUNCPTR Switch_MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	_ptrc_glMapBufferRange = (PFN_PTRC_GLMAPBUFFERRANGEPROC)IntGetProcAddress("glMapBufferRange");
	return _ptrc_glMapBufferRange(target, offset, length, access);
}

static void CODEGEN_FUNCPTR Switch_RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	_ptrc_glRenderbufferStorage = (PFN_PTRC_GLRENDERBUFFERSTORAGEPROC)IntGetProcAddress("glRenderbufferStorage");
	_ptrc_glRenderbufferStorage(target, internalformat, width, height);
}

static void CODEGEN_FUNCPTR Switch_RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	_ptrc_glRenderbufferStorageMultisample = (PFN_PTRC_GLRENDERBUFFERSTORAGEMULTISAMPLEPROC)IntGetProcAddress("glRenderbufferStorageMultisample");
	_ptrc_glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}

static void CODEGEN_FUNCPTR Switch_TexParameterIiv(GLenum target, GLenum pname, const GLint * params)
{
	_ptrc_glTexParameterIiv = (PFN_PTRC_GLTEXPARAMETERIIVPROC)IntGetProcAddress("glTexParameterIiv");
	_ptrc_glTexParameterIiv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_TexParameterIuiv(GLenum target, GLenum pname, const GLuint * params)
{
	_ptrc_glTexParameterIuiv = (PFN_PTRC_GLTEXPARAMETERIUIVPROC)IntGetProcAddress("glTexParameterIuiv");
	_ptrc_glTexParameterIuiv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode)
{
	_ptrc_glTransformFeedbackVaryings = (PFN_PTRC_GLTRANSFORMFEEDBACKVARYINGSPROC)IntGetProcAddress("glTransformFeedbackVaryings");
	_ptrc_glTransformFeedbackVaryings(program, count, varyings, bufferMode);
}

static void CODEGEN_FUNCPTR Switch_Uniform1ui(GLint location, GLuint v0)
{
	_ptrc_glUniform1ui = (PFN_PTRC_GLUNIFORM1UIPROC)IntGetProcAddress("glUniform1ui");
	_ptrc_glUniform1ui(location, v0);
}

static void CODEGEN_FUNCPTR Switch_Uniform1uiv(GLint location, GLsizei count, const GLuint * value)
{
	_ptrc_glUniform1uiv = (PFN_PTRC_GLUNIFORM1UIVPROC)IntGetProcAddress("glUniform1uiv");
	_ptrc_glUniform1uiv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform2ui(GLint location, GLuint v0, GLuint v1)
{
	_ptrc_glUniform2ui = (PFN_PTRC_GLUNIFORM2UIPROC)IntGetProcAddress("glUniform2ui");
	_ptrc_glUniform2ui(location, v0, v1);
}

static void CODEGEN_FUNCPTR Switch_Uniform2uiv(GLint location, GLsizei count, const GLuint * value)
{
	_ptrc_glUniform2uiv = (PFN_PTRC_GLUNIFORM2UIVPROC)IntGetProcAddress("glUniform2uiv");
	_ptrc_glUniform2uiv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
	_ptrc_glUniform3ui = (PFN_PTRC_GLUNIFORM3UIPROC)IntGetProcAddress("glUniform3ui");
	_ptrc_glUniform3ui(location, v0, v1, v2);
}

static void CODEGEN_FUNCPTR Switch_Uniform3uiv(GLint location, GLsizei count, const GLuint * value)
{
	_ptrc_glUniform3uiv = (PFN_PTRC_GLUNIFORM3UIVPROC)IntGetProcAddress("glUniform3uiv");
	_ptrc_glUniform3uiv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	_ptrc_glUniform4ui = (PFN_PTRC_GLUNIFORM4UIPROC)IntGetProcAddress("glUniform4ui");
	_ptrc_glUniform4ui(location, v0, v1, v2, v3);
}

static void CODEGEN_FUNCPTR Switch_Uniform4uiv(GLint location, GLsizei count, const GLuint * value)
{
	_ptrc_glUniform4uiv = (PFN_PTRC_GLUNIFORM4UIVPROC)IntGetProcAddress("glUniform4uiv");
	_ptrc_glUniform4uiv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI1i(GLuint index, GLint x)
{
	_ptrc_glVertexAttribI1i = (PFN_PTRC_GLVERTEXATTRIBI1IPROC)IntGetProcAddress("glVertexAttribI1i");
	_ptrc_glVertexAttribI1i(index, x);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI1iv(GLuint index, const GLint * v)
{
	_ptrc_glVertexAttribI1iv = (PFN_PTRC_GLVERTEXATTRIBI1IVPROC)IntGetProcAddress("glVertexAttribI1iv");
	_ptrc_glVertexAttribI1iv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI1ui(GLuint index, GLuint x)
{
	_ptrc_glVertexAttribI1ui = (PFN_PTRC_GLVERTEXATTRIBI1UIPROC)IntGetProcAddress("glVertexAttribI1ui");
	_ptrc_glVertexAttribI1ui(index, x);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI1uiv(GLuint index, const GLuint * v)
{
	_ptrc_glVertexAttribI1uiv = (PFN_PTRC_GLVERTEXATTRIBI1UIVPROC)IntGetProcAddress("glVertexAttribI1uiv");
	_ptrc_glVertexAttribI1uiv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI2i(GLuint index, GLint x, GLint y)
{
	_ptrc_glVertexAttribI2i = (PFN_PTRC_GLVERTEXATTRIBI2IPROC)IntGetProcAddress("glVertexAttribI2i");
	_ptrc_glVertexAttribI2i(index, x, y);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI2iv(GLuint index, const GLint * v)
{
	_ptrc_glVertexAttribI2iv = (PFN_PTRC_GLVERTEXATTRIBI2IVPROC)IntGetProcAddress("glVertexAttribI2iv");
	_ptrc_glVertexAttribI2iv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI2ui(GLuint index, GLuint x, GLuint y)
{
	_ptrc_glVertexAttribI2ui = (PFN_PTRC_GLVERTEXATTRIBI2UIPROC)IntGetProcAddress("glVertexAttribI2ui");
	_ptrc_glVertexAttribI2ui(index, x, y);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI2uiv(GLuint index, const GLuint * v)
{
	_ptrc_glVertexAttribI2uiv = (PFN_PTRC_GLVERTEXATTRIBI2UIVPROC)IntGetProcAddress("glVertexAttribI2uiv");
	_ptrc_glVertexAttribI2uiv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI3i(GLuint index, GLint x, GLint y, GLint z)
{
	_ptrc_glVertexAttribI3i = (PFN_PTRC_GLVERTEXATTRIBI3IPROC)IntGetProcAddress("glVertexAttribI3i");
	_ptrc_glVertexAttribI3i(index, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI3iv(GLuint index, const GLint * v)
{
	_ptrc_glVertexAttribI3iv = (PFN_PTRC_GLVERTEXATTRIBI3IVPROC)IntGetProcAddress("glVertexAttribI3iv");
	_ptrc_glVertexAttribI3iv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z)
{
	_ptrc_glVertexAttribI3ui = (PFN_PTRC_GLVERTEXATTRIBI3UIPROC)IntGetProcAddress("glVertexAttribI3ui");
	_ptrc_glVertexAttribI3ui(index, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI3uiv(GLuint index, const GLuint * v)
{
	_ptrc_glVertexAttribI3uiv = (PFN_PTRC_GLVERTEXATTRIBI3UIVPROC)IntGetProcAddress("glVertexAttribI3uiv");
	_ptrc_glVertexAttribI3uiv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4bv(GLuint index, const GLbyte * v)
{
	_ptrc_glVertexAttribI4bv = (PFN_PTRC_GLVERTEXATTRIBI4BVPROC)IntGetProcAddress("glVertexAttribI4bv");
	_ptrc_glVertexAttribI4bv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
	_ptrc_glVertexAttribI4i = (PFN_PTRC_GLVERTEXATTRIBI4IPROC)IntGetProcAddress("glVertexAttribI4i");
	_ptrc_glVertexAttribI4i(index, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4iv(GLuint index, const GLint * v)
{
	_ptrc_glVertexAttribI4iv = (PFN_PTRC_GLVERTEXATTRIBI4IVPROC)IntGetProcAddress("glVertexAttribI4iv");
	_ptrc_glVertexAttribI4iv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4sv(GLuint index, const GLshort * v)
{
	_ptrc_glVertexAttribI4sv = (PFN_PTRC_GLVERTEXATTRIBI4SVPROC)IntGetProcAddress("glVertexAttribI4sv");
	_ptrc_glVertexAttribI4sv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4ubv(GLuint index, const GLubyte * v)
{
	_ptrc_glVertexAttribI4ubv = (PFN_PTRC_GLVERTEXATTRIBI4UBVPROC)IntGetProcAddress("glVertexAttribI4ubv");
	_ptrc_glVertexAttribI4ubv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
	_ptrc_glVertexAttribI4ui = (PFN_PTRC_GLVERTEXATTRIBI4UIPROC)IntGetProcAddress("glVertexAttribI4ui");
	_ptrc_glVertexAttribI4ui(index, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4uiv(GLuint index, const GLuint * v)
{
	_ptrc_glVertexAttribI4uiv = (PFN_PTRC_GLVERTEXATTRIBI4UIVPROC)IntGetProcAddress("glVertexAttribI4uiv");
	_ptrc_glVertexAttribI4uiv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribI4usv(GLuint index, const GLushort * v)
{
	_ptrc_glVertexAttribI4usv = (PFN_PTRC_GLVERTEXATTRIBI4USVPROC)IntGetProcAddress("glVertexAttribI4usv");
	_ptrc_glVertexAttribI4usv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer)
{
	_ptrc_glVertexAttribIPointer = (PFN_PTRC_GLVERTEXATTRIBIPOINTERPROC)IntGetProcAddress("glVertexAttribIPointer");
	_ptrc_glVertexAttribIPointer(index, size, type, stride, pointer);
}


/* Extension: 3.1*/
static void CODEGEN_FUNCPTR Switch_CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
	_ptrc_glCopyBufferSubData = (PFN_PTRC_GLCOPYBUFFERSUBDATAPROC)IntGetProcAddress("glCopyBufferSubData");
	_ptrc_glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
}

static void CODEGEN_FUNCPTR Switch_DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
{
	_ptrc_glDrawArraysInstanced = (PFN_PTRC_GLDRAWARRAYSINSTANCEDPROC)IntGetProcAddress("glDrawArraysInstanced");
	_ptrc_glDrawArraysInstanced(mode, first, count, instancecount);
}

static void CODEGEN_FUNCPTR Switch_DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount)
{
	_ptrc_glDrawElementsInstanced = (PFN_PTRC_GLDRAWELEMENTSINSTANCEDPROC)IntGetProcAddress("glDrawElementsInstanced");
	_ptrc_glDrawElementsInstanced(mode, count, type, indices, instancecount);
}

static void CODEGEN_FUNCPTR Switch_GetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName)
{
	_ptrc_glGetActiveUniformBlockName = (PFN_PTRC_GLGETACTIVEUNIFORMBLOCKNAMEPROC)IntGetProcAddress("glGetActiveUniformBlockName");
	_ptrc_glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
}

static void CODEGEN_FUNCPTR Switch_GetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params)
{
	_ptrc_glGetActiveUniformBlockiv = (PFN_PTRC_GLGETACTIVEUNIFORMBLOCKIVPROC)IntGetProcAddress("glGetActiveUniformBlockiv");
	_ptrc_glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName)
{
	_ptrc_glGetActiveUniformName = (PFN_PTRC_GLGETACTIVEUNIFORMNAMEPROC)IntGetProcAddress("glGetActiveUniformName");
	_ptrc_glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
}

static void CODEGEN_FUNCPTR Switch_GetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params)
{
	_ptrc_glGetActiveUniformsiv = (PFN_PTRC_GLGETACTIVEUNIFORMSIVPROC)IntGetProcAddress("glGetActiveUniformsiv");
	_ptrc_glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
}

static GLuint CODEGEN_FUNCPTR Switch_GetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName)
{
	_ptrc_glGetUniformBlockIndex = (PFN_PTRC_GLGETUNIFORMBLOCKINDEXPROC)IntGetProcAddress("glGetUniformBlockIndex");
	return _ptrc_glGetUniformBlockIndex(program, uniformBlockName);
}

static void CODEGEN_FUNCPTR Switch_GetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices)
{
	_ptrc_glGetUniformIndices = (PFN_PTRC_GLGETUNIFORMINDICESPROC)IntGetProcAddress("glGetUniformIndices");
	_ptrc_glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
}

static void CODEGEN_FUNCPTR Switch_PrimitiveRestartIndex(GLuint index)
{
	_ptrc_glPrimitiveRestartIndex = (PFN_PTRC_GLPRIMITIVERESTARTINDEXPROC)IntGetProcAddress("glPrimitiveRestartIndex");
	_ptrc_glPrimitiveRestartIndex(index);
}

static void CODEGEN_FUNCPTR Switch_TexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
{
	_ptrc_glTexBuffer = (PFN_PTRC_GLTEXBUFFERPROC)IntGetProcAddress("glTexBuffer");
	_ptrc_glTexBuffer(target, internalformat, buffer);
}

static void CODEGEN_FUNCPTR Switch_UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
	_ptrc_glUniformBlockBinding = (PFN_PTRC_GLUNIFORMBLOCKBINDINGPROC)IntGetProcAddress("glUniformBlockBinding");
	_ptrc_glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
}


/* Extension: 3.2*/
static GLenum CODEGEN_FUNCPTR Switch_ClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	_ptrc_glClientWaitSync = (PFN_PTRC_GLCLIENTWAITSYNCPROC)IntGetProcAddress("glClientWaitSync");
	return _ptrc_glClientWaitSync(sync, flags, timeout);
}

static void CODEGEN_FUNCPTR Switch_DeleteSync(GLsync sync)
{
	_ptrc_glDeleteSync = (PFN_PTRC_GLDELETESYNCPROC)IntGetProcAddress("glDeleteSync");
	_ptrc_glDeleteSync(sync);
}

static void CODEGEN_FUNCPTR Switch_DrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex)
{
	_ptrc_glDrawElementsBaseVertex = (PFN_PTRC_GLDRAWELEMENTSBASEVERTEXPROC)IntGetProcAddress("glDrawElementsBaseVertex");
	_ptrc_glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
}

static void CODEGEN_FUNCPTR Switch_DrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex)
{
	_ptrc_glDrawElementsInstancedBaseVertex = (PFN_PTRC_GLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)IntGetProcAddress("glDrawElementsInstancedBaseVertex");
	_ptrc_glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
}

static void CODEGEN_FUNCPTR Switch_DrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex)
{
	_ptrc_glDrawRangeElementsBaseVertex = (PFN_PTRC_GLDRAWRANGEELEMENTSBASEVERTEXPROC)IntGetProcAddress("glDrawRangeElementsBaseVertex");
	_ptrc_glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
}

static GLsync CODEGEN_FUNCPTR Switch_FenceSync(GLenum condition, GLbitfield flags)
{
	_ptrc_glFenceSync = (PFN_PTRC_GLFENCESYNCPROC)IntGetProcAddress("glFenceSync");
	return _ptrc_glFenceSync(condition, flags);
}

static void CODEGEN_FUNCPTR Switch_FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
	_ptrc_glFramebufferTexture = (PFN_PTRC_GLFRAMEBUFFERTEXTUREPROC)IntGetProcAddress("glFramebufferTexture");
	_ptrc_glFramebufferTexture(target, attachment, texture, level);
}

static void CODEGEN_FUNCPTR Switch_GetBufferParameteri64v(GLenum target, GLenum pname, GLint64 * params)
{
	_ptrc_glGetBufferParameteri64v = (PFN_PTRC_GLGETBUFFERPARAMETERI64VPROC)IntGetProcAddress("glGetBufferParameteri64v");
	_ptrc_glGetBufferParameteri64v(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetInteger64i_v(GLenum target, GLuint index, GLint64 * data)
{
	_ptrc_glGetInteger64i_v = (PFN_PTRC_GLGETINTEGER64I_VPROC)IntGetProcAddress("glGetInteger64i_v");
	_ptrc_glGetInteger64i_v(target, index, data);
}

static void CODEGEN_FUNCPTR Switch_GetInteger64v(GLenum pname, GLint64 * data)
{
	_ptrc_glGetInteger64v = (PFN_PTRC_GLGETINTEGER64VPROC)IntGetProcAddress("glGetInteger64v");
	_ptrc_glGetInteger64v(pname, data);
}

static void CODEGEN_FUNCPTR Switch_GetMultisamplefv(GLenum pname, GLuint index, GLfloat * val)
{
	_ptrc_glGetMultisamplefv = (PFN_PTRC_GLGETMULTISAMPLEFVPROC)IntGetProcAddress("glGetMultisamplefv");
	_ptrc_glGetMultisamplefv(pname, index, val);
}

static void CODEGEN_FUNCPTR Switch_GetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values)
{
	_ptrc_glGetSynciv = (PFN_PTRC_GLGETSYNCIVPROC)IntGetProcAddress("glGetSynciv");
	_ptrc_glGetSynciv(sync, pname, bufSize, length, values);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsSync(GLsync sync)
{
	_ptrc_glIsSync = (PFN_PTRC_GLISSYNCPROC)IntGetProcAddress("glIsSync");
	return _ptrc_glIsSync(sync);
}

static void CODEGEN_FUNCPTR Switch_MultiDrawElementsBaseVertex(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei drawcount, const GLint * basevertex)
{
	_ptrc_glMultiDrawElementsBaseVertex = (PFN_PTRC_GLMULTIDRAWELEMENTSBASEVERTEXPROC)IntGetProcAddress("glMultiDrawElementsBaseVertex");
	_ptrc_glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
}

static void CODEGEN_FUNCPTR Switch_ProvokingVertex(GLenum mode)
{
	_ptrc_glProvokingVertex = (PFN_PTRC_GLPROVOKINGVERTEXPROC)IntGetProcAddress("glProvokingVertex");
	_ptrc_glProvokingVertex(mode);
}

static void CODEGEN_FUNCPTR Switch_SampleMaski(GLuint maskNumber, GLbitfield mask)
{
	_ptrc_glSampleMaski = (PFN_PTRC_GLSAMPLEMASKIPROC)IntGetProcAddress("glSampleMaski");
	_ptrc_glSampleMaski(maskNumber, mask);
}

static void CODEGEN_FUNCPTR Switch_TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	_ptrc_glTexImage2DMultisample = (PFN_PTRC_GLTEXIMAGE2DMULTISAMPLEPROC)IntGetProcAddress("glTexImage2DMultisample");
	_ptrc_glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

static void CODEGEN_FUNCPTR Switch_TexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	_ptrc_glTexImage3DMultisample = (PFN_PTRC_GLTEXIMAGE3DMULTISAMPLEPROC)IntGetProcAddress("glTexImage3DMultisample");
	_ptrc_glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

static void CODEGEN_FUNCPTR Switch_WaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	_ptrc_glWaitSync = (PFN_PTRC_GLWAITSYNCPROC)IntGetProcAddress("glWaitSync");
	_ptrc_glWaitSync(sync, flags, timeout);
}


/* Extension: 3.3*/
static void CODEGEN_FUNCPTR Switch_BindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name)
{
	_ptrc_glBindFragDataLocationIndexed = (PFN_PTRC_GLBINDFRAGDATALOCATIONINDEXEDPROC)IntGetProcAddress("glBindFragDataLocationIndexed");
	_ptrc_glBindFragDataLocationIndexed(program, colorNumber, index, name);
}

static void CODEGEN_FUNCPTR Switch_BindSampler(GLuint unit, GLuint sampler)
{
	_ptrc_glBindSampler = (PFN_PTRC_GLBINDSAMPLERPROC)IntGetProcAddress("glBindSampler");
	_ptrc_glBindSampler(unit, sampler);
}

static void CODEGEN_FUNCPTR Switch_DeleteSamplers(GLsizei count, const GLuint * samplers)
{
	_ptrc_glDeleteSamplers = (PFN_PTRC_GLDELETESAMPLERSPROC)IntGetProcAddress("glDeleteSamplers");
	_ptrc_glDeleteSamplers(count, samplers);
}

static void CODEGEN_FUNCPTR Switch_GenSamplers(GLsizei count, GLuint * samplers)
{
	_ptrc_glGenSamplers = (PFN_PTRC_GLGENSAMPLERSPROC)IntGetProcAddress("glGenSamplers");
	_ptrc_glGenSamplers(count, samplers);
}

static GLint CODEGEN_FUNCPTR Switch_GetFragDataIndex(GLuint program, const GLchar * name)
{
	_ptrc_glGetFragDataIndex = (PFN_PTRC_GLGETFRAGDATAINDEXPROC)IntGetProcAddress("glGetFragDataIndex");
	return _ptrc_glGetFragDataIndex(program, name);
}

static void CODEGEN_FUNCPTR Switch_GetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params)
{
	_ptrc_glGetQueryObjecti64v = (PFN_PTRC_GLGETQUERYOBJECTI64VPROC)IntGetProcAddress("glGetQueryObjecti64v");
	_ptrc_glGetQueryObjecti64v(id, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params)
{
	_ptrc_glGetQueryObjectui64v = (PFN_PTRC_GLGETQUERYOBJECTUI64VPROC)IntGetProcAddress("glGetQueryObjectui64v");
	_ptrc_glGetQueryObjectui64v(id, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params)
{
	_ptrc_glGetSamplerParameterIiv = (PFN_PTRC_GLGETSAMPLERPARAMETERIIVPROC)IntGetProcAddress("glGetSamplerParameterIiv");
	_ptrc_glGetSamplerParameterIiv(sampler, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params)
{
	_ptrc_glGetSamplerParameterIuiv = (PFN_PTRC_GLGETSAMPLERPARAMETERIUIVPROC)IntGetProcAddress("glGetSamplerParameterIuiv");
	_ptrc_glGetSamplerParameterIuiv(sampler, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params)
{
	_ptrc_glGetSamplerParameterfv = (PFN_PTRC_GLGETSAMPLERPARAMETERFVPROC)IntGetProcAddress("glGetSamplerParameterfv");
	_ptrc_glGetSamplerParameterfv(sampler, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params)
{
	_ptrc_glGetSamplerParameteriv = (PFN_PTRC_GLGETSAMPLERPARAMETERIVPROC)IntGetProcAddress("glGetSamplerParameteriv");
	_ptrc_glGetSamplerParameteriv(sampler, pname, params);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsSampler(GLuint sampler)
{
	_ptrc_glIsSampler = (PFN_PTRC_GLISSAMPLERPROC)IntGetProcAddress("glIsSampler");
	return _ptrc_glIsSampler(sampler);
}

static void CODEGEN_FUNCPTR Switch_QueryCounter(GLuint id, GLenum target)
{
	_ptrc_glQueryCounter = (PFN_PTRC_GLQUERYCOUNTERPROC)IntGetProcAddress("glQueryCounter");
	_ptrc_glQueryCounter(id, target);
}

static void CODEGEN_FUNCPTR Switch_SamplerParameterIiv(GLuint sampler, GLenum pname, const GLint * param)
{
	_ptrc_glSamplerParameterIiv = (PFN_PTRC_GLSAMPLERPARAMETERIIVPROC)IntGetProcAddress("glSamplerParameterIiv");
	_ptrc_glSamplerParameterIiv(sampler, pname, param);
}

static void CODEGEN_FUNCPTR Switch_SamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint * param)
{
	_ptrc_glSamplerParameterIuiv = (PFN_PTRC_GLSAMPLERPARAMETERIUIVPROC)IntGetProcAddress("glSamplerParameterIuiv");
	_ptrc_glSamplerParameterIuiv(sampler, pname, param);
}

static void CODEGEN_FUNCPTR Switch_SamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
{
	_ptrc_glSamplerParameterf = (PFN_PTRC_GLSAMPLERPARAMETERFPROC)IntGetProcAddress("glSamplerParameterf");
	_ptrc_glSamplerParameterf(sampler, pname, param);
}

static void CODEGEN_FUNCPTR Switch_SamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat * param)
{
	_ptrc_glSamplerParameterfv = (PFN_PTRC_GLSAMPLERPARAMETERFVPROC)IntGetProcAddress("glSamplerParameterfv");
	_ptrc_glSamplerParameterfv(sampler, pname, param);
}

static void CODEGEN_FUNCPTR Switch_SamplerParameteri(GLuint sampler, GLenum pname, GLint param)
{
	_ptrc_glSamplerParameteri = (PFN_PTRC_GLSAMPLERPARAMETERIPROC)IntGetProcAddress("glSamplerParameteri");
	_ptrc_glSamplerParameteri(sampler, pname, param);
}

static void CODEGEN_FUNCPTR Switch_SamplerParameteriv(GLuint sampler, GLenum pname, const GLint * param)
{
	_ptrc_glSamplerParameteriv = (PFN_PTRC_GLSAMPLERPARAMETERIVPROC)IntGetProcAddress("glSamplerParameteriv");
	_ptrc_glSamplerParameteriv(sampler, pname, param);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribDivisor(GLuint index, GLuint divisor)
{
	_ptrc_glVertexAttribDivisor = (PFN_PTRC_GLVERTEXATTRIBDIVISORPROC)IntGetProcAddress("glVertexAttribDivisor");
	_ptrc_glVertexAttribDivisor(index, divisor);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	_ptrc_glVertexAttribP1ui = (PFN_PTRC_GLVERTEXATTRIBP1UIPROC)IntGetProcAddress("glVertexAttribP1ui");
	_ptrc_glVertexAttribP1ui(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
{
	_ptrc_glVertexAttribP1uiv = (PFN_PTRC_GLVERTEXATTRIBP1UIVPROC)IntGetProcAddress("glVertexAttribP1uiv");
	_ptrc_glVertexAttribP1uiv(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	_ptrc_glVertexAttribP2ui = (PFN_PTRC_GLVERTEXATTRIBP2UIPROC)IntGetProcAddress("glVertexAttribP2ui");
	_ptrc_glVertexAttribP2ui(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
{
	_ptrc_glVertexAttribP2uiv = (PFN_PTRC_GLVERTEXATTRIBP2UIVPROC)IntGetProcAddress("glVertexAttribP2uiv");
	_ptrc_glVertexAttribP2uiv(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	_ptrc_glVertexAttribP3ui = (PFN_PTRC_GLVERTEXATTRIBP3UIPROC)IntGetProcAddress("glVertexAttribP3ui");
	_ptrc_glVertexAttribP3ui(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
{
	_ptrc_glVertexAttribP3uiv = (PFN_PTRC_GLVERTEXATTRIBP3UIVPROC)IntGetProcAddress("glVertexAttribP3uiv");
	_ptrc_glVertexAttribP3uiv(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	_ptrc_glVertexAttribP4ui = (PFN_PTRC_GLVERTEXATTRIBP4UIPROC)IntGetProcAddress("glVertexAttribP4ui");
	_ptrc_glVertexAttribP4ui(index, type, normalized, value);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value)
{
	_ptrc_glVertexAttribP4uiv = (PFN_PTRC_GLVERTEXATTRIBP4UIVPROC)IntGetProcAddress("glVertexAttribP4uiv");
	_ptrc_glVertexAttribP4uiv(index, type, normalized, value);
}


/* Extension: 4.0*/
static void CODEGEN_FUNCPTR Switch_BeginQueryIndexed(GLenum target, GLuint index, GLuint id)
{
	_ptrc_glBeginQueryIndexed = (PFN_PTRC_GLBEGINQUERYINDEXEDPROC)IntGetProcAddress("glBeginQueryIndexed");
	_ptrc_glBeginQueryIndexed(target, index, id);
}

static void CODEGEN_FUNCPTR Switch_BindTransformFeedback(GLenum target, GLuint id)
{
	_ptrc_glBindTransformFeedback = (PFN_PTRC_GLBINDTRANSFORMFEEDBACKPROC)IntGetProcAddress("glBindTransformFeedback");
	_ptrc_glBindTransformFeedback(target, id);
}

static void CODEGEN_FUNCPTR Switch_BlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
	_ptrc_glBlendEquationSeparatei = (PFN_PTRC_GLBLENDEQUATIONSEPARATEIPROC)IntGetProcAddress("glBlendEquationSeparatei");
	_ptrc_glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
}

static void CODEGEN_FUNCPTR Switch_BlendEquationi(GLuint buf, GLenum mode)
{
	_ptrc_glBlendEquationi = (PFN_PTRC_GLBLENDEQUATIONIPROC)IntGetProcAddress("glBlendEquationi");
	_ptrc_glBlendEquationi(buf, mode);
}

static void CODEGEN_FUNCPTR Switch_BlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	_ptrc_glBlendFuncSeparatei = (PFN_PTRC_GLBLENDFUNCSEPARATEIPROC)IntGetProcAddress("glBlendFuncSeparatei");
	_ptrc_glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

static void CODEGEN_FUNCPTR Switch_BlendFunci(GLuint buf, GLenum src, GLenum dst)
{
	_ptrc_glBlendFunci = (PFN_PTRC_GLBLENDFUNCIPROC)IntGetProcAddress("glBlendFunci");
	_ptrc_glBlendFunci(buf, src, dst);
}

static void CODEGEN_FUNCPTR Switch_DeleteTransformFeedbacks(GLsizei n, const GLuint * ids)
{
	_ptrc_glDeleteTransformFeedbacks = (PFN_PTRC_GLDELETETRANSFORMFEEDBACKSPROC)IntGetProcAddress("glDeleteTransformFeedbacks");
	_ptrc_glDeleteTransformFeedbacks(n, ids);
}

static void CODEGEN_FUNCPTR Switch_DrawArraysIndirect(GLenum mode, const void * indirect)
{
	_ptrc_glDrawArraysIndirect = (PFN_PTRC_GLDRAWARRAYSINDIRECTPROC)IntGetProcAddress("glDrawArraysIndirect");
	_ptrc_glDrawArraysIndirect(mode, indirect);
}

static void CODEGEN_FUNCPTR Switch_DrawElementsIndirect(GLenum mode, GLenum type, const void * indirect)
{
	_ptrc_glDrawElementsIndirect = (PFN_PTRC_GLDRAWELEMENTSINDIRECTPROC)IntGetProcAddress("glDrawElementsIndirect");
	_ptrc_glDrawElementsIndirect(mode, type, indirect);
}

static void CODEGEN_FUNCPTR Switch_DrawTransformFeedback(GLenum mode, GLuint id)
{
	_ptrc_glDrawTransformFeedback = (PFN_PTRC_GLDRAWTRANSFORMFEEDBACKPROC)IntGetProcAddress("glDrawTransformFeedback");
	_ptrc_glDrawTransformFeedback(mode, id);
}

static void CODEGEN_FUNCPTR Switch_DrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream)
{
	_ptrc_glDrawTransformFeedbackStream = (PFN_PTRC_GLDRAWTRANSFORMFEEDBACKSTREAMPROC)IntGetProcAddress("glDrawTransformFeedbackStream");
	_ptrc_glDrawTransformFeedbackStream(mode, id, stream);
}

static void CODEGEN_FUNCPTR Switch_EndQueryIndexed(GLenum target, GLuint index)
{
	_ptrc_glEndQueryIndexed = (PFN_PTRC_GLENDQUERYINDEXEDPROC)IntGetProcAddress("glEndQueryIndexed");
	_ptrc_glEndQueryIndexed(target, index);
}

static void CODEGEN_FUNCPTR Switch_GenTransformFeedbacks(GLsizei n, GLuint * ids)
{
	_ptrc_glGenTransformFeedbacks = (PFN_PTRC_GLGENTRANSFORMFEEDBACKSPROC)IntGetProcAddress("glGenTransformFeedbacks");
	_ptrc_glGenTransformFeedbacks(n, ids);
}

static void CODEGEN_FUNCPTR Switch_GetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
{
	_ptrc_glGetActiveSubroutineName = (PFN_PTRC_GLGETACTIVESUBROUTINENAMEPROC)IntGetProcAddress("glGetActiveSubroutineName");
	_ptrc_glGetActiveSubroutineName(program, shadertype, index, bufsize, length, name);
}

static void CODEGEN_FUNCPTR Switch_GetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
{
	_ptrc_glGetActiveSubroutineUniformName = (PFN_PTRC_GLGETACTIVESUBROUTINEUNIFORMNAMEPROC)IntGetProcAddress("glGetActiveSubroutineUniformName");
	_ptrc_glGetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);
}

static void CODEGEN_FUNCPTR Switch_GetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values)
{
	_ptrc_glGetActiveSubroutineUniformiv = (PFN_PTRC_GLGETACTIVESUBROUTINEUNIFORMIVPROC)IntGetProcAddress("glGetActiveSubroutineUniformiv");
	_ptrc_glGetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
}

static void CODEGEN_FUNCPTR Switch_GetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values)
{
	_ptrc_glGetProgramStageiv = (PFN_PTRC_GLGETPROGRAMSTAGEIVPROC)IntGetProcAddress("glGetProgramStageiv");
	_ptrc_glGetProgramStageiv(program, shadertype, pname, values);
}

static void CODEGEN_FUNCPTR Switch_GetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params)
{
	_ptrc_glGetQueryIndexediv = (PFN_PTRC_GLGETQUERYINDEXEDIVPROC)IntGetProcAddress("glGetQueryIndexediv");
	_ptrc_glGetQueryIndexediv(target, index, pname, params);
}

static GLuint CODEGEN_FUNCPTR Switch_GetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar * name)
{
	_ptrc_glGetSubroutineIndex = (PFN_PTRC_GLGETSUBROUTINEINDEXPROC)IntGetProcAddress("glGetSubroutineIndex");
	return _ptrc_glGetSubroutineIndex(program, shadertype, name);
}

static GLint CODEGEN_FUNCPTR Switch_GetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar * name)
{
	_ptrc_glGetSubroutineUniformLocation = (PFN_PTRC_GLGETSUBROUTINEUNIFORMLOCATIONPROC)IntGetProcAddress("glGetSubroutineUniformLocation");
	return _ptrc_glGetSubroutineUniformLocation(program, shadertype, name);
}

static void CODEGEN_FUNCPTR Switch_GetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params)
{
	_ptrc_glGetUniformSubroutineuiv = (PFN_PTRC_GLGETUNIFORMSUBROUTINEUIVPROC)IntGetProcAddress("glGetUniformSubroutineuiv");
	_ptrc_glGetUniformSubroutineuiv(shadertype, location, params);
}

static void CODEGEN_FUNCPTR Switch_GetUniformdv(GLuint program, GLint location, GLdouble * params)
{
	_ptrc_glGetUniformdv = (PFN_PTRC_GLGETUNIFORMDVPROC)IntGetProcAddress("glGetUniformdv");
	_ptrc_glGetUniformdv(program, location, params);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsTransformFeedback(GLuint id)
{
	_ptrc_glIsTransformFeedback = (PFN_PTRC_GLISTRANSFORMFEEDBACKPROC)IntGetProcAddress("glIsTransformFeedback");
	return _ptrc_glIsTransformFeedback(id);
}

static void CODEGEN_FUNCPTR Switch_MinSampleShading(GLfloat value)
{
	_ptrc_glMinSampleShading = (PFN_PTRC_GLMINSAMPLESHADINGPROC)IntGetProcAddress("glMinSampleShading");
	_ptrc_glMinSampleShading(value);
}

static void CODEGEN_FUNCPTR Switch_PatchParameterfv(GLenum pname, const GLfloat * values)
{
	_ptrc_glPatchParameterfv = (PFN_PTRC_GLPATCHPARAMETERFVPROC)IntGetProcAddress("glPatchParameterfv");
	_ptrc_glPatchParameterfv(pname, values);
}

static void CODEGEN_FUNCPTR Switch_PatchParameteri(GLenum pname, GLint value)
{
	_ptrc_glPatchParameteri = (PFN_PTRC_GLPATCHPARAMETERIPROC)IntGetProcAddress("glPatchParameteri");
	_ptrc_glPatchParameteri(pname, value);
}

static void CODEGEN_FUNCPTR Switch_PauseTransformFeedback(void)
{
	_ptrc_glPauseTransformFeedback = (PFN_PTRC_GLPAUSETRANSFORMFEEDBACKPROC)IntGetProcAddress("glPauseTransformFeedback");
	_ptrc_glPauseTransformFeedback();
}

static void CODEGEN_FUNCPTR Switch_ResumeTransformFeedback(void)
{
	_ptrc_glResumeTransformFeedback = (PFN_PTRC_GLRESUMETRANSFORMFEEDBACKPROC)IntGetProcAddress("glResumeTransformFeedback");
	_ptrc_glResumeTransformFeedback();
}

static void CODEGEN_FUNCPTR Switch_Uniform1d(GLint location, GLdouble x)
{
	_ptrc_glUniform1d = (PFN_PTRC_GLUNIFORM1DPROC)IntGetProcAddress("glUniform1d");
	_ptrc_glUniform1d(location, x);
}

static void CODEGEN_FUNCPTR Switch_Uniform1dv(GLint location, GLsizei count, const GLdouble * value)
{
	_ptrc_glUniform1dv = (PFN_PTRC_GLUNIFORM1DVPROC)IntGetProcAddress("glUniform1dv");
	_ptrc_glUniform1dv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform2d(GLint location, GLdouble x, GLdouble y)
{
	_ptrc_glUniform2d = (PFN_PTRC_GLUNIFORM2DPROC)IntGetProcAddress("glUniform2d");
	_ptrc_glUniform2d(location, x, y);
}

static void CODEGEN_FUNCPTR Switch_Uniform2dv(GLint location, GLsizei count, const GLdouble * value)
{
	_ptrc_glUniform2dv = (PFN_PTRC_GLUNIFORM2DVPROC)IntGetProcAddress("glUniform2dv");
	_ptrc_glUniform2dv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z)
{
	_ptrc_glUniform3d = (PFN_PTRC_GLUNIFORM3DPROC)IntGetProcAddress("glUniform3d");
	_ptrc_glUniform3d(location, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_Uniform3dv(GLint location, GLsizei count, const GLdouble * value)
{
	_ptrc_glUniform3dv = (PFN_PTRC_GLUNIFORM3DVPROC)IntGetProcAddress("glUniform3dv");
	_ptrc_glUniform3dv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_Uniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	_ptrc_glUniform4d = (PFN_PTRC_GLUNIFORM4DPROC)IntGetProcAddress("glUniform4d");
	_ptrc_glUniform4d(location, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_Uniform4dv(GLint location, GLsizei count, const GLdouble * value)
{
	_ptrc_glUniform4dv = (PFN_PTRC_GLUNIFORM4DVPROC)IntGetProcAddress("glUniform4dv");
	_ptrc_glUniform4dv(location, count, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glUniformMatrix2dv = (PFN_PTRC_GLUNIFORMMATRIX2DVPROC)IntGetProcAddress("glUniformMatrix2dv");
	_ptrc_glUniformMatrix2dv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glUniformMatrix2x3dv = (PFN_PTRC_GLUNIFORMMATRIX2X3DVPROC)IntGetProcAddress("glUniformMatrix2x3dv");
	_ptrc_glUniformMatrix2x3dv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glUniformMatrix2x4dv = (PFN_PTRC_GLUNIFORMMATRIX2X4DVPROC)IntGetProcAddress("glUniformMatrix2x4dv");
	_ptrc_glUniformMatrix2x4dv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glUniformMatrix3dv = (PFN_PTRC_GLUNIFORMMATRIX3DVPROC)IntGetProcAddress("glUniformMatrix3dv");
	_ptrc_glUniformMatrix3dv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glUniformMatrix3x2dv = (PFN_PTRC_GLUNIFORMMATRIX3X2DVPROC)IntGetProcAddress("glUniformMatrix3x2dv");
	_ptrc_glUniformMatrix3x2dv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glUniformMatrix3x4dv = (PFN_PTRC_GLUNIFORMMATRIX3X4DVPROC)IntGetProcAddress("glUniformMatrix3x4dv");
	_ptrc_glUniformMatrix3x4dv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glUniformMatrix4dv = (PFN_PTRC_GLUNIFORMMATRIX4DVPROC)IntGetProcAddress("glUniformMatrix4dv");
	_ptrc_glUniformMatrix4dv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glUniformMatrix4x2dv = (PFN_PTRC_GLUNIFORMMATRIX4X2DVPROC)IntGetProcAddress("glUniformMatrix4x2dv");
	_ptrc_glUniformMatrix4x2dv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glUniformMatrix4x3dv = (PFN_PTRC_GLUNIFORMMATRIX4X3DVPROC)IntGetProcAddress("glUniformMatrix4x3dv");
	_ptrc_glUniformMatrix4x3dv(location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_UniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint * indices)
{
	_ptrc_glUniformSubroutinesuiv = (PFN_PTRC_GLUNIFORMSUBROUTINESUIVPROC)IntGetProcAddress("glUniformSubroutinesuiv");
	_ptrc_glUniformSubroutinesuiv(shadertype, count, indices);
}


/* Extension: 4.1*/
static void CODEGEN_FUNCPTR Switch_ActiveShaderProgram(GLuint pipeline, GLuint program)
{
	_ptrc_glActiveShaderProgram = (PFN_PTRC_GLACTIVESHADERPROGRAMPROC)IntGetProcAddress("glActiveShaderProgram");
	_ptrc_glActiveShaderProgram(pipeline, program);
}

static void CODEGEN_FUNCPTR Switch_BindProgramPipeline(GLuint pipeline)
{
	_ptrc_glBindProgramPipeline = (PFN_PTRC_GLBINDPROGRAMPIPELINEPROC)IntGetProcAddress("glBindProgramPipeline");
	_ptrc_glBindProgramPipeline(pipeline);
}

static void CODEGEN_FUNCPTR Switch_ClearDepthf(GLfloat d)
{
	_ptrc_glClearDepthf = (PFN_PTRC_GLCLEARDEPTHFPROC)IntGetProcAddress("glClearDepthf");
	_ptrc_glClearDepthf(d);
}

static GLuint CODEGEN_FUNCPTR Switch_CreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const* strings)
{
	_ptrc_glCreateShaderProgramv = (PFN_PTRC_GLCREATESHADERPROGRAMVPROC)IntGetProcAddress("glCreateShaderProgramv");
	return _ptrc_glCreateShaderProgramv(type, count, strings);
}

static void CODEGEN_FUNCPTR Switch_DeleteProgramPipelines(GLsizei n, const GLuint * pipelines)
{
	_ptrc_glDeleteProgramPipelines = (PFN_PTRC_GLDELETEPROGRAMPIPELINESPROC)IntGetProcAddress("glDeleteProgramPipelines");
	_ptrc_glDeleteProgramPipelines(n, pipelines);
}

static void CODEGEN_FUNCPTR Switch_DepthRangeArrayv(GLuint first, GLsizei count, const GLdouble * v)
{
	_ptrc_glDepthRangeArrayv = (PFN_PTRC_GLDEPTHRANGEARRAYVPROC)IntGetProcAddress("glDepthRangeArrayv");
	_ptrc_glDepthRangeArrayv(first, count, v);
}

static void CODEGEN_FUNCPTR Switch_DepthRangeIndexed(GLuint index, GLdouble n, GLdouble f)
{
	_ptrc_glDepthRangeIndexed = (PFN_PTRC_GLDEPTHRANGEINDEXEDPROC)IntGetProcAddress("glDepthRangeIndexed");
	_ptrc_glDepthRangeIndexed(index, n, f);
}

static void CODEGEN_FUNCPTR Switch_DepthRangef(GLfloat n, GLfloat f)
{
	_ptrc_glDepthRangef = (PFN_PTRC_GLDEPTHRANGEFPROC)IntGetProcAddress("glDepthRangef");
	_ptrc_glDepthRangef(n, f);
}

static void CODEGEN_FUNCPTR Switch_GenProgramPipelines(GLsizei n, GLuint * pipelines)
{
	_ptrc_glGenProgramPipelines = (PFN_PTRC_GLGENPROGRAMPIPELINESPROC)IntGetProcAddress("glGenProgramPipelines");
	_ptrc_glGenProgramPipelines(n, pipelines);
}

static void CODEGEN_FUNCPTR Switch_GetDoublei_v(GLenum target, GLuint index, GLdouble * data)
{
	_ptrc_glGetDoublei_v = (PFN_PTRC_GLGETDOUBLEI_VPROC)IntGetProcAddress("glGetDoublei_v");
	_ptrc_glGetDoublei_v(target, index, data);
}

static void CODEGEN_FUNCPTR Switch_GetFloati_v(GLenum target, GLuint index, GLfloat * data)
{
	_ptrc_glGetFloati_v = (PFN_PTRC_GLGETFLOATI_VPROC)IntGetProcAddress("glGetFloati_v");
	_ptrc_glGetFloati_v(target, index, data);
}

static void CODEGEN_FUNCPTR Switch_GetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, void * binary)
{
	_ptrc_glGetProgramBinary = (PFN_PTRC_GLGETPROGRAMBINARYPROC)IntGetProcAddress("glGetProgramBinary");
	_ptrc_glGetProgramBinary(program, bufSize, length, binaryFormat, binary);
}

static void CODEGEN_FUNCPTR Switch_GetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
	_ptrc_glGetProgramPipelineInfoLog = (PFN_PTRC_GLGETPROGRAMPIPELINEINFOLOGPROC)IntGetProcAddress("glGetProgramPipelineInfoLog");
	_ptrc_glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
}

static void CODEGEN_FUNCPTR Switch_GetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params)
{
	_ptrc_glGetProgramPipelineiv = (PFN_PTRC_GLGETPROGRAMPIPELINEIVPROC)IntGetProcAddress("glGetProgramPipelineiv");
	_ptrc_glGetProgramPipelineiv(pipeline, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision)
{
	_ptrc_glGetShaderPrecisionFormat = (PFN_PTRC_GLGETSHADERPRECISIONFORMATPROC)IntGetProcAddress("glGetShaderPrecisionFormat");
	_ptrc_glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
}

static void CODEGEN_FUNCPTR Switch_GetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params)
{
	_ptrc_glGetVertexAttribLdv = (PFN_PTRC_GLGETVERTEXATTRIBLDVPROC)IntGetProcAddress("glGetVertexAttribLdv");
	_ptrc_glGetVertexAttribLdv(index, pname, params);
}

static GLboolean CODEGEN_FUNCPTR Switch_IsProgramPipeline(GLuint pipeline)
{
	_ptrc_glIsProgramPipeline = (PFN_PTRC_GLISPROGRAMPIPELINEPROC)IntGetProcAddress("glIsProgramPipeline");
	return _ptrc_glIsProgramPipeline(pipeline);
}

static void CODEGEN_FUNCPTR Switch_ProgramBinary(GLuint program, GLenum binaryFormat, const void * binary, GLsizei length)
{
	_ptrc_glProgramBinary = (PFN_PTRC_GLPROGRAMBINARYPROC)IntGetProcAddress("glProgramBinary");
	_ptrc_glProgramBinary(program, binaryFormat, binary, length);
}

static void CODEGEN_FUNCPTR Switch_ProgramParameteri(GLuint program, GLenum pname, GLint value)
{
	_ptrc_glProgramParameteri = (PFN_PTRC_GLPROGRAMPARAMETERIPROC)IntGetProcAddress("glProgramParameteri");
	_ptrc_glProgramParameteri(program, pname, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform1d(GLuint program, GLint location, GLdouble v0)
{
	_ptrc_glProgramUniform1d = (PFN_PTRC_GLPROGRAMUNIFORM1DPROC)IntGetProcAddress("glProgramUniform1d");
	_ptrc_glProgramUniform1d(program, location, v0);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble * value)
{
	_ptrc_glProgramUniform1dv = (PFN_PTRC_GLPROGRAMUNIFORM1DVPROC)IntGetProcAddress("glProgramUniform1dv");
	_ptrc_glProgramUniform1dv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform1f(GLuint program, GLint location, GLfloat v0)
{
	_ptrc_glProgramUniform1f = (PFN_PTRC_GLPROGRAMUNIFORM1FPROC)IntGetProcAddress("glProgramUniform1f");
	_ptrc_glProgramUniform1f(program, location, v0);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
{
	_ptrc_glProgramUniform1fv = (PFN_PTRC_GLPROGRAMUNIFORM1FVPROC)IntGetProcAddress("glProgramUniform1fv");
	_ptrc_glProgramUniform1fv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform1i(GLuint program, GLint location, GLint v0)
{
	_ptrc_glProgramUniform1i = (PFN_PTRC_GLPROGRAMUNIFORM1IPROC)IntGetProcAddress("glProgramUniform1i");
	_ptrc_glProgramUniform1i(program, location, v0);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint * value)
{
	_ptrc_glProgramUniform1iv = (PFN_PTRC_GLPROGRAMUNIFORM1IVPROC)IntGetProcAddress("glProgramUniform1iv");
	_ptrc_glProgramUniform1iv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform1ui(GLuint program, GLint location, GLuint v0)
{
	_ptrc_glProgramUniform1ui = (PFN_PTRC_GLPROGRAMUNIFORM1UIPROC)IntGetProcAddress("glProgramUniform1ui");
	_ptrc_glProgramUniform1ui(program, location, v0);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
{
	_ptrc_glProgramUniform1uiv = (PFN_PTRC_GLPROGRAMUNIFORM1UIVPROC)IntGetProcAddress("glProgramUniform1uiv");
	_ptrc_glProgramUniform1uiv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1)
{
	_ptrc_glProgramUniform2d = (PFN_PTRC_GLPROGRAMUNIFORM2DPROC)IntGetProcAddress("glProgramUniform2d");
	_ptrc_glProgramUniform2d(program, location, v0, v1);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble * value)
{
	_ptrc_glProgramUniform2dv = (PFN_PTRC_GLPROGRAMUNIFORM2DVPROC)IntGetProcAddress("glProgramUniform2dv");
	_ptrc_glProgramUniform2dv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
{
	_ptrc_glProgramUniform2f = (PFN_PTRC_GLPROGRAMUNIFORM2FPROC)IntGetProcAddress("glProgramUniform2f");
	_ptrc_glProgramUniform2f(program, location, v0, v1);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
{
	_ptrc_glProgramUniform2fv = (PFN_PTRC_GLPROGRAMUNIFORM2FVPROC)IntGetProcAddress("glProgramUniform2fv");
	_ptrc_glProgramUniform2fv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
{
	_ptrc_glProgramUniform2i = (PFN_PTRC_GLPROGRAMUNIFORM2IPROC)IntGetProcAddress("glProgramUniform2i");
	_ptrc_glProgramUniform2i(program, location, v0, v1);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint * value)
{
	_ptrc_glProgramUniform2iv = (PFN_PTRC_GLPROGRAMUNIFORM2IVPROC)IntGetProcAddress("glProgramUniform2iv");
	_ptrc_glProgramUniform2iv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
{
	_ptrc_glProgramUniform2ui = (PFN_PTRC_GLPROGRAMUNIFORM2UIPROC)IntGetProcAddress("glProgramUniform2ui");
	_ptrc_glProgramUniform2ui(program, location, v0, v1);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
{
	_ptrc_glProgramUniform2uiv = (PFN_PTRC_GLPROGRAMUNIFORM2UIVPROC)IntGetProcAddress("glProgramUniform2uiv");
	_ptrc_glProgramUniform2uiv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2)
{
	_ptrc_glProgramUniform3d = (PFN_PTRC_GLPROGRAMUNIFORM3DPROC)IntGetProcAddress("glProgramUniform3d");
	_ptrc_glProgramUniform3d(program, location, v0, v1, v2);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble * value)
{
	_ptrc_glProgramUniform3dv = (PFN_PTRC_GLPROGRAMUNIFORM3DVPROC)IntGetProcAddress("glProgramUniform3dv");
	_ptrc_glProgramUniform3dv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	_ptrc_glProgramUniform3f = (PFN_PTRC_GLPROGRAMUNIFORM3FPROC)IntGetProcAddress("glProgramUniform3f");
	_ptrc_glProgramUniform3f(program, location, v0, v1, v2);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
{
	_ptrc_glProgramUniform3fv = (PFN_PTRC_GLPROGRAMUNIFORM3FVPROC)IntGetProcAddress("glProgramUniform3fv");
	_ptrc_glProgramUniform3fv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
{
	_ptrc_glProgramUniform3i = (PFN_PTRC_GLPROGRAMUNIFORM3IPROC)IntGetProcAddress("glProgramUniform3i");
	_ptrc_glProgramUniform3i(program, location, v0, v1, v2);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint * value)
{
	_ptrc_glProgramUniform3iv = (PFN_PTRC_GLPROGRAMUNIFORM3IVPROC)IntGetProcAddress("glProgramUniform3iv");
	_ptrc_glProgramUniform3iv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
{
	_ptrc_glProgramUniform3ui = (PFN_PTRC_GLPROGRAMUNIFORM3UIPROC)IntGetProcAddress("glProgramUniform3ui");
	_ptrc_glProgramUniform3ui(program, location, v0, v1, v2);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
{
	_ptrc_glProgramUniform3uiv = (PFN_PTRC_GLPROGRAMUNIFORM3UIVPROC)IntGetProcAddress("glProgramUniform3uiv");
	_ptrc_glProgramUniform3uiv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
{
	_ptrc_glProgramUniform4d = (PFN_PTRC_GLPROGRAMUNIFORM4DPROC)IntGetProcAddress("glProgramUniform4d");
	_ptrc_glProgramUniform4d(program, location, v0, v1, v2, v3);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble * value)
{
	_ptrc_glProgramUniform4dv = (PFN_PTRC_GLPROGRAMUNIFORM4DVPROC)IntGetProcAddress("glProgramUniform4dv");
	_ptrc_glProgramUniform4dv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	_ptrc_glProgramUniform4f = (PFN_PTRC_GLPROGRAMUNIFORM4FPROC)IntGetProcAddress("glProgramUniform4f");
	_ptrc_glProgramUniform4f(program, location, v0, v1, v2, v3);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat * value)
{
	_ptrc_glProgramUniform4fv = (PFN_PTRC_GLPROGRAMUNIFORM4FVPROC)IntGetProcAddress("glProgramUniform4fv");
	_ptrc_glProgramUniform4fv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	_ptrc_glProgramUniform4i = (PFN_PTRC_GLPROGRAMUNIFORM4IPROC)IntGetProcAddress("glProgramUniform4i");
	_ptrc_glProgramUniform4i(program, location, v0, v1, v2, v3);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint * value)
{
	_ptrc_glProgramUniform4iv = (PFN_PTRC_GLPROGRAMUNIFORM4IVPROC)IntGetProcAddress("glProgramUniform4iv");
	_ptrc_glProgramUniform4iv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	_ptrc_glProgramUniform4ui = (PFN_PTRC_GLPROGRAMUNIFORM4UIPROC)IntGetProcAddress("glProgramUniform4ui");
	_ptrc_glProgramUniform4ui(program, location, v0, v1, v2, v3);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint * value)
{
	_ptrc_glProgramUniform4uiv = (PFN_PTRC_GLPROGRAMUNIFORM4UIVPROC)IntGetProcAddress("glProgramUniform4uiv");
	_ptrc_glProgramUniform4uiv(program, location, count, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glProgramUniformMatrix2dv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX2DVPROC)IntGetProcAddress("glProgramUniformMatrix2dv");
	_ptrc_glProgramUniformMatrix2dv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glProgramUniformMatrix2fv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX2FVPROC)IntGetProcAddress("glProgramUniformMatrix2fv");
	_ptrc_glProgramUniformMatrix2fv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glProgramUniformMatrix2x3dv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX2X3DVPROC)IntGetProcAddress("glProgramUniformMatrix2x3dv");
	_ptrc_glProgramUniformMatrix2x3dv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glProgramUniformMatrix2x3fv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX2X3FVPROC)IntGetProcAddress("glProgramUniformMatrix2x3fv");
	_ptrc_glProgramUniformMatrix2x3fv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glProgramUniformMatrix2x4dv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX2X4DVPROC)IntGetProcAddress("glProgramUniformMatrix2x4dv");
	_ptrc_glProgramUniformMatrix2x4dv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glProgramUniformMatrix2x4fv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX2X4FVPROC)IntGetProcAddress("glProgramUniformMatrix2x4fv");
	_ptrc_glProgramUniformMatrix2x4fv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glProgramUniformMatrix3dv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX3DVPROC)IntGetProcAddress("glProgramUniformMatrix3dv");
	_ptrc_glProgramUniformMatrix3dv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glProgramUniformMatrix3fv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX3FVPROC)IntGetProcAddress("glProgramUniformMatrix3fv");
	_ptrc_glProgramUniformMatrix3fv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glProgramUniformMatrix3x2dv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX3X2DVPROC)IntGetProcAddress("glProgramUniformMatrix3x2dv");
	_ptrc_glProgramUniformMatrix3x2dv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glProgramUniformMatrix3x2fv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX3X2FVPROC)IntGetProcAddress("glProgramUniformMatrix3x2fv");
	_ptrc_glProgramUniformMatrix3x2fv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glProgramUniformMatrix3x4dv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX3X4DVPROC)IntGetProcAddress("glProgramUniformMatrix3x4dv");
	_ptrc_glProgramUniformMatrix3x4dv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glProgramUniformMatrix3x4fv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX3X4FVPROC)IntGetProcAddress("glProgramUniformMatrix3x4fv");
	_ptrc_glProgramUniformMatrix3x4fv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glProgramUniformMatrix4dv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX4DVPROC)IntGetProcAddress("glProgramUniformMatrix4dv");
	_ptrc_glProgramUniformMatrix4dv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glProgramUniformMatrix4fv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX4FVPROC)IntGetProcAddress("glProgramUniformMatrix4fv");
	_ptrc_glProgramUniformMatrix4fv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glProgramUniformMatrix4x2dv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX4X2DVPROC)IntGetProcAddress("glProgramUniformMatrix4x2dv");
	_ptrc_glProgramUniformMatrix4x2dv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glProgramUniformMatrix4x2fv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX4X2FVPROC)IntGetProcAddress("glProgramUniformMatrix4x2fv");
	_ptrc_glProgramUniformMatrix4x2fv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
	_ptrc_glProgramUniformMatrix4x3dv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX4X3DVPROC)IntGetProcAddress("glProgramUniformMatrix4x3dv");
	_ptrc_glProgramUniformMatrix4x3dv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	_ptrc_glProgramUniformMatrix4x3fv = (PFN_PTRC_GLPROGRAMUNIFORMMATRIX4X3FVPROC)IntGetProcAddress("glProgramUniformMatrix4x3fv");
	_ptrc_glProgramUniformMatrix4x3fv(program, location, count, transpose, value);
}

static void CODEGEN_FUNCPTR Switch_ReleaseShaderCompiler(void)
{
	_ptrc_glReleaseShaderCompiler = (PFN_PTRC_GLRELEASESHADERCOMPILERPROC)IntGetProcAddress("glReleaseShaderCompiler");
	_ptrc_glReleaseShaderCompiler();
}

static void CODEGEN_FUNCPTR Switch_ScissorArrayv(GLuint first, GLsizei count, const GLint * v)
{
	_ptrc_glScissorArrayv = (PFN_PTRC_GLSCISSORARRAYVPROC)IntGetProcAddress("glScissorArrayv");
	_ptrc_glScissorArrayv(first, count, v);
}

static void CODEGEN_FUNCPTR Switch_ScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height)
{
	_ptrc_glScissorIndexed = (PFN_PTRC_GLSCISSORINDEXEDPROC)IntGetProcAddress("glScissorIndexed");
	_ptrc_glScissorIndexed(index, left, bottom, width, height);
}

static void CODEGEN_FUNCPTR Switch_ScissorIndexedv(GLuint index, const GLint * v)
{
	_ptrc_glScissorIndexedv = (PFN_PTRC_GLSCISSORINDEXEDVPROC)IntGetProcAddress("glScissorIndexedv");
	_ptrc_glScissorIndexedv(index, v);
}

static void CODEGEN_FUNCPTR Switch_ShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryformat, const void * binary, GLsizei length)
{
	_ptrc_glShaderBinary = (PFN_PTRC_GLSHADERBINARYPROC)IntGetProcAddress("glShaderBinary");
	_ptrc_glShaderBinary(count, shaders, binaryformat, binary, length);
}

static void CODEGEN_FUNCPTR Switch_UseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
{
	_ptrc_glUseProgramStages = (PFN_PTRC_GLUSEPROGRAMSTAGESPROC)IntGetProcAddress("glUseProgramStages");
	_ptrc_glUseProgramStages(pipeline, stages, program);
}

static void CODEGEN_FUNCPTR Switch_ValidateProgramPipeline(GLuint pipeline)
{
	_ptrc_glValidateProgramPipeline = (PFN_PTRC_GLVALIDATEPROGRAMPIPELINEPROC)IntGetProcAddress("glValidateProgramPipeline");
	_ptrc_glValidateProgramPipeline(pipeline);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribL1d(GLuint index, GLdouble x)
{
	_ptrc_glVertexAttribL1d = (PFN_PTRC_GLVERTEXATTRIBL1DPROC)IntGetProcAddress("glVertexAttribL1d");
	_ptrc_glVertexAttribL1d(index, x);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribL1dv(GLuint index, const GLdouble * v)
{
	_ptrc_glVertexAttribL1dv = (PFN_PTRC_GLVERTEXATTRIBL1DVPROC)IntGetProcAddress("glVertexAttribL1dv");
	_ptrc_glVertexAttribL1dv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribL2d(GLuint index, GLdouble x, GLdouble y)
{
	_ptrc_glVertexAttribL2d = (PFN_PTRC_GLVERTEXATTRIBL2DPROC)IntGetProcAddress("glVertexAttribL2d");
	_ptrc_glVertexAttribL2d(index, x, y);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribL2dv(GLuint index, const GLdouble * v)
{
	_ptrc_glVertexAttribL2dv = (PFN_PTRC_GLVERTEXATTRIBL2DVPROC)IntGetProcAddress("glVertexAttribL2dv");
	_ptrc_glVertexAttribL2dv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
	_ptrc_glVertexAttribL3d = (PFN_PTRC_GLVERTEXATTRIBL3DPROC)IntGetProcAddress("glVertexAttribL3d");
	_ptrc_glVertexAttribL3d(index, x, y, z);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribL3dv(GLuint index, const GLdouble * v)
{
	_ptrc_glVertexAttribL3dv = (PFN_PTRC_GLVERTEXATTRIBL3DVPROC)IntGetProcAddress("glVertexAttribL3dv");
	_ptrc_glVertexAttribL3dv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	_ptrc_glVertexAttribL4d = (PFN_PTRC_GLVERTEXATTRIBL4DPROC)IntGetProcAddress("glVertexAttribL4d");
	_ptrc_glVertexAttribL4d(index, x, y, z, w);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribL4dv(GLuint index, const GLdouble * v)
{
	_ptrc_glVertexAttribL4dv = (PFN_PTRC_GLVERTEXATTRIBL4DVPROC)IntGetProcAddress("glVertexAttribL4dv");
	_ptrc_glVertexAttribL4dv(index, v);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer)
{
	_ptrc_glVertexAttribLPointer = (PFN_PTRC_GLVERTEXATTRIBLPOINTERPROC)IntGetProcAddress("glVertexAttribLPointer");
	_ptrc_glVertexAttribLPointer(index, size, type, stride, pointer);
}

static void CODEGEN_FUNCPTR Switch_ViewportArrayv(GLuint first, GLsizei count, const GLfloat * v)
{
	_ptrc_glViewportArrayv = (PFN_PTRC_GLVIEWPORTARRAYVPROC)IntGetProcAddress("glViewportArrayv");
	_ptrc_glViewportArrayv(first, count, v);
}

static void CODEGEN_FUNCPTR Switch_ViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	_ptrc_glViewportIndexedf = (PFN_PTRC_GLVIEWPORTINDEXEDFPROC)IntGetProcAddress("glViewportIndexedf");
	_ptrc_glViewportIndexedf(index, x, y, w, h);
}

static void CODEGEN_FUNCPTR Switch_ViewportIndexedfv(GLuint index, const GLfloat * v)
{
	_ptrc_glViewportIndexedfv = (PFN_PTRC_GLVIEWPORTINDEXEDFVPROC)IntGetProcAddress("glViewportIndexedfv");
	_ptrc_glViewportIndexedfv(index, v);
}


/* Extension: 4.2*/
static void CODEGEN_FUNCPTR Switch_BindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
{
	_ptrc_glBindImageTexture = (PFN_PTRC_GLBINDIMAGETEXTUREPROC)IntGetProcAddress("glBindImageTexture");
	_ptrc_glBindImageTexture(unit, texture, level, layered, layer, access, format);
}

static void CODEGEN_FUNCPTR Switch_DrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance)
{
	_ptrc_glDrawArraysInstancedBaseInstance = (PFN_PTRC_GLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)IntGetProcAddress("glDrawArraysInstancedBaseInstance");
	_ptrc_glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
}

static void CODEGEN_FUNCPTR Switch_DrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLuint baseinstance)
{
	_ptrc_glDrawElementsInstancedBaseInstance = (PFN_PTRC_GLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)IntGetProcAddress("glDrawElementsInstancedBaseInstance");
	_ptrc_glDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);
}

static void CODEGEN_FUNCPTR Switch_DrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance)
{
	_ptrc_glDrawElementsInstancedBaseVertexBaseInstance = (PFN_PTRC_GLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)IntGetProcAddress("glDrawElementsInstancedBaseVertexBaseInstance");
	_ptrc_glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
}

static void CODEGEN_FUNCPTR Switch_DrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount)
{
	_ptrc_glDrawTransformFeedbackInstanced = (PFN_PTRC_GLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)IntGetProcAddress("glDrawTransformFeedbackInstanced");
	_ptrc_glDrawTransformFeedbackInstanced(mode, id, instancecount);
}

static void CODEGEN_FUNCPTR Switch_DrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount)
{
	_ptrc_glDrawTransformFeedbackStreamInstanced = (PFN_PTRC_GLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)IntGetProcAddress("glDrawTransformFeedbackStreamInstanced");
	_ptrc_glDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
}

static void CODEGEN_FUNCPTR Switch_GetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params)
{
	_ptrc_glGetActiveAtomicCounterBufferiv = (PFN_PTRC_GLGETACTIVEATOMICCOUNTERBUFFERIVPROC)IntGetProcAddress("glGetActiveAtomicCounterBufferiv");
	_ptrc_glGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params)
{
	_ptrc_glGetInternalformativ = (PFN_PTRC_GLGETINTERNALFORMATIVPROC)IntGetProcAddress("glGetInternalformativ");
	_ptrc_glGetInternalformativ(target, internalformat, pname, bufSize, params);
}

static void CODEGEN_FUNCPTR Switch_MemoryBarrier(GLbitfield barriers)
{
	_ptrc_glMemoryBarrier = (PFN_PTRC_GLMEMORYBARRIERPROC)IntGetProcAddress("glMemoryBarrier");
	_ptrc_glMemoryBarrier(barriers);
}

static void CODEGEN_FUNCPTR Switch_TexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
{
	_ptrc_glTexStorage1D = (PFN_PTRC_GLTEXSTORAGE1DPROC)IntGetProcAddress("glTexStorage1D");
	_ptrc_glTexStorage1D(target, levels, internalformat, width);
}

static void CODEGEN_FUNCPTR Switch_TexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	_ptrc_glTexStorage2D = (PFN_PTRC_GLTEXSTORAGE2DPROC)IntGetProcAddress("glTexStorage2D");
	_ptrc_glTexStorage2D(target, levels, internalformat, width, height);
}

static void CODEGEN_FUNCPTR Switch_TexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	_ptrc_glTexStorage3D = (PFN_PTRC_GLTEXSTORAGE3DPROC)IntGetProcAddress("glTexStorage3D");
	_ptrc_glTexStorage3D(target, levels, internalformat, width, height, depth);
}


/* Extension: 4.3*/
static void CODEGEN_FUNCPTR Switch_BindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
{
	_ptrc_glBindVertexBuffer = (PFN_PTRC_GLBINDVERTEXBUFFERPROC)IntGetProcAddress("glBindVertexBuffer");
	_ptrc_glBindVertexBuffer(bindingindex, buffer, offset, stride);
}

static void CODEGEN_FUNCPTR Switch_ClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data)
{
	_ptrc_glClearBufferData = (PFN_PTRC_GLCLEARBUFFERDATAPROC)IntGetProcAddress("glClearBufferData");
	_ptrc_glClearBufferData(target, internalformat, format, type, data);
}

static void CODEGEN_FUNCPTR Switch_ClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data)
{
	_ptrc_glClearBufferSubData = (PFN_PTRC_GLCLEARBUFFERSUBDATAPROC)IntGetProcAddress("glClearBufferSubData");
	_ptrc_glClearBufferSubData(target, internalformat, offset, size, format, type, data);
}

static void CODEGEN_FUNCPTR Switch_CopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
{
	_ptrc_glCopyImageSubData = (PFN_PTRC_GLCOPYIMAGESUBDATAPROC)IntGetProcAddress("glCopyImageSubData");
	_ptrc_glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
}

static void CODEGEN_FUNCPTR Switch_DebugMessageCallback(GLDEBUGPROC callback, const void * userParam)
{
	_ptrc_glDebugMessageCallback = (PFN_PTRC_GLDEBUGMESSAGECALLBACKPROC)IntGetProcAddress("glDebugMessageCallback");
	_ptrc_glDebugMessageCallback(callback, userParam);
}

static void CODEGEN_FUNCPTR Switch_DebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled)
{
	_ptrc_glDebugMessageControl = (PFN_PTRC_GLDEBUGMESSAGECONTROLPROC)IntGetProcAddress("glDebugMessageControl");
	_ptrc_glDebugMessageControl(source, type, severity, count, ids, enabled);
}

static void CODEGEN_FUNCPTR Switch_DebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf)
{
	_ptrc_glDebugMessageInsert = (PFN_PTRC_GLDEBUGMESSAGEINSERTPROC)IntGetProcAddress("glDebugMessageInsert");
	_ptrc_glDebugMessageInsert(source, type, id, severity, length, buf);
}

static void CODEGEN_FUNCPTR Switch_DispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
{
	_ptrc_glDispatchCompute = (PFN_PTRC_GLDISPATCHCOMPUTEPROC)IntGetProcAddress("glDispatchCompute");
	_ptrc_glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
}

static void CODEGEN_FUNCPTR Switch_DispatchComputeIndirect(GLintptr indirect)
{
	_ptrc_glDispatchComputeIndirect = (PFN_PTRC_GLDISPATCHCOMPUTEINDIRECTPROC)IntGetProcAddress("glDispatchComputeIndirect");
	_ptrc_glDispatchComputeIndirect(indirect);
}

static void CODEGEN_FUNCPTR Switch_FramebufferParameteri(GLenum target, GLenum pname, GLint param)
{
	_ptrc_glFramebufferParameteri = (PFN_PTRC_GLFRAMEBUFFERPARAMETERIPROC)IntGetProcAddress("glFramebufferParameteri");
	_ptrc_glFramebufferParameteri(target, pname, param);
}

static GLuint CODEGEN_FUNCPTR Switch_GetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog)
{
	_ptrc_glGetDebugMessageLog = (PFN_PTRC_GLGETDEBUGMESSAGELOGPROC)IntGetProcAddress("glGetDebugMessageLog");
	return _ptrc_glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
}

static void CODEGEN_FUNCPTR Switch_GetFramebufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
	_ptrc_glGetFramebufferParameteriv = (PFN_PTRC_GLGETFRAMEBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetFramebufferParameteriv");
	_ptrc_glGetFramebufferParameteriv(target, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params)
{
	_ptrc_glGetInternalformati64v = (PFN_PTRC_GLGETINTERNALFORMATI64VPROC)IntGetProcAddress("glGetInternalformati64v");
	_ptrc_glGetInternalformati64v(target, internalformat, pname, bufSize, params);
}

static void CODEGEN_FUNCPTR Switch_GetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label)
{
	_ptrc_glGetObjectLabel = (PFN_PTRC_GLGETOBJECTLABELPROC)IntGetProcAddress("glGetObjectLabel");
	_ptrc_glGetObjectLabel(identifier, name, bufSize, length, label);
}

static void CODEGEN_FUNCPTR Switch_GetObjectPtrLabel(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label)
{
	_ptrc_glGetObjectPtrLabel = (PFN_PTRC_GLGETOBJECTPTRLABELPROC)IntGetProcAddress("glGetObjectPtrLabel");
	_ptrc_glGetObjectPtrLabel(ptr, bufSize, length, label);
}

static void CODEGEN_FUNCPTR Switch_GetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params)
{
	_ptrc_glGetProgramInterfaceiv = (PFN_PTRC_GLGETPROGRAMINTERFACEIVPROC)IntGetProcAddress("glGetProgramInterfaceiv");
	_ptrc_glGetProgramInterfaceiv(program, programInterface, pname, params);
}

static GLuint CODEGEN_FUNCPTR Switch_GetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar * name)
{
	_ptrc_glGetProgramResourceIndex = (PFN_PTRC_GLGETPROGRAMRESOURCEINDEXPROC)IntGetProcAddress("glGetProgramResourceIndex");
	return _ptrc_glGetProgramResourceIndex(program, programInterface, name);
}

static GLint CODEGEN_FUNCPTR Switch_GetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar * name)
{
	_ptrc_glGetProgramResourceLocation = (PFN_PTRC_GLGETPROGRAMRESOURCELOCATIONPROC)IntGetProcAddress("glGetProgramResourceLocation");
	return _ptrc_glGetProgramResourceLocation(program, programInterface, name);
}

static GLint CODEGEN_FUNCPTR Switch_GetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar * name)
{
	_ptrc_glGetProgramResourceLocationIndex = (PFN_PTRC_GLGETPROGRAMRESOURCELOCATIONINDEXPROC)IntGetProcAddress("glGetProgramResourceLocationIndex");
	return _ptrc_glGetProgramResourceLocationIndex(program, programInterface, name);
}

static void CODEGEN_FUNCPTR Switch_GetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name)
{
	_ptrc_glGetProgramResourceName = (PFN_PTRC_GLGETPROGRAMRESOURCENAMEPROC)IntGetProcAddress("glGetProgramResourceName");
	_ptrc_glGetProgramResourceName(program, programInterface, index, bufSize, length, name);
}

static void CODEGEN_FUNCPTR Switch_GetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params)
{
	_ptrc_glGetProgramResourceiv = (PFN_PTRC_GLGETPROGRAMRESOURCEIVPROC)IntGetProcAddress("glGetProgramResourceiv");
	_ptrc_glGetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
}

static void CODEGEN_FUNCPTR Switch_InvalidateBufferData(GLuint buffer)
{
	_ptrc_glInvalidateBufferData = (PFN_PTRC_GLINVALIDATEBUFFERDATAPROC)IntGetProcAddress("glInvalidateBufferData");
	_ptrc_glInvalidateBufferData(buffer);
}

static void CODEGEN_FUNCPTR Switch_InvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length)
{
	_ptrc_glInvalidateBufferSubData = (PFN_PTRC_GLINVALIDATEBUFFERSUBDATAPROC)IntGetProcAddress("glInvalidateBufferSubData");
	_ptrc_glInvalidateBufferSubData(buffer, offset, length);
}

static void CODEGEN_FUNCPTR Switch_InvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments)
{
	_ptrc_glInvalidateFramebuffer = (PFN_PTRC_GLINVALIDATEFRAMEBUFFERPROC)IntGetProcAddress("glInvalidateFramebuffer");
	_ptrc_glInvalidateFramebuffer(target, numAttachments, attachments);
}

static void CODEGEN_FUNCPTR Switch_InvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_ptrc_glInvalidateSubFramebuffer = (PFN_PTRC_GLINVALIDATESUBFRAMEBUFFERPROC)IntGetProcAddress("glInvalidateSubFramebuffer");
	_ptrc_glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
}

static void CODEGEN_FUNCPTR Switch_InvalidateTexImage(GLuint texture, GLint level)
{
	_ptrc_glInvalidateTexImage = (PFN_PTRC_GLINVALIDATETEXIMAGEPROC)IntGetProcAddress("glInvalidateTexImage");
	_ptrc_glInvalidateTexImage(texture, level);
}

static void CODEGEN_FUNCPTR Switch_InvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth)
{
	_ptrc_glInvalidateTexSubImage = (PFN_PTRC_GLINVALIDATETEXSUBIMAGEPROC)IntGetProcAddress("glInvalidateTexSubImage");
	_ptrc_glInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
}

static void CODEGEN_FUNCPTR Switch_MultiDrawArraysIndirect(GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride)
{
	_ptrc_glMultiDrawArraysIndirect = (PFN_PTRC_GLMULTIDRAWARRAYSINDIRECTPROC)IntGetProcAddress("glMultiDrawArraysIndirect");
	_ptrc_glMultiDrawArraysIndirect(mode, indirect, drawcount, stride);
}

static void CODEGEN_FUNCPTR Switch_MultiDrawElementsIndirect(GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride)
{
	_ptrc_glMultiDrawElementsIndirect = (PFN_PTRC_GLMULTIDRAWELEMENTSINDIRECTPROC)IntGetProcAddress("glMultiDrawElementsIndirect");
	_ptrc_glMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
}

static void CODEGEN_FUNCPTR Switch_ObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar * label)
{
	_ptrc_glObjectLabel = (PFN_PTRC_GLOBJECTLABELPROC)IntGetProcAddress("glObjectLabel");
	_ptrc_glObjectLabel(identifier, name, length, label);
}

static void CODEGEN_FUNCPTR Switch_ObjectPtrLabel(const void * ptr, GLsizei length, const GLchar * label)
{
	_ptrc_glObjectPtrLabel = (PFN_PTRC_GLOBJECTPTRLABELPROC)IntGetProcAddress("glObjectPtrLabel");
	_ptrc_glObjectPtrLabel(ptr, length, label);
}

static void CODEGEN_FUNCPTR Switch_PopDebugGroup(void)
{
	_ptrc_glPopDebugGroup = (PFN_PTRC_GLPOPDEBUGGROUPPROC)IntGetProcAddress("glPopDebugGroup");
	_ptrc_glPopDebugGroup();
}

static void CODEGEN_FUNCPTR Switch_PushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar * message)
{
	_ptrc_glPushDebugGroup = (PFN_PTRC_GLPUSHDEBUGGROUPPROC)IntGetProcAddress("glPushDebugGroup");
	_ptrc_glPushDebugGroup(source, id, length, message);
}

static void CODEGEN_FUNCPTR Switch_ShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding)
{
	_ptrc_glShaderStorageBlockBinding = (PFN_PTRC_GLSHADERSTORAGEBLOCKBINDINGPROC)IntGetProcAddress("glShaderStorageBlockBinding");
	_ptrc_glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
}

static void CODEGEN_FUNCPTR Switch_TexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	_ptrc_glTexBufferRange = (PFN_PTRC_GLTEXBUFFERRANGEPROC)IntGetProcAddress("glTexBufferRange");
	_ptrc_glTexBufferRange(target, internalformat, buffer, offset, size);
}

static void CODEGEN_FUNCPTR Switch_TexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	_ptrc_glTexStorage2DMultisample = (PFN_PTRC_GLTEXSTORAGE2DMULTISAMPLEPROC)IntGetProcAddress("glTexStorage2DMultisample");
	_ptrc_glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

static void CODEGEN_FUNCPTR Switch_TexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	_ptrc_glTexStorage3DMultisample = (PFN_PTRC_GLTEXSTORAGE3DMULTISAMPLEPROC)IntGetProcAddress("glTexStorage3DMultisample");
	_ptrc_glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

static void CODEGEN_FUNCPTR Switch_TextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers)
{
	_ptrc_glTextureView = (PFN_PTRC_GLTEXTUREVIEWPROC)IntGetProcAddress("glTextureView");
	_ptrc_glTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribBinding(GLuint attribindex, GLuint bindingindex)
{
	_ptrc_glVertexAttribBinding = (PFN_PTRC_GLVERTEXATTRIBBINDINGPROC)IntGetProcAddress("glVertexAttribBinding");
	_ptrc_glVertexAttribBinding(attribindex, bindingindex);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
	_ptrc_glVertexAttribFormat = (PFN_PTRC_GLVERTEXATTRIBFORMATPROC)IntGetProcAddress("glVertexAttribFormat");
	_ptrc_glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
	_ptrc_glVertexAttribIFormat = (PFN_PTRC_GLVERTEXATTRIBIFORMATPROC)IntGetProcAddress("glVertexAttribIFormat");
	_ptrc_glVertexAttribIFormat(attribindex, size, type, relativeoffset);
}

static void CODEGEN_FUNCPTR Switch_VertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
	_ptrc_glVertexAttribLFormat = (PFN_PTRC_GLVERTEXATTRIBLFORMATPROC)IntGetProcAddress("glVertexAttribLFormat");
	_ptrc_glVertexAttribLFormat(attribindex, size, type, relativeoffset);
}

static void CODEGEN_FUNCPTR Switch_VertexBindingDivisor(GLuint bindingindex, GLuint divisor)
{
	_ptrc_glVertexBindingDivisor = (PFN_PTRC_GLVERTEXBINDINGDIVISORPROC)IntGetProcAddress("glVertexBindingDivisor");
	_ptrc_glVertexBindingDivisor(bindingindex, divisor);
}


/* Extension: 4.4*/
static void CODEGEN_FUNCPTR Switch_BindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint * buffers)
{
	_ptrc_glBindBuffersBase = (PFN_PTRC_GLBINDBUFFERSBASEPROC)IntGetProcAddress("glBindBuffersBase");
	_ptrc_glBindBuffersBase(target, first, count, buffers);
}

static void CODEGEN_FUNCPTR Switch_BindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes)
{
	_ptrc_glBindBuffersRange = (PFN_PTRC_GLBINDBUFFERSRANGEPROC)IntGetProcAddress("glBindBuffersRange");
	_ptrc_glBindBuffersRange(target, first, count, buffers, offsets, sizes);
}

static void CODEGEN_FUNCPTR Switch_BindImageTextures(GLuint first, GLsizei count, const GLuint * textures)
{
	_ptrc_glBindImageTextures = (PFN_PTRC_GLBINDIMAGETEXTURESPROC)IntGetProcAddress("glBindImageTextures");
	_ptrc_glBindImageTextures(first, count, textures);
}

static void CODEGEN_FUNCPTR Switch_BindSamplers(GLuint first, GLsizei count, const GLuint * samplers)
{
	_ptrc_glBindSamplers = (PFN_PTRC_GLBINDSAMPLERSPROC)IntGetProcAddress("glBindSamplers");
	_ptrc_glBindSamplers(first, count, samplers);
}

static void CODEGEN_FUNCPTR Switch_BindTextures(GLuint first, GLsizei count, const GLuint * textures)
{
	_ptrc_glBindTextures = (PFN_PTRC_GLBINDTEXTURESPROC)IntGetProcAddress("glBindTextures");
	_ptrc_glBindTextures(first, count, textures);
}

static void CODEGEN_FUNCPTR Switch_BindVertexBuffers(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides)
{
	_ptrc_glBindVertexBuffers = (PFN_PTRC_GLBINDVERTEXBUFFERSPROC)IntGetProcAddress("glBindVertexBuffers");
	_ptrc_glBindVertexBuffers(first, count, buffers, offsets, strides);
}

static void CODEGEN_FUNCPTR Switch_BufferStorage(GLenum target, GLsizeiptr size, const void * data, GLbitfield flags)
{
	_ptrc_glBufferStorage = (PFN_PTRC_GLBUFFERSTORAGEPROC)IntGetProcAddress("glBufferStorage");
	_ptrc_glBufferStorage(target, size, data, flags);
}

static void CODEGEN_FUNCPTR Switch_ClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void * data)
{
	_ptrc_glClearTexImage = (PFN_PTRC_GLCLEARTEXIMAGEPROC)IntGetProcAddress("glClearTexImage");
	_ptrc_glClearTexImage(texture, level, format, type, data);
}

static void CODEGEN_FUNCPTR Switch_ClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * data)
{
	_ptrc_glClearTexSubImage = (PFN_PTRC_GLCLEARTEXSUBIMAGEPROC)IntGetProcAddress("glClearTexSubImage");
	_ptrc_glClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
}


/* Extension: 4.5*/
static void CODEGEN_FUNCPTR Switch_BindTextureUnit(GLuint unit, GLuint texture)
{
	_ptrc_glBindTextureUnit = (PFN_PTRC_GLBINDTEXTUREUNITPROC)IntGetProcAddress("glBindTextureUnit");
	_ptrc_glBindTextureUnit(unit, texture);
}

static void CODEGEN_FUNCPTR Switch_BlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
	_ptrc_glBlitNamedFramebuffer = (PFN_PTRC_GLBLITNAMEDFRAMEBUFFERPROC)IntGetProcAddress("glBlitNamedFramebuffer");
	_ptrc_glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

static GLenum CODEGEN_FUNCPTR Switch_CheckNamedFramebufferStatus(GLuint framebuffer, GLenum target)
{
	_ptrc_glCheckNamedFramebufferStatus = (PFN_PTRC_GLCHECKNAMEDFRAMEBUFFERSTATUSPROC)IntGetProcAddress("glCheckNamedFramebufferStatus");
	return _ptrc_glCheckNamedFramebufferStatus(framebuffer, target);
}

static void CODEGEN_FUNCPTR Switch_ClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data)
{
	_ptrc_glClearNamedBufferData = (PFN_PTRC_GLCLEARNAMEDBUFFERDATAPROC)IntGetProcAddress("glClearNamedBufferData");
	_ptrc_glClearNamedBufferData(buffer, internalformat, format, type, data);
}

static void CODEGEN_FUNCPTR Switch_ClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data)
{
	_ptrc_glClearNamedBufferSubData = (PFN_PTRC_GLCLEARNAMEDBUFFERSUBDATAPROC)IntGetProcAddress("glClearNamedBufferSubData");
	_ptrc_glClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);
}

static void CODEGEN_FUNCPTR Switch_ClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat depth, GLint stencil)
{
	_ptrc_glClearNamedFramebufferfi = (PFN_PTRC_GLCLEARNAMEDFRAMEBUFFERFIPROC)IntGetProcAddress("glClearNamedFramebufferfi");
	_ptrc_glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);
}

static void CODEGEN_FUNCPTR Switch_ClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value)
{
	_ptrc_glClearNamedFramebufferfv = (PFN_PTRC_GLCLEARNAMEDFRAMEBUFFERFVPROC)IntGetProcAddress("glClearNamedFramebufferfv");
	_ptrc_glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
}

static void CODEGEN_FUNCPTR Switch_ClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value)
{
	_ptrc_glClearNamedFramebufferiv = (PFN_PTRC_GLCLEARNAMEDFRAMEBUFFERIVPROC)IntGetProcAddress("glClearNamedFramebufferiv");
	_ptrc_glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);
}

static void CODEGEN_FUNCPTR Switch_ClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value)
{
	_ptrc_glClearNamedFramebufferuiv = (PFN_PTRC_GLCLEARNAMEDFRAMEBUFFERUIVPROC)IntGetProcAddress("glClearNamedFramebufferuiv");
	_ptrc_glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);
}

static void CODEGEN_FUNCPTR Switch_ClipControl(GLenum origin, GLenum depth)
{
	_ptrc_glClipControl = (PFN_PTRC_GLCLIPCONTROLPROC)IntGetProcAddress("glClipControl");
	_ptrc_glClipControl(origin, depth);
}

static void CODEGEN_FUNCPTR Switch_CompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
{
	_ptrc_glCompressedTextureSubImage1D = (PFN_PTRC_GLCOMPRESSEDTEXTURESUBIMAGE1DPROC)IntGetProcAddress("glCompressedTextureSubImage1D");
	_ptrc_glCompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_CompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
{
	_ptrc_glCompressedTextureSubImage2D = (PFN_PTRC_GLCOMPRESSEDTEXTURESUBIMAGE2DPROC)IntGetProcAddress("glCompressedTextureSubImage2D");
	_ptrc_glCompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_CompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data)
{
	_ptrc_glCompressedTextureSubImage3D = (PFN_PTRC_GLCOMPRESSEDTEXTURESUBIMAGE3DPROC)IntGetProcAddress("glCompressedTextureSubImage3D");
	_ptrc_glCompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

static void CODEGEN_FUNCPTR Switch_CopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
	_ptrc_glCopyNamedBufferSubData = (PFN_PTRC_GLCOPYNAMEDBUFFERSUBDATAPROC)IntGetProcAddress("glCopyNamedBufferSubData");
	_ptrc_glCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
}

static void CODEGEN_FUNCPTR Switch_CopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
	_ptrc_glCopyTextureSubImage1D = (PFN_PTRC_GLCOPYTEXTURESUBIMAGE1DPROC)IntGetProcAddress("glCopyTextureSubImage1D");
	_ptrc_glCopyTextureSubImage1D(texture, level, xoffset, x, y, width);
}

static void CODEGEN_FUNCPTR Switch_CopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_ptrc_glCopyTextureSubImage2D = (PFN_PTRC_GLCOPYTEXTURESUBIMAGE2DPROC)IntGetProcAddress("glCopyTextureSubImage2D");
	_ptrc_glCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
}

static void CODEGEN_FUNCPTR Switch_CopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_ptrc_glCopyTextureSubImage3D = (PFN_PTRC_GLCOPYTEXTURESUBIMAGE3DPROC)IntGetProcAddress("glCopyTextureSubImage3D");
	_ptrc_glCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
}

static void CODEGEN_FUNCPTR Switch_CreateBuffers(GLsizei n, GLuint * buffers)
{
	_ptrc_glCreateBuffers = (PFN_PTRC_GLCREATEBUFFERSPROC)IntGetProcAddress("glCreateBuffers");
	_ptrc_glCreateBuffers(n, buffers);
}

static void CODEGEN_FUNCPTR Switch_CreateFramebuffers(GLsizei n, GLuint * framebuffers)
{
	_ptrc_glCreateFramebuffers = (PFN_PTRC_GLCREATEFRAMEBUFFERSPROC)IntGetProcAddress("glCreateFramebuffers");
	_ptrc_glCreateFramebuffers(n, framebuffers);
}

static void CODEGEN_FUNCPTR Switch_CreateProgramPipelines(GLsizei n, GLuint * pipelines)
{
	_ptrc_glCreateProgramPipelines = (PFN_PTRC_GLCREATEPROGRAMPIPELINESPROC)IntGetProcAddress("glCreateProgramPipelines");
	_ptrc_glCreateProgramPipelines(n, pipelines);
}

static void CODEGEN_FUNCPTR Switch_CreateQueries(GLenum target, GLsizei n, GLuint * ids)
{
	_ptrc_glCreateQueries = (PFN_PTRC_GLCREATEQUERIESPROC)IntGetProcAddress("glCreateQueries");
	_ptrc_glCreateQueries(target, n, ids);
}

static void CODEGEN_FUNCPTR Switch_CreateRenderbuffers(GLsizei n, GLuint * renderbuffers)
{
	_ptrc_glCreateRenderbuffers = (PFN_PTRC_GLCREATERENDERBUFFERSPROC)IntGetProcAddress("glCreateRenderbuffers");
	_ptrc_glCreateRenderbuffers(n, renderbuffers);
}

static void CODEGEN_FUNCPTR Switch_CreateSamplers(GLsizei n, GLuint * samplers)
{
	_ptrc_glCreateSamplers = (PFN_PTRC_GLCREATESAMPLERSPROC)IntGetProcAddress("glCreateSamplers");
	_ptrc_glCreateSamplers(n, samplers);
}

static void CODEGEN_FUNCPTR Switch_CreateTextures(GLenum target, GLsizei n, GLuint * textures)
{
	_ptrc_glCreateTextures = (PFN_PTRC_GLCREATETEXTURESPROC)IntGetProcAddress("glCreateTextures");
	_ptrc_glCreateTextures(target, n, textures);
}

static void CODEGEN_FUNCPTR Switch_CreateTransformFeedbacks(GLsizei n, GLuint * ids)
{
	_ptrc_glCreateTransformFeedbacks = (PFN_PTRC_GLCREATETRANSFORMFEEDBACKSPROC)IntGetProcAddress("glCreateTransformFeedbacks");
	_ptrc_glCreateTransformFeedbacks(n, ids);
}

static void CODEGEN_FUNCPTR Switch_CreateVertexArrays(GLsizei n, GLuint * arrays)
{
	_ptrc_glCreateVertexArrays = (PFN_PTRC_GLCREATEVERTEXARRAYSPROC)IntGetProcAddress("glCreateVertexArrays");
	_ptrc_glCreateVertexArrays(n, arrays);
}

static void CODEGEN_FUNCPTR Switch_DisableVertexArrayAttrib(GLuint vaobj, GLuint index)
{
	_ptrc_glDisableVertexArrayAttrib = (PFN_PTRC_GLDISABLEVERTEXARRAYATTRIBPROC)IntGetProcAddress("glDisableVertexArrayAttrib");
	_ptrc_glDisableVertexArrayAttrib(vaobj, index);
}

static void CODEGEN_FUNCPTR Switch_EnableVertexArrayAttrib(GLuint vaobj, GLuint index)
{
	_ptrc_glEnableVertexArrayAttrib = (PFN_PTRC_GLENABLEVERTEXARRAYATTRIBPROC)IntGetProcAddress("glEnableVertexArrayAttrib");
	_ptrc_glEnableVertexArrayAttrib(vaobj, index);
}

static void CODEGEN_FUNCPTR Switch_FlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length)
{
	_ptrc_glFlushMappedNamedBufferRange = (PFN_PTRC_GLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)IntGetProcAddress("glFlushMappedNamedBufferRange");
	_ptrc_glFlushMappedNamedBufferRange(buffer, offset, length);
}

static void CODEGEN_FUNCPTR Switch_GenerateTextureMipmap(GLuint texture)
{
	_ptrc_glGenerateTextureMipmap = (PFN_PTRC_GLGENERATETEXTUREMIPMAPPROC)IntGetProcAddress("glGenerateTextureMipmap");
	_ptrc_glGenerateTextureMipmap(texture);
}

static void CODEGEN_FUNCPTR Switch_GetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void * pixels)
{
	_ptrc_glGetCompressedTextureImage = (PFN_PTRC_GLGETCOMPRESSEDTEXTUREIMAGEPROC)IntGetProcAddress("glGetCompressedTextureImage");
	_ptrc_glGetCompressedTextureImage(texture, level, bufSize, pixels);
}

static void CODEGEN_FUNCPTR Switch_GetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void * pixels)
{
	_ptrc_glGetCompressedTextureSubImage = (PFN_PTRC_GLGETCOMPRESSEDTEXTURESUBIMAGEPROC)IntGetProcAddress("glGetCompressedTextureSubImage");
	_ptrc_glGetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
}

static GLenum CODEGEN_FUNCPTR Switch_GetGraphicsResetStatus(void)
{
	_ptrc_glGetGraphicsResetStatus = (PFN_PTRC_GLGETGRAPHICSRESETSTATUSPROC)IntGetProcAddress("glGetGraphicsResetStatus");
	return _ptrc_glGetGraphicsResetStatus();
}

static void CODEGEN_FUNCPTR Switch_GetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 * params)
{
	_ptrc_glGetNamedBufferParameteri64v = (PFN_PTRC_GLGETNAMEDBUFFERPARAMETERI64VPROC)IntGetProcAddress("glGetNamedBufferParameteri64v");
	_ptrc_glGetNamedBufferParameteri64v(buffer, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint * params)
{
	_ptrc_glGetNamedBufferParameteriv = (PFN_PTRC_GLGETNAMEDBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetNamedBufferParameteriv");
	_ptrc_glGetNamedBufferParameteriv(buffer, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetNamedBufferPointerv(GLuint buffer, GLenum pname, void ** params)
{
	_ptrc_glGetNamedBufferPointerv = (PFN_PTRC_GLGETNAMEDBUFFERPOINTERVPROC)IntGetProcAddress("glGetNamedBufferPointerv");
	_ptrc_glGetNamedBufferPointerv(buffer, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void * data)
{
	_ptrc_glGetNamedBufferSubData = (PFN_PTRC_GLGETNAMEDBUFFERSUBDATAPROC)IntGetProcAddress("glGetNamedBufferSubData");
	_ptrc_glGetNamedBufferSubData(buffer, offset, size, data);
}

static void CODEGEN_FUNCPTR Switch_GetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params)
{
	_ptrc_glGetNamedFramebufferAttachmentParameteriv = (PFN_PTRC_GLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)IntGetProcAddress("glGetNamedFramebufferAttachmentParameteriv");
	_ptrc_glGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint * param)
{
	_ptrc_glGetNamedFramebufferParameteriv = (PFN_PTRC_GLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetNamedFramebufferParameteriv");
	_ptrc_glGetNamedFramebufferParameteriv(framebuffer, pname, param);
}

static void CODEGEN_FUNCPTR Switch_GetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint * params)
{
	_ptrc_glGetNamedRenderbufferParameteriv = (PFN_PTRC_GLGETNAMEDRENDERBUFFERPARAMETERIVPROC)IntGetProcAddress("glGetNamedRenderbufferParameteriv");
	_ptrc_glGetNamedRenderbufferParameteriv(renderbuffer, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
	_ptrc_glGetQueryBufferObjecti64v = (PFN_PTRC_GLGETQUERYBUFFEROBJECTI64VPROC)IntGetProcAddress("glGetQueryBufferObjecti64v");
	_ptrc_glGetQueryBufferObjecti64v(id, buffer, pname, offset);
}

static void CODEGEN_FUNCPTR Switch_GetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
	_ptrc_glGetQueryBufferObjectiv = (PFN_PTRC_GLGETQUERYBUFFEROBJECTIVPROC)IntGetProcAddress("glGetQueryBufferObjectiv");
	_ptrc_glGetQueryBufferObjectiv(id, buffer, pname, offset);
}

static void CODEGEN_FUNCPTR Switch_GetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
	_ptrc_glGetQueryBufferObjectui64v = (PFN_PTRC_GLGETQUERYBUFFEROBJECTUI64VPROC)IntGetProcAddress("glGetQueryBufferObjectui64v");
	_ptrc_glGetQueryBufferObjectui64v(id, buffer, pname, offset);
}

static void CODEGEN_FUNCPTR Switch_GetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
	_ptrc_glGetQueryBufferObjectuiv = (PFN_PTRC_GLGETQUERYBUFFEROBJECTUIVPROC)IntGetProcAddress("glGetQueryBufferObjectuiv");
	_ptrc_glGetQueryBufferObjectuiv(id, buffer, pname, offset);
}

static void CODEGEN_FUNCPTR Switch_GetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
{
	_ptrc_glGetTextureImage = (PFN_PTRC_GLGETTEXTUREIMAGEPROC)IntGetProcAddress("glGetTextureImage");
	_ptrc_glGetTextureImage(texture, level, format, type, bufSize, pixels);
}

static void CODEGEN_FUNCPTR Switch_GetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat * params)
{
	_ptrc_glGetTextureLevelParameterfv = (PFN_PTRC_GLGETTEXTURELEVELPARAMETERFVPROC)IntGetProcAddress("glGetTextureLevelParameterfv");
	_ptrc_glGetTextureLevelParameterfv(texture, level, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint * params)
{
	_ptrc_glGetTextureLevelParameteriv = (PFN_PTRC_GLGETTEXTURELEVELPARAMETERIVPROC)IntGetProcAddress("glGetTextureLevelParameteriv");
	_ptrc_glGetTextureLevelParameteriv(texture, level, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTextureParameterIiv(GLuint texture, GLenum pname, GLint * params)
{
	_ptrc_glGetTextureParameterIiv = (PFN_PTRC_GLGETTEXTUREPARAMETERIIVPROC)IntGetProcAddress("glGetTextureParameterIiv");
	_ptrc_glGetTextureParameterIiv(texture, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint * params)
{
	_ptrc_glGetTextureParameterIuiv = (PFN_PTRC_GLGETTEXTUREPARAMETERIUIVPROC)IntGetProcAddress("glGetTextureParameterIuiv");
	_ptrc_glGetTextureParameterIuiv(texture, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTextureParameterfv(GLuint texture, GLenum pname, GLfloat * params)
{
	_ptrc_glGetTextureParameterfv = (PFN_PTRC_GLGETTEXTUREPARAMETERFVPROC)IntGetProcAddress("glGetTextureParameterfv");
	_ptrc_glGetTextureParameterfv(texture, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTextureParameteriv(GLuint texture, GLenum pname, GLint * params)
{
	_ptrc_glGetTextureParameteriv = (PFN_PTRC_GLGETTEXTUREPARAMETERIVPROC)IntGetProcAddress("glGetTextureParameteriv");
	_ptrc_glGetTextureParameteriv(texture, pname, params);
}

static void CODEGEN_FUNCPTR Switch_GetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
{
	_ptrc_glGetTextureSubImage = (PFN_PTRC_GLGETTEXTURESUBIMAGEPROC)IntGetProcAddress("glGetTextureSubImage");
	_ptrc_glGetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
}

static void CODEGEN_FUNCPTR Switch_GetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 * param)
{
	_ptrc_glGetTransformFeedbacki64_v = (PFN_PTRC_GLGETTRANSFORMFEEDBACKI64_VPROC)IntGetProcAddress("glGetTransformFeedbacki64_v");
	_ptrc_glGetTransformFeedbacki64_v(xfb, pname, index, param);
}

static void CODEGEN_FUNCPTR Switch_GetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint * param)
{
	_ptrc_glGetTransformFeedbacki_v = (PFN_PTRC_GLGETTRANSFORMFEEDBACKI_VPROC)IntGetProcAddress("glGetTransformFeedbacki_v");
	_ptrc_glGetTransformFeedbacki_v(xfb, pname, index, param);
}

static void CODEGEN_FUNCPTR Switch_GetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint * param)
{
	_ptrc_glGetTransformFeedbackiv = (PFN_PTRC_GLGETTRANSFORMFEEDBACKIVPROC)IntGetProcAddress("glGetTransformFeedbackiv");
	_ptrc_glGetTransformFeedbackiv(xfb, pname, param);
}

static void CODEGEN_FUNCPTR Switch_GetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param)
{
	_ptrc_glGetVertexArrayIndexed64iv = (PFN_PTRC_GLGETVERTEXARRAYINDEXED64IVPROC)IntGetProcAddress("glGetVertexArrayIndexed64iv");
	_ptrc_glGetVertexArrayIndexed64iv(vaobj, index, pname, param);
}

static void CODEGEN_FUNCPTR Switch_GetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint * param)
{
	_ptrc_glGetVertexArrayIndexediv = (PFN_PTRC_GLGETVERTEXARRAYINDEXEDIVPROC)IntGetProcAddress("glGetVertexArrayIndexediv");
	_ptrc_glGetVertexArrayIndexediv(vaobj, index, pname, param);
}

static void CODEGEN_FUNCPTR Switch_GetVertexArrayiv(GLuint vaobj, GLenum pname, GLint * param)
{
	_ptrc_glGetVertexArrayiv = (PFN_PTRC_GLGETVERTEXARRAYIVPROC)IntGetProcAddress("glGetVertexArrayiv");
	_ptrc_glGetVertexArrayiv(vaobj, pname, param);
}

static void CODEGEN_FUNCPTR Switch_GetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void * pixels)
{
	_ptrc_glGetnCompressedTexImage = (PFN_PTRC_GLGETNCOMPRESSEDTEXIMAGEPROC)IntGetProcAddress("glGetnCompressedTexImage");
	_ptrc_glGetnCompressedTexImage(target, lod, bufSize, pixels);
}

static void CODEGEN_FUNCPTR Switch_GetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
{
	_ptrc_glGetnTexImage = (PFN_PTRC_GLGETNTEXIMAGEPROC)IntGetProcAddress("glGetnTexImage");
	_ptrc_glGetnTexImage(target, level, format, type, bufSize, pixels);
}

static void CODEGEN_FUNCPTR Switch_GetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble * params)
{
	_ptrc_glGetnUniformdv = (PFN_PTRC_GLGETNUNIFORMDVPROC)IntGetProcAddress("glGetnUniformdv");
	_ptrc_glGetnUniformdv(program, location, bufSize, params);
}

static void CODEGEN_FUNCPTR Switch_GetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat * params)
{
	_ptrc_glGetnUniformfv = (PFN_PTRC_GLGETNUNIFORMFVPROC)IntGetProcAddress("glGetnUniformfv");
	_ptrc_glGetnUniformfv(program, location, bufSize, params);
}

static void CODEGEN_FUNCPTR Switch_GetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint * params)
{
	_ptrc_glGetnUniformiv = (PFN_PTRC_GLGETNUNIFORMIVPROC)IntGetProcAddress("glGetnUniformiv");
	_ptrc_glGetnUniformiv(program, location, bufSize, params);
}

static void CODEGEN_FUNCPTR Switch_GetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint * params)
{
	_ptrc_glGetnUniformuiv = (PFN_PTRC_GLGETNUNIFORMUIVPROC)IntGetProcAddress("glGetnUniformuiv");
	_ptrc_glGetnUniformuiv(program, location, bufSize, params);
}

static void CODEGEN_FUNCPTR Switch_InvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments)
{
	_ptrc_glInvalidateNamedFramebufferData = (PFN_PTRC_GLINVALIDATENAMEDFRAMEBUFFERDATAPROC)IntGetProcAddress("glInvalidateNamedFramebufferData");
	_ptrc_glInvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);
}

static void CODEGEN_FUNCPTR Switch_InvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
	_ptrc_glInvalidateNamedFramebufferSubData = (PFN_PTRC_GLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)IntGetProcAddress("glInvalidateNamedFramebufferSubData");
	_ptrc_glInvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);
}

static void * CODEGEN_FUNCPTR Switch_MapNamedBuffer(GLuint buffer, GLenum access)
{
	_ptrc_glMapNamedBuffer = (PFN_PTRC_GLMAPNAMEDBUFFERPROC)IntGetProcAddress("glMapNamedBuffer");
	return _ptrc_glMapNamedBuffer(buffer, access);
}

static void * CODEGEN_FUNCPTR Switch_MapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	_ptrc_glMapNamedBufferRange = (PFN_PTRC_GLMAPNAMEDBUFFERRANGEPROC)IntGetProcAddress("glMapNamedBufferRange");
	return _ptrc_glMapNamedBufferRange(buffer, offset, length, access);
}

static void CODEGEN_FUNCPTR Switch_MemoryBarrierByRegion(GLbitfield barriers)
{
	_ptrc_glMemoryBarrierByRegion = (PFN_PTRC_GLMEMORYBARRIERBYREGIONPROC)IntGetProcAddress("glMemoryBarrierByRegion");
	_ptrc_glMemoryBarrierByRegion(barriers);
}

static void CODEGEN_FUNCPTR Switch_NamedBufferData(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage)
{
	_ptrc_glNamedBufferData = (PFN_PTRC_GLNAMEDBUFFERDATAPROC)IntGetProcAddress("glNamedBufferData");
	_ptrc_glNamedBufferData(buffer, size, data, usage);
}

static void CODEGEN_FUNCPTR Switch_NamedBufferStorage(GLuint buffer, GLsizeiptr size, const void * data, GLbitfield flags)
{
	_ptrc_glNamedBufferStorage = (PFN_PTRC_GLNAMEDBUFFERSTORAGEPROC)IntGetProcAddress("glNamedBufferStorage");
	_ptrc_glNamedBufferStorage(buffer, size, data, flags);
}

static void CODEGEN_FUNCPTR Switch_NamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data)
{
	_ptrc_glNamedBufferSubData = (PFN_PTRC_GLNAMEDBUFFERSUBDATAPROC)IntGetProcAddress("glNamedBufferSubData");
	_ptrc_glNamedBufferSubData(buffer, offset, size, data);
}

static void CODEGEN_FUNCPTR Switch_NamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf)
{
	_ptrc_glNamedFramebufferDrawBuffer = (PFN_PTRC_GLNAMEDFRAMEBUFFERDRAWBUFFERPROC)IntGetProcAddress("glNamedFramebufferDrawBuffer");
	_ptrc_glNamedFramebufferDrawBuffer(framebuffer, buf);
}

static void CODEGEN_FUNCPTR Switch_NamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum * bufs)
{
	_ptrc_glNamedFramebufferDrawBuffers = (PFN_PTRC_GLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)IntGetProcAddress("glNamedFramebufferDrawBuffers");
	_ptrc_glNamedFramebufferDrawBuffers(framebuffer, n, bufs);
}

static void CODEGEN_FUNCPTR Switch_NamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param)
{
	_ptrc_glNamedFramebufferParameteri = (PFN_PTRC_GLNAMEDFRAMEBUFFERPARAMETERIPROC)IntGetProcAddress("glNamedFramebufferParameteri");
	_ptrc_glNamedFramebufferParameteri(framebuffer, pname, param);
}

static void CODEGEN_FUNCPTR Switch_NamedFramebufferReadBuffer(GLuint framebuffer, GLenum src)
{
	_ptrc_glNamedFramebufferReadBuffer = (PFN_PTRC_GLNAMEDFRAMEBUFFERREADBUFFERPROC)IntGetProcAddress("glNamedFramebufferReadBuffer");
	_ptrc_glNamedFramebufferReadBuffer(framebuffer, src);
}

static void CODEGEN_FUNCPTR Switch_NamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	_ptrc_glNamedFramebufferRenderbuffer = (PFN_PTRC_GLNAMEDFRAMEBUFFERRENDERBUFFERPROC)IntGetProcAddress("glNamedFramebufferRenderbuffer");
	_ptrc_glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
}

static void CODEGEN_FUNCPTR Switch_NamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level)
{
	_ptrc_glNamedFramebufferTexture = (PFN_PTRC_GLNAMEDFRAMEBUFFERTEXTUREPROC)IntGetProcAddress("glNamedFramebufferTexture");
	_ptrc_glNamedFramebufferTexture(framebuffer, attachment, texture, level);
}

static void CODEGEN_FUNCPTR Switch_NamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
	_ptrc_glNamedFramebufferTextureLayer = (PFN_PTRC_GLNAMEDFRAMEBUFFERTEXTURELAYERPROC)IntGetProcAddress("glNamedFramebufferTextureLayer");
	_ptrc_glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
}

static void CODEGEN_FUNCPTR Switch_NamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height)
{
	_ptrc_glNamedRenderbufferStorage = (PFN_PTRC_GLNAMEDRENDERBUFFERSTORAGEPROC)IntGetProcAddress("glNamedRenderbufferStorage");
	_ptrc_glNamedRenderbufferStorage(renderbuffer, internalformat, width, height);
}

static void CODEGEN_FUNCPTR Switch_NamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	_ptrc_glNamedRenderbufferStorageMultisample = (PFN_PTRC_GLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)IntGetProcAddress("glNamedRenderbufferStorageMultisample");
	_ptrc_glNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
}

static void CODEGEN_FUNCPTR Switch_ReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data)
{
	_ptrc_glReadnPixels = (PFN_PTRC_GLREADNPIXELSPROC)IntGetProcAddress("glReadnPixels");
	_ptrc_glReadnPixels(x, y, width, height, format, type, bufSize, data);
}

static void CODEGEN_FUNCPTR Switch_TextureBarrier(void)
{
	_ptrc_glTextureBarrier = (PFN_PTRC_GLTEXTUREBARRIERPROC)IntGetProcAddress("glTextureBarrier");
	_ptrc_glTextureBarrier();
}

static void CODEGEN_FUNCPTR Switch_TextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer)
{
	_ptrc_glTextureBuffer = (PFN_PTRC_GLTEXTUREBUFFERPROC)IntGetProcAddress("glTextureBuffer");
	_ptrc_glTextureBuffer(texture, internalformat, buffer);
}

static void CODEGEN_FUNCPTR Switch_TextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	_ptrc_glTextureBufferRange = (PFN_PTRC_GLTEXTUREBUFFERRANGEPROC)IntGetProcAddress("glTextureBufferRange");
	_ptrc_glTextureBufferRange(texture, internalformat, buffer, offset, size);
}

static void CODEGEN_FUNCPTR Switch_TextureParameterIiv(GLuint texture, GLenum pname, const GLint * params)
{
	_ptrc_glTextureParameterIiv = (PFN_PTRC_GLTEXTUREPARAMETERIIVPROC)IntGetProcAddress("glTextureParameterIiv");
	_ptrc_glTextureParameterIiv(texture, pname, params);
}

static void CODEGEN_FUNCPTR Switch_TextureParameterIuiv(GLuint texture, GLenum pname, const GLuint * params)
{
	_ptrc_glTextureParameterIuiv = (PFN_PTRC_GLTEXTUREPARAMETERIUIVPROC)IntGetProcAddress("glTextureParameterIuiv");
	_ptrc_glTextureParameterIuiv(texture, pname, params);
}

static void CODEGEN_FUNCPTR Switch_TextureParameterf(GLuint texture, GLenum pname, GLfloat param)
{
	_ptrc_glTextureParameterf = (PFN_PTRC_GLTEXTUREPARAMETERFPROC)IntGetProcAddress("glTextureParameterf");
	_ptrc_glTextureParameterf(texture, pname, param);
}

static void CODEGEN_FUNCPTR Switch_TextureParameterfv(GLuint texture, GLenum pname, const GLfloat * param)
{
	_ptrc_glTextureParameterfv = (PFN_PTRC_GLTEXTUREPARAMETERFVPROC)IntGetProcAddress("glTextureParameterfv");
	_ptrc_glTextureParameterfv(texture, pname, param);
}

static void CODEGEN_FUNCPTR Switch_TextureParameteri(GLuint texture, GLenum pname, GLint param)
{
	_ptrc_glTextureParameteri = (PFN_PTRC_GLTEXTUREPARAMETERIPROC)IntGetProcAddress("glTextureParameteri");
	_ptrc_glTextureParameteri(texture, pname, param);
}

static void CODEGEN_FUNCPTR Switch_TextureParameteriv(GLuint texture, GLenum pname, const GLint * param)
{
	_ptrc_glTextureParameteriv = (PFN_PTRC_GLTEXTUREPARAMETERIVPROC)IntGetProcAddress("glTextureParameteriv");
	_ptrc_glTextureParameteriv(texture, pname, param);
}

static void CODEGEN_FUNCPTR Switch_TextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width)
{
	_ptrc_glTextureStorage1D = (PFN_PTRC_GLTEXTURESTORAGE1DPROC)IntGetProcAddress("glTextureStorage1D");
	_ptrc_glTextureStorage1D(texture, levels, internalformat, width);
}

static void CODEGEN_FUNCPTR Switch_TextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	_ptrc_glTextureStorage2D = (PFN_PTRC_GLTEXTURESTORAGE2DPROC)IntGetProcAddress("glTextureStorage2D");
	_ptrc_glTextureStorage2D(texture, levels, internalformat, width, height);
}

static void CODEGEN_FUNCPTR Switch_TextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	_ptrc_glTextureStorage2DMultisample = (PFN_PTRC_GLTEXTURESTORAGE2DMULTISAMPLEPROC)IntGetProcAddress("glTextureStorage2DMultisample");
	_ptrc_glTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
}

static void CODEGEN_FUNCPTR Switch_TextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	_ptrc_glTextureStorage3D = (PFN_PTRC_GLTEXTURESTORAGE3DPROC)IntGetProcAddress("glTextureStorage3D");
	_ptrc_glTextureStorage3D(texture, levels, internalformat, width, height, depth);
}

static void CODEGEN_FUNCPTR Switch_TextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	_ptrc_glTextureStorage3DMultisample = (PFN_PTRC_GLTEXTURESTORAGE3DMULTISAMPLEPROC)IntGetProcAddress("glTextureStorage3DMultisample");
	_ptrc_glTextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
}

static void CODEGEN_FUNCPTR Switch_TextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
{
	_ptrc_glTextureSubImage1D = (PFN_PTRC_GLTEXTURESUBIMAGE1DPROC)IntGetProcAddress("glTextureSubImage1D");
	_ptrc_glTextureSubImage1D(texture, level, xoffset, width, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_TextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
{
	_ptrc_glTextureSubImage2D = (PFN_PTRC_GLTEXTURESUBIMAGE2DPROC)IntGetProcAddress("glTextureSubImage2D");
	_ptrc_glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_TextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels)
{
	_ptrc_glTextureSubImage3D = (PFN_PTRC_GLTEXTURESUBIMAGE3DPROC)IntGetProcAddress("glTextureSubImage3D");
	_ptrc_glTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

static void CODEGEN_FUNCPTR Switch_TransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer)
{
	_ptrc_glTransformFeedbackBufferBase = (PFN_PTRC_GLTRANSFORMFEEDBACKBUFFERBASEPROC)IntGetProcAddress("glTransformFeedbackBufferBase");
	_ptrc_glTransformFeedbackBufferBase(xfb, index, buffer);
}

static void CODEGEN_FUNCPTR Switch_TransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	_ptrc_glTransformFeedbackBufferRange = (PFN_PTRC_GLTRANSFORMFEEDBACKBUFFERRANGEPROC)IntGetProcAddress("glTransformFeedbackBufferRange");
	_ptrc_glTransformFeedbackBufferRange(xfb, index, buffer, offset, size);
}

static GLboolean CODEGEN_FUNCPTR Switch_UnmapNamedBuffer(GLuint buffer)
{
	_ptrc_glUnmapNamedBuffer = (PFN_PTRC_GLUNMAPNAMEDBUFFERPROC)IntGetProcAddress("glUnmapNamedBuffer");
	return _ptrc_glUnmapNamedBuffer(buffer);
}

static void CODEGEN_FUNCPTR Switch_VertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex)
{
	_ptrc_glVertexArrayAttribBinding = (PFN_PTRC_GLVERTEXARRAYATTRIBBINDINGPROC)IntGetProcAddress("glVertexArrayAttribBinding");
	_ptrc_glVertexArrayAttribBinding(vaobj, attribindex, bindingindex);
}

static void CODEGEN_FUNCPTR Switch_VertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
	_ptrc_glVertexArrayAttribFormat = (PFN_PTRC_GLVERTEXARRAYATTRIBFORMATPROC)IntGetProcAddress("glVertexArrayAttribFormat");
	_ptrc_glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
}

static void CODEGEN_FUNCPTR Switch_VertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
	_ptrc_glVertexArrayAttribIFormat = (PFN_PTRC_GLVERTEXARRAYATTRIBIFORMATPROC)IntGetProcAddress("glVertexArrayAttribIFormat");
	_ptrc_glVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
}

static void CODEGEN_FUNCPTR Switch_VertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
	_ptrc_glVertexArrayAttribLFormat = (PFN_PTRC_GLVERTEXARRAYATTRIBLFORMATPROC)IntGetProcAddress("glVertexArrayAttribLFormat");
	_ptrc_glVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
}

static void CODEGEN_FUNCPTR Switch_VertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor)
{
	_ptrc_glVertexArrayBindingDivisor = (PFN_PTRC_GLVERTEXARRAYBINDINGDIVISORPROC)IntGetProcAddress("glVertexArrayBindingDivisor");
	_ptrc_glVertexArrayBindingDivisor(vaobj, bindingindex, divisor);
}

static void CODEGEN_FUNCPTR Switch_VertexArrayElementBuffer(GLuint vaobj, GLuint buffer)
{
	_ptrc_glVertexArrayElementBuffer = (PFN_PTRC_GLVERTEXARRAYELEMENTBUFFERPROC)IntGetProcAddress("glVertexArrayElementBuffer");
	_ptrc_glVertexArrayElementBuffer(vaobj, buffer);
}

static void CODEGEN_FUNCPTR Switch_VertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
{
	_ptrc_glVertexArrayVertexBuffer = (PFN_PTRC_GLVERTEXARRAYVERTEXBUFFERPROC)IntGetProcAddress("glVertexArrayVertexBuffer");
	_ptrc_glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
}

static void CODEGEN_FUNCPTR Switch_VertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides)
{
	_ptrc_glVertexArrayVertexBuffers = (PFN_PTRC_GLVERTEXARRAYVERTEXBUFFERSPROC)IntGetProcAddress("glVertexArrayVertexBuffers");
	_ptrc_glVertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);
}



static void ClearExtensionVariables(void)
{
}

typedef struct ogl_MapTable_s
{
	char *extName;
	int *extVariable;
}ogl_MapTable;

static ogl_MapTable g_mappingTable[1]; /*This is intensionally left uninitialized.*/

static void LoadExtByName(const char *extensionName)
{
	ogl_MapTable *tableEnd = &g_mappingTable[0];
	ogl_MapTable *entry = &g_mappingTable[0];
	for(; entry != tableEnd; ++entry)
	{
		if(strcmp(entry->extName, extensionName) == 0)
			break;
	}
	
	if(entry != tableEnd)
		*(entry->extVariable) = 1;
}

void ProcExtsFromExtList(void)
{
	GLint iLoop;
	GLint iNumExtensions = 0;
	_ptrc_glGetIntegerv(GL_NUM_EXTENSIONS, &iNumExtensions);

	for(iLoop = 0; iLoop < iNumExtensions; iLoop++)
	{
		const char *strExtensionName = (const char *)_ptrc_glGetStringi(GL_EXTENSIONS, iLoop);
		LoadExtByName(strExtensionName);
	}
}

void ogl_CheckExtensions()
{
	ClearExtensionVariables();
	
	ProcExtsFromExtList();
}

