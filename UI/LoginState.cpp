#include "LoginState.h"


LoginState::LoginState()
{
    tabs_.push_back(std::make_unique<HomeTab>());   // 0
    tabs_.push_back(std::make_unique<RoleTab>());   // 1
    tabs_.push_back(std::make_unique<LoginTab>());  // 2
    currentTab_=0;
}

LoginState::~LoginState()=default;

void LoginState::handleEvent(SDL_Event& e)
{
    if(currentTab_==0)
    {
        tabs_[currentTab_]->handleEvent(e);
        if(tabs_[currentTab_]->status_==DONE) currentTab_++;               
    }
    else if(currentTab_==1)
    {        
        tabs_[currentTab_]->handleEvent(e);
        if(tabs_[currentTab_]->buttons_[0]->isClicked(e)) identity_=GUEST;
        else if(tabs_[currentTab_]->buttons_[1]->isClicked(e)) identity_=STAFF;            
        if(tabs_[currentTab_]->status_==DONE) currentTab_++;
        else if(tabs_[currentTab_]->status_==BACK)
        {   
            tabs_[currentTab_]->status_=DOING;
            currentTab_--;   
            tabs_[currentTab_]->status_=DOING;
        }
    }
    else
    {
        tabs_[currentTab_]->handleEvent(e);
        if(tabs_[currentTab_]->status_==DONE) currentTab_++;
        else if(tabs_[currentTab_]->status_==BACK)
        {   
            tabs_[currentTab_]->status_=DOING;
            currentTab_--;   
            tabs_[currentTab_]->status_=DOING;
        }
    }
}

void LoginState::update()
{

};
void LoginState::render(SDL_Renderer* des_,const SDL_Rect* clip)
{
    tabs_[currentTab_]->render(des_);
}; 
