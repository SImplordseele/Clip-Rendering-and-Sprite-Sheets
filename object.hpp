#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <stdio.h>
using std::cout;
using std::string;
const int screen_width = 640;
const int screen_height = 480;
bool Init();
bool LoadMedia();
void CLOSE();
SDL_Window* g_window = NULL;
SDL_Renderer* g_screen = NULL;
SDL_Event g_event;
class BaseObject {
protected:
	SDL_Texture* text;
	int wid;
	int heig;
public:
	BaseObject();
	~BaseObject();
	void free();
	void render(int,int,SDL_Rect*);
	int GetWid();
	int GetHeig();
	SDL_Texture* GetText();
	bool LoadImg(string);
};
SDL_Rect circle[4];
BaseObject g_image;