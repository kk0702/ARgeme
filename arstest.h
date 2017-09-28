#pragma once

#ifndef _DEBUG
#pragma comment(lib, "../lib/ARS.lib")
#pragma comment(lib, "../lib/WML.lib")
#else
#pragma comment(lib, "../lib/ARSd.lib")
#pragma comment(lib, "../lib/WMLd.lib")
#endif



#define _CRT_SECURE_NO_WARNINGS

#define CLASSNAME "ARSTEST"
#define APPNAME "ARSTEST"

class Ball : public Mesh, public Touchable{
public:
	float rand0 = rand() % 35;
	float vx, vy, vx1, vy1 , first_vx = rand0*0.01, first_vy = -0.5;
	int n = 0;
	bool onframe_x,onframe_y;
	void onTouch(Event* ev);
	void move();
	Ball();
	Ball(ARSG* _g, wchar_t fln[]) 
		: Mesh(_g, fln), vx(0.2f), vy(-0.2f), onframe_x(false), onframe_y(false)
	{
		shape = this;
	}
};

class Plate : public Texture, public Touchable{
public:
	float vx, vy;
	void onTouch(Event* ev);
	void move();
	Plate(ARSG* _g, wchar_t fln[])
		: Texture(_g, fln), vx(0.2f), vy(-0.2f)
	{
		shape = this;
	}

};
