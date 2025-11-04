#ifndef LOGIN_TAB_H
#define LOGIN_TAB_H

#include"Tab.h"
#include"BaseObject.h"
#include"Button.h"
#include"LoginState.h"
#include<vector>



class HomeTab : public Tab
{
public:
    HomeTab();//load cac image, bg vao truoc
    ~HomeTab();
    void handleEvent(SDL_Event& e);//Handle event cua button
    void update() override;
    void render(SDL_Renderer* des_, const SDL_Rect* clip = nullptr) override;//Render het ra - truyen tham so vi tri
protected:            
};

class RoleTab : public Tab
{
public:
    RoleTab();//load cac image, bg vao truoc
    ~RoleTab();
    void handleEvent(SDL_Event& e) override;//Handle event cua button
    void update() override;
    void render(SDL_Renderer* des_, const SDL_Rect* clip = nullptr) override;//Render het ra - truyen tham so vi tri       
protected:    
      
    
};
class LoginTab : public Tab
{
public:
    LoginTab();//load cac image, bg vao truoc
    ~LoginTab();
    void handleEvent(SDL_Event& e) override;//Handle event cua button
    void update() override;
    void render(SDL_Renderer* des_, const SDL_Rect* clip = nullptr) override;//Render het ra - truyen tham so vi tri
protected:            
};
#endif