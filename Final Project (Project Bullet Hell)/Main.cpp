/*
 * Name: Corey Dixon
 * Main
 * Project Bullet Hell
 * Date: 3/12/2013
 * Description: Creates a Game, Keyboard and mouse object. Has the main loop
 *				which calls the game loop function. sets up a window and 
 *				call back functions for all input. loads textures into memory.
 *				enables OpenGL for the window, configures OpenGL. draws background
 *				texture.
 *				I DID NOT WRITE EnableOpenGL(), DisableOpenGL(), LoadTexture().
 *				I slightly modified WndProc so it would use my keyboard/mouse class.
 *				Sources: http://www.nullterminator.net/opengl32.html
 *						http://content.gpwiki.org/index.php/LoadTGACpp
 *						http://content.gpwiki.org/index.php/OpenGL:Tutorials:Tutorial_Framework:Base
 *						http://content.gpwiki.org/index.php/OpenGL:Tutorials:Tutorial_Framework:Texture_Mapping
 *						http://content.gpwiki.org/index.php/OpenGL:Tutorials:Tutorial_Framework:Ortho_and_Alpha
 *				This is a bit messy because i'm still learning OpenGL and haven't
 *				read a book on OpenGL yet.
 *				I will be changing this to use GLFW after turning this in.
 *				http://www.glfw.org/
 *				GLFW will maintain the window for me and allow me to port this to
 *				other platforms such as linux & mac.
 */

#include <windows.h>
#include <windowsx.h>
#include <gl/gl.h>
#include <gl/glu.h>
#pragma comment(lib,"opengl32.lib")

#include "keyboard.h"
#include "Mouse.h"
#include "Game.h"
#include "Projectile.h"
#include "tga.h"
#include "Node.h"
#include "Quadtree.h"
#include "GameConstants.h"

// Function Declarations

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);
GLuint LoadTexture(char *TexName);

// functions I wrote
void draw();

// globals
Keyboard keyboard;
Mouse mouse;
Game game(&keyboard, &mouse);

// WinMain

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int iCmdShow)
{
	WNDCLASS wc;
	HWND hWnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	BOOL quit = FALSE;

	int height = 720;
	int width = height * 16 / 9;
	LPCSTR windowName = LPCSTR("Zimhey: Bullet Hell");
	int startLocX = 250;
	int startLocY = 250;

	GLfloat ZIMBLUE[3] = {0, 0.5, 1};
	GLfloat ZIMRED[3] = {1, 0, 0};

	// register window class
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = LPCSTR("GLSample");
	RegisterClass( &wc );

	// create main window
	hWnd = CreateWindow(
		LPCSTR("GLSample"), windowName,
		WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
		startLocY, startLocX, gameWidth+8, gameHeight+26,
		NULL, NULL, hInstance, NULL );


	// enable OpenGL for the window
	EnableOpenGL( hWnd, &hDC, &hRC );
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	float aspect = (float)width / (float)height;

	glOrtho(0, width, height, 0, -100, 100);

	LoadTexture("assets\\texture\\ship.tga");
	LoadTexture("assets\\texture\\projectile.tga");
	LoadTexture("assets\\texture\\background.tga");
	LoadTexture("assets\\texture\\asteroid.tga");
	LoadTexture("assets\\texture\\enemy_ship.tga");
	LoadTexture("assets\\texture\\enemy_projectile.tga");
	LoadTexture("assets\\texture\\error.tga");
	LoadTexture("assets\\texture\\defeat.tga");

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// program main loop
	while ( !quit )
	{

		// check for messages
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )  )
		{

			// handle or dispatch messages
			if ( msg.message == WM_QUIT )
			{
				quit = TRUE;
			}
			else
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}

		}
		else
		{
			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
			glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();

			draw();	// draw background

			game.loop();	// runs our game

			SwapBuffers( hDC );

		}

	}


	// shutdown OpenGL
	DisableOpenGL( hWnd, hDC, hRC );

	// destroy the window explicitly
	DestroyWindow( hWnd );

	return msg.wParam;

}

void draw()
{
	// draw background
	glPushMatrix();
	glColor4f(1.0f,1.0f,1.0f,1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, background);
		glBegin(GL_QUADS);
			glTexCoord2d(0.0,0.0); glVertex3d(0, 0, -90.0);
			glTexCoord2d(1.0,0.0); glVertex3d(1280, 0, -90.0);
			glTexCoord2d(1.0,1.0); glVertex3d(1280, 720, -90.0);
			glTexCoord2d(0.0,1.0); glVertex3d(0, 720, -90.0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glDepthMask(FALSE);
		glDisable(GL_DEPTH_TEST);
	glPopMatrix();
}

// Window Procedure

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_CREATE:
		return 0;

	case WM_CLOSE:
		PostQuitMessage( 0 );
		return 0;

	case WM_DESTROY:
		return 0;

	case WM_MOUSEMOVE:
		mouse.setX( GET_X_LPARAM(lParam) );
		mouse.setY( GET_Y_LPARAM(lParam)/*+26*/ );
		return 0;

	case WM_LBUTTONDOWN:
		mouse.setButtonState(0, true);
		return 0;
	case WM_RBUTTONDOWN:
		mouse.setButtonState(1, true);
		return 0;
	case WM_MBUTTONDOWN:
		mouse.setButtonState(2, true);
		return 0;
	case WM_LBUTTONUP:
		mouse.setButtonState(0, false);
		return 0;
	case WM_RBUTTONUP:
		mouse.setButtonState(1, false);
		return 0;
	case WM_MBUTTONUP:
		mouse.setButtonState(2, false);
		return 0;

	case WM_KEYDOWN:
		keyboard.setKeyState((unsigned int)wParam, true);
		lParam;
		switch ( wParam )
		{
		
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;

		}
		return 0;
	case WM_KEYUP:
		keyboard.setKeyState((unsigned int)wParam, false);
		return 0;
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );

	}

}

// Enable OpenGL

void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC)
{
	PIXELFORMATDESCRIPTOR pfd;
	int format;

	// get the device context (DC)
	*hDC = GetDC( hWnd );

	// set the pixel format for the DC
	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat( *hDC, &pfd );
	SetPixelFormat( *hDC, format, &pfd );

	// create and enable the render context (RC)
	*hRC = wglCreateContext( *hDC );
	wglMakeCurrent( *hDC, *hRC );

}

// Disable OpenGL

void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( hRC );
	ReleaseDC( hWnd, hDC );
}


 GLuint LoadTexture(char *TexName)
  {
   TGAImg Img;        // Image loader
   GLuint Texture;
 
  // Load our Texture
   if(Img.Load(TexName)!=IMG_OK)
    return -1;
 
   glGenTextures(1,&Texture);            // Allocate space for texture
   glBindTexture(GL_TEXTURE_2D,Texture); // Set our Tex handle as current
 
   // Create the texture
    if(Img.GetBPP()==24)
     glTexImage2D(GL_TEXTURE_2D,0,3,Img.GetWidth(),Img.GetHeight(),0,
                  GL_RGB,GL_UNSIGNED_BYTE,Img.GetImg());
    else if(Img.GetBPP()==32)
     glTexImage2D(GL_TEXTURE_2D,0,4,Img.GetWidth(),Img.GetHeight(),0,
                  GL_RGBA,GL_UNSIGNED_BYTE,Img.GetImg());
    else
     return -1;
 
   // Specify filtering and edge actions
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
 
   return Texture;
  }