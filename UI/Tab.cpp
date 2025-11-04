#include"Tab.h"


Tab::Tab() { };
Tab::~Tab() { };
void Tab::handleEvent(SDL_Event& e)
{
    for(int i=0;i<buttons_.size();i++)
    {
        buttons_[i]->handleEvent(e);
    }
};
void Tab::update()
{

};
void Tab::render(SDL_Renderer* des_, const SDL_Rect* clip)
{      
    bG_.render(des_,clip);
    for(int i=0;i<texts_.size();i++)
    {
        texts_[i].render(des_,clip);
    }
    for(int i=0;i<buttons_.size();i++)
    {
        buttons_[i]->render(des_,clip);
    }
};
    

