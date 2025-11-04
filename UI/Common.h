#ifndef COMMON_H
#define COMMON_H
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<iostream>
#include <memory>

extern TTF_Font* font;
//Core
extern SDL_Window* window;
extern SDL_Renderer* screen;
extern SDL_Event event;

//SCREEN
const int SCREEN_WIDTH=1280;
const int SCREEN_HEIGHT=720;
const int SCREEN_HPP=32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
#endif