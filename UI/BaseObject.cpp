#include "BaseObject.h"

BaseObject::BaseObject()
{
    obj_=nullptr;
    rect_.x=0;
    rect_.y=0;
    rect_.w=0;
    rect_.h=0;    
}
BaseObject::~BaseObject()
{

}
bool BaseObject::loadImg(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture=nullptr;
    
    SDL_Surface* new_surface=IMG_Load(path.c_str());
    if(new_surface!=nullptr)
    {
        SDL_SetColorKey(new_surface,SDL_TRUE, SDL_MapRGB(new_surface->format, COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
        new_texture=SDL_CreateTextureFromSurface(screen,new_surface);
        if(new_texture!=nullptr)
        {
            rect_.w=new_surface->w;
            rect_.h=new_surface->h;
        }
    }
    SDL_FreeSurface(new_surface);
    obj_=new_texture;
    return obj_!=nullptr;
}
void BaseObject::Render(SDL_Renderer* des_,const SDL_Rect* clip)
{
    SDL_Rect renderquad={rect_.x,rect_.y,rect_.w,rect_.h};
    SDL_RenderCopy(des_,obj_,clip,&renderquad);
}
void BaseObject::Free()
{
    if(obj_!=nullptr)
    {
        SDL_DestroyTexture(obj_);
        obj_=nullptr;
        rect_.w=0;
        rect_.h=0;
    }
    
}

