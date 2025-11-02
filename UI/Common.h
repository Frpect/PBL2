#ifndef COMMON_H
#define COMMON_H
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<iostream>

//Core
static SDL_Window* window=nullptr;
static SDL_Renderer* screen=nullptr;
static SDL_Event event;

//SCREEN
const int SCREEN_WIDTH=1920;
const int SCREEN_HEIGHT=1080;
const int SCREEN_HPP=32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
#endif