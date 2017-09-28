#pragma once

#include <cstring>
#include <time.h>
#include <tchar.h>
#include <windows.h>
#define D3D_DEBUG_INFO
#include <stdlib.h>
#include <math.h>
#include <d3dx9.h>
#include <XAudio2.h>
#include <vector>
#include <list>

#include "../include/WindowManager.h"
#include "../include/ars.h"
#include "touchable.h"
#include "arstest.h"

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------


void subtract_mask(Texture* result, Texture* bg, Texture* src, DWORD border);



UINT MainLoop(WindowManager *winmgr)
{
	ShowDebugWindow();
	

	//for debug(1/2)
	//Window window2;
	//winmgr->RegisterWindow(&window2);

	//ARSG arsgd(window2.hWnd, sizex, sizey, true);
	//Texture debug(&arsgd, sizex, sizey);
	//debug.SetDrawMode(true);
	
	Window window;
	winmgr->RegisterWindow(&window);

	ARSG g(window.hWnd, sizex, sizey, true);
	g.SetBackgroundColor(255,0,0,0);

	Light light(&g);	
	g.Register(&light);

	srand((unsigned int)time(NULL));

	ARSD d;
	d.Init();
	d.AttachCam(0);
	d.StartGraph();
	
	Texture hitArea(&g,sizex,sizey);
	Texture stored (&g,sizex,sizey);
	Texture source (&g,sizex,sizey);
	source.SetDrawMode(TRUE);
	g.Register(&source);

	srand(100);

	Ball ball(&g, L"ball.x");	
	ball.SetScale(1.0f, 1.0f, 1.0f);
	ball.SetPosition(0.0f, 8.0f, 0.0f, GL_ABSOLUTE);
	g.Register(&ball);
	
	

	//Plate face(&g,L"face.bmp");
	//face.SetScale(5.0f, 5.0f, 0.5f);
	//face.SetPosition(6.0f, 6.0f, 0.0f, GL_ABSOLUTE);
	//g.Register(&face);



	InputHandler *keyIn = window.GetInputHandler();
	
	while(!d.GetCamImage(&stored));

	while (!winmgr->WaitingForTermination()){
		if (keyIn->GetKeyTrig('A'))
			d.GetCamImage(&stored);
		d.GetCamImage(&source);
		if (keyIn->GetKeyTrig('Q')) break;
			
		subtract_mask(&hitArea,&stored,&source,0x20202020);	
		
		Touchable::update(&hitArea, 100);
		
		
		ball.move();		
		//face.move();

		//for debug(2/2)
		//debug = hitArea;
		//arsgd.Draw(&debug);
		g.Draw();
		
	}
	d.StopGraph();
	return 0;
}

inline void subtract_mask(Texture* result, Texture* backgrnd, Texture* src, DWORD border)
{
	ARSC::diff(result,backgrnd,src,border);
	ARSC::monochrome(result,result);
	ARSC::thresholding(result,result,border);
}

inline void Ball::onTouch(Event* e)
{
	VECTOR2D c = getPosition2D();

	vx =  (c.x - e->x) * 0.1f;
	vy = -(c.y - e->y) * 0.1f;
	vy1 = vy;
	vx1 = vx;
	n = 1;
}

int call_rand(){
	
	
	return  (rand() % 500 - 250);
}

inline void Ball::move()
{

	 static float first_vx = call_rand(), first_vy = -1.;
	
	VECTOR2D c=getPosition2D();


	//˜g‚Ì”½ŽË
	bool side = c.x < 0 || c.x > sizex;
	bool ground = c.y > sizey - 50 && vy < 0||c.y<30;

	if (!onframe_x && side){
		SetPosition(0.0f, 8.0f, 0.0f, GL_ABSOLUTE);
		first_vx = call_rand()*0.01,
		onframe_x = true;
		n = 0;
	}
	else if (onframe_x && !side){ onframe_x = false; }
	

	if (!onframe_y && ground){
		SetPosition(0.0f, 8.0f, 0.0f, GL_ABSOLUTE);
		first_vx = call_rand()*0.01,
		onframe_y = true;
		n = 0;
	}
	else if (onframe_y && !ground){ onframe_y = false; }

	if (n == 2){
		
	}
		if (n == 0){
			vy = first_vy;
			vx = first_vx;
		}
	if (n == 1){
		vy = vy1;
		vx = vx1;
	}
	
	

	SetPosition(vx, vy, 0.0f, GL_RELATIVE);
}

void Plate::onTouch(Event* e)
{

}

void Plate::move()
{

}


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	WindowManager program(hInstance, &MainLoop);
#ifdef DEBUG
    MessageBox(NULL,L"OK?",TEXT(APPNAME), NULL);
#endif
    return 0;
}
