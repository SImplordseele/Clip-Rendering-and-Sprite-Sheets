#pragma once
#include "object.hpp"
bool Init() {
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}
		//Create window
		g_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
		if (g_window == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Create renderer for window
			g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
			if (g_screen == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(g_screen, 0xFF, 0xFF, 0xFF, 0xFF);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}
BaseObject::BaseObject() {
	this->text = NULL;
	this->wid = 0;
	this->heig = 0;
}
BaseObject::~BaseObject() {
	free();
}
void BaseObject::free() {
	if (this->text != NULL) {
		SDL_DestroyTexture(this->text);
		this->text = NULL;
		this->wid = 0;
		this->heig = 0;
	}
}
void BaseObject::render(int x, int y, SDL_Rect* clip) {
	SDL_Rect rect = { x,y,this->wid,this->heig };
	if (clip != NULL) {
		rect.w = clip->w;
		rect.h = clip->h;
	}
	SDL_RenderCopy(g_screen, this->text, clip, &rect);
}
int BaseObject::GetHeig() {
	return this->heig;
}
int BaseObject::GetWid() {
	return this->wid;
}
SDL_Texture* BaseObject::GetText() {
	return this->text;
}
bool BaseObject::LoadImg(string path) {
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) return false;
	texture = SDL_CreateTextureFromSurface(g_screen, surface);
	if (texture == NULL) return false;
	this->text = texture;
	this->wid = surface->w;
	this->heig = surface->h;
	return this->text != NULL;
}
bool LoadMedia() {
	if (!g_image.LoadImg("11_clip_rendering_and_sprite_sheets/dots.png")) return false;
	//Set top left sprite
	circle[0].x = 0;
	circle[0].y = 0;
	circle[0].w = 100;
	circle[0].h = 100;

	//Set top right sprite
	circle[1].x = 100;
	circle[1].y = 0;
	circle[1].w = 100;
	circle[1].h = 100;

	//Set bottom left sprite
	circle[2].x = 0;
	circle[2].y = 100;
	circle[2].w = 100;
	circle[2].h = 100;

	//Set bottom right sprite
	circle[3].x = 100;
	circle[3].y = 100;
	circle[3].w = 100;
	circle[3].h = 100;

	return true;
}
void CLOSE() {
	g_image.free();
	SDL_DestroyRenderer(g_screen);
	SDL_DestroyWindow(g_window);
	g_screen = NULL;
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
}