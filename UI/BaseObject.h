#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "Common.h"
class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void setRect(const int& x, const int& y) {rect_.x=x;rect_.y=y;}
    SDL_Rect getRect(){return rect_;};
    SDL_Texture* getObj(){return obj_;};

    bool loadImg(std::string path, SDL_Renderer* screen);
    bool render(SDL_Renderer* des_, const SDL_Rect* clip=nullptr);
    void free();
protected:
    SDL_Texture* obj_;
    SDL_Rect rect_;
};

#endif