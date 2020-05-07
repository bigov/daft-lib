/*
 *		This Code Was Created By Jeff Molofee 2000
 *		Modified by Shawn T. to handle (%3.2f, num) parameters.
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 */

#include <math.h>			  // Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <gl_com_3.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <iostream>

#include "freetype.hpp"	// Header for our little font library.

// This holds all the information for the font that we are going to create.
freetype::font_data our_font;	

HDC			hDC=NULL;		// Private GDI Device Context
//HGLRC		hRC=NULL;		// Permanent Rendering Context
//HWND		hWnd=NULL;		// Holds Our Window Handle
//HINSTANCE	hInstance;		// Holds The Instance Of The Application

GLuint	base;				// Base Display List For The Font Set
GLfloat	cnt1;				// 1st Counter Used To Move Text & For Coloring
GLfloat	cnt2;				// 2nd Counter Used To Move Text & For Coloring

//bool	keys[256];			// Array Used For The Keyboard Routine
//bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
//bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

//LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLvoid BuildFont(GLvoid)								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = gl::GenLists(96);								// Storage For 96 Characters

	font = CreateFont(	-24,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Times New Roman");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font); // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, base);			// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							  // Selects The Font We Want
	DeleteObject(font);									      // Delete The Font
}

GLvoid KillFont(GLvoid)									// Delete The Font List
{
	gl::DeleteLists(base, 96);							// Delete All 96 Characters
}

GLvoid glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	gl::PushAttrib(gl::LIST_BIT);							// Pushes The Display List Bits
	gl::ListBase(base - 32);								// Sets The Base Character to 32
	gl::CallLists(strlen(text), gl::UNSIGNED_BYTE, text);	// Draws The Display List Text
	gl::PopAttrib();										// Pops The Display List Bits
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	gl::ShadeModel(gl::SMOOTH);							// Enable Smooth Shading
	gl::ClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	gl::ClearDepth(1.0f);									// Depth Buffer Setup
	gl::Enable(gl::DEPTH_TEST);							// Enables Depth Testing
	gl::DepthFunc(gl::LEQUAL);								// The Type Of Depth Testing To Do
	gl::Hint(gl::PERSPECTIVE_CORRECTION_HINT, gl::NICEST);	// Really Nice Perspective Calculations

	BuildFont();										// Build The Font

	our_font.init("test.TTF", 16);					    //Build the freetype font

	return TRUE;										// Initialization Went OK
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	gl::LoadIdentity();									// Reset The Current Modelview Matrix
	gl::Translatef(0.0f,0.0f,-1.0f);						// Move One Unit Into The Screen

	// Blue Text
	gl::Color3ub(0,0,0xff);

	// Position The WGL Text On The Screen
	gl::RasterPos2f(-0.40f, 0.35f);
 	glPrint("Active WGL Bitmap Text With NeHe - %7.2f", cnt1);	// Print GL Text To The Screen

	// Here We Print Some Text Using Our FreeType Font
	// The only really important command is the actual print() call,
	// but for the sake of making the results a bit more interesting
	// I have put in some code to rotate and scale the text.

	// Red text
	gl::Color3ub(0xff,0,0);

	gl::PushMatrix();
	gl::LoadIdentity();
	gl::Rotatef(cnt1,0,0,1);
	gl::Scalef(1,.8+.3*cos(cnt1/5),1);
	gl::Translatef(-180,0,0);
	freetype::print(our_font, 320, 240, "Active FreeType Text - %7.2f", cnt1);
	gl::PopMatrix();

	//Uncomment this to test out print's ability to handle newlines.
	//freetype::print(our_font, 320, 200, "Here\nthere\nbe\n\nnewlines\n.", cnt1);

	cnt1+=0.051f;										// Increase The First Counter
	cnt2+=0.005f;										// Increase The First Counter
	return TRUE;										// Everything Went OK
}

void app()
{
	if(0 != SDL_Init(SDL_INIT_EVERYTHING)) 
		throw std::runtime_error("Can't init SDL-lib.");
	
	SDL_Window * win_id;
	int w = 800, h = 600;

	win_id = SDL_CreateWindow( "test", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	
	if(nullptr == win_id)
			throw std::runtime_error("Can't create SDL_WINDOW_OPENGL");
	
	if(!SDL_GL_CreateContext(win_id))
		throw std::runtime_error("Can't create context");

	if(!gl::sys::LoadFunctions())
		throw	std::runtime_error("Can't load OpenGl finctions");
	
	InitGL();

	SDL_Event ev;
	while(ev.window.event != SDL_WINDOWEVENT_CLOSE)
	{
		DrawGLScene();
		SDL_GL_SwapWindow(win_id);
		SDL_PollEvent(&ev);
	}
	return;
}

int main(int argc, char *argv[])
{
	try
	{
		app();
	}
	catch(std::exception & e)
	{
		std::cout << e.what() << "\n\n";
		return EXIT_FAILURE;
	}
	catch(...)
	{
		std::cout << "FAILURE: undefined exception.\n\n";
		return EXIT_FAILURE;
	} 

	*argv[0] = argc;
	return EXIT_SUCCESS;
}

